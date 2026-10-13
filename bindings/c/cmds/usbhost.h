/**
 * @file
 * This command group provides direct access to the USB host functionality of the uC.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_USBHOST_H__
#define __BRP_BALTECH_SDK_CMDS_USBHOST_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * No device connected.
 */
#define BRP_UsbHost_UsbhstErrNotconnected BRP_ERR_STATUS(0x4400, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Device did not respond within Timeout.
 */
#define BRP_UsbHost_UsbhstErrTimeout BRP_ERR_STATUS(0x4400, 0x02)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Device responded only with NACK within Timeout.
 */
#define BRP_UsbHost_UsbhstErrNack BRP_ERR_STATUS(0x4400, 0x03)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Device responded with STALL.
 */
#define BRP_UsbHost_UsbhstErrStall BRP_ERR_STATUS(0x4400, 0x04)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Error on transferring data (CRC, Invalid PID, ...).
 */
#define BRP_UsbHost_UsbhstErrTransfer BRP_ERR_STATUS(0x4400, 0x05)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Device sent unexpected data.
 */
#define BRP_UsbHost_UsbhstErrUnexpectedPkt BRP_ERR_STATUS(0x4400, 0x06)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Received too much data.
 */
#define BRP_UsbHost_UsbhstErrBufferoverflow BRP_ERR_STATUS(0x4400, 0x07)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Failure on setting up pipes.
 */
#define BRP_UsbHost_UsbhstErrSetupPipes BRP_ERR_STATUS(0x4400, 0x20)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	bool Enable;
} brp_UsbHost_Enable_t;
/**
 * Enable/Disable the USB-Host-Interface of the uC.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Enable** (in) Enable/Disable the USB interface.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_Enable(brp_protocol protocol, bool _input_Enable);
#else
brp_errcode brp_UsbHost_Enable(brp_UsbHost_Enable_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool* Connected;
} brp_UsbHost_IsConnected_t;
/**
 * Check if a device is connected.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Connected** (out) _true_ if a device is connected.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_IsConnected(brp_protocol protocol, bool* Connected);
#else
brp_errcode brp_UsbHost_IsConnected(brp_UsbHost_IsConnected_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_UsbHost_SetupPipes_Pipes_Entry* Pipes;
	size_t Pipes_len;
} brp_UsbHost_SetupPipes_t;
/**
 * Setup all Pipes Definitions (uC's internal configuration).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Pipes** (in) 
 *   - **Pipes_len** (in) Number of elements in **Pipes**.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_SetupPipes(brp_protocol protocol, brp_UsbHost_SetupPipes_Pipes_Entry* _input_Pipes, size_t _input_Pipes_len);
#else
brp_errcode brp_UsbHost_SetupPipes(brp_UsbHost_SetupPipes_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
} brp_UsbHost_SetAddr_t;
/**
 * Set Address of device.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) Sets the address the uC shall use when accessing the device.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_SetAddr(brp_protocol protocol, unsigned _input_Address);
#else
brp_errcode brp_UsbHost_SetAddr(brp_UsbHost_SetAddr_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_UsbHost_Reset_t;
/**
 * Send a Reset via USB interface, Remove all Pipes Definitions and reset address of device to 0.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_Reset(brp_protocol protocol);
#else
brp_errcode brp_UsbHost_Reset(brp_UsbHost_Reset_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf SetupData;
	unsigned PipeNo;
	unsigned Timeout;
} brp_UsbHost_TransRawSetup_t;
/**
 * Transfers a raw SETUP packet. Has to be combined with a call of UsbHost.TransSetupIn or UsbHost.TransSetupOut.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SetupData** (in) Data to transfer in SETUP stage.
 *   - **PipeNo** (in) Number of pipe.
 *   - **Timeout** (in) Timeout for transaction.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_TransRawSetup(brp_protocol protocol, brp_buf _input_SetupData, unsigned _input_PipeNo, unsigned _input_Timeout);
#else
brp_errcode brp_UsbHost_TransRawSetup(brp_UsbHost_TransRawSetup_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf SetupData;
	unsigned PipeNo;
	unsigned Timeout;
	brp_buf* InData;
	size_t* InData_len;
	brp_mempool *mempool;
} brp_UsbHost_TransSetupIn_t;
/**
 * Transfers a SETUP transaction with a IN DATA stage.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SetupData** (in) Data to transfer in SETUP stage.
 *   - **PipeNo** (in) Number of pipe.
 *   - **Timeout** (in) Timeout for transaction.
 *   - **InData** (out) Resulting data.
 *   - **InData_len** (out) Length of **InData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_TransSetupIn(brp_protocol protocol, brp_buf _input_SetupData, unsigned _input_PipeNo, unsigned _input_Timeout, brp_buf* InData, size_t* InData_len, brp_mempool *mempool);
#else
brp_errcode brp_UsbHost_TransSetupIn(brp_UsbHost_TransSetupIn_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf SetupData;
	brp_buf OutData;
	size_t OutData_len;
	unsigned PipeNo;
	unsigned Timeout;
} brp_UsbHost_TransSetupOut_t;
/**
 * Transfers a SETUP transaction with a OUT DATA stage.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SetupData** (in) Data to transfer in SETUP Stage.
 *   - **OutData** (in) Data to send.
 *   - **OutData_len** (in) Length of **OutData** (in bytes).
 *   - **PipeNo** (in) Number of pipe.
 *   - **Timeout** (in) Timeout for transaction.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_TransSetupOut(brp_protocol protocol, brp_buf _input_SetupData, brp_buf _input_OutData, size_t _input_OutData_len, unsigned _input_PipeNo, unsigned _input_Timeout);
#else
brp_errcode brp_UsbHost_TransSetupOut(brp_UsbHost_TransSetupOut_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned PipeNo;
	unsigned Timeout;
	brp_buf* InData;
	size_t* InData_len;
	brp_mempool *mempool;
} brp_UsbHost_TransIn_t;
/**
 * Transfers an IN transaction.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PipeNo** (in) Number of pipe.
 *   - **Timeout** (in) Timeout for transaction.
 *   - **InData** (out) Resulting data.
 *   - **InData_len** (out) Length of **InData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_TransIn(brp_protocol protocol, unsigned _input_PipeNo, unsigned _input_Timeout, brp_buf* InData, size_t* InData_len, brp_mempool *mempool);
#else
brp_errcode brp_UsbHost_TransIn(brp_UsbHost_TransIn_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf OutData;
	size_t OutData_len;
	unsigned PipeNo;
	bool Continue;
	unsigned Timeout;
} brp_UsbHost_TransOut_t;
/**
 * Transfers an OUT transaction.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **OutData** (in) Data to send.
 *   - **OutData_len** (in) Length of **OutData** (in bytes).
 *   - **PipeNo** (in) Number of pipe.
 *   - **Continue** (in) Set to true if this transaction shall be continued.
 *   - **Timeout** (in) Timeout for transaction.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_TransOut(brp_protocol protocol, brp_buf _input_OutData, size_t _input_OutData_len, unsigned _input_PipeNo, bool _input_Continue, unsigned _input_Timeout);
#else
brp_errcode brp_UsbHost_TransOut(brp_UsbHost_TransOut_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_UsbHost_Suspend_t;
/**
 * Send a Suspend via USB interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_Suspend(brp_protocol protocol);
#else
brp_errcode brp_UsbHost_Suspend(brp_UsbHost_Suspend_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_UsbHost_Resume_t;
/**
 * Send a Resume via USB interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_Resume(brp_protocol protocol);
#else
brp_errcode brp_UsbHost_Resume(brp_UsbHost_Resume_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */