/**
 * @file
 * Hardware-test commands for production-line bring-up of BALTECH readers. Peripheral-agnostic: bundles Ethernet, GPIO, USB host, and flash test commands behind one opaque BRP group. Commands address peripherals by name, so the same firmware binary serves every hardware variant in a family.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_DHWCTRL_H__
#define __BRP_BALTECH_SDK_CMDS_DHWCTRL_H__
#include "../typedefs.h"
#ifdef BALTECH_SDK_INTERNAL
/**
 * Peripheral instance _Index_ is out of range for this firmware. The valid range per category is discoverable via ListPeripherals.
 */
#define BRP_DHWCtrl_ErrInvalidIndex BRP_ERR_STATUS(0xE100, 0x01)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Peripheral instance is not activated.
 */
#define BRP_DHWCtrl_ErrNotActive BRP_ERR_STATUS(0xE100, 0x02)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Peripheral instance is already active. Call _Deactivate_ first to change the pin map or MAC.
 */
#define BRP_DHWCtrl_ErrAlreadyActive BRP_ERR_STATUS(0xE100, 0x03)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Parameter out of range. Covers every rejected _PinMap_ : a required function missing, a pin name the target peripheral does not use, a duplicated name, or a function assigned to a GPIO it cannot be routed to. Also a bad enum value, or a wrong direction bit in a control SETUP.
 */
#define BRP_DHWCtrl_ErrInvalidParam BRP_ERR_STATUS(0xE100, 0x04)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Operation did not complete within the requested timeout.
 */
#define BRP_DHWCtrl_ErrTimeout BRP_ERR_STATUS(0xE100, 0x05)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Ethernet frame longer than 1518 bytes (excluding CRC).
 */
#define BRP_DHWCtrl_ErrEthFrameTooBig BRP_ERR_STATUS(0xE100, 0x10)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * No device on this USB host port.
 */
#define BRP_DHWCtrl_ErrUsbNotConnected BRP_ERR_STATUS(0xE100, 0x20)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Endpoint returned STALL.
 */
#define BRP_DHWCtrl_ErrUsbStall BRP_ERR_STATUS(0xE100, 0x21)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Transfer-level error (CRC, invalid PID, framing).
 */
#define BRP_DHWCtrl_ErrUsbTransfer BRP_ERR_STATUS(0xE100, 0x22)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Device returned more data than the requested in_len / max_len.
 */
#define BRP_DHWCtrl_ErrUsbBufferOverflow BRP_ERR_STATUS(0xE100, 0x23)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Sector + count outside slot bounds, or len(data) % sector_size != 0 on FlashWrite.
 */
#define BRP_DHWCtrl_ErrFlashRange BRP_ERR_STATUS(0xE100, 0x30)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Programming failed (driver-reported verify mismatch or NACK).
 */
#define BRP_DHWCtrl_ErrFlashWrite BRP_ERR_STATUS(0xE100, 0x31)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Erase failed.
 */
#define BRP_DHWCtrl_ErrFlashErase BRP_ERR_STATUS(0xE100, 0x32)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Underlying driver returned an unrecoverable error.
 */
#define BRP_DHWCtrl_ErrHardware BRP_ERR_STATUS(0xE100, 0xFF)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlPinMapEntry* PinMap;
	size_t PinMap_len;
	unsigned PeripheralIndex;
	brp_buf MacAddress;
} brp_DHWCtrl_EthActivate_t;
/**
 * Initialize MAC + PHY for _PeripheralIndex_ : apply the pin routing described by _PinMap_ , program the source _MacAddress_ , enable RX/TX. Returns once init completes; PHY autonegotiation runs asynchronously - call EthWaitLinkState to block until the link is up.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PinMap** (in) Logical-to-physical pin assignments for this port. Must contain exactly the functions this instance requires (RMII data/control plus MDIO management); unknown, surplus, or duplicate names are rejected with ErrInvalidParam.
 *   - **PinMap_len** (in) Number of elements in **PinMap**.
 *   - **PeripheralIndex** (in) Zero-based instance index within this peripheral category; defaults to 0 (the first instance). The valid range is firmware/hardware-variant specific; discoverable via ListPeripherals.
 *   - **MacAddress** (in) Source MAC address (6 bytes) to program into the MAC engine.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_EthActivate(brp_protocol protocol, brp_DHWCtrlPinMapEntry* _input_PinMap, size_t _input_PinMap_len, unsigned _input_PeripheralIndex, brp_buf _input_MacAddress);
#else
brp_errcode brp_DHWCtrl_EthActivate(brp_DHWCtrl_EthActivate_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
} brp_DHWCtrl_EthDeactivate_t;
/**
 * Stop the MAC RX/TX engines on _Index_. Whether pins, clocks and IRQ are released back to the SoC pool is implementation-defined.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_EthDeactivate(brp_protocol protocol, unsigned _input_Index);
#else
brp_errcode brp_DHWCtrl_EthDeactivate(brp_DHWCtrl_EthDeactivate_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	brp_buf DstMac;
	brp_buf SrcMac;
	brp_DHWCtrlEtherType EtherType;
	brp_buf Payload;
	size_t Payload_len;
} brp_DHWCtrl_EthSendFrame_t;
/**
 * Transmit one Ethernet frame on _Index_. The MAC hardware appends the CRC; no firmware-side padding. Total wire length must be in [14, 1518] bytes (excl. CRC).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **DstMac** (in) Destination MAC address (6 bytes).
 *   - **SrcMac** (in) Source MAC address (6 bytes). Should match the value passed to EthActivate for spec-compliant frames, but may be set freely for bench tests (MAC-spoofing scenarios).
 *   - **EtherType** (in) Outer EtherType of the frame to send. --- EtherType field of an Ethernet II frame header, identifying the upper-layer protocol carried in the payload. IEEE 802.3 distinguishes by value: <= 1500 (0x05DC) is interpreted as a legacy LLC frame length; >= 1536 (0x0600) is an EtherType per the IANA registry. The enum lists the common values seen on the bench; the field is extendable so any 16-bit value can be sent / received for bench tests (malformed-frame scenarios, experimental protocols).
 *   - **Payload** (in) Bytes following the EtherType. For VLAN-tagged frames the first 2 bytes are the TCI followed by the inner EtherType, then the actual payload.
 *   - **Payload_len** (in) Length of **Payload** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_EthSendFrame(brp_protocol protocol, unsigned _input_Index, brp_buf _input_DstMac, brp_buf _input_SrcMac, brp_DHWCtrlEtherType _input_EtherType, brp_buf _input_Payload, size_t _input_Payload_len);
#else
brp_errcode brp_DHWCtrl_EthSendFrame(brp_DHWCtrl_EthSendFrame_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	unsigned TimeoutMs;
	unsigned* TimestampUs;
	unsigned* Seq;
	bool* RxOverflow;
	bool* CrcError;
	bool* Truncated;
	brp_buf* DstMac;
	brp_buf* SrcMac;
	brp_DHWCtrlEtherType* EtherType;
	brp_buf* Payload;
	size_t* Payload_len;
	brp_mempool *mempool;
} brp_DHWCtrl_EthRecvFrame_t;
/**
 * Block until the next Ethernet frame is received on _Index_ , or until _TimeoutMs_ milliseconds elapse. Promiscuous: any frame on the wire is returned; host filters. Returns the L2 frame without CRC plus per-frame metadata.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **TimeoutMs** (in) Maximum time to wait for a frame, in milliseconds.
 *   - **TimestampUs** (out) Boot-relative monotonic microseconds at RX completion. Wraps every ~71 minutes; caller must handle wrap.
 *   - **Seq** (out) Monotonic frame counter since EthActivate(_Index_). Increments by 1 per delivered frame; gaps imply RX-queue drops since the previous EthRecvFrame.
 *   - **RxOverflow** (out) Firmware dropped frames between the previous EthRecvFrame and this one.
 *   - **CrcError** (out) Frame had a CRC error. Only set when firmware is in error-frame-accept mode; normally such frames are dropped silently in hardware.
 *   - **Truncated** (out) Frame exceeded firmware's RX buffer; _Payload_ contains the leading bytes only.
 *   - **DstMac** (out) Destination MAC address (6 bytes).
 *   - **SrcMac** (out) Source MAC address (6 bytes).
 *   - **EtherType** (out) Outer EtherType of the received frame. --- EtherType field of an Ethernet II frame header, identifying the upper-layer protocol carried in the payload. IEEE 802.3 distinguishes by value: <= 1500 (0x05DC) is interpreted as a legacy LLC frame length; >= 1536 (0x0600) is an EtherType per the IANA registry. The enum lists the common values seen on the bench; the field is extendable so any 16-bit value can be sent / received for bench tests (malformed-frame scenarios, experimental protocols).
 *   - **Payload** (out) Bytes following the EtherType, up to the end of the captured frame.
 *   - **Payload_len** (out) Length of **Payload** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_EthRecvFrame(brp_protocol protocol, unsigned _input_Index, unsigned _input_TimeoutMs, unsigned* TimestampUs, unsigned* Seq, bool* RxOverflow, bool* CrcError, bool* Truncated, brp_buf* DstMac, brp_buf* SrcMac, brp_DHWCtrlEtherType* EtherType, brp_buf* Payload, size_t* Payload_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrl_EthRecvFrame(brp_DHWCtrl_EthRecvFrame_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	brp_DHWCtrlEthLinkState State;
	unsigned TimeoutMs;
} brp_DHWCtrl_EthWaitLinkState_t;
/**
 * Block until the PHY-reported link state on _Index_ matches _State_ , or until _TimeoutMs_ milliseconds elapse. Returns OK once the link reaches the requested state, ErrTimeout otherwise. Use _TimeoutMs_ = 0 to probe the current state in a single round-trip.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **State** (in) Desired link state to wait for. --- PHY-reported link state of an Ethernet port. Used as the target state for EthWaitLinkState.
 *   - **TimeoutMs** (in) Maximum time the firmware will wait for the operation to complete, in milliseconds.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_EthWaitLinkState(brp_protocol protocol, unsigned _input_Index, brp_DHWCtrlEthLinkState _input_State, unsigned _input_TimeoutMs);
#else
brp_errcode brp_DHWCtrl_EthWaitLinkState(brp_DHWCtrl_EthWaitLinkState_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	brp_DHWCtrl_EthGetCommMode_Speed* Speed;
	brp_DHWCtrl_EthGetCommMode_Duplex* Duplex;
} brp_DHWCtrl_EthGetCommMode_t;
/**
 * Read the PHY-negotiated link parameters on _Index_. Typically called after EthWaitLinkState(_State_ = _Up_) succeeds. If autonegotiation has not yet completed, _Speed_ and/or _Duplex_ may read as _Unknown_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **Speed** (out) PHY-negotiated link speed.
 *   - **Duplex** (out) PHY-negotiated duplex mode.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_EthGetCommMode(brp_protocol protocol, unsigned _input_Index, brp_DHWCtrl_EthGetCommMode_Speed* Speed, brp_DHWCtrl_EthGetCommMode_Duplex* Duplex);
#else
brp_errcode brp_DHWCtrl_EthGetCommMode(brp_DHWCtrl_EthGetCommMode_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlGpioPin Pin;
	brp_DHWCtrl_GpioConfigure_Mode Mode;
} brp_DHWCtrl_GpioConfigure_t;
/**
 * Set direction / drive of a single GPIO pin. For outputs, the level is driven immediately to avoid glitches. _OpenDrain_ starts Hi-Z; drive low via GpioSetState(_Low_) and release via GpioSetState(_High_).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Pin** (in) Reference to a single physical GPIO pin: SoC bank (_DHWCtrlGpioPort_) plus pin number within the bank. The firmware rejects pin numbers outside the bank's actual width with ErrInvalidParam.
 *   - **Mode** (in) Direction and drive configuration for the pin.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_GpioConfigure(brp_protocol protocol, brp_DHWCtrlGpioPin _input_Pin, brp_DHWCtrl_GpioConfigure_Mode _input_Mode);
#else
brp_errcode brp_DHWCtrl_GpioConfigure(brp_DHWCtrl_GpioConfigure_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlGpioPin Pin;
	brp_DHWCtrlGpioLevel Level;
} brp_DHWCtrl_GpioSetState_t;
/**
 * Drive an already-configured output pin to the requested _Level_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Pin** (in) Reference to a single physical GPIO pin: SoC bank (_DHWCtrlGpioPort_) plus pin number within the bank. The firmware rejects pin numbers outside the bank's actual width with ErrInvalidParam.
 *   - **Level** (in) Target output level to drive. --- Logic level of a single GPIO pin.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_GpioSetState(brp_protocol protocol, brp_DHWCtrlGpioPin _input_Pin, brp_DHWCtrlGpioLevel _input_Level);
#else
brp_errcode brp_DHWCtrl_GpioSetState(brp_DHWCtrl_GpioSetState_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlGpioPin Pin;
	brp_DHWCtrlGpioLevel Level;
	unsigned TimeoutMs;
} brp_DHWCtrl_GpioWaitState_t;
/**
 * Block until the pad level of _Pin_ matches _Level_ , or until _TimeoutMs_ milliseconds elapse. The pad is read regardless of prior GpioConfigure state - pre-config waits are routine. Use _TimeoutMs_ = 0 to probe the current level (call once per candidate value).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Pin** (in) Reference to a single physical GPIO pin: SoC bank (_DHWCtrlGpioPort_) plus pin number within the bank. The firmware rejects pin numbers outside the bank's actual width with ErrInvalidParam.
 *   - **Level** (in) Pad level to wait for. --- Logic level of a single GPIO pin.
 *   - **TimeoutMs** (in) Maximum time the firmware will wait for the operation to complete, in milliseconds.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_GpioWaitState(brp_protocol protocol, brp_DHWCtrlGpioPin _input_Pin, brp_DHWCtrlGpioLevel _input_Level, unsigned _input_TimeoutMs);
#else
brp_errcode brp_DHWCtrl_GpioWaitState(brp_DHWCtrl_GpioWaitState_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlPinMapEntry* PinMap;
	size_t PinMap_len;
	unsigned PeripheralIndex;
} brp_DHWCtrl_UsbHostActivate_t;
/**
 * Apply the pin routing described by _PinMap_ and bring up the USB host controller on _PeripheralIndex_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PinMap** (in) Logical-to-physical pin assignments for this controller (_UsbDp_ / _UsbDm_). Must contain exactly the functions this instance requires; unknown, surplus, or duplicate names are rejected with ErrInvalidParam.
 *   - **PinMap_len** (in) Number of elements in **PinMap**.
 *   - **PeripheralIndex** (in) Zero-based instance index within this peripheral category; defaults to 0 (the first instance). The valid range is firmware/hardware-variant specific; discoverable via ListPeripherals.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostActivate(brp_protocol protocol, brp_DHWCtrlPinMapEntry* _input_PinMap, size_t _input_PinMap_len, unsigned _input_PeripheralIndex);
#else
brp_errcode brp_DHWCtrl_UsbHostActivate(brp_DHWCtrl_UsbHostActivate_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
} brp_DHWCtrl_UsbHostDeactivate_t;
/**
 * Shut down the USB host controller on _Index_. All firmware-side transfer state is dropped.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostDeactivate(brp_protocol protocol, unsigned _input_Index);
#else
brp_errcode brp_DHWCtrl_UsbHostDeactivate(brp_DHWCtrl_UsbHostDeactivate_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
} brp_DHWCtrl_UsbHostBusReset_t;
/**
 * Drive a USB bus reset on _Index_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostBusReset(brp_protocol protocol, unsigned _input_Index);
#else
brp_errcode brp_DHWCtrl_UsbHostBusReset(brp_DHWCtrl_UsbHostBusReset_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
} brp_DHWCtrl_UsbHostBusSuspend_t;
/**
 * Drive bus suspend on _Index_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostBusSuspend(brp_protocol protocol, unsigned _input_Index);
#else
brp_errcode brp_DHWCtrl_UsbHostBusSuspend(brp_DHWCtrl_UsbHostBusSuspend_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
} brp_DHWCtrl_UsbHostBusResume_t;
/**
 * Drive bus resume on _Index_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostBusResume(brp_protocol protocol, unsigned _input_Index);
#else
brp_errcode brp_DHWCtrl_UsbHostBusResume(brp_DHWCtrl_UsbHostBusResume_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	brp_DHWCtrlUsbPortState State;
	unsigned TimeoutMs;
	brp_DHWCtrl_UsbHostWaitPortStatus_Speed* Speed;
} brp_DHWCtrl_UsbHostWaitPortStatus_t;
/**
 * Block until the attach state on _Index_ matches _State_ , or until _TimeoutMs_ milliseconds elapse. Always returns OK with the current _Speed_ (_NoDevice_ if no device is attached, _Low_ / _Full_ / _High_ otherwise) - the host compares the response against its requested _State_ to decide whether the wait condition was met. Use _TimeoutMs_ = 0 to probe.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **State** (in) Desired attach state to wait for. --- Attach state of a USB host port. Used as the target state for UsbHostWaitPortStatus.
 *   - **TimeoutMs** (in) Maximum time the firmware will wait for the operation to complete, in milliseconds.
 *   - **Speed** (out) Current bus speed of the attached USB device.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostWaitPortStatus(brp_protocol protocol, unsigned _input_Index, brp_DHWCtrlUsbPortState _input_State, unsigned _input_TimeoutMs, brp_DHWCtrl_UsbHostWaitPortStatus_Speed* Speed);
#else
brp_errcode brp_DHWCtrl_UsbHostWaitPortStatus(brp_DHWCtrl_UsbHostWaitPortStatus_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	unsigned Addr;
	unsigned Mps;
	brp_buf Setup;
	unsigned InLen;
	unsigned TimeoutMs;
	brp_buf* InData;
	size_t* InData_len;
	brp_mempool *mempool;
} brp_DHWCtrl_UsbHostTransferCtrlIn_t;
/**
 * Control transfer to (_Addr_ , EP0) with a device-to-host data stage. _Setup_ carries the 8-byte USB SETUP packet (bmRequestType, bRequest, wValue, wIndex, wLength - the wXxx fields are little-endian per USB spec and transmitted as opaque bytes). Firmware must reject SETUPs whose bmRequestType[7] = 0 with ErrInvalidParam. Firmware reads up to _InLen_ bytes as the IN data stage; _InData_ carries the bytes actually returned. _Mps_ is the device's bMaxPacketSize0 (typically 8 / 16 / 32 / 64).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **Addr** (in) USB device address on the host port.
 *   - **Mps** (in) Device's bMaxPacketSize0 for EP0 (typically 8, 16, 32 or 64).
 *   - **Setup** (in) 8-byte USB SETUP packet: bmRequestType, bRequest, wValue, wIndex, wLength. The wXxx fields are little-endian per USB spec (not BRP convention) and are transmitted as opaque bytes.
 *   - **InLen** (in) Maximum number of bytes to read in the IN data stage.
 *   - **TimeoutMs** (in) Maximum time the firmware will wait for the operation to complete, in milliseconds.
 *   - **InData** (out) Bytes returned by the device in the IN data stage.
 *   - **InData_len** (out) Length of **InData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostTransferCtrlIn(brp_protocol protocol, unsigned _input_Index, unsigned _input_Addr, unsigned _input_Mps, brp_buf _input_Setup, unsigned _input_InLen, unsigned _input_TimeoutMs, brp_buf* InData, size_t* InData_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrl_UsbHostTransferCtrlIn(brp_DHWCtrl_UsbHostTransferCtrlIn_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	unsigned Addr;
	unsigned Mps;
	brp_buf Setup;
	brp_buf OutData;
	size_t OutData_len;
	unsigned TimeoutMs;
} brp_DHWCtrl_UsbHostTransferCtrlOut_t;
/**
 * Control transfer to (_Addr_ , EP0) with a host-to-device data stage (or no data stage). Firmware must reject SETUPs whose bmRequestType[7] = 1 with ErrInvalidParam. _OutData_ may be empty - this is the canonical encoding for no-data-stage SETUPs (e.g. SET_ADDRESS, SET_CONFIGURATION) where bmRequestType[7] = 0 and wLength = 0.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **Addr** (in) USB device address on the host port.
 *   - **Mps** (in) Device's bMaxPacketSize0 for EP0 (typically 8, 16, 32 or 64).
 *   - **Setup** (in) 8-byte USB SETUP packet: bmRequestType, bRequest, wValue, wIndex, wLength. The wXxx fields are little-endian per USB spec (not BRP convention) and are transmitted as opaque bytes.
 *   - **OutData** (in) Bytes to send in the OUT data stage. Empty for no-data-stage SETUPs (e.g. SET_ADDRESS).
 *   - **OutData_len** (in) Length of **OutData** (in bytes).
 *   - **TimeoutMs** (in) Maximum time the firmware will wait for the operation to complete, in milliseconds.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostTransferCtrlOut(brp_protocol protocol, unsigned _input_Index, unsigned _input_Addr, unsigned _input_Mps, brp_buf _input_Setup, brp_buf _input_OutData, size_t _input_OutData_len, unsigned _input_TimeoutMs);
#else
brp_errcode brp_DHWCtrl_UsbHostTransferCtrlOut(brp_DHWCtrl_UsbHostTransferCtrlOut_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	unsigned Addr;
	unsigned Ep;
	brp_DHWCtrlUsbTransferAttr Attr;
	unsigned Mps;
	unsigned MaxLen;
	unsigned TimeoutMs;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_DHWCtrl_UsbHostTransferIn_t;
/**
 * IN transfer on (_Addr_ , _Ep_). _Attr_ selects pipe type; _Mps_ is the endpoint's wMaxPacketSize. Firmware reads up to _MaxLen_ bytes; returns the bytes actually read in _Data_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **Addr** (in) USB device address on the host port.
 *   - **Ep** (in) USB endpoint number. Direction is implied by the command.
 *   - **Attr** (in) Endpoint type for a USB host data transfer.
 *   - **Mps** (in) Endpoint's wMaxPacketSize (16-bit field per USB descriptor).
 *   - **MaxLen** (in) Maximum number of bytes to read from the endpoint.
 *   - **TimeoutMs** (in) Maximum time the firmware will wait for the operation to complete, in milliseconds.
 *   - **Data** (out) Bytes returned by the device on the IN endpoint.
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostTransferIn(brp_protocol protocol, unsigned _input_Index, unsigned _input_Addr, unsigned _input_Ep, brp_DHWCtrlUsbTransferAttr _input_Attr, unsigned _input_Mps, unsigned _input_MaxLen, unsigned _input_TimeoutMs, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrl_UsbHostTransferIn(brp_DHWCtrl_UsbHostTransferIn_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	unsigned Addr;
	unsigned Ep;
	brp_DHWCtrlUsbTransferAttr Attr;
	unsigned Mps;
	brp_buf Data;
	size_t Data_len;
	unsigned TimeoutMs;
} brp_DHWCtrl_UsbHostTransferOut_t;
/**
 * OUT transfer on (_Addr_ , _Ep_). Firmware sends _Data_ and returns once the device has accepted all of it or _TimeoutMs_ elapses.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **Addr** (in) USB device address on the host port.
 *   - **Ep** (in) USB endpoint number. Direction is implied by the command.
 *   - **Attr** (in) Endpoint type for a USB host data transfer.
 *   - **Mps** (in) Endpoint's wMaxPacketSize (16-bit field per USB descriptor).
 *   - **Data** (in) Bytes to send to the device on the OUT endpoint.
 *   - **Data_len** (in) Length of **Data** (in bytes).
 *   - **TimeoutMs** (in) Maximum time the firmware will wait for the operation to complete, in milliseconds.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostTransferOut(brp_protocol protocol, unsigned _input_Index, unsigned _input_Addr, unsigned _input_Ep, brp_DHWCtrlUsbTransferAttr _input_Attr, unsigned _input_Mps, brp_buf _input_Data, size_t _input_Data_len, unsigned _input_TimeoutMs);
#else
brp_errcode brp_DHWCtrl_UsbHostTransferOut(brp_DHWCtrl_UsbHostTransferOut_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	unsigned Addr;
	unsigned Ep;
} brp_DHWCtrl_UsbHostTransferCancel_t;
/**
 * Cancel any pending or in-flight transfer on (_Addr_ , _Ep_). No-op if no transfer is pending.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **Addr** (in) USB device address on the host port.
 *   - **Ep** (in) USB endpoint number. Direction is implied by the command.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostTransferCancel(brp_protocol protocol, unsigned _input_Index, unsigned _input_Addr, unsigned _input_Ep);
#else
brp_errcode brp_DHWCtrl_UsbHostTransferCancel(brp_DHWCtrl_UsbHostTransferCancel_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	bool Enable;
} brp_DHWCtrl_UsbHostSofControl_t;
/**
 * Enable or disable SOF generation on _Index_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **Enable** (in) Enable (true) or disable (false) SOF generation.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostSofControl(brp_protocol protocol, unsigned _input_Index, bool _input_Enable);
#else
brp_errcode brp_DHWCtrl_UsbHostSofControl(brp_DHWCtrl_UsbHostSofControl_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlPinMapEntry* PinMap;
	size_t PinMap_len;
	unsigned PeripheralIndex;
	unsigned* SectorSize;
	unsigned* SectorCount;
} brp_DHWCtrl_FlashActivate_t;
/**
 * Apply the pin routing described by _PinMap_ and bring up the flash slot on _PeripheralIndex_. Returns the slot geometry (_SectorSize_ , _SectorCount_) so the host can size FlashRead / FlashWrite / FlashErase calls without carrying the geometry out-of-band.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PinMap** (in) Logical-to-physical pin assignments for this slot (SDMMC: _SdmmcClk_ / _SdmmcCmd_ / _SdmmcDat0..7_). Must contain exactly the functions this instance requires; unknown, surplus, or duplicate names are rejected with ErrInvalidParam.
 *   - **PinMap_len** (in) Number of elements in **PinMap**.
 *   - **PeripheralIndex** (in) Zero-based instance index within this peripheral category; defaults to 0 (the first instance). The valid range is firmware/hardware-variant specific; discoverable via ListPeripherals.
 *   - **SectorSize** (out) Size of one sector in bytes. All FlashRead / FlashWrite / FlashErase transfers are expressed in whole sectors of this size.
 *   - **SectorCount** (out) Total number of sectors in the slot. Valid _Sector_ indices are 0 .. _SectorCount_ \- 1.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_FlashActivate(brp_protocol protocol, brp_DHWCtrlPinMapEntry* _input_PinMap, size_t _input_PinMap_len, unsigned _input_PeripheralIndex, unsigned* SectorSize, unsigned* SectorCount);
#else
brp_errcode brp_DHWCtrl_FlashActivate(brp_DHWCtrl_FlashActivate_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
} brp_DHWCtrl_FlashDeactivate_t;
/**
 * Shut down the flash slot on _Index_. Whether pins and clocks are released back to the SoC pool is implementation-defined.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_FlashDeactivate(brp_protocol protocol, unsigned _input_Index);
#else
brp_errcode brp_DHWCtrl_FlashDeactivate(brp_DHWCtrl_FlashDeactivate_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	unsigned Sector;
	unsigned Count;
	brp_buf* Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_DHWCtrl_FlashRead_t;
/**
 * Read _Count_ sectors starting at _Sector_. Response is _Count_ * sector_size bytes packed contiguously into _Data_. The raw16 wire length field caps a single Read at 65535 bytes - hosts chunk larger reads.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **Sector** (in) Zero-based sector index within the slot.
 *   - **Count** (in) Number of sectors to read.
 *   - **Data** (out) Read sectors packed contiguously (_Count_ * sector_size bytes).
 *   - **Data_len** (out) Length of **Data** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_FlashRead(brp_protocol protocol, unsigned _input_Index, unsigned _input_Sector, unsigned _input_Count, brp_buf* Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrl_FlashRead(brp_DHWCtrl_FlashRead_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	unsigned Sector;
	brp_buf Data;
	size_t Data_len;
} brp_DHWCtrl_FlashWrite_t;
/**
 * Write len(_Data_) / sector_size sectors starting at _Sector_. Firmware derives the sector count from the data length; len(_Data_) % sector_size != 0 returns ErrFlashRange. For NOR / write-once slots the target sectors must already be in erased state; for eMMC / managed-flash slots the write is unconditional.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **Sector** (in) Zero-based sector index within the slot.
 *   - **Data** (in) Sector contents to write. Length must be a multiple of the slot's sector_size; firmware derives the sector count as len(_Data_) / sector_size.
 *   - **Data_len** (in) Length of **Data** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_FlashWrite(brp_protocol protocol, unsigned _input_Index, unsigned _input_Sector, brp_buf _input_Data, size_t _input_Data_len);
#else
brp_errcode brp_DHWCtrl_FlashWrite(brp_DHWCtrl_FlashWrite_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	unsigned Sector;
	unsigned Count;
} brp_DHWCtrl_FlashErase_t;
/**
 * Erase _Count_ sectors starting at _Sector_. For managed-flash slots (e.g. eMMC) this may be a TRIM hint or a no-op; the status is OK in either case.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **Sector** (in) Zero-based sector index within the slot.
 *   - **Count** (in) Number of sectors to erase.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_FlashErase(brp_protocol protocol, unsigned _input_Index, unsigned _input_Sector, unsigned _input_Count);
#else
brp_errcode brp_DHWCtrl_FlashErase(brp_DHWCtrl_FlashErase_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlPinMapEntry* PinMap;
	size_t PinMap_len;
	unsigned PeripheralIndex;
	brp_DHWCtrlSpiSettings Settings;
} brp_DHWCtrl_SpiActivate_t;
/**
 * Apply the pin routing described by _PinMap_ and bring up the SPI master on _PeripheralIndex_ with the requested clock, mode, and bit order. Word size is fixed at 8 bits. The controller drives only SCK/MOSI/MISO; chip-select is not managed here - drive it as an ordinary GPIO via GpioConfigure / GpioSetState, and poll a BUSY/IRQ line via GpioWaitState where the target requires it.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PinMap** (in) Logical-to-physical pin assignments for this master (_SpiSck_ / _SpiMosi_ / _SpiMiso_ ; chip-select is a plain GPIO and is not part of the map). Must contain exactly the functions this instance requires; unknown, surplus, or duplicate names are rejected with ErrInvalidParam.
 *   - **PinMap_len** (in) Number of elements in **PinMap**.
 *   - **PeripheralIndex** (in) Zero-based instance index within this peripheral category; defaults to 0 (the first instance). The valid range is firmware/hardware-variant specific; discoverable via ListPeripherals.
 *   - **Settings** (in) Bus configuration for an SPI master, applied by SpiActivate. Word size is fixed at 8 bits.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_SpiActivate(brp_protocol protocol, brp_DHWCtrlPinMapEntry* _input_PinMap, size_t _input_PinMap_len, unsigned _input_PeripheralIndex, brp_DHWCtrlSpiSettings _input_Settings);
#else
brp_errcode brp_DHWCtrl_SpiActivate(brp_DHWCtrl_SpiActivate_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
} brp_DHWCtrl_SpiDeactivate_t;
/**
 * Shut down the SPI master on _Index_. Whether pins and clocks are released back to the SoC pool is implementation-defined.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_SpiDeactivate(brp_protocol protocol, unsigned _input_Index);
#else
brp_errcode brp_DHWCtrl_SpiDeactivate(brp_DHWCtrl_SpiDeactivate_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Index;
	brp_buf DataOut;
	size_t DataOut_len;
	brp_buf* DataIn;
	size_t* DataIn_len;
	brp_mempool *mempool;
} brp_DHWCtrl_SpiTransfer_t;
/**
 * Clock _DataOut_ out on MOSI and capture _DataIn_ on MISO on the same clock edges (full duplex). _DataIn_ is always exactly as long as _DataOut_. For a write-only slave, ignore _DataIn_ ; for a read phase, send dummy bytes to generate the clocks. The whole buffer is clocked as one contiguous burst - wrap it in a chip-select window on the caller side (see SpiActivate).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Index** (in) Zero-based instance index within this peripheral category. The valid range is firmware / hardware-variant specific; discoverable via ListPeripherals.
 *   - **DataOut** (in) Bytes to shift out on MOSI.
 *   - **DataOut_len** (in) Length of **DataOut** (in bytes).
 *   - **DataIn** (out) Bytes captured on MISO; same length as _DataOut_.
 *   - **DataIn_len** (out) Length of **DataIn** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_SpiTransfer(brp_protocol protocol, unsigned _input_Index, brp_buf _input_DataOut, size_t _input_DataOut_len, brp_buf* DataIn, size_t* DataIn_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrl_SpiTransfer(brp_DHWCtrl_SpiTransfer_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_DHWCtrlPeripheralCategory Category;
	brp_DHWCtrlPinMapEntry* PinMap;
	size_t PinMap_len;
	unsigned** Indices;
	size_t* Indices_len;
	brp_mempool *mempool;
} brp_DHWCtrl_ListPeripherals_t;
/**
 * Discover which instances of a given peripheral _Category_ can be brought up with a candidate _PinMap_. The firmware returns the _PeripheralIndex_ of every instance in that category whose required functions are all present in _PinMap_ and routable to the GPIOs it assigns them. An empty result means the wiring drives no instance of that category. GPIO itself is not enumerated: addressing is SoC-native via _DHWCtrlGpioPin_ (_port_ \+ pin number) and the caller is expected to know their SoC. The response carries no pin information; since each _Activate_ map is exact, the host already holds every instance's pin set and detects cross-peripheral pin conflicts client-side.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Category** (in) Peripheral category to enumerate; only instances of this category are returned. --- Peripheral category; selects which Activate/transfer commands apply, and is the mandatory filter of ListPeripherals.
 *   - **PinMap** (in) Candidate logical-to-physical pin assignments to test. Each returned index is an instance of _Category_ whose required functions are all present here and routable to the assigned GPIOs.
 *   - **PinMap_len** (in) Number of elements in **PinMap**.
 *   - **Indices** (out) Zero-based instance indices of _Category_ that the supplied _PinMap_ can bring up; each is passable as _PeripheralIndex_ to the category's _Activate_ command.
 *   - **Indices_len** (out) Number of elements in **Indices**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_ListPeripherals(brp_protocol protocol, brp_DHWCtrlPeripheralCategory _input_Category, brp_DHWCtrlPinMapEntry* _input_PinMap, size_t _input_PinMap_len, unsigned** Indices, size_t* Indices_len, brp_mempool *mempool);
#else
brp_errcode brp_DHWCtrl_ListPeripherals(brp_DHWCtrl_ListPeripherals_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */