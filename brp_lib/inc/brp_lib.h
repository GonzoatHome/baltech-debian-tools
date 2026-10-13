/**
 * @file
 * A single include header file, that includes all header files necessary for
 * the BRP library.
 *
 * @defgroup brp_lib BRP Communication Library
 * @{
 */

#ifndef __BRP_H__
#define __BRP_H__

#if defined(__cplusplus)
extern "C" {
#endif


#include "brp_lib/common.h"
#include "brp_lib/errorcodes.h"
#include "brp_lib/frames.h"
#include "brp_lib/mempool.h"
#include "brp_lib/names.h"

#include "brp_lib/brp_protocol.h"
#include "brp_lib/usb_hid_protocol.h"
#include "brp_lib/rs232_protocol.h"
#include "brp_lib/security_protocol.h"
#include "brp_lib/composite_protocol.h"
#include "brp_lib/monitor_protocol.h"
#include "brp_lib/ioiter.h"

#include "brp_lib/commands.h"
#include "brp_lib/version.h"
#include "brp_lib/platform.h"

#if defined(__cplusplus)
}
#endif

#endif //__BRP_H__

/** @} */ // end of defgroup brp_lib
