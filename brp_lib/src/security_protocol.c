#include "brp_lib/brp_protocol.h"
#include "brp_lib/security_protocol.h"
#include "brp_lib/aes.h"
#include "brp_lib/platform.h"


#define TIMEOUT_AUTH1      100
#define TIMEOUT_AUTH2      100

#define CMDCODE_AUTHPHASE1 0x0704
#define CMDCODE_AUTHPHASE2 0x0705
#define CMDCODE_TUNNEL     0x0706

#define SECBITS_CONT_IV    0x80
#define SECBITS_ENCRYPT    0x40
#define SECBITS_MAC        0x20
#define SECBITS_SESSIONKEY 0x10

#define BRP_MAC_SIZE          8


typedef struct sec_protocol_t {
	struct brp_protocol_t p;
	int security_level;
	brp_sec_key base_key;
	int sec_mode;
	brp_sec_iv iv;
	aes_ctx session_key;
	int last_cmd_code;
} * sec_protocol;


brp_errcode brp_mutual_authenticate(
		brp_protocol protocol, int security_level, brp_sec_key key,
		int * req_auth_modes, brp_sec_key session_key)
{
	brp_sec_key rnd_a, enc_rnd_a, enc2_rnd_a, recv_enc2_rnd_a;
	brp_sec_key rnd_b, enc_rnd_b, enc2_rnd_b;
	aes_ctx prepared_key = NULL;
	brp_frame_reader frm_rdr;
	brp_errcode errcode;

	if (protocol == NULL  ||  key == NULL)
		return BRP_ERR_INVALID_API_CALL;

	if (security_level > BRP_MAX_SECURITY_LEVEL)
		return BRP_ERR_SEC_LEVEL_NOT_SUPPORTED;

	if (! brp_get_random(rnd_a, AES_BLOCK_SIZE))
		return BRP_ERR_GEN_RANDOM_DATA;

	brp_frame_write_start(&protocol->send_frame);
	brp_frame_write_int8(&protocol->send_frame, BRP_MODE_STD);
	brp_frame_write_int16(&protocol->send_frame, CMDCODE_AUTHPHASE1);
	brp_frame_write_int32(&protocol->send_frame, TIMEOUT_AUTH1);
	brp_frame_write_int8(&protocol->send_frame, security_level);
	brp_frame_write(&protocol->send_frame, rnd_a, BRP_AES_KEY_SIZE);
	errcode = brp_send_frame(protocol);
	if (errcode != BRP_OK)
		return errcode;

	errcode = brp_recv_any_frame(protocol, TIMEOUT_AUTH1);
	if (errcode != BRP_OK)
		return errcode;

	brp_frame_reader_start(&frm_rdr, &protocol->recv_frame);
	brp_frame_read(&frm_rdr, recv_enc2_rnd_a, BRP_AES_KEY_SIZE);
	brp_frame_read(&frm_rdr, rnd_b, BRP_AES_KEY_SIZE);
	*req_auth_modes = (int) brp_frame_read_int8(&frm_rdr);
	if (! brp_frame_read_eof(&frm_rdr))
		return BRP_ERR_CRYPTO_FORMAT;

	prepared_key = aes_create_ctx(key);
	if (prepared_key == NULL)
		return BRP_ERR_OUT_OF_MEMORY;

	if (aes_encrypt_block(prepared_key, rnd_a, enc_rnd_a) != AES_OK)
	{
		aes_destroy_ctx(prepared_key);
		return BRP_ERR_CRYPTO_FORMAT;
	}
	if (aes_encrypt_block(prepared_key, enc_rnd_a, enc2_rnd_a) != AES_OK)
	{
		aes_destroy_ctx(prepared_key);
		return BRP_ERR_CRYPTO_FORMAT;
	}
	if (memcmp(recv_enc2_rnd_a, enc2_rnd_a, BRP_AES_KEY_SIZE) != 0)
	{
		aes_destroy_ctx(prepared_key);
		return BRP_ERR_INVALID_KEY;
	}

	if (aes_encrypt_block(prepared_key, rnd_b, enc_rnd_b) != AES_OK)
	{
		aes_destroy_ctx(prepared_key);
		return BRP_ERR_CRYPTO_FORMAT;
	}
	if (aes_encrypt_block(prepared_key, enc_rnd_b, enc2_rnd_b) != AES_OK)
	{
		aes_destroy_ctx(prepared_key);
		return BRP_ERR_CRYPTO_FORMAT;
	}

	aes_destroy_ctx(prepared_key);

	brp_frame_write_start(&protocol->send_frame);
	brp_frame_write_int8(&protocol->send_frame, BRP_MODE_STD);
	brp_frame_write_int16(&protocol->send_frame, CMDCODE_AUTHPHASE2);
	brp_frame_write_int32(&protocol->send_frame, TIMEOUT_AUTH2);
	brp_frame_write(&protocol->send_frame, enc2_rnd_b, BRP_AES_KEY_SIZE);
	errcode = brp_send_frame(protocol);
	if (errcode != BRP_OK)
		return errcode;
	
	errcode = brp_recv_any_frame(protocol, TIMEOUT_AUTH2);
	if (errcode != BRP_OK)
		return errcode;
	brp_frame_reader_start(&frm_rdr, &protocol->recv_frame);
	if (! brp_frame_read_eof(&frm_rdr))
		return BRP_ERR_FRAMEFORMAT;
	
	memcpy(session_key, enc_rnd_a, 8);
	memcpy(session_key + 8, enc_rnd_b + 8, 8);
	
	// wipe all key-related data before leaving
	memset(rnd_a, 0, sizeof(rnd_a));
	memset(enc_rnd_a, 0, sizeof(enc_rnd_a));
	memset(enc2_rnd_a, 0, sizeof(enc2_rnd_a));
	memset(recv_enc2_rnd_a, 0, sizeof(recv_enc2_rnd_a));
	memset(rnd_b, 0, sizeof(rnd_b));
	memset(enc_rnd_b, 0, sizeof(enc_rnd_b));
	memset(enc2_rnd_b, 0, sizeof(enc2_rnd_b));
	return BRP_OK;
}


// attention: "iv" is an input AND output parameter
static brp_buf calc_aes_cmac(brp_buf data, size_t size,
		brp_buf iv, aes_ctx key_schedule)
{
	size_t bestfit_size = size / BRP_AES_BLOCK_SIZE * BRP_AES_BLOCK_SIZE;
	if (bestfit_size > 0)
		aes_cbc_mac(key_schedule, data, bestfit_size, iv);
	if (bestfit_size != size)
	{
		// "size" is not multiple of AES_BLOCK_SIZE =>
		// last block has to be extended by zeros
		unsigned char last_blk[BRP_AES_BLOCK_SIZE];
		memset(last_blk, 0, AES_BLOCK_SIZE);
		memcpy(last_blk, data + bestfit_size, size-bestfit_size);
		aes_cbc_mac(key_schedule, last_blk, BRP_AES_BLOCK_SIZE, iv);
	}
	return iv;
}


static brp_errcode secured_send_frm_prepkey(
		brp_protocol protocol, int security_level, int sec_mode,
		aes_ctx key, brp_sec_iv iv,
		int cmd_code, brp_buf param_buf, size_t param_len,
		brp_time cmd_timeout, int mode)
{
	brp_sec_iv work_iv;
	size_t protected_start;
	size_t padding_len, plain_len;
	brp_frame frm = &protocol->send_frame;
	unsigned char sec_bits = SECBITS_MAC;
	
	if (! (sec_mode & BRP_SECMODE_PLAIN))
		sec_bits |= SECBITS_ENCRYPT;
	if (! (sec_mode & BRP_SECMODE_STATELESS))
	{
		sec_bits |= SECBITS_SESSIONKEY|SECBITS_CONT_IV;
		if (iv == NULL)
			return BRP_ERR_INVALID_API_CALL;
		memcpy(work_iv, iv, BRP_AES_BLOCK_SIZE);
	}
	else
		memset(work_iv, 0, BRP_AES_BLOCK_SIZE);
	
	brp_frame_write_start(frm);
	brp_frame_write_int8(frm, mode);
	brp_frame_write_int16(frm, CMDCODE_TUNNEL);
	brp_frame_write_int32(frm, (unsigned) cmd_timeout);
	brp_frame_write_int8(frm, sec_bits | security_level);
	protected_start = frm->act_size;
	brp_frame_write_int16(frm, cmd_code);
	brp_frame_write_int16(frm, (unsigned) param_len);
	brp_frame_write(frm, param_buf, param_len);
	if (sec_mode & BRP_SECMODE_PLAIN)
	{
		brp_frame_write(frm,
						calc_aes_cmac(frm->ptr + protected_start,
									  frm->act_size - protected_start,
									  work_iv, key),
						BRP_MAC_SIZE);
		if (! (sec_mode & BRP_SECMODE_STATELESS))
			memcpy(iv, work_iv, BRP_AES_BLOCK_SIZE);
	}
	else
	{
		plain_len = frm->act_size - protected_start;
		padding_len = (AES_BLOCK_SIZE - (plain_len % AES_BLOCK_SIZE))
					  % AES_BLOCK_SIZE;
		if (padding_len < BRP_MAC_SIZE)
			padding_len += AES_BLOCK_SIZE;
		brp_frame_write_fill(frm, 0, padding_len);
		aes_cbc_encrypt(key,
						frm->ptr + protected_start,
						frm->act_size - protected_start,
						frm->ptr + protected_start,
						work_iv);
		if (! (sec_mode & BRP_SECMODE_STATELESS))
			memcpy(iv, frm->ptr + frm->act_size - BRP_AES_BLOCK_SIZE,
					BRP_AES_BLOCK_SIZE);
	}
	
	return brp_send_frame(protocol);
}


brp_errcode brp_secured_send_frm(
		brp_protocol protocol, int security_level, int sec_mode,
		brp_sec_key key, brp_sec_iv iv,
		int cmd_code, brp_buf param_buf, size_t param_len,
		brp_time cmd_timeout, int mode)
{
	aes_ctx prepared_key = NULL;
	brp_errcode errcode;
	if (protocol == NULL || key == NULL || (param_buf == NULL && param_len!=0))
		return BRP_ERR_INVALID_API_CALL;
	prepared_key = aes_create_ctx(key);
	if (prepared_key == NULL)
		return BRP_ERR_OUT_OF_MEMORY;
	errcode = secured_send_frm_prepkey(
			protocol, security_level, sec_mode, prepared_key, iv, cmd_code,
			param_buf, param_len, cmd_timeout, mode);
	aes_destroy_ctx(prepared_key);
	return errcode;
}


static brp_errcode secured_recv_frm_prepkey(
		brp_protocol protocol, int sec_mode, aes_ctx  key,
		brp_sec_iv iv, int cmd_code, brp_frame resp_frm, brp_time timeout)
{
	brp_errcode errcode;
	struct brp_frame_t plain_frm;
	brp_frame_reader plain_rdr;
	brp_sec_iv temp_iv;
	unsigned status;
	size_t resp_len, cmac_pos;
	brp_buf padding_start;

	// receive frame from underlying protocol
	errcode = brp_recv_any_frame(protocol, timeout);
	if (errcode != BRP_OK)
		return errcode;
	
	// setup crypto parameters (key_schedule/IV)
	if (sec_mode & BRP_SECMODE_STATELESS)
	{
		memset(temp_iv, 0, BRP_AES_BLOCK_SIZE);
		iv = temp_iv;
	}

	brp_frame_init(&plain_frm);
	if (sec_mode & BRP_SECMODE_PLAIN)
	{
		if (protocol->recv_frame.act_size < BRP_MAC_SIZE)
			return BRP_ERR_CRYPTO_FORMAT;
		cmac_pos = protocol->recv_frame.act_size - BRP_MAC_SIZE;
		// transfer payload without CMAC to plain_frm
		brp_frame_write(&plain_frm, protocol->recv_frame.ptr, cmac_pos);
		calc_aes_cmac(plain_frm.ptr, cmac_pos, iv, key);
		if (memcmp(protocol->recv_frame.ptr + cmac_pos,
				iv,
				BRP_MAC_SIZE) != 0)
			return BRP_ERR_CRYPTO_FORMAT;
	}
	else
	{
		if (protocol->recv_frame.act_size < BRP_AES_BLOCK_SIZE)
			return BRP_ERR_CRYPTO_FORMAT;
		// decode encrypted payload to plain_frm
		brp_frame_write_fill(&plain_frm, 0, protocol->recv_frame.act_size);
		if (brp_frame_write_err(&plain_frm))
		{
			brp_frame_deinit(&plain_frm);
			return BRP_ERR_OUT_OF_MEMORY;
		}
		if (aes_cbc_decrypt(key,
				protocol->recv_frame.ptr,
				protocol->recv_frame.act_size,
				plain_frm.ptr, iv) != AES_OK)
		{
			brp_frame_deinit(&plain_frm);
			return BRP_ERR_CRYPTO_FORMAT;
		}
		memcpy(iv, protocol->recv_frame.ptr + protocol->recv_frame.act_size
		       - AES_BLOCK_SIZE, AES_BLOCK_SIZE);
	}
	
	// decode plain payload
	brp_frame_reader_start(&plain_rdr, &plain_frm);
	status = brp_frame_read_int8(&plain_rdr);
	resp_len = (size_t) brp_frame_read_int16(&plain_rdr);
	brp_frame_read_frm(&plain_rdr, resp_frm, resp_len);
	padding_start = plain_rdr.ptr;
	
	// do error checks
	while (!brp_frame_read_eof(&plain_rdr))
		if ((sec_mode & BRP_SECMODE_PLAIN) ||
		    brp_frame_read_err(&plain_rdr)  ||
		    brp_frame_read_int8(&plain_rdr) != 0)
		{
			// padding was not 0
			brp_frame_deinit(&plain_frm);
			return BRP_ERR_CRYPTO_FORMAT;
		}
	brp_frame_deinit(&plain_frm);
	if (! (sec_mode & BRP_SECMODE_PLAIN))
		// in encrypted mode expect "block-size" additional zeros...
		if (plain_rdr.ptr - padding_start < BRP_MAC_SIZE)
			return BRP_ERR_CRYPTO_FORMAT;
	if (status != 0)
		return BRP_ERR_STATUS(cmd_code, status);
	if (brp_frame_write_err(resp_frm))
		return BRP_ERR_OUT_OF_MEMORY;

	return BRP_OK;
}


brp_errcode brp_secured_recv_frm(
		brp_protocol protocol, int sec_mode, brp_sec_key key, brp_sec_iv iv,
		int cmd_code, brp_frame resp_frm, brp_time timeout)
{
	aes_ctx prepared_key = NULL;
	brp_errcode errcode;
	if (key == NULL || resp_frm == NULL)
		return BRP_ERR_INVALID_API_CALL;
	prepared_key = aes_create_ctx(key);
	if (prepared_key == NULL)
		return BRP_ERR_OUT_OF_MEMORY;
	errcode = secured_recv_frm_prepkey(
			protocol, sec_mode, prepared_key, iv, cmd_code, resp_frm, timeout);
	aes_destroy_ctx(prepared_key);
	return errcode;
}


static brp_errcode cb_destroy(sec_protocol sec_prot)
{
	// Securely destroy session key
	aes_destroy_ctx(sec_prot->session_key);

	// Clear remaining data
	memset(sec_prot, 0, sizeof(struct sec_protocol_t));

	free(sec_prot);
	return BRP_OK;
}


static brp_errcode cb_open(sec_protocol sec_prot)
{
	brp_errcode errcode = redirect_open(sec_prot->p.base_protocol);
	if (errcode != BRP_OK)
		return errcode;

	if (sec_prot->sec_mode & BRP_SECMODE_STATELESS)
	{
		sec_prot->session_key = aes_create_ctx(sec_prot->base_key);
		if (sec_prot->session_key == NULL)
			return BRP_ERR_OUT_OF_MEMORY;
		return BRP_OK;
	}
	else
	{
		int req_auth_modes;
		brp_sec_key session_key_buf;
		memset(sec_prot->iv, 0, BRP_AES_BLOCK_SIZE);
		errcode = brp_mutual_authenticate(
				sec_prot->p.base_protocol,
				sec_prot->security_level,
				sec_prot->base_key,
				&req_auth_modes,
				session_key_buf);
		if (errcode != BRP_OK)
		{
			redirect_close(sec_prot->p.base_protocol);
			return errcode;
		}
		sec_prot->session_key = aes_create_ctx(session_key_buf);
		memset(session_key_buf, 0, BRP_AES_KEY_SIZE);  // remove key from stack

		if (sec_prot->session_key == NULL)
		{
			redirect_close(sec_prot->p.base_protocol);
			return BRP_ERR_OUT_OF_MEMORY;
		}

		return BRP_OK;
	}
}


static brp_errcode cb_send_frame(sec_protocol sec_prot)
{
	int mode;
	brp_time timeout;
	
	brp_frame_reader frm_rdr;
	brp_frame_reader_start(&frm_rdr, &sec_prot->p.send_frame);
	mode = (int) brp_frame_read_int8(&frm_rdr);
	sec_prot->last_cmd_code = (int) brp_frame_read_int16(&frm_rdr);
	timeout = (brp_time) brp_frame_read_int32(&frm_rdr);
	return secured_send_frm_prepkey(
			sec_prot->p.base_protocol,
			sec_prot->security_level,
			sec_prot->sec_mode,
			sec_prot->session_key,
			sec_prot->iv,
			sec_prot->last_cmd_code,
			frm_rdr.ptr,
			brp_frame_rest(&frm_rdr),
			timeout,
			mode);
}


static brp_errcode cb_recv_any_frame(sec_protocol sec_prot, brp_time timeout)
{
	return secured_recv_frm_prepkey(
			sec_prot->p.base_protocol,
			sec_prot->sec_mode,
			sec_prot->session_key,
			sec_prot->iv,
			sec_prot->last_cmd_code,
			&sec_prot->p.recv_frame,
			timeout);
}


brp_protocol brp_create_secure_channel(int security_level,
		brp_sec_key key, int sec_mode)
{
	sec_protocol new_protocol;
	if (key == NULL || security_level == 0 || security_level > 3)
		return NULL;
	
	new_protocol = (sec_protocol) brp_protocol_alloc(
		sizeof(struct sec_protocol_t), BRP_PROTID_SECURE_CHANNEL);
	if (new_protocol == NULL)
		return NULL;

	new_protocol->p.cb_destroy = (brp_cb_generic_t) cb_destroy;
	new_protocol->p.cb_open = (brp_cb_generic_t) cb_open;
	new_protocol->p.cb_send_frame = (brp_cb_generic_t) cb_send_frame;
	new_protocol->p.cb_recv_any_frame =
			(brp_cb_recv_any_frame_t) cb_recv_any_frame;
	new_protocol->security_level = security_level;
	memcpy(new_protocol->base_key, key, BRP_AES_BLOCK_SIZE);
	new_protocol->sec_mode = sec_mode;

	return (brp_protocol) new_protocol;
}
