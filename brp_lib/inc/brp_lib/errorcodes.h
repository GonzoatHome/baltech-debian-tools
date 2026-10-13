/**
 * @file
 * Contains all possible error codes that could be returned by BRP library.
 *
 * Please note that this does not include error codes, that are generated
 * in the device (see #BRP_ERRGRP_DEVICE)
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __ERRORCODES_H__
#define __ERRORCODES_H__


/**
 * This type is used library-wide for passing error codes in the return
 * value of functions.
 *
 * It has to be interpreted as a bitfield of three fields. For details see
 * @ref BRP_MASK_XXX.
 */
typedef unsigned int brp_errcode;


/**
 * @name BRP_MASK_XXX
 * @anchor BRP_MASK_XXX
 * Defines bitmasks for :brp_errcode.
 * If a errcode is and'ed with one of the bitmasks the corresponding part of
 * the error can be extracted.
 *
 * @{
 */

#define BRP_ERRMASK_GROUP              0xFFFF0000
#define BRP_ERRMASK_CODE               0x0000FFFF

/**
 * @}
 */


/**
 * @name BRP_ERRGRP_XXX
 * @anchor BRP_ERRGRP_XXX
 *
 *
 *
 * @{
 */


/**
 * A command failed to execute due to a error on the device side which is
 * not host communication related (card error, ...)
 *
 * The lower 16bits of the error code will contains the command group code and
 * the status code (see also #BRP_ERR_STATUS() on how to construct a specific
 * error code).
 * The exact list of error codes returned by the device can be found
 * in the @ref baltech_sdk.
 */
#define BRP_ERRGRP_DEVICE              0x00010000u


/**
 * A command cannot be executed as the device does not support the requested
 * feature
  */
#define BRP_ERRGRP_COMM_UNSUPPORTED    0x00800000u


/**
 * A command cannot be executed as the device does not allow access this
 * features in the current operations mode
 */
#define BRP_ERRGRP_COMM_ACCESSDENIED   0x01000000u


/**
 * A the device or host exceeded the allowed time for sending a frame
 */
#define BRP_ERRGRP_COMM_TIMEOUT        0x02000000u


/**
 * The device or host send a frame that does not correspond the expected frame
 */
#define BRP_ERRGRP_COMM_FRAMEFORMAT    0x04000000u


/**
 * any device <-> host communication problem which is not categoriezed by
 * one of the BRP_ERRGRP_COMM_* macros
 */
#define BRP_ERRGRP_COMM_UNDEFINED      0x08000000u


/**
 * Any kind of device <-> host communication problem
 */
#define BRP_ERRGRP_COMMUNICATION       0x0F800000u


/**
 * The libraries API was used in an invalid manner
 */
#define BRP_ERRGRP_LIB_INVALIDCALL     0x10000000u


/**
 * A fatal error occured, which the library cannot recover from.
 * The application should be closed
 */
#define BRP_ERRGRP_LIB_NONRECOVERABLE  0x20000000u


/**
 * A error in the operating system layer (i.e. hardware drivers) occured
 */
#define BRP_ERRGRP_LIB_OS              0x40000000u


/**
 * any library specific error which is not one of the BRP_ERRGRP_LIB_* macros.
 */
#define BRP_ERRGRP_LIB_UNDEFINED       0x80000000u


/**
 * Any error which occured in the library
 */
#define BRP_ERRGRP_LIBRARY             0xF0000000u

/**
 * @}
 */



/**
 * @name BRP_ERR_XXX
 * @anchor BRP_ERR_XXX
 *
 * A list of standard error codes that required all over this library.
 *
 * @{
 */

/**
 * If a function of return type :brp_errcode runs properly, it returns
 * this value.
 */
#define BRP_OK                      0x00000000u


/**
 * This error must not be returned if the library operatares correctly.
 * It is only returned, if a bug in the implementation was detetcted.
 */
#define BRP_ERR_INTERNAL            (0x0001u | BRP_ERRGRP_LIB_NONRECOVERABLE)


/**
 * A BRP command that was send by brp_send_frame() exceeded the specified
 * timeout (see also brp_send_cmd() / brp_exec_cmd()).
 *
 * **Attentention:** must not be intermixed with #BRP_ERR_TIMEOUT.
 */
#define BRP_ERR_CMD_TIMEOUT         (0x0002u | BRP_ERRGRP_COMM_TIMEOUT)


/**
 * The frame returned from the reader does not match the format expected
 * by the BRP protocol.
 */
#define BRP_ERR_FRAMEFORMAT         (0x0003u | BRP_ERRGRP_COMM_FRAMEFORMAT)


/**
 * Returned if the a parameter contains an invalid value.
 * I.e. if a required pointer is set to NULL.
 */
#define BRP_ERR_INVALID_API_CALL    (0x0004u | BRP_ERRGRP_LIB_INVALIDCALL)


/**
 * The heap has not enough memory to allocate a buffer that is required
 * for the wanted operation.
 */
#define BRP_ERR_OUT_OF_MEMORY       (0x0005u | BRP_ERRGRP_LIB_NONRECOVERABLE)


/**
 * The requested feature is not implemented yet
 */
#define BRP_ERR_NOT_IMPLEMENTED     (0x0006u | BRP_ERRGRP_LIB_INVALIDCALL)


/**
 * The Library is not ready to send/receive data. Probably it is still
 * processing another request.
 */
#define BRP_ERR_BUSY                (0x0007u | BRP_ERRGRP_LIB_INVALIDCALL)


/**
 * The protocol/device is not opened
 */
#define BRP_ERR_CLOSED              (0x0008u | BRP_ERRGRP_LIB_INVALIDCALL)


/**
 * A Command's response is bigger than the buffer provided for the response.
 */
#define BRP_ERR_BUFFER_OVERFLOW     (0x0009u | BRP_ERRGRP_COMM_FRAMEFORMAT)


/**
 * Failed to open the I/O connection
 */
#define BRP_ERR_OPEN_IO             (0x000Au | BRP_ERRGRP_LIB_OS)


/**
 * Failed to send data via IO connection
 */
#define BRP_ERR_WRITE_IO            (0x000Bu | BRP_ERRGRP_LIB_OS)


/**
 * Failed to wait for data via IO connection
 */
#define BRP_ERR_WAIT_IO             (0x000Cu | BRP_ERRGRP_LIB_OS)


/**
 * Failed to wait for data via IO connection
 */
#define BRP_ERR_READ_IO             (0x000Du | BRP_ERRGRP_LIB_OS)


/**
 * Failed to open the I/O connection
 */
#define BRP_ERR_CLOSE_IO            (0x000Eu | BRP_ERRGRP_LIB_OS)


/**
 * The payload of a frame has invalid format
 */
#define BRP_ERR_PAYLOAD_FORMAT      (0x000Fu | BRP_ERRGRP_COMM_FRAMEFORMAT)


/**
 * The payload of an encrypted command had invalid format/response.
 */
#define BRP_ERR_CRYPTO_FORMAT          (0x0010u | BRP_ERRGRP_COMM_FRAMEFORMAT)


/**
 * The given securitylevel is not supported
 */
#define BRP_ERR_SEC_LEVEL_NOT_SUPPORTED   \
	(0x0016u | BRP_ERRGRP_COMM_ACCESSDENIED)


/**
 * The specified BRP command is not supported by the connected device
 *
 * Internally the driver maps the status code BRP_ERR_STATUS(xxxx, 0x41) to this
 * (cmdcode independant) error code.
 */
#define BRP_ERR_UNSUPPORTED_COMMAND (0x0020u | BRP_ERRGRP_COMM_UNSUPPORTED)


/**
 * The BRP command is not allowed to be executed from the current security level
 *
 * Internally the driver maps the status code BRP_ERR_STATUS(xxxx, 0x42) to this
 * (cmdcode independant) error code.
 */
#define BRP_ERR_COMMAND_DENIED      (0x0021u |BRP_ERRGRP_COMM_ACCESSDENIED)


/**
 * The received frame is a valid BRP frame but not expected in this protocol
 * state.
 */
#define BRP_ERR_UNEXPECTED_FRAME    (0x0022u | BRP_ERRGRP_COMM_FRAMEFORMAT)


/**
 * The response to a brp_recv_frame() / brp_recv_any_frame() is not returned
 * within the specified timeout.
 *
 * **Attention:** Must not be intermixed with #BRP_ERR_CMD_TIMEOUT, which is
 * returned if the timeout of a BRP command is exceeded (see brp_send_cmd()).
 */
#define BRP_ERR_TIMEOUT             (0x0023u | BRP_ERRGRP_COMM_TIMEOUT)


/**
 * Returned if the a frame passed to a function to be transferred to the device
 * has invalid format
 */
#define BRP_ERR_CALLED_INVALID_FRAME (0x0024u | BRP_ERRGRP_LIB_INVALIDCALL)


/**
 * The layer is tried to be added to a composite protocol
 * (see brp_add_layer() / brp_set_layer()) although already added earliert.
 * Or it is tried to be removed (brp_detach_layer()) also not part of the
 * composite protocol.
 */
#define BRP_ERR_EXISTING_LAYER      (0x0025u | BRP_ERRGRP_LIB_INVALIDCALL)


/**
 * The OS failed to generate a random number
 */
#define BRP_ERR_GEN_RANDOM_DATA       (0x0026u | BRP_ERRGRP_LIB_OS)


/**
 * The readers KEY does not match the key of the host.
 */
#define BRP_ERR_INVALID_KEY          (0x0027u | BRP_ERRGRP_COMM_ACCESSDENIED)


/**
 * No device was found when trying to open a connection.
 * For USB/HID this means no matching device was enumerated.
 */
#define BRP_ERR_NO_DEVICE_FOUND       (0x0028u | BRP_ERRGRP_LIB_OS)


/**
 * Multiple devices were found but the connection string does not uniquely
 * identify a single device. For USB/HID this happens when snr=0 is used
 * but multiple readers are connected.
 */
#define BRP_ERR_AMBIGUOUS_DEVICE      (0x0029u | BRP_ERRGRP_LIB_OS)


/**
 * Error codes that happen on the reader side are encoded by this macro.
 *
 * In practice this macro is only for internal use, as all error codes
 * are available as separate macro definitions in @ref baltech_sdk.
 *
 * 'cmd_code' is a 16bit value identifing the reader command that caused the
 * error. statuscode is a 8bit value that is returned by this command.
 * The [BRP Reference Manual](https://docs.baltech.de/refman/cmds/index.html)
 * lists all command codes and their possible status codes.
 */
#define BRP_ERR_STATUS(cmd_code, statuscode) \
	((brp_errcode)(((cmd_code) & 0xFF00u) \
	               | ((statuscode) & 0xFFu) \
	               | BRP_ERRGRP_DEVICE))



/**
 * @}
 */


#endif

/** @} */ // end of defgroup brp_lib
