/**
 * AES abstraction implementation using OpenSSL EVP API.
 *
 * Compatible with both OpenSSL 1.1.x and 3.x
 * Requires: libssl-dev / openssl-devel
 */

#include "brp_lib/aes.h"
#include <openssl/evp.h>
#include <openssl/crypto.h>
#include <stdlib.h>
#include <string.h>


/**
 * Actual key context struct (backend-specific).
 * Stores the raw key for use in EVP operations.
 */
struct aes_ctx_t {
	unsigned char key[AES_KEY_SIZE];
};


aes_ctx aes_create_ctx(const unsigned char key[AES_KEY_SIZE])
{
	aes_ctx ctx;

	// Validate input
	if (key == NULL)
		return NULL;

	ctx = (aes_ctx)malloc(sizeof(struct aes_ctx_t));
	if (ctx == NULL)
		return NULL;

	// Zero entire struct to avoid uninitialized padding bytes
	memset(ctx, 0, sizeof(struct aes_ctx_t));

	// Store key for later use
	memcpy(ctx->key, key, AES_KEY_SIZE);

	return ctx;
}


int aes_encrypt_block(
	aes_ctx ctx,
	const unsigned char plaintext[AES_BLOCK_SIZE],
	unsigned char ciphertext[AES_BLOCK_SIZE])
{
	EVP_CIPHER_CTX *evp_ctx = NULL;
	int len;
	int final_len;

	// Validate inputs
	if (ctx == NULL || plaintext == NULL || ciphertext == NULL)
		return AES_ERR_INVALID_PARAM;

	// Create and initialize cipher context
	evp_ctx = EVP_CIPHER_CTX_new();
	if (evp_ctx == NULL)
	{
		OPENSSL_cleanse(ciphertext, AES_BLOCK_SIZE);
		return AES_ERR_CRYPTO_FAILURE;
	}

	// Initialize encryption with AES-128-ECB
	if (EVP_EncryptInit_ex(evp_ctx, EVP_aes_128_ecb(), NULL, ctx->key, NULL) != 1)
	{
		OPENSSL_cleanse(ciphertext, AES_BLOCK_SIZE);
		EVP_CIPHER_CTX_free(evp_ctx);
		return AES_ERR_CRYPTO_FAILURE;
	}

	// Disable padding (we're doing raw block encryption)
	EVP_CIPHER_CTX_set_padding(evp_ctx, 0);

	// Encrypt single block
	if (EVP_EncryptUpdate(evp_ctx, ciphertext, &len, plaintext, AES_BLOCK_SIZE) != 1)
	{
		OPENSSL_cleanse(ciphertext, AES_BLOCK_SIZE);
		EVP_CIPHER_CTX_free(evp_ctx);
		return AES_ERR_CRYPTO_FAILURE;
	}

	// Finalize (no additional output expected)
	if (EVP_EncryptFinal_ex(evp_ctx, ciphertext + len, &final_len) != 1)
	{
		OPENSSL_cleanse(ciphertext, AES_BLOCK_SIZE);
		EVP_CIPHER_CTX_free(evp_ctx);
		return AES_ERR_CRYPTO_FAILURE;
	}

	// Verify total output length
	if (len + final_len != AES_BLOCK_SIZE)
	{
		OPENSSL_cleanse(ciphertext, AES_BLOCK_SIZE);
		EVP_CIPHER_CTX_free(evp_ctx);
		return AES_ERR_CRYPTO_FAILURE;
	}

	// Clean up
	EVP_CIPHER_CTX_free(evp_ctx);
	return AES_OK;
}


int aes_cbc_encrypt(
	aes_ctx ctx,
	const unsigned char * plaintext,
	size_t plaintext_len,
	unsigned char * ciphertext,
	const unsigned char iv[AES_BLOCK_SIZE])
{
	EVP_CIPHER_CTX *evp_ctx = NULL;
	int len;
	int ciphertext_len;
	unsigned char iv_copy[AES_BLOCK_SIZE];

	// Validate inputs
	if (ctx == NULL || plaintext == NULL || ciphertext == NULL || iv == NULL)
		return AES_ERR_INVALID_PARAM;

	// Validate length is non-zero and block-aligned
	if (plaintext_len == 0 || plaintext_len % AES_BLOCK_SIZE != 0)
		return AES_ERR_INVALID_LENGTH;

	// Check for size_t to int overflow (int is typically 32-bit)
	if (plaintext_len > INT_MAX)
		return AES_ERR_INVALID_LENGTH;

	// OpenSSL modifies the IV, so make a copy
	memcpy(iv_copy, iv, AES_BLOCK_SIZE);

	// Create and initialize cipher context
	evp_ctx = EVP_CIPHER_CTX_new();
	if (evp_ctx == NULL)
	{
		OPENSSL_cleanse(iv_copy, AES_BLOCK_SIZE);
		return AES_ERR_CRYPTO_FAILURE;
	}

	// Initialize encryption with AES-128-CBC
	if (EVP_EncryptInit_ex(evp_ctx, EVP_aes_128_cbc(), NULL, ctx->key, iv_copy) != 1)
	{
		OPENSSL_cleanse(iv_copy, AES_BLOCK_SIZE);
		OPENSSL_cleanse(ciphertext, plaintext_len);
		EVP_CIPHER_CTX_free(evp_ctx);
		return AES_ERR_CRYPTO_FAILURE;
	}

	// Disable padding (data must be block-aligned)
	EVP_CIPHER_CTX_set_padding(evp_ctx, 0);

	// Encrypt
	if (EVP_EncryptUpdate(evp_ctx, ciphertext, &len, plaintext, (int)plaintext_len) != 1)
	{
		OPENSSL_cleanse(iv_copy, AES_BLOCK_SIZE);
		OPENSSL_cleanse(ciphertext, plaintext_len);
		EVP_CIPHER_CTX_free(evp_ctx);
		return AES_ERR_CRYPTO_FAILURE;
	}
	ciphertext_len = len;

	// Finalize
	if (EVP_EncryptFinal_ex(evp_ctx, ciphertext + len, &len) != 1)
	{
		OPENSSL_cleanse(iv_copy, AES_BLOCK_SIZE);
		OPENSSL_cleanse(ciphertext, plaintext_len);
		EVP_CIPHER_CTX_free(evp_ctx);
		return AES_ERR_CRYPTO_FAILURE;
	}
	ciphertext_len += len;

	// Clear IV copy from stack
	OPENSSL_cleanse(iv_copy, AES_BLOCK_SIZE);

	// Verify output length matches input
	if ((size_t)ciphertext_len != plaintext_len)
	{
		OPENSSL_cleanse(ciphertext, plaintext_len);
		EVP_CIPHER_CTX_free(evp_ctx);
		return AES_ERR_CRYPTO_FAILURE;
	}

	// Clean up
	EVP_CIPHER_CTX_free(evp_ctx);

	return AES_OK;
}


int aes_cbc_decrypt(
	aes_ctx ctx,
	const unsigned char * ciphertext,
	size_t ciphertext_len,
	unsigned char * plaintext,
	const unsigned char iv[AES_BLOCK_SIZE])
{
	EVP_CIPHER_CTX *evp_ctx = NULL;
	int len;
	int plaintext_len_out;
	unsigned char iv_copy[AES_BLOCK_SIZE];

	// Validate inputs
	if (ctx == NULL || ciphertext == NULL || plaintext == NULL || iv == NULL)
		return AES_ERR_INVALID_PARAM;

	// Validate length is non-zero and block-aligned
	if (ciphertext_len == 0 || ciphertext_len % AES_BLOCK_SIZE != 0)
		return AES_ERR_INVALID_LENGTH;

	// Check for size_t to int overflow (int is typically 32-bit)
	if (ciphertext_len > INT_MAX)
		return AES_ERR_INVALID_LENGTH;

	// OpenSSL modifies the IV, so make a copy
	memcpy(iv_copy, iv, AES_BLOCK_SIZE);

	// Create and initialize cipher context
	evp_ctx = EVP_CIPHER_CTX_new();
	if (evp_ctx == NULL)
	{
		OPENSSL_cleanse(iv_copy, AES_BLOCK_SIZE);
		return AES_ERR_CRYPTO_FAILURE;
	}

	// Initialize decryption with AES-128-CBC
	if (EVP_DecryptInit_ex(evp_ctx, EVP_aes_128_cbc(), NULL, ctx->key, iv_copy) != 1)
	{
		OPENSSL_cleanse(iv_copy, AES_BLOCK_SIZE);
		OPENSSL_cleanse(plaintext, ciphertext_len);
		EVP_CIPHER_CTX_free(evp_ctx);
		return AES_ERR_CRYPTO_FAILURE;
	}

	// Disable padding (data must be block-aligned)
	EVP_CIPHER_CTX_set_padding(evp_ctx, 0);

	// Decrypt
	if (EVP_DecryptUpdate(evp_ctx, plaintext, &len, ciphertext, (int)ciphertext_len) != 1)
	{
		OPENSSL_cleanse(iv_copy, AES_BLOCK_SIZE);
		OPENSSL_cleanse(plaintext, ciphertext_len);
		EVP_CIPHER_CTX_free(evp_ctx);
		return AES_ERR_CRYPTO_FAILURE;
	}
	plaintext_len_out = len;

	// Finalize
	if (EVP_DecryptFinal_ex(evp_ctx, plaintext + len, &len) != 1)
	{
		OPENSSL_cleanse(iv_copy, AES_BLOCK_SIZE);
		OPENSSL_cleanse(plaintext, ciphertext_len);
		EVP_CIPHER_CTX_free(evp_ctx);
		return AES_ERR_CRYPTO_FAILURE;
	}
	plaintext_len_out += len;

	// Clear IV copy from stack
	OPENSSL_cleanse(iv_copy, AES_BLOCK_SIZE);

	// Verify output length matches input
	if ((size_t)plaintext_len_out != ciphertext_len)
	{
		OPENSSL_cleanse(plaintext, ciphertext_len);
		EVP_CIPHER_CTX_free(evp_ctx);
		return AES_ERR_CRYPTO_FAILURE;
	}

	// Clean up
	EVP_CIPHER_CTX_free(evp_ctx);

	return AES_OK;
}


int aes_cbc_mac(
	aes_ctx ctx,
	const unsigned char * plaintext,
	size_t plaintext_len,
	unsigned char mac[AES_BLOCK_SIZE])
{
	EVP_CIPHER_CTX *evp_ctx = NULL;
	int len;
	unsigned char * temp_buffer = NULL;
	unsigned char iv_copy[AES_BLOCK_SIZE];
	int result = AES_ERR_CRYPTO_FAILURE;

	// Validate inputs
	if (ctx == NULL || plaintext == NULL || mac == NULL)
		return AES_ERR_INVALID_PARAM;

	// Validate length is at least one block and block-aligned
	if (plaintext_len < AES_BLOCK_SIZE || plaintext_len % AES_BLOCK_SIZE != 0)
		return AES_ERR_INVALID_LENGTH;

	// Check for size_t to int overflow (int is typically 32-bit)
	if (plaintext_len > INT_MAX)
		return AES_ERR_INVALID_LENGTH;

	// CBC-MAC: Encrypt in CBC mode and keep only the last block

	// Make a copy of the IV (mac serves as both input IV and output MAC)
	memcpy(iv_copy, mac, AES_BLOCK_SIZE);

	// Allocate temporary buffer for ciphertext
	temp_buffer = (unsigned char *)malloc(plaintext_len);
	if (temp_buffer == NULL)
	{
		OPENSSL_cleanse(iv_copy, AES_BLOCK_SIZE);
		return AES_ERR_CRYPTO_FAILURE;
	}

	// Create and initialize cipher context
	evp_ctx = EVP_CIPHER_CTX_new();
	if (evp_ctx == NULL)
		goto cleanup;

	// Initialize encryption with AES-128-CBC
	if (EVP_EncryptInit_ex(evp_ctx, EVP_aes_128_cbc(), NULL, ctx->key, iv_copy) != 1)
		goto cleanup;

	// Disable padding
	EVP_CIPHER_CTX_set_padding(evp_ctx, 0);

	// Encrypt
	if (EVP_EncryptUpdate(evp_ctx, temp_buffer, &len, plaintext, (int)plaintext_len) != 1)
		goto cleanup;

	// Finalize
	if (EVP_EncryptFinal_ex(evp_ctx, temp_buffer + len, &len) != 1)
		goto cleanup;

	// Copy last block to MAC output
	memcpy(mac, temp_buffer + plaintext_len - AES_BLOCK_SIZE, AES_BLOCK_SIZE);

	result = AES_OK;

cleanup:
	// Clear IV copy from stack
	OPENSSL_cleanse(iv_copy, AES_BLOCK_SIZE);

	// Securely wipe temporary buffer before freeing
	if (temp_buffer != NULL)
	{
		OPENSSL_cleanse(temp_buffer, plaintext_len);
		free(temp_buffer);
	}

	// Clear MAC output on error
	if (result != 0 && mac != NULL)
		OPENSSL_cleanse(mac, AES_BLOCK_SIZE);

	if (evp_ctx != NULL)
		EVP_CIPHER_CTX_free(evp_ctx);

	return result;
}


void aes_destroy_ctx(aes_ctx ctx)
{
	if (ctx != NULL)
	{
		// Securely wipe the key
		// Use OPENSSL_cleanse for OpenSSL 1.1.x and 3.x compatibility
		OPENSSL_cleanse(ctx->key, AES_KEY_SIZE);
		free(ctx);
	}
}
