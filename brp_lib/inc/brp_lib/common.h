/**
 * @file
 * Contains the basic defines that are required throughout the BRP library.
 *
 * This is primarly error codes and handling of compitibility issues between
 * different compiler platforms.
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __COMMONDEFS_H__
#define __COMMONDEFS_H__


/**
 * @cond INTERNAL
 */


#include <stdlib.h>
#include <string.h>

// boolean definitions
#if (__STDC_VERSION__ >= 199901L)
	#include <stdbool.h>
#else
	#define false   0
	#define true    1
	#define bool    unsigned char
#endif
#if ! defined(BRP_LIB)
	#if defined(_MSC_VER)
		#if defined(brp_lib_EXPORTS)
			#define BRP_LIB   __declspec(dllexport)
		#else
			#define BRP_LIB   __declspec(dllimport)
		#endif
	#else
		#define BRP_LIB
	#endif
#endif


#if ! defined(min)
	#define min(a,b) (((a)<(b))?(a):(b))
#endif
#if ! defined(max)
	#define max(a,b) (((a)>(b))?(a):(b))
#endif


/**
 * @endcond
 */

 
/**
 * represents a pointer to a protocol data buffer.
 */
typedef unsigned char * brp_buf;


/**
 * absolute/relative timeout/delay in ms.
 */
typedef unsigned long brp_time;


/**
 * is used if #brp_time shall be infinite.
 */
#define BRP_INFINITE        0xFFFFFFFF


#define BRP_TIME_SUBTRACT(time, delta)   { \
	if ((time) != BRP_INFINITE) { \
		if ((time) < delta) (time) = 0; \
		else (time) -= (delta); } }


#endif

/** @} */ // end of defgroup brp_lib
