#include "brp_lib/rs232_protocol.h"
#include "brp_lib/composite_protocol.h"
#include "rs232.h"
#include "brp_lib/platform.h"
#include "ctype.h"


#if defined(_WIN32)
	#define DEVICE_NAME_PREFIX   "\\\\.\\"
#else
	#define DEVICE_NAME_PREFIX   "/dev/"
#endif


typedef struct rs232_protocol_t {
	struct brp_protocol_t p;
	char * dev_name;
	unsigned baudrate;
	char parity;
	comPort port;
	brp_time interbyte_timeout;
} * rs232_protocol;



static brp_errcode cb_open(rs232_protocol protocol)
{
	int parity;
	switch (protocol->parity)
	{
		case 'N': parity = PARITY_NONE; break;
		case 'O': parity = PARITY_ODD; break;
		case 'E': parity = PARITY_EVEN; break;
	}
	protocol->port = comOpen(protocol->dev_name, protocol->baudrate, parity);
	if (protocol->port == NULL)
		return BRP_ERR_OPEN_IO;
	comSetDtr(protocol->port, true);
	// The DTR Line has to be set to support older CP210X based devices!
	// (Otherwise they will not boot, as the DTR line is connected
	// to RESET pin of uC).
	// But on macOS this command causes trouble, which is why we do not evaluate
	// its result any more (especially as nearly all new readers do not need
	// setting the DTR line)
	return BRP_OK;
}


static brp_errcode cb_close(rs232_protocol protocol)
{
	comClose(protocol->port);
	return BRP_OK;
}


static brp_errcode cb_send_frame(rs232_protocol protocol)
{
	brp_frame send_frame = &protocol->p.send_frame;
	if (brp_frame_write_err(send_frame))
		return BRP_ERR_CALLED_INVALID_FRAME;
	if ((size_t) comWrite(
			protocol->port, (char*)send_frame->ptr, send_frame->act_size)
		< send_frame->act_size)
		return BRP_ERR_WRITE_IO;
	return BRP_OK;
}


static brp_errcode cb_recv_frame(
		rs232_protocol protocol, brp_time timeout,
		brp_cb_fmt_spec_t fmt_spec_callback, void * ctx)
{
	bool is_first_block = true;
	protocol->p.recv_delay = 0;
	while (true)
	{
		brp_buf recv_buf;
		size_t actual_bytes;
		size_t missing_bytes = fmt_spec_callback(&protocol->p.recv_frame, ctx);
		brp_time start_time;
		if (missing_bytes == 0)
			break;
		
		recv_buf = brp_frame_write_buf(&protocol->p.recv_frame, missing_bytes);
		
		if (recv_buf == NULL)
			return BRP_ERR_OUT_OF_MEMORY;
		start_time = brp_get_time();
		actual_bytes = (size_t) comReadBlocking(
			protocol->port,
			(char *) recv_buf,
			missing_bytes,
			protocol->p.recv_delay > timeout ?
				(unsigned) 0 :
				(unsigned) (timeout - protocol->p.recv_delay),
			(unsigned) protocol->interbyte_timeout);
		protocol->p.recv_delay += brp_get_time() - start_time;
		if (actual_bytes == 0 && is_first_block)
		{
			protocol->p.recv_delay = timeout;
			return BRP_ERR_TIMEOUT;
		}
		if (actual_bytes < missing_bytes)
			return BRP_ERR_FRAMEFORMAT;
		is_first_block = false;
	}
	return BRP_OK;
}


static brp_errcode cb_destroy(rs232_protocol protocol)
{
	if (protocol->dev_name != NULL)
		free(protocol->dev_name);
	brp_protocol_free(&protocol->p);
	return BRP_OK;
}


static brp_errcode cb_flush(rs232_protocol protocol)
{
	char dummy_buf[0x10];
	while (comRead(protocol->port, dummy_buf, sizeof(dummy_buf))
	       == sizeof(dummy_buf))
		;
	return BRP_OK;
}


static brp_errcode cb_get_id(rs232_protocol protocol,
		char * * intf_name, brp_frame instance_id)
{
	char *name_iter, *id_iter, chr;
	brp_buf id_buf;
	
	brp_frame_write_start(instance_id);
	id_buf = brp_frame_write_buf(instance_id, strlen(protocol->dev_name) + 1);
	if (id_buf == NULL)
		return BRP_ERR_OUT_OF_MEMORY;
	
	// extract last part of device name "path" (i.e. /dev/ttyS0 -> ttyS0) and
	// convert it to upper case if windows.
	id_iter = (char *) id_buf;
	for (name_iter=protocol->dev_name; (chr = *name_iter) != '\0'; name_iter++)
		if (chr == '/' || chr == '\\')
			id_iter = (char *) id_buf;
		else
		{
			#if WIN32
				chr = toupper(chr);
			#endif
			*id_iter = chr;
			id_iter++;
		}
	*id_iter = '\0';
	instance_id->act_size = id_iter - (char*)id_buf + 1;
	
	*intf_name = "RS232";
	return BRP_OK;
}


brp_protocol brp_create_rs232(char * dev_name, unsigned baudrate, char parity)
{
	if (dev_name == NULL)
		return NULL;
	if (parity != 'N'  &&  parity != 'O'  &&  parity != 'E')
		return NULL;

	rs232_protocol new_protocol = (rs232_protocol) brp_protocol_alloc(
		sizeof(struct rs232_protocol_t), BRP_PROTID_RS232);
	if (new_protocol == NULL)
		return NULL;

	new_protocol->p.cb_destroy = (brp_cb_generic_t) cb_destroy;
	new_protocol->p.cb_open = (brp_cb_generic_t) cb_open;
	new_protocol->p.cb_close = (brp_cb_generic_t) cb_close;
	new_protocol->p.cb_send_frame = (brp_cb_generic_t) cb_send_frame;
	new_protocol->p.cb_recv_frame = (brp_cb_recv_frame_t) cb_recv_frame;
	new_protocol->p.cb_flush = (brp_cb_generic_t) cb_flush;
	new_protocol->p.cb_get_id = (brp_cb_get_id_t) cb_get_id;
	new_protocol->baudrate = baudrate;
	new_protocol->parity = parity;
	new_protocol->interbyte_timeout = BRP_DEFAULT_RS232_INTERBYTE_TIMEOUT;
	if (strncmp(dev_name, DEVICE_NAME_PREFIX, strlen(DEVICE_NAME_PREFIX)) == 0)
		dev_name += strlen(DEVICE_NAME_PREFIX);
	new_protocol->dev_name = malloc(
			strlen(DEVICE_NAME_PREFIX) + strlen(dev_name) + 1);
	if (new_protocol->dev_name == NULL)
	{
		free(new_protocol);
		return NULL;
	}
	strcpy(new_protocol->dev_name, DEVICE_NAME_PREFIX);
	strcat(new_protocol->dev_name, dev_name);

	return (brp_protocol) new_protocol;
}


brp_errcode brp_set_rs232_interbyte_timeout(brp_protocol protocol,
                                            brp_time timeout)
{
	rs232_protocol rs232_prot = (rs232_protocol) require_protocol(
		protocol, BRP_PROTID_RS232, BRP_LAYERID_IO);
	if (rs232_prot == NULL)
		return BRP_ERR_INVALID_API_CALL;
#if defined(_WIN32)
	rs232_prot->interbyte_timeout = timeout;
	return BRP_OK;
#else
	// Interbyte timeout configuration is only supported on Windows
	return BRP_ERR_INVALID_API_CALL;
#endif
}
