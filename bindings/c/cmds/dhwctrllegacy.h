/**
 * @file
 * Low level hardware commands. These are usually commands to test the hardware and have very low level access to the AVR peripherals.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_DHWCTRLLEGACY_H__
#define __BRP_BALTECH_SDK_CMDS_DHWCTRLLEGACY_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * This port is not available on this hardware platform.
 */
#define BRP_DHWCtrlLegacy_ErrUnknownPort BRP_ERR_STATUS(0xE000, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * The structure of a StartupRun-block is wrong or the command DHWCtrlLegacy.GetStartupRun has not properly been called.
 */
#define BRP_DHWCtrlLegacy_ErrMarshall BRP_ERR_STATUS(0xE000, 0x02)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * There was no StartupRun-block, or the DHWCtrlLegacy.GetStartupRun command was not executed.
 */
#define BRP_DHWCtrlLegacy_ErrNoStartupRun BRP_ERR_STATUS(0xE000, 0x03)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * The Power Manager was unable to take the module into suspend mode.
 */
#define BRP_DHWCtrlLegacy_ErrNoPowermgr BRP_ERR_STATUS(0xE000, 0x04)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * No production loader is present in the reader's flash memory.
 */
#define BRP_DHWCtrlLegacy_ErrNoProdloader BRP_ERR_STATUS(0xE000, 0x05)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * No PlatformID2 available.
 */
#define BRP_DHWCtrlLegacy_ErrPfid2NotAvailable BRP_ERR_STATUS(0xE000, 0x06)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Specified EEPROM address and amount of Bytes to write are not compatible.
 */
#define BRP_DHWCtrlLegacy_ErrEepIndex BRP_ERR_STATUS(0xE000, 0x11)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Data written to EEPROM could not be verified.
 */
#define BRP_DHWCtrlLegacy_ErrEepVerify BRP_ERR_STATUS(0xE000, 0x12)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Data could not be written within timeout.
 */
#define BRP_DHWCtrlLegacy_ErrEepTimeout BRP_ERR_STATUS(0xE000, 0x13)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Dataflash could not be found.
 */
#define BRP_DHWCtrlLegacy_ErrDataflash BRP_ERR_STATUS(0xE000, 0x20)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Timeout occurred.
 */
#define BRP_DHWCtrlLegacy_ErrDataflashTimeout BRP_ERR_STATUS(0xE000, 0x21)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Verification failed after writing data.
 */
#define BRP_DHWCtrlLegacy_ErrDataflashVerify BRP_ERR_STATUS(0xE000, 0x22)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Parameter(s)/address(es) are not valid.
 */
#define BRP_DHWCtrlLegacy_ErrDataflashParam BRP_ERR_STATUS(0xE000, 0x23)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Communication via SPI interface failed.
 */
#define BRP_DHWCtrlLegacy_ErrDataflashSpi BRP_ERR_STATUS(0xE000, 0x24)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Flash device behaves in an unspecified manner.
 */
#define BRP_DHWCtrlLegacy_ErrDataflashFlash BRP_ERR_STATUS(0xE000, 0x25)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * SPI programming instruction couldn't be executed successfully.
 */
#define BRP_DHWCtrlLegacy_ErrAvrProgSpi BRP_ERR_STATUS(0xE000, 0x30)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * PDI operation couldn't be executed successfully.
 */
#define BRP_DHWCtrlLegacy_ErrAvrProgPdi BRP_ERR_STATUS(0xE000, 0x31)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * RC (PN) EEProm access error.
 */
#define BRP_DHWCtrlLegacy_ErrRcAccess BRP_ERR_STATUS(0xE000, 0x40)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * No data was received by NIC.
 */
#define BRP_DHWCtrlLegacy_ErrNicNoData BRP_ERR_STATUS(0xE000, 0x50)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Received data was to big for buffer.
 */
#define BRP_DHWCtrlLegacy_ErrNicBufferFlow BRP_ERR_STATUS(0xE000, 0x51)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned Port;
	brp_DHWCtrlLegacy_PortConfig_Mode Mode;
} brp_DHWCtrlLegacy_PortConfig_t;
/**
 * Configures a port.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Port** (in) Number of port to access.
 *   - **Mode** (in) There are four modes possible:
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PortConfig(brp_protocol protocol, unsigned _input_Port, brp_DHWCtrlLegacy_PortConfig_Mode _input_Mode);
#else
brp_errcode brp_DHWCtrlLegacy_PortConfig(brp_DHWCtrlLegacy_PortConfig_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Port;
	bool* Level;
} brp_DHWCtrlLegacy_PortGet_t;
/**
 * Reads the current input of a port.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Port** (in) Number of port to access.
 *   - **Level** (out) The read level.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PortGet(brp_protocol protocol, unsigned _input_Port, bool* Level);
#else
brp_errcode brp_DHWCtrlLegacy_PortGet(brp_DHWCtrlLegacy_PortGet_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Port;
	bool Level;
} brp_DHWCtrlLegacy_PortSet_t;
/**
 * Sets the state of a port.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Port** (in) Number of port to access.
 *   - **Level** (in) Level of the port.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PortSet(brp_protocol protocol, unsigned _input_Port, bool _input_Level);
#else
brp_errcode brp_DHWCtrlLegacy_PortSet(brp_DHWCtrlLegacy_PortSet_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Port;
	bool Level;
	unsigned Timeout;
	unsigned* ReactionTime;
} brp_DHWCtrlLegacy_PortWait_t;
/**
 * Waits until a port has reached the specified level, or until timeout.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Port** (in) Port to monitor.
 *   - **Level** (in) Level which must be reached by _Port_.
 *   - **Timeout** (in) Timeout value in milliseconds. 0xFFFF means no timeout.
 *   - **ReactionTime** (out) The time in milliseconds until _Port_ reached desired _Level_ value. 0xFFFF is returned when the timeout value is reached. 0xFFFE is otherwise the maximum value.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PortWait(brp_protocol protocol, unsigned _input_Port, bool _input_Level, unsigned _input_Timeout, unsigned* ReactionTime);
#else
brp_errcode brp_DHWCtrlLegacy_PortWait(brp_DHWCtrlLegacy_PortWait_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned* ResetCause;
} brp_DHWCtrlLegacy_GetResetCause_t;
/**
 * Returns the cause of the microcontroller's last reset.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ResetCause** (out) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_GetResetCause(brp_protocol protocol, unsigned* ResetCause);
#else
brp_errcode brp_DHWCtrlLegacy_GetResetCause(brp_DHWCtrlLegacy_GetResetCause_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Port;
	unsigned Count;
	unsigned** Voltages;
	size_t* Voltages_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_APortMeasure_t;
/**
 * The selected ADC Clock is MCU Clock / 128 (i.e. 13.56 Mhz / 128) 
 * 
 * After 13 ADC Clock Ticks the first sample will measured. 13 ADC Clock Ticks are needed for one sample: 
 * 
 * (1 / 13.56 Mhz) * 128 * 13 = 0.123 ms 
 * 
 * So we have each 0.123ms one sample. As reference voltage the AVR internal 2.56V is used, the results are 10 bit values, so to get the voltage in Volt use the following formula: 
 * 
 * Vin = float(result) / 1024 * 2.56V = float(result) / 400V
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Port** (in) Measured port (same variable as in DHWCtrlLegacy.PortGet)
 *   - **Count** (in) Count of taken measurements.
 *   - **Voltages** (out) 
 *   - **Voltages_len** (out) Number of elements in **Voltages**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_APortMeasure(brp_protocol protocol, unsigned _input_Port, unsigned _input_Count, unsigned** Voltages, size_t* Voltages_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_APortMeasure(brp_DHWCtrlLegacy_APortMeasure_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned SramSize;
	bool* Success;
} brp_DHWCtrlLegacy_SRAMTest_t;
/**
 * Tests the external SRAM.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SramSize** (in) Size of SRAM in Bytes
 *   - **Success** (out) Indicates that the SRAM Test was successfully run.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_SRAMTest(brp_protocol protocol, unsigned _input_SramSize, bool* Success);
#else
brp_errcode brp_DHWCtrlLegacy_SRAMTest(brp_DHWCtrlLegacy_SRAMTest_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Baudrate NewBaudrate;
} brp_DHWCtrlLegacy_SetBaudrate_t;
/**
 * Changes the baudrate. This command should not be called over BRP.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **NewBaudrate** (in) The Baudrate specifies the performance of an RS-232/UART based interface in bits per second.   **For the old-style 8bit format, which omits the least significant digit, this format is not supported any more. Configurations using this format cannot be opened.**
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_SetBaudrate(brp_protocol protocol, brp_Baudrate _input_NewBaudrate);
#else
brp_errcode brp_DHWCtrlLegacy_SetBaudrate(brp_DHWCtrlLegacy_SetBaudrate_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf Data;
	size_t Data_len;
	brp_buf* MirroredData;
	size_t* MirroredData_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_MirrorData_t;
/**
 * Sends the exact same data back.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Data** (in) 
 *   - **Data_len** (in) Length of **Data** (in bytes).
 *   - **MirroredData** (out) 
 *   - **MirroredData_len** (out) Length of **MirroredData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_MirrorData(brp_protocol protocol, brp_buf _input_Data, size_t _input_Data_len, brp_buf* MirroredData, size_t* MirroredData_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_MirrorData(brp_DHWCtrlLegacy_MirrorData_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool Enable;
} brp_DHWCtrlLegacy_DispEnable_t;
/**
 * Enables the Display.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Enable** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DispEnable(brp_protocol protocol, bool _input_Enable);
#else
brp_errcode brp_DHWCtrlLegacy_DispEnable(brp_DHWCtrlLegacy_DispEnable_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool Backlight;
} brp_DHWCtrlLegacy_DispBacklight_t;
/**
 * Enables the Baltech reader display's backlight.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Backlight** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DispBacklight(brp_protocol protocol, bool _input_Backlight);
#else
brp_errcode brp_DHWCtrlLegacy_DispBacklight(brp_DHWCtrlLegacy_DispBacklight_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlLegacy_DispColor_Color Color;
} brp_DHWCtrlLegacy_DispColor_t;
/**
 * Set the drawing color
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Color** (in) Drawing color.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DispColor(brp_protocol protocol, brp_DHWCtrlLegacy_DispColor_Color _input_Color);
#else
brp_errcode brp_DHWCtrlLegacy_DispColor(brp_DHWCtrlLegacy_DispColor_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Contrast;
} brp_DHWCtrlLegacy_DispContrast_t;
/**
 * Changes the display contrast.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Contrast** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DispContrast(brp_protocol protocol, unsigned _input_Contrast);
#else
brp_errcode brp_DHWCtrlLegacy_DispContrast(brp_DHWCtrlLegacy_DispContrast_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned X;
	unsigned Y;
	unsigned Width;
	unsigned Height;
} brp_DHWCtrlLegacy_DispBox_t;
/**
 * Draws a filled box.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **X** (in) 
 *   - **Y** (in) 
 *   - **Width** (in) 
 *   - **Height** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DispBox(brp_protocol protocol, unsigned _input_X, unsigned _input_Y, unsigned _input_Width, unsigned _input_Height);
#else
brp_errcode brp_DHWCtrlLegacy_DispBox(brp_DHWCtrlLegacy_DispBox_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned InterfaceID;
	bool Enable;
	brp_Baudrate NewBaudrate;
	brp_Parity NewParity;
	unsigned Stopbits;
} brp_DHWCtrlLegacy_Ser2Ctrl_t;
/**
 * Enable/Disable and setup the reader's 2nd RS-232/UART interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **InterfaceID** (in) 
 *   - **Enable** (in) 
 *   - **NewBaudrate** (in) The Baudrate specifies the performance of an RS-232/UART based interface in bits per second.   **For the old-style 8bit format, which omits the least significant digit, this format is not supported any more. Configurations using this format cannot be opened.**
 *   - **NewParity** (in) Specifies the Parity-bit mode which is used for RS-232/UART protocols.
 *   - **Stopbits** (in) Number of stop bits.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Ser2Ctrl(brp_protocol protocol, unsigned _input_InterfaceID, bool _input_Enable, brp_Baudrate _input_NewBaudrate, brp_Parity _input_NewParity, unsigned _input_Stopbits);
#else
brp_errcode brp_DHWCtrlLegacy_Ser2Ctrl(brp_DHWCtrlLegacy_Ser2Ctrl_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned MaxReadCount;
	unsigned Timeout;
	brp_buf WriteData;
	size_t WriteData_len;
	brp_buf* ReadData;
	size_t* ReadData_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_Ser2WriteRead_t;
/**
 * Write/Read data to/from the reader's 2nd RS-232/UART interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **MaxReadCount** (in) Number of Bytes to read via the reader's 2nd RS-232/UART interface.
 *   - **Timeout** (in) Number of milliseconds to wait for Bytes.
 *   - **WriteData** (in) Data to write to the reader's 2nd RS-232/UART interface.
 *   - **WriteData_len** (in) Length of **WriteData** (in bytes).
 *   - **ReadData** (out) Data read from the reader's 2nd RS-232/UART interface.
 *   - **ReadData_len** (out) Length of **ReadData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Ser2WriteRead(brp_protocol protocol, unsigned _input_MaxReadCount, unsigned _input_Timeout, brp_buf _input_WriteData, size_t _input_WriteData_len, brp_buf* ReadData, size_t* ReadData_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_Ser2WriteRead(brp_DHWCtrlLegacy_Ser2WriteRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_Ser2Flush_t;
/**
 * Wait until output to 2nd RS-232/UART interface is sent out.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Ser2Flush(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_Ser2Flush(brp_DHWCtrlLegacy_Ser2Flush_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Delay;
} brp_DHWCtrlLegacy_Delay1ms_t;
/**
 * Sleeps for some milliseconds.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Delay** (in) Number of milliseconds to sleep.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Delay1ms(brp_protocol protocol, unsigned _input_Delay);
#else
brp_errcode brp_DHWCtrlLegacy_Delay1ms(brp_DHWCtrlLegacy_Delay1ms_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Delay;
} brp_DHWCtrlLegacy_Delay10us_t;
/**
 * Sleeps for some microseconds.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Delay** (in) Number of 10s of microseconds to sleep.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Delay10us(brp_protocol protocol, unsigned _input_Delay);
#else
brp_errcode brp_DHWCtrlLegacy_Delay10us(brp_DHWCtrlLegacy_Delay10us_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Delay;
	bool KeyboardWakeup;
} brp_DHWCtrlLegacy_PowermgrSuspend_t;
/**
 * Takes the board into suspend mode, i.e. energy saving mode.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Delay** (in) Time to sleep in milliseconds.
 *   - **KeyboardWakeup** (in) If _true_ , the keyboard can wake up the board.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PowermgrSuspend(brp_protocol protocol, unsigned _input_Delay, bool _input_KeyboardWakeup);
#else
brp_errcode brp_DHWCtrlLegacy_PowermgrSuspend(brp_DHWCtrlLegacy_PowermgrSuspend_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Bitmask;
} brp_DHWCtrlLegacy_ScanMatrix_t;
/**
 * Writes a bitmask to the 573, which is used for keyboard scanning.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Bitmask** (in) The bitmask which should be written to Matrixrows
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ScanMatrix(brp_protocol protocol, unsigned _input_Bitmask);
#else
brp_errcode brp_DHWCtrlLegacy_ScanMatrix(brp_DHWCtrlLegacy_ScanMatrix_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlLegacy_GetReaderChipType_ChipType* ChipType;
} brp_DHWCtrlLegacy_GetReaderChipType_t;
/**
 * Returns the RC reader chip type.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ChipType** (out) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_GetReaderChipType(brp_protocol protocol, brp_DHWCtrlLegacy_GetReaderChipType_ChipType* ChipType);
#else
brp_errcode brp_DHWCtrlLegacy_GetReaderChipType(brp_DHWCtrlLegacy_GetReaderChipType_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Ant;
} brp_DHWCtrlLegacy_SelectAntenna_t;
/**
 * Switch external antenna.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Ant** (in) Antenna that should be activated (0 or 1)
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_SelectAntenna(brp_protocol protocol, unsigned _input_Ant);
#else
brp_errcode brp_DHWCtrlLegacy_SelectAntenna(brp_DHWCtrlLegacy_SelectAntenna_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlLegacy_GetSamType_ChipType* ChipType;
} brp_DHWCtrlLegacy_GetSamType_t;
/**
 * Returns the RC reader chip type
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ChipType** (out) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_GetSamType(brp_protocol protocol, brp_DHWCtrlLegacy_GetSamType_ChipType* ChipType);
#else
brp_errcode brp_DHWCtrlLegacy_GetSamType(brp_DHWCtrlLegacy_GetSamType_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlLegacy_HfAcquire_ModuleId ModuleId;
} brp_DHWCtrlLegacy_HfAcquire_t;
/**
 * Acquire specific HF Subsystem.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ModuleId** (in) HF subsystem to activate
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_HfAcquire(brp_protocol protocol, brp_DHWCtrlLegacy_HfAcquire_ModuleId _input_ModuleId);
#else
brp_errcode brp_DHWCtrlLegacy_HfAcquire(brp_DHWCtrlLegacy_HfAcquire_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
	brp_buf Data;
	size_t Data_len;
} brp_DHWCtrlLegacy_EepromWrite_t;
/**
 * Writes data to an arbitrary address in the EEPROM.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) Address of block to write.
 *   - **Data** (in) Data to write into the EEPROM.
 *   - **Data_len** (in) Length of **Data** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_EepromWrite(brp_protocol protocol, unsigned _input_Address, brp_buf _input_Data, size_t _input_Data_len);
#else
brp_errcode brp_DHWCtrlLegacy_EepromWrite(brp_DHWCtrlLegacy_EepromWrite_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Device;
	unsigned* PageCount;
	unsigned* PageSize;
} brp_DHWCtrlLegacy_DataflashGetSize_t;
/**
 * Retrieves the flash size.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Device** (in) Flash device number.
 *   - **PageCount** (out) Number of pages.
 *   - **PageSize** (out) Size of a page.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DataflashGetSize(brp_protocol protocol, unsigned _input_Device, unsigned* PageCount, unsigned* PageSize);
#else
brp_errcode brp_DHWCtrlLegacy_DataflashGetSize(brp_DHWCtrlLegacy_DataflashGetSize_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Device;
	unsigned StartPage;
	unsigned Len;
} brp_DHWCtrlLegacy_DataflashErasePages_t;
/**
 * Erase a group of pages.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Device** (in) Flash device number.
 *   - **StartPage** (in) Number of first page to erase.
 *   - **Len** (in) Number of pages to erase.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DataflashErasePages(brp_protocol protocol, unsigned _input_Device, unsigned _input_StartPage, unsigned _input_Len);
#else
brp_errcode brp_DHWCtrlLegacy_DataflashErasePages(brp_DHWCtrlLegacy_DataflashErasePages_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Device;
	unsigned Page;
	unsigned StartAdr;
	unsigned Len;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_DataflashRead_t;
/**
 * Read data within a certain page.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Device** (in) Flash device number.
 *   - **Page** (in) Number of first page to erase.
 *   - **StartAdr** (in) Start address relative to page.
 *   - **Len** (in) Number of Bytes to read.
 *   - **Data** (out) Data read from the Dataflash.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DataflashRead(brp_protocol protocol, unsigned _input_Device, unsigned _input_Page, unsigned _input_StartAdr, unsigned _input_Len, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_DataflashRead(brp_DHWCtrlLegacy_DataflashRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Device;
	unsigned Mode;
	unsigned Page;
	unsigned StartAdr;
	brp_buf Data;
	size_t Data_len;
} brp_DHWCtrlLegacy_DataflashWrite_t;
/**
 * Write data to a certain page.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Device** (in) Flash device number.
 *   - **Mode** (in) Writing mode.
 *   - **Page** (in) Number of page to write to.
 *   - **StartAdr** (in) Start address relative to page.
 *   - **Data** (in) Data to write to the Dataflash.
 *   - **Data_len** (in) Length of **Data** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DataflashWrite(brp_protocol protocol, unsigned _input_Device, unsigned _input_Mode, unsigned _input_Page, unsigned _input_StartAdr, brp_buf _input_Data, size_t _input_Data_len);
#else
brp_errcode brp_DHWCtrlLegacy_DataflashWrite(brp_DHWCtrlLegacy_DataflashWrite_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned StartAdr;
	unsigned Len;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_EepromRead_t;
/**
 * Reads data from the EEPROM.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **StartAdr** (in) Address of block to read from.
 *   - **Len** (in) Number of Bytes to read.
 *   - **Data** (out) Data read from the EEPROM.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_EepromRead(brp_protocol protocol, unsigned _input_StartAdr, unsigned _input_Len, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_EepromRead(brp_DHWCtrlLegacy_EepromRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_SecurityAndConfigReset_t;
/**
 * Reset configuration incl. "Encryption and Authorization" settings.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_SecurityAndConfigReset(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_SecurityAndConfigReset(brp_DHWCtrlLegacy_SecurityAndConfigReset_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Port;
	unsigned Frequency;
} brp_DHWCtrlLegacy_PulseGenerate_t;
/**
 * Generates a pulse of specified frequency on a certain pin.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Port** (in) The number of the pin to access.
 *   - **Frequency** (in) The desired pulse frequency in kHz. Set to 0 to switch pulse off.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PulseGenerate(brp_protocol protocol, unsigned _input_Port, unsigned _input_Frequency);
#else
brp_errcode brp_DHWCtrlLegacy_PulseGenerate(brp_DHWCtrlLegacy_PulseGenerate_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitSer2_t;
/**
 * Initializes the serial2 module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitSer2(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitSer2(brp_DHWCtrlLegacy_InitSer2_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitRtc_t;
/**
 * Initializes the rtc module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitRtc(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitRtc(brp_DHWCtrlLegacy_InitRtc_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitLcdDrv_t;
/**
 * Initializes the display module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitLcdDrv(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitLcdDrv(brp_DHWCtrlLegacy_InitLcdDrv_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitRc_t;
/**
 * Initializes the rc module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitRc(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitRc(brp_DHWCtrlLegacy_InitRc_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitMf_t;
/**
 * Initializes the Mifare module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitMf(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitMf(brp_DHWCtrlLegacy_InitMf_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitIso14A_t;
/**
 * Initializes the ISO14443A module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitIso14A(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitIso14A(brp_DHWCtrlLegacy_InitIso14A_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitIso14B_t;
/**
 * Initializes the ISO14443B module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitIso14B(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitIso14B(brp_DHWCtrlLegacy_InitIso14B_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitIso15_t;
/**
 * Initializes the ISO15693 module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitIso15(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitIso15(brp_DHWCtrlLegacy_InitIso15_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitLg_t;
/**
 * Initializes the Legic module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitLg(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitLg(brp_DHWCtrlLegacy_InitLg_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitLga_t;
/**
 * Initializes the Legic Advant module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitLga(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitLga(brp_DHWCtrlLegacy_InitLga_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitDf_t;
/**
 * Initializes the dataflash module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitDf(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitDf(brp_DHWCtrlLegacy_InitDf_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitRc125_t;
/**
 * Initializes the RC125 module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitRc125(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitRc125(brp_DHWCtrlLegacy_InitRc125_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitCc_t;
/**
 * Initializes the TDA8007 or CCUART module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitCc(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitCc(brp_DHWCtrlLegacy_InitCc_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitUsbHost_t;
/**
 * Initializes the USB-Host module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitUsbHost(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitUsbHost(brp_DHWCtrlLegacy_InitUsbHost_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitNic_t;
/**
 * Initializes the Network Interface (NIC) module.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitNic(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitNic(brp_DHWCtrlLegacy_InitNic_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool Enable;
	bool Bug6WorkaroundEnabled;
} brp_DHWCtrlLegacy_BohEnable_t;
/**
 * Enables the BRP over HID interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Enable** (in) True if the interface should be enabled.
 *   - **Bug6WorkaroundEnabled** (in) Enable the workaround for BUG6.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_BohEnable(brp_protocol protocol, bool _input_Enable, bool _input_Bug6WorkaroundEnabled);
#else
brp_errcode brp_DHWCtrlLegacy_BohEnable(brp_DHWCtrlLegacy_BohEnable_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool Enable;
} brp_DHWCtrlLegacy_NicEnable_t;
/**
 * Enables the Network Interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Enable** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_NicEnable(brp_protocol protocol, bool _input_Enable);
#else
brp_errcode brp_DHWCtrlLegacy_NicEnable(brp_DHWCtrlLegacy_NicEnable_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* ChipType;
	size_t* ChipType_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_NicGetChipType_t;
/**
 * Returns the chip type of the Network Interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ChipType** (out) The Chip type characterizing byte stream (DM9006: 0x 0A 46 90 06 02).
 *   - **ChipType_len** (out) Length of **ChipType** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_NicGetChipType(brp_protocol protocol, brp_buf* ChipType, size_t* ChipType_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_NicGetChipType(brp_DHWCtrlLegacy_NicGetChipType_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned* LinkStatus;
} brp_DHWCtrlLegacy_NicGetLinkStatus_t;
/**
 * Retrieve the Link status of the Network Interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **LinkStatus** (out) Link status: Bit0 = Port0, Bit1 = Port1; Bit is set if port is linked.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_NicGetLinkStatus(brp_protocol protocol, unsigned* LinkStatus);
#else
brp_errcode brp_DHWCtrlLegacy_NicGetLinkStatus(brp_DHWCtrlLegacy_NicGetLinkStatus_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf SendData;
	size_t SendData_len;
} brp_DHWCtrlLegacy_NicSend_t;
/**
 * Sends a frame via the Network Interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SendData** (in) Ethernet frame to send via NIC.
 *   - **SendData_len** (in) Length of **SendData** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_NicSend(brp_protocol protocol, brp_buf _input_SendData, size_t _input_SendData_len);
#else
brp_errcode brp_DHWCtrlLegacy_NicSend(brp_DHWCtrlLegacy_NicSend_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Timeout;
	brp_buf* RecvData;
	size_t* RecvData_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_NicReceive_t;
/**
 * Receives a frame from the Network Interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Timeout** (in) Max. time in ms to wait for reception.
 *   - **RecvData** (out) The received frame without ethernet CRC.
 *   - **RecvData_len** (out) Length of **RecvData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_NicReceive(brp_protocol protocol, unsigned _input_Timeout, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_NicReceive(brp_DHWCtrlLegacy_NicReceive_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf MAC;
} brp_DHWCtrlLegacy_NicSetMAC_t;
/**
 * Set the MAC address of the Network Interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **MAC** (in) MAC address.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_NicSetMAC(brp_protocol protocol, brp_buf _input_MAC);
#else
brp_errcode brp_DHWCtrlLegacy_NicSetMAC(brp_DHWCtrlLegacy_NicSetMAC_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Speed;
} brp_DHWCtrlLegacy_ApspiSetSpeed_t;
/**
 * Set the speed of SPI programming mode.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Speed** (in) SPI speed in kbit/s.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ApspiSetSpeed(brp_protocol protocol, unsigned _input_Speed);
#else
brp_errcode brp_DHWCtrlLegacy_ApspiSetSpeed(brp_DHWCtrlLegacy_ApspiSetSpeed_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool Enable;
} brp_DHWCtrlLegacy_ApspiEnable_t;
/**
 * Enables/disables the SPI programming mode of a connected slave AVR.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Enable** (in) True if the programming mode should be enabled.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ApspiEnable(brp_protocol protocol, bool _input_Enable);
#else
brp_errcode brp_DHWCtrlLegacy_ApspiEnable(brp_DHWCtrlLegacy_ApspiEnable_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned CmdCode;
	unsigned Address;
	unsigned CmdData;
	unsigned Delay;
} brp_DHWCtrlLegacy_ApspiSingleSend_t;
/**
 * Send a single SPI programming instruction.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CmdCode** (in) command code of instruction.
 *   - **Address** (in) target address of instruction.
 *   - **CmdData** (in) data byte of instruction.
 *   - **Delay** (in) Delay to assert before next command in milliseconds.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ApspiSingleSend(brp_protocol protocol, unsigned _input_CmdCode, unsigned _input_Address, unsigned _input_CmdData, unsigned _input_Delay);
#else
brp_errcode brp_DHWCtrlLegacy_ApspiSingleSend(brp_DHWCtrlLegacy_ApspiSingleSend_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned CmdCode;
	unsigned Address;
	unsigned* CmdData;
} brp_DHWCtrlLegacy_ApspiSingleRecv_t;
/**
 * Send a single SPI programming instruction and receive one data byte.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CmdCode** (in) command code of instruction.
 *   - **Address** (in) target address of instruction.
 *   - **CmdData** (out) data Byte received.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ApspiSingleRecv(brp_protocol protocol, unsigned _input_CmdCode, unsigned _input_Address, unsigned* CmdData);
#else
brp_errcode brp_DHWCtrlLegacy_ApspiSingleRecv(brp_DHWCtrlLegacy_ApspiSingleRecv_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned CmdCodeA;
	unsigned CmdCodeB;
	unsigned Address;
	brp_buf CmdData;
	size_t CmdData_len;
	unsigned Delay;
} brp_DHWCtrlLegacy_ApspiAlternateSend_t;
/**
 * Send alternately SPI programming instructions. First CmdCodeA with address adr and the first byte in the data buffer, then CmdCodeB with the same address and the second byte in the buffer is sent. After that the address will be incremented. This is repeated as long as data bytes are in the buffer.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CmdCodeA** (in) command code of first instruction.
 *   - **CmdCodeB** (in) command code of second instruction.
 *   - **Address** (in) start address.
 *   - **CmdData** (in) collection of all data bytes to send.
 *   - **CmdData_len** (in) Length of **CmdData** (in bytes).
 *   - **Delay** (in) Delay to assert before next command in milliseconds.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ApspiAlternateSend(brp_protocol protocol, unsigned _input_CmdCodeA, unsigned _input_CmdCodeB, unsigned _input_Address, brp_buf _input_CmdData, size_t _input_CmdData_len, unsigned _input_Delay);
#else
brp_errcode brp_DHWCtrlLegacy_ApspiAlternateSend(brp_DHWCtrlLegacy_ApspiAlternateSend_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned CmdCodeA;
	unsigned CmdCodeB;
	unsigned Address;
	unsigned CmdDataLen;
	brp_buf* CmdData;
	size_t* CmdData_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_ApspiAlternateRecv_t;
/**
 * Send alternately SPI programming instructions and receive data bytes. Works similar to ApspiAlternateSend.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CmdCodeA** (in) command code of first instruction.
 *   - **CmdCodeB** (in) command code of second instruction.
 *   - **Address** (in) start address.
 *   - **CmdDataLen** (in) Number of data Bytes that should be retrieved.
 *   - **CmdData** (out) collection of all data Bytes received.
 *   - **CmdData_len** (out) Length of **CmdData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ApspiAlternateRecv(brp_protocol protocol, unsigned _input_CmdCodeA, unsigned _input_CmdCodeB, unsigned _input_Address, unsigned _input_CmdDataLen, brp_buf* CmdData, size_t* CmdData_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_ApspiAlternateRecv(brp_DHWCtrlLegacy_ApspiAlternateRecv_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool Enable;
} brp_DHWCtrlLegacy_PdiEnable_t;
/**
 * Enables/disables the PDI programming mode of a connected target AVR.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Enable** (in) True if the programming mode should be enabled.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiEnable(brp_protocol protocol, bool _input_Enable);
#else
brp_errcode brp_DHWCtrlLegacy_PdiEnable(brp_DHWCtrlLegacy_PdiEnable_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_PdiEraseDevice_t;
/**
 * Erases the target chip device.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiEraseDevice(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_PdiEraseDevice(brp_DHWCtrlLegacy_PdiEraseDevice_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Adr;
	unsigned ReadLen;
	brp_buf* ReadData;
	size_t* ReadData_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_PdiReadFlash_t;
/**
 * Read flash memory from target device.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Adr** (in) start address.
 *   - **ReadLen** (in) number of bytes to read
 *   - **ReadData** (out) Data Bytes read from device.
 *   - **ReadData_len** (out) Length of **ReadData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiReadFlash(brp_protocol protocol, unsigned _input_Adr, unsigned _input_ReadLen, brp_buf* ReadData, size_t* ReadData_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_PdiReadFlash(brp_DHWCtrlLegacy_PdiReadFlash_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Adr;
} brp_DHWCtrlLegacy_PdiEraseFlashPage_t;
/**
 * Erase flash page.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Adr** (in) page address.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiEraseFlashPage(brp_protocol protocol, unsigned _input_Adr);
#else
brp_errcode brp_DHWCtrlLegacy_PdiEraseFlashPage(brp_DHWCtrlLegacy_PdiEraseFlashPage_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Adr;
	brp_buf WriteData;
	size_t WriteData_len;
} brp_DHWCtrlLegacy_PdiWriteFlashPage_t;
/**
 * Write to internal flash page buffer.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Adr** (in) start address.
 *   - **WriteData** (in) Data Bytes to be written.
 *   - **WriteData_len** (in) Length of **WriteData** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiWriteFlashPage(brp_protocol protocol, unsigned _input_Adr, brp_buf _input_WriteData, size_t _input_WriteData_len);
#else
brp_errcode brp_DHWCtrlLegacy_PdiWriteFlashPage(brp_DHWCtrlLegacy_PdiWriteFlashPage_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Adr;
} brp_DHWCtrlLegacy_PdiProgramFlashPage_t;
/**
 * Program flash page. Page must be written with PdiWriteFlashPage before.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Adr** (in) page address.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiProgramFlashPage(brp_protocol protocol, unsigned _input_Adr);
#else
brp_errcode brp_DHWCtrlLegacy_PdiProgramFlashPage(brp_DHWCtrlLegacy_PdiProgramFlashPage_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Adr;
	unsigned ReadLen;
	brp_buf* ReadData;
	size_t* ReadData_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_PdiReadEeprom_t;
/**
 * Read eeprom memory from target device.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Adr** (in) start address.
 *   - **ReadLen** (in) number of bytes to read
 *   - **ReadData** (out) Data Bytes read from device.
 *   - **ReadData_len** (out) Length of **ReadData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiReadEeprom(brp_protocol protocol, unsigned _input_Adr, unsigned _input_ReadLen, brp_buf* ReadData, size_t* ReadData_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_PdiReadEeprom(brp_DHWCtrlLegacy_PdiReadEeprom_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Adr;
	brp_buf WriteData;
	size_t WriteData_len;
} brp_DHWCtrlLegacy_PdiProgramEepromPage_t;
/**
 * Write an eeprom page to target device.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Adr** (in) start address.
 *   - **WriteData** (in) Data Bytes to be written.
 *   - **WriteData_len** (in) Length of **WriteData** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiProgramEepromPage(brp_protocol protocol, unsigned _input_Adr, brp_buf _input_WriteData, size_t _input_WriteData_len);
#else
brp_errcode brp_DHWCtrlLegacy_PdiProgramEepromPage(brp_DHWCtrlLegacy_PdiProgramEepromPage_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Adr;
	unsigned ReadLen;
	brp_buf* ReadData;
	size_t* ReadData_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_PdiReadFuses_t;
/**
 * Read fuse memory from target device.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Adr** (in) start address.
 *   - **ReadLen** (in) number of bytes to read
 *   - **ReadData** (out) Data Bytes read from device.
 *   - **ReadData_len** (out) Length of **ReadData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiReadFuses(brp_protocol protocol, unsigned _input_Adr, unsigned _input_ReadLen, brp_buf* ReadData, size_t* ReadData_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_PdiReadFuses(brp_DHWCtrlLegacy_PdiReadFuses_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Adr;
	unsigned Fuse;
} brp_DHWCtrlLegacy_PdiWriteFuse_t;
/**
 * Write a fuse byte to target device.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Adr** (in) start address.
 *   - **Fuse** (in) Fuse content to be written.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiWriteFuse(brp_protocol protocol, unsigned _input_Adr, unsigned _input_Fuse);
#else
brp_errcode brp_DHWCtrlLegacy_PdiWriteFuse(brp_DHWCtrlLegacy_PdiWriteFuse_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned* PageSize;
} brp_DHWCtrlLegacy_FlashGetPageSize_t;
/**
 * Retrieves the page size of the program flash.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PageSize** (out) Size of a page.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_FlashGetPageSize(brp_protocol protocol, unsigned* PageSize);
#else
brp_errcode brp_DHWCtrlLegacy_FlashGetPageSize(brp_DHWCtrlLegacy_FlashGetPageSize_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned StartAdr;
	unsigned Len;
} brp_DHWCtrlLegacy_FlashErasePage_t;
/**
 * Erases one or several consecutive program flash pages.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **StartAdr** (in) Address of first page to erase. Has to be a multiple of the page size.
 *   - **Len** (in) Number of Bytes to erase. Should be always a multiple of the page size.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_FlashErasePage(brp_protocol protocol, unsigned _input_StartAdr, unsigned _input_Len);
#else
brp_errcode brp_DHWCtrlLegacy_FlashErasePage(brp_DHWCtrlLegacy_FlashErasePage_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned StartAdr;
	unsigned Len;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_FlashRead_t;
/**
 * Read data from program flash.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **StartAdr** (in) Start address of the data to read.
 *   - **Len** (in) Number of Bytes to read.
 *   - **Data** (out) Data read from the program flash.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_FlashRead(brp_protocol protocol, unsigned _input_StartAdr, unsigned _input_Len, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_FlashRead(brp_DHWCtrlLegacy_FlashRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned StartAdr;
	brp_buf Data;
	size_t Data_len;
} brp_DHWCtrlLegacy_FlashWritePage_t;
/**
 * Write to a temporary page buffer. Can be executed several times until the page buffer is filled.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **StartAdr** (in) Start address the data should be written to.
 *   - **Data** (in) Data to write to the page buffer.
 *   - **Data_len** (in) Length of **Data** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_FlashWritePage(brp_protocol protocol, unsigned _input_StartAdr, brp_buf _input_Data, size_t _input_Data_len);
#else
brp_errcode brp_DHWCtrlLegacy_FlashWritePage(brp_DHWCtrlLegacy_FlashWritePage_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned StartAdr;
} brp_DHWCtrlLegacy_FlashProgramPage_t;
/**
 * Program a page to program flash. The data has to be written to the temporary page buffer with FlashWritePage before.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **StartAdr** (in) Start address of the page that should be programmed. Has to be a multiple of the page size.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_FlashProgramPage(brp_protocol protocol, unsigned _input_StartAdr);
#else
brp_errcode brp_DHWCtrlLegacy_FlashProgramPage(brp_DHWCtrlLegacy_FlashProgramPage_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned RegAdr;
	unsigned* RegValue;
} brp_DHWCtrlLegacy_RegisterRead_t;
/**
 * Read processor register.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **RegAdr** (in) Address of register to read.
 *   - **RegValue** (out) Value of register.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_RegisterRead(brp_protocol protocol, unsigned _input_RegAdr, unsigned* RegValue);
#else
brp_errcode brp_DHWCtrlLegacy_RegisterRead(brp_DHWCtrlLegacy_RegisterRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned RegAdr;
	unsigned RegValue;
} brp_DHWCtrlLegacy_RegisterWrite_t;
/**
 * Write processor register.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **RegAdr** (in) Address of register to write.
 *   - **RegValue** (in) Value of register to write.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_RegisterWrite(brp_protocol protocol, unsigned _input_RegAdr, unsigned _input_RegValue);
#else
brp_errcode brp_DHWCtrlLegacy_RegisterWrite(brp_DHWCtrlLegacy_RegisterWrite_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlLegacy_AesWrapKey_WrappedKeyNr WrappedKeyNr;
	brp_buf Key;
	size_t Key_len;
	brp_buf* WrappedKey;
	size_t* WrappedKey_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_AesWrapKey_t;
/**
 * Wraps an AES key for secure storage
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **WrappedKeyNr** (in) 
 *   - **Key** (in) Key to use for wrapping
 *   - **Key_len** (in) Length of **Key** (in bytes).
 *   - **WrappedKey** (out) Wrapped key
 *   - **WrappedKey_len** (out) Length of **WrappedKey** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_AesWrapKey(brp_protocol protocol, brp_DHWCtrlLegacy_AesWrapKey_WrappedKeyNr _input_WrappedKeyNr, brp_buf _input_Key, size_t _input_Key_len, brp_buf* WrappedKey, size_t* WrappedKey_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_AesWrapKey(brp_DHWCtrlLegacy_AesWrapKey_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlLegacy_AesEncrypt_WrappedKeyNr WrappedKeyNr;
	brp_buf Block;
	size_t Block_len;
	brp_buf Key;
	size_t Key_len;
	brp_buf* EncBlock;
	size_t* EncBlock_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_AesEncrypt_t;
/**
 * Encrypts a block
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **WrappedKeyNr** (in) 
 *   - **Block** (in) Block to encrypt
 *   - **Block_len** (in) Length of **Block** (in bytes).
 *   - **Key** (in) Key to use for encryption
 *   - **Key_len** (in) Length of **Key** (in bytes).
 *   - **EncBlock** (out) Encrypted block
 *   - **EncBlock_len** (out) Length of **EncBlock** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_AesEncrypt(brp_protocol protocol, brp_DHWCtrlLegacy_AesEncrypt_WrappedKeyNr _input_WrappedKeyNr, brp_buf _input_Block, size_t _input_Block_len, brp_buf _input_Key, size_t _input_Key_len, brp_buf* EncBlock, size_t* EncBlock_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_AesEncrypt(brp_DHWCtrlLegacy_AesEncrypt_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlLegacy_AesDecrypt_WrappedKeyNr WrappedKeyNr;
	brp_buf EncBlock;
	size_t EncBlock_len;
	brp_buf Key;
	size_t Key_len;
	brp_buf* Block;
	size_t* Block_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_AesDecrypt_t;
/**
 * Decrypts a block
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **WrappedKeyNr** (in) 
 *   - **EncBlock** (in) Encrypted block to decrypt
 *   - **EncBlock_len** (in) Length of **EncBlock** (in bytes).
 *   - **Key** (in) Key to use for decryption
 *   - **Key_len** (in) Length of **Key** (in bytes).
 *   - **Block** (out) Decrypted block
 *   - **Block_len** (out) Length of **Block** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_AesDecrypt(brp_protocol protocol, brp_DHWCtrlLegacy_AesDecrypt_WrappedKeyNr _input_WrappedKeyNr, brp_buf _input_EncBlock, size_t _input_EncBlock_len, brp_buf _input_Key, size_t _input_Key_len, brp_buf* Block, size_t* Block_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_AesDecrypt(brp_DHWCtrlLegacy_AesDecrypt_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned** HWCIdLst;
	size_t* HWCIdLst_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_GetPlatformId2_t;
/**
 * This command retrieves the PlatformId2. A list of all supported HardwareComponents is returned.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **HWCIdLst** (out) 
 *   - **HWCIdLst_len** (out) Number of elements in **HWCIdLst**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_GetPlatformId2(brp_protocol protocol, unsigned** HWCIdLst, size_t* HWCIdLst_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_GetPlatformId2(brp_DHWCtrlLegacy_GetPlatformId2_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned* LoaderBaudrate;
} brp_DHWCtrlLegacy_GetProdLoader_t;
/**
 * Returns the baudrate Byte of the production-loader.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **LoaderBaudrate** (out) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_GetProdLoader(brp_protocol protocol, unsigned* LoaderBaudrate);
#else
brp_errcode brp_DHWCtrlLegacy_GetProdLoader(brp_DHWCtrlLegacy_GetProdLoader_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_StartProdLoader_t;
/**
 * Starts the production-loader.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_StartProdLoader(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_StartProdLoader(brp_DHWCtrlLegacy_StartProdLoader_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf CommandList;
	size_t CommandList_len;
	unsigned* Status;
	brp_buf* Response;
	size_t* Response_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_Run_t;
/**
 * Executes a list of commands. The commands are stored sequentially in the buffer. Every command has as a header the command code and the length of the following parameters. Both are given in bytes. It is possible to execute every DHWCtrl command through this interface.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CommandList** (in) Commands to execute.
 *   - **CommandList_len** (in) Length of **CommandList** (in bytes).
 *   - **Status** (out) 
 *   - **Response** (out) Collection of all answers.
 *   - **Response_len** (out) Length of **Response** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Run(brp_protocol protocol, brp_buf _input_CommandList, size_t _input_CommandList_len, unsigned* Status, brp_buf* Response, size_t* Response_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_Run(brp_DHWCtrlLegacy_Run_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned* Status;
	brp_buf* Response;
	size_t* Response_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_GetStartupRun_t;
/**
 * Returns the result of the execution of DHWCtrl-commands at the startup.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Status** (out) 
 *   - **Response** (out) Collection of all answers.
 *   - **Response_len** (out) Length of **Response** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_GetStartupRun(brp_protocol protocol, unsigned* Status, brp_buf* Response, size_t* Response_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_GetStartupRun(brp_DHWCtrlLegacy_GetStartupRun_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_InitBgm_t;
/**
 * Initializes the Bluetooth BGM12X chip.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitBgm(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_InitBgm(brp_DHWCtrlLegacy_InitBgm_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf Cmd;
	size_t Cmd_len;
	unsigned Timeout;
	brp_buf* Rsp;
	size_t* Rsp_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_BgmExec_t;
/**
 * Execute a Bgm12X API command.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Cmd** (in) Command data Bytes to be sent.
 *   - **Cmd_len** (in) Length of **Cmd** (in bytes).
 *   - **Timeout** (in) Maximum time to wait for receiving a response.
 *   - **Rsp** (out) Received data Bytes.
 *   - **Rsp_len** (out) Length of **Rsp** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_BgmExec(brp_protocol protocol, brp_buf _input_Cmd, size_t _input_Cmd_len, unsigned _input_Timeout, brp_buf* Rsp, size_t* Rsp_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_BgmExec(brp_DHWCtrlLegacy_BgmExec_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* BootloaderString;
	size_t* BootloaderString_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_Sm4x00BootloaderStart_t;
/**
 * Start SM4x00 Bootloader.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **BootloaderString** (out) Received Bootloader TLV string.
 *   - **BootloaderString_len** (out) Length of **BootloaderString** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Sm4x00BootloaderStart(brp_protocol protocol, brp_buf* BootloaderString, size_t* BootloaderString_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_Sm4x00BootloaderStart(brp_DHWCtrlLegacy_Sm4x00BootloaderStart_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_DHWCtrlLegacy_Sm4x00EraseFlash_t;
/**
 * Erase SM4x00 Flash. Must be issued directly after DHWCtrlLegacy.Sm4x00BootloaderStart. Erasing lasts about 20-30 seconds. Use DHWCtrlLegacy.Sm4x00WaitForFlashErase to find out when it has been finished.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Sm4x00EraseFlash(brp_protocol protocol);
#else
brp_errcode brp_DHWCtrlLegacy_Sm4x00EraseFlash(brp_DHWCtrlLegacy_Sm4x00EraseFlash_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Timeout;
	brp_buf* EraseResponse;
	size_t* EraseResponse_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_Sm4x00WaitForFlashErase_t;
/**
 * Check if flash erasing has been finished.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Timeout** (in) 
 *   - **EraseResponse** (out) Received response from SM4x00 if erasing has finished. Response is empty if erasing is still in progress after Timeout expired.
 *   - **EraseResponse_len** (out) Length of **EraseResponse** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Sm4x00WaitForFlashErase(brp_protocol protocol, unsigned _input_Timeout, brp_buf* EraseResponse, size_t* EraseResponse_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_Sm4x00WaitForFlashErase(brp_DHWCtrlLegacy_Sm4x00WaitForFlashErase_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool IsLast;
	brp_buf FwBlock;
	size_t FwBlock_len;
	brp_buf* ProgramResponse;
	size_t* ProgramResponse_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_Sm4x00ProgramBlock_t;
/**
 * Program one 128 byte block of SM4x00 firmware.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **IsLast** (in) Flag that signals if this is last block.
 *   - **FwBlock** (in) Firmware block to be programmed.
 *   - **FwBlock_len** (in) Length of **FwBlock** (in bytes).
 *   - **ProgramResponse** (out) Received response from SM4x00.
 *   - **ProgramResponse_len** (out) Length of **ProgramResponse** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Sm4x00ProgramBlock(brp_protocol protocol, bool _input_IsLast, brp_buf _input_FwBlock, size_t _input_FwBlock_len, brp_buf* ProgramResponse, size_t* ProgramResponse_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_Sm4x00ProgramBlock(brp_DHWCtrlLegacy_Sm4x00ProgramBlock_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Timeout;
	brp_buf* Rsp;
	size_t* Rsp_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_BgmRead_t;
/**
 * Read from Bgm12X.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Timeout** (in) Maximum time to wait for receiving data.
 *   - **Rsp** (out) Received data Bytes.
 *   - **Rsp_len** (out) Length of **Rsp** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_BgmRead(brp_protocol protocol, unsigned _input_Timeout, brp_buf* Rsp, size_t* Rsp_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_BgmRead(brp_DHWCtrlLegacy_BgmRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
	unsigned Length;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_DHWCtrlLegacy_Rc5180EepromRead_t;
/**
 * Reads EEPROM Data from RCxxx (PNxxx).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) EEPROM address
 *   - **Length** (in) Number of bytes to read
 *   - **Data** (out) EEPROM data
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Rc5180EepromRead(brp_protocol protocol, unsigned _input_Address, unsigned _input_Length, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrlLegacy_Rc5180EepromRead(brp_DHWCtrlLegacy_Rc5180EepromRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Address;
	brp_buf Data;
	size_t Data_len;
} brp_DHWCtrlLegacy_Rc5180EepromWrite_t;
/**
 * Writes EEPROM Data to the RCxxx (PNxxx).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (in) EEPROM address
 *   - **Data** (in) EEPROM data
 *   - **Data_len** (in) Length of **Data** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Rc5180EepromWrite(brp_protocol protocol, unsigned _input_Address, brp_buf _input_Data, size_t _input_Data_len);
#else
brp_errcode brp_DHWCtrlLegacy_Rc5180EepromWrite(brp_DHWCtrlLegacy_Rc5180EepromWrite_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */