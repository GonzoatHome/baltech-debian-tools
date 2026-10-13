/**
 * @file
 * This are HID 125kHz card commands.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_HID_H__
#define __BRP_BALTECH_SDK_CMDS_HID_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * No tag error.
 */
#define BRP_HID_ErrHidNoTag BRP_ERR_STATUS(0x3300, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Wrong length or wrong data.
 */
#define BRP_HID_ErrHidRxdata BRP_ERR_STATUS(0x3300, 0x03)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Parity error.
 */
#define BRP_HID_ErrHidParity BRP_ERR_STATUS(0x3300, 0x05)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Wrong command param (on HF).
 */
#define BRP_HID_ErrHidParam BRP_ERR_STATUS(0x3300, 0x07)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Another task requested control over HF via hf_request_control.
 */
#define BRP_HID_ErrHidHfreqctrl BRP_ERR_STATUS(0x3300, 0x08)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Reader chip hardware error.
 */
#define BRP_HID_ErrHidHw BRP_ERR_STATUS(0x3300, 0x09)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Hardware not supported.
 */
#define BRP_HID_ErrHidHwNotSupported BRP_ERR_STATUS(0x3300, 0x0B)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * You use an HID Prox/Indala/Keri card, but the reader doesn't have the [required Prox license](https://docs.baltech.de/project-setup/get-prox-license-for-hid-prox-indala-keri.html).
 */
#define BRP_HID_ErrLicense BRP_ERR_STATUS(0x3300, 0x0C)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_HID_IndalaRead_t;
/**
 * Returns data of Indala tags (read only tag).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (out) Indala data.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_IndalaRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_HID_IndalaRead(brp_HID_IndalaRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_HID_ProxRead_t;
/**
 * Returns raw data of HID prox tag (read only tag / 44 bit).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (out) HID data.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_ProxRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_HID_ProxRead(brp_HID_ProxRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_HID_AwidRead_t;
/**
 * Returns number of a AWID tag (read only tag / 44 bit).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (out) Awid data
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_AwidRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_HID_AwidRead(brp_HID_AwidRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_HID_IoProxRead_t;
/**
 * Returns number of a IoProx tag (read only tag / 64 bit).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (out) IoProx data (5 byte).
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_IoProxRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_HID_IoProxRead(brp_HID_IoProxRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_HID_Prox32Read_t;
/**
 * Returns raw data of HID prox 32 (orange) tag (read only tag / 32bit).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (out) HID prox32 data.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_Prox32Read(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_HID_Prox32Read(brp_HID_Prox32Read_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned* Len;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_HID_PyramidRead_t;
/**
 * Returns number of Farpointe Pyramid cards (variable bitlength).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Len** (out) 
 *   - **Data** (out) 
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_PyramidRead(brp_protocol protocol, unsigned* Len, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_HID_PyramidRead(brp_HID_PyramidRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_HID_IndalaSecureRead_t;
/**
 * Returns data of indala tags (read only tag).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (out) Indala data.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_IndalaSecureRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_HID_IndalaSecureRead(brp_HID_IndalaSecureRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_HID_IdteckRead_t;
/**
 * Returns data of idteck tags (read only tag).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (out) Idteck data.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_IdteckRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_HID_IdteckRead(brp_HID_IdteckRead_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */