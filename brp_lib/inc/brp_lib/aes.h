/**
 * @file
 * AES (Advanced Encryption Standard) abstraction for brp_lib.
 * Provides AES-128 operations in ECB and CBC modes.
 *
 * @internal
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __AES_H__
#define __AES_H__

#include "common.h"

/**
 * AES block size in bytes (128 bits)
 */
#define AES_BLOCK_SIZE 16

/**
 * AES-128 key size in bytes
 */
#define AES_KEY_SIZE 16

/**
 * AES-128 key size in bits
 */
#define AES_KEY_SIZE_BITS 128

/**
 * AES operation return codes
 */
#define AES_OK 0                     // Success
#define AES_ERR_INVALID_PARAM 1      // NULL pointer or invalid parameter
#define AES_ERR_INVALID_LENGTH 2     // Invalid data length (not block-aligned or zero)
#define AES_ERR_CRYPTO_FAILURE 3     // Underlying crypto operation failed

/**
 * Opaque AES key schedule type.
 * Actual struct definition is backend-specific.
 */
typedef struct aes_ctx_t* aes_ctx;


/**
 * Create and initialize an AES-128 context from a key.
 *
 * @param key  128-bit (16-byte) AES key
 * @return     AES context, or NULL on failure
 *
 * @note Must be freed with aes_destroy_ctx()
 */
aes_ctx aes_create_ctx(const unsigned char key[AES_KEY_SIZE]);


/**
 * Encrypt a single 16-byte block using AES-128 in ECB mode.
 *
 * @param ctx        AES context from aes_create_ctx()
 * @param plaintext  16-byte input block
 * @param ciphertext 16-byte output block
 * @return AES_OK on success, AES_ERR_* on error
 *
 * @note All pointers must be non-NULL
 */
int aes_encrypt_block(
	aes_ctx ctx,
	const unsigned char plaintext[AES_BLOCK_SIZE],
	unsigned char ciphertext[AES_BLOCK_SIZE]
);


/**
 * Encrypt data using AES-128 in CBC mode.
 *
 * @param ctx            AES context from aes_create_ctx()
 * @param plaintext      Input data
 * @param plaintext_len  Length in bytes (must be multiple of AES_BLOCK_SIZE)
 * @param ciphertext     Output buffer (same length as plaintext)
 * @param iv             16-byte initialization vector
 * @return AES_OK on success, AES_ERR_* on error
 */
int aes_cbc_encrypt(
	aes_ctx ctx,
	const unsigned char * plaintext,
	size_t plaintext_len,
	unsigned char * ciphertext,
	const unsigned char iv[AES_BLOCK_SIZE]
);


/**
 * Decrypt data using AES-128 in CBC mode.
 *
 * @param ctx             AES context from aes_create_ctx()
 * @param ciphertext      Input data
 * @param ciphertext_len  Length in bytes (must be multiple of AES_BLOCK_SIZE)
 * @param plaintext       Output buffer (same length as ciphertext)
 * @param iv              16-byte initialization vector
 * @return AES_OK on success, AES_ERR_* on error
 */
int aes_cbc_decrypt(
	aes_ctx ctx,
	const unsigned char * ciphertext,
	size_t ciphertext_len,
	unsigned char * plaintext,
	const unsigned char iv[AES_BLOCK_SIZE]
);


/**
 * Calculate CBC-MAC (Cipher Block Chaining Message Authentication Code).
 *
 * @param ctx            AES context from aes_create_ctx()
 * @param plaintext      Input data
 * @param plaintext_len  Length in bytes (must be multiple of AES_BLOCK_SIZE)
 * @param mac            Input: IV (16 bytes), Output: MAC (16 bytes)
 * @return AES_OK on success, AES_ERR_* on error
 *
 * @note mac is both input (IV) and output (MAC result)
 */
int aes_cbc_mac(
	aes_ctx ctx,
	const unsigned char * plaintext,
	size_t plaintext_len,
	unsigned char mac[AES_BLOCK_SIZE]
);


/**
 * Destroy an AES context and securely wipe its memory.
 * Always call this after finished using an AES context.
 *
 * @param ctx  Context to destroy and free
 */
void aes_destroy_ctx(aes_ctx ctx);


#endif  // __AES_H__

/** @} */
