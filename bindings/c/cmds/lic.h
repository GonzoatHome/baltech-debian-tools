/**
 * @file
 * This command group contains commands related to license management.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_LIC_H__
#define __BRP_BALTECH_SDK_CMDS_LIC_H__
#include "../typedefs.h"
/**
 * No valid LicenseCard detected.
 */
#define BRP_Lic_ErrNoLicCard BRP_ERR_STATUS(0x0B00, 0x01)
/**
 * Card cannot be accessed (e.g. card was removed too early).
 */
#define BRP_Lic_ErrAccess BRP_ERR_STATUS(0x0B00, 0x02)
/**
 * The license type of the presented LicenseCard isn't supported by the reader hardware or firmware.  
 * _Example:_ Readers without 125 kHz interface don't support LicenseCards containing [Prox licenses](https://docs.baltech.de/installation/deploy-license.html).
 */
#define BRP_Lic_ErrNotSupported BRP_ERR_STATUS(0x0B00, 0x03)
/**
 * A license of this type is already activated on the reader.
 */
#define BRP_Lic_ErrAlreadyActive BRP_ERR_STATUS(0x0B00, 0x04)
/**
 * The LicenseCard contains no free license.
 */
#define BRP_Lic_ErrNoFreeLicense BRP_ERR_STATUS(0x0B00, 0x05)
/**
 * The license couldn't be activated on the reader.  
 * 
 * 
 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
 */
#define BRP_Lic_ErrActivation BRP_ERR_STATUS(0x0B00, 0x06)
typedef struct {
	brp_protocol protocol;
	brp_LicenseBitMask* LicenseBitMask;
} brp_Lic_GetLicenses_t;
/**
 * This command retrieves a bit mask of the licenses that are activated on the reader.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **LicenseBitMask** (out) License bit mask
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Lic_GetLicenses(brp_protocol protocol, brp_LicenseBitMask* LicenseBitMask);
#else
brp_errcode brp_Lic_GetLicenses(brp_Lic_GetLicenses_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Lic_ReadLicCard_t;
/**
 * This command reads and evaluates a LicenseCard. 
 * 
 * A license is debited from the card and activated on the reader if the following applies: 
 * 
 *   * The presented card is a valid LicenseCard.
 *   * This license type is supported by the reader.
 *   * A license of this type is not yet activated on the reader.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Lic_ReadLicCard(brp_protocol protocol);
#else
brp_errcode brp_Lic_ReadLicCard(brp_Lic_ReadLicCard_t params);
#endif
#endif
/**
 * @}
 */