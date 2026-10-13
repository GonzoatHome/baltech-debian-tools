/**
 * @file
 * Every protocol has to be identified unique by a protocol ID.
 * This file lists all protocol IDs.
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#if ! defined(__PROTOCOL_IDS_H__)
#define __PROTOCOL_IDS_H__


/**
 * identificator for BRP protocols (see brp_protocol.h)
 */
#define BRP_PROTID_BRP                 1


/**
 * identificator for composed protocols (see composite_protocol.h)
 */
#define BRP_PROTID_COMPOSITE           4


/**
 * internal identificator for unused protocol layers in composed protocols
 * (see composite_protocol.h). Not for used by application
 */
#define BRP_PROTID_DUMMY               5


/**
 * identificator for USB HID protocols (see usb_hid_protocol.h)
 */
#define BRP_PROTID_USB_HID             6


/**
 * identificator for RS232/Virtual Comport protocols (see usb_hid_protocol.h)
 */
#define BRP_PROTID_RS232               7


/**
 * identificator for RS232 protocol (see rs232_protocol.h)
 */
#define BRP_PROTID_SECURE_CHANNEL      8


/**
 * identificator for transparent BRP monitor protocol. It relies on a BRP
 * protocol and provides a BRP protocol. All data send to this protocol
 * is forwarded to the underlying protocol and written to a log file
 */
#define BRP_PROTID_MONITOR             9


/**
 * identificator for custom protocols (=not implemented by this library)
 */
#define BRP_PROTID_CUSTOM(ndx)         (0x80+(ndx))




#define BRP_LAYERID_ANONYMOUS      0   ///< unnamed protocol layer
#define BRP_LAYERID_IO             1   ///< lowest protocol layer that forwards
                                       ///  data to OS drivers
#define BRP_LAYERID_BRP            3   ///< brp layer
#define BRP_LAYERID_MONITOR        5   ///< monitoring layer
#define BRP_LAYERID_CRYPTO         4   ///< encryption layer
#define BRP_LAYERID_PLAIN_MONITOR  6   ///< monitoring layer for dencrypted cmds




#endif

/** @} */ // end of defgroup brp_lib
