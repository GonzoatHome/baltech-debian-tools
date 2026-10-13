/**
 * @file
 * With the _Sys_ command group, you can interact with the reader itself. You can e.g. retrieve reader information, set up its behavior, and control it during runtime. 
 * 
 * For a quick overview, please see our list of [ most important Sys commands](https://docs.baltech.de/developers/run-sys-cmds.html).
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_SYS_H__
#define __BRP_BALTECH_SDK_CMDS_SYS_H__
#include "../typedefs.h"
/**
 * There's not enough space to store the reader's configuration values.
 */
#define BRP_Sys_ErrCfgFull BRP_ERR_STATUS(0x0000, 0x01)
/**
 * Reading/writing to the internal memory failed.  
 * 
 * 
 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
 */
#define BRP_Sys_ErrCfgAccess BRP_ERR_STATUS(0x0000, 0x02)
/**
 * The meaning of this status code varies depending on the access mode: 
 * 
 *   * _Read access:_ The desired key/value couldn't be found in the configuration. 
 *   * _Write access:_ The key/value ID is invalid. The value couldn't be set.
 */
#define BRP_Sys_ErrCfgNotFound BRP_ERR_STATUS(0x0000, 0x03)
/**
 * The format of the configuration file (BEC file) is invalid.
 */
#define BRP_Sys_ErrInvalidCfgBlock BRP_ERR_STATUS(0x0000, 0x04)
/**
 * Memory access denied. The configuration value ID is too high (> 0x80).
 */
#define BRP_Sys_ErrCfgAccessDenied BRP_ERR_STATUS(0x0000, 0x05)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Register cannot be modified or doesn't exist.
 */
#define BRP_Sys_ErrRegAccess BRP_ERR_STATUS(0x0000, 0x06)
#endif  // BALTECH_SDK_INTERNAL
/**
 * The selected protocol isn't supported by the current firmware.
 */
#define BRP_Sys_ErrInvalidProtocol BRP_ERR_STATUS(0x0000, 0x07)
/**
 * This feature isn't supported by the reader hardware.
 */
#define BRP_Sys_ErrNotSupportedByHardware BRP_ERR_STATUS(0x0000, 0x08)
/**
 * Restoring the reader's factory settings failed.
 */
#define BRP_Sys_ErrFactsetRestore BRP_ERR_STATUS(0x0000, 0x09)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Sys.CfgLoadBlock was run with an invalid Config Security Code, i.e. the configuration you're trying to deploy is not a new version of the existing configuration, but a completely different configuration ([ learn more](https://docs.baltech.de/project-setup/security.html#config-security-code)).
 */
#define BRP_Sys_ErrCfgConfigSecurityCode BRP_ERR_STATUS(0x0000, 0x0A)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Sys.CfgLoadBlock was run with a configuration version that is older than the one currently deployed ([ learn more](https://docs.baltech.de/project-setup/security.html#configuration-updates-with-rollback-prevention)).
 */
#define BRP_Sys_ErrCfgVersion BRP_ERR_STATUS(0x0000, 0x0B)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * The command can't be run in the current (CfgLoadBlock) state, i.e.  Sys.CfgLoadFinish must be run after  Sys.CfgLoadPrepare.
 */
#define BRP_Sys_ErrCfgLoadWrongState BRP_ERR_STATUS(0x0000, 0x0C)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * The CRC of the firmware is invalid. This error can only be returned by the Sys.GetFwCrc command.
 */
#define BRP_Sys_ErrInvalidFwCrc BRP_ERR_STATUS(0x0000, 0x7F)
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned* MaxSendSize;
	unsigned* MaxRecvSize;
	unsigned* TotalSize;
} brp_Sys_GetBufferSize_t;
/**
 * This command returns the maximum sizes of [command](https://docs.baltech.de/developers/brp-command-frame.html) and [response](https://docs.baltech.de/developers/brp-response-frame.html) frames that the reader can send and receive. This information is indicated by 3 return values: _MaxSendSize_ , _MaxRecvSize_ , and _TotalSize_. They're determined by the firmware. 
 * 
 * **You need to comply with _all_ 3 values in your application: It's not enough if the command frame size and the expected response frame size are each smaller than or equal to _MaxSendSize_ and _MaxRecvSize_ , respectively. Their combined frame size must not exceed _TotalSize_ either. If _all_ 3 values are < 128 bytes, you don't need to use _Sys_GetBufferSize_ because this is the minimum size that all BALTECH readers support.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **MaxSendSize** (out) Maximum number of bytes in command frame
 *   - **MaxRecvSize** (out) Maximum number of bytes in response frame
 *   - **TotalSize** (out) Maximum number of bytes in command and response frame combined
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetBufferSize(brp_protocol protocol, unsigned* MaxSendSize, unsigned* MaxRecvSize, unsigned* TotalSize);
#else
brp_errcode brp_Sys_GetBufferSize(brp_Sys_GetBufferSize_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned OffDuration;
} brp_Sys_HFReset_t;
/**
 * This command turns the HF antenna off or on. 
 * 
 * **You cannot use it in combination with VHL commands .**
 * 
 * The behavior is as follows: 
 * 
 *   * When the antenna is _on_ , the command turns it off for the time defined in _OffDuration_. To turn it off permanently, set the value to 0. 
 *   * When the antenna is _off_ , the command turns it on. To do so, set _OffDuration_ > 0\. 
 * 
 * 
 * 
 * **The HF antenna is turned _off_ after booting. If, however, the reader is configured for[ Autoread](https://docs.baltech.de/developers/map-autoread.html) , the HF antenna is turned on automatically during initialization, so you don't need to actively turn it on. This is the default behavior as of ID-engine Z.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **OffDuration** (in) Time (in ms) to turn off the HF antenna. To turn it off permanently, set the value to 0.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_HFReset(brp_protocol protocol, unsigned _input_OffDuration);
#else
brp_errcode brp_Sys_HFReset(brp_Sys_HFReset_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Sys_Reset_t;
/**
 * This command reboots the reader. Its main purpose is to apply configuration changes made e.g. with Sys.CfgSetValue. 
 * 
 * ## Close and reopen the connection after running Sys.Reset
 * 
 * Close the connection to the reader immediately after running _Sys.Reset_. Depending on the protocol, the connection may be lost. In this case, you need to reconnect.
 * 
 * ### When to reconnect?
 * 
 * The reset takes about 500 to 1000 ms to complete. Thus, we recommend you wait about 100 ms after closing the connection. Then try to reconnect every 100 ms.
 * 
 * ### When is a reconnect successful?
 * 
 * Consider a reconnect successful as soon as the reader executes a command. Opening a port is not a guarantee that you've reconnected.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_Reset(brp_protocol protocol);
#else
brp_errcode brp_Sys_Reset(brp_Sys_Reset_t params);
#endif
typedef struct {
	brp_protocol protocol;
	char** Info;
	brp_mempool *mempool;
} brp_Sys_GetInfo_t;
/**
 * This command retrieves the firmware string of the reader, which holds information about the reader firmware and serial number. It has the following format: 
 * 
 * _1xxx nnnnnnnnn r.rr.rr dd/dd/dd ssssssss_
 * 
 * _1xxx_ |  ID of firmware (4 digits)   
 * ---|---  
 * _nnnnnnnnn_ |  Name of firmware (9 alphanumeric characters/spaces)   
 * _r.rr.rr_ |  Release of firmware (major release, minor release, build ID)   
 * _dd/dd/dd_ |  Date of release   
 * _ssssssss_ |  Serial number of reader (8 digits)   
 *   
 * **The combination of ID and release uniquely identifies any firmware version. You can use this information e.g. to retrieve the firmware in our download area.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Info** (out) 
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetInfo(brp_protocol protocol, char** Info, brp_mempool *mempool);
#else
brp_errcode brp_Sys_GetInfo(brp_Sys_GetInfo_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Sys_GetBootStatus_BootStatus* BootStatus;
} brp_Sys_GetBootStatus_t;
/**
 * This command retrieves the boot status of the reader, i.e. it describes the state of each component of the reader's hardware. Every bit in the returned value corresponds to a reader-internal component or a system error. If the component couldn't be initialized or the system error is triggered, the related bit is set. 
 * 
 *   * _Error bits (0-23):_ You have to solve these issues before you can use the reader. 
 *   * _Warning bits (24-31):_ The reader may still work properly. However, we highly recommend you solve these issues as well.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **BootStatus** (out) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetBootStatus(brp_protocol protocol, brp_Sys_GetBootStatus_BootStatus* BootStatus);
#else
brp_errcode brp_Sys_GetBootStatus(brp_Sys_GetBootStatus_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_IoPortBitmask* PortMask;
} brp_Sys_GetPort_t;
/**
 * **Please use UI.Sense instead of this command for new applications.**
 * 
 * This command retrieves the logic state for the custom I/O ports of the module. Each module can have up to 16 ports, with each bit of the returned _PortMask_ value corresponding to a port. _1_ corresponds to high state (VCC), while _0_ corresponds to low state (GND).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PortMask** (out) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetPort(brp_protocol protocol, brp_IoPortBitmask* PortMask);
#else
brp_errcode brp_Sys_GetPort(brp_Sys_GetPort_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_IoPortBitmask PortMask;
} brp_Sys_SetPort_t;
/**
 * **Please use UI.Enable and UI.Disable instead of this command for new applications.**
 * 
 * Sets/clears custom I/O ports of the module. Every bit in _PortMask_ is assigned to an I/O port. By calling this command all output ports are set. Some ports need to be configured as output ports before being set via this command.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PortMask** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_SetPort(brp_protocol protocol, brp_IoPortBitmask _input_PortMask);
#else
brp_errcode brp_Sys_SetPort(brp_Sys_SetPort_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned Key;
	unsigned Value;
	brp_buf* Content;
	size_t* Content_len;
	brp_mempool *mempool;
} brp_Sys_CfgGetValue_t;
/**
 * This command retrieves a desired value of the reader's configuration, specified by the _Key_ and _Value_ parameters.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Key** (in) 
 *   - **Value** (in) 
 *   - **Content** (out) Content of the value as string (maximal allowed length: 0x80).
 *   - **Content_len** (out) Length of **Content** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgGetValue(brp_protocol protocol, unsigned _input_Key, unsigned _input_Value, brp_buf* Content, size_t* Content_len, brp_mempool *mempool);
#else
brp_errcode brp_Sys_CfgGetValue(brp_Sys_CfgGetValue_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Key;
	unsigned Value;
	brp_buf Content;
	size_t Content_len;
} brp_Sys_CfgSetValue_t;
/**
 * This command stores a value in the reader's configuration. The _Content_ parameter will be stored to the desired configuration value specified by the _Key_ and _Value_ parameters. If the value is already stored in the configuration, it will be replaced.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Key** (in) 
 *   - **Value** (in) 
 *   - **Content** (in) Content to write as configuration value (maximal allowed length: 0x80).
 *   - **Content_len** (in) Length of **Content** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgSetValue(brp_protocol protocol, unsigned _input_Key, unsigned _input_Value, brp_buf _input_Content, size_t _input_Content_len);
#else
brp_errcode brp_Sys_CfgSetValue(brp_Sys_CfgSetValue_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Key;
	unsigned Value;
} brp_Sys_CfgDelValues_t;
/**
 * This command deletes a key or a value from the reader's configuration. 
 * 
 *   * It is possible to use the wildcard character (0xFF). 
 *   * If 0xFF is used as _Value_ , all values of the given _Key_ will be deleted. For instance, setting 0x0101 as _Key_ and 0xFF as _Value_ will delete all configuration values within the key 0x0101. 
 *   * If 0xFF is used as SubKey (low order byte of the _Key_ variable), all SubKeys from a specified MasterKey will be deleted. For instance, setting 0x01FF as _Key_ delete all SubKeys and thus also all values contained in MasterKey 0x01. The content of the _Value_ variable is irrelevant in this case. 
 *   * If 0xFF is used as MasterKey (high order byte of the _Key_ variable), the complete configuration will be deleted. The contents of the low order byte of the _Key_ variable and of the _Value_ variable are irrelevant in this case. 
 *   * This command is subject to potential restrictions . Specifically, SubKeys >= 0x80 are not deleted when the 0xFF wildcard is used. Deletion of these SubKeys must be performed explicitly.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Key** (in) 
 *   - **Value** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgDelValues(brp_protocol protocol, unsigned _input_Key, unsigned _input_Value);
#else
brp_errcode brp_Sys_CfgDelValues(brp_Sys_CfgDelValues_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned** KeyList;
	size_t* KeyList_len;
	brp_mempool *mempool;
} brp_Sys_CfgGetKeyList_t;
/**
 * Retrieves a list of all keys stored in the reader's configuration.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **KeyList** (out) 
 *   - **KeyList_len** (out) Number of elements in **KeyList**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgGetKeyList(brp_protocol protocol, unsigned** KeyList, size_t* KeyList_len, brp_mempool *mempool);
#else
brp_errcode brp_Sys_CfgGetKeyList(brp_Sys_CfgGetKeyList_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Key;
	unsigned** ValueList;
	size_t* ValueList_len;
	brp_mempool *mempool;
} brp_Sys_CfgGetValueList_t;
/**
 * Returns a list of all configuration values within a specified _Key_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Key** (in) 
 *   - **ValueList** (out) 
 *   - **ValueList_len** (out) Number of elements in **ValueList**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgGetValueList(brp_protocol protocol, unsigned _input_Key, unsigned** ValueList, size_t* ValueList_len, brp_mempool *mempool);
#else
brp_errcode brp_Sys_CfgGetValueList(brp_Sys_CfgGetValueList_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_buf TlvBlock;
	size_t TlvBlock_len;
} brp_Sys_CfgWriteTlvSector_t;
/**
 * **Please use Sys.CfgLoadBlock instead of this command for new applications.**
 * 
 * This command parses the given TLV block and stores all its keys and values into the reader's configuration memory.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **TlvBlock** (in) 
 *   - **TlvBlock_len** (in) Length of **TlvBlock** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgWriteTlvSector(brp_protocol protocol, brp_buf _input_TlvBlock, size_t _input_TlvBlock_len);
#else
brp_errcode brp_Sys_CfgWriteTlvSector(brp_Sys_CfgWriteTlvSector_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned* TotalSize;
	unsigned* FreeSize;
} brp_Sys_CfgCheck_t;
/**
 * This command checks the consistency of the reader's internal configuration. Additionally, it returns the overall configuration data size as well as the amount of free space for further configuration data. Please keep in mind that each value (including empty values) requires a few extra bytes of overhead for data management purposes. 
 * 
 * **Starting with reader generation ID-engine Z, configuration consistency is always checked during powerup. That's why this command is no longer needed and always returns 0 (for _TotalSize_ and _FreeSize_ ) without any further checks.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **TotalSize** (out) Total size of configuration (in bytes)
 *   - **FreeSize** (out) Available free space for configuration data (in bytes)
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgCheck(brp_protocol protocol, unsigned* TotalSize, unsigned* FreeSize);
#else
brp_errcode brp_Sys_CfgCheck(brp_Sys_CfgCheck_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_IoPortBitmask InpOutp;
	brp_IoPortBitmask DefaultState;
} brp_Sys_ConfigPort_t;
/**
 * **This command is obsolete when working with UI.Enable , UI.Disable and UI.Sense , which should be used for new applications.**
 * 
 * Configures generic I/O ports for input/output. 
 * 
 * **Some ports are unidirectional (only usable either as an input or as an output). Only bidirectional ports can be reconfigured via this command.**
 * 
 * **I/O Port configuration can also be performed via scripts in the configuration editor. See the BaltechScript documentation for further details.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **InpOutp** (in) Bit mask describing if I/O pins should be configured for input or output use:     * Logical '1': pin used as output    * Logical '0': pin used as input
 *   - **DefaultState** (in) Bit mask describing the initial state of I/O pins. The specified values have to be interpreted in combination with the I/O pins' direction (according to the _InpOutp_ variable).     * When a port is configured as input:      * _0_ : Port is configured as tri-state.      * _1_ : port is pulled up to VCC. This is the default state of all GPIOs.    * When a port is configured as output:      * _0_ : logic low (GND)      * _1_ : logic high (VCC), corresponds to the default state of the output ports.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_ConfigPort(brp_protocol protocol, brp_IoPortBitmask _input_InpOutp, brp_IoPortBitmask _input_DefaultState);
#else
brp_errcode brp_Sys_ConfigPort(brp_Sys_ConfigPort_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool ResetRegister;
	brp_Sys_SetRegister_RegisterAssignments_Entry* RegisterAssignments;
	size_t RegisterAssignments_len;
} brp_Sys_SetRegister_t;
/**
 * Sets one or multiple of the reader's internal registers. 
 * 
 * **To reset a register, its _Value_ should be set to 0xFFFF.**
 * 
 * **If the parameter _ResetRegister_ is set to _True_ , all registers of the reader will be reset.**
 * 
 * **Register setting operations are usually performed by changing the relevant configuration values.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ResetRegister** (in) 
 *   - **RegisterAssignments** (in) 
 *   - **RegisterAssignments_len** (in) Number of elements in **RegisterAssignments**.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_SetRegister(brp_protocol protocol, bool _input_ResetRegister, brp_Sys_SetRegister_RegisterAssignments_Entry* _input_RegisterAssignments, size_t _input_RegisterAssignments_len);
#else
brp_errcode brp_Sys_SetRegister(brp_Sys_SetRegister_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned ID;
	unsigned* Value;
} brp_Sys_GetRegister_t;
/**
 * Retrieves one of the reader's internal registers. 
 * 
 * **Register setting operations are usually performed by changing the relevant configuration values.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ID** (in) ID of register to retrieve
 *   - **Value** (out) Value of retrieved register
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetRegister(brp_protocol protocol, unsigned _input_ID, unsigned* Value);
#else
brp_errcode brp_Sys_GetRegister(brp_Sys_GetRegister_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Sys_PowerDown_t;
/**
 * Powers off the device. 
 * 
 * This command is only supported by Baltech devices with special hardware support. 
 * 
 * **_WARNING:_ This function has the wrong name. It does not put the device into _power down_ mode (low power sleep) but turns it off completely.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_PowerDown(brp_protocol protocol);
#else
brp_errcode brp_Sys_PowerDown(brp_Sys_PowerDown_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_ProtocolID Protocol;
} brp_Sys_SelectProtocol_t;
/**
 * This command starts a host protocol. 
 * 
 * Depending on the reader's hardware and firmware, multiple protocols may be supported. For most reader-to-host interfaces (e.g. USB, Ethernet), an unlimited number of protocols can be used on the physical channel, but in some cases only a single protocol per physical channel can be used at a time. This is for example the case when using a serial (RS-232/UART) interface, offering two physical channels, in which case each physical channel must be shared by several protocols. 
 * 
 * **After power-up, the reader activates all protocols specified in the Device / Run / EnabledProtocols configuration value. To change the activated protocols at runtime, this command has to be used.**
 * 
 * In case only a single protocol is allowed to run per physical channel, calling this command when a channel is already in use by another protocol will stop the currently running protocol. 
 * 
 * _Example:_ the protocol is currently running on a serial interface (physical channel CH0) when Sys.SelectProtocol is called with _ProtocolID_ = 0x09 (Debug Interface). Since the Debug Interface protocol uses the same physical channel (CH0), it will be disabled.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Protocol** (in) A list of all protocols.   **Not all protocols are available on all Firmware variants.**
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_SelectProtocol(brp_protocol protocol, brp_ProtocolID _input_Protocol);
#else
brp_errcode brp_Sys_SelectProtocol(brp_Sys_SelectProtocol_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_Baudrate NewBaudrate;
	brp_Parity NewParity;
	unsigned CWT;
} brp_Sys_SetCommParam_t;
/**
 * This command is only required when the _serial_ host-to-reader interface is in use. In case the protocol is running, this command can be used to change the settings of the serial line: 
 * 
 *   * Baud rate 
 *   * Parity 
 *   * Character Waiting Time (CWT) 
 * 
 * 
 * 
 * Usually the reader uses the settings specified in the configuration of the reader under the Protocols/BrpSerial Key. If the corresponding configuration values do not exist, the default settings are used (Baud rate 115200; no parity; CWT 20 ms). 
 * 
 * **The BRP response frame to this command is received according to the _old_ serial settings. The new serial settings are only in effect starting with the next BRP command frame.**
 * 
 * **The parameters set by this command are lost when the reader is powered off or reset.**
 * 
 * **CWT must never be smaller than the time needed for transferring a single byte. This is especially important when using baud rates smaller than 9600. It is good practice to adapt the CWT according to the following equation: CWT = 10 / baud rate + 10.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **NewBaudrate** (in) 1/100 of the baud rate to set --- The Baudrate specifies the performance of an RS-232/UART based interface in bits per second.   **For the old-style 8bit format, which omits the least significant digit, this format is not supported any more. Configurations using this format cannot be opened.**
 *   - **NewParity** (in) 'N' for no parity, 'E' for even parity and 'O' for odd parity --- Specifies the Parity-bit mode which is used for RS-232/UART protocols.
 *   - **CWT** (in) Character Waiting Time: maximum time to wait between two characters in a frame.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_SetCommParam(brp_protocol protocol, brp_Baudrate _input_NewBaudrate, brp_Parity _input_NewParity, unsigned _input_CWT);
#else
brp_errcode brp_Sys_SetCommParam(brp_Sys_SetCommParam_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned Version;
	brp_buf Data;
	size_t Data_len;
} brp_Sys_CfgLoadBlock_t;
/**
 * This command transfers the configuration from a BEC file into the reader. You have to call it for every _block_ tag in the BEC file. 
 * 
 * **All _Sys.CfgLoad_ commands only work with the legacy file format BEC. For the current[ default format BEC2](https://docs.baltech.de/deployable-file-formats) , please use Main.Bf3UploadStart and Main.Bf3UploadContinue as explained in this[ overview](https://docs.baltech.de/developers/implement-wired-upload.html) .**
 * 
 * ## Commands to run before and after
 * 
 * To initiate the transfer, run Sys.CfgLoadPrepare before the first _Sys.CfgLoadBlock_.  
 * For legacy reasons, you can ommit _Sys.CfgLoadPrepare_ because it's not supported by readers older than our current product lines based on ID-engine Z. In this case, ensure that the _Sys.CfgLoadBlock_ transferring the first block of the BEC file is the first _Sys.CfgLoadBlock_ after powerup. 
 * 
 * To complete the operation once all _block_ tags are transferred, run Sys.CfgLoadFinish.  
 * If you omit _Sys.CfgLoadPrepare_ for legacy reasons, omit _Sys.CfgLoadFinish_ as well. In this case, do a a manual reset to activate the configuration changes.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Version** (in) Has to contain the _version_ attribute of every _block_ tag.
 *   - **Data** (in) Has to contain the _content_ attribute of every _block_ x tag (converted into binary format).
 *   - **Data_len** (in) Length of **Data** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgLoadBlock(brp_protocol protocol, unsigned _input_Version, brp_buf _input_Data, size_t _input_Data_len);
#else
brp_errcode brp_Sys_CfgLoadBlock(brp_Sys_CfgLoadBlock_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_buf* PlatformId;
	unsigned* BootloaderId;
	unsigned* BootloaderMajor;
	unsigned* BootloaderMinor;
	unsigned* BootloaderBuild;
	brp_mempool *mempool;
} brp_Sys_GetPlatformId_t;
/**
 * Maintenance command only needed for Baltech internal use to get detailed information about the actually used hardware. 
 * 
 * **This command must only be used if the Main.MatchPlatformId2 command is not supported by the current firmware.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PlatformId** (out) PlatformID of Device (Baltech internal use)
 *   - **BootloaderId** (out) Compilation of Bootloader (Baltech internal use)
 *   - **BootloaderMajor** (out) Majornumber of Bootloader version (Baltech internal use)
 *   - **BootloaderMinor** (out) Minornumber of Bootloader version (Baltech internal use)
 *   - **BootloaderBuild** (out) Buildnumber of Bootloader version (Baltech internal use)
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetPlatformId(brp_protocol protocol, brp_buf* PlatformId, unsigned* BootloaderId, unsigned* BootloaderMajor, unsigned* BootloaderMinor, unsigned* BootloaderBuild, brp_mempool *mempool);
#else
brp_errcode brp_Sys_GetPlatformId(brp_Sys_GetPlatformId_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
} brp_Sys_CfgReset_t;
/**
 * Deletes the complete configuration. This command has the same effect as the Sys.CfgDelValues command using 0xFF as MasterKey. 
 * 
 * **Like Sys.CfgDelValues , this command is subject to potential restrictions . Specifically, SubKeys > = 0x80 are not deleted by this command. Deletion of these SubKeys must be performed explicitly using Sys.CfgDelValues .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgReset(brp_protocol protocol);
#else
brp_errcode brp_Sys_CfgReset(brp_Sys_CfgReset_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_ProtocolID Protocol;
} brp_Sys_StopProtocol_t;
/**
 * This command stops a host protocol. No reaction is expected after the protocol has been stopped. More details on protocols can be found in the Sys.SelectProtocol command reference.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Protocol** (in) A list of all protocols.   **Not all protocols are available on all Firmware variants.**
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_StopProtocol(brp_protocol protocol, brp_ProtocolID _input_Protocol);
#else
brp_errcode brp_Sys_StopProtocol(brp_Sys_StopProtocol_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_ProtocolID Protocol;
	brp_MessageType MsgType;
	brp_buf Message;
	size_t Message_len;
} brp_Sys_SendMessage_t;
/**
 * This command sends a message to the host via a certain protocol. 
 * 
 * If _Protocol_ is 0, the message is sent to _all_ active protocols. Furthermore, it is transformed by the corresponding HostMsgFormatTemplates, e.g. Protocols/KeyboardEmulation/HostMsgFormatTemplate in case of keyboard emulation. 
 * 
 * If _Protocol_ is a protocol ID, the message is sent to this protocol only and _no_ HostMsgFormatTemplate conversion is initiated. The desired protocol must be active, e.g. by calling Sys.SelectProtocol.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Protocol** (in) A list of all protocols.   **Not all protocols are available on all Firmware variants.**
 *   - **MsgType** (in) Event that triggered the message. It allows the host application to interpret the message content correctly.
 *   - **Message** (in) The message to be sent
 *   - **Message_len** (in) Length of **Message** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_SendMessage(brp_protocol protocol, brp_ProtocolID _input_Protocol, brp_MessageType _input_MsgType, brp_buf _input_Message, size_t _input_Message_len);
#else
brp_errcode brp_Sys_SendMessage(brp_Sys_SendMessage_t params);
#endif
typedef struct {
	brp_protocol protocol;
	char** ConfigId;
	char** ConfigName;
	brp_mempool *mempool;
} brp_Sys_CfgGetId_t;
/**
 * This command returns the identifier of the reader configuration. The prerequisite is that the configuration contains a valid host interface component and/or RFID interface component. 
 * 
 * **If the RFID interface component(s) are stored in one configuration and other components (typically the host interface component) in another configuration, this command will only return the ID for the configuration with the RFID interface component(s). To get the ID for the configuration with the host interface component, run Sys.CfgGetDeviceSettingsId .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ConfigId** (out) Configuration ID   This is a 15-digit number as defined in the [ BALTECH configuration naming scheme](https://docs.baltech.de/project-setup/order-config.html#naming-scheme).   **Only configurations created by BALTECH have a configuration ID.**
 *   - **ConfigName** (out) Configuration name   This is the name specified in BALTECH ConfigEditor.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgGetId(brp_protocol protocol, char** ConfigId, char** ConfigName, brp_mempool *mempool);
#else
brp_errcode brp_Sys_CfgGetId(brp_Sys_CfgGetId_t params);
#endif
typedef struct {
	brp_protocol protocol;
	char** ConfigId;
	char** ConfigName;
	brp_mempool *mempool;
} brp_Sys_CfgGetDeviceSettingsId_t;
/**
 * This command retrieves the ID of the reader configuration containing the device settings. 
 * 
 * **Use this command if the RFID interface component(s) are stored in one configuration and other components (typically the host interface component) in another configuration. If you have no RFID interface component or a configuration containing all components, run Sys.CfgGetId to get the configuration ID.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ConfigId** (out) Configuration ID   This is a 15-digit number as defined in the [ BALTECH configuration naming scheme](https://docs.baltech.de/project-setup/order-config.html#naming-scheme).   **Only configurations created by BALTECH have a configuration ID.**
 *   - **ConfigName** (out) Configuration name   This is the name specified in BALTECH ConfigEditor.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgGetDeviceSettingsId(brp_protocol protocol, char** ConfigId, char** ConfigName, brp_mempool *mempool);
#else
brp_errcode brp_Sys_CfgGetDeviceSettingsId(brp_Sys_CfgGetDeviceSettingsId_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
} brp_Sys_FactoryResetLegacy_t;
/**
 * **This is a legacy command! For new developments please use Sys.FactoryReset .**
 * 
 * This command resets the device's configuration to the state it had, when leaving the factory. 
 * 
 * A factory reset is only available on newer devices (about 2017 and later). When running it on a older Hardware Sys.ErrNotSupportedByHardware is returned. 
 * 
 * **After a factory reset a Sys.Reset has to be done to ensure that the factory settings are fully activated.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_FactoryResetLegacy(brp_protocol protocol);
#else
brp_errcode brp_Sys_FactoryResetLegacy(brp_Sys_FactoryResetLegacy_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	bool DeleteCounters;
	brp_Sys_GetStatistics_CounterTuple_Entry** CounterTuple;
	size_t* CounterTuple_len;
	brp_mempool *mempool;
} brp_Sys_GetStatistics_t;
/**
 * This command retrieves all available statistics counters from the reader's configuration. The statistics counters are stored in the Device / Statistics configuration key. 
 * 
 * **This command is designed for Baltech internal use only.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **DeleteCounters** (in) 
 *   - **CounterTuple** (out) 
 *   - **CounterTuple_len** (out) Number of elements in **CounterTuple**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetStatistics(brp_protocol protocol, bool _input_DeleteCounters, brp_Sys_GetStatistics_CounterTuple_Entry** CounterTuple, size_t* CounterTuple_len, brp_mempool *mempool);
#else
brp_errcode brp_Sys_GetStatistics(brp_Sys_GetStatistics_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_FeatureID** FeatureList;
	size_t* FeatureList_len;
	brp_FeatureID* MaxFeatureID;
	brp_mempool *mempool;
} brp_Sys_GetFeatures_t;
/**
 * This command retrieves the list of features supported by the reader, so you can find out if the reader meets your requirements. The list of features includes e.g. supported card types, LEDs, encryption methods, and maintenance options. It depends both on the reader hardware and firmware.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **FeatureList** (out) 
 *   - **FeatureList_len** (out) Number of elements in **FeatureList**.
 *   - **MaxFeatureID** (out) The number of the highest feature ID known to the firmware   Features with a higher ID are undefined! (They could have been already available in an older firmware version, but not included explicitly in the feature list)   **Don't make any assumptions about features with higher IDs in your application.**
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetFeatures(brp_protocol protocol, brp_FeatureID** FeatureList, size_t* FeatureList_len, brp_FeatureID* MaxFeatureID, brp_mempool *mempool);
#else
brp_errcode brp_Sys_GetFeatures(brp_Sys_GetFeatures_t params);
#endif
typedef struct {
	brp_protocol protocol;
	char** PartNo;
	char** HwRevNo;
	brp_mempool *mempool;
} brp_Sys_GetPartNumber_t;
/**
 * This command returns the part number and the hardware revision number of the device. This information, which is usually also printed on the label, allows you to identify the reader model type for e.g. reorder purposes. 
 * 
 * **Don't use this command to distinguish the device features in your application! Use Sys.GetFeatures instead. The reason is: Baltech may offer (replacement) products with the same or a similar feature set, which have different part numbers. If the application would stick to a certain part number these devices would not be deployable.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PartNo** (out) Part number
 *   - **HwRevNo** (out) Hardware revision number
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetPartNumber(brp_protocol protocol, char** PartNo, char** HwRevNo, brp_mempool *mempool);
#else
brp_errcode brp_Sys_GetPartNumber(brp_Sys_GetPartNumber_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_AuthReqUpload AuthReq;
} brp_Sys_CfgLoadPrepare_t;
/**
 * This command initiates the transfer of a BEC file via Sys.CfgLoadBlock. It will cancel any running BEC transfer and start loading a new one. 
 * 
 * **All _Sys.CfgLoad_ commands only work with the legacy file format BEC. For the current[ default format BEC2](https://docs.baltech.de/deployable-file-formats) , please use Main.Bf3UploadStart and Main.Bf3UploadContinue as explained in this[ overview](https://docs.baltech.de/developers/implement-wired-upload.html) .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **AuthReq** (in) If this value is _Default_ , the configuration value AuthReqUploadViaBrp will be consulted. --- Specifies the authentication level the BEC/BEC2/BF3 file or ConfigCard has to fulfill to be accepted.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgLoadPrepare(brp_protocol protocol, brp_AuthReqUpload _input_AuthReq);
#else
brp_errcode brp_Sys_CfgLoadPrepare(brp_Sys_CfgLoadPrepare_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Sys_CfgLoadFinish_FinalizeAction FinalizeAction;
} brp_Sys_CfgLoadFinish_t;
/**
 * This command has to be called after transferring a BEC file with Sys.CfgLoadBlock. Depending on how you set the parameter _FinalizeAction_ , this command will do one of the following: 
 * 
 *   * Complete the transfer; this requires all _Sys.CfgLoadBlock_ calls to have succeeded. 
 *   * Cancel the transfer and undo all configuration changes since Sys.CfgLoadPrepare. 
 * 
 * 
 * 
 * **All _Sys.CfgLoad_ commands only work with the legacy file format BEC. For the current[ default format BEC2](https://docs.baltech.de/deployable-file-formats) , please use Main.Bf3UploadStart and Main.Bf3UploadContinue as explained in this[ overview](https://docs.baltech.de/developers/implement-wired-upload.html) .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **FinalizeAction** (in) Defines the reader's behaviour on error/success
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgLoadFinish(brp_protocol protocol, brp_Sys_CfgLoadFinish_FinalizeAction _input_FinalizeAction);
#else
brp_errcode brp_Sys_CfgLoadFinish(brp_Sys_CfgLoadFinish_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool PerformReboot;
} brp_Sys_FactoryReset_t;
/**
 * This command restores the reader's [ factory settings](https://docs.baltech.de/project-setup/factory-settings.html).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PerformReboot** (in) If _true_ , the reader automatically reboots after reset. If _false_ , you have to explicitly perform a reboot later.   **Without a reboot, the configuration remains inconsistent. Only use _false_ if you have good reasons to postpone it, e.g. if you update the firmware afterwards, which includes a reboot anyway.**
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_FactoryReset(brp_protocol protocol, bool _input_PerformReboot);
#else
brp_errcode brp_Sys_FactoryReset(brp_Sys_FactoryReset_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_LicenseBitMask* LicenseBitMask;
} brp_Sys_GetLicenses_t;
/**
 * This command retrieves a bit mask of the licenses that are activated in the reader.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **LicenseBitMask** (out) License bit mask
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetLicenses(brp_protocol protocol, brp_LicenseBitMask* LicenseBitMask);
#else
brp_errcode brp_Sys_GetLicenses(brp_Sys_GetLicenses_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned* CRC;
} brp_Sys_GetFwCrc_t;
/**
 * Maintenance command only needed for Baltech internal use to get the CRC of the firmware.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CRC** (out) 32 bit Firmware CRC value (Baltech internal use)
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetFwCrc(brp_protocol protocol, unsigned* CRC);
#else
brp_errcode brp_Sys_GetFwCrc(brp_Sys_GetFwCrc_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */