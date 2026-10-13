/**
 * @file
 * This command group allows to emulate an ISO 14443-3 card.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_CARDEMU_H__
#define __BRP_BALTECH_SDK_CMDS_CARDEMU_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * No tag error.
 */
#define BRP_CardEmu_CardemuErrNoTag BRP_ERR_STATUS(0x4700, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Collision occurred (status value will be stored with bit position of collision in high nibble).
 */
#define BRP_CardEmu_CardemuErrCollision BRP_ERR_STATUS(0x4700, 0x02)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * General HF error.
 */
#define BRP_CardEmu_CardemuErrHf BRP_ERR_STATUS(0x4700, 0x04)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Bit error, parity error or frame error (start /stop bit).
 */
#define BRP_CardEmu_CardemuErrFrame BRP_ERR_STATUS(0x4700, 0x07)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * CRC checksum error.
 */
#define BRP_CardEmu_CardemuErrCrc BRP_ERR_STATUS(0x4700, 0x08)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Communication error uC - reader chip.
 */
#define BRP_CardEmu_CardemuErrCom BRP_ERR_STATUS(0x4700, 0x10)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Remaining data in FIFO / FIFO overflow.
 */
#define BRP_CardEmu_CardemuErrBuflen BRP_ERR_STATUS(0x4700, 0x11)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Timeout occurred while waiting for card / APDU command.
 */
#define BRP_CardEmu_CardemuErrTimeout BRP_ERR_STATUS(0x4700, 0x3F)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned* MaxFrameSize;
} brp_CardEmu_GetMaxFrameSize_t;
/**
 * This command returns the maximum size of a single ISO14443-3 frame that may be sent/received via CardEmu.StartEmu or CardEmu.TransparentCmd.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **MaxFrameSize** (out) Maximum size of a single frame.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_CardEmu_GetMaxFrameSize(brp_protocol protocol, unsigned* MaxFrameSize);
#else
brp_errcode brp_CardEmu_GetMaxFrameSize(brp_CardEmu_GetMaxFrameSize_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf Snr;
	unsigned ATQA;
	unsigned SAK;
	unsigned Timeout;
	brp_buf* FirstCmd;
	size_t* FirstCmd_len;
	brp_mempool *mempool;
} brp_CardEmu_StartEmu_t;
/**
 * Switch to Passive mode and wait for a ISO1443-3a Request/Anticoll/Select sequence and receive the first frame.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Snr** (in) Serial number of card to emulate (first Byte has to be 0x08).
 *   - **ATQA** (in) Attention: When transferred via HF, the ATQA is sent LSB (instead of the MSB order used here).
 *   - **SAK** (in) Select Acknowledge (SAK), according to the ISO 14443-3 (Type A) standard.
 *   - **Timeout** (in) Maximum time to wait for a Request.
 *   - **FirstCmd** (out) First ISO14443-3 command sent from the remote reader.
 *   - **FirstCmd_len** (out) Length of **FirstCmd** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_CardEmu_StartEmu(brp_protocol protocol, brp_buf _input_Snr, unsigned _input_ATQA, unsigned _input_SAK, unsigned _input_Timeout, brp_buf* FirstCmd, size_t* FirstCmd_len, brp_mempool *mempool);
#else
brp_errcode brp_CardEmu_StartEmu(brp_CardEmu_StartEmu_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf Rsp;
	size_t Rsp_len;
	unsigned Timeout;
	brp_buf* Cmd;
	size_t* Cmd_len;
	brp_mempool *mempool;
} brp_CardEmu_TransparentCmd_t;
/**
 * Sends a response to the command returned by CardEmu.StartEmu or to the command returned by the last CardEmu.TransparentCmd.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Rsp** (in) Response that should be sent to the remote reader as reply to the last command.
 *   - **Rsp_len** (in) Length of **Rsp** (in bytes).
 *   - **Timeout** (in) Maximum time to wait for a Request.
 *   - **Cmd** (out) Next ISO14443-3 command received from the remote reader.
 *   - **Cmd_len** (out) Length of **Cmd** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_CardEmu_TransparentCmd(brp_protocol protocol, brp_buf _input_Rsp, size_t _input_Rsp_len, unsigned _input_Timeout, brp_buf* Cmd, size_t* Cmd_len, brp_mempool *mempool);
#else
brp_errcode brp_CardEmu_TransparentCmd(brp_CardEmu_TransparentCmd_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned* ExtFieldStat;
} brp_CardEmu_GetExternalHfStatus_t;
/**
 * Returns _true_ if an external HF field is detected.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ExtFieldStat** (out) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_CardEmu_GetExternalHfStatus(brp_protocol protocol, unsigned* ExtFieldStat);
#else
brp_errcode brp_CardEmu_GetExternalHfStatus(brp_CardEmu_GetExternalHfStatus_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool NfcAPassiv;
	brp_buf Snr;
	unsigned ATQA;
	unsigned SAK;
	unsigned Timeout;
	brp_buf* FirstCmd;
	size_t* FirstCmd_len;
	brp_mempool *mempool;
} brp_CardEmu_StartNfc_t;
/**
 * Switch to Passive mode and wait for an NFC powerup sequence
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **NfcAPassiv** (in) enables NFC-A passive mode - command terninates after receiving the RATS command.
 *   - **Snr** (in) 4 byte serial number of card to emulate.
 *   - **ATQA** (in) Attention: When transferred via HF, the ATQA is sent LSB (instead of the MSB order used here).
 *   - **SAK** (in) Select Acknowledge (SAK), according to the ISO 14443-3 (Type A) standard.
 *   - **Timeout** (in) Maximum time to wait for a Request.
 *   - **FirstCmd** (out) First ISO14443 command sent from the remote reader.
 *   - **FirstCmd_len** (out) Length of **FirstCmd** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_CardEmu_StartNfc(brp_protocol protocol, bool _input_NfcAPassiv, brp_buf _input_Snr, unsigned _input_ATQA, unsigned _input_SAK, unsigned _input_Timeout, brp_buf* FirstCmd, size_t* FirstCmd_len, brp_mempool *mempool);
#else
brp_errcode brp_CardEmu_StartNfc(brp_CardEmu_StartNfc_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */