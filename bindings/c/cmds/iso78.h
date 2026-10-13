/**
 * @file
 * This command group enables to access ISO 7816 compatible SAM modules attached to the Baltech ID-engine reader. It creates a transparent channel to the SAM which can be used in order to exchange APDUs following the ISO 7816-3 standard. 
 * 
 * This command group supports multiple SAM slots, which can be switched via the Iso78.SelectSlot command.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_ISO78_H__
#define __BRP_BALTECH_SDK_CMDS_ISO78_H__
#include "../typedefs.h"
/**
 * The specified slot index is not supported.
 */
#define BRP_Iso78_ErrInvalidSlot BRP_ERR_STATUS(0x4000, 0x02)
/**
 * SAM aborted command execution by sending an abort command.
 */
#define BRP_Iso78_ErrAbort BRP_ERR_STATUS(0x4000, 0x10)
/**
 * The specified protocol is not supported.
 */
#define BRP_Iso78_ErrProtNotSupported BRP_ERR_STATUS(0x4000, 0x20)
/**
 * Communication error.
 */
#define BRP_Iso78_ErrCom BRP_ERR_STATUS(0x4000, 0x21)
/**
 * Hardware error.
 */
#define BRP_Iso78_ErrHw BRP_ERR_STATUS(0x4000, 0x22)
/**
 * The command/parameter(s) is/are not supported by the SAM.
 */
#define BRP_Iso78_ErrInvalid7816Cmd BRP_ERR_STATUS(0x4000, 0x31)
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned SlotIndex;
} brp_Iso78_SelectSlot_t;
/**
 * This command can be used for readers with more than one SAM slot to switch between the slots. The slots are indexed starting at 0. At power up, slot 0 is selected. All following commands are routed to the SAM in the selected slot. 
 * 
 * It is possible to switch the slots after opening a SAM.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SlotIndex** (in) Index of Slot to select.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_SelectSlot(brp_protocol protocol, unsigned _input_SlotIndex);
#else
brp_errcode brp_Iso78_SelectSlot(brp_Iso78_SelectSlot_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* ATR;
	size_t* ATR_len;
	brp_mempool *mempool;
} brp_Iso78_OpenSamLegacy_t;
/**
 * This command sets up a communication channel to the SAM in the currently selected slot. If Iso78.OpenSAM was executed successfully, Iso78.ExchangeApdu can then be used to communicate with the SAM. 
 * 
 * To close the communication channel after data exchange, the Iso78.CloseSam command has to be called.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ATR** (out) ATR (Answer To Reset) string of SAM.
 *   - **ATR_len** (out) Length of **ATR** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_OpenSamLegacy(brp_protocol protocol, brp_buf* ATR, size_t* ATR_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso78_OpenSamLegacy(brp_Iso78_OpenSamLegacy_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Iso78_CloseSamLegacy_t;
/**
 * This command closes a communication channel previously opened via the Iso78.OpenSAM command. It is recommended to call this command before physically removing the SAM from its slot since it also powers down the SAM module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_CloseSamLegacy(brp_protocol protocol);
#else
brp_errcode brp_Iso78_CloseSamLegacy(brp_Iso78_CloseSamLegacy_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf SendData;
	size_t SendData_len;
	brp_buf* RecvData;
	size_t* RecvData_len;
	brp_mempool *mempool;
} brp_Iso78_ExchangeApduLegacy_t;
/**
 * This command sends an APDU command on the currently selected and opened SAM. Please note that the complete APDU command including the CLA, INS, P1, P2, Lc and Le values need part of the _SendData_ parameter.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SendData** (in) APDU command data including CLA, INS, P1, P2, Lc and Le.
 *   - **SendData_len** (in) Length of **SendData** (in bytes).
 *   - **RecvData** (out) APDU response data.
 *   - **RecvData_len** (out) Length of **RecvData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_ExchangeApduLegacy(brp_protocol protocol, brp_buf _input_SendData, size_t _input_SendData_len, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso78_ExchangeApduLegacy(brp_Iso78_ExchangeApduLegacy_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_Iso78_OpenSam_LID LID;
	unsigned* SamHandle;
	brp_buf* ATR;
	size_t* ATR_len;
	brp_mempool *mempool;
} brp_Iso78_OpenSam_t;
/**
 * This command sets up a communication channel to a Secure Access Module (SAM) inserted into the reader. To select the SAM, you specify it using the _LID_ parameter as described below. Once you've run this command successfully, you can run Iso78.ExchangeApdu to communicate with the SAM. 
 * 
 * To close the communication channel after data exchange, run Iso78.CloseSam.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **LID** (in) Logical SAM-ID (LID)
 *   - **SamHandle** (out) Identifier for SAM communication. Use this value in all subsequent calls of Iso78.CloseSam and Iso78.ExchangeApdu.
 *   - **ATR** (out) ATR (Answer To Reset) string of SAM
 *   - **ATR_len** (out) Length of **ATR** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_OpenSam(brp_protocol protocol, brp_Iso78_OpenSam_LID _input_LID, unsigned* SamHandle, brp_buf* ATR, size_t* ATR_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso78_OpenSam(brp_Iso78_OpenSam_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned SamHandle;
} brp_Iso78_CloseSam_t;
/**
 * This command closes a communication channel previously opened via the Iso78.OpenSam command. It is recommended to call this command before physically removing the SAM from its slot since it also powers down the SAM module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SamHandle** (in) Identifier for SAM communication (use _SAM_Handle_ value returned by the Iso78.OpenSam command).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_CloseSam(brp_protocol protocol, unsigned _input_SamHandle);
#else
brp_errcode brp_Iso78_CloseSam(brp_Iso78_CloseSam_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned SamHandle;
	brp_buf SendData;
	size_t SendData_len;
	brp_buf* RecvData;
	size_t* RecvData_len;
	brp_mempool *mempool;
} brp_Iso78_ExchangeApdu_t;
/**
 * This command sends an APDU command on the currently selected and opened SAM module using a logical ID. Please note that the complete APDU command including the CLA, INS, P1, P2, Lc and Le values need part of the _SendData_ parameter.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SamHandle** (in) Identifier for SAM communication (use _SAM_Handle_ value returned by the Iso78.OpenSam command).
 *   - **SendData** (in) APDU command data including CLA, INS, P1, P2, Lc and Le.
 *   - **SendData_len** (in) Length of **SendData** (in bytes).
 *   - **RecvData** (out) APDU response data.
 *   - **RecvData_len** (out) Length of **RecvData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_ExchangeApdu(brp_protocol protocol, unsigned _input_SamHandle, brp_buf _input_SendData, size_t _input_SendData_len, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso78_ExchangeApdu(brp_Iso78_ExchangeApdu_t params);
#endif
#endif
/**
 * @}
 */