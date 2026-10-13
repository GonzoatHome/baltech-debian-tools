/**
 * @file
 * Implements a "Probe" Protocol, that logs all transferred data to a file.
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __MONITOR_PROTOCOL_H__
#define __MONITOR_PROTOCOL_H__


#include "protocol.h"


#if !defined(BRP_LOG_DIR_PREFIX)
	#define BRP_LOG_DIR_PREFIX    "brp-logs/"
#endif


/**
 * Creates a new Monitor protocol layer.
 *
 * This protocol layer will log all actions executed to a file and forward them
 * one-to-one to the underlying protocol.
 *
 * @return A BRP protocol on success or NULL on failure.
 */
BRP_LIB brp_protocol brp_create_monitor(void);


/**
 * Marks the beginning of a related block of log entries
 *
 * @param protocol A protocol which shall be annotated. Must not necessary a
 *                 brp_monitor_protocol as it will search for all
 *                 monitor_protocols which are comming below this protocol.
 */
BRP_LIB void brp_annotation_start(brp_protocol protocol);


/**
 * Marks the end of a related block of log entries and adds some kind of
 * comment to it.
 *
 * @param protocol A protocol which shall be annotated. Must not necessary a
 *                 brp_monitor_protocol as it will search for all
 *                 monitor_protocols which are comming below this protocol.
 * @param success  Specifies if the Annotated Block of commands was successful
 *                 or not.
 * @param comment  A comment that is shown together with the embraced log
 *                 entries
 */
BRP_LIB void brp_annotation_end(
	brp_protocol protocol, bool success, char * comment
);


/**
 * Sets a custom log file path.
 *
 * If the path ends with '/' or '\', it is treated as a directory and the
 * default filename schema ({interface}-{instance}.html) will be used.
 * Otherwise, the path is used as the full file path.
 *
 * Setting path to NULL restores the default behavior.
 *
 * If a log file is currently open, it will be closed and the new path will be
 * used for the next log entry.
 *
 * @param protocol A protocol stack containing a monitor protocol layer.
 * @param path     The custom log file path, or NULL for default behavior.
 * @return BRP_OK on success, or an error code on failure.
 */
BRP_LIB brp_errcode brp_set_log_path(brp_protocol protocol, const char * path);


/**
 * Returns the current log file path.
 *
 * @param protocol  A protocol stack containing a monitor protocol layer.
 * @param mempool   Optional mempool for memory allocation. If NULL, uses
 *                  the protocol's mempool.
 * @return The allocated path string, or NULL on error.
 */
BRP_LIB char * brp_get_log_path(brp_protocol protocol, brp_mempool * mempool);


/**
 * Returns the anchor ID of the current (last written) log entry.
 *
 * The anchor can be used to create direct links to specific log entries,
 * e.g., "file:///path/to/log.html#_a3"
 *
 * @param protocol  A protocol stack containing a monitor protocol layer.
 * @param anchor    Output parameter for the allocated anchor string (e.g., "_a3").
 *                  Set to NULL if no log entries have been written yet.
 * @param mempool   Optional mempool for memory allocation. If NULL, uses
 *                  the protocol's mempool.
 * @return BRP_OK on success, or an error code on failure.
 */
BRP_LIB brp_errcode brp_get_current_log_anchor(brp_protocol protocol, char ** anchor, brp_mempool * mempool);


#endif //__MONITOR_PROTOCOL_H__

/** @} */ // end of defgroup brp_lib
