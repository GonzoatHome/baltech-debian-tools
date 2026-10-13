#include <stdio.h>
#include "reader_updater.h"
#include "baltech_sdk.h"


#define BASE_RECONNECT_TIMEOUT  10000


static int hex_digit_value(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	return -1;
}


brp_errcode brp_get_update_blob_from_string(
	const char * hex_str,
	size_t hex_len,
	brp_buf * blob,
	size_t * blob_size,
	brp_mempool * mempool)
{
	size_t pos = 0;
	size_t buf_capacity = 0x1000;
	brp_buf buf;

	if (hex_str == NULL || blob == NULL || blob_size == NULL || mempool == NULL)
		return BRP_ERR_INVALID_API_CALL;

	/* Skip header lines until empty line (two consecutive newlines) */
	while (pos < hex_len)
	{
		/* Find end of current line */
		size_t line_start = pos;
		while (pos < hex_len && hex_str[pos] != '\n')
			pos++;

		/* Check if line is empty (only whitespace before newline) */
		{
			bool is_empty = true;
			size_t i;
			for (i = line_start; i < pos; i++)
			{
				if (hex_str[i] != '\r' && hex_str[i] != ' ' && hex_str[i] != '\t')
				{
					is_empty = false;
					break;
				}
			}
			if (pos < hex_len)
				pos++;  /* skip the \n */
			if (is_empty)
				break;
		}
	}

	/* Allocate initial buffer */
	buf = brp_mempool_create_buf(mempool, buf_capacity);
	if (buf == NULL)
		return BRP_ERR_OUT_OF_MEMORY;

	/* Decode hex pairs from payload */
	*blob_size = 0;
	while (pos < hex_len)
	{
		int hi, lo;
		char c = hex_str[pos];

		/* Skip whitespace and newlines */
		if (c == '\n' || c == '\r' || c == ' ' || c == '\t')
		{
			pos++;
			continue;
		}

		hi = hex_digit_value(c);
		if (hi < 0)
			return BRP_ERR_PAYLOAD_FORMAT;
		pos++;

		if (pos >= hex_len)
			return BRP_ERR_PAYLOAD_FORMAT;

		lo = hex_digit_value(hex_str[pos]);
		if (lo < 0)
			return BRP_ERR_PAYLOAD_FORMAT;
		pos++;

		/* Grow buffer if needed */
		if (*blob_size >= buf_capacity)
		{
			buf_capacity *= 2;
			buf = brp_mempool_resize_buf(buf, buf_capacity);
			if (buf == NULL)
				return BRP_ERR_OUT_OF_MEMORY;
		}

		buf[*blob_size] = (unsigned char)((hi << 4) | lo);
		(*blob_size)++;
	}

	/* Trim buffer to actual size */
	if (*blob_size > 0)
	{
		buf = brp_mempool_resize_buf(buf, *blob_size);
		if (buf == NULL)
			return BRP_ERR_OUT_OF_MEMORY;
	}

	*blob = buf;
	return BRP_OK;
}



static brp_errcode reconnect_reader(
	brp_protocol dev,
	unsigned timeout)
{
	brp_time starttime, now;
	brp_errcode errcode;
	bool dev_was_unregistered = false;

	errcode = brp_close(dev);
	if (errcode != BRP_OK)
		return errcode;

	starttime = brp_get_time();
	do
	{
		now = brp_get_time();
		if (now - starttime > BASE_RECONNECT_TIMEOUT + timeout)
			return BRP_ERR_TIMEOUT;

		errcode = brp_open(dev);
		if (errcode != BRP_OK)
			dev_was_unregistered = true;
		else
		{
			if (dev_was_unregistered)
				return BRP_OK;
			else
				brp_close(dev);
		}
	}
	while (!(dev_was_unregistered && errcode == BRP_OK));

	return BRP_OK;
}


brp_errcode brp_update_reader_from_blob(
	brp_protocol dev,
	brp_buf blob,
	size_t blob_size,
	brp_update_progress_cb progress_cb)
{
	unsigned req_adr, req_len;
	unsigned transferred = 0;
	unsigned estimated_total = 0;
	unsigned time_overhead = 0;
	brp_errcode errcode;

	if (dev == NULL || blob == NULL)
		return BRP_ERR_INVALID_API_CALL;

	errcode = brp_Main_Bf3UploadStart((brp_Main_Bf3UploadStart_t){
		dev,
		.ReqDataAdr = &req_adr,
		.ReqDataLen = &req_len
	});
	if (errcode != BRP_OK)
		return errcode;

	for (;;)
	{
		bool reconnect = false;
		bool cont = false;
		unsigned next_adr = 0, next_len = 0;
		bool contains_estimation = false;
		bool contains_reconnect_timeout = false;
		unsigned reconnect_timeout = 0;
		unsigned est_bytes = 0, est_overhead = 0;

		if ((size_t)(req_adr + req_len) > blob_size)
			return BRP_ERR_INVALID_API_CALL;

		transferred += req_len;

		errcode = brp_Main_Bf3UploadContinue((brp_Main_Bf3UploadContinue_t){
			dev,
			.DataAdr = req_adr,
			.Data = blob + req_adr,
			.Data_len = req_len,
			.Reconnect = &reconnect,
			.Continue = &cont,
			.ReqDataAdr = &next_adr,
			.ReqDataLen = &next_len,
			.ContainsEstimation = &contains_estimation,
			.ContainsReconnectRetryTimeout = &contains_reconnect_timeout,
			.ReconnectRetryTimeout = &reconnect_timeout,
			.EstimatedNumberOfBytes = &est_bytes,
			.EstimatedTimeOverhead = &est_overhead
		});

		if (errcode == BRP_Main_ErrAlreadyUpToDate)
			return BRP_OK;
		if (errcode != BRP_OK)
			return errcode;

		if (contains_estimation)
		{
			estimated_total = est_bytes;
			time_overhead = est_overhead;
		}

		if (progress_cb != NULL)
		{
			unsigned progress_percent = 0;
			if (estimated_total > 0)
			{
				progress_percent = 100 * transferred / estimated_total;
				if (progress_percent > 100)
					progress_percent = 100;
			}
			progress_cb(transferred, estimated_total,
				progress_percent, time_overhead, reconnect);
		}

		if (reconnect)
		{
			unsigned timeout = contains_reconnect_timeout
				? reconnect_timeout : 0;
			errcode = reconnect_reader(dev, timeout);
			if (errcode != BRP_OK)
				return errcode;
		}

		if (!cont)
			break;

		req_adr = next_adr;
		req_len = next_len;
	}

	return BRP_OK;
}


brp_errcode brp_update_reader(
	brp_protocol dev,
	const char * filepath,
	brp_update_progress_cb progress_cb)
{
	FILE * file;
	long file_size;
	brp_buf content;
	brp_buf blob;
	size_t blob_size;
	brp_errcode errcode;
	brp_mempool mempool = NULL;

	if (dev == NULL || filepath == NULL)
		return BRP_ERR_INVALID_API_CALL;

	file = fopen(filepath, "rb");
	if (file == NULL)
		return BRP_ERR_OPEN_IO;

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	content = brp_mempool_create_buf(&mempool, file_size);
	if (content == NULL)
	{
		fclose(file);
		return BRP_ERR_OUT_OF_MEMORY;
	}

	if ((long)fread(content, 1, file_size, file) != file_size)
	{
		fclose(file);
		brp_mempool_free(&mempool);
		return BRP_ERR_OPEN_IO;
	}
	fclose(file);

	errcode = brp_get_update_blob_from_string(
		(const char *)content, (size_t)file_size, &blob, &blob_size, &mempool);
	if (errcode != BRP_OK)
	{
		brp_mempool_free(&mempool);
		return errcode;
	}

	errcode = brp_update_reader_from_blob(dev, blob, blob_size, progress_cb);
	brp_mempool_free(&mempool);
	return errcode;
}
