/**
 * @file
 * This file defines the iterator API for enumerating available I/O devices.
 *
 * The iterator allows discovering BRP-compatible devices (currently USB HID)
 * and creating protocol objects for each discovered device.
 *
 * @defgroup brp_ioiter I/O Device Iterator
 * @ingroup brp_lib
 * @{
 */

#ifndef __IOITER_H__
#define __IOITER_H__

#include "common.h"
#include "protocol.h"

/**
 * Base structure for I/O device iterators.
 *
 * Protocol-specific implementations inherit from this structure by having it
 * as the first member, similar to brp_protocol_t.
 */
struct brp_ioiter_t
{
	brp_errcode (*next_fn)(struct brp_ioiter_t* iter, brp_protocol* protocol);
	void (*destroy_fn)(struct brp_ioiter_t* iter);
};

/**
 * Handle to an I/O device iterator.
 */
typedef struct brp_ioiter_t * brp_ioiter;


/**
 * Creates an iterator for enumerating all available I/O devices.
 *
 * This function creates a composite iterator that enumerates all supported
 * I/O protocols (currently USB HID only). The iterator will enumerate all
 * devices across all supported protocols.
 *
 * For USB HID devices: Enumerates devices with default Baltech VID (0x13AD)
 * and PID ranges (40000-40999, 1000-1999, 0xF001-0xFFFF).
 * Only devices with valid numeric serial numbers and BRP interface
 * (usage_page=0xFF00, usage=1) are included.
 *
 * The iterator must be destroyed with brp_ioiter_destroy() when done.
 *
 * @return Iterator handle or NULL on failure (e.g., out of memory)
 *
 * @code
 * brp_ioiter iter = brp_ioiter_create();
 * if (iter == NULL) {
 *     // Handle error
 *     return;
 * }
 *
 * brp_protocol protocol;
 * while (brp_ioiter_next(iter, &protocol) == BRP_OK && protocol != NULL) {
 *     // Use protocol
 *     char* name = brp_get_friendly_name(protocol);
 *     printf("Found device: %s\n", name ? name : "Unknown");
 *
 *     // Clean up protocol when done
 *     brp_destroy(protocol);
 * }
 *
 * brp_ioiter_destroy(&iter);
 * @endcode
 */
BRP_LIB brp_ioiter brp_ioiter_create(void);


/**
 * Retrieves the next device from the iterator.
 *
 * Each call advances the iterator and creates a new brp_protocol for the
 * next available device. The caller is responsible for destroying each
 * protocol using brp_destroy() when done.
 *
 * The protocol's id field contains the device serial number, and the
 * friendly_name field contains the product name (accessible via
 * brp_get_friendly_name()).
 *
 * @param iter Iterator handle created by brp_ioiter_create()
 * @param protocol Output parameter for the protocol handle. Set to NULL when
 *                 no more devices are available.
 * @return BRP_OK on success (check protocol for NULL to detect end),
 *         BRP_ERR_INVALID_API_CALL if iter is NULL,
 *         BRP_ERR_OUT_OF_MEMORY on allocation failure
 */
BRP_LIB brp_errcode brp_ioiter_next(brp_ioiter iter, brp_protocol* protocol);


/**
 * Destroys an iterator and frees all associated resources.
 *
 * After calling this function, the iterator handle must not be used anymore.
 * Note: This does not destroy any protocols created by brp_ioiter_next().
 * Those must be destroyed separately using brp_destroy().
 *
 * @param iter Pointer to iterator handle. Will be set to NULL after destruction.
 */
BRP_LIB void brp_ioiter_destroy(brp_ioiter* iter);


#endif

/** @} */ // end of defgroup brp_ioiter
