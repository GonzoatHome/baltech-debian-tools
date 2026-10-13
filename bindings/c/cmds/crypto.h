/**
 * @file
 * This command group regroups the commands needed to use the integrated _crypto-engine_ of the Baltech reader.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_CRYPTO_H__
#define __BRP_BALTECH_SDK_CMDS_CRYPTO_H__
#include "../typedefs.h"
/**
 * Encrypted block format is invalid.
 */
#define BRP_Crypto_CrptErrInvalidBlock BRP_ERR_STATUS(0x0200, 0x01)
/**
 * Internal key cannot be accessed for the specified action due to the access condition flags settings.
 */
#define BRP_Crypto_CrptErrAuth BRP_ERR_STATUS(0x0200, 0x02)
/**
 * Specified key not available in the internal key list.
 */
#define BRP_Crypto_CrptErrKeyNotFound BRP_ERR_STATUS(0x0200, 0x03)
/**
 * Configuration key cannot be stored in the reader's configuration.
 */
#define BRP_Crypto_CrptErrWriteConfigkey BRP_ERR_STATUS(0x0200, 0x04)
/**
 * No valid configuration card key. Since no key is present, the reader is forced to work unencrypted. 
 * 
 * **This status code is not supported by Crypto.Encrypt/Crypto.Decrypt commands due to legacy reasons.**
 */
#define BRP_Crypto_CrptErrInvalidKey BRP_ERR_STATUS(0x0200, 0x05)
typedef struct {
	brp_protocol protocol;
	unsigned KeyIndex;
	brp_buf KeyValue;
	brp_buf Block;
	brp_buf* EncryptedBlock;
	brp_mempool *mempool;
} brp_Crypto_EncryptBlock_t;
/**
 * This command encrypts an 8-Byte data block given in the _Block_ parameter using the SkipJack algorithm. If _KeyIndex_ is set to 0x00, _KeyValue_ will be used as encryption key. Otherwise, _KeyIndex_ is interpreted as the index of the corresponding entry in the internal key list. _KeyIndex_ = 0x01 denotes configuration value 0x81, _KeyIndex_ = 0x02 denotes configuration value 0x82, etc.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **KeyIndex** (in) Index of key to use to encrypt data. _KeyIndex_ must be set to 0x00 if a user-defined key, specified in the _KeyValue_ parameter, should be used for encryption.
 *   - **KeyValue** (in) If _KeyIndex_ is set to 0x00, this value specifies a user-defined encryption key.
 *   - **Block** (in) Data block to encrypt.
 *   - **EncryptedBlock** (out) Encrypted data block.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_EncryptBlock(brp_protocol protocol, unsigned _input_KeyIndex, brp_buf _input_KeyValue, brp_buf _input_Block, brp_buf* EncryptedBlock, brp_mempool *mempool);
#else
brp_errcode brp_Crypto_EncryptBlock(brp_Crypto_EncryptBlock_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned KeyIndex;
	brp_buf KeyValue;
	brp_buf Block;
	brp_buf* UnencryptedBlock;
	brp_mempool *mempool;
} brp_Crypto_DecryptBlock_t;
/**
 * This command decrypts an 8-Byte data block given in the _Block_ parameter using the SkipJack algorithm. If _KeyIndex_ is set to 0x00, _KeyValue_ will be used as encryption key. Otherwise, _KeyIndex_ is interpreted as the index of the corresponding entry in the internal key list. _KeyIndex_ = 0x01 denotes configuration value 0x81, _KeyIndex_ = 0x02 denotes configuration value 0x82, etc.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **KeyIndex** (in) Index of key to use to decrypt data. _KeyIndex_ must be set to 0x00 if a user-defined key, specified in the _KeyValue_ parameter, should be used for decryption.
 *   - **KeyValue** (in) If _KeyIndex_ is set to 0x00, this value specifies a user-defined decryption key.
 *   - **Block** (in) Data block to decrypt.
 *   - **UnencryptedBlock** (out) Unencrypted data block after decryption.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_DecryptBlock(brp_protocol protocol, unsigned _input_KeyIndex, brp_buf _input_KeyValue, brp_buf _input_Block, brp_buf* UnencryptedBlock, brp_mempool *mempool);
#else
brp_errcode brp_Crypto_DecryptBlock(brp_Crypto_DecryptBlock_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned KeyIndex;
	brp_buf KeyValue;
	brp_buf InitialVector;
	brp_buf Buffer;
	size_t Buffer_len;
	brp_buf* NextInitialVector;
	brp_buf* EncryptedBuffer;
	size_t* EncryptedBuffer_len;
	brp_mempool *mempool;
} brp_Crypto_EncryptBuffer_t;
/**
 * This command encrypts a variable length buffer given in the _Buffer_ parameter using the SkipJack algorithm. If _KeyIndex_ is set to 0x00, _KeyValue_ will be used as encryption key. Otherwise, _KeyIndex_ is interpreted as the index of the corresponding entry in the internal key list. _KeyIndex_ = 0x01 denotes configuration value 0x81, _KeyIndex_ = 0x02 denotes configuration value 0x82, etc. 
 * 
 * The value returned in the _InitialVector_ variable is necessary for CBC encryption. If large amounts of data must be encrypted, this command has to be called more than once. In this case, the returned _InitialVector_ variable of call _i_ of the command has to be specified as the _InitialVector_ parameter of call _i+1_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **KeyIndex** (in) Index of key to use to encrypt data. _KeyIndex_ must be set to 0x00 if a user-defined key, specified in the _KeyValue_ parameter, should be used for encryption.
 *   - **KeyValue** (in) If _KeyIndex_ is set to 0x00, this value specifies a user-defined encryption key.
 *   - **InitialVector** (in) Initial vector (IV) used for encryption.
 *   - **Buffer** (in) Data buffer to encrypt.
 *   - **Buffer_len** (in) Length of **Buffer** (in bytes).
 *   - **NextInitialVector** (out) Initial vector to be used as _InitialVector_ parameter in the next call of this command.
 *   - **EncryptedBuffer** (out) Buffer after encryption.
 *   - **EncryptedBuffer_len** (out) Length of **EncryptedBuffer** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_EncryptBuffer(brp_protocol protocol, unsigned _input_KeyIndex, brp_buf _input_KeyValue, brp_buf _input_InitialVector, brp_buf _input_Buffer, size_t _input_Buffer_len, brp_buf* NextInitialVector, brp_buf* EncryptedBuffer, size_t* EncryptedBuffer_len, brp_mempool *mempool);
#else
brp_errcode brp_Crypto_EncryptBuffer(brp_Crypto_EncryptBuffer_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned KeyIndex;
	brp_buf KeyValue;
	brp_buf InitialVector;
	brp_buf Buffer;
	size_t Buffer_len;
	brp_buf* NextInitialVector;
	brp_buf* UnencryptedBuffer;
	size_t* UnencryptedBuffer_len;
	brp_mempool *mempool;
} brp_Crypto_DecryptBuffer_t;
/**
 * This command decrypts a variable length buffer given in the _Buffer_ parameter using the SkipJack algorithm. If _KeyIndex_ is set to 0x00, _KeyValue_ will be used as encryption key. Otherwise, _KeyIndex_ is interpreted as the index of the corresponding entry in the internal key list. _KeyIndex_ = 0x01 denotes configuration value 0x81, _KeyIndex_ = 0x02 denotes configuration value 0x82, etc. 
 * 
 * The value returned in the _InitialVector_ variable is necessary for CBC encryption. If large amounts of data must be encrypted, this command has to be called more than once. In this case, the returned _InitialVector_ variable of call _i_ of the command has to be specified as the _InitialVector_ parameter of call _i+1_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **KeyIndex** (in) Index of key to use to decrypt data. _KeyIndex_ must be set to 0x00 if a user-defined key, specified in the _KeyValue_ parameter, should be used for decryption.
 *   - **KeyValue** (in) If _KeyIndex_ is set to 0x00, this value specifies a user-defined decryption key.
 *   - **InitialVector** (in) Initial vector (IV) used for decryption.
 *   - **Buffer** (in) Data buffer to decrypt.
 *   - **Buffer_len** (in) Length of **Buffer** (in bytes).
 *   - **NextInitialVector** (out) Initial vector to be used as _InitialVector_ parameter in the next call of this command.
 *   - **UnencryptedBuffer** (out) Unencrypted buffer after decryption.
 *   - **UnencryptedBuffer_len** (out) Length of **UnencryptedBuffer** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_DecryptBuffer(brp_protocol protocol, unsigned _input_KeyIndex, brp_buf _input_KeyValue, brp_buf _input_InitialVector, brp_buf _input_Buffer, size_t _input_Buffer_len, brp_buf* NextInitialVector, brp_buf* UnencryptedBuffer, size_t* UnencryptedBuffer_len, brp_mempool *mempool);
#else
brp_errcode brp_Crypto_DecryptBuffer(brp_Crypto_DecryptBuffer_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned KeyVersion;
	unsigned EmbeddedKeyIndex;
	unsigned EmbeddedKeyPos;
	brp_buf Buffer;
	size_t Buffer_len;
	brp_buf InitialVector;
	size_t InitialVector_len;
	brp_buf* EncryptedBuffer;
	size_t* EncryptedBuffer_len;
	brp_buf* NextInitialVector;
	size_t* NextInitialVector_len;
	brp_mempool *mempool;
} brp_Crypto_BalKeyEncryptBuffer_t;
/**
 * This command is a special version of the Crypto.EncryptBuffer command which always uses a customer key to encrypt a buffer of data and inserts a Crypto-Key at a desired position before encryption. 
 * 
 * The key to insert has to be specified in the _EmbeddedKeyIndex_ parameter. In this case, the 10 Byte Key will, on the one hand, replace the data at the _EmbeddedKeyPos_ position, and on the other hand, replace the last two Bytes by a CRC (16-bit, 8404B, MSB encoded) that is generated on the data contained in _Buffer_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **KeyVersion** (in) 2: use SkipJack Key, 3: Use AES Key.
 *   - **EmbeddedKeyIndex** (in) Index of the embedded key to insert in the data (value != 0x00). No key is inserted when this parameter is set to 0x00.
 *   - **EmbeddedKeyPos** (in) If an embedded key is specified, this value specifies the position where to include the key.
 *   - **Buffer** (in) Data buffer to encrypt.
 *   - **Buffer_len** (in) Length of **Buffer** (in bytes).
 *   - **InitialVector** (in) Initial vector (IV) used for encryption.
 *   - **InitialVector_len** (in) Length of **InitialVector** (in bytes).
 *   - **EncryptedBuffer** (out) Buffer after encryption.
 *   - **EncryptedBuffer_len** (out) Length of **EncryptedBuffer** (in bytes).
 *   - **NextInitialVector** (out) Initial vector to be used as _InitialVector_ parameter in the next call of this command.
 *   - **NextInitialVector_len** (out) Length of **NextInitialVector** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_BalKeyEncryptBuffer(brp_protocol protocol, unsigned _input_KeyVersion, unsigned _input_EmbeddedKeyIndex, unsigned _input_EmbeddedKeyPos, brp_buf _input_Buffer, size_t _input_Buffer_len, brp_buf _input_InitialVector, size_t _input_InitialVector_len, brp_buf* EncryptedBuffer, size_t* EncryptedBuffer_len, brp_buf* NextInitialVector, size_t* NextInitialVector_len, brp_mempool *mempool);
#else
brp_errcode brp_Crypto_BalKeyEncryptBuffer(brp_Crypto_BalKeyEncryptBuffer_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned KeyIndex;
	brp_buf KeyValue;
	unsigned* KeySignature;
} brp_Crypto_GetKeySig_t;
/**
 * Returns a signature of the ConfigurationKey to identify the MasterCard needed for this reader.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **KeyIndex** (in) Index of key to get the signature from. _KeyIndex_ must be set to 0x00 if a user-defined key, specified in the _KeyValue_ parameter, should be used instead.
 *   - **KeyValue** (in) If _KeyIndex_ is set to 0x00, this value specifies the key to get the signature from.
 *   - **KeySignature** (out) Unique signature of the desired ConfigurationKey.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_GetKeySig(brp_protocol protocol, unsigned _input_KeyIndex, brp_buf _input_KeyValue, unsigned* KeySignature);
#else
brp_errcode brp_Crypto_GetKeySig(brp_Crypto_GetKeySig_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned KeyIndex;
	bool ForceDefaultKey;
} brp_Crypto_CopyConfigKey_t;
/**
 * Copies the configuration card key 0x0202/0x85 (_Device/Run/ConfigCardEncryptKey_) to the _Custom/Crypto/Key[x]_ area of the Baltech reader's configuration, where _x_ is the index of the target key, specified in the _KeyIndex_ parameter. 
 * 
 * When a key does not exist, a Baltech standard key is used instead.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **KeyIndex** (in) Index of custom key configuration value in which the configuration card key should be copied. This value must be != 0x00.
 *   - **ForceDefaultKey** (in) If _true_ , the Baltech standard key will be copied even if a custom key is defined.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_CopyConfigKey(brp_protocol protocol, unsigned _input_KeyIndex, bool _input_ForceDefaultKey);
#else
brp_errcode brp_Crypto_CopyConfigKey(brp_Crypto_CopyConfigKey_t params);
#endif
#endif
/**
 * @}
 */