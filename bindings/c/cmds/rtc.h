/**
 * @file
 * If the reader has a Real Time Clock (RTC) on board, its current time can be set and retrieved with commands from this command group.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_RTC_H__
#define __BRP_BALTECH_SDK_CMDS_RTC_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * The RTC hardware is defect.
 */
#define BRP_Rtc_ErrHardware BRP_ERR_STATUS(0x0400, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * The battery of the RTC is low. The time may be invalid.
 */
#define BRP_Rtc_ErrVoltageLow BRP_ERR_STATUS(0x0400, 0x02)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned ClockId;
	unsigned* Now;
} brp_Rtc_GetTime_t;
/**
 * Retrieve current time of on-board RTC.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ClockId** (in) Index of clock to get time of.
 *   - **Now** (out) Datetime in local time (PC local).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Rtc_GetTime(brp_protocol protocol, unsigned _input_ClockId, unsigned* Now);
#else
brp_errcode brp_Rtc_GetTime(brp_Rtc_GetTime_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned ClockId;
	unsigned Now;
} brp_Rtc_SetTime_t;
/**
 * Set the time of the on-board RTC.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ClockId** (in) Index of clock to set.
 *   - **Now** (in) When _Now_ is an integer, its value represents the seconds since 1.1.1970-00:00:00 GMT (UNIX Time).   When _Now_ is a _datetime()_ object, it must be set to the local time, not the UTC (or GMT) time. This is due to the fact that the _mktime()_ function is used internally, transforming the local time into UNIX Time.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Rtc_SetTime(brp_protocol protocol, unsigned _input_ClockId, unsigned _input_Now);
#else
brp_errcode brp_Rtc_SetTime(brp_Rtc_SetTime_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */