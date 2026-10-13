/**
 * @file
 * A composite protocol is a container object, that provides a single protocol
 * object for handling a stack of multiple sub-protocols at once.
 *
 * This means all sub-protocols are opened/closed when the composite is
 * opened/closed. Furthermore they are destroyed when the composite is
 * destroyed.
 *
 * **ATTENTION**: This means that a protocol added to a container
 * must not be destroyed manually (except it is unlinked by
 * brp_detach_layer()!
 *
 * A composite is organized in layers, which are identified by unique
 * integers (see BRP_LAYERID_..., like #BRP_LAYERID_IO).
 * The order of the layer is fix and is usually defined by the order
 * of calling brp_add_layer() (or brp_set_layer(), which does an implicit
 * brp_add_layer() if a layer is unknown yet). Via brp_set_layer() you can
 * assign a protocol to a layer. When running a command / sending a frame,
 * it will be internally routed from the topmost protocol to the
 * bottom protocol.
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __COMPOSITE_PROTOCOL_H__
#define __COMPOSITE_PROTOCOL_H__


#include "protocol.h"


/**
 * @name BRP_MONITOR_XXX
 * @anchor BRP_MONITOR_XXX
 * Specifies the mode of monitoring
 * @{
 */
 
#define BRP_MONITOR_DISABLED          0 ///< avoid that BRP traffic could leak
                                        /// (required when sensitive data is transferred)
#define BRP_MONITOR_ENABLED           1 ///< allow monitoring of BRP data (DEFAULT)
                                        ///  encrypted sessions will show only encryted data
#define BRP_MONITOR_PLAINTEXT 2         ///< allow monitoring of plaintext BRP data
                                        ///  (only relevant for encrypted sessions)

/**
 * @}
 * */


/**
 * Creates an empty composite protocol.
 * Composite protocols are used to manage a protocol stack by a single protocol
 * handle.
 *
 * @return NULL on error, otherwise the created protocol
 */
BRP_LIB brp_protocol brp_create_composite(void);


/**
 * Creates a bare custom protocol whose callbacks are meant to be filled in by
 * the caller (e.g. a language binding implementing an I/O protocol or a
 * transformation layer in its own runtime).
 *
 * The returned protocol is allocated and owned by this library: its
 * cb_destroy is preset to free the protocol via brp_protocol_free(), so it is
 * released like any other protocol via brp_destroy(). The caller assigns the
 * desired cb_* callbacks (and may wrap cb_destroy, as long as it still frees
 * the protocol via brp_protocol_free()).
 *
 * @param custom_index distinguishes custom protocol types; must be in
 *                     [0, 0x80) so the protocol_id stays in the custom range
 *                     BRP_PROTID_CUSTOM(custom_index) (= 0x80 + index).
 * @return NULL on error (incl. custom_index out of range), otherwise the protocol
 */
BRP_LIB brp_protocol brp_create_custom(int custom_index);


/**
 * This is equivalent to the following call:
 *
 * @code
 * brp_protocol composite_prot = brp_create_composite();
 * brp_protocol brp_prot = brp_create_brp();
 * brp_add_layer(composite_prot, BRP_LAYERID_IO);
 * brp_set_layer(composite_prot, BRP_LAYERID_BRP, brp_prot);
 * brp_add_layer(composite_prot, BRP_LAYERID_CRYPTO);
 * @endcode
 */
BRP_LIB brp_protocol brp_create(void);


/**
 * Adds a protocol layer without assigning a protocol to it.
 *
 * If the specified protocol layer was already added #BRP_ERR_EXISTING_LAYER
 * be returned, otherwise the layer will be added at the top of the
 * protocol stack.
 *
 * To assign a specific protocol to the new layer use brp_set_layer().
 */
BRP_LIB brp_errcode brp_add_layer
(
	brp_protocol composite_protocol,  ///< composite where layer shall be
	                                  ///  retrieved
	brp_layer_id layer_id             ///< identification of layer (see
	                                  ///  BRP_LAYERID_*,
	                                  ///  i.e. #BRP_LAYERID_BRP)
);


/**
 * Adds/replaces a protocol layer to a composite protocol.
 *
 * Attention: when adding a protocol to a composite protocol, the composite
 * protocol takes ownership of layer_protocol. Thus layer_protocol must not
 * be freed manually except it is removed from the composite again by
 * brp_detach_layer().
 *
 * If the layer specified by ID is already in use, the previous protocol for
 * this layer will be destroyed and the new layer_protocol will inserted
 * exactly at the same layer as the destroyed protocol (=replace it).
 *
 * If the layer ID is not part of the composite protocol yet,
 * it will be added implicitly at the top of the protocol stack
 * (see brp_add_layer()).
 *
 * If the composite protocol is already opened, the layer protocol will be
 * opened implicitely before being added. In contrary it is invalid to set
 * an already opened layer protocol!
 *
 * If this call fails, ownership of layer_protocol stays with the caller
 * (it is NOT inserted and NOT destroyed — in contrast to brp_set_io() /
 * brp_set_crypto(), which destroy their protocol argument on failure).
 *
 * @attention: If the @em layer_protocol is a composite on its own, the
 * @em composite_protocol will not take over ownership. This means you have
 * to destroy layer_protocol on your own after composite_protocol was destroyed.
 * Furthermore layer_protocol will not be automaticially opened/closed in this
 * case.
 */
BRP_LIB brp_errcode brp_set_layer
(
	brp_protocol composite_protocol,  ///< composite where layer shall be added
	brp_layer_id layer_id,            ///< identification of layer (see
	                                  ///  BRP_LAYERID_*,
	                                  ///  i.e. #BRP_LAYERID_BRP)
	brp_protocol layer_protocol       ///< new layer protocol. Must not be NULL!
);


/**
 * Retrieves a protocol layer from a composite protocol.
 *
 * @returns
 * the protocol with is identified by layer_id or NULL if not found.
 */
BRP_LIB brp_protocol brp_get_layer
(
	brp_protocol composite_protocol,  ///< composite where layer shall be
	                                  ///  retrieved
	brp_layer_id layer_id             ///< identification of layer (see
	                                  ///  BRP_LAYERID_*,
	                                  ///  i.e. #BRP_LAYERID_BRP)
);


/**
 * Removes a protocol from a composite protocol stack without destroying.
 *
 * After calling this function, the application is responsible for destroying
 * the returned protocol object (expect it was NULL)!
 *
 * This function ensures, that the detached protocol will be closed. All other
 * layers will be kept open, except the closed protocol was the I/O layer.
 * In the latter case the other protocols will be closed, too.
 *
 * The protocol layer will
 * keep intact, so that you can insert another protocol at exactly the same
 * position, later when specifing the same layer_id.
 *
 * @returns
 * The protocol previously attached to the specified layer ID. If the layer ID
 * is not used yet, or set to NULL, NULL will be returned.
 */
BRP_LIB brp_protocol brp_detach_layer
(
	brp_protocol composite_protocol,   ///< composite protocol to where layer
	                                   ///  shall be removed from
	brp_layer_id layer_id              ///< identification of layer (see
	                                   ///  BRP_LAYERID_*,
	                                   ///  i.e. #BRP_LAYERID_BRP) which
	                                   ///  protocol shall be detached
);


/**
 * Assigns an I/O protocol to a composite protocol (protocol stack).
 *
 * This is similar to the following call:
 *
 *     brp_set_layer(protocol, BRP_LAYERID_IO, io_protocol).
 *
 * Attention: In contrary to brp_set_layer 'io_protocol' will be destroyed
 * if this call fails for some reason
 * (brp_destroy() must not be called in this case)!
 */
BRP_LIB brp_errcode brp_set_io
(
	brp_protocol protocol,    ///< the composite protocol, which I/O shall
	                          ///  be set.
	brp_protocol io_protocol  ///< the new I/O protocol of the composite prot.
);


/**
 * Assigns a crypto protocol to a composite protocol (protocol stack).
 *
 * This is similar to the following call:
 *
 *     brp_set_layer(protocol, BRP_LAYERID_CRYPTO, crypto_protocol).
 *
 * Attention: In contrary to brp_set_layer, 'crypto_protocol' will be destroyed
 * if this call fails for some reason
 * (brp_destroy() must not be called in this case)!
 */
BRP_LIB brp_errcode brp_set_crypto
(
	brp_protocol composite_protocol, ///< the composite protocol, where a crypto layer shall be added to
	brp_protocol crypto_protocol     ///< the crypto protocol that shall be layered
	                                 ///  on top of 'protocol'.
);


/**
 * Disables the <a href="https://docs.baltech.de/developers/analyze-communication.html" target="_blank">monitoring feature</a>
 * of this library.
 *
 * @deprecated Please use brp_set_monitor() instead.
 *
 * This Library always returns BRP_OK.
 */
BRP_LIB brp_errcode brp_suppress_monitoring(brp_protocol protocol);


/**
 * When communicating encrypted (see brp_set_crypto()) the
 * <a href="https://docs.baltech.de/developers/analyze-communication.html" target="_blank">monitoring feature</a>
 * of this library logs the plaintext data.
 *
 * @attention This feature should only be activated during development
 *
 * This Library always returns BRP_OK.
 */
BRP_LIB brp_errcode brp_set_monitor(
	brp_protocol protocol,  ///< the composite protocol, where monitor shall be configured
	int mode                ///< monitoring mode (see @ref BRP_MONITOR_XXX )
);



/**
 * @cond INTERNAL
 */

/**
 * Retrieve a reference to a specific protocol ID, no matter if the passed
 * protocol is a composite protocol which contains the specified protocol ID,
 * or if it is the protocol ID on its own.
 */
brp_protocol require_protocol
(
	brp_protocol protocol,
	int protocol_id,
	brp_layer_id layer_id
);


/**
 * @endcond
 */


#endif

/** @} */ // end of defgroup brp_lib
