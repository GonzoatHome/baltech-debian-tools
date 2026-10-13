/**
 * @file
 * These are the Quadrakey 125kHz card commands.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_QKEY_H__
#define __BRP_BALTECH_SDK_CMDS_QKEY_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * No tag error.
 */
#define BRP_QKey_ErrQkeyNoTag BRP_ERR_STATUS(0x3500, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Wrong length or wrong data.
 */
#define BRP_QKey_ErrQkeyRxdata BRP_ERR_STATUS(0x3500, 0x03)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Parity error.
 */
#define BRP_QKey_ErrQkeyParity BRP_ERR_STATUS(0x3500, 0x05)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Wrong command param (on HF).
 */
#define BRP_QKey_ErrQkeyParam BRP_ERR_STATUS(0x3500, 0x07)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Another task requested control over HF via hf_request_control.
 */
#define BRP_QKey_ErrQkeyHfreqctrl BRP_ERR_STATUS(0x3500, 0x08)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Missing Platform ID or Readerchip error.
 */
#define BRP_QKey_ErrQkeyHw BRP_ERR_STATUS(0x3500, 0x09)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Hardware not supported.
 */
#define BRP_QKey_ErrQkeyHwNotSupported BRP_ERR_STATUS(0x3500, 0x0B)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_QKey_Read_t;
/**
 * Returns data of quadrakey tags (read only tag).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (out) Quadrakey data.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_QKey_Read(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_QKey_Read(brp_QKey_Read_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */