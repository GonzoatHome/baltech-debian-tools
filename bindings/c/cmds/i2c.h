/**
 * @file
 * This command group enables to access the I2C interface.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_I2C_H__
#define __BRP_BALTECH_SDK_CMDS_I2C_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * Error reading from I2C interface.
 */
#define BRP_I2c_ErrI2CRead BRP_ERR_STATUS(0x0800, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Error writing to I2C interface.
 */
#define BRP_I2c_ErrI2CWrite BRP_ERR_STATUS(0x0800, 0x02)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	bool FastMode;
} brp_I2c_SetSpeed_t;
/**
 * Set speed of I2C interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **FastMode** (in) True if I2C fastmode (400kbit) should be enabled, otherwise normal speed (100kbit) is activated.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_I2c_SetSpeed(brp_protocol protocol, bool _input_FastMode);
#else
brp_errcode brp_I2c_SetSpeed(brp_I2c_SetSpeed_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
	unsigned ReadLen;
	brp_buf* ReadData;
	size_t* ReadData_len;
	brp_mempool *mempool;
} brp_I2c_Read_t;
/**
 * Read data from I2C interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) I2C device address.
 *   - **ReadLen** (in) Number of bytes to read.
 *   - **ReadData** (out) Data read from I2C interface.
 *   - **ReadData_len** (out) Length of **ReadData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_I2c_Read(brp_protocol protocol, unsigned _input_Address, unsigned _input_ReadLen, brp_buf* ReadData, size_t* ReadData_len, brp_mempool *mempool);
#else
brp_errcode brp_I2c_Read(brp_I2c_Read_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
	brp_buf WriteData;
	size_t WriteData_len;
} brp_I2c_Write_t;
/**
 * Write data to I2C interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) I2C device address.
 *   - **WriteData** (in) Data to write to I2C interface.
 *   - **WriteData_len** (in) Length of **WriteData** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_I2c_Write(brp_protocol protocol, unsigned _input_Address, brp_buf _input_WriteData, size_t _input_WriteData_len);
#else
brp_errcode brp_I2c_Write(brp_I2c_Write_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
	brp_buf CmdData;
	size_t CmdData_len;
	unsigned ReadLen;
	brp_buf* ReadData;
	size_t* ReadData_len;
	brp_mempool *mempool;
} brp_I2c_TxRx_t;
/**
 * Write data and directly after that read from I2C interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) I2C device address.
 *   - **CmdData** (in) Command Data to write before reading (e.g. start address).
 *   - **CmdData_len** (in) Length of **CmdData** (in bytes).
 *   - **ReadLen** (in) Number of bytes to read.
 *   - **ReadData** (out) Data read from I2C interface.
 *   - **ReadData_len** (out) Length of **ReadData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_I2c_TxRx(brp_protocol protocol, unsigned _input_Address, brp_buf _input_CmdData, size_t _input_CmdData_len, unsigned _input_ReadLen, brp_buf* ReadData, size_t* ReadData_len, brp_mempool *mempool);
#else
brp_errcode brp_I2c_TxRx(brp_I2c_TxRx_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */