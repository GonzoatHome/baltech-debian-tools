/**
 * @file
 * This are ASK 125kHz card commands.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_ASK_H__
#define __BRP_BALTECH_SDK_CMDS_ASK_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * No Tag.
 */
#define BRP_ASK_ErrAskNoTag BRP_ERR_STATUS(0x3600, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Wrong length or wrong data.
 */
#define BRP_ASK_ErrAskRxdata BRP_ERR_STATUS(0x3600, 0x03)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Parity error.
 */
#define BRP_ASK_ErrAskParity BRP_ERR_STATUS(0x3600, 0x05)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Wrong command param (on HF).
 */
#define BRP_ASK_ErrAskParam BRP_ERR_STATUS(0x3600, 0x07)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Another task requested control over HF via hf_request_control.
 */
#define BRP_ASK_ErrAskHfreqctrl BRP_ERR_STATUS(0x3600, 0x08)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Missing Platform ID or Readerchip error.
 */
#define BRP_ASK_ErrAskHw BRP_ERR_STATUS(0x3600, 0x09)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Hardware not supported.
 */
#define BRP_ASK_ErrAskHwNotSupported BRP_ERR_STATUS(0x3600, 0x0B)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_ASK_SecuraKeyRead_t;
/**
 * Returns data of SecuraKey tags (read only tag).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (out) SecuraKey data.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_ASK_SecuraKeyRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_ASK_SecuraKeyRead(brp_ASK_SecuraKeyRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_ASK_GproxRead_t;
/**
 * Returns data of G-Prox tags (read only tag).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (out) G-Prox data.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_ASK_GproxRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_ASK_GproxRead(brp_ASK_GproxRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_ASK_CotagRead_t;
/**
 * Returns data of Cotag tags (read only tag).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (out) Cotag data.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_ASK_CotagRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_ASK_CotagRead(brp_ASK_CotagRead_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */