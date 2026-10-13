/**
 * @file
 * With this command group, you can access MIFARE Ultralight cards in low-level mode. To work with this command group, a card has to be in ISO 14443-3 Type A selected state. This can be achieved using the Iso14a command group.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_ULTRALIGHT_H__
#define __BRP_BALTECH_SDK_CMDS_ULTRALIGHT_H__
#include "../typedefs.h"
/**
 * There's no card in the HF field, or the card doesn't respond.
 */
#define BRP_Ultralight_ErrNoTag BRP_ERR_STATUS(0x2500, 0x01)
/**
 * Authentication with the card has failed.
 */
#define BRP_Ultralight_ErrAuth BRP_ERR_STATUS(0x2500, 0x02)
/**
 * The response frame is invalid, e.g. it may contain an invalid number of bits or an invalid CRC checksum. Please rerun the command.
 */
#define BRP_Ultralight_ErrHf BRP_ERR_STATUS(0x2500, 0x03)
/**
 * The encryption key is undefined or inaccessible.
 */
#define BRP_Ultralight_ErrKey BRP_ERR_STATUS(0x2500, 0x04)
/**
 * The card didn't accept the command. Please check the conditions and rerun the command.
 */
#define BRP_Ultralight_ErrNack BRP_ERR_STATUS(0x2500, 0x05)
/**
 * Communication with the reader chip has failed. Please reset the reader with Sys.Reset and check the reader chip status with Sys.GetBootStatus.
 */
#define BRP_Ultralight_ErrInterface BRP_ERR_STATUS(0x2500, 0x18)
/**
 * The specified command or parameters are unknown.
 */
#define BRP_Ultralight_ErrCmd BRP_ERR_STATUS(0x2500, 0x19)
/**
 * This command isn't supported by the reader hardware.
 */
#define BRP_Ultralight_ErrHwNotSupported BRP_ERR_STATUS(0x2500, 0x20)
#ifdef BALTECH_SDK_INTERNAL
/**
 * This command isn't supported by the reader firmware.
 */
#define BRP_Ultralight_ErrFirmwareNotSupported BRP_ERR_STATUS(0x2500, 0x21)
#endif  // BALTECH_SDK_INTERNAL
/**
 * The command has been aborted because the HF interface has been requested by another task or command. Please reselect the card. 
 * 
 * **This error only occurs when you combine VHL and low-level commands. We highly recommend you avoid that combination as these 2 command sets will interfere with each other's card states.**
 */
#define BRP_Ultralight_BreakErr BRP_ERR_STATUS(0x2500, 0x28)
typedef struct {
	brp_protocol protocol;
	unsigned Cmd;
	brp_buf Param;
	size_t Param_len;
	brp_buf* Response;
	size_t* Response_len;
	brp_mempool *mempool;
} brp_Ultralight_ExecCmd_t;
/**
 * Generic command to communicate to a Mifare Ultralight card.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Cmd** (in) Ultralight command code.
 *   - **Param** (in) Command paramter.
 *   - **Param_len** (in) Length of **Param** (in bytes).
 *   - **Response** (out) Command response.
 *   - **Response_len** (out) Length of **Response** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Ultralight_ExecCmd(brp_protocol protocol, unsigned _input_Cmd, brp_buf _input_Param, size_t _input_Param_len, brp_buf* Response, size_t* Response_len, brp_mempool *mempool);
#else
brp_errcode brp_Ultralight_ExecCmd(brp_Ultralight_ExecCmd_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned PageAdr;
	brp_buf* PageData;
	brp_mempool *mempool;
} brp_Ultralight_Read_t;
/**
 * Standard read command for Ultralight cards. Command returns 4 pages of a card (16 byte).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PageAdr** (in) Page address
 *   - **PageData** (out) Returns content of 4 pages.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Ultralight_Read(brp_protocol protocol, unsigned _input_PageAdr, brp_buf* PageData, brp_mempool *mempool);
#else
brp_errcode brp_Ultralight_Read(brp_Ultralight_Read_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned PageAdr;
	brp_buf PageData;
} brp_Ultralight_Write_t;
/**
 * Standard write command for Ultralight cards. 1 page (4 bytes) is writen to a card.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PageAdr** (in) Page address
 *   - **PageData** (in) 4 byte page data.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Ultralight_Write(brp_protocol protocol, unsigned _input_PageAdr, brp_buf _input_PageData);
#else
brp_errcode brp_Ultralight_Write(brp_Ultralight_Write_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Ultralight_AuthE2_DivMode DivMode;
	bool HasExtIdx;
	unsigned KeyIdx;
	brp_buf DivData;
	size_t DivData_len;
	unsigned KeyExtIdx;
} brp_Ultralight_AuthE2_t;
/**
 * Authenticates to a Ultralight-c card. 
 * 
 * The key used for authentication is specified in the Device / CryptoKey key of the reader's configuration. Key has to be of type 3DES (16 bytes).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **DivMode** (in) Specifies diversification algorithm.
 *   - **HasExtIdx** (in) 
 *   - **KeyIdx** (in) Index
 *   - **DivData** (in) Diversification data.
 *   - **DivData_len** (in) Length of **DivData** (in bytes).
 *   - **KeyExtIdx** (in) Crypto memory index (SAM or crypto memory) of authentication key     * SAM: key version (0..0xFF)    * Crypto memory: page (0..15)
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Ultralight_AuthE2(brp_protocol protocol, brp_Ultralight_AuthE2_DivMode _input_DivMode, bool _input_HasExtIdx, unsigned _input_KeyIdx, brp_buf _input_DivData, size_t _input_DivData_len, unsigned _input_KeyExtIdx);
#else
brp_errcode brp_Ultralight_AuthE2(brp_Ultralight_AuthE2_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Ultralight_AuthUser_CryptoMode CryptoMode;
	brp_buf Key;
	size_t Key_len;
} brp_Ultralight_AuthUser_t;
/**
 * Authenticates to an Ultralight-C/EV1 card.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CryptoMode** (in) Sets the encryption algorithm.
 *   - **Key** (in) Authentication key
 *   - **Key_len** (in) Length of **Key** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Ultralight_AuthUser(brp_protocol protocol, brp_Ultralight_AuthUser_CryptoMode _input_CryptoMode, brp_buf _input_Key, size_t _input_Key_len);
#else
brp_errcode brp_Ultralight_AuthUser(brp_Ultralight_AuthUser_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned SectorNumber;
} brp_Ultralight_SectorSwitch_t;
/**
 * Selects a sector of an Ultralight-C/EV1 card.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SectorNumber** (in) The command is only supported by cards with more than 1Kb memory. The sector number corresponds to the MSB of the block number.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Ultralight_SectorSwitch(brp_protocol protocol, unsigned _input_SectorNumber);
#else
brp_errcode brp_Ultralight_SectorSwitch(brp_Ultralight_SectorSwitch_t params);
#endif
#endif
/**
 * @}
 */