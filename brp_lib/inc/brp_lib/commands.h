/**
 * @file
 * This is replaced by the *Baltech API*!
 *
 * @deprecated
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#if ! defined(__COMMANDS_H__)
#define __COMMANDS_H__


#include "brp_protocol.h"


#define BRP_ERR_AR_NOMESSAGE       BRP_ERR_STATUS(0x0500, 0x01)
#define BRP_ERR_AR_DISABLED        BRP_ERR_STATUS(0x0500, 0x10)


/**
 * maximum length of firmwarestring (see brp_exec_Sys_GetInfo())
 */
#define BRP_CMD_SYS_GETINFO_FWS_LEN      41


/**
 * Retrieves the firmware string.
 *
 * @deprecated
 *
 * @attention This function has to be move to "Baltech API" and renamed to
 * brp_Sys_GetInfo()!
 */
BRP_LIB brp_errcode brp_exec_Sys_GetInfo
(
	brp_protocol protocol,   ///< the BRP protocol to the device
	char * fws               ///< A pointer to a buffer of size
	                         ///  #BRP_CMD_SYS_GETINFO_FWS_LEN. Will be filled
	                         ///  with the zero terminated ASCII string
	                         ///  that identifies the firmware.
);


/**
 * Returns the last message read by device
 *
 * @deprecated
 *
 * @attention This function has to be move to "Baltech API" and renamed to
 * brp_AR_GetMessage()!
 */
BRP_LIB brp_errcode brp_exec_AR_GetMessage
(
	brp_protocol protocol,   ///< the BRP protocol to the device
	int * msg_type,          ///< type of message
	                         /// (keyboard entry, card presentation, ...)
	char * msg,              ///< ASCII message text (with trailing zero).
	size_t max_msg_len,      ///< maximum size of message
	size_t * msg_len         ///< actual size of message
);


/**
 * Modifies the devices (permanent) configuration.
 * This command can set a single configuration value.
 * (see also brp_exec_Sys_CfgGetValue())
 *
 * @deprecated
 *
 * @attention This function has to be move to "Baltech API" and renamed to
 * brp_Sys_CfgSetValue()!
 */
BRP_LIB brp_errcode brp_exec_Sys_CfgSetValue
(
	brp_protocol protocol,   ///< the BRP protocol to the device
	int key,                 ///< the key of configuration value
	int value,               ///< the value of configuration value
	brp_buf data,            ///< content of configuraton value to write
	size_t data_len          ///< length of 'data' in bytes
);


/**
 * Retrieves a configuration value from the device.
 * (see also brp_exec_Sys_CfgSetValue())
 *
 * @deprecated
 *
 * @attention This function has to be move to "Baltech API" and renamed to
 * brp_Sys_CfgGetValue()!
*/
BRP_LIB brp_errcode brp_exec_Sys_CfgGetValue
(
	brp_protocol protocol,   ///< the BRP protocol to the device
	int key,                 ///< the key of the configuration value
	int value,               ///< the value of the configuration value
	brp_buf data,            ///< the buffer, where the content of the
	                         ///  configuration value shall be stored into.
	                         ///  If NULL, the value has to be empty
	size_t max_data_len,     ///< the size of 'data'. If the configuration value
	                         ///  is bigger than max_data_len an
	                         ///  #BRP_ERR_INVALID_API_CALL is returned.
	size_t * data_len        ///< the actual length of the configuraiton value.
	                         ///  If NULL, the actual length has to be identical
	                         ///  to max_data_len
);


#endif

/** @} */ // end of defgroup brp_lib
