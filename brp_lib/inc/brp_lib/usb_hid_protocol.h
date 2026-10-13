/**
 * @file
 * This is the adapter for USB devices that are connected via the
 * Human Interface Device (HID) Protocol.
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */


#ifndef __USBHID_CHANNEL_H__
#define __USBHID_CHANNEL_H__


#include "protocol.h"
#include "ioiter.h"


/**
 * Creates an (USB) HID protocol object from the connected baltech device with
 * serialnumber 'snr'.
 *
 * Please note that this function succeeds no matter if a matching reader is
 * connected or not (If no matching reader is connected brp_open() will fail).
 *
 * If 'snr' is 0 the serialnumber will be detected automaticially. If more
 * than one device is connected to the PC #BRP_ERR_OPEN_IO is returned.
 * When closing the device and reopen it again, the library will guarantee that
 * the same device is connected. If the device was disconnected between
 * brp_close() and brp_open() an #BRP_ERR_OPEN_IO error is returned.
 *
 * @return a protocol object, that can be used for brp_set_io().
 * NULL, if out of memory.
 */
BRP_LIB brp_protocol brp_create_usb_hid(long long snr);


/**
 * Creates an iterator for enumerating USB HID devices.
 *
 * Enumerates USB HID devices with default Baltech VID (0x13AD)
 * and PID ranges (40000-40999, 1000-1999, 0xF001-0xFFFF).
 * Only devices with valid numeric serial numbers and BRP interface
 * (usage_page=0xFF00, usage=1) are included.
 *
 * The iterator must be destroyed with brp_ioiter_destroy() when done.
 *
 * @return Iterator handle or NULL on failure (e.g., out of memory)
 *
 * @code
 * brp_ioiter iter = brp_ioiter_create_usb_hid();
 * if (iter == NULL) {
 *     // Handle error
 *     return;
 * }
 *
 * brp_protocol protocol;
 * while (brp_ioiter_next(iter, &protocol) == BRP_OK && protocol != NULL) {
 *     // Use protocol
 *     char* name = brp_get_friendly_name(protocol);
 *     printf("Found USB HID device: %s\n", name ? name : "Unknown");
 *
 *     // Clean up protocol when done
 *     brp_destroy(protocol);
 * }
 *
 * brp_ioiter_destroy(&iter);
 * @endcode
 */
BRP_LIB brp_ioiter brp_ioiter_create_usb_hid(void);


#endif

/** @} */ // end of defgroup brp_lib
