/**
 * @file
 * Defines a mempool that allows centralized memory allocation.
 *
 * This module is used during command execution to store the response data.
 *
 * @see <a href="https://docs.baltech.de/developers/use-brp-mempool.html" target="_blank">How to use brp_mempool</a>
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__


#include "common.h"


/**
 * mempool handle.
 *
 * A mempool manages multiple buffer. The buffer can be created at runtime.
 * The mempool takes care of the memory management of buffers.
 *
 * Handles must be initialized via ``brp_mempool mempool = NULL;``.
 * Handles must be freed via ``brp_mempool_free(*mempool);``.
 */
typedef struct brp_mempool_object_t* brp_mempool;


/**
 * @cond INTERNAL
 */

/**
 * Creates a new brp_buf in the brp_mempool
 *
 * @param mempool The mempool to manage the buffer
 * @param initial_size The initial size of the buffer
 *
 * @return pointer to the reallocated buffer. NULL if out of memory.
 */
BRP_LIB brp_buf brp_mempool_create_buf(brp_mempool *mempool, size_t initial_size);


/**
 * Resizes an buffer, managed by a mempool.
 *
 * @param buf       The buffer to resize.
 *                  (must be created with ``brp_mempool_create_buf(mempool)``)
 * @param size      The desired size of the buffer.
 *
 * @return pointer to the reallocated buffer. NULL if out of memory.
 */
BRP_LIB brp_buf brp_mempool_resize_buf(brp_buf buf, size_t new_size);

/**
 * @endcond
 */

/**
 * Releases the memory of a brp_mempool.
 *
 * All brp_bufs created by the mempool are getting invalid and the memory is realeased.
 * The mempool itself is empty afterwards and can be reuse again.
 */
BRP_LIB void brp_mempool_free(brp_mempool *mempool);


#endif

/** @} */ // end of defgroup brp_lib
