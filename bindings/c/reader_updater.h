#ifndef __BRP_READER_UPDATER_H__
#define __BRP_READER_UPDATER_H__

#include <brp_lib.h>

#if defined(__cplusplus)
extern "C" {
#endif


/**
 * Progress notification callback for reader update operations.
 *
 * @param transferred_bytes      Number of bytes transferred so far
 * @param estimated_total        Estimated total bytes (0 if unknown)
 * @param progress_percent       Progress 0 to 100 (0 if unknown)
 * @param estimated_time_overhead  Estimated overhead in ms beyond transfer (0 if unknown)
 * @param reconnecting           true if reader is about to reconnect
 */
typedef void (*brp_update_progress_cb)(
	unsigned transferred_bytes,
	unsigned estimated_total,
	unsigned progress_percent,
	unsigned estimated_time_overhead,
	bool reconnecting
);


/**
 * Parse BEC2/BF3 hex string to binary blob.
 *
 * The hex format has header lines followed by an empty line, then hex-encoded
 * payload bytes. Header lines are skipped.
 *
 * @param hex_str    Pointer to the hex string content
 * @param hex_len    Length of hex_str in bytes
 * @param blob       Output: pointer to parsed binary blob (allocated in mempool)
 * @param blob_size  Output: size of the parsed blob
 * @param mempool    Memory pool for allocation. Caller frees via brp_mempool_free.
 *
 * @return BRP_OK on success, BRP_ERR_PAYLOAD_FORMAT on invalid hex data,
 *         BRP_ERR_OUT_OF_MEMORY on allocation failure
 */
brp_errcode brp_get_update_blob_from_string(
	const char * hex_str,
	size_t hex_len,
	brp_buf * blob,
	size_t * blob_size,
	brp_mempool * mempool
);


/**
 * Upload binary blob to reader with optional progress notification.
 *
 * Implements the BF3/BEC2 upload protocol: Bf3UploadStart followed by
 * iterative Bf3UploadContinue calls. Handles reconnect internally.
 *
 * @param dev          Protocol handle (must be open)
 * @param blob         Binary blob data to upload
 * @param blob_size    Size of blob in bytes
 * @param progress_cb  Progress callback (may be NULL)
 *
 * @return BRP_OK on success (including already-up-to-date),
 *         BRP_ERR_INVALID_API_CALL if blob is too small for reader request
 */
brp_errcode brp_update_reader_from_blob(
	brp_protocol dev,
	brp_buf blob,
	size_t blob_size,
	brp_update_progress_cb progress_cb
);


/**
 * Convenience: load hex file and upload to reader.
 *
 * Reads the file, parses hex content, and uploads to the reader.
 * Memory is managed internally.
 *
 * @param dev          Protocol handle (must be open)
 * @param filepath     Path to BEC2/BF3 hex file
 * @param progress_cb  Progress callback (may be NULL)
 *
 * @return BRP_OK on success, BRP_ERR_OPEN_IO if file cannot be opened
 */
brp_errcode brp_update_reader(
	brp_protocol dev,
	const char * filepath,
	brp_update_progress_cb progress_cb
);


#if defined(__cplusplus)
}
#endif

#endif
