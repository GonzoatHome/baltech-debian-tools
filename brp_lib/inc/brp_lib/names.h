/**
 * @file
 * Resolves all errorcodes, codes, ... to its corresponding names, descriptions
 * or documentation urls
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __NAMES_H__
#define __NAMES_H__


#include "common.h"
#include "errorcodes.h"


/**
 * Retrieve name of errorcode.
 *
 * @return The string representation (i.e. "BRP_OK", "BRP_ERR_INVALID_KEY", ...)
 * of the according error code or NULL if the error code is unknown.
 */
BRP_LIB char * brp_map_errcode(brp_errcode errcode);


/**
 * Retrieve textual description of errorcode in english.
 *
 * @return NULL if the error code is unknown.
 */
BRP_LIB char * brp_map_errcode_to_desc(brp_errcode errcode);


/**
 * Retrieve URL of the documentation describing the passed errcode
 *
 * @return NULL if the error code is unknown.
 */
BRP_LIB char * brp_map_errcode_to_docurl(brp_errcode errcode);


/**
 * Retrieve the name of a (16bit) cmdcode as C string.
 *
 * @return NULL if the cmdcode is unknown.
 */
BRP_LIB char * brp_map_cmdcode(unsigned cmd_code);


/**
 * Retrieve URL of the documentation describing the passed cmdcode
 *
 * @return NULL if the cmdcode is unknown.
 */
BRP_LIB char * brp_map_cmdcode_to_docurl(unsigned cmd_code);



#endif

/** @} */ // end of defgroup brp_lib
