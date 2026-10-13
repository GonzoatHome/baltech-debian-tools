/**
 * @file
 * This command group contains commands needed to update the firmware of the reader.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_MAIN_H__
#define __BRP_BALTECH_SDK_CMDS_MAIN_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * Is returned by isFirmwareUpToDate() if the following piece of firmware is not up to date.
 */
#define BRP_Main_ErrOutdatedFirmware BRP_ERR_STATUS(0xF000, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Is returned by isFirmwareUpToDate() if it's unknown whether the following piece of firmware is outdated or not.
 */
#define BRP_Main_ErrUnknownVersion BRP_ERR_STATUS(0xF000, 0x02)
#endif  // BALTECH_SDK_INTERNAL
/**
 * Is returned by Bf3UploadStart if an upload process is already running or by Bf3UploadContinue if an upload process is currently not active.
 */
#define BRP_Main_ErrInvalidState BRP_ERR_STATUS(0xF000, 0x10)
/**
 * Is returned by Bf3UploadContinue if BF3/BEC2 file data couldn't be retrieved from the host.
 */
#define BRP_Main_ErrReadFile BRP_ERR_STATUS(0xF000, 0x11)
/**
 * Is returned by Bf3UploadContinue if the BF3/BEC2 file has an invalid format.
 */
#define BRP_Main_ErrInvalidFormat BRP_ERR_STATUS(0xF000, 0x12)
/**
 * Is returned by Bf3UploadContinue if the customer key of the BEC2 file doesn't match the customer key stored in the reader.
 */
#define BRP_Main_ErrInvalidCustomerKey BRP_ERR_STATUS(0xF000, 0x13)
/**
 * Is returned by Bf3UploadContinue if the Config Security Code of the BEC2 file doesn't match the Config Security Code stored in the reader ([ learn more](https://docs.baltech.de/project-setup/security.html#config-security-code)).
 */
#define BRP_Main_ErrInvalidConfigSecurityCode BRP_ERR_STATUS(0xF000, 0x14)
/**
 * Is returned by Bf3UploadContinue if the configuration version of the BEC2 file is older than the configuration version stored in the reader.
 */
#define BRP_Main_ErrInvalidConfigVersion BRP_ERR_STATUS(0xF000, 0x15)
/**
 * Is returned by Bf3UploadContinue if the Message Authentication Code (CMAC) of the BF3/BEC2 file is incorrect.
 */
#define BRP_Main_ErrInvalidCmac BRP_ERR_STATUS(0xF000, 0x16)
/**
 * Is returned by Bf3UploadContinue if a component of the current BF3/BEC2 file couldn't be written to the reader memory.
 */
#define BRP_Main_ErrUpload BRP_ERR_STATUS(0xF000, 0x17)
/**
 * Is returned by Bf3UploadContinue if the BF3/BEC2 file contains a firmware which is not supported by the reader hardware.
 */
#define BRP_Main_ErrUnsupportedFirmware BRP_ERR_STATUS(0xF000, 0x18)
/**
 * Is returned by Bf3UploadContinue if all relevant components of the current BF3/BEC2 file are already up to date.
 */
#define BRP_Main_ErrAlreadyUpToDate BRP_ERR_STATUS(0xF000, 0x19)
/**
 * Is returned by Bf3UploadContinue if the reader was not able to decode the current BEC2 file, because there is no Config Security Code stored in the reader yet.
 */
#define BRP_Main_ErrMissingConfigSecurityCode BRP_ERR_STATUS(0xF000, 0x1A)
/**
 * The elliptic curve key that is used to encrypt the configuration is wrong.
 */
#define BRP_Main_ErrInvalidEccKey BRP_ERR_STATUS(0xF000, 0x1B)
/**
 * Is returned by SwitchFW and Bf3UploadContinue if the cryptographic signature of the firmware cannot be verified successfully.
 */
#define BRP_Main_ErrVerify BRP_ERR_STATUS(0xF000, 0x1C)
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_buf Bf2Line;
	size_t Bf2Line_len;
	brp_Main_Bf2Upload_ResultCode* ResultCode;
	unsigned* InvertedResultCode;
} brp_Main_Bf2Upload_t;
/**
 * This command transfers a single line of a BF2 file starting with a colon to the reader (needed for firmware upload).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Bf2Line** (in) This corresponds to 1 line in a BF2 file starting with a colon instead of a hash sign. As BF2 files are text files, you need to strip each space and colon from a BF2 line and transform each hex digit pair to a byte. Then, transfer the resulting sequence of bytes in this field.
 *   - **Bf2Line_len** (in) Length of **Bf2Line** (in bytes).
 *   - **ResultCode** (out) Error code of this operation
 *   - **InvertedResultCode** (out) Value of _ResultCode_ with inverted bits (= _ResultCode_ XOR 0xFF)
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Main_Bf2Upload(brp_protocol protocol, brp_buf _input_Bf2Line, size_t _input_Bf2Line_len, brp_Main_Bf2Upload_ResultCode* ResultCode, unsigned* InvertedResultCode);
#else
brp_errcode brp_Main_Bf2Upload(brp_Main_Bf2Upload_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Main_SwitchFW_t;
/**
 * After uploading the complete firmware with Main.Bf2Upload, this command is needed to activate the new firmware and reboot the reader.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Main_SwitchFW(brp_protocol protocol);
#else
brp_errcode brp_Main_SwitchFW(brp_Main_SwitchFW_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf Filter;
	size_t Filter_len;
	bool* Matches;
} brp_Main_MatchPlatformId2_t;
/**
 * This command checks if the PlatformID2 of the reader matches the PlatformID2 provided in the _Filter_ parameter. 
 * 
 * **If this command is not available, the Sys.GetPlatformId command can be used as a fallback.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Filter** (in) Filter string from a BF2 file to compare to the reader's PlatformID2.
 *   - **Filter_len** (in) Length of **Filter** (in bytes).
 *   - **Matches** (out) Returns _true_ if the _Filter_ string matches the PlatformID2 of the reader.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Main_MatchPlatformId2(brp_protocol protocol, brp_buf _input_Filter, size_t _input_Filter_len, bool* Matches);
#else
brp_errcode brp_Main_MatchPlatformId2(brp_Main_MatchPlatformId2_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf VersionDesc;
	size_t VersionDesc_len;
} brp_Main_IsFirmwareUpToDate_t;
/**
 * This command checks if the following part of the firmware is already up to date. It must be called exactly in the order it occurs in the BF2 file: If the firmware is split in 2 parts and this command is in between them, it has to be called after transferring the first part and before loading the second part. Otherwise it is not guaranteed that it works correctly.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **VersionDesc** (in) A pattern that describes the firmware version of the following firmware part. Should not be interpreted by user software!
 *   - **VersionDesc_len** (in) Length of **VersionDesc** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Main_IsFirmwareUpToDate(brp_protocol protocol, brp_buf _input_VersionDesc, size_t _input_VersionDesc_len);
#else
brp_errcode brp_Main_IsFirmwareUpToDate(brp_Main_IsFirmwareUpToDate_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned* ReqDataAdr;
	unsigned* ReqDataLen;
} brp_Main_Bf3UploadStart_t;
/**
 * This command starts the upload of a BEC2/BF3 file to update the reader's configuration and/or firmware.  
 * The reader responds by requesting the first data block within the BEC2/BF3 file. To transfer this data block, run the Main.Bf3UploadContinue command afterwards. 
 * 
 * **For more details about implementation, please refer to the help topic[ Implement wired upload via the host](https://docs.baltech.de/developers/implement-wired-upload.html) .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ReqDataAdr** (out) Start byte of first data block requested by the reader
 *   - **ReqDataLen** (out) Number of bytes of first data block requested by the reader
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Main_Bf3UploadStart(brp_protocol protocol, unsigned* ReqDataAdr, unsigned* ReqDataLen);
#else
brp_errcode brp_Main_Bf3UploadStart(brp_Main_Bf3UploadStart_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned DataAdr;
	brp_buf Data;
	size_t Data_len;
	bool* Reconnect;
	bool* Continue;
	unsigned* ReqDataAdr;
	unsigned* ReqDataLen;
	bool* ContainsEstimation;
	bool* ContainsReconnectRetryTimeout;
	unsigned* ReconnectRetryTimeout;
	unsigned* EstimatedNumberOfBytes;
	unsigned* EstimatedTimeOverhead;
} brp_Main_Bf3UploadContinue_t;
/**
 * This command is used to transfer the data of a BEC2/BF3 file block by block to the reader.  
 * The host transfers the data block of the BEC2/BF3 file which has been requested by the reader previously. The response parameter _RequiredAction_ indicates how the host has to proceed afterwards: 
 * 
 *   * Transfer the next data block. 
 *   * Disconnect and reconnect to the reader. 
 *   * Upload completed - no more data to transfer. 
 * 
 * 
 * 
 * **For more details about implementation, please refer to the help topic[ Implement wired upload via the host](https://docs.baltech.de/developers/implement-wired-upload.html) .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **DataAdr** (in) Address of data block that is being transferred. Has to correspond to the _ReqDataAdr_ parameter in the reader's response to the previous command (i.e. the last _Bf3UploadContinue_ or the Main.Bf3UploadStart command).
 *   - **Data** (in) Data requested by the reader
 *   - **Data_len** (in) Length of **Data** (in bytes).
 *   - **Reconnect** (out) If _true_ , the host has to disconnect and reconnect to the reader.
 *   - **Continue** (out) If _true_ , the host has to continue by transferring the next data block of the BEC2/BF3 file.   If _false_ , the reader has received all required data blocks: Upload is completed.
 *   - **ReqDataAdr** (out) Start byte of next data block requested by the reader
 *   - **ReqDataLen** (out) Number of bytes of next data block requested by the reader. This value may also be 0.
 *   - **ContainsEstimation** (out) If _true_ , the response contains estimation information fields.
 *   - **ContainsReconnectRetryTimeout** (out) If _true_ , the response contains the _ReconnectRetryTimeout_ field.
 *   - **ReconnectRetryTimeout** (out) If a reconnect is requested, this field specifies how long the host has to try (time period in ms).  **You need to add the _ReconnectRetryTimout_ to the OS-specific base reconnect timeout.   For Windows, we recommend a base reconnect timeout of 10000 ms. For all other platforms, please check how long it takes for a reader to be available again after a reboot.**
 *   - **EstimatedNumberOfBytes** (out) This is an estimation of the total amount of data bytes that have to be transferred from the host to the reader to upload the current BEC2/BF3 file.   **  This information is only returned once as soon as the reader has gathered enough data to perform this estimation.  _Note:_   In special cases, e.g. if you re-perform a firmware upload that was aborted before, the reader returns a worst-case estimation that may be higher than the actual amount of data bytes to transfer.  **
 *   - **EstimatedTimeOverhead** (out) This is an estimation of the total time in ms the reader requires for additional internal tasks during the upload, which lead to occasional communication pauses.   If the reader can maintain communication during such a task, it keeps responding to calls of the _Bf3UploadContinue_ command; the _ReqDataLen_ response parameter will then be set to _0_. If the reader can't maintain communication, it asks for a reconnect with an additional retry timeout, which is indicated by the optional _ReconnectRetryTimeout_ parameter.   **This information is only returned once as soon as the reader has gathered enough data to perform this estimation.**
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Main_Bf3UploadContinue(brp_protocol protocol, unsigned _input_DataAdr, brp_buf _input_Data, size_t _input_Data_len, bool* Reconnect, bool* Continue, unsigned* ReqDataAdr, unsigned* ReqDataLen, bool* ContainsEstimation, bool* ContainsReconnectRetryTimeout, unsigned* ReconnectRetryTimeout, unsigned* EstimatedNumberOfBytes, unsigned* EstimatedTimeOverhead);
#else
brp_errcode brp_Main_Bf3UploadContinue(brp_Main_Bf3UploadContinue_t params);
#endif
#endif
/**
 * @}
 */