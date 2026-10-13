/**
 * @file
 * This are Hitag 125 kHz card commands.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_HITAG_H__
#define __BRP_BALTECH_SDK_CMDS_HITAG_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * No tag error.
 */
#define BRP_Hitag_ErrHtgNoTag BRP_ERR_STATUS(0x3000, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Collision occurred.
 */
#define BRP_Hitag_ErrHtgCollision BRP_ERR_STATUS(0x3000, 0x02)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Wrong length or wrong data.
 */
#define BRP_Hitag_ErrHtgRxdata BRP_ERR_STATUS(0x3000, 0x03)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Receive checksum error.
 */
#define BRP_Hitag_HtgChecksum BRP_ERR_STATUS(0x3000, 0x04)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Wrong command parameter.
 */
#define BRP_Hitag_HtgWrongParam BRP_ERR_STATUS(0x3000, 0x07)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Authentication error.
 */
#define BRP_Hitag_ErrHtgAuth BRP_ERR_STATUS(0x3000, 0x09)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * ISR buffer overflow during send/receive, TO during send.
 */
#define BRP_Hitag_ErrHtgOvTo BRP_ERR_STATUS(0x3000, 0x08)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Reader chip HW error.
 */
#define BRP_Hitag_ErrHtgHw BRP_ERR_STATUS(0x3000, 0x0A)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Crypt processor HW error.
 */
#define BRP_Hitag_ErrHtgCr BRP_ERR_STATUS(0x3000, 0x0B)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Update of configuration not successful.
 */
#define BRP_Hitag_ErrHtgCfg BRP_ERR_STATUS(0x3000, 0x0C)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Another task requested control over HF via hf_request_control.
 */
#define BRP_Hitag_ErrHtgHfreqctrl BRP_ERR_STATUS(0x3000, 0x0D)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Hardware not supported.
 */
#define BRP_Hitag_ErrHtgHwNotSupported BRP_ERR_STATUS(0x3000, 0x0F)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_Hitag_Request_TagType TagType;
	brp_Hitag_Request_Mode Mode;
	unsigned* Snr;
} brp_Hitag_Request_t;
/**
 * Request and AC / according to Mode byte you can request Hitag-1 and Hitag-S tags.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **TagType** (in) 
 *   - **Mode** (in) 
 *   - **Snr** (out) Serial Number of selected label.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Hitag_Request(brp_protocol protocol, brp_Hitag_Request_TagType _input_TagType, brp_Hitag_Request_Mode _input_Mode, unsigned* Snr);
#else
brp_errcode brp_Hitag_Request(brp_Hitag_Request_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Hitag_Select_SelMode SelMode;
	unsigned Pwd;
	unsigned* Page1;
} brp_Hitag_Select_t;
/**
 * Selects a Hitag-1 or Hitag-S tag and returns page 1.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SelMode** (in) 
 *   - **Pwd** (in) Password for Hitag2.
 *   - **Page1** (out) Page 1 (CON and (PWDH0)).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Hitag_Select(brp_protocol protocol, brp_Hitag_Select_SelMode _input_SelMode, unsigned _input_Pwd, unsigned* Page1);
#else
brp_errcode brp_Hitag_Select(brp_Hitag_Select_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Hitag_Halt_t;
/**
 * Sets a Hitag1/S label in halt mode.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Hitag_Halt(brp_protocol protocol);
#else
brp_errcode brp_Hitag_Halt(brp_Hitag_Halt_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
	bool InvRead;
	bool KeyB;
	bool Encrypt;
	bool BlockRead;
	unsigned** PageNr;
	size_t* PageNr_len;
	brp_mempool *mempool;
} brp_Hitag_Read_t;
/**
 * Reads a Hitag1/S label.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) Page address of a label.
 *   - **InvRead** (in) B3 = 1: for Hitag2: Inverted read, result is returned not inverted.
 *   - **KeyB** (in) B2 = 1: for Hitag1: KeyB will be used for authentification.
 *   - **Encrypt** (in) B1 = 1: for Hitag1: block will be read encrypted.
 *   - **BlockRead** (in) B0 = 1: block(up to 4 pages) will be read instead of a single block.
 *   - **PageNr** (out) 
 *   - **PageNr_len** (out) Number of elements in **PageNr**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Hitag_Read(brp_protocol protocol, unsigned _input_Address, bool _input_InvRead, bool _input_KeyB, bool _input_Encrypt, bool _input_BlockRead, unsigned** PageNr, size_t* PageNr_len, brp_mempool *mempool);
#else
brp_errcode brp_Hitag_Read(brp_Hitag_Read_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
	bool KeyB;
	bool Encrypt;
	bool BlockWrite;
	unsigned* PageNr;
	size_t PageNr_len;
} brp_Hitag_Write_t;
/**
 * Writes data to a Hitag1/S label.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) Page address of a label.
 *   - **KeyB** (in) B2 = 1: for Hitag1: KeyB will be used for authentification.
 *   - **Encrypt** (in) B1 = 1: for Hitag1: block will be read encrypted.
 *   - **BlockWrite** (in) B0 = 1: block(up to 4 pages) will be read instead of a single block.
 *   - **PageNr** (in) 
 *   - **PageNr_len** (in) Number of elements in **PageNr**.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Hitag_Write(brp_protocol protocol, unsigned _input_Address, bool _input_KeyB, bool _input_Encrypt, bool _input_BlockWrite, unsigned* _input_PageNr, size_t _input_PageNr_len);
#else
brp_errcode brp_Hitag_Write(brp_Hitag_Write_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool Reset;
	bool HtgS;
	unsigned* Len;
	size_t Len_len;
} brp_Hitag_PersonaliseHtg_t;
/**
 * Writes personalization data for Hitag1/2 to coprocessor.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Reset** (in) B1=True: reset Htg1/2/S personalization values to 0xFF.
 *   - **HtgS** (in) B0=True: Personalize HtgS (3 words) instead of Htg1/2 (9 words).
 *   - **Len** (in) 
 *   - **Len_len** (in) Number of elements in **Len**.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Hitag_PersonaliseHtg(brp_protocol protocol, bool _input_Reset, bool _input_HtgS, unsigned* _input_Len, size_t _input_Len_len);
#else
brp_errcode brp_Hitag_PersonaliseHtg(brp_Hitag_PersonaliseHtg_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */