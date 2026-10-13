
#include "brp_lib/brp_protocol.h"
#include <stdlib.h>


#define TIMEOUT_CMDWORK                     100
#define TIMEOUT_BREAKCMD                    500

// bit definitions of CMDCTRL byte
#define SENDFRAME_CTRL_RFU1                0x80
#define SENDFRAME_CTRL_RFU2                0x40
#define SENDFRAME_CTRL_CHKSUM_MASK         0x30
#define SENDFRAME_CTRL_LEN16               0x08
#define SENDFRAME_CTRL_DEVCODE             0x04
#define SENDFRAME_CTRL_CONTMODE            0x02
#define SENDFRAME_CTRL_REPMODE             0x01

// bit definitions of CTRLFLAGS byte
#define RECVFRAME_CTRL_STATUSCODE          0x80
#define RECVFRAME_CTRL_BOOTSTATUS          0x40
#define RECVFRAME_CTRL_CHKSUM_MASK         0x30
#define RECVFRAME_CTRL_LEN16               0x08
#define RECVFRAME_CTRL_DEVCODE             0x04
#define RECVFRAME_CTRL_CONTMODE            0x02
#define RECVFRAME_CTRL_REPMODE             0x01


typedef struct _brp_protocol_t {
	struct brp_protocol_t p;
	bool busy, force_reset;
	int running_cmd_code;
	int running_mode;
	brp_time rest_cmd_timeout;
	brp_errcode status_code;
	brp_time rest_cmdwork_timeout;
} * _brp_protocol;


struct recv_context_t {
	int cmd_code;
	brp_errcode errcode_device;
	brp_frame payload;
	int stop_mode;
} ;


brp_errcode brp_send_cmd(brp_protocol protocol, int cmd_code, brp_buf param_buf,
                         size_t param_len, brp_time cmd_timeout, int mode)
{
	brp_frame frm;
	if (protocol == NULL  ||
		(param_len > 0  &&  param_buf == NULL))
		return BRP_ERR_INVALID_API_CALL;

	frm = &protocol->send_frame;
	brp_frame_write_start(frm);
	brp_frame_write_int8(frm, (unsigned) mode);
	brp_frame_write_int16(frm, (unsigned) cmd_code);
	brp_frame_write_int32(frm, (unsigned) cmd_timeout);
	brp_frame_write(frm, param_buf, param_len);
	if (brp_frame_write_err(frm))
		return BRP_ERR_OUT_OF_MEMORY;
	return brp_send_frame(protocol);
}


brp_errcode brp_recv_cmd(brp_protocol protocol,
                         brp_buf resp_buf, size_t max_resp_len,
                         size_t * resp_len, brp_time timeout)
{
	brp_errcode errcode;
	brp_frame_reader frm_rdr;

	if (protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;

	errcode = brp_recv_any_frame(protocol, timeout);
	if (errcode != BRP_OK)
		return errcode;

	brp_frame_read_start(&frm_rdr, &protocol->recv_frame);

	if (resp_len == NULL)
	{
		brp_frame_read(&frm_rdr, resp_buf, max_resp_len);
		if (! brp_frame_read_eof(&frm_rdr))
			return BRP_ERR_PAYLOAD_FORMAT;
	}
	else
	{
		size_t act_resp_len;
		brp_frame_read_var(&frm_rdr, resp_buf, max_resp_len, &act_resp_len);
		*resp_len = (int) act_resp_len;
		if (brp_frame_read_err(&frm_rdr))
			return BRP_ERR_FRAMEFORMAT;
		if (! brp_frame_read_eof(&frm_rdr))
			return BRP_ERR_BUFFER_OVERFLOW;
	}

	return BRP_OK;
}


brp_errcode brp_break_cmd(brp_protocol protocol)
{
	brp_errcode errcode;
	brp_frame frm;

	if (protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;

	frm = &protocol->send_frame;
	brp_frame_write_start(frm);
	brp_frame_write_int8(frm, BRP_MODE_BREAK);
	brp_frame_write_int16(frm, 0);
	brp_frame_write_int32(frm, 0);
	if (brp_frame_write_err(frm))
		return BRP_ERR_OUT_OF_MEMORY;
	errcode = brp_send_frame(protocol);
	if (errcode != BRP_OK)
		return errcode;

	return BRP_OK;
}


brp_errcode brp_exec_cmd(brp_protocol protocol,
	int cmd_code, brp_buf param_buf, size_t param_len,
	brp_buf resp_buf, size_t max_resp_len, size_t * resp_len,
	brp_time cmd_timeout)
{
	brp_errcode errcode;

	errcode = brp_send_cmd(protocol, cmd_code, param_buf, param_len,
	                       cmd_timeout, BRP_MODE_STD);
	if (errcode != BRP_OK)
		return errcode;

	return brp_recv_cmd(protocol, resp_buf, max_resp_len, resp_len,
	                    BRP_INFINITE);
}


static brp_errcode send_frame(_brp_protocol protocol)
{
	brp_errcode errcode;
	int mode, cmd_code;
	size_t param_len;
	brp_time cmd_timeout, cmdwork_timeout = BRP_INFINITE;
	brp_frame_reader in_frm_rdr;
	brp_frame out_frm = &protocol->p.base_protocol->send_frame;
	bool on_success_is_busy;

	brp_frame_read_start(&in_frm_rdr, &protocol->p.send_frame);
	mode = brp_frame_read_int8(&in_frm_rdr);
	cmd_code = brp_frame_read_int16(&in_frm_rdr);
	cmd_timeout = (brp_time) brp_frame_read_int32(&in_frm_rdr);
	param_len = brp_frame_rest(&in_frm_rdr);
	if (brp_frame_read_err(&in_frm_rdr))
		return BRP_ERR_CALLED_INVALID_FRAME;

	if (mode == BRP_MODE_BREAK)
	{
		if (protocol->busy  &&  protocol->running_mode == BRP_MODE_STD)
			return BRP_ERR_INVALID_API_CALL;

		cmd_code = 0xFFFF;
		cmd_timeout = 0;
		mode = BRP_MODE_STD;
		protocol->force_reset = true;
		on_success_is_busy = false;
	}
	else
	{
		if (in_frm_rdr.err)
			return BRP_ERR_INVALID_API_CALL;
		if (protocol->busy)
			return BRP_ERR_INVALID_API_CALL;

		if (mode == BRP_MODE_STD)
			;
		else if (mode == BRP_MODE_CONTINUOUS  ||  mode == BRP_MODE_REPEAT)
		{
			cmdwork_timeout = TIMEOUT_CMDWORK;
			cmd_timeout = BRP_INFINITE;
		}
		else
			return BRP_ERR_INVALID_API_CALL;

		if (protocol->force_reset)
		{
			errcode = brp_flush(protocol->p.base_protocol);
			if (errcode != BRP_OK)
				return errcode;
			protocol->force_reset = false;
		}

		on_success_is_busy = true;
	}

	brp_frame_write_start(out_frm);
	brp_frame_write_int8(
		out_frm,
		(unsigned)
	    SENDFRAME_CTRL_DEVCODE |
	    SENDFRAME_CTRL_LEN16 |
	    (mode == BRP_MODE_CONTINUOUS ? RECVFRAME_CTRL_CONTMODE : 0) |
	    (mode == BRP_MODE_REPEAT ? RECVFRAME_CTRL_REPMODE : 0));
	brp_frame_write_int16(out_frm, (unsigned) cmd_code);
	brp_frame_write_int8(out_frm, (unsigned) param_len);
	brp_frame_write_int8(out_frm, (unsigned) param_len >> 8);
	brp_frame_write_frm_rest(out_frm, &in_frm_rdr);
	if (brp_frame_write_err(out_frm))
		return BRP_ERR_OUT_OF_MEMORY;

	errcode = brp_send_frame(protocol->p.base_protocol);
	if (errcode != BRP_OK)
	{
		protocol->busy = false;
		protocol->force_reset = true;
		return errcode;
	}

	protocol->busy = on_success_is_busy;
	protocol->running_cmd_code = cmd_code;
	protocol->rest_cmd_timeout = cmd_timeout;
	protocol->running_mode = mode;
	protocol->rest_cmdwork_timeout = cmdwork_timeout;
	return BRP_OK;
}


static size_t brp_fmt_spec(brp_frame in_frame, struct recv_context_t * recv_ctx)
{
	brp_frame_reader in_frm_rdr;
	int flag_byte, payload_len_hi, payload_len_lo;
	size_t payload_len;

	brp_frame_read_start(&in_frm_rdr, in_frame);

	/// read header flag byte
	BRP_FMTSPEC_EXPECT_MORE(&in_frm_rdr, 1);
	flag_byte = brp_frame_read_int8(&in_frm_rdr);
	if ( ! (flag_byte & RECVFRAME_CTRL_DEVCODE) ||
	       (flag_byte & RECVFRAME_CTRL_CHKSUM_MASK))
		return 0;
	switch (flag_byte & (RECVFRAME_CTRL_CONTMODE | RECVFRAME_CTRL_REPMODE))
	{
		case RECVFRAME_CTRL_CONTMODE:
			recv_ctx->stop_mode = BRP_MODE_CONTINUOUS;
			break;
		case RECVFRAME_CTRL_REPMODE:
			recv_ctx->stop_mode = BRP_MODE_REPEAT;
			break;
		default:
			recv_ctx->stop_mode = BRP_MODE_STD;
	}

	/// read header
	BRP_FMTSPEC_EXPECT_MORE(
			&in_frm_rdr, (size_t) ((flag_byte & RECVFRAME_CTRL_LEN16) ? 4 : 3));
	recv_ctx->cmd_code = brp_frame_read_int16(&in_frm_rdr);
	payload_len_lo = brp_frame_read_int8(&in_frm_rdr);
	if (flag_byte & RECVFRAME_CTRL_LEN16)
		payload_len_hi = brp_frame_read_int8(&in_frm_rdr);
	else
		payload_len_hi = 0;
	payload_len = (size_t) (payload_len_hi << 8) | payload_len_lo;

	/// read statuscode/params
	BRP_FMTSPEC_EXPECT_MORE(&in_frm_rdr, payload_len);
	if (flag_byte & RECVFRAME_CTRL_STATUSCODE)
	{
		int status_code;
		if (payload_len == 0)
			return 0;
		status_code = brp_frame_read_int8(&in_frm_rdr);
		payload_len--;

		switch (status_code)
		{
			case 0x41:
				recv_ctx->errcode_device = BRP_ERR_UNSUPPORTED_COMMAND;
				break;
			case 0x42:
				recv_ctx->errcode_device = BRP_ERR_COMMAND_DENIED;
				break;
			default:
				recv_ctx->errcode_device =
					BRP_ERR_STATUS(recv_ctx->cmd_code, status_code);
				break;
		}
	}
	else
		recv_ctx->errcode_device = BRP_OK;
	brp_frame_read_frm(&in_frm_rdr, recv_ctx->payload, payload_len);

	BRP_FMTSPEC_EXPECT_END(&in_frm_rdr);

	return 0;
}


static brp_errcode recv_any_frame(_brp_protocol protocol, brp_time timeout)
{
	brp_errcode errcode;
	struct recv_context_t recv_ctx;
	brp_time recv_delay;

	if (!protocol->busy  ||  protocol->p.base_protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;
	protocol->force_reset = true;
	protocol->busy = false;

	protocol->p.recv_delay = 0;
	while (protocol->p.recv_delay < (brp_time) timeout)
	{
		recv_ctx.payload = &protocol->p.recv_frame;
		errcode = brp_recv_frame(
			protocol->p.base_protocol,
			min(timeout, protocol->rest_cmd_timeout),
			(brp_cb_fmt_spec_t) brp_fmt_spec,
			&recv_ctx);
		if (brp_frame_write_err(recv_ctx.payload))
			return BRP_ERR_OUT_OF_MEMORY;

		recv_delay = protocol->p.base_protocol->recv_delay;
		protocol->p.recv_delay += recv_delay;
		BRP_TIME_SUBTRACT(protocol->rest_cmdwork_timeout, recv_delay);
		BRP_TIME_SUBTRACT(protocol->rest_cmd_timeout, recv_delay);
		BRP_TIME_SUBTRACT(timeout, recv_delay);
		if (errcode == BRP_ERR_TIMEOUT)
		{
			if (protocol->rest_cmd_timeout == 0)
				return BRP_ERR_CMD_TIMEOUT;
			else
			{
				protocol->force_reset = false;
				protocol->busy = true;
				return BRP_ERR_TIMEOUT;
			}
		}

		if (errcode == BRP_ERR_PAYLOAD_FORMAT)
			return BRP_ERR_FRAMEFORMAT;
		if (errcode != BRP_OK)
			return errcode;
		if (recv_ctx.cmd_code != protocol->running_cmd_code)
			return BRP_ERR_UNEXPECTED_FRAME;
		if (recv_ctx.stop_mode != BRP_MODE_STD  &&
		    recv_ctx.stop_mode != protocol->running_mode)
			return BRP_ERR_UNEXPECTED_FRAME;

		// stop at any other status than CMD_WORK
		if (recv_ctx.errcode_device != BRP_ERR_STATUS(recv_ctx.cmd_code, 0x40))
			break;

		if (protocol->running_mode == BRP_MODE_STD)
			return BRP_ERR_UNEXPECTED_FRAME;
	}

	if (protocol->running_mode == BRP_MODE_REPEAT  &&
	    recv_ctx.stop_mode == BRP_MODE_STD)
		protocol->busy = true;
	protocol->force_reset = false;
	return recv_ctx.errcode_device;
}


brp_errcode destroy(_brp_protocol protocol)
{
	brp_protocol_free(&protocol->p);
	return BRP_OK;
}


brp_protocol brp_create_brp(void)
{
	_brp_protocol protocol = (_brp_protocol) brp_protocol_alloc(
		sizeof(struct _brp_protocol_t), BRP_PROTID_BRP);
	if (protocol == NULL)
		return NULL;

	protocol->p.cb_send_frame = (brp_cb_generic_t) send_frame;
	protocol->p.cb_recv_any_frame = (brp_cb_recv_any_frame_t) recv_any_frame;
	protocol->p.cb_destroy = (brp_cb_generic_t) destroy;
	protocol->force_reset = true;

	return (brp_protocol) protocol;
}
