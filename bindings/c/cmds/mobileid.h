/**
 * @file
 * With this command group, you can set up the Mobile ID functionality to read virtual credentials from smartphones.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_MOBILEID_H__
#define __BRP_BALTECH_SDK_CMDS_MOBILEID_H__
#include "../typedefs.h"
/**
 * No valid credential has been presented to the reader so far.
 */
#define BRP_MobileId_ErrNoCredential BRP_ERR_STATUS(0x4C00, 0x01)
/**
 * The credential is trying to perform an action that doesn't comply with the BALTECH Mobile ID protocol. (For details, please refer to the protocol specification, available on request.)
 */
#define BRP_MobileId_ErrProtocol BRP_ERR_STATUS(0x4C00, 0x02)
/**
 * An authentication error occured, e.g. invalid encryption key or authentication tag.
 */
#define BRP_MobileId_ErrAuthentication BRP_ERR_STATUS(0x4C00, 0x03)
/**
 * The version of the presented credential is not compatible with the current reader firmware.
 */
#define BRP_MobileId_ErrCredentialVersion BRP_ERR_STATUS(0x4C00, 0x04)
/**
 * The presented credential is rejected due to an invalid CMAC.
 */
#define BRP_MobileId_ErrCredentialCmac BRP_ERR_STATUS(0x4C00, 0x05)
/**
 * Mobile ID functionality is currently disabled.
 */
#define BRP_MobileId_ErrDisabled BRP_ERR_STATUS(0x4C00, 0x10)
typedef struct {
	brp_protocol protocol;
	brp_MobileId_Enable_Mode Mode;
} brp_MobileId_Enable_t;
/**
 * This command enables/disables Mobile ID.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Mode** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_MobileId_Enable(brp_protocol protocol, brp_MobileId_Enable_Mode _input_Mode);
#else
brp_errcode brp_MobileId_Enable(brp_MobileId_Enable_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* CredentialId;
	size_t* CredentialId_len;
	brp_mempool *mempool;
} brp_MobileId_GetVirtualCredentialId_t;
/**
 * This command checks if a Mobile ID credential has been presented to the reader since the last _MobileId.GetVirtualCredentialId_ execution. 
 * 
 *   * If a valid credential is detected, the credential identification will be returned in _CredentialId_. 
 *   * If no credential is detected, the MobileId.ErrNoCredential status code will be returned. 
 *   * If an invalid credential is detected, one of the other status codes will be returned. 
 * 
 * 
 * 
 * **If you use Autoread, run AR.GetMessage instead of this command to retrieve the ID of a presented credential.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CredentialId** (out) ASCII-encoded value containing the credential ID
 *   - **CredentialId_len** (out) Length of **CredentialId** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_MobileId_GetVirtualCredentialId(brp_protocol protocol, brp_buf* CredentialId, size_t* CredentialId_len, brp_mempool *mempool);
#else
brp_errcode brp_MobileId_GetVirtualCredentialId(brp_MobileId_GetVirtualCredentialId_t params);
#endif
#endif
/**
 * @}
 */