/**
 * @file
 * With this command group, you can access MIFARE cards in low-level mode. 
 * 
 * Whenever a card enters the HF field, it will be in _idle state_. From the idle state, a card switches to the _requested state_ as soon as the Mif.Request command is executed. Cards in requested state participate in the anti-collision sequence, controlled by the Mif.Anticoll command, resulting in an unambiguous serial number belonging to one of the cards in the HF field. The card with this serial number may now be selected with the Mif.Select command. All other cards will fall back to idle state again and wait for the next call of the Mif.Request command. The selected card, however, changes from requested state to _selected state_. 
 * 
 * **The Mif.Anticoll and Mif.Select commands can only process serial numbers with a length of 4 bytes. Since 2010, however, MIFARE cards with a 7-byte serial number are available. Please use the ISO 14443-3 (Type A) command group to select and process cards with 7-byte serial numbers.**
 * 
 * When a card is in selected state, communication with the card is possible. Nevertheless, it is necessary to be authenticated before a sector of the card can be accessed. Authentication can be performed either with the Mif.AuthE2 command or with the Mif.AuthUser command. Both commands send a key to the currently selected card along with information regarding whether this key should be compared to key A or key B on the card. If the given key matches the corresponding sector's key (either key A or key B, as specified in the command's parameters), then access according to the access conditions of the desired sector will be granted. 
 * 
 * Finally, a card that is in select state can be set to _halt state_. A card in halt state will not respond to any command unless a specially parameterized Mif.Request command is called, or when it leaves and then re-enters the HF field of the reader's antenna. The halt state is helpful when it is necessary to deal with multiple cards present in the reader's antenna HF field. 
 * 
 * The Mif.Read and Mif.Write commands can be use to read/write data from/to a certain block. Additionally, a data sector may be turned into a special _value sector_ (also called _value block_), which is initialized with a specific starting value and can then only be changed by means of _increment_ and _decrement_ operations using the _ChangeValue_ or _ChangeValueBackup_ commands. Value sectors are very useful in some scenarios, such as for cash-based applications. To create a value sector, it is simply required to write specially formatted data to it: 
 * 
 *   * The first 4 bytes (bytes 0-3) represent the initially stored value. 
 *   * The following 4 bytes (bytes 4-7) have to be the _two's complement_ of the first 4 bytes. 
 *   * The next 4 bytes (bytes 8-11) are a copy of the first 4 bytes. 
 *   * The last 4 bytes (bytes 12-15) contain the 1-byte address of a block which can be used for backup management. This address is stored on both byte 12 and byte 14, while its two's complement is stored on both byte 13 and byte 15. These 4 bytes are not affected by calls of the Mif.ChangeValue and Mif.ChangeValueBackup commands. 
 * 
 * 
 * 
 * Each increment and decrement operation has to be followed by a _transfer_ operation, using the Mif.TransferBlock command, in order to make the increment/decrement persistent. This feature guarantees that no data will be lost during a recalculation of the value on the card.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_MIF_H__
#define __BRP_BALTECH_SDK_CMDS_MIF_H__
#include "../typedefs.h"
/**
 * There's no card in the HF field, or the card doesn't respond.
 */
#define BRP_Mif_ErrNoTag BRP_ERR_STATUS(0x1000, 0x01)
#ifdef BALTECH_SDK_INTERNAL
/**
 * The response frame is invalid, e.g. it may contain an invalid CRC checksum. Please rerun the command.
 */
#define BRP_Mif_ErrCrc BRP_ERR_STATUS(0x1000, 0x02)
#endif  // BALTECH_SDK_INTERNAL
/**
 * Card authentication has failed.
 */
#define BRP_Mif_ErrAuth BRP_ERR_STATUS(0x1000, 0x04)
/**
 * Legacy error code: The parity bits don't match the transmitted data. Authentication has been lost. Please reauthenticate and rerun the commands.
 */
#define BRP_Mif_ErrParity BRP_ERR_STATUS(0x1000, 0x05)
/**
 * The card behaves in an unspecified way. Please rerun the command or reselect the card.
 */
#define BRP_Mif_ErrCode BRP_ERR_STATUS(0x1000, 0x06)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Legacy error code: The serial number is wrong.
 */
#define BRP_Mif_ErrSnr BRP_ERR_STATUS(0x1000, 0x08)
#endif  // BALTECH_SDK_INTERNAL
/**
 * The key in the SAM/crypto memory is invalid or missing.
 */
#define BRP_Mif_ErrKey BRP_ERR_STATUS(0x1000, 0x09)
/**
 * Card authentication has failed. The current configuration/state doesn't allow the requested command.
 */
#define BRP_Mif_ErrNotauth BRP_ERR_STATUS(0x1000, 0x0A)
/**
 * Legacy error code: HF data transition error. The number of received bits is invalid.
 */
#define BRP_Mif_ErrBitcount BRP_ERR_STATUS(0x1000, 0x0B)
/**
 * Legacy error code: HF data transition error. The number of received bytes is invalid.
 */
#define BRP_Mif_ErrBytecount BRP_ERR_STATUS(0x1000, 0x0C)
/**
 * The proximity check has timed out. Please reselect the card.
 */
#define BRP_Mif_VcsAndProxCheckError BRP_ERR_STATUS(0x1000, 0x0E)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Writing to the card has failed. Please rerun the command or check the access conditions.
 */
#define BRP_Mif_ErrWrite BRP_ERR_STATUS(0x1000, 0x0F)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Legacy error code: Increment couldn't be performed.
 */
#define BRP_Mif_ErrInc BRP_ERR_STATUS(0x1000, 0x10)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Legacy error code: Decrement couldn't be performed.
 */
#define BRP_Mif_ErrDecr BRP_ERR_STATUS(0x1000, 0x11)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Reading data from the card has failed. Please rerun the command or check the access conditions.
 */
#define BRP_Mif_ErrRead BRP_ERR_STATUS(0x1000, 0x12)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Legacy error code: An overflow occurred during decrement or increment.
 */
#define BRP_Mif_ErrOvfl BRP_ERR_STATUS(0x1000, 0x13)
#endif  // BALTECH_SDK_INTERNAL
/**
 * The response frame is invalid, e.g. it may contain an invalid number of bits. Please rerun the command.
 */
#define BRP_Mif_ErrFraming BRP_ERR_STATUS(0x1000, 0x15)
#ifdef BALTECH_SDK_INTERNAL
/**
 * The command has been aborted because the HF interface has been requested by another task or command. Please reselect the card. 
 * 
 * **This error only occurs when you combine VHL and low-level commands. We highly recommend you avoid that combination as these 2 command sets will interfere with each other's card states.**
 */
#define BRP_Mif_ErrBreak BRP_ERR_STATUS(0x1000, 0x16)
#endif  // BALTECH_SDK_INTERNAL
/**
 * The specified command or parameters are unknown.
 */
#define BRP_Mif_ErrCmd BRP_ERR_STATUS(0x1000, 0x17)
/**
 * An error occurred in the anti-collision sequence. Please reselect the card.
 */
#define BRP_Mif_ErrColl BRP_ERR_STATUS(0x1000, 0x18)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Communication with the reader's HF interface has failed. Please reset the HF interface with Sys.HFReset and check the reader status with Sys.GetBootStatus.
 */
#define BRP_Mif_ErrReaderChipCommunication BRP_ERR_STATUS(0x1000, 0x1A)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * This command isn't supported by the reader firmware.
 */
#define BRP_Mif_ErrFirmwareNotSupported BRP_ERR_STATUS(0x1000, 0x1D)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * A value operation, e.g. increment or decrement, has failed. This may have several reasons, e.g. an invalid value format, or the value to manipulate doesn't exist on the card.
 */
#define BRP_Mif_ErrVal BRP_ERR_STATUS(0x1000, 0x1E)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Secure messaging error: The CRC or MAC checksum doesn't match the transmitted data. Authentication has been lost. Please reauthenticate and rerun the commands, or check the security conditions.
 */
#define BRP_Mif_ErrIntegrity BRP_ERR_STATUS(0x1000, 0x1F)
#endif  // BALTECH_SDK_INTERNAL
/**
 * Card error as per MIFARE specification: Condition of use not satisfied.
 */
#define BRP_Mif_CondNotvalid BRP_ERR_STATUS(0x1000, 0x20)
#ifdef BALTECH_SDK_INTERNAL
/**
 * This command isn't supported by the reader hardware, i.e. by the SAM or reader chip.
 */
#define BRP_Mif_ErrHwNotSupported BRP_ERR_STATUS(0x1000, 0x21)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Unlocking/authenticating with the SAM has failed. Please check the SamAVx configuration values.
 */
#define BRP_Mif_ErrSamUnlock BRP_ERR_STATUS(0x1000, 0x22)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Communication with the SAM has failed. This may have several reasons, e.g. the wrong SAM type or a failure to activate the SAM. Please check the SAM status and reset the reader with Sys.Reset.
 */
#define BRP_Mif_ErrSamCommunication BRP_ERR_STATUS(0x1000, 0x23)
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned KeyIdx;
	brp_buf Key;
} brp_Mif_LoadKey_t;
/**
 * This command writes a MIFARE Classic key to the reader's secure key memory. The reader can store 32 different keys so the key index must not exceed 31. These keys will be used for the authentication of certain sectors.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **KeyIdx** (in) Key memory index: address in memory at which to store the key.
 *   - **Key** (in) The key itself.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_LoadKey(brp_protocol protocol, unsigned _input_KeyIdx, brp_buf _input_Key);
#else
brp_errcode brp_Mif_LoadKey(brp_Mif_LoadKey_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	bool ReqAll;
	unsigned* ATQA;
} brp_Mif_Request_t;
/**
 * Request labels in the field of the antenna. 
 * 
 * _ATQA_ is a two byte value (MSB first). This value is called _tagtype_ and for MIFARE 1 CSCs, it is expected to be equal to 0x0004. 
 * 
 * **For new applications, the Iso14a.Request command should be used instead.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ReqAll** (in) If set, all cards (even those in halt state) will be requested. Otherwise, only cards in idle state will be requested.
 *   - **ATQA** (out) Answer to request.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_Request(brp_protocol protocol, bool _input_ReqAll, unsigned* ATQA);
#else
brp_errcode brp_Mif_Request(brp_Mif_Request_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned BitCount;
	brp_buf PreSelSer;
	brp_buf* Snr;
	brp_mempool *mempool;
} brp_Mif_Anticoll_t;
/**
 * This command performs an anti-collision sequence. 
 * 
 * A number of bits equal to the _BitCount_ value will be used in _PreSelSer_ for preselection of cards in the HF field of the antenna. This means that only cards with a serial number matching the first _BitCount_ bits of _PreSelSer_ will be taken into consideration. The command returns an unambiguous serial number in the _Snr_ value which may be used for the card selection procedure, using the Mif.Select command. 
 * 
 * **For new applications, the Iso14a.Anticoll command should be used instead.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **BitCount** (in) Number of bits to be considered in _PreSelSer_.
 *   - **PreSelSer** (in) Part of the card's serial number which will be used for preselection of cards. The amount of considered bits is specified by the _BitCount_ value.
 *   - **Snr** (out) Unambiguous serial number of selected label.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_Anticoll(brp_protocol protocol, unsigned _input_BitCount, brp_buf _input_PreSelSer, brp_buf* Snr, brp_mempool *mempool);
#else
brp_errcode brp_Mif_Anticoll(brp_Mif_Anticoll_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf Snr;
	unsigned* SAK;
} brp_Mif_Select_t;
/**
 * This command selects a card with a 4 Byte serial number specified in the _Snr_ parameter. 
 * 
 * **This command is deprecated. For new applications, the Iso14a.Select command should be used instead.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Snr** (in) Serial number of card.
 *   - **SAK** (out) Select Acknowledge (SAK), according to the ISO 14443-3 (Type A) standard.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_Select(brp_protocol protocol, brp_buf _input_Snr, unsigned* SAK);
#else
brp_errcode brp_Mif_Select(brp_Mif_Select_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_Mif_AuthE2_AuthMode AuthMode;
	unsigned Block;
	unsigned KeyIdx;
} brp_Mif_AuthE2_t;
/**
 * This command authenticates a certain sector of a card using a key from the secure EEPROM of the Baltech reader chip. 
 * 
 * Depending on the value of the _AuthMode_ variable, either key A or key B of the sector specified by the _Block_ variable will be compared to the key specified in _KeyIdx_. 
 * 
 * It is only possible to authenticate one sector at a time.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **AuthMode** (in) Authentication Mode.
 *   - **Block** (in) Block to authenticate.
 *   - **KeyIdx** (in) Index of key in EEPROM which shall be used for authentication (range: 0 to 31).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_AuthE2(brp_protocol protocol, brp_Mif_AuthE2_AuthMode _input_AuthMode, unsigned _input_Block, unsigned _input_KeyIdx);
#else
brp_errcode brp_Mif_AuthE2(brp_Mif_AuthE2_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Mif_AuthUser_AuthMode AuthMode;
	unsigned Block;
	brp_buf Key;
} brp_Mif_AuthUser_t;
/**
 * This command authenticates a certain sector of a card using the key specified in the _Key_ variable. 
 * 
 * Depending on the value of the _AuthMode_ variable, either key A or key B of the sector specified by the _Block_ variable will be compared to the key specified in _KeyIdx_. 
 * 
 * It is only possible to authenticate one sector at a time.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **AuthMode** (in) Authentication Mode.
 *   - **Block** (in) Block to authenticate.
 *   - **Key** (in) Key to use for authentication.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_AuthUser(brp_protocol protocol, brp_Mif_AuthUser_AuthMode _input_AuthMode, unsigned _input_Block, brp_buf _input_Key);
#else
brp_errcode brp_Mif_AuthUser(brp_Mif_AuthUser_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Block;
	brp_buf* BlockData;
	brp_mempool *mempool;
} brp_Mif_Read_t;
/**
 * This command reads data from a specified block of the currently selected card, providing authentication has been performed beforehand.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Block** (in) Block to read.
 *   - **BlockData** (out) Data of selected block.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_Read(brp_protocol protocol, unsigned _input_Block, brp_buf* BlockData, brp_mempool *mempool);
#else
brp_errcode brp_Mif_Read(brp_Mif_Read_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Block;
	brp_buf BlockData;
} brp_Mif_Write_t;
/**
 * This command write data to a specified block of the currently selected card, providing authentication has been performed beforehand.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Block** (in) Block to write.
 *   - **BlockData** (in) Data of selected block.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_Write(brp_protocol protocol, unsigned _input_Block, brp_buf _input_BlockData);
#else
brp_errcode brp_Mif_Write(brp_Mif_Write_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Mif_ChangeValue_Mode Mode;
	unsigned Block;
	unsigned Value;
} brp_Mif_ChangeValue_t;
/**
 * This command uses the value block specified by the _Block_ parameter and performs an operation given by the _Mode_ parameter. The result is stored in the card's Transfer Buffer. 
 * 
 * _Mode_ = 1 increments the _value_ , _Mode_ = 0 decrements the value, _Mode_ = 0x02 simply transfers the value to the Transfer Buffer - the _Value_ parameter is ignored. 
 * 
 * In order to persistently store the calculated value on the card, a _transfer_ operation, using the Mif.TransferBlock command, has to be performed directly after the completion of this command. 
 * 
 * This command can be used for MIFARE Classic cards and only works on value sectors. 
 * 
 * **This command is not supported by LEGIC readers.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Mode** (in) Access mode.
 *   - **Block** (in) Sector to load data from (only value sectors are supported).
 *   - **Value** (in) Value to add/subtract. This parameter is ignored when _Mode_ = 0x02.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ChangeValue(brp_protocol protocol, brp_Mif_ChangeValue_Mode _input_Mode, unsigned _input_Block, unsigned _input_Value);
#else
brp_errcode brp_Mif_ChangeValue(brp_Mif_ChangeValue_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Mif_ChangeValueBackup_Mode Mode;
	unsigned Block;
	unsigned Value;
} brp_Mif_ChangeValueBackup_t;
/**
 * This command is identical to Mif.ChangeValue, but can only be used for MIFARE cards which support automatic transfer, such as _Pro_ or _Light_ MIFARE variants. 
 * 
 * **This command is not supported by LEGIC readers.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Mode** (in) Access mode.
 *   - **Block** (in) Block to load data from (only value blocks are supported).
 *   - **Value** (in) Value to add/subtract. This parameter is ignored when _Mode_ = 0x02.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ChangeValueBackup(brp_protocol protocol, brp_Mif_ChangeValueBackup_Mode _input_Mode, unsigned _input_Block, unsigned _input_Value);
#else
brp_errcode brp_Mif_ChangeValueBackup(brp_Mif_ChangeValueBackup_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Block;
} brp_Mif_TransferBlock_t;
/**
 * This command transfers data from the card's internal Transfer Buffer to a specified block. 
 * 
 * This command needs to be called directly after any operation on the internal data register performed by Mif.ChangeValue or Mif.ChangeValueBackup in order to make the results of these commands persistent. 
 * 
 * **This command is not supported by LEGIC readers.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Block** (in) Sector to transfer the data to.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_TransferBlock(brp_protocol protocol, unsigned _input_Block);
#else
brp_errcode brp_Mif_TransferBlock(brp_Mif_TransferBlock_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
} brp_Mif_Halt_t;
/**
 * Switch card to halt state. The card has to be selected before it may be switched to halt state.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_Halt(brp_protocol protocol);
#else
brp_errcode brp_Mif_Halt(brp_Mif_Halt_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_Mif_AuthE2Extended_AuthLevel AuthLevel;
	bool KeyHasExtIdx;
	bool EV1Mode;
	bool IsKeyB;
	unsigned Block;
	unsigned KeyIdx;
	unsigned KeyExtIdx;
	brp_buf DivData;
	size_t DivData_len;
} brp_Mif_AuthE2Extended_t;
/**
 * This command is identical to the Mif.AuthE2 command with the exception that it supports stronger authentication methods (MIFARE and AES), supported by MIFARE Pro cards. 
 * 
 * **MIFARE Plus SL2 support was deprecated and removed in firmware 2.12.00. It is unsupported in this and all later versions.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **AuthLevel** (in) Desired authentication level.
 *   - **KeyHasExtIdx** (in) Set this flag if extended crypto memory is used (using KeyExtIdx parameter).
 *   - **EV1Mode** (in) Switches to EV1 secure messaging. (Only supported by MFP EV1 cards)
 *   - **IsKeyB** (in) Key B is used when this flag is set, whereas Key A is used when this flag is cleared.
 *   - **Block** (in) Block/Key address of MIFARE Pro card.
 *   - **KeyIdx** (in) Crypto Memory Index (SAM or CryptoMemory) of MIFARE key     * SAM: 0-7F    * CrMem: 80-BF
 *   - **KeyExtIdx** (in) Crypto Memory Index (SAM or CryptoMemory) of authentication key     * SAM: SAM: Key version (0..0xFF)    * Crypto Memory: Page (0..15)
 *   - **DivData** (in) Key diversification according to NXP AN10922 will be done if diversification data bytes are specified.
 *   - **DivData_len** (in) Length of **DivData** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_AuthE2Extended(brp_protocol protocol, brp_Mif_AuthE2Extended_AuthLevel _input_AuthLevel, bool _input_KeyHasExtIdx, bool _input_EV1Mode, bool _input_IsKeyB, unsigned _input_Block, unsigned _input_KeyIdx, unsigned _input_KeyExtIdx, brp_buf _input_DivData, size_t _input_DivData_len);
#else
brp_errcode brp_Mif_AuthE2Extended(brp_Mif_AuthE2Extended_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Mif_AuthUserExtended_AuthLevel AuthLevel;
	bool EV1Mode;
	bool KeyB;
	unsigned Block;
	brp_buf Key;
	size_t Key_len;
} brp_Mif_AuthUserExtended_t;
/**
 * This command is identical to the Mif.AuthUser command with the exception that it supports stronger authentication methods (MIFARE and AES), supported by MIFARE Pro cards. 
 * 
 * **MIFARE Plus SL2 support was deprecated and removed in firmware 2.12.00. It is unsupported in this and all later versions.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **AuthLevel** (in) Desired authentication level.
 *   - **EV1Mode** (in) Switches to EV1 secure messaging. (Only supported by MFP EV1 cards)
 *   - **KeyB** (in) Key B is used when this flag is set, whereas Key A is used when this flag is cleared.
 *   - **Block** (in) Block/Key address of MIFARE Pro card.
 *   - **Key** (in) Key to use for authentication.
 *   - **Key_len** (in) Length of **Key** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_AuthUserExtended(brp_protocol protocol, brp_Mif_AuthUserExtended_AuthLevel _input_AuthLevel, bool _input_EV1Mode, bool _input_KeyB, unsigned _input_Block, brp_buf _input_Key, size_t _input_Key_len);
#else
brp_errcode brp_Mif_AuthUserExtended(brp_Mif_AuthUserExtended_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Mif_ResetAuth_t;
/**
 * This command resets the reader's authentication state (used for MIFARE Pro specific Read/Write counters.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ResetAuth(brp_protocol protocol);
#else
brp_errcode brp_Mif_ResetAuth(brp_Mif_ResetAuth_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool NoMacOnCmd;
	bool PlainData;
	bool NoMacOnResp;
	unsigned Block;
	unsigned BlockNr;
	brp_buf* BlockData;
	size_t* BlockData_len;
	brp_mempool *mempool;
} brp_Mif_ReadSL3_t;
/**
 * This command reads blocks from an SL3-authenticated MIFARE Pro card.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **NoMacOnCmd** (in) 
 *   - **PlainData** (in) 
 *   - **NoMacOnResp** (in) 
 *   - **Block** (in) Block number where reading starts.
 *   - **BlockNr** (in) Number of blocks to read.
 *   - **BlockData** (out) Read data blocks.
 *   - **BlockData_len** (out) Length of **BlockData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ReadSL3(brp_protocol protocol, bool _input_NoMacOnCmd, bool _input_PlainData, bool _input_NoMacOnResp, unsigned _input_Block, unsigned _input_BlockNr, brp_buf* BlockData, size_t* BlockData_len, brp_mempool *mempool);
#else
brp_errcode brp_Mif_ReadSL3(brp_Mif_ReadSL3_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool PlainData;
	bool NoMacOnResp;
	unsigned Block;
	brp_buf BlockData;
	size_t BlockData_len;
} brp_Mif_WriteSL3_t;
/**
 * This command writes blocks to an SL3-authenticated MIFARE Pro card.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PlainData** (in) 
 *   - **NoMacOnResp** (in) 
 *   - **Block** (in) Block number where writing starts.
 *   - **BlockData** (in) Data blocks to write.
 *   - **BlockData_len** (in) Length of **BlockData** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_WriteSL3(brp_protocol protocol, bool _input_PlainData, bool _input_NoMacOnResp, unsigned _input_Block, brp_buf _input_BlockData, size_t _input_BlockData_len);
#else
brp_errcode brp_Mif_WriteSL3(brp_Mif_WriteSL3_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool KeyHasExtIdx;
	bool NoMacOnResp;
	unsigned Block;
	unsigned KeyIdx;
	unsigned KeyExtIdx;
	brp_buf DivData;
	size_t DivData_len;
} brp_Mif_ChangeAESKey_t;
/**
 * This command changes an AES key on a MIFARE Plus card.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **KeyHasExtIdx** (in) Set this flag if extended crypto memory is used (using KeyExtIdx parameter).
 *   - **NoMacOnResp** (in) 
 *   - **Block** (in) Key block number.
 *   - **KeyIdx** (in) Crypto Memory Index of secure reader chip key     * SAM: 0-7F    * CrMem: 80-FC
 *   - **KeyExtIdx** (in) Crypto Memory Index (SAM or CryptoMemory) of authentication key     * SAM: SAM: Key version (0..0xFF)    * Crypto Memory: Page (0..15)
 *   - **DivData** (in) Key diversification according to NXP AN10922 will be done if diversification data bytes are specified.
 *   - **DivData_len** (in) Length of **DivData** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ChangeAESKey(brp_protocol protocol, bool _input_KeyHasExtIdx, bool _input_NoMacOnResp, unsigned _input_Block, unsigned _input_KeyIdx, unsigned _input_KeyExtIdx, brp_buf _input_DivData, size_t _input_DivData_len);
#else
brp_errcode brp_Mif_ChangeAESKey(brp_Mif_ChangeAESKey_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool NoMacOnResp;
	brp_Mif_ValueSL3_Cmd Cmd;
	unsigned Block;
	unsigned DestBlock;
	unsigned Value;
	brp_buf* TMCounterTMValue;
	size_t* TMCounterTMValue_len;
	brp_mempool *mempool;
} brp_Mif_ValueSL3_t;
/**
 * This command performs an operation on a value block. 
 * 
 * It can be used for MIFARE Plus cards in security level 3.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **NoMacOnResp** (in) 
 *   - **Cmd** (in) Selects a value operation.
 *   - **Block** (in) Value block number.
 *   - **DestBlock** (in) Destination block number for combined IncrementTransfer or IncrementTransfer command.
 *   - **Value** (in) Value for Increment, Decrement, IncrementTransfer, IncrementTransfer.
 *   - **TMCounterTMValue** (out) Present if targeting a TMProtectedBlock which is configured to return TMC (4 bytes) and TMV (8 bytes)
 *   - **TMCounterTMValue_len** (out) Length of **TMCounterTMValue** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ValueSL3(brp_protocol protocol, bool _input_NoMacOnResp, brp_Mif_ValueSL3_Cmd _input_Cmd, unsigned _input_Block, unsigned _input_DestBlock, unsigned _input_Value, brp_buf* TMCounterTMValue, size_t* TMCounterTMValue_len, brp_mempool *mempool);
#else
brp_errcode brp_Mif_ValueSL3(brp_Mif_ValueSL3_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned M;
	bool DisableIsoWrapping;
	bool UseExtProxKey;
	bool DiversifyProxKey;
	bool UseProxKey;
	unsigned ProxKeyIdx;
	brp_buf DivData;
	size_t DivData_len;
	brp_buf ProxKey;
	size_t ProxKey_len;
} brp_Mif_ProxCheck_t;
/**
 * This command performs a proximity check. The key-related parameters are only used if no authentication has been performed before this command is called.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **M** (in) Number of random bytes which are sent within one proximity check round.
 *   - **DisableIsoWrapping** (in) 
 *   - **UseExtProxKey** (in) Use (external) Proximity key given as command parameter.   If the card is already authenticated (VC Selection or Card Authentication), do not activate this option.
 *   - **DiversifyProxKey** (in) Key diversification of the proximity key defined in Crypto Memory or SAM will be done according to NXP AN10922.
 *   - **UseProxKey** (in) Proximity key is defined in Crypto Memory or SAM.   If the card is already authenticated (Card Authentication), do not activate this option.
 *   - **ProxKeyIdx** (in) Crypto Memory Index (SAM or CryptoMemory) of Proximity Check Key     * SAM: MSByte: Key version / LSByte: KeyIdx    * Crypto Memory: MSByte: Page (0..15) / LSByte: KeyIdx (0x80-0xBF)
 *   - **DivData** (in) Key diversification according to NXP AN10922.
 *   - **DivData_len** (in) Length of **DivData** (in bytes).
 *   - **ProxKey** (in) Proximity Check Key
 *   - **ProxKey_len** (in) Length of **ProxKey** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ProxCheck(brp_protocol protocol, unsigned _input_M, bool _input_DisableIsoWrapping, bool _input_UseExtProxKey, bool _input_DiversifyProxKey, bool _input_UseProxKey, unsigned _input_ProxKeyIdx, brp_buf _input_DivData, size_t _input_DivData_len, brp_buf _input_ProxKey, size_t _input_ProxKey_len);
#else
brp_errcode brp_Mif_ProxCheck(brp_Mif_ProxCheck_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* CardVersion;
	size_t* CardVersion_len;
	brp_mempool *mempool;
} brp_Mif_GetCardVersion_t;
/**
 * This command returns HW- / SW- / Production-Information. (only MIFARE+ EV1 and newer)
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CardVersion** (out) Card version information -> HW- / SW- / Prod-Information
 *   - **CardVersion_len** (out) Length of **CardVersion** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_GetCardVersion(brp_protocol protocol, brp_buf* CardVersion, size_t* CardVersion_len, brp_mempool *mempool);
#else
brp_errcode brp_Mif_GetCardVersion(brp_Mif_GetCardVersion_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* NxpSignature;
	size_t* NxpSignature_len;
	brp_mempool *mempool;
} brp_Mif_ReadSig_t;
/**
 * 
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **NxpSignature** (out) NXP Originality Signature
 *   - **NxpSignature_len** (out) Length of **NxpSignature** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ReadSig(brp_protocol protocol, brp_buf* NxpSignature, size_t* NxpSignature_len, brp_mempool *mempool);
#else
brp_errcode brp_Mif_ReadSig(brp_Mif_ReadSig_t params);
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
	brp_Mif_VirtualCardSelect_FciType* FciType;
	brp_buf* Fci;
	size_t* Fci_len;
	brp_mempool *mempool;
} brp_Mif_VirtualCardSelect_t;
/**
 * Command is only supported by MIFARE Plus EV1 cards. Selected in ISO14443-3 mode the VCSupportLastISOL3 command is executed. Selected in ISO14443-4 mode the IsoSelect command is executed If the card answers in the latter case with a Payload (UID does not match or authentication with VCSelection is mandatory) the reader executes an additional ISOExternalAuthentication command
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ForceVcsAuthentication** (in) Forces authentication to a virtual card. A card without encryption returns Mif.VcsAndProxCheckError
 *   - **UseExtVcSelectKeys** (in) Authenticates to a virtual card. A MAC and an encryption key have to be specified. Use (external) Virtual Card keys given as command parameter.
 *   - **DiversifyMacKey** (in) Diversifies VC Mac key.   Remarks for use of divinput:   VC-UID is obtained by decryption of the card response. If VC-UID is concatenated with divinput the input wil be limited to 31 bytes.
 *   - **DiversifyEncKey** (in) Diversifies VC Encryption key
 *   - **UseVcSelectKeys** (in) Authenticates to a virtual card. A MAC and a encryption key has to be specified. Use keys stored in CryptoMemory or SAM.
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
 *   - **FciType** (out) Type of File Control Information returned.
 *   - **Fci** (out) File control information
 *   - **Fci_len** (out) Length of **Fci** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_VirtualCardSelect(brp_protocol protocol, bool _input_ForceVcsAuthentication, bool _input_UseExtVcSelectKeys, unsigned _input_DiversifyMacKey, bool _input_DiversifyEncKey, bool _input_UseVcSelectKeys, brp_buf _input_IID, size_t _input_IID_len, unsigned _input_EncKeyIdx, unsigned _input_MacKeyIdx, brp_buf _input_DivData, size_t _input_DivData_len, brp_buf _input_EncKey, size_t _input_EncKey_len, brp_buf _input_MacKey, size_t _input_MacKey_len, brp_Mif_VirtualCardSelect_FciType* FciType, brp_buf* Fci, size_t* Fci_len, brp_mempool *mempool);
#else
brp_errcode brp_Mif_VirtualCardSelect(brp_Mif_VirtualCardSelect_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool L3SectorSwitch;
	unsigned SectorSwitchKeyIdx;
	brp_buf SectorSwitchKeyDivData;
	size_t SectorSwitchKeyDivData_len;
	brp_Mif_SectorSwitch_SectorSpec_Entry* SectorSpec;
	size_t SectorSpec_len;
	brp_buf SectorKeysDivData;
	size_t SectorKeysDivData_len;
} brp_Mif_SectorSwitch_t;
/**
 * This command performs a sector switch command (only for EV1 cards). Prior the card has to be set in 14443-4 mode, all sectors are addressed with sector Key B.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **L3SectorSwitch** (in) If _true_ , the target level of the sector switch is SL3, else SL1/SL3-Mixed.
 *   - **SectorSwitchKeyIdx** (in) Crypto Memory Index (SAM or CryptoMemory) of L1L3MixSectorSwitchKey or L3SectorSwitchKey     * SAM: MSByte: Key version / LSByte: KeyIdx    * Crypto Memory: MSByte: Page (0..15) / LSByte: KeyIdx (0x80-0xBF)
 *   - **SectorSwitchKeyDivData** (in) If diversification data is specified, key diversification of the SectorSwitchKey will be done according to NXP AN10922.
 *   - **SectorSwitchKeyDivData_len** (in) Length of **SectorSwitchKeyDivData** (in bytes).
 *   - **SectorSpec** (in) 
 *   - **SectorSpec_len** (in) Number of elements in **SectorSpec**.
 *   - **SectorKeysDivData** (in) If diversification data is specified, key diversification of the sector keys will be done according to NXP AN10922.
 *   - **SectorKeysDivData_len** (in) Length of **SectorKeysDivData** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_SectorSwitch(brp_protocol protocol, bool _input_L3SectorSwitch, unsigned _input_SectorSwitchKeyIdx, brp_buf _input_SectorSwitchKeyDivData, size_t _input_SectorSwitchKeyDivData_len, brp_Mif_SectorSwitch_SectorSpec_Entry* _input_SectorSpec, size_t _input_SectorSpec_len, brp_buf _input_SectorKeysDivData, size_t _input_SectorKeysDivData_len);
#else
brp_errcode brp_Mif_SectorSwitch(brp_Mif_SectorSwitch_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Block;
	brp_buf* EncTRI;
	size_t* EncTRI_len;
	brp_mempool *mempool;
} brp_Mif_CommitReaderID_t;
/**
 * This commands commits a reader ID from a card and returns the encrypted TMRI to the host. Authentication must take place before using this command.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Block** (in) Value block number.
 *   - **EncTRI** (out) Encrypted transaction reader ID
 *   - **EncTRI_len** (out) Length of **EncTRI** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_CommitReaderID(brp_protocol protocol, unsigned _input_Block, brp_buf* EncTRI, size_t* EncTRI_len, brp_mempool *mempool);
#else
brp_errcode brp_Mif_CommitReaderID(brp_Mif_CommitReaderID_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Mif_SetFraming_CommMode CommMode;
} brp_Mif_SetFraming_t;
/**
 * This command switches the communication protocol mode for MIFARE Plus EV1 cards.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CommMode** (in) Defines 14443-4 communication mode for MIFARE Plus EV1 cards.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_SetFraming(brp_protocol protocol, brp_Mif_SetFraming_CommMode _input_CommMode);
#else
brp_errcode brp_Mif_SetFraming(brp_Mif_SetFraming_t params);
#endif
#endif
/**
 * @}
 */