/**
 * @file
 * With the _MCE_ command group, you can set up and control the Mobile Card Emulation (MCE) functionality.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_MCE_H__
#define __BRP_BALTECH_SDK_CMDS_MCE_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * No valid MCE device is currently presented to the reader.
 */
#define BRP_Mce_ErrNoTag BRP_ERR_STATUS(0x4D00, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * MCE functionality is currently disabled.
 */
#define BRP_Mce_ErrDisabled BRP_ERR_STATUS(0x4D00, 0x03)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * A valid BLE license is required, but not available.
 */
#define BRP_Mce_ErrLicense BRP_ERR_STATUS(0x4D00, 0x04)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_Mce_Enable_Mode Mode;
} brp_Mce_Enable_t;
/**
 * This command enables/disables Mobile Card Emulation (MCE).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Mode** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mce_Enable(brp_protocol protocol, brp_Mce_Enable_Mode _input_Mode);
#else
brp_errcode brp_Mce_Enable(brp_Mce_Enable_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* Snr;
	size_t* Snr_len;
	brp_mempool *mempool;
} brp_Mce_Request_t;
/**
 * This command is used to check if a Mobile Card Emulation (MCE) device (usually a smartphone running a particular app) is currently presented to the reader. As long as an MCE device is detected, the command returns the serial number that has been transferred from the device to the reader. 
 * 
 * If no MCE device is detected, the status code Mce.ErrNoTag will be returned. In case MCE is not enabled on the reader, Mce.ErrDisabled will be returned.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Snr** (out) Emulated serial number
 *   - **Snr_len** (out) Length of **Snr** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mce_Request(brp_protocol protocol, brp_buf* Snr, size_t* Snr_len, brp_mempool *mempool);
#else
brp_errcode brp_Mce_Request(brp_Mce_Request_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */