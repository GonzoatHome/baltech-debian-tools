#include "brp_lib/common.h"
#include "brp_lib/usb_hid_protocol.h"
#include "brp_lib/platform.h"
#include "hidapi.h"
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>


#define VENDOR_ID        0x13AD

#define MAX_PATH_SIZE    0x100

const static size_t max_payload_sizes_default[] = { 12, 60, 252, 1020 };
const static size_t max_payload_sizes_cust1[] = { 230 };

#define REPORT_CNT_DEFAULT  (sizeof(max_payload_sizes_default) / sizeof(size_t))
#define REPORT_CNT_CUST1    (sizeof(max_payload_sizes_cust1) / sizeof(size_t))

typedef struct usb_hid_protocol_t
{
	struct brp_protocol_t p;
	long long snr;
	hid_device * hid_device;
	struct brp_frame_t report;
	size_t max_report_size;
	const size_t * max_payload_sizes;
	unsigned report_cnt;
} * usb_hid_protocol;


// Helper function to convert wchar_t string to char string
// Always returns a valid string pointer (never NULL).
// Returns empty string "" if input is NULL or allocation fails.
static char* wchar_to_char(const wchar_t* wstr, brp_mempool* mempool)
{
	static const char empty[] = "";

	if (wstr == NULL)
		return (char*)empty;

	size_t len = wcslen(wstr);
	char* str = (char*) brp_mempool_create_buf(mempool, len + 1);
	if (str == NULL)
		return (char*)empty;

	// Simple ASCII conversion (sufficient for manufacturer/product strings)
	for (size_t i = 0; i < len; i++)
	{
		if (wstr[i] > 0x7F)
			str[i] = '?';  // Replace non-ASCII characters
		else
			str[i] = (char) wstr[i];
	}
	str[len] = '\0';
	return str;
}


// Helper function to check if a HID device is a valid BRP device
static bool is_brp_device(struct hid_device_info* dev)
{
	// Check vendor ID
	if (dev->vendor_id != VENDOR_ID)
		return false;

	// Check product ID (use Baltech default product ID ranges)
	unsigned short pid = dev->product_id;
	if (!(pid >= 40000 && pid <= 40999) &&
	    !(pid >= 1000 && pid <= 1999) &&
	    !((pid & 0xF001) == 0xF001))
		return false;

	// Check if this is the BRP interface of a composite device
	if (dev->usage_page != 0xFF00 || dev->usage != 1)
		return false;

	// Check if serial number is valid (not NULL and numeric)
	if (dev->serial_number == NULL)
		return false;

	long long snr = wcstoll(dev->serial_number, NULL, 10);
	if (snr == 0)
		return false;  // Invalid or non-numeric serial number

	return true;
}


// searches for device matching serialnumber
static brp_errcode probe_device(usb_hid_protocol protocol, char * path)
// (and even sets the serialnumber if 0)
{
	struct hid_device_info * iter;
	struct hid_device_info * dev_info = hid_enumerate(VENDOR_ID, 0);
	bool matching_snr_detected = false;
	bool autodetect_snr = (protocol->snr == 0);

	for (iter = dev_info; iter != NULL; iter = iter->next)
	{
		// Check if this is a valid BRP device
		if (!is_brp_device(iter))
			continue;

		// Check if the serialnumber matches
		// (or more than one device is detected in case of snr==0)
		if (iter->path == NULL)
			/* This may happen if device is disconnected during enumeration
			 * (see SDK-92) */
			continue;
		else if (autodetect_snr)
		{
			if (matching_snr_detected)
			{
				// only ONE device must be connected if snr == 0
				hid_free_enumeration(dev_info);
				return BRP_ERR_AMBIGUOUS_DEVICE;
			}
		}
		else if (protocol->snr != wcstoll(iter->serial_number, NULL, 10))
			continue;

		if (path != NULL)
		{
			if (strlen(iter->path) > MAX_PATH_SIZE)
			{
				hid_free_enumeration(dev_info);
				return BRP_ERR_OUT_OF_MEMORY;
			}
			strcpy(path, iter->path);
		}

		// Save data of detected device to protocol structure
		protocol->snr = wcstoll(iter->serial_number, NULL, 10);

		// Set device metadata based on product ID
		if (iter->product_id >= 40000 && iter->product_id <= 40999)
		{
			protocol->max_payload_sizes = max_payload_sizes_cust1;
			protocol->report_cnt = REPORT_CNT_CUST1;
		}
		else
		{
			protocol->max_payload_sizes = max_payload_sizes_default;
			protocol->report_cnt = REPORT_CNT_DEFAULT;
		}

		// Populate friendly_name from product_string if available
		if (iter->product_string != NULL && protocol->p.friendly_name == NULL)
		{
			protocol->p.friendly_name = wchar_to_char(iter->product_string, &protocol->p.mempool);
		}

		matching_snr_detected = true;

		// if autodetection (snr==0) continue looping and ensure that no other
		// baltech reader is connected.
		if (! autodetect_snr)
			break;
	}

	hid_free_enumeration(dev_info);
	return matching_snr_detected ? BRP_OK : BRP_ERR_NO_DEVICE_FOUND;
}


static brp_errcode open(usb_hid_protocol protocol)
{
	size_t max_payload_size;
	char path[MAX_PATH_SIZE + 1];
	brp_errcode errcode = probe_device(protocol, path);
	if (errcode != BRP_OK)
		return errcode;
	
	protocol->hid_device = hid_open_path(path);
	if (protocol->hid_device == NULL)
		return BRP_ERR_OPEN_IO;
	
	max_payload_size = protocol->max_payload_sizes[protocol->report_cnt - 1];
	
	protocol->max_report_size = 1 + 2 + max_payload_size;
	return BRP_OK;
}


static brp_errcode send_frame(usb_hid_protocol protocol)
{
	int act_send_len;
	brp_errcode errcode;
	brp_frame report = &protocol->report;
	unsigned report_id;
	size_t act_payload_size = (size_t) protocol->p.send_frame.act_size;
	
	for (report_id = 1; report_id <= protocol->report_cnt; report_id++)
		if (act_payload_size <= protocol->max_payload_sizes[report_id - 1])
			break;
	if (report_id > protocol->report_cnt)
		return BRP_ERR_CALLED_INVALID_FRAME;
	
	brp_frame_write_start(report);
	brp_frame_write_int8(report, protocol->report_cnt > 1 ? report_id : 0);
	brp_frame_write_int8(report, (unsigned char)(act_payload_size & 0xFF));
	brp_frame_write_int8(report, (unsigned char)((act_payload_size>>8) & 0xFF));
	brp_frame_write(report, protocol->p.send_frame.ptr, (int)act_payload_size);
	brp_frame_write_fill(
			report,
			0,
			(int) (protocol->max_payload_sizes[report_id - 1] - act_payload_size));
	if (brp_frame_write_err(report))
		return BRP_ERR_OUT_OF_MEMORY;
	
	act_send_len = hid_write(
			protocol->hid_device, report->ptr, (size_t) report->act_size);
	errcode = (act_send_len >= (int) report->act_size)
				? BRP_OK : BRP_ERR_WRITE_IO;
	
	return errcode;
}


static brp_errcode recv_any_frame(usb_hid_protocol protocol, brp_time timeout)
{
	unsigned report_id;
	size_t report_len, act_payload_len, header_len;
	brp_buf recv_buf;
	brp_frame_reader recv_rdr;
	
	brp_frame_write_start(&protocol->report);
	recv_buf = brp_frame_write_buf(&protocol->report,protocol->max_report_size);
	if (recv_buf == NULL)
		return BRP_ERR_OUT_OF_MEMORY;
	
	brp_time start_time = brp_get_time();
	report_len = (size_t) hid_read_timeout(
			protocol->hid_device,
			recv_buf,
			protocol->max_report_size,
			(int) timeout);
	protocol->p.recv_delay = brp_get_time() - start_time;

	if (report_len == -1)
		return BRP_ERR_READ_IO;
	else if (report_len == 0)
	{
		protocol->p.recv_delay = timeout;
		return BRP_ERR_TIMEOUT;
	}
	protocol->report.act_size = report_len;
	
	brp_frame_reader_start(&recv_rdr, &protocol->report);
	if (protocol->report_cnt == 1)
		report_id = 1;
	else
	{
		report_id = brp_frame_read_int8(&recv_rdr);
		if (report_id == 0 || report_id > protocol->report_cnt)
			return BRP_ERR_FRAMEFORMAT;
	}
	act_payload_len = brp_frame_read_int8(&recv_rdr);
	act_payload_len |= brp_frame_read_int8(&recv_rdr) << 8;
	header_len = recv_rdr.ptr - recv_rdr.frame->ptr;
	if (report_len < header_len + protocol->max_payload_sizes[report_id-1])
		return BRP_ERR_FRAMEFORMAT;
	if (act_payload_len > protocol->max_payload_sizes[report_id-1])
		return BRP_ERR_FRAMEFORMAT;
	
	brp_frame_write_start(&protocol->p.recv_frame);
	brp_frame_write_frm(&protocol->p.recv_frame, &recv_rdr, act_payload_len);
	if (brp_frame_write_err(&protocol->p.recv_frame))
		return BRP_ERR_OUT_OF_MEMORY;
	
	return brp_frame_read_err(&recv_rdr) ? BRP_ERR_FRAMEFORMAT : BRP_OK;
}


static brp_errcode flush(usb_hid_protocol protocol)
{
	int report_len;
	brp_buf recv_buf;
	
	brp_frame_write_start(&protocol->report);
	recv_buf = brp_frame_write_buf(&protocol->report,protocol->max_report_size);
	if (recv_buf == NULL)
		return BRP_ERR_OUT_OF_MEMORY;

	do
	{
		report_len = hid_read_timeout(
				protocol->hid_device, recv_buf, protocol->max_report_size, 0);
		if (report_len == -1)
			return BRP_ERR_READ_IO;
	}
	while (report_len > 0);
	return BRP_OK;
}


static brp_errcode get_id(usb_hid_protocol protocol,
		char **intf_name, brp_frame instance_id)
{
	char * snr_str;
	
	if (protocol->snr == 0)
	{
		brp_errcode errcode = probe_device(protocol, NULL);
		if (errcode != BRP_OK)
			return errcode;
	}
	
	brp_frame_write_start(instance_id);
	snr_str = (char*) brp_frame_write_buf(instance_id, 8+1);
	if (snr_str == NULL)
		return BRP_ERR_OUT_OF_MEMORY;
	sprintf(snr_str, "%08lld", protocol->snr % 100000000);
	*intf_name = "USB/HID";
	return BRP_OK;
}


static brp_errcode close(usb_hid_protocol protocol)
{
	hid_close(protocol->hid_device);
	protocol->hid_device = NULL;
	return BRP_OK;
}


static brp_errcode destroy(usb_hid_protocol protocol)
{
	brp_frame_deinit(&protocol->report);
	brp_protocol_free(&protocol->p);
	return BRP_OK;
}


brp_protocol brp_create_usb_hid(long long snr)
{
	usb_hid_protocol protocol;
	protocol = (usb_hid_protocol) brp_protocol_alloc(
		sizeof(struct usb_hid_protocol_t), BRP_PROTID_USB_HID);
	if (protocol == NULL)
		return NULL;
	brp_frame_init(&protocol->report);
	protocol->p.cb_open = (brp_cb_generic_t) open;
	protocol->p.cb_send_frame = (brp_cb_generic_t) send_frame;
	protocol->p.cb_recv_any_frame = (brp_cb_recv_any_frame_t) recv_any_frame;
	protocol->p.cb_flush = (brp_cb_generic_t) flush;
	protocol->p.cb_get_id = (brp_cb_get_id_t) get_id;
	protocol->p.cb_close = (brp_cb_generic_t) close;
	protocol->p.cb_destroy = (brp_cb_generic_t) destroy;
	protocol->snr = snr;
	return (brp_protocol) protocol;
}


// ============================================================================
// USB HID Iterator Implementation
// ============================================================================

// USB HID iterator structure
// Inherits from brp_ioiter_t by having it as the first member
typedef struct brp_ioiter_usb_hid_t
{
	struct brp_ioiter_t base;           // FIRST MEMBER - base iterator
	struct hid_device_info* hid_dev_list;
	struct hid_device_info* current;
} * brp_ioiter_usb_hid;


// USB HID iterator next function
static brp_errcode usb_hid_ioiter_next(brp_ioiter iter, brp_protocol* protocol)
{
	brp_ioiter_usb_hid usb_iter = (brp_ioiter_usb_hid) iter;

	if (protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;

	// Initialize output
	*protocol = NULL;

	// Find next matching device
	while (usb_iter->current != NULL)
	{
		struct hid_device_info* dev = usb_iter->current;

		// Advance iterator before checking (so we're ready for next call)
		usb_iter->current = usb_iter->current->next;

		// Check if this device is a BRP device
		if (!is_brp_device(dev))
			continue;

		// Device matches! Create protocol for it
		long long snr = wcstoll(dev->serial_number, NULL, 10);
		brp_protocol prot = brp_create_usb_hid(snr);
		if (prot == NULL)
			return BRP_ERR_OUT_OF_MEMORY;

		// Populate friendly_name using protocol's mempool
		if (dev->product_string != NULL)
		{
			prot->friendly_name = wchar_to_char(dev->product_string, &prot->mempool);
			// If allocation fails, friendly_name will be empty string (acceptable)
		}

		*protocol = prot;
		return BRP_OK;
	}

	// No more devices
	*protocol = NULL;
	return BRP_OK;
}


// USB HID iterator destroy function
static void usb_hid_ioiter_destroy(brp_ioiter iter)
{
	brp_ioiter_usb_hid usb_iter = (brp_ioiter_usb_hid) iter;

	// Free HID enumeration list
	if (usb_iter->hid_dev_list != NULL)
		hid_free_enumeration(usb_iter->hid_dev_list);
}


brp_ioiter brp_ioiter_create_usb_hid(void)
{
	// Allocate USB HID iterator structure
	brp_ioiter_usb_hid iter = (brp_ioiter_usb_hid) malloc(sizeof(struct brp_ioiter_usb_hid_t));
	if (iter == NULL)
		return NULL;

	// Set up callbacks
	iter->base.next_fn = usb_hid_ioiter_next;
	iter->base.destroy_fn = usb_hid_ioiter_destroy;

	// Enumerate all HID devices with Baltech VID and initialize iterator
	iter->hid_dev_list = hid_enumerate(VENDOR_ID, 0);
	iter->current = iter->hid_dev_list;

	return (brp_ioiter) iter;
}
