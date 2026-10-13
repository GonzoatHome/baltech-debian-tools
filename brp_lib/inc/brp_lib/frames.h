/**
 * @file
 * Defines frame objects that allow dynamic sized buffers to be handled easily.
 *
 * This module is used throughout BRP library for creating, analysing and
 * passing data frames.
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __FRAMES_H__
#define __FRAMES_H__



#include "common.h"


#define BRP_FRAME_INVALID_SIZE    ((size_t) -1)


/**
 * @cond INTERNAL
 */


/**
 * An struct for managing dynamic sized buffers.
 *
 * This structure must be initialized via ``brp_frame_init(&frm)`` and
 * uninitialized via ``brp_frame_deinit(&frm).
 *
 * The members of this struct should never be accessed directly.
 */
typedef struct brp_frame_t
{
	brp_buf ptr;    ///< pointer to protocol data buffer
	size_t act_size;   ///< the required size of the buffer.
	size_t total_size; ///< the actual size reserved on heap
} * brp_frame;


/**
 * gets the current send frame pointer of a frame.
 */
#define BRP_FRAME_PTR(frm)    ((frm)->ptr)


/**
 * gets the current size of a frame.
 */
#define BRP_FRAME_SIZE(frm)    ((frm)->act_size)



/**
 * An internal struct for reading :brp_frame objects piece by piece.
 * See BRP_FRAME_READ_START()
 */
typedef struct brp_frame_reader_t
{
	brp_frame frame;  ///< pointer to :brp_frame that shall be iterated
	brp_buf ptr;      ///< pointer to current object
	bool err;         ///< set if an error during iterating occured
} brp_frame_reader;


/**
 * Iterates through a list of frame parts (see also brp_frame_reader_start())
 */
BRP_LIB void brp_frame_reader_start
(
	brp_frame_reader * frame_rdr, ///< pointer to frame iterator
	brp_frame frame               ///< pointer to frame that shall be iterated
);


/**
 * Iterates through a list of frame parts (see also brp_frame_reader_start())
 */
BRP_LIB brp_buf brp_frame_reader_next
(
	brp_frame_reader * frame_rdr, ///< pointer to frame iterator
	size_t block_size             ///< size of next block
);


/**
 * Initializes a brp_frame.
 */
BRP_LIB void brp_frame_init(brp_frame frame);


/**
 * DeInitializes a brp_frame.
 */
BRP_LIB void brp_frame_deinit(brp_frame frame);


/**
 * initiate writing a #brp_frame object.
 *
 * @code
 * BRP_FRAME_START(frame);
 * BRP_FRAME_WRITE(frame, data_ptr, data_len);
 * if (brp_frame_write_err(frame)) do_some_action_with_frame(frame);
 * @endcode
 */
BRP_LIB void brp_frame_write_start(brp_frame frame);


/**
 * checking if writing the #brp_frame since the
 * last #brp_frame_write_start failed.
 */
BRP_LIB bool brp_frame_write_err(brp_frame frame);


/**
 * creating #brp_frame (see #brp_frame_write_start )
 * from a C buffer
 */
BRP_LIB void brp_frame_write(brp_frame frame, brp_buf data, size_t data_len);


/**
 * creating #brp_frame (see #brp_frame_write_start )
 * from a C int (8 bit)
 */
BRP_LIB void brp_frame_write_int8(brp_frame frame, unsigned value);


/**
 * creating #brp_frame (see #brp_frame_write_start )
 * from a C int (16 bit)
 */
BRP_LIB void brp_frame_write_int16(brp_frame frame, unsigned value);


/**
 * creating #brp_frame (see #brp_frame_write_start )
 * from a C int (24 bit)
 */
BRP_LIB void brp_frame_write_int24(brp_frame frame, unsigned value);


/**
 * creating #brp_frame (see #brp_frame_write_start )
 * from a C int (32 bit)
 */
BRP_LIB void brp_frame_write_int32(brp_frame frame, unsigned value);


/**
 * Copies 'cnt' bytes from 'src_frame' to 'dst_frame'.
 * from another frame (via a frame reader)
 */
BRP_LIB void brp_frame_write_frm(
		brp_frame dst_frame, brp_frame_reader * src_frame_rdr, size_t cnt);


/**
 * Copies all remaining bytes from 'src_frame' to 'dst_frame'.
 * from the remaining bytes of another frame (via a frame reader)
 */
BRP_LIB void brp_frame_write_frm_rest(
		brp_frame dst_frame, brp_frame_reader * src_frame_rdr);


/**
 * Fills 'cnt' bytes of value 'val' into the end of the buffer
 */
BRP_LIB void brp_frame_write_fill(brp_frame frame, int val, size_t cnt);


/**
 * Ensures that the buffer referred to by a :brp_frame is big enough to hold
 * min_size more bytes.
 *
 * @attention The returned pointer is valid only until the next brp_frame_*()
 *            operation is done with the *frame* handle.
 *
 * @return pointer to buffer that was added to "frame". NULL if out of memory.
 */
BRP_LIB brp_buf brp_frame_write_buf
(
	brp_frame frame,    ///< pointer to dyn_buf, that shall be extended by
	                    ///  buffer
	size_t add_size     ///< size in byte, that shall be added to frame.
);


/**
 * reading frames.
 */
BRP_LIB void brp_frame_read_start(brp_frame_reader *frame_rdr, brp_frame frame);


/**
 * reading a part of fix length of a #brp_frame
 * (see #BRP_FRAME_READ_START )
 */
BRP_LIB void brp_frame_read(
		brp_frame_reader * frame_rdr, brp_buf data, size_t data_len);


/**
 * reading a part of variable length of a #brp_frame
 * (see #BRP_FRAME_READ_START )
 */
BRP_LIB void brp_frame_read_var(brp_frame_reader * frame_rdr, brp_buf data,
		size_t max_data_len, size_t * data_len_ptr);


/**
 * skipping cnt bytes in #brp_frame (see #BRP_FRAME_READ_START )
 */
BRP_LIB void brp_frame_skip(brp_frame_reader * frame_rdr, size_t cnt);


/**
 * reading a #brp_frame as 8 bit integer
 * (see #BRP_FRAME_READ_START )
 */
BRP_LIB unsigned brp_frame_read_int8(brp_frame_reader * frame_rdr);


/**
 * reading a #brp_frame as 16 bit integer
 * (see #BRP_FRAME_READ_START )
 */
BRP_LIB unsigned brp_frame_read_int16(brp_frame_reader * frame_rdr);


/**
 * reading a #brp_frame as 24 bit integer
 * (see #BRP_FRAME_READ_START )
 */
BRP_LIB unsigned brp_frame_read_int24(brp_frame_reader * frame_rdr);


/**
 * reading a #brp_frame as 32 bit integer
 * (see #BRP_FRAME_READ_START )
 */
BRP_LIB unsigned brp_frame_read_int32(brp_frame_reader * frame_rdr);


/**
 * reading a #brp_frame (see #BRP_FRAME_READ_START )
 * into another frame
 */
BRP_LIB void brp_frame_read_frm(
		brp_frame_reader * frame_rdr, brp_frame dst_frame, size_t cnt);


/**
 * reading a #brp_frame (see #BRP_FRAME_READ_START )
 * into another frame
 */
BRP_LIB void brp_frame_read_frm_rest(
		brp_frame_reader * frame_rdr, brp_frame dst_frame);


/**
 * true, if an error occured
 */
BRP_LIB bool brp_frame_read_err(brp_frame_reader * frame_rdr);


/**
 * returns the remaining bytes of frame_rdr
 */
BRP_LIB size_t brp_frame_rest(brp_frame_reader * frame_rdr);


/**
 * returns true, if frame_rdr was successfully (!) read to end
 */
BRP_LIB bool brp_frame_read_eof(brp_frame_reader * frame_rdr);


/**
 * returns difference in bytes between the two iterators or -1 on failure
 */
BRP_LIB size_t brp_frame_read_diff(
		brp_frame_reader * new_rdr, brp_frame_reader * old_rdr);
	 
	 
/**
 * unreads the specified number of bytes
 */
BRP_LIB void brp_frame_unread(brp_frame_reader * frame_rdr, size_t byte_cnt);


/**
 * @endcond
 */




#endif

/** @} */ // end of defgroup brp_lib
