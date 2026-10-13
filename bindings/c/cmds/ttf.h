/**
 * @file
 * Command to read 125kHz TTF (tag talks first) cards.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_TTF_H__
#define __BRP_BALTECH_SDK_CMDS_TTF_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * No tag error.
 */
#define BRP_TTF_ErrTtfNoTag BRP_ERR_STATUS(0x3400, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Wrong length or wrong data.
 */
#define BRP_TTF_ErrTtfRxdata BRP_ERR_STATUS(0x3400, 0x03)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Wrong cmd param.
 */
#define BRP_TTF_ErrTtfParam BRP_ERR_STATUS(0x3400, 0x07)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * ISR buffer overflow during receive.
 */
#define BRP_TTF_ErrTtfOvTo BRP_ERR_STATUS(0x3400, 0x08)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Another task requested control over HF via hf_request_control.
 */
#define BRP_TTF_ErrTtfHfreqctrl BRP_ERR_STATUS(0x3400, 0x09)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Platform ID missing or hardware error.
 */
#define BRP_TTF_ErrTtfHw BRP_ERR_STATUS(0x3400, 0x0A)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Hardware not supported.
 */
#define BRP_TTF_ErrTtfHwNotSupported BRP_ERR_STATUS(0x3400, 0x0C)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	bool ResetDataPtr;
	unsigned SamplingTime;
	unsigned Rxlen;
	brp_TTF_ReadByteStream_RxMod RxMod;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_TTF_ReadByteStream_t;
/**
 * Returns raw data of the 125 kHz HF interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ResetDataPtr** (in) Resets data pointer and starts sampling.
 *   - **SamplingTime** (in) For ID-engine X: If different from 0, this parameter starts new sampling.   For ID-engine Z: Dummy value
 *   - **Rxlen** (in) Number of Bytes to receive.
 *   - **RxMod** (in) Decoder settings - for ID-engine Z use SMPL.
 *   - **Data** (out) 
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_TTF_ReadByteStream(brp_protocol protocol, bool _input_ResetDataPtr, unsigned _input_SamplingTime, unsigned _input_Rxlen, brp_TTF_ReadByteStream_RxMod _input_RxMod, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_TTF_ReadByteStream(brp_TTF_ReadByteStream_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */