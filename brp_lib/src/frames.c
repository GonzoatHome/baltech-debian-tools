
#include "brp_lib/frames.h"



brp_buf brp_frame_write_buf(brp_frame frame, size_t add_size)
{
	size_t new_size;
	brp_buf new_buf;

	if (frame->act_size == BRP_FRAME_INVALID_SIZE)
		return NULL;

	new_size = frame->act_size + add_size;

	if (new_size > frame->total_size  ||  frame->ptr == NULL)
	{
		// find next greater power of 2 for the size of the new buffer
		if (frame->total_size == 0)
			frame->total_size = 1;
		while (new_size > frame->total_size)
			frame->total_size <<= 1;

		frame->ptr = realloc(frame->ptr, frame->total_size);
		if (frame->ptr == NULL)
		{
			frame->total_size = 0;
			frame->act_size = BRP_FRAME_INVALID_SIZE;
			return NULL;
		}
	}

	new_buf = frame->ptr + frame->act_size;
	frame->act_size = new_size;
	return new_buf;
}


void brp_frame_reader_start(brp_frame_reader * frame_rdr, brp_frame frame)
{
	frame_rdr->frame = frame;
	frame_rdr->ptr = frame->ptr;
	frame_rdr->err = false;
}


brp_buf brp_frame_reader_next(brp_frame_reader * frame_rdr, size_t block_size)
{
	brp_buf cur_ptr = frame_rdr->ptr;

	if (frame_rdr->err  ||  block_size == BRP_FRAME_INVALID_SIZE)
		return NULL;

	else if (frame_rdr->frame->act_size == 0)
		if (block_size == 0)
		{
			static unsigned char dummy;
			return &dummy;
		}
		else
		{
			frame_rdr->err = true;
			return NULL;
		}

	else if ((cur_ptr - frame_rdr->frame->ptr) + block_size >
	         frame_rdr->frame->act_size)
	{
		frame_rdr->err = true;
		return NULL;
	}

	frame_rdr->ptr += block_size;
	return cur_ptr;
}


void brp_frame_init(brp_frame frame)
{
	memset(frame, 0, sizeof(struct brp_frame_t));
}


void brp_frame_deinit(brp_frame frame)
{
	free((frame)->ptr);
	(frame)->ptr = NULL;
}


void brp_frame_write_start(brp_frame frame)
{
	(frame)->act_size = 0;
}


bool brp_frame_write_err(brp_frame frame)
{
	return frame->act_size == BRP_FRAME_INVALID_SIZE;
}


void brp_frame_write(brp_frame frame, brp_buf data, size_t data_len)
{
	brp_buf new_buf = brp_frame_write_buf(frame, data_len);
	if (new_buf != NULL)
		memcpy(new_buf, data, data_len);
}


void brp_frame_write_int8(brp_frame frame, unsigned value)
{
	brp_buf new_buf = brp_frame_write_buf(frame, 1);
	if (new_buf != NULL)
		new_buf[0] = (unsigned char) (value);
}


void brp_frame_write_int16(brp_frame frame, unsigned value)
{
	brp_buf new_buf = brp_frame_write_buf(frame, 2);
	if (new_buf != NULL) {
		new_buf[0] = (unsigned char) ((value) >> 8);
		new_buf[1] = (unsigned char) ((value) >> 0);
	}
}


void brp_frame_write_int24(brp_frame frame, unsigned value)
{
	brp_buf new_buf = brp_frame_write_buf(frame, 3);
	if (new_buf != NULL) {
		new_buf[0] = (unsigned char) ((value) >> 16);
		new_buf[1] = (unsigned char) ((value) >> 8);
		new_buf[2] = (unsigned char) ((value) >> 0);
	}
}


void brp_frame_write_int32(brp_frame frame, unsigned value)
{
	brp_buf new_buf = brp_frame_write_buf(frame, 4);
	if (new_buf != NULL) {
		new_buf[0] = (unsigned char) ((value) >> 24);
		new_buf[1] = (unsigned char) ((value) >> 16);
		new_buf[2] = (unsigned char) ((value) >> 8);
		new_buf[3] = (unsigned char) ((value) >> 0);
	}
}


void brp_frame_write_frm(
		brp_frame dst_frame, brp_frame_reader * src_frame_rdr, size_t cnt)
{
	brp_buf src_buf = brp_frame_reader_next(src_frame_rdr, cnt);
	if (src_buf != NULL)
	{
		brp_buf dst_buf = brp_frame_write_buf(dst_frame, cnt);
		if (dst_buf != NULL)
			memcpy(dst_buf, src_buf, cnt);
		else
			src_frame_rdr->ptr = src_buf; /* restore reader on out-of-mem */
	}
	else
		dst_frame->act_size = BRP_FRAME_INVALID_SIZE;
}


void brp_frame_write_frm_rest(
		brp_frame dst_frame, brp_frame_reader * src_frame_rdr)
{
	brp_frame_write_frm(dst_frame, src_frame_rdr,brp_frame_rest(src_frame_rdr));
}


void brp_frame_write_fill(brp_frame frame, int val, size_t cnt)
{
	brp_buf new_buf = brp_frame_write_buf(frame, cnt);
	if (new_buf != NULL  &&  cnt > 0)
		memset(new_buf, val, cnt);
}


void brp_frame_read_start(brp_frame_reader *frame_rdr, brp_frame frame)
{
	brp_frame_reader_start(frame_rdr, frame);
}


void brp_frame_read(
		brp_frame_reader * frame_rdr, brp_buf data, size_t data_len)
{
	brp_buf buf = brp_frame_reader_next(frame_rdr, data_len);
	if (buf != NULL)
		memcpy(data, buf, data_len);
}


void brp_frame_read_var(brp_frame_reader * frame_rdr, brp_buf data,
		size_t max_data_len, size_t * data_len_ptr)
{
	*data_len_ptr = min(brp_frame_rest(frame_rdr), (int) max_data_len);
	brp_frame_read(frame_rdr, data, *data_len_ptr);
}


void brp_frame_skip(brp_frame_reader * frame_rdr, size_t cnt)
{
	brp_frame_reader_next(frame_rdr, cnt);
}


unsigned brp_frame_read_int8(brp_frame_reader * frame_rdr)
{
	brp_buf buf = brp_frame_reader_next(frame_rdr, 1);
	if (buf != NULL)
		return buf[0];
	else
		return 0;
}


unsigned brp_frame_read_int16(brp_frame_reader * frame_rdr)
{
	brp_buf buf = brp_frame_reader_next(frame_rdr, 2);
	if (buf != NULL)
		return (((unsigned) buf[0]) << 8)
			   | (((unsigned) buf[1]) << 0);
	else
		return 0;
}


unsigned brp_frame_read_int24(brp_frame_reader * frame_rdr)
{
	brp_buf buf = brp_frame_reader_next(frame_rdr, 3);
	if (buf != NULL)
		return (((unsigned) buf[0]) << 16)
			   | (((unsigned) buf[1]) << 8)
			   | (((unsigned) buf[2]) << 0);
	else
		return 0;
}


unsigned brp_frame_read_int32(brp_frame_reader * frame_rdr)
{
	brp_buf buf = brp_frame_reader_next(frame_rdr, 4);
	if (buf != NULL)
		return (((unsigned) buf[0]) << 24)
			   | (((unsigned) buf[1]) << 16)
			   | (((unsigned) buf[2]) << 8)
			   | (((unsigned) buf[3]) << 0);
	else
		return 0;
}


void brp_frame_read_frm(
		brp_frame_reader * frame_rdr, brp_frame dst_frame, size_t cnt)
{
	brp_frame_write_start(dst_frame);
	brp_frame_write_frm(dst_frame, frame_rdr, cnt);
}


void brp_frame_read_frm_rest(brp_frame_reader * frame_rdr, brp_frame dst_frame)
{
	brp_frame_write_start(dst_frame);
	brp_frame_write_frm_rest(dst_frame, frame_rdr);
}


bool brp_frame_read_err(brp_frame_reader * frame_rdr)
{
	return frame_rdr->err;
}


size_t brp_frame_rest(brp_frame_reader * frame_rdr)
{
	if (brp_frame_read_err(frame_rdr))
		return 0;
	else if ((frame_rdr)->frame->act_size == 0)
		return 0;
	else
	 	return (frame_rdr->frame->ptr + frame_rdr->frame->act_size
	 	        - frame_rdr->ptr);
}


bool brp_frame_read_eof(brp_frame_reader * frame_rdr)
{
	return !brp_frame_read_err(frame_rdr)  &&  brp_frame_rest(frame_rdr) == 0;
}


size_t brp_frame_read_diff(
		brp_frame_reader * new_rdr, brp_frame_reader * old_rdr)
{
	if (!brp_frame_read_err(new_rdr) && !brp_frame_read_err(old_rdr) &&
	   (new_rdr)->frame == (old_rdr)->frame)
	 	return ((new_rdr)->ptr - (old_rdr)->ptr);
	else
		return BRP_FRAME_INVALID_SIZE;
}


void brp_frame_unread(brp_frame_reader * frame_rdr, size_t byte_cnt)
{
	if (!brp_frame_read_err(frame_rdr))
		frame_rdr->ptr -= byte_cnt;
}
