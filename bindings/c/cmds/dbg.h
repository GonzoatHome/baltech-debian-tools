/**
 * @file
 * This is a command group for getting debug logs.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_DBG_H__
#define __BRP_BALTECH_SDK_CMDS_DBG_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * Still processing last command.
 */
#define BRP_Dbg_DbgErrBusy BRP_ERR_STATUS(0xF300, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	char** LogData;
	brp_mempool *mempool;
} brp_Dbg_ReadLogs_t;
/**
 * Get next available block of debug data.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **LogData** (out) 
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Dbg_ReadLogs(brp_protocol protocol, char** LogData, brp_mempool *mempool);
#else
brp_errcode brp_Dbg_ReadLogs(brp_Dbg_ReadLogs_t params);
#endif
typedef struct {
	brp_protocol protocol;
	char* Cmd;
} brp_Dbg_RunCmd_t;
/**
 * Run a command by emulating the corresponding keypress in DebugCommandInterface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Cmd** (in) Command to emulate.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Dbg_RunCmd(brp_protocol protocol, char* _input_Cmd);
#else
brp_errcode brp_Dbg_RunCmd(brp_Dbg_RunCmd_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */