
#include "brp_lib/commands.h"


brp_errcode brp_exec_Sys_GetInfo(brp_protocol protocol, char * fws)
{
	size_t resp_len;
	brp_errcode errcode = brp_exec_cmd(
		protocol,
		0x0004, NULL, 0,
		(brp_buf) fws, BRP_CMD_SYS_GETINFO_FWS_LEN, &resp_len,
		50);
	if (errcode != BRP_OK)
		return errcode;
	if (resp_len != BRP_CMD_SYS_GETINFO_FWS_LEN)
		return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}


brp_errcode brp_exec_AR_GetMessage(brp_protocol protocol, 
	int * msg_type, char * msg, size_t max_msg_len, size_t * msg_len)
{
	brp_errcode errcode;
	brp_frame_reader resp_rdr;
	int msg_type_val;
	size_t msg_len_val;

	errcode = brp_send_cmd(protocol, 0x0501, NULL, 0, 100, BRP_MODE_STD);
	if (errcode != BRP_OK)
		return errcode;

	errcode = brp_recv_any_frame(protocol, BRP_INFINITE);
	if (errcode != BRP_OK)
		return errcode;

	brp_frame_read_start(&resp_rdr, &protocol->recv_frame);
	msg_type_val = brp_frame_read_int8(&resp_rdr);
	msg_len_val = brp_frame_read_int8(&resp_rdr);
	brp_frame_read(&resp_rdr, (brp_buf) msg, (size_t) msg_len_val);
	if (! brp_frame_read_eof(&resp_rdr))
		return BRP_ERR_PAYLOAD_FORMAT;

	if (msg_type != NULL)
		*msg_type = msg_type_val;
	if (msg_len != NULL)
		*msg_len = msg_len_val;
	return BRP_OK;
}


brp_errcode brp_exec_Sys_CfgSetValue(
	brp_protocol protocol, int key, int value, brp_buf data, size_t data_len)
{
	unsigned char params[4 + 0x80];
	if (data_len > 0x80)
		return BRP_ERR_INVALID_API_CALL;

	params[0] = (unsigned char)(key >> 8);
	params[1] = (unsigned char) key;
	params[2] = (unsigned char) value;
	params[3] = (unsigned char) data_len;
	memcpy(params + 4, data, data_len);
	return brp_exec_cmd(protocol, 0x0009, params, 4+data_len,
	                    NULL, 0, NULL, 2000);
}


brp_errcode brp_exec_Sys_CfgGetValue(
	brp_protocol protocol, int key, int value, 
	brp_buf data, size_t max_data_len, size_t * data_len)
{
	unsigned char params[3], resp[1 + 0x80];
	brp_errcode errcode;
	size_t resp_len;

	params[0] = (unsigned char) (key >> 8);
	params[1] = (unsigned char) (key);
	params[2] = (unsigned char) (value);
	errcode = brp_exec_cmd(protocol, 0x0008, params, 3,
	                       resp, sizeof(resp), &resp_len, 100);
	if (errcode != BRP_OK)
		return errcode;

	if (resp_len < 1)
		return BRP_ERR_PAYLOAD_FORMAT;
	if (resp[0] != resp_len - 1)
		return BRP_ERR_PAYLOAD_FORMAT;
	if (resp[0] > max_data_len)
		return BRP_ERR_INVALID_API_CALL;
	if (data == NULL  &&  max_data_len != 0)
		return BRP_ERR_INVALID_API_CALL;
	if (data == NULL)
	{
		if (resp[0] != 0)
			return BRP_ERR_PAYLOAD_FORMAT;
		else
			return BRP_OK;
	}
	if (data_len != NULL)
		*data_len = resp[0];
	else
		if (resp[0] != max_data_len)
			return BRP_ERR_PAYLOAD_FORMAT;

	memcpy(data, resp+1, resp[0]);
	return BRP_OK;
}
