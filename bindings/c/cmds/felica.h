/**
 * @file
 * These are FeliCa card low-level commands.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_FELICA_H__
#define __BRP_BALTECH_SDK_CMDS_FELICA_H__
#include "../typedefs.h"
/**
 * No PICC in HF field.
 */
#define BRP_Felica_ErrFelicaNoTag BRP_ERR_STATUS(0x1C00, 0x01)
/**
 * PICC-reader communication error.
 */
#define BRP_Felica_ErrFelicaHf BRP_ERR_STATUS(0x1C00, 0x04)
/**
 * Bit error, parity error or frame error.
 */
#define BRP_Felica_ErrFelicaFrame BRP_ERR_STATUS(0x1C00, 0x07)
/**
 * Communication error uC - reader chip.
 */
#define BRP_Felica_ErrFelicaCom BRP_ERR_STATUS(0x1C00, 0x10)
/**
 * Reader chip does not support cardtype-selected baud rate.
 */
#define BRP_Felica_ErrFelicaCardNotSupported BRP_ERR_STATUS(0x1C00, 0x22)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Command not supported by hardware.
 */
#define BRP_Felica_ErrFelicaHwNotSupported BRP_ERR_STATUS(0x1C00, 0x23)
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_Felica_GenericCmd_FastBaud FastBaud;
	unsigned Cmd;
	brp_buf Param;
	size_t Param_len;
	unsigned Timeout;
	brp_buf* Resp;
	size_t* Resp_len;
	brp_mempool *mempool;
} brp_Felica_GenericCmd_t;
/**
 * Generic command for FeliCa.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **FastBaud** (in) Baudrate PCD-PICC.
 *   - **Cmd** (in) Command to card.
 *   - **Param** (in) Parameter of command.
 *   - **Param_len** (in) Length of **Param** (in bytes).
 *   - **Timeout** (in) Timeout send PCD and receive PICC.
 *   - **Resp** (out) Response of command.
 *   - **Resp_len** (out) Length of **Resp** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Felica_GenericCmd(brp_protocol protocol, brp_Felica_GenericCmd_FastBaud _input_FastBaud, unsigned _input_Cmd, brp_buf _input_Param, size_t _input_Param_len, unsigned _input_Timeout, brp_buf* Resp, size_t* Resp_len, brp_mempool *mempool);
#else
brp_errcode brp_Felica_GenericCmd(brp_Felica_GenericCmd_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf UID2;
} brp_Felica_SetUID2_t;
/**
 * Sets UID2 used by generic command.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **UID2** (in) Parameter of command.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Felica_SetUID2(brp_protocol protocol, brp_buf _input_UID2);
#else
brp_errcode brp_Felica_SetUID2(brp_Felica_SetUID2_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Felica_Request_FastBaud FastBaud;
	unsigned SystemCode;
	unsigned RequestCode;
	unsigned* ColFlag;
	brp_Felica_Request_Labels_Entry** Labels;
	size_t* Labels_len;
	brp_mempool *mempool;
} brp_Felica_Request_t;
/**
 * Polls for tags with number of time slots, returns NFCID2 list of detected tags (maximum 16 / length 8).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **FastBaud** (in) Baudrate PCD-PICC.
 *   - **SystemCode** (in) Application ID for PICC preselection, All:0xFFFF.
 *   - **RequestCode** (in) RequestCode.
 *   - **ColFlag** (out) True if collision occurs.
 *   - **Labels** (out) 
 *   - **Labels_len** (out) Number of elements in **Labels**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Felica_Request(brp_protocol protocol, brp_Felica_Request_FastBaud _input_FastBaud, unsigned _input_SystemCode, unsigned _input_RequestCode, unsigned* ColFlag, brp_Felica_Request_Labels_Entry** Labels, size_t* Labels_len, brp_mempool *mempool);
#else
brp_errcode brp_Felica_Request(brp_Felica_Request_t params);
#endif
#endif
/**
 * @}
 */