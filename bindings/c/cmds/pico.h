/**
 * @file
 * Picopass card commands.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_PICO_H__
#define __BRP_BALTECH_SDK_CMDS_PICO_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * No PICC
 */
#define BRP_Pico_ErrNoTag BRP_ERR_STATUS(0x1A00, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Collision occurred (value will be ordered with bit position of collision in high nibble!)
 */
#define BRP_Pico_ErrCollision BRP_ERR_STATUS(0x1A00, 0x02)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * General HF error
 */
#define BRP_Pico_ErrHf BRP_ERR_STATUS(0x1A00, 0x04)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Bit error, parity error or frame error (start/stop-bit)
 */
#define BRP_Pico_ErrFrame BRP_ERR_STATUS(0x1A00, 0x07)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * CRC checksum error
 */
#define BRP_Pico_ErrCrc BRP_ERR_STATUS(0x1A00, 0x08)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Communication error UC - reader chip
 */
#define BRP_Pico_ErrCom BRP_ERR_STATUS(0x1A00, 0x10)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Reader chip does not support card type
 */
#define BRP_Pico_ErrCardNotSupported BRP_ERR_STATUS(0x1A00, 0x22)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Command not supported by hardware
 */
#define BRP_Pico_ErrHwNotSupported BRP_ERR_STATUS(0x1A00, 0x23)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned HfMode;
} brp_Pico_SetHfMode_t;
/**
 * Specify HF communication mode that should be used by the commands in this command-set.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **HfMode** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_SetHfMode(brp_protocol protocol, unsigned _input_HfMode);
#else
brp_errcode brp_Pico_SetHfMode(brp_Pico_SetHfMode_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* ASNB;
	size_t* ASNB_len;
	brp_mempool *mempool;
} brp_Pico_RequestAnticoll_t;
/**
 * Request PICCs and perform anticollision.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ASNB** (out) Anticollision serial number of PICC
 *   - **ASNB_len** (out) Length of **ASNB** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_RequestAnticoll(brp_protocol protocol, brp_buf* ASNB, size_t* ASNB_len, brp_mempool *mempool);
#else
brp_errcode brp_Pico_RequestAnticoll(brp_Pico_RequestAnticoll_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf ASNB;
	size_t ASNB_len;
	brp_buf* Serial;
	size_t* Serial_len;
	brp_mempool *mempool;
} brp_Pico_Select_t;
/**
 * Select PICC.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ASNB** (in) Anticollision serial number of PICC
 *   - **ASNB_len** (in) Length of **ASNB** (in bytes).
 *   - **Serial** (out) Effective serial number of PICC
 *   - **Serial_len** (out) Length of **Serial** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_Select(brp_protocol protocol, brp_buf _input_ASNB, size_t _input_ASNB_len, brp_buf* Serial, size_t* Serial_len, brp_mempool *mempool);
#else
brp_errcode brp_Pico_Select(brp_Pico_Select_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Pico_Halt_t;
/**
 * Set PICC to halt mode.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_Halt(brp_protocol protocol);
#else
brp_errcode brp_Pico_Halt(brp_Pico_Halt_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Book;
	unsigned Page;
	brp_buf* Page1;
	size_t* Page1_len;
	brp_mempool *mempool;
} brp_Pico_SelectBookPage_t;
/**
 * Selects book and page of a selected picopass label
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Book** (in) 
 *   - **Page** (in) 
 *   - **Page1** (out) 
 *   - **Page1_len** (out) Length of **Page1** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_SelectBookPage(brp_protocol protocol, unsigned _input_Book, unsigned _input_Page, brp_buf* Page1, size_t* Page1_len, brp_mempool *mempool);
#else
brp_errcode brp_Pico_SelectBookPage(brp_Pico_SelectBookPage_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool IsDebitKey;
	unsigned KeyIdx;
} brp_Pico_Authenticate_t;
/**
 * Authenticates a previously selected picopass label
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **IsDebitKey** (in) 
 *   - **KeyIdx** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_Authenticate(brp_protocol protocol, bool _input_IsDebitKey, unsigned _input_KeyIdx);
#else
brp_errcode brp_Pico_Authenticate(brp_Pico_Authenticate_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned PageAdr;
	unsigned PageNr;
	brp_buf* PageData;
	size_t* PageData_len;
	brp_mempool *mempool;
} brp_Pico_Read_t;
/**
 * Reads a picopass label
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PageAdr** (in) 
 *   - **PageNr** (in) 
 *   - **PageData** (out) 
 *   - **PageData_len** (out) Length of **PageData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_Read(brp_protocol protocol, unsigned _input_PageAdr, unsigned _input_PageNr, brp_buf* PageData, size_t* PageData_len, brp_mempool *mempool);
#else
brp_errcode brp_Pico_Read(brp_Pico_Read_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned PageAdr;
	brp_buf PageData;
	size_t PageData_len;
} brp_Pico_Write_t;
/**
 * Writes to picopass label
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PageAdr** (in) 
 *   - **PageData** (in) 
 *   - **PageData_len** (in) Length of **PageData** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_Write(brp_protocol protocol, unsigned _input_PageAdr, brp_buf _input_PageData, size_t _input_PageData_len);
#else
brp_errcode brp_Pico_Write(brp_Pico_Write_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */