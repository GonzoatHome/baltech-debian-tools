
#include "brp_lib/protocol.h"


brp_errcode redirect_open(brp_protocol protocol)
{
	brp_errcode errcode;

	if (protocol == NULL)
		return BRP_OK;

	if (protocol->opened)
		return BRP_OK;

	if (protocol->cb_open != NULL)
	{
		errcode = protocol->cb_open(protocol);
		if (errcode != BRP_OK)
			return errcode;
	}
	else if (protocol->base_protocol != NULL && !protocol->base_protocol->opened)
	{
		errcode = redirect_open(protocol->base_protocol);
		if (errcode != BRP_OK)
			return errcode;
	}

	protocol->opened = true;
	return BRP_OK;
}


brp_errcode redirect_close(brp_protocol protocol)
{
	brp_errcode errcode = BRP_OK;

	if (protocol == NULL)
		return BRP_OK;

	if (!protocol->opened)
		return BRP_OK;

	if (protocol->cb_close != NULL)
		errcode = protocol->cb_close(protocol);
	else if (protocol->base_protocol != NULL && protocol->base_protocol->opened)
		errcode = redirect_close(protocol->base_protocol);

	protocol->opened = false;

	return errcode;
}


brp_errcode brp_open(brp_protocol protocol)
{
	if (protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;
	return redirect_open(protocol);
}


brp_errcode brp_close(brp_protocol protocol)
{
	if (protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;
	return redirect_close(protocol);
}


brp_errcode brp_send_frame(brp_protocol protocol)
{
	brp_errcode errcode;

	if (protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;

	if (!protocol->opened)
		return BRP_ERR_CLOSED;

	if (protocol->cb_send_frame == NULL)
		return BRP_ERR_NOT_IMPLEMENTED;

	if (protocol->send_frame.act_size == -1)
		return BRP_ERR_OUT_OF_MEMORY;

	errcode = protocol->cb_send_frame(protocol);
	protocol->send_frame.act_size = 0;
	return errcode;
}


brp_errcode brp_recv_any_frame(brp_protocol protocol, brp_time timeout)
{
	brp_errcode errcode;

	if (protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;

	if (!protocol->opened)
		return BRP_ERR_CLOSED;

	if (protocol->cb_recv_any_frame == NULL)
		return BRP_ERR_NOT_IMPLEMENTED;

	protocol->recv_delay = -1;
	errcode = (*protocol->cb_recv_any_frame)(protocol, timeout);
	if (protocol->recv_delay == -1)
	{
		if (protocol->base_protocol == NULL)
			protocol->recv_delay = 0;
		else
			protocol->recv_delay = protocol->base_protocol->recv_delay;
	}
	return errcode;
}


static size_t fixsize_fmt_spec(brp_frame frame, const size_t * size)
{
	brp_frame_reader frame_rdr;

	brp_frame_read_start(&frame_rdr, frame);
	BRP_FMTSPEC_EXPECT_MORE(&frame_rdr, *size);
	brp_frame_skip(&frame_rdr, *size);
	BRP_FMTSPEC_EXPECT_END(&frame_rdr);

	return 0;
}


brp_errcode brp_recv_fix_frame(
		brp_protocol protocol, brp_time timeout, size_t frame_size)
{
	return brp_recv_frame(
		protocol, timeout, (brp_cb_fmt_spec_t)fixsize_fmt_spec, &frame_size);
}


brp_errcode brp_recv_frame(
	brp_protocol protocol, brp_time timeout,
	brp_cb_fmt_spec_t fmt_spec_callback, void * context)
{
	brp_errcode errcode;

	if (fmt_spec_callback == NULL)
		return brp_recv_any_frame(protocol, timeout);

	if (protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;

	if (!protocol->opened)
		return BRP_ERR_CLOSED;

	if (protocol->cb_recv_frame == NULL)
	{
		errcode = brp_recv_any_frame(protocol, timeout);
		if (errcode != BRP_OK)
			return errcode;

		if ((*fmt_spec_callback)(&protocol->recv_frame, context) != 0)
			return BRP_ERR_PAYLOAD_FORMAT;
	}
	else
	{
		protocol->recv_delay = -1;
		protocol->recv_frame.act_size = 0;

		errcode = (*protocol->cb_recv_frame)(
			protocol, timeout, fmt_spec_callback, context);

		if (protocol->recv_delay == -1)
		{
			if (protocol->base_protocol == NULL)
				protocol->recv_delay = 0;
			else
				protocol->recv_delay = protocol->base_protocol->recv_delay;
		}
	}
	return errcode;
}


brp_errcode brp_flush(brp_protocol protocol)
{
	if (protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;

	if (!protocol->opened)
		return BRP_ERR_CLOSED;

	if (protocol->cb_flush != NULL)
		return (protocol->cb_flush)(protocol);
	else if (protocol->base_protocol != NULL)
		return brp_flush(protocol->base_protocol);
	else
		return BRP_OK;
}


brp_errcode brp_get_io_id(brp_protocol protocol,
	char * * intf_name, brp_frame instance_id)
{
	if (protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;

	while (protocol->base_protocol != NULL)
		protocol = protocol->base_protocol;

	if (protocol->cb_get_id == NULL)
		return BRP_ERR_NOT_IMPLEMENTED;

	return protocol->cb_get_id(protocol, intf_name, instance_id);
}


brp_errcode brp_get_friendly_name(brp_protocol protocol, char** friendly_name)
{
	if (protocol == NULL || friendly_name == NULL)
		return BRP_ERR_INVALID_API_CALL;

	// Traverse protocol stack to find first non-NULL friendly_name
	while (protocol != NULL)
	{
		if (protocol->friendly_name != NULL)
		{
			*friendly_name = protocol->friendly_name;
			return BRP_OK;
		}
		protocol = protocol->base_protocol;
	}

	*friendly_name = NULL;
	return BRP_OK;
}


brp_protocol brp_protocol_alloc(size_t size, int protocol_id)
{
	brp_protocol protocol = malloc(size);
	if (protocol == NULL)
		return NULL;

	memset(protocol, 0, size);
	brp_frame_init(&protocol->recv_frame);
	brp_frame_init(&protocol->send_frame);
	protocol->protocol_id = protocol_id;

	return protocol;
}


void brp_protocol_free(brp_protocol protocol)
{
	brp_frame_deinit(&protocol->recv_frame);
	brp_frame_deinit(&protocol->send_frame);
	brp_mempool_free(&protocol->mempool);
	free(protocol);
}


brp_errcode brp_destroy(brp_protocol protocol)
{
	if (protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;

	if (protocol->opened)
	{
		brp_errcode errcode = brp_close(protocol);
		if (errcode != BRP_OK)
			return errcode;
	}


	if (protocol->cb_destroy != NULL)
		return protocol->cb_destroy(protocol);
	else
		return BRP_OK;
}
