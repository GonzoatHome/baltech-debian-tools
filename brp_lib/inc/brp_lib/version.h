/**
 * @file
 * Allows to retrieve compiler version
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */
 
#if ! defined(__GET_VERSION__)
#define __GET_VERSION__


#include "common.h"


/**
 * Returns the version of the *BRP Communication Libary*.
 *
 * Must not be confused with the defines #BRP_BALTECH_API_VERSION, which has
 * the format but refers to the version of the *Baltech API* (which might be
 * different, see README.html!)
 *
 * @return A 7 byte ASCII string of the format "x.yy.zz"
 * (where x is the major version, y is the minor version and z is the release)
 */
BRP_LIB char * brp_get_version(void);


#endif

/** @} */ // end of defgroup brp_lib
