/**
 * @file
 * Implements the standard security layer.
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __CRYPTO_PROTOCOL_H__
#define __CRYPTO_PROTOCOL_H__


#include "protocol.h"


#define BRP_AES_KEY_SIZE    16
#define BRP_AES_BLOCK_SIZE  16

/**
 * A AES128 key, that is required for crypto operations.
 */
typedef unsigned char brp_sec_key[BRP_AES_KEY_SIZE];


/**
 * A AES IV
 */
typedef unsigned char brp_sec_iv[BRP_AES_BLOCK_SIZE];


/**
 * BRP_SECMODE_* specifies the level of security that shall be applied when
 * establishing a secure channel.
 *
 * Internally this bitmask is translated to the authmode bitmask.
 *
 * @name BRP_SECMODE_ Security Modes
 * @anchor BRP_SECMODE_ Security Modes
 * @{
 */

/**
 * This is the recommended setting as it provides ideal security.
 *
 * It provides:
 *  - **Authentication** of payload.
 *    Ensures that a man-in-the middle cannot tamper with the transmitted data.
 *  - **Encryption** of payload (in send and receive direction)
 *  - **Replay protection**. Ensures that a man-in-the middle cannot resend
 *    a previously transmitted command
 *  - **Session key generation**: Ensures that every session is working with
 *    a different key. Thus, even if a session key is compromised, you cannot
 *    reuse it at a later time.
 */
#define BRP_SECMODE_STD                        0

/**
 * Same as #BRP_SECMODE_STD, except that encryption is disabled.
 *
 * To guarantee Authentication and Replay Protection a 8 Byte signature is
 * appended to every command/response.
 *
 * This mode is useful if no sensible data is transferred but you want to be
 * able to monitor the transferred commands (i.e. for logging purposes).
 *
 * Can only be used *instead of* #BRP_SECMODE_STD.
 */
#define BRP_SECMODE_PLAIN                      1

/**
 * Allows secured communication without session handling.
 *
 * This flag disables session key generation and continuous IV managing.
 * Thus no initial mutual authentication sequence is needed and the
 * communication is more robust, as no syncronisation of the session between
 * reader and host is needed.
 *
 * @attention Security is considerably reduced with this mode.
 *
 * @attention Running a command in a stateless protocol after a
 * stateful-protocol in the same security level will result in an
 * #BRP_ERR_COMMAND_DENIED.
 *
 * This mode can be combined with #BRP_SECMODE_PLAIN to deactivate encryption.
 * Otherwise encryption is active (i.e. #BRP_SECMODE_STATELESS is the same as
 * #BRP_SECMODE_STD|BRP_SECMODE_STATELESS)
 */
#define BRP_SECMODE_STATELESS                  2

/**
 * @}
 */
 
                                        
#define BRP_MAX_SECURITY_LEVEL      3   ///< highest security level

/**
 * Creates a new secured channel that allows you to establish an authenticated
 * and encrypted connection over an insecure BRP channel.
 *
 * This protocol layer will manage all AES authentication and
 * encryption on top of another BRP protocol layer.
 *
 * @return A BRP protocol on success or NULL on failure. All commands executed
 * via the returned protocol are transferred encrypted.
 */
BRP_LIB brp_protocol brp_create_secure_channel
(
	int security_level,          ///< security level that shall be authenticated
	brp_sec_key key,             ///< the key that shall be used to establish a
	                             ///  secure channel
	int sec_mode                 ///< a bitmask of @ref BRP_SECMODE_ constants.
	                             ///  should be #BRP_SECMODE_STD by default.
);


/**
 * Does a mutual authentication and generates a session key.
 *
 * This command is only for low-level usage. Instead of using it, it is
 * recommended to use the high-level wrapper brp_create_secure_channel()
 *
 * This lowlevel operation is usually used only internally by
 * brp_create_crypto() and is not needed by end users.
 */
BRP_LIB brp_errcode brp_mutual_authenticate
(
	brp_protocol protocol,       ///< device against which the library
	                             ///  shall authenticate
	int security_level,          ///< security level that shall be authenticated
	brp_sec_key key,             ///< the key that shall be used to establish a
	                             ///  secure channel
	int * req_auth_modes,        ///< a bitmask of auth modes that are required
	brp_sec_key session_key      ///< session key that can be used by
                                 ///< brp_secured_exec_cmd(). Maybe NULL, if
                                 ///  sessionkey is not needed.
);


/**
 * Sends an encrypted command
 *
 * This command is only for low-level usage. Instead of using it, it is
 * recommended to use the high-level wrapper brp_create_secure_channel()
 */
BRP_LIB brp_errcode brp_secured_send_frm
(
	brp_protocol protocol, ///< device against which the library
	                       ///  shall authenticate
	int security_level,    ///< security level that shall be authenticated
	int sec_mode,          ///< see @ref BRP_SECMODE_ constants.
	                       ///< By default BRP_SECMODE_STD
	brp_sec_key key,       ///< the key that shall be used to establish
	                       ///  a secure channel.
	brp_sec_iv iv,         ///< next IV (has to be initialized to 00 ... 00 00).
	                       ///  Is only relevant if
	                       ///  #BRP_SECMODE_STATELESS is not set
	                       ///  (otherwise may be NULL).
	                       ///  ATTENTION: This value will change and the
	                       ///  changed value has to be passed to next
	                       ///  brp_secured_recv_frm()!!!
	int cmd_code,          ///< A 16bit code identifiying the exact command to
	                       ///  run (bits 0-7 are "command code", bits 8-15 are
	                       ///  "device code")
	brp_buf param_buf,     ///< A buffer where command parameter are
	                       ///  stored in serialized form. If NULL, it will be
	                       ///  ignored.
	size_t param_len,      ///< Length of 'param_buf' in bytes.
	brp_time cmd_timeout,  ///< Maximum time to wait until command is
	                       ///  executed. If the command is not run within this
	                       ///  time a #BRP_ERR_CMD_TIMEOUT is returned.
	int mode               ///< has to be one of the BRP_MODE_* constants.
	                       ///  by default BRP_MODE_STD could be used.
);


/**
 * Sends an encrypted command
 *
 * This command is only for low-level usage. Instead of using it, it is
 * recommended to use the high-level wrapper brp_create_secure_channel()
 */
BRP_LIB brp_errcode brp_secured_recv_frm
(
	brp_protocol protocol, ///< device against which the library
	                       ///  shall authenticate
	int sec_mode,          ///< see @ref BRP_SECMODE_ constants.
	                       ///< By default BRP_SECMODE_STD
	brp_sec_key key,       ///< the key that shall be used to establish
	                       ///  a secure channel. Please note that this key is
	                       /// copied and stays in memory until calling
	                       /// brp_destroy(protocol)
	brp_sec_iv iv,         ///< next IV (has to be initialized to 00 ... 00 00).
	                       ///  Is only relevant if
	                       ///  #BRP_SECMODE_STATELESS is not set
	                       ///  (otherwise may be NULL).
	                       ///  ATTENTION: This value will change and the
	                       ///  changed value has to be passed to next
	                       ///  brp_secured_send_frm()!!!
	int cmd_code,          ///< Same as cmd_code in brp_secured_send_frm().
	                       ///  Required for correct error codes.
	brp_frame resp_frm,    ///< Reference to a frame, where the response shall
	                       ///  be stored (=added).
	brp_time timeout       ///< maximum time to wait for response. If more time
	                       ///  is required BRP_ERR_TIMEOUT
);


#endif

/** @} */ // end of defgroup brp_lib
