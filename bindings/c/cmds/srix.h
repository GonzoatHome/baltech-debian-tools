/**
 * @file
 * Srix card commands.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_SRIX_H__
#define __BRP_BALTECH_SDK_CMDS_SRIX_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * No Tag
 */
#define BRP_Srix_ErrNoTag BRP_ERR_STATUS(0x2400, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Frame Error (CRC, parity...)
 */
#define BRP_Srix_ErrFrame BRP_ERR_STATUS(0x2400, 0x03)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * General hf error
 */
#define BRP_Srix_ErrHf BRP_ERR_STATUS(0x2400, 0x04)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Hardware error
 */
#define BRP_Srix_ErrCom BRP_ERR_STATUS(0x2400, 0x05)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Chip type not supported by reader chip
 */
#define BRP_Srix_ErrSrixCardtypeNotSupported BRP_ERR_STATUS(0x2400, 0x06)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Hardware does not support reader chip
 */
#define BRP_Srix_ErrHwNotSupported BRP_ERR_STATUS(0x2400, 0x07)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Command has been interrupted
 */
#define BRP_Srix_ErrCmdBreak BRP_ERR_STATUS(0x2400, 0x08)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_buf* Snr;
	size_t* Snr_len;
	brp_mempool *mempool;
} brp_Srix_Select_t;
/**
 * This command selects a label including anticollision.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Snr** (out) Serial number of selected label
 *   - **Snr_len** (out) Length of **Snr** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Srix_Select(brp_protocol protocol, brp_buf* Snr, size_t* Snr_len, brp_mempool *mempool);
#else
brp_errcode brp_Srix_Select(brp_Srix_Select_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Adr;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_Srix_Read_t;
/**
 * This command reads a secure data page
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Adr** (in) Page Address
 *   - **Data** (out) Data block
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Srix_Read(brp_protocol protocol, unsigned _input_Adr, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_Srix_Read(brp_Srix_Read_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Adr;
	brp_buf Data;
	size_t Data_len;
} brp_Srix_Write_t;
/**
 * This command writes data to a page address of a label.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Adr** (in) Page Address of block to write
 *   - **Data** (in) Len of value counter / data block
 *   - **Data_len** (in) Length of **Data** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Srix_Write(brp_protocol protocol, unsigned _input_Adr, brp_buf _input_Data, size_t _input_Data_len);
#else
brp_errcode brp_Srix_Write(brp_Srix_Write_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */