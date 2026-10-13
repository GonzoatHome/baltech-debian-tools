/**
 * @file
 * This command group regroups the commands needed for Advanced Encryption Standard (AES)-based protocol encryption, and to access the reader's internal security system. These mechanisms enable to protect the reader-host communication.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_SEC_H__
#define __BRP_BALTECH_SDK_CMDS_SEC_H__
#include "../typedefs.h"
/**
 * Invalid key used for encryption/MACing, MAC address invalid, or decrypted data invalid.
 */
#define BRP_Sec_ErrCrypto BRP_ERR_STATUS(0x0700, 0x01)
/**
 * It is not possible to tunnel this command.
 */
#define BRP_Sec_ErrTunnel BRP_ERR_STATUS(0x0700, 0x02)
typedef struct {
	brp_protocol protocol;
	unsigned SecLevel;
	brp_HostSecurityAccessConditionBits* AcMask;
} brp_Sec_GetAcMask_t;
/**
 * This command retrieves the Access Condition Mask of a specified security level. 
 * 
 * The Access Condition Mask can be set using the command Sec.SetAcMask or by loading a reader configuration file which defines the respective configuration values Device/HostSecurity/AccessConditionMask. 
 * 
 * **In case of security level 0 (plain access) the actual Access Condition Mask that is applied by the reader may deviate from the value which is returned by this command. Refer to Sec.GetCurAcMask .**
 * 
 * **It is _not_ possible to deny the retrieval of the Access Condition Mask via the "Encryption and Authorization" settings in the configuration. This means that this command will never return the ERR_ACCESS_DENIED status code.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SecLevel** (in) Security Level to get the Access Condition Mask from. Must be between 0 and 3. If this value is 0xFF, the Access Condition Mask of the current Security Level will be returned.
 *   - **AcMask** (out) Access Condition Mask of the Security Level specified in the _SecurityLevel_ parameter. --- Every Feature in this list can be disabled by not setting the corresponding bit.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_GetAcMask(brp_protocol protocol, unsigned _input_SecLevel, brp_HostSecurityAccessConditionBits* AcMask);
#else
brp_errcode brp_Sec_GetAcMask(brp_Sec_GetAcMask_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned SecLevel;
	brp_HostSecurityAccessConditionBits AcMask;
} brp_Sec_SetAcMask_t;
/**
 * This command sets the Access Condition Mask of the security level specified in the _SecurityLevel_ parameter to the _AcMask_ value. 
 * 
 * Alternatively Access Condition Masks may also be set via reader configuration, refer to Device/HostSecurity/AccessConditionMask. 
 * 
 * **The Access Condition Mask of security level 3 is by definition 0xFFFFFFFF. It can not be restricted.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SecLevel** (in) Security Level which needs to be modified (must be between 0 and 3). If this value is 0xFF, the Access Condition Mask of the current Security Level will be modified.
 *   - **AcMask** (in) New Access Condition Mask. It is not possible to delete the FactoryReset bit with this bitmask (see Sec.LockReset) --- Every Feature in this list can be disabled by not setting the corresponding bit.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_SetAcMask(brp_protocol protocol, unsigned _input_SecLevel, brp_HostSecurityAccessConditionBits _input_AcMask);
#else
brp_errcode brp_Sec_SetAcMask(brp_Sec_SetAcMask_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool ContinuousIV;
	bool Encrypted;
	bool MACed;
	bool SessionKey;
	unsigned DeriveKey;
	unsigned SecLevel;
	brp_buf Key;
} brp_Sec_SetKey_t;
/**
 * Sets a key and the appropriate Authorization Mode bits for a specified Security Level. 
 * 
 * If one or more of the _SessionKey_ , _MACed_ , _Encrypted_ or _ContinuousIV_ bits are set, it is not possible to authenticate without the corresponding authentication mode setting.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ContinuousIV** (in) If _true_ , encryption/MACing will use Cipher Block Chaining (CBC). In this case, a continuous initial vector (IV) will be used.   If this bit is not set, CBC is not used, i.e. the IV will be reset to all zeros (00 00 ... 00) before every command or response is encrypted/MACed.
 *   - **Encrypted** (in) Requires that commands running in this security level always have to be encrypted.   **This flag cannot be set at the same time as the _MACed_ flag.**
 *   - **MACed** (in) Requires that commands running in this security level always have to be MACed.   **This flag cannot be set at the same time as the _Encrypted_ flag.**
 *   - **SessionKey** (in) Requires a two-phase authentication to be able to enter a security level. This two-phase authentication process needs to be performed using the Sec.AuthPhase1 and Sec.AuthPhase2 commands.
 *   - **DeriveKey** (in) This value is not used and must be 0.   Until firmware v2.14.00, this value referenced the key of the security level, which was used to derive _Key_. Since firmware v2.20.00, this feature is no longer supported.
 *   - **SecLevel** (in) The security level for which the key has to be set.
 *   - **Key** (in) Key/Password for authentication of security level _SecLevel_.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_SetKey(brp_protocol protocol, bool _input_ContinuousIV, bool _input_Encrypted, bool _input_MACed, bool _input_SessionKey, unsigned _input_DeriveKey, unsigned _input_SecLevel, brp_buf _input_Key);
#else
brp_errcode brp_Sec_SetKey(brp_Sec_SetKey_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned SecLevel;
	brp_buf RndA;
	brp_buf* EncRndA;
	brp_buf* RndB;
	bool* ContinuousIV;
	bool* Encrypted;
	bool* MACed;
	bool* SessionKey;
	brp_mempool *mempool;
} brp_Sec_AuthPhase1_t;
/**
 * This command initiates a 2-phase authentication. The 2-phase authentication is required for entering a security level, if its Authorization Mode enforces a session key. 
 * 
 * In the first phase of the 2-phase authentication, the host sends a random number (_RndA_) to the reader. The reader encrypts this number two times, using AES128 encryption, with the key of the Security Level specified in _SecLevel_ , and sends the result back to the host as _EncRndA_. The host then has to check if the reader encrypted the number correctly. If this is the case, the reader returns the OK status code and the Sec.AuthPhase2 command can be called to initiate the second phase of the 2-phase authentication procedure. 
 * 
 * If _EncRndA_ is invalid, the reader is configured with an invalid key, different from the one expected by the host. In this case, an error status code is returned.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SecLevel** (in) The Security Level which needs to be authenticated.
 *   - **RndA** (in) Random number to be encrypted by reader.
 *   - **EncRndA** (out) A version of _RndA_ twice encrypted by the reader using the key of the Security Level specified by _SecLevel_.
 *   - **RndB** (out) A second random number (generated by reader).
 *   - **ContinuousIV** (out) Requires a contionous IV to avoid replay attacks.
 *   - **Encrypted** (out) Requires that commands running in this security level always have to be encrypted.   **This flag cannot be set at the same time as the _MACed_ flag.**
 *   - **MACed** (out) Requires that commands running in this security level always have to be MACed.   **This flag cannot be set at the same time as the _Encrypted_ flag.**
 *   - **SessionKey** (out) Requires a two-phase authentication to be able to enter a security level. This two-phase authentication process needs to be performed using the Sec.AuthPhase1 and Sec.AuthPhase2 commands.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_AuthPhase1(brp_protocol protocol, unsigned _input_SecLevel, brp_buf _input_RndA, brp_buf* EncRndA, brp_buf* RndB, bool* ContinuousIV, bool* Encrypted, bool* MACed, bool* SessionKey, brp_mempool *mempool);
#else
brp_errcode brp_Sec_AuthPhase1(brp_Sec_AuthPhase1_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf EncRndB;
} brp_Sec_AuthPhase2_t;
/**
 * This command finishes the 2-phase authentication procedure started by the Sec.AuthPhase1 command. The host has to encrypt the parameter _RndB_ returned by Sec.AuthPhase1 two times, using AES128 encryption, with the key of the Security Level specified by the _SecLevel_ parameter of Sec.AuthPhase1. The host then sends the result back to the reader as _EncRndB_. 
 * 
 * If _RndB_ was encrypted correctly, the reader returns the OK status code and enters the security level specified in Sec.AuthPhase1 as parameter _SecLevel_. Depending on the Authentication Mode, the reader enters this Security Level permanently (all subsequent commands are executed in this Security Level) or temporarily (only encrypted/MACed commands are executed in this Security Level). To ensure that the reader enters the Security Level temporarily, one of the _Encrypted_ /_MACed_ flags of the Authentication Mode has to be set. Please refer to the Sec.SetKey command for details. 
 * 
 * Additionally, the Sec.AuthPhase2 command generates a session key by encrypting the _RndA_ parameter of Sec.AuthPhase1 and the _RndB_ value returned by Sec.AuthPhase1, _each only once_. The resulting 16 Byte session key is the result of the encryption of the concatenated _RndA_ (first 8 Bytes) and _RndB_ (last 8 Bytes).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **EncRndB** (in) _RndB_ value returned by Sec.AuthPhase1 encrypted twice by the key of Security Level specified by the _SecLevel_ variable of Sec.AuthPhase1.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_AuthPhase2(brp_protocol protocol, brp_buf _input_EncRndB);
#else
brp_errcode brp_Sec_AuthPhase2(brp_Sec_AuthPhase2_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool ContinuousIV;
	bool Encrypted;
	bool MACed;
	bool SessionKey;
	unsigned SecLevel;
	brp_buf TunnelledCmd;
	size_t TunnelledCmd_len;
	brp_buf* TunnelledResp;
	size_t* TunnelledResp_len;
	brp_mempool *mempool;
} brp_Sec_Tunnel_t;
/**
 * This command enables to send a specific command, called the _tunnelled_ command, to the reader (and to receive its response) in an encrypted and/or MACed fashion. 
 * 
 * Depending on the values of the _AuthModeAndSecLevel_ bit mask, the tunnelled command will either be encrypted, MACed or both. The structure of the _TunnelledCmd_ parameter and of the _TunnelledResp_ response vary depending on the encryption/MACing behaviour: 
 * 
 *   * _Encrypted only_ : 
 *     * The data has to be padded to the next 16 Byte boundary by appending "00"-Bytes. 
 *     * The initial vector (IV) has to be reset to all zeros (00 00 ... 00) if if the _ContinuousIV_ flag is not set. If _ContinuousIV_ is set, Cipher Block Chaining (CBC) will be used in the encryption process. In this case, the result from the last block encryption will be used as IV. 
 * 
 *     * The padded data is encrypted using AES128 in CBC mode. The key for encryption is either the key assigned to the currently selected Security Level or, if the _SessionKey_ flag is set, the session key derived from the values _RndA_ and _RndB_ of the Sec.AuthPhase1 command: 
 * 
 * _SessionKey = encrypt(RndA[0..7] + RndB[8..15])_
 * 
 *   * _Encrypted and MACed_ : Same as the _encrypted only_ variant, but a number of padding Bytes (at least 8) are appended to the encrypted data before transmission. The receiver always has to check whether the padding Bytes have the 0x00 value. If not, the frame is considered invalid. 
 *   * _MACed only_ : The encryption process is applied to the data which has to be MACed, but unlike in the _encryption only_ mode, the data is not modified. The first 8 Bytes of the hash value resulting from the encryption process (normally used as an IV for the next data block) are simply appended to the original data block to get the MACed data block. 
 * 
 * 
 * 
 * **This command must not be used in BRP _Repeat Mode_ .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ContinuousIV** (in) If _true_ , encryption/MACing will use a continuous IV for CBC mode will be used. That means the state of the IV after the first command will be used as the IV for the second command and so on.   If this bit is not set, the IV will be reset to zeros (00 00 ... 00) before every command or response is encrypted/MACed.
 *   - **Encrypted** (in) Requires that commands running in this security level always have to be encrypted.
 *   - **MACed** (in) Requires that commands running in this security level always have to be MACed.
 *   - **SessionKey** (in) If _true_ , a session key needs to be used instead of a fixed key. A session key can be generated using the 2-phase authentication process triggered by the Sec.AuthPhase1 and Sec.AuthPhase2 commands.
 *   - **SecLevel** (in) The Security Level (0-3), which should be entered when executing the tunnelled command.
 *   - **TunnelledCmd** (in) Encrypted and/or MACed command. This variable has the following data structure (before encryption):     * _Byte 0 (DeviceCode):_ Device code of the command to tunnel.    * _Byte 1 (CommandCode):_ Command code of the command to tunnel.    * _Byte 2-3 (ParamLen):_ Length of the parameter block of the command to tunnel.   **Unlike standard BRP frames, this parameter is MSB encoded.**    * _Byte 4-x (Param):_ Parameter block of the command to tunnel.    * _Byte x-n (PadByteAndMac):_ Depending on the Authorization Mode flags, these Bytes are either zero-padding bytes (always 0) or a MAC.
 *   - **TunnelledCmd_len** (in) Length of **TunnelledCmd** (in bytes).
 *   - **TunnelledResp** (out) Encrypted/MACed response of command. This variable has the following data structure (before encryption):     * _Byte 0 (StatusCode):_ The status code of the command which was tunnelled.    * _Byte 1-2 (RespLen):_ The length of the response block of the command which was tunnelled   **Unlike standard BRP frames, this parameter is MSB encoded.**    * _Byte 3-x (Resp):_ Response block of the command which was tunnelled.    * _Byte x-n (PadByteAndMac):_ Depending on the Authorization Mode flags, these Bytes are either zero-padding bytes (always 0) or a MAC.
 *   - **TunnelledResp_len** (out) Length of **TunnelledResp** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_Tunnel(brp_protocol protocol, bool _input_ContinuousIV, bool _input_Encrypted, bool _input_MACed, bool _input_SessionKey, unsigned _input_SecLevel, brp_buf _input_TunnelledCmd, size_t _input_TunnelledCmd_len, brp_buf* TunnelledResp, size_t* TunnelledResp_len, brp_mempool *mempool);
#else
brp_errcode brp_Sec_Tunnel(brp_Sec_Tunnel_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Sec_Reset_t;
/**
 * This command resets the Baltech ID engine's security system. After its execution, all security features will be disabled and the whole memory (i.e. the whole configuration) will be deleted. 
 * 
 * Unless a Sec.LockReset was executed beforehand, this command runs in every security level. If available, factory settings as well as "Encryption and Authorization" settings are restored.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_Reset(brp_protocol protocol);
#else
brp_errcode brp_Sec_Reset(brp_Sec_Reset_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned SecLevel;
} brp_Sec_LockReset_t;
/**
 * This command prevents, that a Sys.FactoryReset is run for the Security Level specified in the _SecLevel_ command. See also Sec.SetAcMask.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SecLevel** (in) Security Level which should be locked against the Sys.Reset command. A value of 0xFF indicates the current Security Level.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_LockReset(brp_protocol protocol, unsigned _input_SecLevel);
#else
brp_errcode brp_Sec_LockReset(brp_Sec_LockReset_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_HostSecurityAccessConditionBits* AcMask;
} brp_Sec_GetCurAcMask_t;
/**
 * This command retrieves the Access Condition Mask, which is applied by the reader in the current context (i.e. security level, protocol). 
 * 
 * If this command is executed in security level 1-3 the actual Access Condition Mask is defined by the value which has been set for the particular security level before via Sec.SetAcMask command respectively the configuration value Device/HostSecurity/AccessConditionMask. In this case this command is identical to Sec.GetAcMask for the respective security level. 
 * 
 * In case of security level 0 (plain access) the applied Access Condition Mask is determined by the protocol-specific Access Condition Mask ( Protocols/AccessConditionsBitsStd, Protocols/AccessConditionsBitsAlt). If this value is not available for the particular protocol the reader uses the value that has been set with Sec.SetAcMask respectively Device/HostSecurity/AccessConditionMask[0] before in combination (bitwise AND) with a hard-coded default value as fallback; in most cases this default value corresponds to all access rights - for BRP over TCP it is zero. 
 * 
 * **It is _not_ possible to deny the retrieval of the Access Condition Mask via the "Encryption and Authorization" settings in the configuration. This means that this command will never return the ERR_ACCESS_DENIED status code.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **AcMask** (out) Current Access Condition Mask. --- Every Feature in this list can be disabled by not setting the corresponding bit.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_GetCurAcMask(brp_protocol protocol, brp_HostSecurityAccessConditionBits* AcMask);
#else
brp_errcode brp_Sec_GetCurAcMask(brp_Sec_GetCurAcMask_t params);
#endif
#endif
/**
 * @}
 */