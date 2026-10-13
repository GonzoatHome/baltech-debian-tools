/**
 * @file
 * Defines generic, platform specific functions which are required for
 * the SDK internally.
 *
 * @internal
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __PLATFORM_H__
#define __PLATFORM_H__



#include "common.h"


#ifdef _WIN32
	#if ! defined(PATH_MAX)
		#define PATH_MAX    _MAX_PATH
	#endif
#else
	#include <limits.h>
#endif


/**
 * Retrieves a monotonic timer since powerup
 *
 * @return time in ms
 */
BRP_LIB brp_time brp_get_time(void);



/**
 * Retrieve random data and store it into a buffer
 */
BRP_LIB bool brp_get_random
(
	brp_buf buf,   ///< buffer to store random data into
	size_t len     ///< length of @em buf
);


/**
 * Retrieves the HOME directory of the current user.
 *
 * @return true on success.
 */
BRP_LIB bool brp_get_home_dir
(
	char * result    ///< pointer to buffer where directory shall be stored.
	                 ///  Must be prepared to store PATH_MAX bytes.
	                 ///  Is undefined if return value is false.
);


/**
 * Retrieves the (file-)name of the current process.
 *
 * @return true on success
 */
BRP_LIB bool brp_get_process_name
(
	char * result    ///< pointer to buffer where processname shall be stored.
	                 ///  Must be prepared to store PATH_MAX bytes.
	                 ///  Is undefined if return value is false.
);


/**
 * Creates a directory recursively, creating intermediate directories as needed.
 *
 * @param path The directory path to create.
 * @return true on success, false on failure.
 */
BRP_LIB bool brp_create_directory_recursive(const char *path);


/**
 * Checks if a directory exists at the given path.
 *
 * @param path The directory path to check.
 * @return true if the directory exists, false otherwise.
 */
BRP_LIB bool brp_directory_exists(const char *path);


/**
 * Retrieves the value of an environment variable.
 *
 * This function provides a cross-platform way to access environment variables,
 * ensuring that changes made after DLL loading are reflected (unlike some
 * platform-specific implementations that cache environment variables).
 *
 * @param name The name of the environment variable to retrieve.
 * @param result Pointer to buffer where the value shall be stored.
 * @param len Size of the result buffer in bytes.
 *            Must be large enough to hold the environment variable value plus null terminator.
 *            Is undefined if return value is false.
 * @return true on success (variable exists), false if not found, buffer too small, or error.
 */
BRP_LIB bool brp_getenv(const char *name, char *result, size_t len);


#endif

/** @} */ // end of defgroup brp_lib
