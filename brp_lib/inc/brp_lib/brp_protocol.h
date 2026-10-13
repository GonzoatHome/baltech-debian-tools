/**
 * @file
 * Implements the core BRP protocol.
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __BRP_PROTOCOL_H__
#define __BRP_PROTOCOL_H__


#include "protocol.h"


/**
 * @name BRP_MODE_XXX
 * @anchor BRP_MODE_XXX
 * Specifies the run mode / frame format of BRP protocol.
 * @{
 */


/**
 * Standard mode. This means the reader responds immediately to the command.
 */
#define BRP_MODE_STD            0x00
#define BRP_MODE_NONE           BRP_MODE_STD     ///< legacy define


/**
 * Continous mode.
 *
 * This means that the command works until being finished (either successfully
 * or with error). The exact meaning depends on the command (For details see
 * device commands documentation).
 *
 * NOT IMPLEMENTED YET.
 */
#define BRP_MODE_CONTINUOUS    0x01


/**
 * Repeat mode.
 *
 * Repeats execution of command until being finished by host.
 *
 * NOT IMPLEMENTED YET.
 */
#define BRP_MODE_REPEAT        0x02


/**
 * Stop continuous / repeat mode
 */
#define BRP_MODE_BREAK         0x03

/**
 * @}
 */


/**
 * Creates a new BRP protocol.
 *
 * @return A protocol on success or NULL on failure.
 */
BRP_LIB brp_protocol brp_create_brp(void);


/**
 * Runs a command on the BRP device connected via the assigned protocol.
 *
 * This is recommended for syncronous command execution.
 * Internally it is a shortcut for running:
 *
 * - brp_send_cmd()
 * - brp_recv_cmd()
 *
 * for asyncronous command execution run these commands directly.
 *
 * @return A error code indicating the success of the execution of the command.
 */
BRP_LIB brp_errcode brp_exec_cmd
(
	brp_protocol protocol, ///< a protocol handle, where the
	                       ///  connected reader shall run the passed command.
	int cmd_code,          ///< A 16bit code identifiying the exact command to
	                       ///  run (bits 0-7 are "command code", bits 8-15 are
	                       ///  "device code")
	brp_buf param_buf,     ///< A buffer where command parameter are
	                       ///  stored in serialized form. If NULL, it will be
	                       ///  ignored.
	size_t param_len,      ///< Length of 'param_buf' in bytes.
	brp_buf resp_buf,      ///< Reference to a buffer, where the response is
	                       ///  stored.
	size_t max_resp_len,   ///< maximum size of 'resp_buf'.
	                       ///  If more data is returned than this value,
	                       ///  the first max_resp_len bytes will be written
	                       ///  and #BRP_ERR_BUFFER_OVERFLOW will be returned.
    size_t * resp_len,     ///< actual size of response. If NULL, this command
                           ///  has to return exactly max_resp_len bytes
                           ///  (otherwise #BRP_ERR_FRAMEFORMAT is returned)
	brp_time cmd_timeout   ///< Maximum time to wait until command is
	                       ///  executed. If the command is not run within this
	                       ///  time a #BRP_ERR_CMD_TIMEOUT is returned.
);


/**
 * Sends a command frame via a BRP protocol.
 *
 * @return A error code indicating the success of the execution of the command.
 */
BRP_LIB brp_errcode brp_send_cmd
(
	brp_protocol protocol, ///< a protocol handle, where the
	                       ///  connected reader shall run the passed command.
	int cmd_code,          ///< A 16bit code identifiying the exact command to
	                       ///  run (bits 0-7 are "command code", bits 8-15 are
	                       ///  "device code")
	brp_buf param_buf,     ///< A buffer where command parameter are
	                       ///  stored in serialized form. If NULL, it will be
	                       ///  ignored.
	size_t param_len,      ///< Length of 'param_buf' in bytes.
	brp_time cmd_timeout,  ///< maximum time this command may require in ms.
	                       ///  If its exceeds this time, #BRP_ERR_CMD_TIMEOUT
	                       ///  is returned.
	int mode               ///< specifys run mode ( @ref BRP_MODE_XXX )
);


/**
 * Returns the response of a command runned on the BRP device connected via
 * *base_protocol*.
 *
 * @return A error code indicating the success of the execution of the command.
 */
BRP_LIB brp_errcode brp_recv_cmd
(
	brp_protocol protocol, ///< a protocol handle, where the response shall be
	                       ///  retrieved from
	brp_buf resp_buf,      ///< Reference to a buffer, where the response is
	                       ///  stored.
	size_t max_resp_len,   ///< size of 'resp_len'. If 0, the response is thrown
	                       ///  away
    size_t * resp_len,     ///< actual size of response.
	brp_time timeout       ///< maximum time to wait for response. If more time
	                       ///  is required #BRP_ERR_TIMEOUT
);



/**
 * Stops a command that was run with brp_send_cmd() with the mode parameter set
 * to in #BRP_MODE_CONTINUOUS or #BRP_MODE_REPEAT.
 */
BRP_LIB brp_errcode brp_break_cmd
(
	brp_protocol protocol  ///< a protocol handle of the device where shall be
	                       ///  a running command shall be stopped.
);


#endif //__BRP_H__

/** @} */ // end of defgroup brp_lib
