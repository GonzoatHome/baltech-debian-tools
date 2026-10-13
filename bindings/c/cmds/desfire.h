/**
 * @file
 * With this command group, you can access MIFARE DESFire cards in low-level mode. 
 * 
 * You can use these commands to completely manage the card's cryptographic functionality and to simplify the handling of DESFire cards.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_DESFIRE_H__
#define __BRP_BALTECH_SDK_CMDS_DESFIRE_H__
#include "../typedefs.h"
/**
 * There's no card in the HF field, or the card doesn't respond.
 */
#define BRP_Desfire_ErrIso14NoTag BRP_ERR_STATUS(0x1B00, 0x01)
/**
 * The command has been aborted because the HF interface has been requested by another task or command. Please reselect the card. 
 * 
 * **This error only occurs when you combine VHL and low-level commands. We highly recommend you avoid that combination as these 2 command sets will interfere with each other's card states.**
 */
#define BRP_Desfire_ErrBreak BRP_ERR_STATUS(0x1B00, 0x03)
/**
 * The response frame received from the PICC is invalid, e.g. it may contain an invalid number of bits. Please rerun the command.
 */
#define BRP_Desfire_ErrIso14Hf BRP_ERR_STATUS(0x1B00, 0x04)
/**
 * The card behaves in an unspecified way or is corrupted. Please rerun the command or reselect the card.
 */
#define BRP_Desfire_ErrIso14CardInvalid BRP_ERR_STATUS(0x1B00, 0x05)
/**
 * Communication with the reader's HF interface has failed. Please reset the HF interface with Sys.HFReset and check the reader status with Sys.GetBootStatus.
 */
#define BRP_Desfire_ErrReaderChipCommunication BRP_ERR_STATUS(0x1B00, 0x06)
/**
 * ISO 14443-4 error: The command or parameters are invalid.
 */
#define BRP_Desfire_ErrIso14ApduCmd BRP_ERR_STATUS(0x1B00, 0x07)
/**
 * ISO 14443-4 error: The card returned an invalid response, e.g. data with an invalid length. This may have several reasons, e.g. a wrong card type.
 */
#define BRP_Desfire_ErrIso14InvalidResponse BRP_ERR_STATUS(0x1B00, 0x08)
/**
 * Authentication with the PICC has failed, e.g. because the encryption algorithm or key is wrong.
 */
#define BRP_Desfire_ErrPcdAuthentication BRP_ERR_STATUS(0x1B00, 0x09)
/**
 * Secure messaging error: The CRC or MAC checksum doesn't match the transmitted data. Authentication has been lost. Please reauthenticate and rerun the commands.
 */
#define BRP_Desfire_ErrIntegrity BRP_ERR_STATUS(0x1B00, 0x0A)
/**
 * The key in the SAM/crypto memory is invalid or missing.
 */
#define BRP_Desfire_ErrPcdKey BRP_ERR_STATUS(0x1B00, 0x0B)
/**
 * Card error as per DESFire specification: No changes done to backup files, CommitTransaction / AbortTransaction not necessary.
 */
#define BRP_Desfire_ErrNoChanges BRP_ERR_STATUS(0x1B00, 0x0C)
/**
 * The BRP command contains an invalid parameter.
 */
#define BRP_Desfire_ErrPcdParam BRP_ERR_STATUS(0x1B00, 0x0D)
/**
 * The proximity check has timed out. Please reselect the card.
 */
#define BRP_Desfire_VcsAndProxCheckError BRP_ERR_STATUS(0x1B00, 0x0F)
/**
 * This command or parameter isn't supported by the reader firmware.
 */
#define BRP_Desfire_ErrFirmwareNotSupported BRP_ERR_STATUS(0x1B00, 0x10)
/**
 * Communication with the SAM has failed. This may have several reasons, e.g. the wrong SAM type or a failure to activate the SAM. Please check the SAM status and reset the reader with Sys.Reset.
 */
#define BRP_Desfire_ErrSamCommunication BRP_ERR_STATUS(0x1B00, 0x11)
/**
 * Unlocking/authenticating with the SAM has failed. Please check the SamAVx configuration values.
 */
#define BRP_Desfire_ErrSamUnlock BRP_ERR_STATUS(0x1B00, 0x12)
/**
 * This command isn't supported by the reader hardware. 
 * 
 * **This error may refer to any hardware component.**
 */
#define BRP_Desfire_ErrHardwareNotSupported BRP_ERR_STATUS(0x1B00, 0x13)
/**
 * Card error as per DESFire specification: Command code not supported by card. This status code is identical to ErrIllegalCmd (0x33) und returned be older firmware versions.
 */
#define BRP_Desfire_ErrIllegalCmdLegacy BRP_ERR_STATUS(0x1B00, 0x1C)
/**
 * Card error as per DESFire specification: Length of command string invalid.
 */
#define BRP_Desfire_ErrLength BRP_ERR_STATUS(0x1B00, 0x20)
/**
 * Card error as per DESFire specification: Current configuration/state does not allow the requested command.
 */
#define BRP_Desfire_ErrPermissionDenied BRP_ERR_STATUS(0x1B00, 0x21)
/**
 * Card error as per DESFire specification: Value of the parameter invalid.
 */
#define BRP_Desfire_ErrParameter BRP_ERR_STATUS(0x1B00, 0x22)
/**
 * Card error as per DESFire specification: Requested AID not present on PICC.
 */
#define BRP_Desfire_ErrAppNotFound BRP_ERR_STATUS(0x1B00, 0x23)
/**
 * Card error as per DESFire specification: Unrecoverable error in application. Application will be disabled.
 */
#define BRP_Desfire_ErrAppIntegrity BRP_ERR_STATUS(0x1B00, 0x24)
/**
 * Card error as per DESFire specification: Current authentication status does not allow execution of requested command.
 */
#define BRP_Desfire_ErrAuthentication BRP_ERR_STATUS(0x1B00, 0x25)
/**
 * Card error as per DESFire specification: Attempted to read/write beyond the limits of the file.
 */
#define BRP_Desfire_ErrBoundary BRP_ERR_STATUS(0x1B00, 0x27)
/**
 * Card error as per DESFire specification: Unrecoverable error within PICC, PICC will be disabled.
 */
#define BRP_Desfire_ErrPiccIntegrity BRP_ERR_STATUS(0x1B00, 0x28)
/**
 * Card error as per DESFire specification: Previous command was not fully completed. Not all frames were requested or provided by the reader.
 */
#define BRP_Desfire_ErrCommandAborted BRP_ERR_STATUS(0x1B00, 0x29)
/**
 * Card error as per DESFire specification: PICC was disabled by an unrecoverable error.
 */
#define BRP_Desfire_ErrPiccDisabled BRP_ERR_STATUS(0x1B00, 0x2A)
/**
 * Card error as per DESFire specification: Number of applications limited to 28, no additional CreateApplication possible.
 */
#define BRP_Desfire_ErrCount BRP_ERR_STATUS(0x1B00, 0x2B)
/**
 * Card error as per DESFire specification: Creation of file/application failed because file/application with same number already exists.
 */
#define BRP_Desfire_ErrDuplicate BRP_ERR_STATUS(0x1B00, 0x2C)
/**
 * Card error as per DESFire specification: Could not complete NV-write operation due to loss of power, internal backup/rollback mechanism activated.
 */
#define BRP_Desfire_ErrEeprom BRP_ERR_STATUS(0x1B00, 0x2D)
/**
 * Card error as per DESFire specification: Specified file number does not exist.
 */
#define BRP_Desfire_ErrFileNotFound BRP_ERR_STATUS(0x1B00, 0x2E)
/**
 * Card error as per DESFire specification: Unrecoverable error within file, file will be disabled.
 */
#define BRP_Desfire_ErrFileIntegrity BRP_ERR_STATUS(0x1B00, 0x2F)
/**
 * Card error as per DESFire specification: Invalid key number specified.
 */
#define BRP_Desfire_ErrNoSuchKey BRP_ERR_STATUS(0x1B00, 0x30)
/**
 * Card error as per DESFire specification: Insufficient NV-Memory to complete command .
 */
#define BRP_Desfire_ErrOutOfMemory BRP_ERR_STATUS(0x1B00, 0x32)
/**
 * Card error as per DESFire specification: Command code not supported by card.
 */
#define BRP_Desfire_ErrIllegalCmd BRP_ERR_STATUS(0x1B00, 0x33)
/**
 * Card error as per DESFire specification: Too many commands in the session or transaction.
 */
#define BRP_Desfire_ErrCmdOverflow BRP_ERR_STATUS(0x1B00, 0x34)
typedef struct {
	brp_protocol protocol;
	unsigned Cmd;
	brp_buf Header;
	size_t Header_len;
	brp_buf Param;
	size_t Param_len;
	brp_Desfire_ExecCommand_CryptoMode CryptoMode;
	unsigned ResponseLen;
	brp_buf* Resp;
	size_t* Resp_len;
	brp_mempool *mempool;
} brp_Desfire_ExecCommand_t;
/**
 * Generic command to communicate to a DESFire card. Depending on the value of the _CryptoMode_ parameter, data will be transmitted plain, MACed or encrypted. 
 * 
 * The DESFire command frame has to be split into two parts, header and data. The data block will be encrypted whereas the header block is left unencrypted. 
 * 
 * Example: in the Desfire _ChangeKeySettings_ command, the header is empty. The encrypted key settings will be transferred in the data block.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Cmd** (in) DESFire Command code
 *   - **Header** (in) Header of command. The header is always sent buf unencrypted. It must not be larger than 59 bytes.
 *   - **Header_len** (in) Length of **Header** (in bytes).
 *   - **Param** (in) Parameter data of command (will be encrypted or MACed according to the value of the _CryptoMode_ variable).
 *   - **Param_len** (in) Length of **Param** (in bytes).
 *   - **CryptoMode** (in) Type of encryption.
 *   - **ResponseLen** (in) Expected length of response. For commands where the length of the response is not known by the host (i.e. Desfire.ReadData with _Len_ = 0), this value has to be set to 0xFFFF.
 *   - **Resp** (out) Response of command.
 *   - **Resp_len** (out) Length of **Resp** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_ExecCommand(brp_protocol protocol, unsigned _input_Cmd, brp_buf _input_Header, size_t _input_Header_len, brp_buf _input_Param, size_t _input_Param_len, brp_Desfire_ExecCommand_CryptoMode _input_CryptoMode, unsigned _input_ResponseLen, brp_buf* Resp, size_t* Resp_len, brp_mempool *mempool);
#else
brp_errcode brp_Desfire_ExecCommand(brp_Desfire_ExecCommand_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Desfire_Authenticate_SecureMessaging SecureMessaging;
	unsigned DesKeynr;
	unsigned KeyId;
	bool KeyHasDivData;
	brp_Desfire_Authenticate_KeyDivMode KeyDivMode;
	bool KeyHasExtIdx;
	brp_buf KeyDivData;
	size_t KeyDivData_len;
	unsigned KeyExtIdx;
} brp_Desfire_Authenticate_t;
/**
 * This command authenticates a card with the reader. All authentication modes of DESFire cards are supported. Subsequent commands, such as Desfire.ExecCommand, take the authentication mode into account when communicating with a card. 
 * 
 * The key used for authentication is specified in the Device / CryptoKey key of the reader's configuration.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SecureMessaging** (in) Sets the secure messaging mode.
 *   - **DesKeynr** (in) DESFire key number.
 *   - **KeyId** (in) ID of authentication key in the reader's configuration (0x00-0xBF).
 *   - **KeyHasDivData** (in) Specifies external diversification data (_KeyDivData_ parameter) if set.
 *   - **KeyDivMode** (in) Specifies diversification algorithm.
 *   - **KeyHasExtIdx** (in) Set this flag if extended crypto memory is used (using _KeyExtIdx_ parameter).
 *   - **KeyDivData** (in) Diversification data (8 byte for DES / 16 for AES key).
 *   - **KeyDivData_len** (in) Length of **KeyDivData** (in bytes).
 *   - **KeyExtIdx** (in) Crypto Memory Index (SAM or CryptoMemory) of authentication key     * SAM: Key version (0..0xFF)    * Crypto Memory: Page (0..15)
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_Authenticate(brp_protocol protocol, brp_Desfire_Authenticate_SecureMessaging _input_SecureMessaging, unsigned _input_DesKeynr, unsigned _input_KeyId, bool _input_KeyHasDivData, brp_Desfire_Authenticate_KeyDivMode _input_KeyDivMode, bool _input_KeyHasExtIdx, brp_buf _input_KeyDivData, size_t _input_KeyDivData_len, unsigned _input_KeyExtIdx);
#else
brp_errcode brp_Desfire_Authenticate(brp_Desfire_Authenticate_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Desfire_AuthExtKey_SecureMessaging SecureMessaging;
	unsigned DesKeyNr;
	brp_Desfire_AuthExtKey_CryptoMode CryptoMode;
	brp_buf Key;
	size_t Key_len;
} brp_Desfire_AuthExtKey_t;
/**
 * This command authenticates a card with the reader, similarly to the Desfire.Authenticate command, but uses an external authentication key provided as a parameter. Allowed are keys with a length of 8, 16 and 24 Byte. 
 * 
 *   * 8 Byte keys are always DES keys. 
 *   * 16 Byte keys can be DES and AES keys. 
 *   * 24 Byte keys are only used for 3K3DES encryption.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SecureMessaging** (in) Sets the secure messaging mode.
 *   - **DesKeyNr** (in) DESFire key number (0-13).
 *   - **CryptoMode** (in) Sets the encryption algorithm.
 *   - **Key** (in) Key to use for authentication
 *   - **Key_len** (in) Length of **Key** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_AuthExtKey(brp_protocol protocol, brp_Desfire_AuthExtKey_SecureMessaging _input_SecureMessaging, unsigned _input_DesKeyNr, brp_Desfire_AuthExtKey_CryptoMode _input_CryptoMode, brp_buf _input_Key, size_t _input_Key_len);
#else
brp_errcode brp_Desfire_AuthExtKey(brp_Desfire_AuthExtKey_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned AppId;
} brp_Desfire_SelectApplication_t;
/**
 * Selects an application of the DESFire card. Has to be called before any file specific command.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **AppId** (in) ID of application to select - range from 0x00000000 to 0x00FFFFFF. The value 0 corresponds to the Master application (PICC level, root directory).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_SelectApplication(brp_protocol protocol, unsigned _input_AppId);
#else
brp_errcode brp_Desfire_SelectApplication(brp_Desfire_SelectApplication_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned FileId;
	unsigned Adr;
	unsigned Len;
	brp_Desfire_ReadData_Mode Mode;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_Desfire_ReadData_t;
/**
 * Reads data from a Standard or Backup data file.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **FileId** (in) ID of file to read.
 *   - **Adr** (in) Offset position within file. Ranges from 0x000000 to (file size -1).
 *   - **Len** (in) Length of data to read. If _Len_ = 0, the entire data starting from the offset position will be read.
 *   - **Mode** (in) Communication settings linked to the file.
 *   - **Data** (out) Data read from card.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_ReadData(brp_protocol protocol, unsigned _input_FileId, unsigned _input_Adr, unsigned _input_Len, brp_Desfire_ReadData_Mode _input_Mode, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_Desfire_ReadData(brp_Desfire_ReadData_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned FileId;
	unsigned Adr;
	brp_buf Data;
	size_t Data_len;
	brp_Desfire_WriteData_Mode Mode;
} brp_Desfire_WriteData_t;
/**
 * Writes data to a Standard or a Backup data file.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **FileId** (in) ID of file to read.
 *   - **Adr** (in) Position within file.
 *   - **Data** (in) Data read from card.
 *   - **Data_len** (in) Length of **Data** (in bytes).
 *   - **Mode** (in) Communication settings linked to the file.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_WriteData(brp_protocol protocol, unsigned _input_FileId, unsigned _input_Adr, brp_buf _input_Data, size_t _input_Data_len, brp_Desfire_WriteData_Mode _input_Mode);
#else
brp_errcode brp_Desfire_WriteData(brp_Desfire_WriteData_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Desfire_ChangeExtKey_MasterKeyType MasterKeyType;
	bool IsKeySet;
	bool IsAesKey;
	bool IsVersion;
	bool IsChangeKey;
	unsigned KeyNo;
	unsigned KeyVersion;
	brp_buf NewKey;
	size_t NewKey_len;
	brp_buf OldKey;
	size_t OldKey_len;
	unsigned KeySet;
} brp_Desfire_ChangeExtKey_t;
/**
 * This command allows to change any key stored on the card. 
 * 
 * The key length has to be set according to the desired encryption algorithm: 
 * 
 *   * DES encryption uses keys of 8 Byte. 
 *   * 3DES and AES encryption uses keys of 16 Byte. 
 *   * 3K3DES encryption uses keys of 24 Byte.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **MasterKeyType** (in) These bits must only be set if the card's Master Key is changed. They specify the type of the new card's Master Key.
 *   - **IsKeySet** (in) Only needed for Desfire EV2 with multiple Keysets. If _true_ ,the reader executes the Desfire "ChangeKeyEV2" command instead of the Desfire "ChangeKey" command.
 *   - **IsAesKey** (in) Has to be set if the new key is an AES key.
 *   - **IsVersion** (in) Has to be set if the _NewKeyVersion_ parameter is present.
 *   - **IsChangeKey** (in) Has to be set if the key used to authenticate the card is the key that needs to be changed (as specified in _KeyNo_).   In this case, the parameter _OldKey_ has to be omitted.
 *   - **KeyNo** (in) Number of key (0-13) to modify. Has to be 0 if the application Master Key is changed.
 *   - **KeyVersion** (in) Version of the new key.   Remarks:     * If this value is not available (i.e. if _IsVersion_ is not set), 0 will be assumed as _NewKeyVersion_.
 *   - **NewKey** (in) New key (16 bytes).
 *   - **NewKey_len** (in) Length of **NewKey** (in bytes).
 *   - **OldKey** (in) Current key (16 bytes).
 *   - **OldKey_len** (in) Length of **OldKey** (in bytes).
 *   - **KeySet** (in) specifies KeySet needed for multiple keysets (EV2 extension).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_ChangeExtKey(brp_protocol protocol, brp_Desfire_ChangeExtKey_MasterKeyType _input_MasterKeyType, bool _input_IsKeySet, bool _input_IsAesKey, bool _input_IsVersion, bool _input_IsChangeKey, unsigned _input_KeyNo, unsigned _input_KeyVersion, brp_buf _input_NewKey, size_t _input_NewKey_len, brp_buf _input_OldKey, size_t _input_OldKey_len, unsigned _input_KeySet);
#else
brp_errcode brp_Desfire_ChangeExtKey(brp_Desfire_ChangeExtKey_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool IsKeySet;
	bool IsMasterKey;
	bool IsChangeKey;
	unsigned KeyNr;
	brp_Desfire_ChangeKey_NewKeyDivMode NewKeyDivMode;
	bool NewKeyHasDivData;
	bool NewKeyHasExtIdx;
	unsigned NewKeyIdx;
	brp_Desfire_ChangeKey_CurKeyDivMode CurKeyDivMode;
	bool CurKeyHasDivData;
	bool CurKeyHasExtIdx;
	unsigned CurKeyIdx;
	brp_buf NewKeyDivData;
	size_t NewKeyDivData_len;
	brp_buf CurKeyDivData;
	size_t CurKeyDivData_len;
	unsigned NewKeyExtIdx;
	unsigned CurKeyExtIdx;
	unsigned KeySet;
} brp_Desfire_ChangeKey_t;
/**
 * Modifies a DESFire card key defined in the SAM or crypto memory.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **IsKeySet** (in) Only needed for Desfire EV2 with multiple Keysets. If _true_ ,the reader executes the Desfire "ChangeKeyEV2" command instead of the Desfire "ChangeKey" command.
 *   - **IsMasterKey** (in) Has to be set if the key to change is the PICC Master Key.
 *   - **IsChangeKey** (in) Has to be set if the key used to authenticate the card is the key that needs to be changed (as specified in _KeyNo_).   In this case, the parameter _CurKeyIdx_ has to be omitted.
 *   - **KeyNr** (in) Number of card key (0-13) to change.
 *   - **NewKeyDivMode** (in) Specifies diversification algorithm.
 *   - **NewKeyHasDivData** (in) Activates key diversification according to NXP AN10922.
 *   - **NewKeyHasExtIdx** (in) Activates key memory expansion.
 *   - **NewKeyIdx** (in) Index of key in the reader's SAM or crypto memory (configuration range 0x00-0xBF).
 *   - **CurKeyDivMode** (in) Specifies diversification algorithm.
 *   - **CurKeyHasDivData** (in) Activates key diversification according to NXP AN10922.
 *   - **CurKeyHasExtIdx** (in) Activates key memory expansion.
 *   - **CurKeyIdx** (in) Index of key in the reader's SAM or crypto memory (configuration range 0x00-0xBF).
 *   - **NewKeyDivData** (in) Diversification data of the new key.
 *   - **NewKeyDivData_len** (in) Length of **NewKeyDivData** (in bytes).
 *   - **CurKeyDivData** (in) Diversification data of the current key.
 *   - **CurKeyDivData_len** (in) Length of **CurKeyDivData** (in bytes).
 *   - **NewKeyExtIdx** (in) Crypto Memory Index (SAM or CryptoMemory) of new key     * SAM: Key version (0..0xFF)    * Crypto Memory: Page (0..15)
 *   - **CurKeyExtIdx** (in) Crypto Memory Index (SAM or CryptoMemory) of current key     * SAM: Key version (0..0xFF)    * Crypto Memory: Page (0..15)
 *   - **KeySet** (in) specifies a KeySet (needed for multiple keysets - EV2 extension).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_ChangeKey(brp_protocol protocol, bool _input_IsKeySet, bool _input_IsMasterKey, bool _input_IsChangeKey, unsigned _input_KeyNr, brp_Desfire_ChangeKey_NewKeyDivMode _input_NewKeyDivMode, bool _input_NewKeyHasDivData, bool _input_NewKeyHasExtIdx, unsigned _input_NewKeyIdx, brp_Desfire_ChangeKey_CurKeyDivMode _input_CurKeyDivMode, bool _input_CurKeyHasDivData, bool _input_CurKeyHasExtIdx, unsigned _input_CurKeyIdx, brp_buf _input_NewKeyDivData, size_t _input_NewKeyDivData_len, brp_buf _input_CurKeyDivData, size_t _input_CurKeyDivData_len, unsigned _input_NewKeyExtIdx, unsigned _input_CurKeyExtIdx, unsigned _input_KeySet);
#else
brp_errcode brp_Desfire_ChangeKey(brp_Desfire_ChangeKey_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Desfire_SetFraming_CommMode CommMode;
} brp_Desfire_SetFraming_t;
/**
 * This command switches the DESFire communication protocol mode to use (std, iso_wrapping). Please refer to the [DESFire specification](http://www.nxp.com/products/identification-and-security/smart-card-ics/mifare-ics/mifare-desfire:MC_53450) for more information.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CommMode** (in) Defines 14443-4 communication mode to DESFire card.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_SetFraming(brp_protocol protocol, brp_Desfire_SetFraming_CommMode _input_CommMode);
#else
brp_errcode brp_Desfire_SetFraming(brp_Desfire_SetFraming_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Desfire_ResetAuthentication_t;
/**
 * This command resets the reader's authentication state until the next call of the Desfire.Authenticate or Desfire.AuthExtKey commands. All following DESFire commands will be sent and received in plain text without MAC. 
 * 
 * It is not possible to run the Desfire.ExecCommand with _CryptoMode_ set to any other value than PLAIN after the execution of this command, until the card is reauthenticated.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_ResetAuthentication(brp_protocol protocol);
#else
brp_errcode brp_Desfire_ResetAuthentication(brp_Desfire_ResetAuthentication_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned AppId;
	brp_buf AppParams;
	size_t AppParams_len;
	brp_buf EncryptedDefaultDamKey;
	size_t EncryptedDefaultDamKey_len;
	brp_buf DamMacKey;
	size_t DamMacKey_len;
} brp_Desfire_CreateDam_t;
/**
 * This command creates a delegated application
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **AppId** (in) ID of application to select - range from 0x00000001 to 0x00FFFFFF.
 *   - **AppParams** (in) Paramters for the delegated application
 *   - **AppParams_len** (in) Length of **AppParams** (in bytes).
 *   - **EncryptedDefaultDamKey** (in) Encrypted default DAM key (usually provided by the card issuer)
 *   - **EncryptedDefaultDamKey_len** (in) Length of **EncryptedDefaultDamKey** (in bytes).
 *   - **DamMacKey** (in) Mac for DAM creation (usually provided by the card issuer)
 *   - **DamMacKey_len** (in) Length of **DamMacKey** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_CreateDam(brp_protocol protocol, unsigned _input_AppId, brp_buf _input_AppParams, size_t _input_AppParams_len, brp_buf _input_EncryptedDefaultDamKey, size_t _input_EncryptedDefaultDamKey_len, brp_buf _input_DamMacKey, size_t _input_DamMacKey_len);
#else
brp_errcode brp_Desfire_CreateDam(brp_Desfire_CreateDam_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* Signature;
	size_t* Signature_len;
	brp_mempool *mempool;
} brp_Desfire_GetOriginalitySignature_t;
/**
 * This command returns the NXP originality signature of a desfire card.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Signature** (out) Card signature.
 *   - **Signature_len** (out) Length of **Signature** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_GetOriginalitySignature(brp_protocol protocol, brp_buf* Signature, size_t* Signature_len, brp_mempool *mempool);
#else
brp_errcode brp_Desfire_GetOriginalitySignature(brp_Desfire_GetOriginalitySignature_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool ForceVcsAuthentication;
	bool UseExtVcSelectKeys;
	unsigned DiversifyMacKey;
	bool DiversifyEncKey;
	bool UseVcSelectKeys;
	brp_buf IID;
	size_t IID_len;
	unsigned EncKeyIdx;
	unsigned MacKeyIdx;
	brp_buf DivData;
	size_t DivData_len;
	brp_buf EncKey;
	size_t EncKey_len;
	brp_buf MacKey;
	size_t MacKey_len;
	unsigned* FciType;
	brp_buf* Fci;
	size_t* Fci_len;
	brp_mempool *mempool;
} brp_Desfire_VirtualCardSelect_t;
/**
 * This command selects a virtual card
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ForceVcsAuthentication** (in) Forces authentication to a virtual card. A card without encryption returns Desfire.VcsAndProxCheckError
 *   - **UseExtVcSelectKeys** (in) Authenticates to a virtual card. A MAC and a encryption key has to be specified. Use (external) Virtual Card keys given as command parameter.
 *   - **DiversifyMacKey** (in) Diversifies VC Mac key.   Remarks for use of divinput:   VC-UID is obtained by decryption of the card response. If VC-UID is concatenated with divinput the input wil be limited to 31 bytes.
 *   - **DiversifyEncKey** (in) Diversifies VC Encryption key
 *   - **UseVcSelectKeys** (in) Authenticates to a virtual card. A MAC and a encryption key has to be specified. Use Keys stored in CryptoMemory or SAM.
 *   - **IID** (in) Virtual Card Identifier.
 *   - **IID_len** (in) Length of **IID** (in bytes).
 *   - **EncKeyIdx** (in) Crypto Memory Index (SAM or CryptoMemory) of virtual card select key     * SAM: MSByte: Key version / LSByte: KeyIdx    * Crypto Memory: MSByte: Page (0..15) / LSByte: KeyIdx (0x80-0xBF)
 *   - **MacKeyIdx** (in) Crypto Memory Index (SAM or CryptoMemory) of MAC key     * SAM: MSByte: Key version / LSByte: KeyIdx    * Crypto Memory: MSByte: Page (0..15) / LSByte: KeyIdx (0x80-0xBF)
 *   - **DivData** (in) Key diversification according to NXP AN10922.
 *   - **DivData_len** (in) Length of **DivData** (in bytes).
 *   - **EncKey** (in) VC encryption key
 *   - **EncKey_len** (in) Length of **EncKey** (in bytes).
 *   - **MacKey** (in) VC MAC key
 *   - **MacKey_len** (in) Length of **MacKey** (in bytes).
 *   - **FciType** (out) 0: raw data 1: uid_len(1) and card type(1) 2: uid_len(1), card type(1) and memory size(1)
 *   - **Fci** (out) File control information
 *   - **Fci_len** (out) Length of **Fci** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_VirtualCardSelect(brp_protocol protocol, bool _input_ForceVcsAuthentication, bool _input_UseExtVcSelectKeys, unsigned _input_DiversifyMacKey, bool _input_DiversifyEncKey, bool _input_UseVcSelectKeys, brp_buf _input_IID, size_t _input_IID_len, unsigned _input_EncKeyIdx, unsigned _input_MacKeyIdx, brp_buf _input_DivData, size_t _input_DivData_len, brp_buf _input_EncKey, size_t _input_EncKey_len, brp_buf _input_MacKey, size_t _input_MacKey_len, unsigned* FciType, brp_buf* Fci, size_t* Fci_len, brp_mempool *mempool);
#else
brp_errcode brp_Desfire_VirtualCardSelect(brp_Desfire_VirtualCardSelect_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned M;
	bool UseExtProxKey;
	bool DiversifyProxKey;
	bool UseProxKey;
	unsigned ProxKeyIdx;
	brp_buf DivData;
	size_t DivData_len;
	brp_buf ProxKey;
	size_t ProxKey_len;
} brp_Desfire_ProxCheck_t;
/**
 * This command executes a proximity check of the card
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **M** (in) Number of random bytes which are send within one procimity check round.
 *   - **UseExtProxKey** (in) Use (external) Proximity key given as command parameter.   If the card is already authenticated (Card Authentication), do not activate this option.
 *   - **DiversifyProxKey** (in) Key diversification of the proximity key defined in Crypto Memory or SAM will be done according to NXP AN10922.
 *   - **UseProxKey** (in) Proximity key is defined in Crypto Memory or SAM.   If the card is already authenticated (VC Selection or Card Authentication), do not activate this option.
 *   - **ProxKeyIdx** (in) Crypto Memory Index (SAM or CryptoMemory) of proximity check key     * SAM: MSByte: Key version / LSByte: KeyIdx    * Crypto Memory: MSByte: Page (0..15) / LSByte: KeyIdx (0x80-0xBF)
 *   - **DivData** (in) Key diversification according to NXP AN10922.
 *   - **DivData_len** (in) Length of **DivData** (in bytes).
 *   - **ProxKey** (in) Proximity check key
 *   - **ProxKey_len** (in) Length of **ProxKey** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_ProxCheck(brp_protocol protocol, unsigned _input_M, bool _input_UseExtProxKey, bool _input_DiversifyProxKey, bool _input_UseProxKey, unsigned _input_ProxKeyIdx, brp_buf _input_DivData, size_t _input_DivData_len, brp_buf _input_ProxKey, size_t _input_ProxKey_len);
#else
brp_errcode brp_Desfire_ProxCheck(brp_Desfire_ProxCheck_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Desfire_GetDfNames_AppNr_Entry** AppNr;
	size_t* AppNr_len;
	brp_mempool *mempool;
} brp_Desfire_GetDfNames_t;
/**
 * This command returns the application identifiers together with file IDs and (optionally) DF names of all applications with ISO7816-4 support.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **AppNr** (out) 
 *   - **AppNr_len** (out) Number of elements in **AppNr**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_GetDfNames(brp_protocol protocol, brp_Desfire_GetDfNames_AppNr_Entry** AppNr, size_t* AppNr_len, brp_mempool *mempool);
#else
brp_errcode brp_Desfire_GetDfNames(brp_Desfire_GetDfNames_t params);
#endif
#endif
/**
 * @}
 */