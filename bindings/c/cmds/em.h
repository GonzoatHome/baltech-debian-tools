/**
 * @file
 * These are EM-marin 125 kHz card commands.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_EM_H__
#define __BRP_BALTECH_SDK_CMDS_EM_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * No tag error.
 */
#define BRP_EM_ErrEmNoTag BRP_ERR_STATUS(0x3100, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Wrong length or wrong data.
 */
#define BRP_EM_ErrEmRxdata BRP_ERR_STATUS(0x3100, 0x03)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Receive checksum error.
 */
#define BRP_EM_ErrEmChecksum BRP_ERR_STATUS(0x3100, 0x04)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Receive parity error.
 */
#define BRP_EM_ErrEmParity BRP_ERR_STATUS(0x3100, 0x05)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Error detected during command execution.
 */
#define BRP_EM_EmCmdError BRP_ERR_STATUS(0x3100, 0x06)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Unknown tag type or modulation not detected.
 */
#define BRP_EM_EmTagtypeNotDetected BRP_ERR_STATUS(0x3100, 0x07)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * ISR buffer overflow during send/receive, TO during send.
 */
#define BRP_EM_ErrEmOvTo BRP_ERR_STATUS(0x3100, 0x08)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Host command parameter error.
 */
#define BRP_EM_EmParamError BRP_ERR_STATUS(0x3100, 0x09)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Another task requested control over HF via hf_request_control.
 */
#define BRP_EM_ErrEmHfreqctrl BRP_ERR_STATUS(0x3100, 0x0A)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Missing Platform ID or Readerchip error.
 */
#define BRP_EM_ErrEmHw BRP_ERR_STATUS(0x3100, 0x0B)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Hardware not supported.
 */
#define BRP_EM_ErrEmHwNotSupported BRP_ERR_STATUS(0x3100, 0x0D)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_EM_DecodeCfg_RxMod RxMod;
	unsigned RxBaud;
} brp_EM_DecodeCfg_t;
/**
 * Configures Mod and Baudtype of receiver. When _RxMod_ is set to _unknown_ , the Mod is automatically scanned. When _RxBaud_ is set to _unknown_ , the baudtype is automatically detected.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **RxMod** (in) 
 *   - **RxBaud** (in) 0:unknown; 0x08..0x40:fc*x
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_DecodeCfg(brp_protocol protocol, brp_EM_DecodeCfg_RxMod _input_RxMod, unsigned _input_RxBaud);
#else
brp_errcode brp_EM_DecodeCfg(brp_EM_DecodeCfg_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_EM_Read4100_t;
/**
 * Reads the UID from EM4100/4102 labels.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (out) 40 bits data of TTF tag.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Read4100(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_EM_Read4100(brp_EM_Read4100_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
	unsigned* Page;
} brp_EM_Read4205_t;
/**
 * Reads a page from EM4205/4305 labels.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) Page address of a label.
 *   - **Page** (out) Page of a label.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Read4205(brp_protocol protocol, unsigned _input_Address, unsigned* Page);
#else
brp_errcode brp_EM_Read4205(brp_EM_Read4205_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
	unsigned Page;
} brp_EM_Write4205_t;
/**
 * Writes a page to EM4205/4305 labels.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) Page address of a label.
 *   - **Page** (in) Page of a label.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Write4205(brp_protocol protocol, unsigned _input_Address, unsigned _input_Page);
#else
brp_errcode brp_EM_Write4205(brp_EM_Write4205_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_EM_Halt4205_t;
/**
 * Disables a 4205 tag until next power on.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Halt4205(brp_protocol protocol);
#else
brp_errcode brp_EM_Halt4205(brp_EM_Halt4205_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Password;
} brp_EM_Login4205_t;
/**
 * Login to a 4205 tag with data has to match block 1.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Password** (in) Password.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Login4205(brp_protocol protocol, unsigned _input_Password);
#else
brp_errcode brp_EM_Login4205(brp_EM_Login4205_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned ProtectMask;
} brp_EM_Protect4205_t;
/**
 * Protects data from being modified.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ProtectMask** (in) Bit mask of pages to protect.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Protect4205(brp_protocol protocol, unsigned _input_ProtectMask);
#else
brp_errcode brp_EM_Protect4205(brp_EM_Protect4205_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
	unsigned* Page;
} brp_EM_Read4469_t;
/**
 * Reads a page from EM4469/4569 labels.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) Page address of a label.
 *   - **Page** (out) Page of a label.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Read4469(brp_protocol protocol, unsigned _input_Address, unsigned* Page);
#else
brp_errcode brp_EM_Read4469(brp_EM_Read4469_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
	unsigned Page;
} brp_EM_Write4469_t;
/**
 * Writes a page to EM4469/4569 labels.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) Page address of a label.
 *   - **Page** (in) Page of a label.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Write4469(brp_protocol protocol, unsigned _input_Address, unsigned _input_Page);
#else
brp_errcode brp_EM_Write4469(brp_EM_Write4469_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_EM_Halt4469_t;
/**
 * Disables a EM4469/4569 tag until next power on.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Halt4469(brp_protocol protocol);
#else
brp_errcode brp_EM_Halt4469(brp_EM_Halt4469_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Password;
} brp_EM_Login4469_t;
/**
 * Login to a EM4469/4569 tag with data has to match block 1.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Password** (in) Password.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Login4469(brp_protocol protocol, unsigned _input_Password);
#else
brp_errcode brp_EM_Login4469(brp_EM_Login4469_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned StartAdr;
	unsigned EndAdr;
	unsigned** PageNr;
	size_t* PageNr_len;
	brp_mempool *mempool;
} brp_EM_Read4450_t;
/**
 * Reads pages from a EM4450 tag (start to end address).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **StartAdr** (in) Start page address of a label.
 *   - **EndAdr** (in) End page address of a label.
 *   - **PageNr** (out) 
 *   - **PageNr_len** (out) Number of elements in **PageNr**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Read4450(brp_protocol protocol, unsigned _input_StartAdr, unsigned _input_EndAdr, unsigned** PageNr, size_t* PageNr_len, brp_mempool *mempool);
#else
brp_errcode brp_EM_Read4450(brp_EM_Read4450_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */