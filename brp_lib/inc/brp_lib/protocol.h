/**
 * @file
 * This file primarly defines the common part of all protocol's data
 * structures (:brp_protocol_t) and API functions to directly interact with
 * protocols (that usually are only required for plugin developers).
 *
 * The functions in this module are working as a thin layer on top of each
 * :brp_protocol_t. As every protocol provides a stream like interface this
 * layer handles the necessary buffering to avoid that each protocol
 * implements its own mechanisms. Furthermore these functions do some
 * basic security checks to avoid invalid API calls.
 *
 * Please notice that all function are starting with a leading brp_*, which
 * means, that they are ony meant for developers of extension protocols.
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


#include "common.h"
#include "errorcodes.h"
#include "protocol_ids.h"
#include "frames.h"
#include "mempool.h"


/**
 * This is a generic handle of a protocol
 */
typedef struct brp_protocol_t * brp_protocol;


/**
 * identifies the layer of a composite protocol stack
 * (see brp_create() or brp_create_composite().
 * has to be one of BRP_LAYERID_*, i.e. #BRP_LAYERID_IO.
 */
typedef int brp_layer_id;


/**
 * @cond INTERNAL
 */


/**
 * Prototype for callbacks in :brp_protocol.
 */
typedef brp_errcode (*brp_cb_generic_t)
(
	brp_protocol protocol
);


/**
 * Prototype for callbacks in brp_protocol::.
 */
typedef brp_errcode (*brp_cb_generic_t)
(
	brp_protocol protocol
);


/**
 * Prototype for brp_protocol_t::cb_recv_any_frame() callback.
 */
typedef brp_errcode (*brp_cb_recv_any_frame_t)
(
	brp_protocol protocol,
	brp_time timeout
);


/**
 * Prototype for fmt_spec_callback parameter of :brp_cb_recv_frame_t.
 *
 * This function is called while reading and has to analyze the existing data
 * and returned one of the following analyze results:
 * - any positive integer 'X': missing X more bytes to be able to determine if
                               this frame is complete.
 * - 0, This frame is complete or an error was detected.
 *
 * see also the helper macros BRP_FMTSPEC_EXPECT_MORE() and
 * BRP_FMTSPEC_EXPECT_END().
 */
typedef size_t (*brp_cb_fmt_spec_t)
(
	brp_frame frame,
	void * context
);


/**
 * Prototype for brp_protocol_t::cb_recv_frame() callback.
 */
typedef brp_errcode (*brp_cb_recv_frame_t)
(
	brp_protocol protocol,
	brp_time timeout,
	brp_cb_fmt_spec_t fmt_spec_callback,
	void * context
);


/**
 * Retrieves the type and ID string of a protocol
 */
typedef brp_errcode (*brp_cb_get_id_t)
(
	brp_protocol protocol,
	char * * intf_name,
	brp_frame instance_id
);


/**
 * A kind of 'base class' that will be extended by every custom protocol or
 * io-driver (like BRP or TCP/IP) and filled by their protocol specific values.
 *
 * @attention
 * The audience of this headerfile are developers of protocol plugins for this
 * library which should be a **very** rare case..
 * In the case of writing applications that simply sends BRP commands to
 * devices you confidently can ignore this structure (you only will work with
 * pointers to this kind of structure then: :brp_protocol).
 *
 * To write a custom protocol, this structure has to be included at the
 * beginning of the custom protocol's data structure. Then every pointer to the
 * custom protocol can be cast to a :brp_protocol and vice versa. Furthermore
 * custom protocols have to setup this datastructure with callbacks to their
 * implementations for read / write / open / close the protocol interface.
 *
 * Using this protocol structure a protocol stack can be build by creating
 * a linked list. protocol_t::base_protocol of every protocol refers to the
 * base protoocol where all its output data is send to/input data is received
 * from. To stack two protocols the interface_id of the base_protocol has to
 * match the base_interface_id.
 *
 * If you need lowlevel access to a protocol do never call the callbacks
 * directly. Instead always use the brp_* functions of this module.
 */
struct brp_protocol_t
{
	int                 protocol_id;
	brp_layer_id        layer_id;
	brp_protocol        base_protocol;

	brp_cb_generic_t    cb_open;
	brp_cb_generic_t    cb_close;
	brp_cb_generic_t    cb_send_frame;
	brp_cb_recv_any_frame_t cb_recv_any_frame;
	brp_cb_recv_frame_t cb_recv_frame;
	brp_cb_generic_t    cb_flush;
	brp_cb_generic_t    cb_destroy;
	brp_cb_get_id_t     cb_get_id;

	/**
	 * stores the open/closed state.
	 */
	bool                opened;

	/**
	 * this frame buffers all data that shall be send with the next
	 * brp_send_frame()
	 */
	struct brp_frame_t  send_frame;

	/**
	 * this frame buffers all data that shall be send with the next
	 * brp_send_frame()
	 */
	struct brp_frame_t  recv_frame;

	/**
	 * will be set by the last recv_frame command to the actual time in ms
	 * it waitet for the expected data.
	 */
	brp_time            recv_delay;
	
	/**
	 * This mempool can be used to store response data.
	 */
	brp_mempool mempool;

	/**
	 * Human-readable friendly name of the device (e.g., product name for USB HID).
	 * May be NULL if not available or not applicable for this protocol.
	 * Allocated via protocol's mempool.
	 */
	char* friendly_name;
} ;


/**
 * Sends the data collected in protocol->send_frame to the device connected
 * via this protocol.
 */
BRP_LIB brp_errcode brp_send_frame
(
	brp_protocol protocol    ///< protocol to send data to
);


/**
 * Receives the next frame which may be of arbitrary size and stores it in
 * protocol->recv_frame.
 */
BRP_LIB brp_errcode brp_recv_any_frame
(
	brp_protocol protocol,  ///< protocol where for a data-frame shall be waited
	brp_time timeout        ///< maximum time to wait until a frame arrives
);


/**
 * Receives the next frame which has to be exactly of length 'frame_size' and
 * stores it in protocol->recv_frame.
 */
BRP_LIB brp_errcode brp_recv_fix_frame
(
	brp_protocol protocol,  ///< protocol where for a data-frame shall be waited
	brp_time timeout,       ///< maximum time to wait until a frame arrives
	size_t frame_size       ///< number of bytes to receive
);


/**
 * Receives the next frame and stores it in protocol->recv_frame.
 * The length of the frame is calculated on the fly by fmt_spec_callback
 * depending on the frames content.
 */
BRP_LIB brp_errcode brp_recv_frame
(
	brp_protocol protocol,  ///< protocol where for a data-frame shall be waited
	brp_time timeout,       ///< maximum time to wait until a frame arrives
	brp_cb_fmt_spec_t fmt_spec_callback,  ///< user provided callback that
	                        ///  provides information if frame is
	                        ///  OK/invlid/more data is needed
	void * context          ///< context for fmt_spec_callback callback
);


/**
 * Macro for format specifier functions to check if the next chunk has to be
 * requested.
 * If the frame analysed by the format spec function is too small to fullfill
 * the requirements of the forecast macro, this function will request more data.
 *
 * @code
 * ...
 * BRP_FMTSPEC_EXPECT_MORE(frame_rdr, 2);
 * BRP_FRAME_READ_INT8(frame_rdr, x);
 * BRP_FRAME_READ_INT8(frame_rdr, y);
 * BRP_FMTSPEC_EXPECT_MORE(frame_rdr, 3);
 * BRP_FRAME_READ(frame_rdr, z, 3);
 * @endcode
 * ...
 *
 * ATTENTION: Must not be used outside ::brp_cb_fmt_spec_t function.
 */
#define BRP_FMTSPEC_EXPECT_MORE(frame_rdr, requested_byte_cnt) do { \
	if (brp_frame_read_err(frame_rdr)) \
		return -1; \
	else if (brp_frame_rest(frame_rdr) < (requested_byte_cnt)) \
		return (requested_byte_cnt) - brp_frame_rest(frame_rdr); \
} while (0)


/**
 * Macro for format specifier functions to tell, that the end is reached.
 *
 * ATTENTION: Must not be used outside ::brp_cb_fmt_spec_t function.
 */
#define BRP_FMTSPEC_EXPECT_END(frame_rdr) do { \
	if (! brp_frame_read_eof(frame_rdr)) \
		return -1; \
} while (0)


/**
 * Releases all memory allocated for the brp_protocol.
 */
BRP_LIB void brp_protocol_free(brp_protocol protocol);

/**
 * Allocates and zero-initializes a protocol struct of the given size, sets up
 * the embedded send/recv frames and the protocol_id. Used by all brp_create_*
 * functions as their common allocation prefix.
 *
 * @param size         size of the (protocol-specific) struct to allocate. Its
 *                     first member must be a brp_protocol_t.
 * @param protocol_id  value for the protocol_id field (see BRP_PROTID_*).
 * @return NULL on out-of-memory, otherwise the allocated protocol.
 */
brp_protocol brp_protocol_alloc(size_t size, int protocol_id);

/**
 * @endcond
 */


/**
 * Set up a connection via this protocol.
 *
 * Has to be called before running any communication sequence via this
 * protocol.
 *
 * If the protocol is already opened, nothing is done and #BRP_OK is returned.
 */
BRP_LIB brp_errcode brp_open
(
	brp_protocol protocol     ///< protocol handle to open
);


/**
 * Closes protocol.
 *
 * If the protocol is already closed nothing is done and #BRP_OK is returned.
 *
 * This command does not free the allocated resources. To free the resources
 * call brp_destroy().
 */
BRP_LIB brp_errcode brp_close
(
	brp_protocol protocol     ///< protocol handle to close
);


/**
 * Deletes all data that is waiting in input buffers for being read via
 * brp_recv_frame() (or brp_recv_fix_frame() / brp_frecv_any_frame()).
 */
BRP_LIB brp_errcode brp_flush(brp_protocol);


/**
 * Retrieves the instance name of the I/O-protocol of this protocol stack.
 *
 * This command allows to retrieve the unique identification name of the
 * underlying I/O protokoll in a normalized form. Usually this one can be
 * passed to the corresponding brp_create_*() function of the I/O protokoll
 * layer to recreate it.
 *
 * @code
 * char * intf_name;
 * struct brp_frame_t instance_id;
 * brp_protocol prot = brp_create_tcpip("11.22.33.44")
 * brp_frame_init(&instance_id);
 * if (brp_get_io_id(prot, &intf_name, &instance_id) == BRP_OK)
 *     // will display: TCP/IP 11.22.33.44
 *     printf("%s %s\n", intf_name, (char*)BRP_FRAME_PTR(&instance_id));
 * brp_frame_deinit(&instance_id);
 * @endcode
 *
 * @return BRP_ERR_OPEN_IO on invalid protocol.
 */
BRP_LIB brp_errcode brp_get_io_id
(
	brp_protocol protocol,    ///< protocol handle to retrieve I/O
	char * * intf_name,       ///< interface name
	brp_frame instance_id     ///< frame that will hold the name of the
                              ///  I/O prot instance.
                              ///  ATTENTION: The name contains a trailing
                              ///  zero-terminator to correspond to the
                              ///  C string convention.
);


/**
 * Retrieves the friendly name of the device by traversing the protocol stack.
 *
 * This function traverses the protocol stack (via base_protocol chain) and
 * returns the first non-NULL friendly_name found. This allows retrieving
 * device-specific names (like USB product names) regardless of protocol
 * stack configuration.
 *
 * @param protocol Protocol handle to query
 * @param friendly_name Output parameter for the friendly name string.
 *                      Set to NULL if not available in any layer.
 * @return #BRP_OK on success, #BRP_ERR_INVALID_API_CALL if parameters are NULL
 */
BRP_LIB brp_errcode brp_get_friendly_name(brp_protocol protocol, char** friendly_name);


/**
 * Closes a protocol if opened and frees all allocated resources thereafter.
 * The handle must not be used any more after successfully destroying the
 * handle.
 */
BRP_LIB brp_errcode brp_destroy(brp_protocol);


/**
 * @cond INTERNAL
 */

/**
 * Opens the base protocol. Returns BRP_OK if protocol is NULL.
 * Used by protocol implementations to forward open to base_protocol.
 */
brp_errcode redirect_open(brp_protocol protocol);


/**
 * Closes the base protocol. Returns BRP_OK if protocol is NULL.
 * Used by protocol implementations to forward close to base_protocol.
 */
brp_errcode redirect_close(brp_protocol protocol);


/**
 * @endcond
 */


#endif

/** @} */ // end of defgroup brp_lib
