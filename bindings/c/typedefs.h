/**
 * @{
 */
#ifndef __BRP_BALTECH_API_TYPEDEFS_H__
#define __BRP_BALTECH_API_TYPEDEFS_H__

#include "brp_lib.h"

#include <limits.h>
#if UINT_MAX < 0xFFFFFFFF
#error "baltech_api requires unsigned with a size of >=32bits"
#endif

#define BRP_BALTECH_API_VERSION "4.2.0"
/**
 * 
 */
typedef struct {
	/**
	 * Low level card type / programmable decoder
	 */
	bool TTF;
	/**
	 * HITAG 2 Biphase
	 */
	bool Hitag2B;
	/**
	 * HITAG 2 Manchester
	 */
	bool Hitag2M;
	/**
	 * HITAG 1 or S
	 */
	bool Hitag1S;
	/**
	 * ioProx
	 */
	bool HidIoprox;
	/**
	 * HID Proximity
	 */
	bool HidProx;
	/**
	 * AWID
	 */
	bool HidAwid;
	/**
	 * Indala ASP
	 */
	bool HidIndala;
	/**
	 * QuadraKey
	 */
	bool Quadrakey;
	/**
	 * Keri
	 */
	bool Keri;
	/**
	 * HID Prox32
	 */
	bool HidProx32;
	/**
	 * Farpointe Pyramid
	 */
	bool Pyramid;
	/**
	 * EM4450
	 */
	bool EM4450;
	/**
	 * EM4100/EM4102
	 */
	bool EM4100;
	/**
	 * EM4205/EM4305
	 */
	bool EM4205;
} brp_CardTypes125KhzPart1;
/**
 * 
 */
typedef struct {
	/**
	 * Idteck
	 */
	bool Idteck;
	/**
	 * Cotag
	 */
	bool Cotag;
	/**
	 * Indala ASP+
	 */
	bool HidIndalaSecure;
	/**
	 * G-Prox
	 */
	bool GProx;
	/**
	 * SecuraKey
	 */
	bool SecuraKey;
} brp_CardTypes125KhzPart2;
/**
 * * 0x00-0x7F: index to SAM key, key version has to be 0 
 *   * 0x80-0xBF: index to key defined in crypto memory of the reader: Device/CryptoKey
 *   * 0xC0-0xCB: index to key defined in VHL file: DesfireKeyList
 *   * 0xFE: _legacy_ , use transport key 0xFF: key index unused
 */
typedef unsigned brp_DesfireKeyIdx;
/**
 * Filetypes supported by VHL.
 */
typedef enum {
	/**
	 * File is specified by DF name
	 */
	brp_FileType_FileByDfName = 0,
	/**
	 * File is specified by 2 byte FID
	 */
	brp_FileType_FileByFileId = 1,
	/**
	 * File is specified by APDU Select command that has to be executed to activate a file.
	 */
	brp_FileType_FileByApduCmd = 2,
	brp_FileType_undefined = -1
} brp_FileType;
static inline bool brp_FileType_is_valid(int val) {
	switch (val) {
		case 0: /* FileByDfName*/
		case 1: /* FileByFileId*/
		case 2: /* FileByApduCmd*/
			return true;
		default:
			return false;
	}
}
/**
 * This byte defines how a Legic segment shall be accessed. 
 * 
 * There are two possibilities to select a certain segment on a Legic card: 
 * 
 *   * ID: The reader selects the segment with the desired number. 
 *   * Stamp: The reader selects the first segment that matches the desired stamp. 
 * 
 * 
 * 
 * **If possible always stamp search should be used for segment identification to guarantee that only genuine cards are processed!**
 * 
 * Legic advant compatible readers support two addressing modes: 
 * 
 *   * Protocol Header: Stamp data (read-only) can be accessed starting with address 18 (data below address 18 is undefined). Application data follows directly after the stamp. 
 *   * Advant: Application data stored in S_DATA can be accessed starting with address 0. Stamp data is not accessible in this case.
 */
typedef struct {
	/**
	 * Use Advant address mode. If this bit is not set Protocol Header address mode will be applied.
	 */
	bool AdvantAddressMode;
	/**
	 * Use Stamp search to identify the desired segment. If this bit is not set the segment will be identified by ID.
	 */
	bool StampSearch;
} brp_SegmentIdentificationAndAddressing;
/**
 * This word defines the start address according to the addressing mode selected in SegmentIdentificationAndAddressing for every fragment. 
 * 
 * The MSB determines if a CRC check shall be applied for accessing this segment.
 */
typedef struct {
	/**
	 * CRC check is enabled for this fragment. In this case there must be an address entry in LegicCRCAddressList.
	 */
	bool EnableCRC;
} brp_AddressAndEnableCRC;
/**
 * This word defines the CRC address according to the addressing mode selected in SegmentIdentificationAndAddressing. There must be an entry for every fragment that has enabled the CRC check in AddressAndEnableCRC. 
 * 
 * The MSB determines the CRC type.
 */
typedef struct {
	/**
	 * Use 16-bit CRC
	 */
	bool CRC16bit;
} brp_CRCAddressAndCRCType;
/**
 * This bitmask can be combined with a reference to a key index in the readers keylist and specifies more details.
 */
typedef struct {
	/**
	 * The key assigned to this sector shall not be taken from the VHL file
	 */
	bool Secure;
	/**
	 * The key assigned to this sector/block shall be applied as key B
	 */
	bool KeyB;
} brp_MifareClassicVhlKeyAssignment;
/**
 * This value references a key memory type within the reader. VHL detects the security level (SL0..3) of a MIFARE Classic/Plus card automatically. According to the security level, the adequate key memories (AES and/or MIFARE keys) are chosen.
 */
typedef enum {
	/**
	 * References keys within the CryptoKey memory.   
	 * Key offset needed: refer to MifarePlusKeyIdxOffset
	 */
	brp_MifarePlusKeyMemoryType_CryptoKey = 0,
	/**
	 * References keys within a SAM, only available on SAM based readers: key index from 0x00 to 0x7F, a SAM key contains up to 3 AES keys with different versions or 3 Mifare key pairs (A and B). VHL uses always the first SAM key.   
	 * Key offset needed: see MifarePlusKeyIdxOffset
	 */
	brp_MifarePlusKeyMemoryType_SamKey = 1,
	/**
	 * References keys which are stored in reader chip memory: 32 keys (index 0..31) are available. 
	 * 
	 * **This memory contains only keys for Mifare classic cards (SL1).**
	 */
	brp_MifarePlusKeyMemoryType_ReaderChipKey = 2,
	/**
	 * References keys which are defined in respective VHL files:   
	 * AES keys in MifarePlusAesKeyList  
	 * Mifare keys in MifareKeyList
	 */
	brp_MifarePlusKeyMemoryType_VhlKey = 3,
	brp_MifarePlusKeyMemoryType_undefined = -1
} brp_MifarePlusKeyMemoryType;
static inline bool brp_MifarePlusKeyMemoryType_is_valid(int val) {
	switch (val) {
		case 0: /* CryptoKey*/
		case 1: /* SamKey*/
		case 2: /* ReaderChipKey*/
		case 3: /* VhlKey*/
			return true;
		default:
			return false;
	}
}
/**
 * This is the bit order for the _CutNibbles_ command.
 */
typedef enum {
	/**
	 * Handle Bytes in Least significant bit first order.
	 */
	brp_TemplateBitorder_Lsb = 0,
	/**
	 * Handle Bytes in Most significant bit first order.
	 */
	brp_TemplateBitorder_Msb = 1,
	brp_TemplateBitorder_undefined = -1
} brp_TemplateBitorder;
static inline bool brp_TemplateBitorder_is_valid(int val) {
	switch (val) {
		case 0: /* Lsb*/
		case 1: /* Msb*/
			return true;
		default:
			return false;
	}
}
/**
 * This is the desired data alignment.
 */
typedef enum {
	/**
	 * Align to the right. Example: ` 00001234 `
	 */
	brp_Alignment_Right = 1,
	/**
	 * Align to the left. Example: ` 12340000 `
	 */
	brp_Alignment_Left = 0,
	brp_Alignment_undefined = -1
} brp_Alignment;
static inline bool brp_Alignment_is_valid(int val) {
	switch (val) {
		case 0: /* Left*/
		case 1: /* Right*/
			return true;
		default:
			return false;
	}
}
/**
 * For every of these filter bits, a specific data conversion mechanism is specified. This mechanism is applied to a TemplateCommand if the filterbit is set. 
 * 
 * The activated filters are applied ordered by there value. Starting with the smallest value.
 */
typedef struct {
	/**
	 * Converts a BCD number (must only contain nibbles 0-9, not A-F) to a binary number. Input and output data are _MSB encoded_. ` 0x01 0x23 0x45 => 0x30 0x39 `
	 * 
	 * **Note the following restrictions:**
	 * 
	 *   * The largest BCD number this filter can convert is the following 39-digit number (20 bytes): ` 0x03 0x40 0x28 0x23 0x66 0x92 0x09 0x38 0x46 0x34 0x63 0x37 0x46 0x07 0x43 0x17 0x68 0x21 0x14 0x55 `
	 *   * The destination length (in bytes) is calculated by multiplying the source data length by 0.83048 and rounding down to the next byte boundary. 
	 * 
	 * If the source data's binary representation is longer than the calculated destination length, the conversion fails. Example: ` Source data (BCD): 0x12 0x34 Source data length: 2 bytes (4 digits) Converted data (binary): 0x04 0xD2 Actual destination data length: 2 bytes Calculated destination data length: int(2 bytes * 0.83048) = 1 byte `
	 * 
	 * The maximum BCD number convertible for a given source data length can be calculated as follows: ` 2 ^ {int(src_len * 0.83048) * 8} - 1 `
	 * 
	 * For example, for a 2-byte BCD number, the largest convertible value is 255: ` 0x02 0x55 => 0xFF `
	 * 
	 * If the source data may exceed the maximum convertible BCD number, insert an additional leading zero byte in front of it: ` 0x00 0x12 0x34 => 0x04 0xD2 `
	 */
	bool BcdToBin;
	/**
	 * Convert Binarydata to ASCII by converting the ASCII characters 0x00-0x09 to 0x30-0x39 and 0x0A-0x0F to 0x41-0x49. ` 0x01 0x0A -> 0x31 0x41 `
	 */
	bool BinToAscii;
	/**
	 * Splits the high and the low nibble of each byte into two separate bytes, where the high nibble is set to 0. ` 0x01 CF => 0x00 0x01 0x0C 0x0F `
	 */
	bool Unpack;
	/**
	 * Converts a binary Number to a BCD encoded number. Input and Output data are _MSB encoded_. 
	 * 
	 * The length of the destination data is the length of the source data in bytes) multiplied by 1.2041 (and rounded up to the next byte boundary). 
	 * 
	 * **This is not exactly the inverse of BcdToBin, since the length may differ.**
	 * 
	 * ` 0x04 0xD2 => 0x12 0x34 `
	 */
	bool BinToBcd;
	/**
	 * Swap the higher nibble (bits 5-7) of each byte with the lower nibble (bits 0-3). ` 0x12 0x34 0xEF => 0x21 0x43 0xFE `
	 */
	bool SwapNibbles;
	/**
	 * Merges two Bytes at a time to a single one by removing the leading nibble (which has to be 0) of each byte. ` 0x03 0x0F -> 0x3F `
	 */
	bool Pack;
	/**
	 * Convert ASCII to Binarydata by converting the ASCII characters 0x30-0x39 to 0x00-0x09 and 0x41-0x49 (0x61-0x66) to 0x0A-0x0F. ` 0x31 0x41 -> 0x01 0x0A `
	 */
	bool AsciiToBin;
	/**
	 * Swap the first byte with the last one, the second one with the next to last one and so on. ` 0x12 0x3D 0xEF => 0xEF 0x3D 0x12 `
	 */
	bool Reverse;
} brp_TemplateFilter;
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_AutoRunCommand_RunMode_Standard = 0,
	/**
	 * 
	 */
	brp_AutoRunCommand_RunMode_Continuous = 1,
	/**
	 * 
	 */
	brp_AutoRunCommand_RunMode_Repeat = 2,
	brp_AutoRunCommand_RunMode_undefined = -1
} brp_AutoRunCommand_RunMode;
static inline bool brp_AutoRunCommand_RunMode_is_valid(int val) {
	switch (val) {
		case 0: /* Standard*/
		case 1: /* Continuous*/
		case 2: /* Repeat*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * 
	 */
	brp_AutoRunCommand_RunMode RunMode;
	/**
	 * 
	 */
	unsigned DeviceCode;
	/**
	 * 
	 */
	unsigned CommandCode;
	/**
	 * The length of this block depends on the length of the command
	 */
	brp_buf Parameter;
} brp_AutoRunCommand;
/**
 * A list of all protocols. 
 * 
 * **Not all protocols are available on all Firmware variants.**
 */
typedef enum {
	/**
	 * Selects all available protocols. Only applicable for _BaltechScript.SendMsg_
	 */
	brp_ProtocolID_All = 0,
	/**
	 * BRP protocol over RS-232/UART. This protocol has also to be used if the USB-virtual-comport-emulation is used.
	 */
	brp_ProtocolID_BrpSerial = 3,
	/**
	 * BRP protocol over RS485 connection. Is used for long distances or when needing multiple devices on a single host.
	 */
	brp_ProtocolID_BrpRs485 = 4,
	/**
	 * BRP protocol over HID (Human Interface Device) Protocol. This is a standard USB Protocol with drivers for all OSes.
	 */
	brp_ProtocolID_BrpHid = 5,
	/**
	 * BRP protocol over TCP/IP.
	 */
	brp_ProtocolID_BrpTcp = 134,
	/**
	 * The debug interface may be used to look into the readers internals via a Terminal. Works over RS-232/UART or virtual-comport-emulation.
	 */
	brp_ProtocolID_DebugInterface = 9,
	/**
	 * This is a autoread protocol that sends the ID read by autoread mode without any protocol overhead. Works over RS-232/UART or virtual-comport-emulation.
	 */
	brp_ProtocolID_RawSerial = 35,
	/**
	 * This is a autoread protocol that sends the ID read by autoread mode via Wiegand protocol.
	 */
	brp_ProtocolID_Wiegand = 32,
	/**
	 * USB devices will register as keyboard if this value is active. When the autoread mode detected an ID it will be send by emulating keypresses.
	 */
	brp_ProtocolID_KeyboardEmulation = 43,
	/**
	 * configures the pins which are usually used by the _Wiegand_ / _RawSerial_ /... protocol as I/O Ports that can be controlled via scripts. 
	 * 
	 * I/O Port  |  physical pin   
	 * ---|---  
	 * Gpio5  |  TX of RawSerial protocol   
	 * Gpio6  |  direction line on RS485 protocols   
	 * Gpio7  |  RX pin of RawSerial protocol
	 */
	brp_ProtocolID_LowLevelIoPorts = 36,
	/**
	 * 
	 */
	brp_ProtocolID_ClkData = 34,
	/**
	 * 
	 */
	brp_ProtocolID_Omron = 33,
	/**
	 * 
	 */
	brp_ProtocolID_Snet = 16,
	/**
	 * 
	 */
	brp_ProtocolID_Bpa9 = 17,
	/**
	 * LBus protocol. Only supported by customer-specific firmware.
	 */
	brp_ProtocolID_LBus = 50,
	/**
	 * Chip Card Interface Device (CCID). USB protocol that allows a smartcard to be connected to a computer via a card reader using a standard USB interface.
	 */
	brp_ProtocolID_Ccid = 54,
	/**
	 * This is a second Autoread protocol that sends the ID read by Autoread mode without any protocol overhead.
	 */
	brp_ProtocolID_RawSerial2 = 55,
	/**
	 * Open Supervised Standard Protocol. New Protocol Standard used for long distances or when needing multiple devices on a single host.
	 */
	brp_ProtocolID_Osdp = 56,
	/**
	 * BLE HCI Protocol. USB protocol that allows the BLE component to be controlled via Host Controller Interface (HCI) as specified in the Bluetooth Core Specification.
	 */
	brp_ProtocolID_BleHci = 59,
	/**
	 * Indicates that the reader is connected to an IF Converter that connects to a server via Ethernet as HTTPS client.
	 */
	brp_ProtocolID_HttpsClient = 40,
	brp_ProtocolID_undefined = -1
} brp_ProtocolID;
static inline bool brp_ProtocolID_is_valid(int val) {
	switch (val) {
		case 0: /* All*/
		case 3: /* BrpSerial*/
		case 4: /* BrpRs485*/
		case 5: /* BrpHid*/
		case 9: /* DebugInterface*/
		case 16: /* Snet*/
		case 17: /* Bpa9*/
		case 32: /* Wiegand*/
		case 33: /* Omron*/
		case 34: /* ClkData*/
		case 35: /* RawSerial*/
		case 36: /* LowLevelIoPorts*/
		case 40: /* HttpsClient*/
		case 43: /* KeyboardEmulation*/
		case 50: /* LBus*/
		case 54: /* Ccid*/
		case 55: /* RawSerial2*/
		case 56: /* Osdp*/
		case 59: /* BleHci*/
		case 134: /* BrpTcp*/
			return true;
		default:
			return false;
	}
}
/**
 * Event that triggered the message. It allows the host application to interpret the message content correctly.
 */
typedef enum {
	/**
	 * A card or a phone with an active Mobile ID app was presented to the reader. The Autoread subsytem has read and converted the number based on the RFID interface component in the reader configuration. The result is returned in the message content.
	 */
	brp_MessageType_Card = 0,
	/**
	 * The tamper alarm was activated. By default, the message content is empty.
	 */
	brp_MessageType_AlarmOn = 1,
	/**
	 * The tamper alarm was deactivated. By default, the message content is empty.
	 */
	brp_MessageType_AlarmOff = 2,
	/**
	 * A PIN was entered via the reader's keyboard. The entered digits are returned in the message content.
	 */
	brp_MessageType_Keyboard = 3,
	/**
	 * A previously presented card has been removed. By default, the message content is empty. 
	 * 
	 * **This message type is only generated if the reader is configured to scan for card removals (Device.Run.AutoreadWaitForCardRemoval).**
	 */
	brp_MessageType_CardRemoval = 4,
	/**
	 * The user has pressed a certain function key, e.g. the hash (#), star (*), or ENTER (E) key. The code of the entered key is returned in the message content.
	 */
	brp_MessageType_FunctionKey = 5,
	/**
	 * The reader returned a log message. 
	 * 
	 * **When you request support, please forward these log messages to us to help us investigate the underlying issue. Please collect log messages from _all_ readers in your project. Only then will they provide meaningful insights.**
	 */
	brp_MessageType_Logs = 6,
	brp_MessageType_undefined = -1
} brp_MessageType;
static inline bool brp_MessageType_is_valid(int val) {
	switch (val) {
		case 0: /* Card*/
		case 1: /* AlarmOn*/
		case 2: /* AlarmOff*/
		case 3: /* Keyboard*/
		case 4: /* CardRemoval*/
		case 5: /* FunctionKey*/
		case 6: /* Logs*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri106Dsi106 = 0,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri212Dsi106 = 1,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri424Dsi106 = 2,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri848Dsi106 = 3,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri106Dsi212 = 4,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri212Dsi212 = 5,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri424Dsi212 = 6,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri848Dsi212 = 7,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri106Dsi424 = 8,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri212Dsi424 = 9,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri424Dsi424 = 10,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri848Dsi424 = 11,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri106Dsi848 = 12,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri212Dsi848 = 13,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri424Dsi848 = 14,
	/**
	 * 
	 */
	brp_MaxBaudrateIso14443_Dri848Dsi848 = 15,
	brp_MaxBaudrateIso14443_undefined = -1
} brp_MaxBaudrateIso14443;
static inline bool brp_MaxBaudrateIso14443_is_valid(int val) {
	switch (val) {
		case 0: /* Dri106Dsi106*/
		case 1: /* Dri212Dsi106*/
		case 2: /* Dri424Dsi106*/
		case 3: /* Dri848Dsi106*/
		case 4: /* Dri106Dsi212*/
		case 5: /* Dri212Dsi212*/
		case 6: /* Dri424Dsi212*/
		case 7: /* Dri848Dsi212*/
		case 8: /* Dri106Dsi424*/
		case 9: /* Dri212Dsi424*/
		case 10: /* Dri424Dsi424*/
		case 11: /* Dri848Dsi424*/
		case 12: /* Dri106Dsi848*/
		case 13: /* Dri212Dsi848*/
		case 14: /* Dri424Dsi848*/
		case 15: /* Dri848Dsi848*/
			return true;
		default:
			return false;
	}
}
/**
 * Access rights and key info 
 * 
 * Access rights: By default, all operations are allowed. With this bitmask, however, this key can be locked for certain operations.
 */
typedef struct {
	/**
	 * 
	 */
	bool IsVersion;
	/**
	 * The value for diversification data can be found in Project/DiversificationData.
	 */
	bool IsDivInfo;
	/**
	 * The value for diversification data can be found in VhlCfg/File/DesfireDiversificationData.
	 */
	bool IsDivInfoVhl;
	/**
	 * 
	 */
	bool DenyFormat;
	/**
	 * 
	 */
	bool DenyWrite;
	/**
	 * 
	 */
	bool DenyRead;
} brp_KeyAccessRights_KeySettings;
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_KeyAccessRights_DiversificationMode_NoDiversification = 0,
	/**
	 * Key diversification according to NXP AN10922.
	 */
	brp_KeyAccessRights_DiversificationMode_ModeAv2 = 2,
	brp_KeyAccessRights_DiversificationMode_undefined = -1
} brp_KeyAccessRights_DiversificationMode;
static inline bool brp_KeyAccessRights_DiversificationMode_is_valid(int val) {
	switch (val) {
		case 0: /* NoDiversification*/
		case 2: /* ModeAv2*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * Access rights and key info 
	 * 
	 * Access rights: By default, all operations are allowed. With this bitmask, however, this key can be locked for certain operations.
	 */
	brp_KeyAccessRights_KeySettings KeySettings;
	/**
	 * Key version.
	 */
	unsigned Version;
	/**
	 * 
	 */
	brp_KeyAccessRights_DiversificationMode DiversificationMode;
	/**
	 * Index for data converter rule: Possible values: 
	 * 
	 *   * Range 0..0x7F: Rule located in project
	 */
	unsigned DivIdx;
} brp_KeyAccessRights;
/**
 * 
 */
typedef struct {
	/**
	 * Project crypto memory page (range 0..0x0F)
	 */
	unsigned Page;
	/**
	 * Project crypto memory index within page (range 0x80..0xBF)
	 */
	unsigned Idx;
} brp_CryptoMemoryIndex;
/**
 * This byte defines the crypto algorithm that shall be used when working with the key that is following. The CryptoAlgorithm furhtermore implies the length of the following key
 */
typedef enum {
	/**
	 * Keylength: 8 byte
	 */
	brp_CryptoAlgorithm_DES = 1,
	/**
	 * Keylength: 16 byte
	 */
	brp_CryptoAlgorithm_TripleDES = 2,
	/**
	 * Keylength: 24 byte
	 */
	brp_CryptoAlgorithm_ThreeKeyTripleDES = 3,
	/**
	 * Keylength: 16 byte
	 */
	brp_CryptoAlgorithm_AES = 4,
	/**
	 * Keylength: 6 byte
	 */
	brp_CryptoAlgorithm_MifareClassic = 5,
	brp_CryptoAlgorithm_undefined = -1
} brp_CryptoAlgorithm;
static inline bool brp_CryptoAlgorithm_is_valid(int val) {
	switch (val) {
		case 1: /* DES*/
		case 2: /* TripleDES*/
		case 3: /* ThreeKeyTripleDES*/
		case 4: /* AES*/
		case 5: /* MifareClassic*/
			return true;
		default:
			return false;
	}
}
#ifdef BALTECH_SDK_INTERNAL
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_A = 0,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_B = 1,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_C = 2,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_D = 3,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_E = 4,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_F = 5,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_G = 6,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_H = 7,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_I = 8,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_J = 9,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_K = 10,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_L = 11,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_M = 12,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_N = 13,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_O = 14,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_P = 15,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_Q = 16,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_R = 17,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_S = 18,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_T = 19,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_U = 20,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_V = 21,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_W = 22,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_X = 23,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_Y = 24,
	/**
	 * 
	 */
	brp_DHWCtrlGpioPort_Z = 25,
	brp_DHWCtrlGpioPort_undefined = -1
} brp_DHWCtrlGpioPort;
static inline bool brp_DHWCtrlGpioPort_is_valid(int val) {
	switch (val) {
		case 0: /* A*/
		case 1: /* B*/
		case 2: /* C*/
		case 3: /* D*/
		case 4: /* E*/
		case 5: /* F*/
		case 6: /* G*/
		case 7: /* H*/
		case 8: /* I*/
		case 9: /* J*/
		case 10: /* K*/
		case 11: /* L*/
		case 12: /* M*/
		case 13: /* N*/
		case 14: /* O*/
		case 15: /* P*/
		case 16: /* Q*/
		case 17: /* R*/
		case 18: /* S*/
		case 19: /* T*/
		case 20: /* U*/
		case 21: /* V*/
		case 22: /* W*/
		case 23: /* X*/
		case 24: /* Y*/
		case 25: /* Z*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * GPIO bank letter (A..Z).
	 * ---
	 * SoC-native GPIO bank identifier. The keyword letters mirror the bank designators on STM32-style parts; not every part implements the full A..Z range. The firmware rejects banks it doesn't support with ErrInvalidParam.
	 */
	brp_DHWCtrlGpioPort Port;
	/**
	 * Pin number within the bank. Practical range is SoC-specific (typically 0..15 on STM32). Named _Number_ rather than _Index_ to avoid a NameChecker collision with the peripheral-instance _Index_ in ListPeripherals's _Pins_ array (struct parents don't currently participate in field-name namespacing).
	 */
	unsigned Number;
} brp_DHWCtrlGpioPin;
/**
 * 
 */
typedef enum {
	/**
	 * SPI clock.
	 */
	brp_DHWCtrlPinName_SpiSck = 0,
	/**
	 * SPI master-out/slave-in.
	 */
	brp_DHWCtrlPinName_SpiMosi = 1,
	/**
	 * SPI master-in/slave-out.
	 */
	brp_DHWCtrlPinName_SpiMiso = 2,
	/**
	 * RMII transmit data bit 0.
	 */
	brp_DHWCtrlPinName_EthTxd0 = 16,
	/**
	 * RMII transmit data bit 1.
	 */
	brp_DHWCtrlPinName_EthTxd1 = 17,
	/**
	 * RMII transmit enable.
	 */
	brp_DHWCtrlPinName_EthTxEn = 18,
	/**
	 * RMII receive data bit 0.
	 */
	brp_DHWCtrlPinName_EthRxd0 = 19,
	/**
	 * RMII receive data bit 1.
	 */
	brp_DHWCtrlPinName_EthRxd1 = 20,
	/**
	 * RMII carrier-sense/receive-data-valid.
	 */
	brp_DHWCtrlPinName_EthCrsDv = 21,
	/**
	 * RMII 50 MHz reference clock.
	 */
	brp_DHWCtrlPinName_EthRefClk = 22,
	/**
	 * MDIO management clock.
	 */
	brp_DHWCtrlPinName_EthMdc = 23,
	/**
	 * MDIO management data.
	 */
	brp_DHWCtrlPinName_EthMdio = 24,
	/**
	 * SDMMC clock.
	 */
	brp_DHWCtrlPinName_SdmmcClk = 48,
	/**
	 * SDMMC command line.
	 */
	brp_DHWCtrlPinName_SdmmcCmd = 49,
	/**
	 * SDMMC data bit 0.
	 */
	brp_DHWCtrlPinName_SdmmcDat0 = 50,
	/**
	 * SDMMC data bit 1.
	 */
	brp_DHWCtrlPinName_SdmmcDat1 = 51,
	/**
	 * SDMMC data bit 2.
	 */
	brp_DHWCtrlPinName_SdmmcDat2 = 52,
	/**
	 * SDMMC data bit 3.
	 */
	brp_DHWCtrlPinName_SdmmcDat3 = 53,
	/**
	 * SDMMC data bit 4.
	 */
	brp_DHWCtrlPinName_SdmmcDat4 = 54,
	/**
	 * SDMMC data bit 5.
	 */
	brp_DHWCtrlPinName_SdmmcDat5 = 55,
	/**
	 * SDMMC data bit 6.
	 */
	brp_DHWCtrlPinName_SdmmcDat6 = 56,
	/**
	 * SDMMC data bit 7.
	 */
	brp_DHWCtrlPinName_SdmmcDat7 = 57,
	/**
	 * USB D+ data line.
	 */
	brp_DHWCtrlPinName_UsbDp = 64,
	/**
	 * USB D- data line.
	 */
	brp_DHWCtrlPinName_UsbDm = 65,
	brp_DHWCtrlPinName_undefined = -1
} brp_DHWCtrlPinName;
static inline bool brp_DHWCtrlPinName_is_valid(int val) {
	switch (val) {
		case 0: /* SpiSck*/
		case 1: /* SpiMosi*/
		case 2: /* SpiMiso*/
		case 16: /* EthTxd0*/
		case 17: /* EthTxd1*/
		case 18: /* EthTxEn*/
		case 19: /* EthRxd0*/
		case 20: /* EthRxd1*/
		case 21: /* EthCrsDv*/
		case 22: /* EthRefClk*/
		case 23: /* EthMdc*/
		case 24: /* EthMdio*/
		case 48: /* SdmmcClk*/
		case 49: /* SdmmcCmd*/
		case 50: /* SdmmcDat0*/
		case 51: /* SdmmcDat1*/
		case 52: /* SdmmcDat2*/
		case 53: /* SdmmcDat3*/
		case 54: /* SdmmcDat4*/
		case 55: /* SdmmcDat5*/
		case 56: /* SdmmcDat6*/
		case 57: /* SdmmcDat7*/
		case 64: /* UsbDp*/
		case 65: /* UsbDm*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * Logical peripheral function this pin carries.
	 * ---
	 * Logical pin-function identifier, prefixed by electrical bus/signal family (_not_ by DHWCtrl peripheral category). A signal shared by 2 roles on the same bus reuses a single keyword - e.g. _UsbDp_ / _UsbDm_ serve both a USB host and a (future) USB device role. It is used as the logical side of a _DHWCtrlPinMapEntry_ ; a given _Activate_ accepts only the names of the one or more buses its category uses.
	 */
	brp_DHWCtrlPinName Name;
	/**
	 * Physical SoC GPIO the function is routed to.
	 * ---
	 * Reference to a single physical GPIO pin: SoC bank (_DHWCtrlGpioPort_) plus pin number within the bank. The firmware rejects pin numbers outside the bank's actual width with ErrInvalidParam.
	 */
	brp_DHWCtrlGpioPin Pin;
} brp_DHWCtrlPinMapEntry;
/**
 * 
 */
typedef enum {
	/**
	 * Ethernet port; addressed by _Eth*_ commands.
	 */
	brp_DHWCtrlPeripheralCategory_Eth = 0,
	/**
	 * USB host controller; addressed by _UsbHost*_ commands.
	 */
	brp_DHWCtrlPeripheralCategory_UsbHost = 32,
	/**
	 * Flash slot; addressed by _Flash*_ commands.
	 */
	brp_DHWCtrlPeripheralCategory_Flash = 48,
	/**
	 * SPI master; addressed by _Spi*_ commands.
	 */
	brp_DHWCtrlPeripheralCategory_Spi = 64,
	brp_DHWCtrlPeripheralCategory_undefined = -1
} brp_DHWCtrlPeripheralCategory;
static inline bool brp_DHWCtrlPeripheralCategory_is_valid(int val) {
	switch (val) {
		case 0: /* Eth*/
		case 32: /* UsbHost*/
		case 48: /* Flash*/
		case 64: /* Spi*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_DHWCtrlGpioLevel_Low = 0,
	/**
	 * 
	 */
	brp_DHWCtrlGpioLevel_High = 1,
	brp_DHWCtrlGpioLevel_undefined = -1
} brp_DHWCtrlGpioLevel;
static inline bool brp_DHWCtrlGpioLevel_is_valid(int val) {
	switch (val) {
		case 0: /* Low*/
		case 1: /* High*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_DHWCtrlUsbPortState_Disconnected = 0,
	/**
	 * 
	 */
	brp_DHWCtrlUsbPortState_Connected = 1,
	brp_DHWCtrlUsbPortState_undefined = -1
} brp_DHWCtrlUsbPortState;
static inline bool brp_DHWCtrlUsbPortState_is_valid(int val) {
	switch (val) {
		case 0: /* Disconnected*/
		case 1: /* Connected*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_DHWCtrlUsbTransferAttr_Bulk = 0,
	/**
	 * 
	 */
	brp_DHWCtrlUsbTransferAttr_Interrupt = 1,
	/**
	 * 
	 */
	brp_DHWCtrlUsbTransferAttr_Iso = 2,
	brp_DHWCtrlUsbTransferAttr_undefined = -1
} brp_DHWCtrlUsbTransferAttr;
static inline bool brp_DHWCtrlUsbTransferAttr_is_valid(int val) {
	switch (val) {
		case 0: /* Bulk*/
		case 1: /* Interrupt*/
		case 2: /* Iso*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_DHWCtrlEthLinkState_Down = 0,
	/**
	 * 
	 */
	brp_DHWCtrlEthLinkState_Up = 1,
	brp_DHWCtrlEthLinkState_undefined = -1
} brp_DHWCtrlEthLinkState;
static inline bool brp_DHWCtrlEthLinkState_is_valid(int val) {
	switch (val) {
		case 0: /* Down*/
		case 1: /* Up*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * Internet Protocol version 4.
	 */
	brp_DHWCtrlEtherType_IPv4 = 2048,
	/**
	 * Address Resolution Protocol.
	 */
	brp_DHWCtrlEtherType_ARP = 2054,
	/**
	 * Reverse Address Resolution Protocol.
	 */
	brp_DHWCtrlEtherType_ReverseARP = 32821,
	/**
	 * Internet Protocol version 6.
	 */
	brp_DHWCtrlEtherType_IPv6 = 34525,
	/**
	 * IEEE 802.1Q VLAN tag (TPID). The 2 bytes following the EtherType slot carry the TCI (priority + DEI + VLAN ID); the inner EtherType identifying the actual payload protocol follows after that.
	 */
	brp_DHWCtrlEtherType_VlanTagged = 33024,
	/**
	 * IEEE 802.1ad service VLAN tag ("QinQ"). Outer provider tag in stacked-VLAN frames.
	 */
	brp_DHWCtrlEtherType_ServiceVlanTagged = 34984,
	/**
	 * Link Aggregation Control Protocol (IEEE 802.3ad).
	 */
	brp_DHWCtrlEtherType_LACP = 34825,
	/**
	 * MPLS unicast.
	 */
	brp_DHWCtrlEtherType_MplsUnicast = 34887,
	/**
	 * MPLS multicast.
	 */
	brp_DHWCtrlEtherType_MplsMulticast = 34888,
	/**
	 * Link Layer Discovery Protocol (IEEE 802.1AB).
	 */
	brp_DHWCtrlEtherType_LLDP = 35020,
	/**
	 * MAC Security (IEEE 802.1AE).
	 */
	brp_DHWCtrlEtherType_MACsec = 35045,
	/**
	 * Ethernet Configuration Testing Protocol (loopback).
	 */
	brp_DHWCtrlEtherType_Loopback = 36864,
	brp_DHWCtrlEtherType_undefined = -1
} brp_DHWCtrlEtherType;
static inline bool brp_DHWCtrlEtherType_is_valid(int val) {
	switch (val) {
		case 2048: /* IPv4*/
		case 2054: /* ARP*/
		case 32821: /* ReverseARP*/
		case 33024: /* VlanTagged*/
		case 34525: /* IPv6*/
		case 34825: /* LACP*/
		case 34887: /* MplsUnicast*/
		case 34888: /* MplsMulticast*/
		case 34984: /* ServiceVlanTagged*/
		case 35020: /* LLDP*/
		case 35045: /* MACsec*/
		case 36864: /* Loopback*/
			return true;
		default:
			return false;
	}
}
/**
 * Clock polarity: the level the clock rests at while idle.
 */
typedef enum {
	/**
	 * Clock idles low.
	 */
	brp_DHWCtrlSpiSettings_Cpol_IdleLow = 0,
	/**
	 * Clock idles high.
	 */
	brp_DHWCtrlSpiSettings_Cpol_IdleHigh = 1,
	brp_DHWCtrlSpiSettings_Cpol_undefined = -1
} brp_DHWCtrlSpiSettings_Cpol;
static inline bool brp_DHWCtrlSpiSettings_Cpol_is_valid(int val) {
	switch (val) {
		case 0: /* IdleLow*/
		case 1: /* IdleHigh*/
			return true;
		default:
			return false;
	}
}
/**
 * Clock phase: which clock edge of a bit period samples the data.
 */
typedef enum {
	/**
	 * Each bit is sampled on the first clock edge of its bit period.
	 */
	brp_DHWCtrlSpiSettings_Cpha_SampleOnFirstEdge = 0,
	/**
	 * Each bit is sampled on the second clock edge of its bit period.
	 */
	brp_DHWCtrlSpiSettings_Cpha_SampleOnSecondEdge = 1,
	brp_DHWCtrlSpiSettings_Cpha_undefined = -1
} brp_DHWCtrlSpiSettings_Cpha;
static inline bool brp_DHWCtrlSpiSettings_Cpha_is_valid(int val) {
	switch (val) {
		case 0: /* SampleOnFirstEdge*/
		case 1: /* SampleOnSecondEdge*/
			return true;
		default:
			return false;
	}
}
/**
 * Bit transmission order on the wire.
 */
typedef enum {
	/**
	 * Most-significant bit of each byte first.
	 */
	brp_DHWCtrlSpiSettings_BitOrder_MsbFirst = 0,
	/**
	 * Least-significant bit of each byte first.
	 */
	brp_DHWCtrlSpiSettings_BitOrder_LsbFirst = 1,
	brp_DHWCtrlSpiSettings_BitOrder_undefined = -1
} brp_DHWCtrlSpiSettings_BitOrder;
static inline bool brp_DHWCtrlSpiSettings_BitOrder_is_valid(int val) {
	switch (val) {
		case 0: /* MsbFirst*/
		case 1: /* LsbFirst*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * SPI clock frequency in Hz. The firmware rounds down to the nearest achievable prescaler value. Keep this within the maximum clock frequency supported by the connected target.
	 */
	unsigned ClockHz;
	/**
	 * Clock polarity: the level the clock rests at while idle.
	 */
	brp_DHWCtrlSpiSettings_Cpol Cpol;
	/**
	 * Clock phase: which clock edge of a bit period samples the data.
	 */
	brp_DHWCtrlSpiSettings_Cpha Cpha;
	/**
	 * Bit transmission order on the wire.
	 */
	brp_DHWCtrlSpiSettings_BitOrder BitOrder;
} brp_DHWCtrlSpiSettings;
#endif  // BALTECH_SDK_INTERNAL
/**
 * _Divisor Send/Receive Integer_ (DSI/DRI) 
 * 
 * This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 */
typedef enum {
	/**
	 * 
	 */
	brp_DivisorInteger_Kbps106 = 0,
	/**
	 * 
	 */
	brp_DivisorInteger_Kbps212 = 1,
	/**
	 * 
	 */
	brp_DivisorInteger_Kbps424 = 2,
	/**
	 * 
	 */
	brp_DivisorInteger_Kbps848 = 3,
	brp_DivisorInteger_undefined = -1
} brp_DivisorInteger;
static inline bool brp_DivisorInteger_is_valid(int val) {
	switch (val) {
		case 0: /* Kbps106*/
		case 1: /* Kbps212*/
		case 2: /* Kbps424*/
		case 3: /* Kbps848*/
			return true;
		default:
			return false;
	}
}
#ifdef BALTECH_SDK_INTERNAL
/**
 * 
 */
typedef unsigned brp_Time;
/**
 * 
 */
typedef struct {
	/**
	 * 
	 */
	bool Gpio7;
	/**
	 * 
	 */
	bool Gpio6;
	/**
	 * 
	 */
	bool Gpio5;
	/**
	 * 
	 */
	bool Gpio4;
	/**
	 * 
	 */
	bool Gpio3;
	/**
	 * 
	 */
	bool Gpio2;
	/**
	 * 
	 */
	bool Gpio1;
	/**
	 * 
	 */
	bool Gpio0;
	/**
	 * 
	 */
	bool TamperAlarm;
	/**
	 * 
	 */
	bool BlueLed;
	/**
	 * 
	 */
	bool Input1;
	/**
	 * 
	 */
	bool Input0;
	/**
	 * 
	 */
	bool Relay;
	/**
	 * 
	 */
	bool Beeper;
	/**
	 * 
	 */
	bool RedLed;
	/**
	 * 
	 */
	bool GreenLed;
} brp_IoPortBitmask;
#endif  // BALTECH_SDK_INTERNAL
/**
 * 
 */
typedef enum {
	/**
	 * The reader has a green LED.
	 */
	brp_FeatureID_GreenLed = 1,
	/**
	 * The reader has a red LED.
	 */
	brp_FeatureID_RedLed = 2,
	/**
	 * The reader has a beeper.
	 */
	brp_FeatureID_Beeper = 3,
	/**
	 * The reader can switch a relay.
	 */
	brp_FeatureID_Relay = 4,
	/**
	 * The reader supports 13.56 MHz cards.
	 */
	brp_FeatureID_MHz13 = 5,
	/**
	 * The reader supports 125 kHz cards.
	 */
	brp_FeatureID_Khz125 = 6,
	/**
	 * The reader supports ISO 14443 Type A cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Iso14443A = 7,
	/**
	 * The reader can read the UID of an ISO 14443 Type A card.
	 * 
	 * **If _Iso14443A_ is listed as well, that feature scope applies.**
	 */
	brp_FeatureID_Iso14443AUidOnly = 8,
	/**
	 * The reader supports ISO 14443 Type B cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Iso14443B = 9,
	/**
	 * The reader can read the UID of an ISO 14443 Type B card.
	 * 
	 * **If _Iso14443B_ is listed as well, that feature scope applies.**
	 */
	brp_FeatureID_Iso14443BUidOnly = 10,
	/**
	 * The reader supports ISO 15693 cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Iso15693 = 11,
	/**
	 * The reader can read the UID of an ISO 15693 card.
	 * 
	 * **If _Iso15693_ is listed as well, that feature scope applies.**
	 */
	brp_FeatureID_Iso15693UidOnly = 12,
	/**
	 * The reader supports FeliCa cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Felica = 13,
	/**
	 * The reader can read the UID of a FeliCa card.
	 * 
	 * **If _FeliCa_ is listed as well, that feature scope applies.**
	 */
	brp_FeatureID_FelicaUidOnly = 14,
	/**
	 * The reader supports LEGIC cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Legic = 15,
	/**
	 * The reader has a SAM slot.
	 */
	brp_FeatureID_Sam = 16,
	/**
	 * A SAM AV2 card is inserted.
	 */
	brp_FeatureID_SamAv2 = 17,
	/**
	 * An HID SAM card is inserted.
	 */
	brp_FeatureID_SamHid = 18,
	/**
	 * The reader supports PicoPass cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Picopass = 19,
	/**
	 * The reader supports MIFARE Classic cards and MIFARE Plus cards in Security Level 1 using MIFARE CRYPTO1 authentication as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_MifareClassic = 35,
	/**
	 * The reader supports MIFARE Plus EV0 cards in Security Level 3 using AES authentication as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_MifarePlusEv0 = 36,
	/**
	 * The reader supports MIFARE DESFire EV1 cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_MifareDESFireEv1 = 37,
	/**
	 * The reader supports ST SRIX cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Srix = 38,
	/**
	 * The reader supports Jewel cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Jewel = 39,
	/**
	 * The reader supports ISO 14443-4 cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_ISO14443L4 = 40,
	/**
	 * The reader supports inter-industry ISO 14443-4 cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_InterIndustry = 41,
	/**
	 * The reader supports EM 4205 cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_EM4205 = 42,
	/**
	 * The reader supports EM 4100 cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_EM4100 = 43,
	/**
	 * The reader supports EM 4450 cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_EM4450 = 44,
	/**
	 * The reader supports Farpointe Pyramid cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_FarpointePyramid = 45,
	/**
	 * The reader supports HID Prox32 tags as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_HidProx32 = 46,
	/**
	 * The reader supports HID AWID tags as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_HidAwid = 47,
	/**
	 * The reader supports HID Prox tags as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_HidProx = 48,
	/**
	 * The reader supports HID ioProx tags as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_HidIoProx = 49,
	/**
	 * The reader supports Indala cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Indala = 50,
	/**
	 * The reader supports Keri Systems cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Keri = 51,
	/**
	 * The reader supports Indala FlexSecur cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_IndalaSecure = 52,
	/**
	 * The reader supports QuadraKey cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Quadrakey = 53,
	/**
	 * The reader supports SecuraKey cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_SecuraKey = 54,
	/**
	 * The reader supports G-Prox cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_GProx = 55,
	/**
	 * The reader supports Hitag 1 and Hitag S cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Hitag1S = 56,
	/**
	 * The reader supports Hitag 2 Manchester cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Hitag2M = 57,
	/**
	 * The reader supports Hitag 2 Biphase cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Hitag2B = 58,
	/**
	 * The reader has a blue LED.
	 */
	brp_FeatureID_BlueLed = 59,
	/**
	 * The reader supports Cotag cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_Cotag = 60,
	/**
	 * The reader can read the UID of a PicoPass card.
	 * 
	 * **If _Picopass_ is listed as well, that feature scope applies.**
	 */
	brp_FeatureID_PicopassUidOnly = 61,
	/**
	 * The reader supports IDTECK cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_IdTeck = 62,
	/**
	 * The reader has a tamper alarm.
	 */
	brp_FeatureID_Tamper = 63,
	/**
	 * The hardware limits the HF baud rate to 106 kbps.
	 * 
	 * **This applies to LEGIC readers only.**
	 */
	brp_FeatureID_MaxHfBaudrate106kbps = 64,
	/**
	 * The hardware limits the HF baud rate to 212 kbps.
	 * 
	 * **This applies to LEGIC readers only.**
	 */
	brp_FeatureID_MaxHfBaudrate212kbps = 65,
	/**
	 * The hardware limits the HF baud rate to 424 kbps.
	 * 
	 * **This applies to LEGIC readers only.**
	 */
	brp_FeatureID_MaxHfBaudrate424kbps = 66,
	/**
	 * Due to an aborted upload, the firmware on the reader is incomplete and not fully functional. 
	 * 
	 * **Repeat the firmware upload.**
	 */
	brp_FeatureID_FirmwareLoader = 67,
	/**
	 * The firmware can be updated via a serial interface (RS-232/UART or virtual COM port).
	 */
	brp_FeatureID_FwUploadViaBrpOverSer = 68,
	/**
	 * The reader supports AES-encrypted communication with the host.
	 */
	brp_FeatureID_AesHostProtocolEncryption = 69,
	/**
	 * The reader supports PKI-encrypted communication with the host.
	 */
	brp_FeatureID_PkiHostProtocolEncryption = 70,
	/**
	 * General info: The reader supports reading the PCN of HID iCLASS cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_HidIClass = 71,
	/**
	 * More accurate info: The reader supports reading the PCN of HID iCLASS SR cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html). This is supported by LEGIC readers and Multi readers with HID iCLASS SE processor.
	 */
	brp_FeatureID_HidIClassSr = 72,
	/**
	 * More accurate info: The reader supports reading the PCN of HID iCLASS SE and Seos cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html). This is supported by Multi readers with HID iCLASS SE processor.
	 */
	brp_FeatureID_HidIClassSeAndSeos = 73,
	/**
	 * The reader supports Mifare Ultralight cards as documented The reader supports Mifare Ultralight cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_MifareUltralight = 74,
	/**
	 * The reader supports the emulation of ISO14443-4 compatible cards.
	 */
	brp_FeatureID_CardEmulationISO14443L4 = 75,
	/**
	 * The reader supports MIFARE DESFire EV2 cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_MifareDESFireEv2 = 76,
	/**
	 * The reader supports MIFARE Plus EV1 cards in Security Level 3 using AES authentication as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_MifarePlusEv1 = 77,
	/**
	 * A SAM AV3 card is inserted.
	 */
	brp_FeatureID_SamAv3 = 78,
	/**
	 * The reader supports OSDP specification version 2.17.
	 */
	brp_FeatureID_OsdpV217 = 79,
	/**
	 * The reader supports Bluetooth Low Energy (BLE).
	 */
	brp_FeatureID_Bluetooth = 80,
	/**
	 * The reader has an RGB LED that is fully [ customizable](https://docs.baltech.de/project-setup/customize-led.html#customization-options-supported-reader-types).
	 */
	brp_FeatureID_RgbLed = 81,
	/**
	 * The reader has an RGB LED that is [ customizable](https://docs.baltech.de/project-setup/customize-led.html#customization-options-supported-reader-types) to a limited extend.
	 */
	brp_FeatureID_RgbLedLimited = 82,
	/**
	 * The reader supports firmware/configuration upload via BEC2 files.
	 */
	brp_FeatureID_Bec2Upload = 83,
	/**
	 * The reader supports MIFARE DESFire EV3 cards as documented [here](https://docs.baltech.de/developers/supported-card-types.html).
	 */
	brp_FeatureID_MifareDESFireEv3 = 84,
	/**
	 * The reader supports Mobile ID as documented [here](https://docs.baltech.de/mobile-id/map-mobile-id.html).
	 */
	brp_FeatureID_MobileId = 85,
	/**
	 * The reader supports Mobile Card Emulation (MCE).
	 */
	brp_FeatureID_MobileCardEmulation = 86,
	/**
	 * The reader supports the Bluetooth Host Controller Interface (HCI).
	 */
	brp_FeatureID_BleHci = 87,
	/**
	 * The reader can be used as Bluetooth Peripheral.
	 */
	brp_FeatureID_BlePeripheral = 88,
	brp_FeatureID_undefined = -1
} brp_FeatureID;
static inline bool brp_FeatureID_is_valid(int val) {
	switch (val) {
		case 1: /* GreenLed*/
		case 2: /* RedLed*/
		case 3: /* Beeper*/
		case 4: /* Relay*/
		case 5: /* MHz13*/
		case 6: /* Khz125*/
		case 7: /* Iso14443A*/
		case 8: /* Iso14443AUidOnly*/
		case 9: /* Iso14443B*/
		case 10: /* Iso14443BUidOnly*/
		case 11: /* Iso15693*/
		case 12: /* Iso15693UidOnly*/
		case 13: /* Felica*/
		case 14: /* FelicaUidOnly*/
		case 15: /* Legic*/
		case 16: /* Sam*/
		case 17: /* SamAv2*/
		case 18: /* SamHid*/
		case 19: /* Picopass*/
		case 35: /* MifareClassic*/
		case 36: /* MifarePlusEv0*/
		case 37: /* MifareDESFireEv1*/
		case 38: /* Srix*/
		case 39: /* Jewel*/
		case 40: /* ISO14443L4*/
		case 41: /* InterIndustry*/
		case 42: /* EM4205*/
		case 43: /* EM4100*/
		case 44: /* EM4450*/
		case 45: /* FarpointePyramid*/
		case 46: /* HidProx32*/
		case 47: /* HidAwid*/
		case 48: /* HidProx*/
		case 49: /* HidIoProx*/
		case 50: /* Indala*/
		case 51: /* Keri*/
		case 52: /* IndalaSecure*/
		case 53: /* Quadrakey*/
		case 54: /* SecuraKey*/
		case 55: /* GProx*/
		case 56: /* Hitag1S*/
		case 57: /* Hitag2M*/
		case 58: /* Hitag2B*/
		case 59: /* BlueLed*/
		case 60: /* Cotag*/
		case 61: /* PicopassUidOnly*/
		case 62: /* IdTeck*/
		case 63: /* Tamper*/
		case 64: /* MaxHfBaudrate106kbps*/
		case 65: /* MaxHfBaudrate212kbps*/
		case 66: /* MaxHfBaudrate424kbps*/
		case 67: /* FirmwareLoader*/
		case 68: /* FwUploadViaBrpOverSer*/
		case 69: /* AesHostProtocolEncryption*/
		case 70: /* PkiHostProtocolEncryption*/
		case 71: /* HidIClass*/
		case 72: /* HidIClassSr*/
		case 73: /* HidIClassSeAndSeos*/
		case 74: /* MifareUltralight*/
		case 75: /* CardEmulationISO14443L4*/
		case 76: /* MifareDESFireEv2*/
		case 77: /* MifarePlusEv1*/
		case 78: /* SamAv3*/
		case 79: /* OsdpV217*/
		case 80: /* Bluetooth*/
		case 81: /* RgbLed*/
		case 82: /* RgbLedLimited*/
		case 83: /* Bec2Upload*/
		case 84: /* MifareDESFireEv3*/
		case 85: /* MobileId*/
		case 86: /* MobileCardEmulation*/
		case 87: /* BleHci*/
		case 88: /* BlePeripheral*/
			return true;
		default:
			return false;
	}
}
/**
 * A bitmask containing the physical LEDs you want to switch.
 */
typedef struct {
	/**
	 * LED(s) on the left side of the reader 
	 * 
	 * **On readers with only a single LED, this bit has no effect.**
	 */
	bool LeftLed;
	/**
	 * LED(s) on the right side of the reader 
	 * 
	 * **On readers with only a single LED, this bit has no effect.**
	 */
	bool RightLed;
	/**
	 * Single LED of the reader 
	 * 
	 * **On readers with 2 or more LEDs, this bit has no effect.**
	 */
	bool SingleLed;
} brp_LedBitMask;
/**
 * Specifies the Parity-bit mode which is used for RS-232/UART protocols.
 */
typedef enum {
	/**
	 * No Parity is used
	 */
	brp_Parity_None_ = 78,
	/**
	 * Parity is used. The Parity bit is set if number of set bits is even.
	 */
	brp_Parity_Even = 69,
	/**
	 * Parity is used. The Parity bit is set if number of set bits is odd.
	 */
	brp_Parity_Odd = 79,
	brp_Parity_undefined = -1
} brp_Parity;
static inline bool brp_Parity_is_valid(int val) {
	switch (val) {
		case 69: /* Even*/
		case 78: /* None_*/
		case 79: /* Odd*/
			return true;
		default:
			return false;
	}
}
/**
 * The Baudrate specifies the performance of an RS-232/UART based interface in bits per second. 
 * 
 * **For the old-style 8bit format, which omits the least significant digit, this format is not supported any more. Configurations using this format cannot be opened.**
 */
typedef enum {
	/**
	 * 300 Baud
	 */
	brp_Baudrate_Baud300 = 3,
	/**
	 * 600 Baud
	 */
	brp_Baudrate_Baud600 = 6,
	/**
	 * 1200 Baud
	 */
	brp_Baudrate_Baud1200 = 12,
	/**
	 * 2400 Baud
	 */
	brp_Baudrate_Baud2400 = 24,
	/**
	 * 4800 Baud
	 */
	brp_Baudrate_Baud4800 = 48,
	/**
	 * 9600 Baud
	 */
	brp_Baudrate_Baud9600 = 96,
	/**
	 * 14400 Baud
	 */
	brp_Baudrate_Baud14400 = 144,
	/**
	 * 19200 Baud
	 */
	brp_Baudrate_Baud19200 = 192,
	/**
	 * 28800 Baud
	 */
	brp_Baudrate_Baud28800 = 288,
	/**
	 * 38400 Baud
	 */
	brp_Baudrate_Baud38400 = 384,
	/**
	 * 57600 Baud
	 */
	brp_Baudrate_Baud57600 = 576,
	/**
	 * 115200 Baud
	 */
	brp_Baudrate_Baud115200 = 1152,
	/**
	 * 500 kBaud
	 */
	brp_Baudrate_Baud500000 = 5000,
	/**
	 * 576 kBaud
	 */
	brp_Baudrate_Baud576000 = 5760,
	/**
	 * 921 kBaud
	 */
	brp_Baudrate_Baud921600 = 9216,
	brp_Baudrate_undefined = -1
} brp_Baudrate;
static inline bool brp_Baudrate_is_valid(int val) {
	switch (val) {
		case 3: /* Baud300*/
		case 6: /* Baud600*/
		case 12: /* Baud1200*/
		case 24: /* Baud2400*/
		case 48: /* Baud4800*/
		case 96: /* Baud9600*/
		case 144: /* Baud14400*/
		case 192: /* Baud19200*/
		case 288: /* Baud28800*/
		case 384: /* Baud38400*/
		case 576: /* Baud57600*/
		case 1152: /* Baud115200*/
		case 5000: /* Baud500000*/
		case 5760: /* Baud576000*/
		case 9216: /* Baud921600*/
			return true;
		default:
			return false;
	}
}
/**
 * I/O pins of the reader that can be controlled by the user.
 */
typedef enum {
	/**
	 * Enable/disable/toggle the green LED (if available).
	 */
	brp_IoPort_GreenLed = 0,
	/**
	 * Enable/disable/toggle the red LED (if available).
	 */
	brp_IoPort_RedLed = 1,
	/**
	 * Enable/disable/toggle the beeper (if available).
	 */
	brp_IoPort_Beeper = 2,
	/**
	 * Enable/disable/toggle the relay (if available).
	 */
	brp_IoPort_Relay = 3,
	/**
	 * Retrieve the state of the custom input 0.
	 */
	brp_IoPort_Input0 = 4,
	/**
	 * Retrieve the state of the custom input 1.
	 */
	brp_IoPort_Input1 = 5,
	/**
	 * Enable/disable/toggle the blue LED (if available).
	 */
	brp_IoPort_BlueLed = 6,
	/**
	 * Retrieve the state of the tamper alarm.
	 */
	brp_IoPort_TamperAlarm = 7,
	/**
	 * Refers to a general purpose I/O. The physical pin assigned to this logical I/O port depends on the physical setup of the device.
	 */
	brp_IoPort_Gpio0 = 8,
	/**
	 * Refers to a general purpose I/O. The physical pin assigned to this logical I/O port depends on the physical setup of the device.
	 */
	brp_IoPort_Gpio1 = 9,
	/**
	 * Refers to a general purpose I/O. The physical pin assigned to this logical I/O port depends on the physical setup of the device.
	 */
	brp_IoPort_Gpio2 = 10,
	/**
	 * Refers to a general purpose I/O. The physical pin assigned to this logical I/O port depends on the physical setup of the device.
	 */
	brp_IoPort_Gpio3 = 11,
	/**
	 * Refers to a general purpose I/O. The physical pin assigned to this logical I/O port depends on the physical setup of the device.
	 */
	brp_IoPort_Gpio4 = 12,
	/**
	 * Refers to a general purpose I/O. The physical pin assigned to this logical I/O port depends on the physical setup of the device.
	 */
	brp_IoPort_Gpio5 = 13,
	/**
	 * Refers to a general purpose I/O. The physical pin assigned to this logical I/O port depends on the physical setup of the device.
	 */
	brp_IoPort_Gpio6 = 14,
	/**
	 * Refers to a general purpose I/O. The physical pin assigned to this logical I/O port depends on the physical setup of the device.
	 */
	brp_IoPort_Gpio7 = 15,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled0 = 64,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled1 = 65,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled2 = 66,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled3 = 67,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled4 = 68,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled5 = 69,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled6 = 70,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled7 = 71,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled8 = 72,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled9 = 73,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled10 = 74,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled11 = 75,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled12 = 76,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled13 = 77,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled14 = 78,
	/**
	 * Custom Virtual LED (VLED) port. Allows RGB LEDs to be activated with a user-defined color.
	 */
	brp_IoPort_CustomVled15 = 79,
	brp_IoPort_undefined = -1
} brp_IoPort;
static inline bool brp_IoPort_is_valid(int val) {
	switch (val) {
		case 0: /* GreenLed*/
		case 1: /* RedLed*/
		case 2: /* Beeper*/
		case 3: /* Relay*/
		case 4: /* Input0*/
		case 5: /* Input1*/
		case 6: /* BlueLed*/
		case 7: /* TamperAlarm*/
		case 8: /* Gpio0*/
		case 9: /* Gpio1*/
		case 10: /* Gpio2*/
		case 11: /* Gpio3*/
		case 12: /* Gpio4*/
		case 13: /* Gpio5*/
		case 14: /* Gpio6*/
		case 15: /* Gpio7*/
		case 64: /* CustomVled0*/
		case 65: /* CustomVled1*/
		case 66: /* CustomVled2*/
		case 67: /* CustomVled3*/
		case 68: /* CustomVled4*/
		case 69: /* CustomVled5*/
		case 70: /* CustomVled6*/
		case 71: /* CustomVled7*/
		case 72: /* CustomVled8*/
		case 73: /* CustomVled9*/
		case 74: /* CustomVled10*/
		case 75: /* CustomVled11*/
		case 76: /* CustomVled12*/
		case 77: /* CustomVled13*/
		case 78: /* CustomVled14*/
		case 79: /* CustomVled15*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * Enable the port ID stored in the Field _Param_.
	 */
	brp_RunSequenceCmd_CmdCode_EnablePort = 1,
	/**
	 * Disable the port ID of the Field _Param_.
	 */
	brp_RunSequenceCmd_CmdCode_DisablePort = 2,
	/**
	 * Jumps back to the corresponding _StartLoop_ a specified number of repetitions. The field _Param_ specifies the number of loops (0-255).
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop = 5,
	/**
	 * Wait exactly the amount of ms specified in the field _Param_ before going on.
	 */
	brp_RunSequenceCmd_CmdCode_WaitMs = 8,
	/**
	 * Wait exactly the amount of seconds specified in _Param_ before going on.
	 */
	brp_RunSequenceCmd_CmdCode_WaitSec = 9,
	/**
	 * End Of Script Marker. 
	 * 
	 * **Has to be present at the end of every script.**
	 */
	brp_RunSequenceCmd_CmdCode_EndOfSequence = 241,
	/**
	 * Starts a loop. Has to be followed by _RepeatLoopX_ or _RepeatLoop_.
	 */
	brp_RunSequenceCmd_CmdCode_StartLoop = 242,
	/**
	 * If execution of the sequence was aborted, jump to this label and run the following commands until EndOfSequence to restore a default LED state. The following commands must not contain _WaitXXX_ commands as it has to finish immediately.
	 */
	brp_RunSequenceCmd_CmdCode_OnStop = 243,
	/**
	 * This is a ShortCut for _EnablePort GreenLed_ (requires only one byte intead of 2).
	 */
	brp_RunSequenceCmd_CmdCode_EnablePortGreenLed = 16,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_EnablePortRedLed = 17,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_EnablePortBeeper = 18,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_EnablePortRelay = 19,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_EnablePortBlue = 22,
	/**
	 * This is a Shortcut for _DisablePort GreenLed_ (requires only one byte intead of 2).
	 */
	brp_RunSequenceCmd_CmdCode_DisablePortGreenLed = 32,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_DisablePortRedLed = 33,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_DisablePortBeeper = 34,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_DisablePortRelay = 35,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_DisablePortBlue = 38,
	/**
	 * This is a ShortCut for _EnablePort GreenLed_ , if GreenLed is enabled otherwise DisablePort GreenLed.
	 */
	brp_RunSequenceCmd_CmdCode_InvertPortGreenLed = 48,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_InvertPortRedLed = 49,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_InvertPortBeeper = 50,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_InvertPortRelay = 51,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_InvertPortBlue = 54,
	/**
	 * This is a Shortcut for _RepeatLoop 1_ which is actually a dummy operation, as the repeat block is was already executed once.
	 */
	brp_RunSequenceCmd_CmdCode_Repeat1Times = 81,
	/**
	 * This is a ShortCut for _RepeatLoop 2_. It repeats all operations since corresponding StartLoop exactly once. Thus in summary they were run twice (once the first time and once by repeating them).
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop2Times = 82,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop3Times = 83,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop4Times = 84,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop5Times = 85,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop6Times = 86,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop7Times = 87,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop8Times = 88,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop9Times = 89,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop10Times = 90,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop11Times = 91,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop12Times = 92,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop13Times = 93,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop14Times = 94,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_RepeatLoop15Times = 95,
	/**
	 * This is a Shortcut for _WaitMs 100_. It waits 100 ms before going on with the next operation.
	 */
	brp_RunSequenceCmd_CmdCode_Wait100Ms = 129,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait200Ms = 130,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait300Ms = 131,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait400Ms = 132,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait500Ms = 133,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait600Ms = 134,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait700Ms = 135,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait800Ms = 136,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait900Ms = 137,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait1000Ms = 138,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait1100Ms = 139,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait1200Ms = 140,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait1300Ms = 141,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait1400Ms = 142,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait1500Ms = 143,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait1600Ms = 144,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait1700Ms = 145,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait1800Ms = 146,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait1900Ms = 147,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait2000Ms = 148,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait2100Ms = 149,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait2200Ms = 150,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait2300Ms = 151,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait2400Ms = 152,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait2500Ms = 153,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait2600Ms = 154,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait2700Ms = 155,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait2800Ms = 156,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait2900Ms = 157,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait3000Ms = 158,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait3100Ms = 159,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait3200Ms = 160,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait3300Ms = 161,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait3400Ms = 162,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait3500Ms = 163,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait3600Ms = 164,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait3700Ms = 165,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait3800Ms = 166,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait3900Ms = 167,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait4000Ms = 168,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait4100Ms = 169,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait4200Ms = 170,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait4300Ms = 171,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait4400Ms = 172,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait4500Ms = 173,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait4600Ms = 174,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait4700Ms = 175,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait4800Ms = 176,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait4900Ms = 177,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait5000Ms = 178,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait5100Ms = 179,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait5200Ms = 180,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait5300Ms = 181,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait5400Ms = 182,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait5500Ms = 183,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait5600Ms = 184,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait5700Ms = 185,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait5800Ms = 186,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait5900Ms = 187,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait6000Ms = 188,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait6100Ms = 189,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait6200Ms = 190,
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode_Wait6300Ms = 191,
	brp_RunSequenceCmd_CmdCode_undefined = -1
} brp_RunSequenceCmd_CmdCode;
static inline bool brp_RunSequenceCmd_CmdCode_is_valid(int val) {
	switch (val) {
		case 1: /* EnablePort*/
		case 2: /* DisablePort*/
		case 5: /* RepeatLoop*/
		case 8: /* WaitMs*/
		case 9: /* WaitSec*/
		case 16: /* EnablePortGreenLed*/
		case 17: /* EnablePortRedLed*/
		case 18: /* EnablePortBeeper*/
		case 19: /* EnablePortRelay*/
		case 22: /* EnablePortBlue*/
		case 32: /* DisablePortGreenLed*/
		case 33: /* DisablePortRedLed*/
		case 34: /* DisablePortBeeper*/
		case 35: /* DisablePortRelay*/
		case 38: /* DisablePortBlue*/
		case 48: /* InvertPortGreenLed*/
		case 49: /* InvertPortRedLed*/
		case 50: /* InvertPortBeeper*/
		case 51: /* InvertPortRelay*/
		case 54: /* InvertPortBlue*/
		case 81: /* Repeat1Times*/
		case 82: /* RepeatLoop2Times*/
		case 83: /* RepeatLoop3Times*/
		case 84: /* RepeatLoop4Times*/
		case 85: /* RepeatLoop5Times*/
		case 86: /* RepeatLoop6Times*/
		case 87: /* RepeatLoop7Times*/
		case 88: /* RepeatLoop8Times*/
		case 89: /* RepeatLoop9Times*/
		case 90: /* RepeatLoop10Times*/
		case 91: /* RepeatLoop11Times*/
		case 92: /* RepeatLoop12Times*/
		case 93: /* RepeatLoop13Times*/
		case 94: /* RepeatLoop14Times*/
		case 95: /* RepeatLoop15Times*/
		case 129: /* Wait100Ms*/
		case 130: /* Wait200Ms*/
		case 131: /* Wait300Ms*/
		case 132: /* Wait400Ms*/
		case 133: /* Wait500Ms*/
		case 134: /* Wait600Ms*/
		case 135: /* Wait700Ms*/
		case 136: /* Wait800Ms*/
		case 137: /* Wait900Ms*/
		case 138: /* Wait1000Ms*/
		case 139: /* Wait1100Ms*/
		case 140: /* Wait1200Ms*/
		case 141: /* Wait1300Ms*/
		case 142: /* Wait1400Ms*/
		case 143: /* Wait1500Ms*/
		case 144: /* Wait1600Ms*/
		case 145: /* Wait1700Ms*/
		case 146: /* Wait1800Ms*/
		case 147: /* Wait1900Ms*/
		case 148: /* Wait2000Ms*/
		case 149: /* Wait2100Ms*/
		case 150: /* Wait2200Ms*/
		case 151: /* Wait2300Ms*/
		case 152: /* Wait2400Ms*/
		case 153: /* Wait2500Ms*/
		case 154: /* Wait2600Ms*/
		case 155: /* Wait2700Ms*/
		case 156: /* Wait2800Ms*/
		case 157: /* Wait2900Ms*/
		case 158: /* Wait3000Ms*/
		case 159: /* Wait3100Ms*/
		case 160: /* Wait3200Ms*/
		case 161: /* Wait3300Ms*/
		case 162: /* Wait3400Ms*/
		case 163: /* Wait3500Ms*/
		case 164: /* Wait3600Ms*/
		case 165: /* Wait3700Ms*/
		case 166: /* Wait3800Ms*/
		case 167: /* Wait3900Ms*/
		case 168: /* Wait4000Ms*/
		case 169: /* Wait4100Ms*/
		case 170: /* Wait4200Ms*/
		case 171: /* Wait4300Ms*/
		case 172: /* Wait4400Ms*/
		case 173: /* Wait4500Ms*/
		case 174: /* Wait4600Ms*/
		case 175: /* Wait4700Ms*/
		case 176: /* Wait4800Ms*/
		case 177: /* Wait4900Ms*/
		case 178: /* Wait5000Ms*/
		case 179: /* Wait5100Ms*/
		case 180: /* Wait5200Ms*/
		case 181: /* Wait5300Ms*/
		case 182: /* Wait5400Ms*/
		case 183: /* Wait5500Ms*/
		case 184: /* Wait5600Ms*/
		case 185: /* Wait5700Ms*/
		case 186: /* Wait5800Ms*/
		case 187: /* Wait5900Ms*/
		case 188: /* Wait6000Ms*/
		case 189: /* Wait6100Ms*/
		case 190: /* Wait6200Ms*/
		case 191: /* Wait6300Ms*/
		case 241: /* EndOfSequence*/
		case 242: /* StartLoop*/
		case 243: /* OnStop*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * 
	 */
	brp_RunSequenceCmd_CmdCode CmdCode;
	/**
	 * The number of repetitions of the code block between the matching _tLoop_ this _atLoop_ mand. If this number is 2 the interpreter jumps back to _tLoop_ exactly one time (which results in summary in to repetitions).
	 */
	unsigned RepeatCnt;
	/**
	 * This field represents a time (either in milliseconds or seconds). The UI-sequence interpreter will delay the amount of (milli-)seconds before going on.
	 */
	unsigned Param;
	/**
	 * I/O pins of the reader that can be controlled by the user.
	 */
	brp_IoPort SwitchIoPort;
} brp_RunSequenceCmd;
/**
 * In Autoread mode this values are specifing the states that shall be assumed for input ports before reading them the first time. If the first read results in a different state than specified here, an event will be fired.
 */
typedef enum {
	/**
	 * Do never fire the corresponding event (no matter what the corresponding input port's state is)
	 */
	brp_FireEventAtPowerup_Never = 0,
	/**
	 * Fire the corresponding "OnClearXxxx" event if the corresponding input port's state is cleared.
	 */
	brp_FireEventAtPowerup_IfClear = 1,
	/**
	 * Fire the corresponding "OnSetXxxx" event if the corresponding input port's state is set.
	 */
	brp_FireEventAtPowerup_IfSet = 2,
	/**
	 * Fire the corresponding event always (no matter what the corresponding input port's state is)
	 */
	brp_FireEventAtPowerup_Always = 3,
	brp_FireEventAtPowerup_undefined = -1
} brp_FireEventAtPowerup;
static inline bool brp_FireEventAtPowerup_is_valid(int val) {
	switch (val) {
		case 0: /* Never*/
		case 1: /* IfClear*/
		case 2: /* IfSet*/
		case 3: /* Always*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * See description above
	 */
	brp_CardType_Default = 0,
	/**
	 * MIFARE Classic (1k and 4k variants)
	 */
	brp_CardType_MifareClassic = 16,
	/**
	 * Generic ISO 14443-3 Type A without ISO 7816-4 support
	 */
	brp_CardType_Iso14443aGeneric = 17,
	/**
	 * ISO 14443-4 Type A compliant with ISO7816-4; this is a legacy value that is no longer returned since firmware version 2.14.00.
	 */
	brp_CardType_Iso14443aInterIndustryLegacy = 18,
	/**
	 * MIFARE Ultralight
	 */
	brp_CardType_MifareUltraLight = 19,
	/**
	 * MIFARE DESFire (2k, 4k, and 8k variants)
	 */
	brp_CardType_MifareDesfire = 20,
	/**
	 * Infineon my-d proximity (SLE55); this is a legacy value that is no longer returned since firmware version 2.14.00.
	 */
	brp_CardType_InfineonSle55 = 21,
	/**
	 * ISO 14443-4 Type A; this card type is capable of transferring application protocol data units (APDU) as defined in ISO 7816-4
	 */
	brp_CardType_Iso14443aIntIndustry = 22,
	/**
	 * MIFARE Plus L2 (2k and 4k variants)
	 */
	brp_CardType_MifarePlusL2 = 23,
	/**
	 * LEGIC advant ISO 14443 Type A
	 */
	brp_CardType_LEGICAdvantIso14443a = 24,
	/**
	 * MIFARE Plus L3
	 */
	brp_CardType_MifarePlusL3 = 25,
	/**
	 * LEGIC prime; this is a legacy value - it has been replaced by _LEGICPrime_.
	 */
	brp_CardType_LEGICPrimeLegacy = 32,
	/**
	 * LEGIC advant (ISO 14443 Type A/ISO 15693); this is a legacy value - it has been replaced by _LEGICAdvantIso14443a_ and _LEGICAdvantIso15693_.
	 */
	brp_CardType_LEGICAdvantLegacy = 33,
	/**
	 * ISO-15693-compliant label
	 */
	brp_CardType_Iso15693 = 48,
	/**
	 * LEGIC advant ISO 15693
	 */
	brp_CardType_LEGICAdvantIso15693 = 50,
	/**
	 * ISO 14443-3 Type B without ISO 7816-4 support
	 */
	brp_CardType_Iso14443bUnknown = 64,
	/**
	 * ISO 14443-4 Type B with ISO 7816-4 support
	 */
	brp_CardType_Iso14443bIntIndustry = 65,
	/**
	 * iCLASS via standard-compliant ISO 14443 Type B protocol (Level 3 compatible)
	 */
	brp_CardType_IClassIso14B = 66,
	/**
	 * iCLASS via proprietary ISO 14443 Type B protocol derivate (Level 2 compatible)
	 */
	brp_CardType_IClassIso14B2 = 80,
	/**
	 * iCLASS via ISO 15693
	 */
	brp_CardType_IClass = 96,
	/**
	 * FeliCa
	 */
	brp_CardType_Felica = 112,
	/**
	 * EM 4205/EM 4305
	 */
	brp_CardType_EM4205 = 128,
	/**
	 * EM 4100/EM 4102
	 */
	brp_CardType_EM4100 = 129,
	/**
	 * EM 4450
	 */
	brp_CardType_EM4450 = 131,
	/**
	 * Farpointe Pyramid
	 */
	brp_CardType_Pyramid = 132,
	/**
	 * HID Prox32
	 */
	brp_CardType_HidProx32 = 133,
	/**
	 * Keri
	 */
	brp_CardType_Keri = 134,
	/**
	 * QuadraKey
	 */
	brp_CardType_Quadrakey = 135,
	/**
	 * HID Indala ASP
	 */
	brp_CardType_HidIndala = 136,
	/**
	 * AWID
	 */
	brp_CardType_HidAwid = 137,
	/**
	 * HID Proximity
	 */
	brp_CardType_HidProx = 138,
	/**
	 * ioProx
	 */
	brp_CardType_HidIoprox = 139,
	/**
	 * HITAG 1 or S
	 */
	brp_CardType_Hitag1S = 140,
	/**
	 * HITAG 2 Manchester
	 */
	brp_CardType_Hitag2M = 141,
	/**
	 * HITAG 2 Biphase
	 */
	brp_CardType_Hitag2B = 142,
	/**
	 * Low-level card type/programmable decoder
	 */
	brp_CardType_TTF = 143,
	/**
	 * ST SRIX
	 */
	brp_CardType_STSRIX = 144,
	/**
	 * SecuraKey
	 */
	brp_CardType_SecuraKey = 160,
	/**
	 * G-Prox
	 */
	brp_CardType_GProx = 161,
	/**
	 * HID Indala ASP+
	 */
	brp_CardType_HidIndalaSecure = 162,
	/**
	 * Cotag
	 */
	brp_CardType_Cotag = 163,
	/**
	 * IDTECK
	 */
	brp_CardType_Idteck = 164,
	/**
	 * Bluetooth MCE; Mobile Card Emulation over Bluetooth
	 */
	brp_CardType_BluetoothMce = 176,
	/**
	 * LEGIC prime
	 */
	brp_CardType_LEGICPrime = 192,
	/**
	 * Abstract card type for reading SIO Elements
	 */
	brp_CardType_HidSio = 224,
	/**
	 * Fido 2.1
	 */
	brp_CardType_Fido = 228,
	/**
	 * FIPS201 Personal Identity Verification (PIV)
	 */
	brp_CardType_Piv = 229,
	/**
	 * Abstract card type for reading MIFARE DESFire cards using a special VHL implementation for LEGIC readers
	 */
	brp_CardType_DesfireForLegic = 230,
	/**
	 * LEGIC neon file
	 */
	brp_CardType_LEGICNeon = 231,
	brp_CardType_undefined = -1
} brp_CardType;
static inline bool brp_CardType_is_valid(int val) {
	switch (val) {
		case 0: /* Default*/
		case 16: /* MifareClassic*/
		case 17: /* Iso14443aGeneric*/
		case 18: /* Iso14443aInterIndustryLegacy*/
		case 19: /* MifareUltraLight*/
		case 20: /* MifareDesfire*/
		case 21: /* InfineonSle55*/
		case 22: /* Iso14443aIntIndustry*/
		case 23: /* MifarePlusL2*/
		case 24: /* LEGICAdvantIso14443a*/
		case 25: /* MifarePlusL3*/
		case 32: /* LEGICPrimeLegacy*/
		case 33: /* LEGICAdvantLegacy*/
		case 48: /* Iso15693*/
		case 50: /* LEGICAdvantIso15693*/
		case 64: /* Iso14443bUnknown*/
		case 65: /* Iso14443bIntIndustry*/
		case 66: /* IClassIso14B*/
		case 80: /* IClassIso14B2*/
		case 96: /* IClass*/
		case 112: /* Felica*/
		case 128: /* EM4205*/
		case 129: /* EM4100*/
		case 131: /* EM4450*/
		case 132: /* Pyramid*/
		case 133: /* HidProx32*/
		case 134: /* Keri*/
		case 135: /* Quadrakey*/
		case 136: /* HidIndala*/
		case 137: /* HidAwid*/
		case 138: /* HidProx*/
		case 139: /* HidIoprox*/
		case 140: /* Hitag1S*/
		case 141: /* Hitag2M*/
		case 142: /* Hitag2B*/
		case 143: /* TTF*/
		case 144: /* STSRIX*/
		case 160: /* SecuraKey*/
		case 161: /* GProx*/
		case 162: /* HidIndalaSecure*/
		case 163: /* Cotag*/
		case 164: /* Idteck*/
		case 176: /* BluetoothMce*/
		case 192: /* LEGICPrime*/
		case 224: /* HidSio*/
		case 228: /* Fido*/
		case 229: /* Piv*/
		case 230: /* DesfireForLegic*/
		case 231: /* LEGICNeon*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * 
	 */
	bool LEGICPrime;
	/**
	 * 
	 */
	bool BluetoothMce;
	/**
	 * Scans for the following 125kHz cards: SecuraKey, G-Prox, Indala ASP+, Cotag, Idteck. To scan only for a part of this list, set the configuration value ScanCardTypesPart2 accordingly. To scan for other 125kHz card types, set the _Khz125Part1_ flag.
	 */
	bool Khz125Part2;
	/**
	 * 
	 */
	bool Srix;
	/**
	 * Scans for the following 125kHz cards: EM4205, EM4305, EM4100, EM4102, EM4450, Farpointe Pyramid, HID prox, HID ioProx, HID Prox32, Keri, Quadrakey, Indala, AWID, HITAG 1 and S, HITAG 2, TTF (Tag talks first). To scan only for a part of this list, set the configuration value ScanCardTypesPart1 accordingly. To scan for other 125kHz card types, set the _Khz125Part2_ flag.
	 */
	bool Khz125Part1;
	/**
	 * 
	 */
	bool Felica;
	/**
	 * Scans for iCLASS and iCLASS SR cards. 
	 * 
	 * **This flag does not include iCLASS SE or iCLASS Seos. To scan for these card types, set the _Iso14443A_ flag.**
	 */
	bool IClass;
	/**
	 * Can be used instead of _iCLASS_ to increase scanning speed. (Its transport layer protocol is based on the faster ISO 14443 Type B protocol instead of the ISO-15693-like protocol of _iCLASS_). 
	 * 
	 * **Not all iCLASS cards support ISO 14443 Type B. Thus, we recommend you use the _iCLASS_ flag for maximum compatibility and the _IClassIso14B_ flag for maximum speed. When in doubt, please check the specification of the cards used in your project.**
	 */
	bool IClassIso14B;
	/**
	 * 
	 */
	bool Iso14443B;
	/**
	 * Scans for ISO-15693-compatible cards, e.g. EM4033, EM4035, NXP ICODE, or LEGIC advant ISO 15693.
	 */
	bool Iso15693;
	/**
	 * Scans for ISO 14443 Type A compatible cards, e.g. MIFARE Classic, MIFARE Plus, MIFARE DESFire, NXP SmartMX, or Legic advant ISO 14443.
	 */
	bool Iso14443A;
} brp_CardFamilies;
/**
 * Communication settings that define if data is to be MAC'ed or encrypted before it's transmitted to the host system.
 */
typedef enum {
	/**
	 * 
	 */
	brp_DesfireFileDescription_FileCommunicationSecurity_Plain = 0,
	/**
	 * 
	 */
	brp_DesfireFileDescription_FileCommunicationSecurity_Mac = 1,
	/**
	 * 
	 */
	brp_DesfireFileDescription_FileCommunicationSecurity_Encrypted = 3,
	brp_DesfireFileDescription_FileCommunicationSecurity_undefined = -1
} brp_DesfireFileDescription_FileCommunicationSecurity;
static inline bool brp_DesfireFileDescription_FileCommunicationSecurity_is_valid(int val) {
	switch (val) {
		case 0: /* Plain*/
		case 1: /* Mac*/
		case 3: /* Encrypted*/
			return true;
		default:
			return false;
	}
}
/**
 * Type of file to read 
 * 
 * **Only Standard and Backup files are supported. There's no support for Cyclic, Record, or Value files.**
 */
typedef enum {
	/**
	 * 
	 */
	brp_DesfireFileDescription_FileType_Standard = 0,
	/**
	 * Commit will be performed automatically.
	 */
	brp_DesfireFileDescription_FileType_Backup = 1,
	/**
	 * Commit will be performed when writing to address 0xFFFF.
	 */
	brp_DesfireFileDescription_FileType_BackupManualCommit = 2,
	brp_DesfireFileDescription_FileType_undefined = -1
} brp_DesfireFileDescription_FileType;
static inline bool brp_DesfireFileDescription_FileType_is_valid(int val) {
	switch (val) {
		case 0: /* Standard*/
		case 1: /* Backup*/
		case 2: /* BackupManualCommit*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * The DESFire file number to access
	 */
	unsigned FileNo;
	/**
	 * Communication settings that define if data is to be MAC'ed or encrypted before it's transmitted to the host system.
	 */
	brp_DesfireFileDescription_FileCommunicationSecurity FileCommunicationSecurity;
	/**
	 * Type of file to read 
	 * 
	 * **Only Standard and Backup files are supported. There's no support for Cyclic, Record, or Value files.**
	 */
	brp_DesfireFileDescription_FileType FileType;
	/**
	 * _ReadKeyNo_ , i.e. the index of the read key within the DESFire application key table 
	 * 
	 * **The value 14 allows unencrypted access.**
	 */
	unsigned ReadKeyNo;
	/**
	 * _WriteKeyNo_ , i.e. the index of the write key within the DESFire application key table 
	 * 
	 * **The value 14 allows unencrypted access.**
	 */
	unsigned WriteKeyNo;
	/**
	 * Number of the first byte in the DESFire file to map into the VHL file.
	 */
	unsigned Offset;
	/**
	 * Length of byte sequence within the DESFire file to map into the VHL file.
	 */
	unsigned Length;
	/**
	 * Index of the read key on the reader 
	 * 
	 *   1. 0x00-0x7F refer to an index in a SAM (key version has to be 0). 
	 *   2. 0x80-0xBF refer to an index in Crypto Key. 
	 *   3. 0xC0-0xCB refer to an index in VhlCfg/File/DesfireKeyList.
	 */
	unsigned ReadKeyIdx;
	/**
	 * Index of the write key on the reader  
	 * If omitted and _WriteKeyNo_ is equal to _ReadKeyNo_ , it defaults to _ReadKeyIdx_. Otherwise it defaults to _ReadKeyIdx_ \+ 1. 
	 * 
	 *   1. 0x00-0x7F refer to an index in a SAM (key version has to be 0). 
	 *   2. 0x80-0xBF refer to an index in Crypto Key. 
	 *   3. 0xC0-0xCB refers to an index in VhlCfg/File/DesfireKeyList.
	 */
	unsigned WriteKeyIdx;
	/**
	 * **Only needed to run VHL.Format .**
	 * 
	 * This byte is composed of a high nibble (_ReadWriteKeyNo_) and a low nibble (_ChangeKeyNo_). It corresponds to the low byte of the access rights (see DESFire spec 3.5; chapter 8.3) of the DESFire file. The high byte is composed implicitly of _ReadKeyNo_ and _WriteKeyNo_.
	 */
	unsigned AccessRightsLowByte;
	/**
	 * **Only needed to run VHL.Format .**
	 * 
	 * Index of the key on the reader that is used to change a key when running _VHL.Format_. If ChangeKeyNo (see _AccessRightsLowByte_) is equal to _WriteKeyNo_ , this value defaults to _WriteKeyIdx_. Otherwise, it defaults to _WriteKeyIdx_ \+ 1. 
	 * 
	 *   1. 0x00-0x7F refer to an index in a SAM (key version has to be 0). 
	 *   2. 0x80-0xBF refer to an index in Crypto Key. 
	 *   3. 0xC0-0xCB refer to an index in VhlCfg/File/DesfireKeyList.
	 */
	unsigned ChangeKeyIdx;
	/**
	 * **Only needed to run VHL.Format .**
	 * 
	 * The size of the DESfire file. It's usually _Offset_ \+ _Len_.
	 */
	unsigned FileSize;
	/**
	 * **Only needed to run VHL.Format .**
	 * 
	 * ISO file identifier (ISO FID). If the card already contains a DESFire file with the same ISO FID, the existing file will be replaced. If this value is not specified (or 0x3F00), no ISO FID will be used.
	 */
	unsigned IsoFid;
} brp_DesfireFileDescription;
/**
 * Specifies the authentication level the BEC/BEC2/BF3 file or ConfigCard has to fulfill to be accepted.
 */
typedef enum {
	/**
	 * Default settings (Actual behavior is usage-dependent).
	 */
	brp_AuthReqUpload_Default = 0,
	/**
	 * Accept any kind of BEC/BEC2/BF3 files or ConfigCards, even unencrypted ones.
	 */
	brp_AuthReqUpload_None_ = 1,
	/**
	 * Accept only BEC/BEC2/BF3 files or ConfigCards that are encrypted with a matching customer key. Especially deny unencrypted files/ConfigCards.
	 */
	brp_AuthReqUpload_CustomerKey = 2,
	/**
	 * The customer key _and_ the Config Security Code have to match for this BEC/BEC2/BF3 file or ConfigCard to be accepted.
	 */
	brp_AuthReqUpload_ConfigSecurityCode = 3,
	/**
	 * The customer key _and_ the Config Security Code have to match for this BEC/BEC2/BF3 file or ConfigCard to be accepted. Furthermore, the version stored in the file/ConfigCard header has to be greater than or equal to the RFID interface component version.
	 */
	brp_AuthReqUpload_Version = 4,
	/**
	 * The customer key _and_ the Config Security Code have to match for this BEC/BEC2/BF3 file or ConfigCard to be accepted. Furthermore, the version stored in the file/ConfigCard header has to be greater than the RFID interface component version.
	 */
	brp_AuthReqUpload_GreaterVersion = 5,
	brp_AuthReqUpload_undefined = -1
} brp_AuthReqUpload;
static inline bool brp_AuthReqUpload_is_valid(int val) {
	switch (val) {
		case 0: /* Default*/
		case 1: /* None_*/
		case 2: /* CustomerKey*/
		case 3: /* ConfigSecurityCode*/
		case 4: /* Version*/
		case 5: /* GreaterVersion*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * Do not run Autoread at all.
	 */
	brp_AutoReadMode_Disabled = 0,
	/**
	 * The reader will boot in Autoread mode and scan for cards, no matter if its configuration contains an Autoread RFID interface component or not. 
	 * 
	 * If there is an Autoread RFID interface component, the reader will check if a card is valid and buffer its card identification, so you can retrieve it using AR.GetMessage. Then, the reader will continue scanning for other cards. If another card is detected before the last card identification has been retrieved by the host, the last card identifications will be queued in a last-in-first-out queue. 
	 * 
	 * If there is no Autoread RFID interface component, project cards won't be read; however, the reader will still do the following:
	 * 
	 *   * Scan and accept ConfigCards. This means the reader can be reconfigured even if the connection to the host is interrupted.
	 *   * Fire Baltech Script events
	 */
	brp_AutoReadMode_Enabled = 1,
	/**
	 * Same as _Enabled_ ; however, the reader will stop Autoread mode as soon as it has detected (and read) a card. You can now interact with the card using VHL commands. When you're done, reenable Autoread by running AR.SetMode again.
	 */
	brp_AutoReadMode_EnableOnce = 2,
	/**
	 * The reader will boot in Autoread mode only if its configuration contains at least 1 Autoread RFID interface component, i.e. if the configuration value Autoread/Rule[0]/Template is defined. Then the behavior is the same as _Enabled_.
	 */
	brp_AutoReadMode_EnableIfDefinedRules = 255,
	brp_AutoReadMode_undefined = -1
} brp_AutoReadMode;
static inline bool brp_AutoReadMode_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 1: /* Enabled*/
		case 2: /* EnableOnce*/
		case 255: /* EnableIfDefinedRules*/
			return true;
		default:
			return false;
	}
}
/**
 * Every Feature in this list can be disabled by not setting the corresponding bit.
 */
typedef struct {
	/**
	 * Has to be cleared to deny access to commands that allow host-to-host communication
	 */
	bool HostToHostAccess;
	/**
	 * Has to be cleared to deny control autoread task
	 */
	bool AutoreadAccess;
	/**
	 * Has to be cleared to deny allow access to the encryption unit
	 */
	bool CryptoAccess;
	/**
	 * Has to be cleared to deny allow to upload firmware
	 */
	bool Bf2Upload;
	/**
	 * Has to be cleared to deny allow access to the extended reader partition
	 */
	bool ExtendedAccess;
	/**
	 * Has to be cleared to deny write access to flash file system
	 */
	bool FlashFileSystemWrite;
	/**
	 * Has to be cleared to deny read access to flash file system
	 */
	bool FlashFileSystemRead;
	/**
	 * Has to be cleared to deny write access to RTC
	 */
	bool RtcWrite;
	/**
	 * Has to be cleared to deny running VHL APDU Exchange
	 */
	bool VhlExchangeapdu;
	/**
	 * Has to be cleared to deny formattings cards via VHL
	 */
	bool VhlFormat;
	/**
	 * Has to be cleared to deny writing cards via VHL
	 */
	bool VhlWrite;
	/**
	 * Has to be cleared to deny reading cards via VHL
	 */
	bool VhlRead;
	/**
	 * Has to be cleared to deny detection of cards via VHL
	 */
	bool VhlSelect;
	/**
	 * Has to be cleared to deny access to SAM over 7816-3 commands ( Iso78 command group)
	 */
	bool ExtSamAccess;
	/**
	 * Has to be cleared to deny allow to access HF via low level commands
	 */
	bool HfLowlevelAccess;
	/**
	 * Has to be cleared to deny access to keypad/lcd
	 */
	bool GuiAccess;
	/**
	 * Has to be cleared to deny write access to io ports
	 */
	bool IoPortWrite;
	/**
	 * Has to be cleared to deny read access to io ports
	 */
	bool IoPortRead;
	/**
	 * Has to be cleared to deny reset configuration keys/while configuration.
	 */
	bool ConfigReset;
	/**
	 * Has to be cleared to deny write access to configuration keys/values.
	 */
	bool ConfigWrite;
	/**
	 * Has to be cleared to deny read access to configuration keys/values
	 */
	bool ConfigRead;
	/**
	 * Has to be cleared to deny allow reboot/powerdown of system
	 */
	bool SysReset;
	/**
	 * Has to be cleared to deny set ac 2
	 */
	bool SetAccessConditionMask2;
	/**
	 * Has to be cleared to deny set ac 1
	 */
	bool SetAccessConditionMask1;
	/**
	 * Has to be cleared to deny set ac 0
	 */
	bool SetAccessConditionMask0;
	/**
	 * Has to be cleared to deny set security key 3
	 */
	bool SetKey3;
	/**
	 * Has to be cleared to deny set security key 2
	 */
	bool SetKey2;
	/**
	 * Has to be cleared to deny set security key 1
	 */
	bool SetKey1;
	/**
	 * Has to be cleared to deny resetting system to factory settings
	 */
	bool FactoryReset;
} brp_HostSecurityAccessConditionBits;
/**
 * Specifies a minimum of security requirements, when working in this security level
 */
typedef struct {
	/**
	 * Initialvector of CBC encryption is not reset between commands. This prevents replay attacks during a single session but makes the connection more sensible to communication errors.
	 */
	bool RequireContinuousIv;
	/**
	 * Commands are transferred encrypted. No man in the middle can read the data
	 */
	bool RequireEncrypted;
	/**
	 * A Cryptographic Signature is attached to every command. No man in the middle can inject its own commands
	 */
	bool RequireMac;
	/**
	 * 3-pass authentication and sessionkey generation
	 */
	bool RequireSessionKey;
} brp_HostSecurityAuthenticationMode;
/**
 * 
 */
typedef struct {
	/**
	 * BCD number that specifies a firmware ID
	 */
	unsigned FirmwareID;
	/**
	 * Binary that specifies the major number of the smallest blocked fw version
	 */
	unsigned SmallestBlockedFwVersionMajor;
	/**
	 * Binary that specifies the minor number of the smallest blocked fw version
	 */
	unsigned SmallestBlockedFwVersionMinor;
	/**
	 * Binary that specifies the build number of the smallest blocked fw version
	 */
	unsigned SmallestBlockedFwVersionBuild;
	/**
	 * Binary that specifies the major number of the greatest non-blocked fw version
	 */
	unsigned GreatestBlockedFwVersionMajor;
	/**
	 * Binary that specifies the minor number of the greatest non-blocked fw version
	 */
	unsigned GreatestBlockedFwVersionMinor;
	/**
	 * Binary that specifies the build number of the greatest non-blocked fw version
	 */
	unsigned GreatestBlockedFwVersionBuild;
} brp_FirmwareVersion;
/**
 * This byte is required to enable additional fields for the characterization of the desired LED behavior.
 */
typedef struct {
	/**
	 * If _true_ , this virtual LED definition contains an individual transition time, which is applied to this VLED only. If _false_ , the default transition time will be applied.
	 */
	bool ContainsTransitionTime;
	/**
	 * If _true_ , this virtual LED definition describes a pulse signal that continuously fades between 2 RGB colors. It contains the second RGB color value in an additional field.
	 */
	bool IsPulse;
	/**
	 * If _true_ , this virtual LED definition contains the field _PhysicalLedSelection_.  
	 * If _false_ , the firmware uses the default value _All_.
	 */
	bool ContainsPhysicalLedSelection;
} brp_VirtualLedDefinition_Mode;
/**
 * This field defines which physical LEDs are to be activated when the corresponding VLED port is enabled.
 */
typedef enum {
	/**
	 * Activates only the LEDs on the right side.
	 */
	brp_VirtualLedDefinition_PhysicalLedSelection_Right = 1,
	/**
	 * Activates only the LEDs on the left side.
	 */
	brp_VirtualLedDefinition_PhysicalLedSelection_Left = 2,
	/**
	 * Activates all LEDs.
	 */
	brp_VirtualLedDefinition_PhysicalLedSelection_All = 3,
	brp_VirtualLedDefinition_PhysicalLedSelection_undefined = -1
} brp_VirtualLedDefinition_PhysicalLedSelection;
static inline bool brp_VirtualLedDefinition_PhysicalLedSelection_is_valid(int val) {
	switch (val) {
		case 1: /* Right*/
		case 2: /* Left*/
		case 3: /* All*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * This byte is required to enable additional fields for the characterization of the desired LED behavior.
	 */
	brp_VirtualLedDefinition_Mode Mode;
	/**
	 * This is the color of the VLED port in the RGB color space (0x00RRGGBB). In case of a pulse signal, this is the first color value.
	 */
	unsigned RgbColor;
	/**
	 * This field defines which physical LEDs are to be activated when the corresponding VLED port is enabled.
	 */
	brp_VirtualLedDefinition_PhysicalLedSelection PhysicalLedSelection;
	/**
	 * This field is only available in case of a pulse signal. It defines the second RGB color of the pulse.
	 */
	unsigned RgbColor2;
	/**
	 * This field defines the transition time which is applied whenever this virtual LED is enabled. This value overrides the default transition time.
	 */
	unsigned TransitionTime;
} brp_VirtualLedDefinition;
/**
 * License bit mask
 */
typedef struct {
	/**
	 * BLE license 
	 * 
	 * Reader is licensed to operate with Bluetooth. 
	 * 
	 * **This license is only applicable to readers supporting Bluetooth.**
	 */
	bool Ble;
	/**
	 * BLE license required 
	 * 
	 * Reader requires a valid BLE license to operate with Bluetooth. If not set, Bluetooth can be used without a BLE license, provided that the reader hardware supports Bluetooth.
	 */
	bool BleLicRequired;
	/**
	 * SE [Prox license](https://docs.baltech.de/project-setup/get-prox-license-for-hid-prox-indala-keri.html#what-license-types-are-available): 
	 * 
	 * Reader is licensed to read HID Prox, Indala, and Keri project cards if an _HID SE processor is inserted_  
	 * (also known as "iClass SAM"). 
	 * 
	 * **This license is only applicable to 125 kHz readers.**
	 */
	bool HidOnlyForSE;
	/**
	 * Standard [Prox license](https://docs.baltech.de/project-setup/get-prox-license-for-hid-prox-indala-keri.html#what-license-types-are-available): 
	 * 
	 * Reader is licensed to read HID Prox, Indala, and Keri project cards. 
	 * 
	 * **This license is only applicable to 125 kHz readers.**
	 */
	bool Hid;
} brp_LicenseBitMask;
/**
 * 
 */
typedef struct {
	/**
	 * Specifies the UUID (16 or 128 bits) of the BLE characteristic
	 */
	brp_buf CharacteristicUUID;
	/**
	 * Length of **CharacteristicUUID** (in bytes).
	 */
	size_t CharacteristicUUID_len;
	/**
	 * 
	 */
	bool SupportsIndicate;
	/**
	 * 
	 */
	bool SupportsNotify;
	/**
	 * 
	 */
	bool SupportsWrite;
	/**
	 * 
	 */
	bool SupportsWriteNoResponse;
	/**
	 * 
	 */
	bool SupportsRead;
	/**
	 * 
	 */
	bool VariableSize;
	/**
	 * Specifies the size of the characteristic in bytes. If _VariableSize_ in _Flags_ parameter is set, this is not the exact size, but the maximum size of the attribute. 
	 * 
	 * **The maximum supported size of a single characteristic is 512 bytes. The total size of all characteristics may not exceed 1536 bytes.**
	 */
	unsigned Size;
} brp_BlePeriph_DefineService_Characteristics_Entry;
/**
 * Remote device address type
 */
typedef enum {
	/**
	 * Public address
	 */
	brp_BlePeriph_IsConnected_AddressType_Public = 0,
	/**
	 * Random static address
	 */
	brp_BlePeriph_IsConnected_AddressType_RandomStatic = 1,
	/**
	 * Resolvable private random address
	 */
	brp_BlePeriph_IsConnected_AddressType_RandomResolvable = 2,
	/**
	 * Non-resolvable private random address
	 */
	brp_BlePeriph_IsConnected_AddressType_RandomNonResolvable = 3,
	brp_BlePeriph_IsConnected_AddressType_undefined = -1
} brp_BlePeriph_IsConnected_AddressType;
static inline bool brp_BlePeriph_IsConnected_AddressType_is_valid(int val) {
	switch (val) {
		case 0: /* Public*/
		case 1: /* RandomStatic*/
		case 2: /* RandomResolvable*/
		case 3: /* RandomNonResolvable*/
			return true;
		default:
			return false;
	}
}
/**
 * Type of encryption.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Desfire_ExecCommand_CryptoMode_Plain = 0,
	/**
	 * 
	 */
	brp_Desfire_ExecCommand_CryptoMode_MAC = 1,
	/**
	 * 
	 */
	brp_Desfire_ExecCommand_CryptoMode_Encrypted = 3,
	brp_Desfire_ExecCommand_CryptoMode_undefined = -1
} brp_Desfire_ExecCommand_CryptoMode;
static inline bool brp_Desfire_ExecCommand_CryptoMode_is_valid(int val) {
	switch (val) {
		case 0: /* Plain*/
		case 1: /* MAC*/
		case 3: /* Encrypted*/
			return true;
		default:
			return false;
	}
}
/**
 * Sets the secure messaging mode.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Desfire_Authenticate_SecureMessaging_Native = 1,
	/**
	 * 
	 */
	brp_Desfire_Authenticate_SecureMessaging_EV1 = 0,
	/**
	 * 
	 */
	brp_Desfire_Authenticate_SecureMessaging_EV2 = 2,
	brp_Desfire_Authenticate_SecureMessaging_undefined = -1
} brp_Desfire_Authenticate_SecureMessaging;
static inline bool brp_Desfire_Authenticate_SecureMessaging_is_valid(int val) {
	switch (val) {
		case 0: /* EV1*/
		case 1: /* Native*/
		case 2: /* EV2*/
			return true;
		default:
			return false;
	}
}
/**
 * Specifies diversification algorithm.
 */
typedef enum {
	/**
	 * No diversification.
	 */
	brp_Desfire_Authenticate_KeyDivMode_NoDiv = 0,
	/**
	 * SAM AV1 mode (3DES: 1 encryption round).
	 */
	brp_Desfire_Authenticate_KeyDivMode_SamAV1OneRound = 1,
	/**
	 * SAM AV1 compatible mode (AES, 3K3DES, 3DES: 2 encryption rounds).
	 */
	brp_Desfire_Authenticate_KeyDivMode_SamAV1TwoRounds = 2,
	/**
	 * SAM AV2 mode (AES according NXP: AN 10922).
	 */
	brp_Desfire_Authenticate_KeyDivMode_SamAV2 = 3,
	brp_Desfire_Authenticate_KeyDivMode_undefined = -1
} brp_Desfire_Authenticate_KeyDivMode;
static inline bool brp_Desfire_Authenticate_KeyDivMode_is_valid(int val) {
	switch (val) {
		case 0: /* NoDiv*/
		case 1: /* SamAV1OneRound*/
		case 2: /* SamAV1TwoRounds*/
		case 3: /* SamAV2*/
			return true;
		default:
			return false;
	}
}
/**
 * Sets the secure messaging mode.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Desfire_AuthExtKey_SecureMessaging_Native = 1,
	/**
	 * 
	 */
	brp_Desfire_AuthExtKey_SecureMessaging_EV1 = 0,
	/**
	 * 
	 */
	brp_Desfire_AuthExtKey_SecureMessaging_EV2 = 2,
	brp_Desfire_AuthExtKey_SecureMessaging_undefined = -1
} brp_Desfire_AuthExtKey_SecureMessaging;
static inline bool brp_Desfire_AuthExtKey_SecureMessaging_is_valid(int val) {
	switch (val) {
		case 0: /* EV1*/
		case 1: /* Native*/
		case 2: /* EV2*/
			return true;
		default:
			return false;
	}
}
/**
 * Sets the encryption algorithm.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Desfire_AuthExtKey_CryptoMode_DES = 1,
	/**
	 * 
	 */
	brp_Desfire_AuthExtKey_CryptoMode_TripleDES = 2,
	/**
	 * 
	 */
	brp_Desfire_AuthExtKey_CryptoMode_ThreeKeyTripleDES = 3,
	/**
	 * 
	 */
	brp_Desfire_AuthExtKey_CryptoMode_AES = 4,
	brp_Desfire_AuthExtKey_CryptoMode_undefined = -1
} brp_Desfire_AuthExtKey_CryptoMode;
static inline bool brp_Desfire_AuthExtKey_CryptoMode_is_valid(int val) {
	switch (val) {
		case 1: /* DES*/
		case 2: /* TripleDES*/
		case 3: /* ThreeKeyTripleDES*/
		case 4: /* AES*/
			return true;
		default:
			return false;
	}
}
/**
 * Communication settings linked to the file.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Desfire_ReadData_Mode_Plain = 0,
	/**
	 * 
	 */
	brp_Desfire_ReadData_Mode_MAC = 1,
	/**
	 * 
	 */
	brp_Desfire_ReadData_Mode_Encrypted = 3,
	brp_Desfire_ReadData_Mode_undefined = -1
} brp_Desfire_ReadData_Mode;
static inline bool brp_Desfire_ReadData_Mode_is_valid(int val) {
	switch (val) {
		case 0: /* Plain*/
		case 1: /* MAC*/
		case 3: /* Encrypted*/
			return true;
		default:
			return false;
	}
}
/**
 * Communication settings linked to the file.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Desfire_WriteData_Mode_Plain = 0,
	/**
	 * 
	 */
	brp_Desfire_WriteData_Mode_MAC = 1,
	/**
	 * 
	 */
	brp_Desfire_WriteData_Mode_Encrypted = 3,
	brp_Desfire_WriteData_Mode_undefined = -1
} brp_Desfire_WriteData_Mode;
static inline bool brp_Desfire_WriteData_Mode_is_valid(int val) {
	switch (val) {
		case 0: /* Plain*/
		case 1: /* MAC*/
		case 3: /* Encrypted*/
			return true;
		default:
			return false;
	}
}
/**
 * These bits must only be set if the card's Master Key is changed. They specify the type of the new card's Master Key.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Desfire_ChangeExtKey_MasterKeyType_DESorTripleDES = 0,
	/**
	 * 
	 */
	brp_Desfire_ChangeExtKey_MasterKeyType_ThreeKeyTripleDES = 1,
	/**
	 * 
	 */
	brp_Desfire_ChangeExtKey_MasterKeyType_AES = 2,
	brp_Desfire_ChangeExtKey_MasterKeyType_undefined = -1
} brp_Desfire_ChangeExtKey_MasterKeyType;
static inline bool brp_Desfire_ChangeExtKey_MasterKeyType_is_valid(int val) {
	switch (val) {
		case 0: /* DESorTripleDES*/
		case 1: /* ThreeKeyTripleDES*/
		case 2: /* AES*/
			return true;
		default:
			return false;
	}
}
/**
 * Specifies diversification algorithm.
 */
typedef enum {
	/**
	 * SAM AV1 mode for all key types / one encryption round for DES keys.
	 */
	brp_Desfire_ChangeKey_NewKeyDivMode_SamAv1OneRound = 0,
	/**
	 * SAM AV1 mode only for DES keys - two encryption rounds.
	 */
	brp_Desfire_ChangeKey_NewKeyDivMode_SamAv1TwoRounds = 1,
	/**
	 * SAM AV2 mode.
	 */
	brp_Desfire_ChangeKey_NewKeyDivMode_SamAv2 = 2,
	brp_Desfire_ChangeKey_NewKeyDivMode_undefined = -1
} brp_Desfire_ChangeKey_NewKeyDivMode;
static inline bool brp_Desfire_ChangeKey_NewKeyDivMode_is_valid(int val) {
	switch (val) {
		case 0: /* SamAv1OneRound*/
		case 1: /* SamAv1TwoRounds*/
		case 2: /* SamAv2*/
			return true;
		default:
			return false;
	}
}
/**
 * Specifies diversification algorithm.
 */
typedef enum {
	/**
	 * SAM AV1 mode for all key types / one encryption round for DES keys.
	 */
	brp_Desfire_ChangeKey_CurKeyDivMode_SamAv1OneRound = 0,
	/**
	 * SAM AV1 mode only for DES keys - two encryption rounds).
	 */
	brp_Desfire_ChangeKey_CurKeyDivMode_SamAv1TwoRounds = 1,
	/**
	 * SAM AV2 mode.
	 */
	brp_Desfire_ChangeKey_CurKeyDivMode_SamAv2 = 2,
	brp_Desfire_ChangeKey_CurKeyDivMode_undefined = -1
} brp_Desfire_ChangeKey_CurKeyDivMode;
static inline bool brp_Desfire_ChangeKey_CurKeyDivMode_is_valid(int val) {
	switch (val) {
		case 0: /* SamAv1OneRound*/
		case 1: /* SamAv1TwoRounds*/
		case 2: /* SamAv2*/
			return true;
		default:
			return false;
	}
}
/**
 * Defines 14443-4 communication mode to DESFire card.
 */
typedef enum {
	/**
	 * DESFire native mode (default communication mode).
	 */
	brp_Desfire_SetFraming_CommMode_DESFireNative = 1,
	/**
	 * ISO 7816 compatible framing.
	 */
	brp_Desfire_SetFraming_CommMode_ISO7816Compatible = 2,
	brp_Desfire_SetFraming_CommMode_undefined = -1
} brp_Desfire_SetFraming_CommMode;
static inline bool brp_Desfire_SetFraming_CommMode_is_valid(int val) {
	switch (val) {
		case 1: /* DESFireNative*/
		case 2: /* ISO7816Compatible*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * Application ID - range from 0x00000000 to 0x00FFFFFF.
	 */
	unsigned AppId;
	/**
	 * ISO file ID
	 */
	unsigned IsoFileId;
	/**
	 * ISO DF filename (optional, 0..16 bytes)
	 */
	brp_buf IsoDfName;
	/**
	 * Length of **IsoDfName** (in bytes).
	 */
	size_t IsoDfName_len;
} brp_Desfire_GetDfNames_AppNr_Entry;
#ifdef BALTECH_SDK_INTERNAL
/**
 * PHY-negotiated link speed.
 */
typedef enum {
	/**
	 * Autonegotiation has not completed or link is down.
	 */
	brp_DHWCtrl_EthGetCommMode_Speed_Unknown = 0,
	/**
	 * 10 Mbit/s.
	 */
	brp_DHWCtrl_EthGetCommMode_Speed_Mbit10 = 1,
	/**
	 * 100 Mbit/s.
	 */
	brp_DHWCtrl_EthGetCommMode_Speed_Mbit100 = 2,
	/**
	 * 1000 Mbit/s (Gigabit).
	 */
	brp_DHWCtrl_EthGetCommMode_Speed_Mbit1000 = 3,
	brp_DHWCtrl_EthGetCommMode_Speed_undefined = -1
} brp_DHWCtrl_EthGetCommMode_Speed;
static inline bool brp_DHWCtrl_EthGetCommMode_Speed_is_valid(int val) {
	switch (val) {
		case 0: /* Unknown*/
		case 1: /* Mbit10*/
		case 2: /* Mbit100*/
		case 3: /* Mbit1000*/
			return true;
		default:
			return false;
	}
}
/**
 * PHY-negotiated duplex mode.
 */
typedef enum {
	/**
	 * Autonegotiation has not completed or link is down.
	 */
	brp_DHWCtrl_EthGetCommMode_Duplex_Unknown = 0,
	/**
	 * Half-duplex.
	 */
	brp_DHWCtrl_EthGetCommMode_Duplex_Half = 1,
	/**
	 * Full-duplex.
	 */
	brp_DHWCtrl_EthGetCommMode_Duplex_Full = 2,
	brp_DHWCtrl_EthGetCommMode_Duplex_undefined = -1
} brp_DHWCtrl_EthGetCommMode_Duplex;
static inline bool brp_DHWCtrl_EthGetCommMode_Duplex_is_valid(int val) {
	switch (val) {
		case 0: /* Unknown*/
		case 1: /* Half*/
		case 2: /* Full*/
			return true;
		default:
			return false;
	}
}
/**
 * Direction and drive configuration for the pin.
 */
typedef enum {
	/**
	 * Push-pull output driven low.
	 */
	brp_DHWCtrl_GpioConfigure_Mode_OutputLow = 0,
	/**
	 * Push-pull output driven high.
	 */
	brp_DHWCtrl_GpioConfigure_Mode_OutputHigh = 1,
	/**
	 * High-impedance input (no pull resistor).
	 */
	brp_DHWCtrl_GpioConfigure_Mode_InputFloating = 2,
	/**
	 * Input with internal pull-up.
	 */
	brp_DHWCtrl_GpioConfigure_Mode_InputPullUp = 3,
	/**
	 * Input with internal pull-down.
	 */
	brp_DHWCtrl_GpioConfigure_Mode_InputPullDown = 4,
	/**
	 * Open-drain output for wired-OR buses (I2C-style scan). Initial level Hi-Z; drive low via GpioSetState(_Low_) and release via GpioSetState(_High_).
	 */
	brp_DHWCtrl_GpioConfigure_Mode_OpenDrain = 5,
	/**
	 * Pin released back to the SoC default.
	 */
	brp_DHWCtrl_GpioConfigure_Mode_Disabled = 255,
	brp_DHWCtrl_GpioConfigure_Mode_undefined = -1
} brp_DHWCtrl_GpioConfigure_Mode;
static inline bool brp_DHWCtrl_GpioConfigure_Mode_is_valid(int val) {
	switch (val) {
		case 0: /* OutputLow*/
		case 1: /* OutputHigh*/
		case 2: /* InputFloating*/
		case 3: /* InputPullUp*/
		case 4: /* InputPullDown*/
		case 5: /* OpenDrain*/
		case 255: /* Disabled*/
			return true;
		default:
			return false;
	}
}
/**
 * Current bus speed of the attached USB device.
 */
typedef enum {
	/**
	 * No device attached to the port.
	 */
	brp_DHWCtrl_UsbHostWaitPortStatus_Speed_NoDevice = 0,
	/**
	 * Low-Speed (1.5 Mbit/s).
	 */
	brp_DHWCtrl_UsbHostWaitPortStatus_Speed_Low = 1,
	/**
	 * Full-Speed (12 Mbit/s).
	 */
	brp_DHWCtrl_UsbHostWaitPortStatus_Speed_Full = 2,
	/**
	 * High-Speed (480 Mbit/s).
	 */
	brp_DHWCtrl_UsbHostWaitPortStatus_Speed_High = 3,
	brp_DHWCtrl_UsbHostWaitPortStatus_Speed_undefined = -1
} brp_DHWCtrl_UsbHostWaitPortStatus_Speed;
static inline bool brp_DHWCtrl_UsbHostWaitPortStatus_Speed_is_valid(int val) {
	switch (val) {
		case 0: /* NoDevice*/
		case 1: /* Low*/
		case 2: /* Full*/
		case 3: /* High*/
			return true;
		default:
			return false;
	}
}
/**
 * Clock polarity: the level the clock rests at while idle.
 */
typedef enum {
	/**
	 * Clock idles low.
	 */
	brp_DHWCtrl_SpiActivate_Cpol_IdleLow = 0,
	/**
	 * Clock idles high.
	 */
	brp_DHWCtrl_SpiActivate_Cpol_IdleHigh = 1,
	brp_DHWCtrl_SpiActivate_Cpol_undefined = -1
} brp_DHWCtrl_SpiActivate_Cpol;
static inline bool brp_DHWCtrl_SpiActivate_Cpol_is_valid(int val) {
	switch (val) {
		case 0: /* IdleLow*/
		case 1: /* IdleHigh*/
			return true;
		default:
			return false;
	}
}
/**
 * Clock phase: which clock edge of a bit period samples the data.
 */
typedef enum {
	/**
	 * Each bit is sampled on the first clock edge of its bit period.
	 */
	brp_DHWCtrl_SpiActivate_Cpha_SampleOnFirstEdge = 0,
	/**
	 * Each bit is sampled on the second clock edge of its bit period.
	 */
	brp_DHWCtrl_SpiActivate_Cpha_SampleOnSecondEdge = 1,
	brp_DHWCtrl_SpiActivate_Cpha_undefined = -1
} brp_DHWCtrl_SpiActivate_Cpha;
static inline bool brp_DHWCtrl_SpiActivate_Cpha_is_valid(int val) {
	switch (val) {
		case 0: /* SampleOnFirstEdge*/
		case 1: /* SampleOnSecondEdge*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_EM_DecodeCfg_RxMod_Unknown = 0,
	/**
	 * 
	 */
	brp_EM_DecodeCfg_RxMod_Manchester = 16,
	/**
	 * 
	 */
	brp_EM_DecodeCfg_RxMod_Biphase = 32,
	/**
	 * 
	 */
	brp_EM_DecodeCfg_RxMod_NRZ = 48,
	brp_EM_DecodeCfg_RxMod_undefined = -1
} brp_EM_DecodeCfg_RxMod;
static inline bool brp_EM_DecodeCfg_RxMod_is_valid(int val) {
	switch (val) {
		case 0: /* Unknown*/
		case 16: /* Manchester*/
		case 32: /* Biphase*/
		case 48: /* NRZ*/
			return true;
		default:
			return false;
	}
}
/**
 * BRP over TCP connection status.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Eth_GetTcpConnectionStatus_Status_NotConnected = 0,
	/**
	 * 
	 */
	brp_Eth_GetTcpConnectionStatus_Status_ConnectionTrialRunning = 1,
	/**
	 * 
	 */
	brp_Eth_GetTcpConnectionStatus_Status_Connected = 2,
	brp_Eth_GetTcpConnectionStatus_Status_undefined = -1
} brp_Eth_GetTcpConnectionStatus_Status;
static inline bool brp_Eth_GetTcpConnectionStatus_Status_is_valid(int val) {
	switch (val) {
		case 0: /* NotConnected*/
		case 1: /* ConnectionTrialRunning*/
		case 2: /* Connected*/
			return true;
		default:
			return false;
	}
}
/**
 * Connection reason bit mask that is sent to the host as soon as a connection is established.
 */
typedef enum {
	/**
	 * This is the first connection after powerup.
	 */
	brp_Eth_OpenTcpConnection_ConnectionReason_Powerup = 1,
	/**
	 * There has been a Link Change event.
	 */
	brp_Eth_OpenTcpConnection_ConnectionReason_LinkChange = 2,
	/**
	 * The current PKI session is timing/has timed out. Restart PKI authentication.
	 */
	brp_Eth_OpenTcpConnection_ConnectionReason_SessionkeyTimeout = 4,
	/**
	 * Autoread has detected a new card. The card number can be retrieved with AR.GetMessage.
	 */
	brp_Eth_OpenTcpConnection_ConnectionReason_Message = 8,
	/**
	 * This is a UDP introspection induced connection trial. Open a PKI session, configure the device with the connection parameters of the host and restart the device afterwards.
	 */
	brp_Eth_OpenTcpConnection_ConnectionReason_UdpIntrospection = 16,
	/**
	 * There has been a software reset.
	 */
	brp_Eth_OpenTcpConnection_ConnectionReason_Reset = 32,
	/**
	 * There have been one or more connection trial failures before.
	 */
	brp_Eth_OpenTcpConnection_ConnectionReason_FailedConnectionTrials = 32768,
	brp_Eth_OpenTcpConnection_ConnectionReason_undefined = -1
} brp_Eth_OpenTcpConnection_ConnectionReason;
static inline bool brp_Eth_OpenTcpConnection_ConnectionReason_is_valid(int val) {
	switch (val) {
		case 1: /* Powerup*/
		case 2: /* LinkChange*/
		case 4: /* SessionkeyTimeout*/
		case 8: /* Message*/
		case 16: /* UdpIntrospection*/
		case 32: /* Reset*/
		case 32768: /* FailedConnectionTrials*/
			return true;
		default:
			return false;
	}
}
#endif  // BALTECH_SDK_INTERNAL
/**
 * Baudrate PCD-PICC.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Felica_GenericCmd_FastBaud_Kbps212 = 0,
	/**
	 * 
	 */
	brp_Felica_GenericCmd_FastBaud_Kbps424 = 1,
	brp_Felica_GenericCmd_FastBaud_undefined = -1
} brp_Felica_GenericCmd_FastBaud;
static inline bool brp_Felica_GenericCmd_FastBaud_is_valid(int val) {
	switch (val) {
		case 0: /* Kbps212*/
		case 1: /* Kbps424*/
			return true;
		default:
			return false;
	}
}
/**
 * Baudrate PCD-PICC.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Felica_Request_FastBaud_Kbps212 = 0,
	/**
	 * 
	 */
	brp_Felica_Request_FastBaud_Kbps424 = 1,
	brp_Felica_Request_FastBaud_undefined = -1
} brp_Felica_Request_FastBaud;
static inline bool brp_Felica_Request_FastBaud_is_valid(int val) {
	switch (val) {
		case 0: /* Kbps212*/
		case 1: /* Kbps424*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * ID of label. Random if first 2 bytes [01 FE] else unique.
	 */
	brp_buf NFCID;
	/**
	 * Length of **NFCID** (in bytes).
	 */
	size_t NFCID_len;
} brp_Felica_Request_Labels_Entry;
#ifdef BALTECH_SDK_INTERNAL
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_Hitag_Request_TagType_HitagS = 0,
	/**
	 * 
	 */
	brp_Hitag_Request_TagType_Hitag1 = 1,
	/**
	 * 
	 */
	brp_Hitag_Request_TagType_Hitag2Manchester = 2,
	/**
	 * 
	 */
	brp_Hitag_Request_TagType_Hitag2Biphase = 3,
	brp_Hitag_Request_TagType_undefined = -1
} brp_Hitag_Request_TagType;
static inline bool brp_Hitag_Request_TagType_is_valid(int val) {
	switch (val) {
		case 0: /* HitagS*/
		case 1: /* Hitag1*/
		case 2: /* Hitag2Manchester*/
		case 3: /* Hitag2Biphase*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_Hitag_Request_Mode_StdHtg12S = 0,
	/**
	 * 
	 */
	brp_Hitag_Request_Mode_AdvHtg1S = 1,
	/**
	 * 
	 */
	brp_Hitag_Request_Mode_FAdvHS = 2,
	brp_Hitag_Request_Mode_undefined = -1
} brp_Hitag_Request_Mode;
static inline bool brp_Hitag_Request_Mode_is_valid(int val) {
	switch (val) {
		case 0: /* StdHtg12S*/
		case 1: /* AdvHtg1S*/
		case 2: /* FAdvHS*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_Hitag_Select_SelMode_Select = 0,
	/**
	 * 
	 */
	brp_Hitag_Select_SelMode_Quiet = 1,
	/**
	 * 
	 */
	brp_Hitag_Select_SelMode_AuthPwd = 2,
	/**
	 * 
	 */
	brp_Hitag_Select_SelMode_H2AuthOnlyPwd = 3,
	brp_Hitag_Select_SelMode_undefined = -1
} brp_Hitag_Select_SelMode;
static inline bool brp_Hitag_Select_SelMode_is_valid(int val) {
	switch (val) {
		case 0: /* Select*/
		case 1: /* Quiet*/
		case 2: /* AuthPwd*/
		case 3: /* H2AuthOnlyPwd*/
			return true;
		default:
			return false;
	}
}
/**
 * Length of "Unique IDentifier" (UID). The UID may be either a fixed number or a number generated randomly by the PICC (and therefore not unique!).
 */
typedef enum {
	/**
	 * UID length of 4 Bytes.
	 */
	brp_Iso14a_RequestLegacy_UIDSize_SingleSize = 0,
	/**
	 * UID length of 7 Bytes.
	 */
	brp_Iso14a_RequestLegacy_UIDSize_DoubleSize = 1,
	/**
	 * UID length of 10 Bytes.
	 */
	brp_Iso14a_RequestLegacy_UIDSize_TripleSize = 2,
	brp_Iso14a_RequestLegacy_UIDSize_undefined = -1
} brp_Iso14a_RequestLegacy_UIDSize;
static inline bool brp_Iso14a_RequestLegacy_UIDSize_is_valid(int val) {
	switch (val) {
		case 0: /* SingleSize*/
		case 1: /* DoubleSize*/
		case 2: /* TripleSize*/
			return true;
		default:
			return false;
	}
}
#endif  // BALTECH_SDK_INTERNAL
/**
 * _Frame Size proximity coupling Device Integer_ (FSDI) value. This value is mapped to the Frame Size proximity coupling Device (FSD) value, which indicates the maximum frame size accepted by the PCD. 
 * 
 * **The current Baltech reader supports FSD of at least up to 64 bytes (FSDI=0x05). It is not recommended to use a smaller FSDI. Future versions of the Baltech reader might support higher FSDI values.**
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14a_RequestATS_FSDI_Bytes16 = 0,
	/**
	 * 
	 */
	brp_Iso14a_RequestATS_FSDI_Bytes24 = 1,
	/**
	 * 
	 */
	brp_Iso14a_RequestATS_FSDI_Bytes32 = 2,
	/**
	 * 
	 */
	brp_Iso14a_RequestATS_FSDI_Bytes40 = 3,
	/**
	 * 
	 */
	brp_Iso14a_RequestATS_FSDI_Bytes48 = 4,
	/**
	 * 
	 */
	brp_Iso14a_RequestATS_FSDI_Bytes64 = 5,
	/**
	 * 
	 */
	brp_Iso14a_RequestATS_FSDI_Bytes96 = 6,
	/**
	 * Recommended
	 */
	brp_Iso14a_RequestATS_FSDI_Bytes128 = 7,
	/**
	 * 
	 */
	brp_Iso14a_RequestATS_FSDI_Bytes256 = 8,
	brp_Iso14a_RequestATS_FSDI_undefined = -1
} brp_Iso14a_RequestATS_FSDI;
static inline bool brp_Iso14a_RequestATS_FSDI_is_valid(int val) {
	switch (val) {
		case 0: /* Bytes16*/
		case 1: /* Bytes24*/
		case 2: /* Bytes32*/
		case 3: /* Bytes40*/
		case 4: /* Bytes48*/
		case 5: /* Bytes64*/
		case 6: /* Bytes96*/
		case 7: /* Bytes128*/
		case 8: /* Bytes256*/
			return true;
		default:
			return false;
	}
}
/**
 * Number of time slots which should be used for requesting PICCs. The more PICCs are expected, the higher this value should be. In one time slot, at most one PICC may answer.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14b_Request_TimeSlots_TimeSlots1 = 0,
	/**
	 * 
	 */
	brp_Iso14b_Request_TimeSlots_TimeSlots2 = 1,
	/**
	 * 
	 */
	brp_Iso14b_Request_TimeSlots_TimeSlots4 = 2,
	/**
	 * 
	 */
	brp_Iso14b_Request_TimeSlots_TimeSlots8 = 3,
	/**
	 * 
	 */
	brp_Iso14b_Request_TimeSlots_TimeSlots16 = 4,
	brp_Iso14b_Request_TimeSlots_undefined = -1
} brp_Iso14b_Request_TimeSlots;
static inline bool brp_Iso14b_Request_TimeSlots_is_valid(int val) {
	switch (val) {
		case 0: /* TimeSlots1*/
		case 1: /* TimeSlots2*/
		case 2: /* TimeSlots4*/
		case 3: /* TimeSlots8*/
		case 4: /* TimeSlots16*/
			return true;
		default:
			return false;
	}
}
/**
 * _Frame Size proximity Card Integer_ (FSCI). This value is mapped to the Frame Size proximity Card (FSC) value, which indicates the maximum frame size accepted by the PICC. The possible FSC values (mapped to the FSCI index) are listed below.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14b_Request_FSCI_Bytes16 = 0,
	/**
	 * 
	 */
	brp_Iso14b_Request_FSCI_Bytes24 = 1,
	/**
	 * 
	 */
	brp_Iso14b_Request_FSCI_Bytes32 = 2,
	/**
	 * 
	 */
	brp_Iso14b_Request_FSCI_Bytes40 = 3,
	/**
	 * 
	 */
	brp_Iso14b_Request_FSCI_Bytes48 = 4,
	/**
	 * 
	 */
	brp_Iso14b_Request_FSCI_Bytes64 = 5,
	/**
	 * 
	 */
	brp_Iso14b_Request_FSCI_Bytes96 = 6,
	/**
	 * 
	 */
	brp_Iso14b_Request_FSCI_Bytes128 = 7,
	/**
	 * 
	 */
	brp_Iso14b_Request_FSCI_Bytes256 = 8,
	brp_Iso14b_Request_FSCI_undefined = -1
} brp_Iso14b_Request_FSCI;
static inline bool brp_Iso14b_Request_FSCI_is_valid(int val) {
	switch (val) {
		case 0: /* Bytes16*/
		case 1: /* Bytes24*/
		case 2: /* Bytes32*/
		case 3: /* Bytes40*/
		case 4: /* Bytes48*/
		case 5: /* Bytes64*/
		case 6: /* Bytes96*/
		case 7: /* Bytes128*/
		case 8: /* Bytes256*/
			return true;
		default:
			return false;
	}
}
/**
 * When this bit is set, the PICC supports ISO14443-4.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14b_Request_ProtType_NoISO14443L4Support = 0,
	/**
	 * 
	 */
	brp_Iso14b_Request_ProtType_ISO14443L4Support = 1,
	brp_Iso14b_Request_ProtType_undefined = -1
} brp_Iso14b_Request_ProtType;
static inline bool brp_Iso14b_Request_ProtType_is_valid(int val) {
	switch (val) {
		case 0: /* NoISO14443L4Support*/
		case 1: /* ISO14443L4Support*/
			return true;
		default:
			return false;
	}
}
/**
 * _Frame Waiting time Integer_ (FWI). This value is necessary for calculation of the _Frame Waiting Time_ (FWT) value, representing the maximum time needed by the PICC between receiving a frame and sending the corresponding answer. FWT is calculated by: 
 * 
 * FWT = (256 * 16 / 13,56 MHz) * 2 ^ FWI 
 * 
 * The FWT values given here (mapped to the FWI index) are approximate.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Us302 = 0,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Us604 = 1,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Us1208 = 2,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Us2416 = 3,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Us4832 = 4,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Us9664 = 5,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Ms19 = 6,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Ms39 = 7,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Ms77 = 8,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Ms155 = 9,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Ms309 = 10,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Ms618 = 11,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Ms1237 = 12,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Ms2474 = 13,
	/**
	 * 
	 */
	brp_Iso14b_Request_FWI_Ms4948 = 14,
	brp_Iso14b_Request_FWI_undefined = -1
} brp_Iso14b_Request_FWI;
static inline bool brp_Iso14b_Request_FWI_is_valid(int val) {
	switch (val) {
		case 0: /* Us302*/
		case 1: /* Us604*/
		case 2: /* Us1208*/
		case 3: /* Us2416*/
		case 4: /* Us4832*/
		case 5: /* Us9664*/
		case 6: /* Ms19*/
		case 7: /* Ms39*/
		case 8: /* Ms77*/
		case 9: /* Ms155*/
		case 10: /* Ms309*/
		case 11: /* Ms618*/
		case 12: /* Ms1237*/
		case 13: /* Ms2474*/
		case 14: /* Ms4948*/
			return true;
		default:
			return false;
	}
}
/**
 * _Start-up Frame Guard time Integer_ (SFGI). The SFGT (Start-up Frame Gart Time) defines a specific guard time replacing TR2 which is needed by the PICC before it is ready to receive the next frame after it has sent the Answer to ATTRIB command. SFGI is coded in the range from 0 to 14. The value of 15 is RFU. SFGT is calculated by: 
 * 
 * SFGT = (256 * 16 / 13,56 MHz) * 2 ^ SFGI 
 * 
 * The SFGT values given here (mapped to the SFGI index) are approximate.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Us302 = 0,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Us604 = 1,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Us1208 = 2,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Us2416 = 3,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Us4832 = 4,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Us9664 = 5,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Ms19 = 6,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Ms39 = 7,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Ms77 = 8,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Ms155 = 9,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Ms309 = 10,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Ms618 = 11,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Ms1237 = 12,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Ms2474 = 13,
	/**
	 * 
	 */
	brp_Iso14b_Request_SFGI_Ms4948 = 14,
	brp_Iso14b_Request_SFGI_undefined = -1
} brp_Iso14b_Request_SFGI;
static inline bool brp_Iso14b_Request_SFGI_is_valid(int val) {
	switch (val) {
		case 0: /* Us302*/
		case 1: /* Us604*/
		case 2: /* Us1208*/
		case 3: /* Us2416*/
		case 4: /* Us4832*/
		case 5: /* Us9664*/
		case 6: /* Ms19*/
		case 7: /* Ms39*/
		case 8: /* Ms77*/
		case 9: /* Ms155*/
		case 10: /* Ms309*/
		case 11: /* Ms618*/
		case 12: /* Ms1237*/
		case 13: /* Ms2474*/
		case 14: /* Ms4948*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * _Pseudo-Unique PICC Identifier_ (PUPI). With this identifier, each PICC can be distinguished from all others in the HF antenna field.
	 */
	brp_buf PUPI;
	/**
	 * _Application data field_. Contains information about the applications available on this PICC. 
	 * 
	 * According to the _ADC_ value of the _ProtInfo_ bit mask, either a proprietary coding or CRC_B compression coding is used.
	 */
	brp_buf AppData;
	/**
	 * If this flag is set, data must be sent and received at equal bit rates.
	 */
	bool Synced;
	/**
	 * When this flag is set, the PICC can send data with a bit rate of up to 848 kbit/s.
	 */
	bool Send848;
	/**
	 * When this flag is set, the PICC can send data with a bit rate of up to 424 kbit/s.
	 */
	bool Send424;
	/**
	 * When this flag is set, the PICC can send data with a bit rate of up to 212 kbit/s.
	 */
	bool Send212;
	/**
	 * When this flag is set, the PICC can receive data with a bit rate of up to 848 kbit/s.
	 */
	bool Recv848;
	/**
	 * When this flag is set, the PICC can receive data with a bit rate of up to 424 kbit/s.
	 */
	bool Recv424;
	/**
	 * When this flag is set, the PICC can receive data with a bit rate of up to 212 kbit/s.
	 */
	bool Recv212;
	/**
	 * _Frame Size proximity Card Integer_ (FSCI). This value is mapped to the Frame Size proximity Card (FSC) value, which indicates the maximum frame size accepted by the PICC. The possible FSC values (mapped to the FSCI index) are listed below.
	 */
	brp_Iso14b_Request_FSCI FSCI;
	/**
	 * When this bit is set, the PICC supports ISO14443-4.
	 */
	brp_Iso14b_Request_ProtType ProtType;
	/**
	 * _Frame Waiting time Integer_ (FWI). This value is necessary for calculation of the _Frame Waiting Time_ (FWT) value, representing the maximum time needed by the PICC between receiving a frame and sending the corresponding answer. FWT is calculated by: 
	 * 
	 * FWT = (256 * 16 / 13,56 MHz) * 2 ^ FWI 
	 * 
	 * The FWT values given here (mapped to the FWI index) are approximate.
	 */
	brp_Iso14b_Request_FWI FWI;
	/**
	 * Application Data Coding supported by the PICC. Possible values are: 
	 * 
	 *   * 0x00: Application Data is coded using a proprietary mechanism 
	 *   * 0x01: Application Data is coded using CRC_B
	 */
	unsigned ADC;
	/**
	 * If this flag is set, the PPIC supports NAD.
	 */
	bool NAD;
	/**
	 * If this flag is set, the PPIC supports CID.
	 */
	bool CID;
	/**
	 * _Start-up Frame Guard time Integer_ (SFGI). The SFGT (Start-up Frame Gart Time) defines a specific guard time replacing TR2 which is needed by the PICC before it is ready to receive the next frame after it has sent the Answer to ATTRIB command. SFGI is coded in the range from 0 to 14. The value of 15 is RFU. SFGT is calculated by: 
	 * 
	 * SFGT = (256 * 16 / 13,56 MHz) * 2 ^ SFGI 
	 * 
	 * The SFGT values given here (mapped to the SFGI index) are approximate.
	 */
	brp_Iso14b_Request_SFGI SFGI;
} brp_Iso14b_Request_ValueList_Entry;
/**
 * PICC's minimum delay before responding after the end of a command sent by PCD. The values introduced in this parameter need to be divided by the ISO 14443 subcarrier frequency (abbreviated as _fs_).
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14b_Attrib_TR0_Numerator64 = 0,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_TR0_Numerator48 = 1,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_TR0_Numerator16 = 2,
	brp_Iso14b_Attrib_TR0_undefined = -1
} brp_Iso14b_Attrib_TR0;
static inline bool brp_Iso14b_Attrib_TR0_is_valid(int val) {
	switch (val) {
		case 0: /* Numerator64*/
		case 1: /* Numerator48*/
		case 2: /* Numerator16*/
			return true;
		default:
			return false;
	}
}
/**
 * Minimum delay between subcarrier modulation start and beginning of data transmission. The values introduced in this parameter need to be divided by the ISO 14443 subcarrier frequency (abbreviated as _fs_).
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14b_Attrib_TR1_Numerator80 = 0,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_TR1_Numerator64 = 1,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_TR1_Numerator16 = 2,
	brp_Iso14b_Attrib_TR1_undefined = -1
} brp_Iso14b_Attrib_TR1;
static inline bool brp_Iso14b_Attrib_TR1_is_valid(int val) {
	switch (val) {
		case 0: /* Numerator80*/
		case 1: /* Numerator64*/
		case 2: /* Numerator16*/
			return true;
		default:
			return false;
	}
}
/**
 * _End Of Frame_ (EOF) flag for sending data to reader.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14b_Attrib_EOF__EOFrequired = 0,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_EOF__EOFoptional = 1,
	brp_Iso14b_Attrib_EOF__undefined = -1
} brp_Iso14b_Attrib_EOF_;
static inline bool brp_Iso14b_Attrib_EOF__is_valid(int val) {
	switch (val) {
		case 0: /* EOFrequired*/
		case 1: /* EOFoptional*/
			return true;
		default:
			return false;
	}
}
/**
 * _Start Of Frame_ (SOF) flag for sending data to reader.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14b_Attrib_SOF_SOFrequired = 0,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_SOF_SOFoptional = 1,
	brp_Iso14b_Attrib_SOF_undefined = -1
} brp_Iso14b_Attrib_SOF;
static inline bool brp_Iso14b_Attrib_SOF_is_valid(int val) {
	switch (val) {
		case 0: /* SOFrequired*/
		case 1: /* SOFoptional*/
			return true;
		default:
			return false;
	}
}
/**
 * _Frame Size proximity coupling Device Integer_ (FSDI) value. This value is mapped to the Frame Size proximity coupling Device (FSD) value, which indicates the maximum frame size accepted by the PCD. 
 * 
 * **The current Baltech reader supports FSD of at least up to 64 bytes (FSDI=0x05). It is not recommended to use a smaller FSDI. Future versions of the Baltech reader might support higher FSDI values.**
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14b_Attrib_FSDI_Bytes16 = 0,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_FSDI_Bytes24 = 1,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_FSDI_Bytes32 = 2,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_FSDI_Bytes40 = 3,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_FSDI_Bytes48 = 4,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_FSDI_Bytes64 = 5,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_FSDI_Bytes96 = 6,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_FSDI_Bytes128 = 7,
	/**
	 * 
	 */
	brp_Iso14b_Attrib_FSDI_Bytes256 = 8,
	brp_Iso14b_Attrib_FSDI_undefined = -1
} brp_Iso14b_Attrib_FSDI;
static inline bool brp_Iso14b_Attrib_FSDI_is_valid(int val) {
	switch (val) {
		case 0: /* Bytes16*/
		case 1: /* Bytes24*/
		case 2: /* Bytes32*/
		case 3: /* Bytes40*/
		case 4: /* Bytes48*/
		case 5: /* Bytes64*/
		case 6: /* Bytes96*/
		case 7: /* Bytes128*/
		case 8: /* Bytes256*/
			return true;
		default:
			return false;
	}
}
/**
 * _Frame Size proximity Card Integer_ (FSCI). This value is mapped to the Frame Size proximity Card (FSC) value, which indicates the maximum frame size accepted by the PICC. The possible FSC values (mapped to the FSCI index) are listed below.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FSCI_Bytes16 = 0,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FSCI_Bytes24 = 1,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FSCI_Bytes32 = 2,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FSCI_Bytes40 = 3,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FSCI_Bytes48 = 4,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FSCI_Bytes64 = 5,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FSCI_Bytes96 = 6,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FSCI_Bytes128 = 7,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FSCI_Bytes256 = 8,
	brp_Iso14L4_SetupAPDU_FSCI_undefined = -1
} brp_Iso14L4_SetupAPDU_FSCI;
static inline bool brp_Iso14L4_SetupAPDU_FSCI_is_valid(int val) {
	switch (val) {
		case 0: /* Bytes16*/
		case 1: /* Bytes24*/
		case 2: /* Bytes32*/
		case 3: /* Bytes40*/
		case 4: /* Bytes48*/
		case 5: /* Bytes64*/
		case 6: /* Bytes96*/
		case 7: /* Bytes128*/
		case 8: /* Bytes256*/
			return true;
		default:
			return false;
	}
}
/**
 * _Frame Waiting time Integer_ (FWI). This value is necessary for calculation of the _Frame Waiting Time_ (FWT) value, representing the maximum time needed by the PICC between receiving a frame and sending the corresponding answer. FWT is calculated by: 
 * 
 * FWT = (256 * 16 / 13.56 MHz) * 2 ^ FWI 
 * 
 * The FWT values given here (mapped to the FWI index) are approximate.
 */
typedef enum {
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Us302 = 0,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Us604 = 1,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Us1208 = 2,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Us2416 = 3,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Us4832 = 4,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Us9664 = 5,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Ms19 = 6,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Ms39 = 7,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Ms77 = 8,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Ms155 = 9,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Ms309 = 10,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Ms618 = 11,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Ms1237 = 12,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Ms2474 = 13,
	/**
	 * 
	 */
	brp_Iso14L4_SetupAPDU_FWI_Ms4948 = 14,
	brp_Iso14L4_SetupAPDU_FWI_undefined = -1
} brp_Iso14L4_SetupAPDU_FWI;
static inline bool brp_Iso14L4_SetupAPDU_FWI_is_valid(int val) {
	switch (val) {
		case 0: /* Us302*/
		case 1: /* Us604*/
		case 2: /* Us1208*/
		case 3: /* Us2416*/
		case 4: /* Us4832*/
		case 5: /* Us9664*/
		case 6: /* Ms19*/
		case 7: /* Ms39*/
		case 8: /* Ms77*/
		case 9: /* Ms155*/
		case 10: /* Ms309*/
		case 11: /* Ms618*/
		case 12: /* Ms1237*/
		case 13: /* Ms2474*/
		case 14: /* Ms4948*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * Unique ID of label.
	 */
	brp_buf UID;
	/**
	 * DSFID of label, only available, if DSFID bit in _Mode_ has been set.
	 */
	unsigned DSFID;
} brp_Iso15_GetUIDList_Labels_Entry;
/**
 * Communication mode for label addressing.
 */
typedef enum {
	/**
	 * The following label commands are sent without an UID (broadcast).
	 */
	brp_Iso15_SetMode_Mode_Unaddressed = 0,
	/**
	 * The following label commands are sent including the UID given in UID.
	 */
	brp_Iso15_SetMode_Mode_Addressed = 1,
	/**
	 * Useful if a lot of operations need to be performed with the same label since the UID is not transferred to the label over and over again.
	 */
	brp_Iso15_SetMode_Mode_Selected = 2,
	brp_Iso15_SetMode_Mode_undefined = -1
} brp_Iso15_SetMode_Mode;
static inline bool brp_Iso15_SetMode_Mode_is_valid(int val) {
	switch (val) {
		case 0: /* Unaddressed*/
		case 1: /* Addressed*/
		case 2: /* Selected*/
			return true;
		default:
			return false;
	}
}
#ifdef BALTECH_SDK_INTERNAL
/**
 * 
 */
typedef struct {
	/**
	 * **Length is greater than 0! It was set to zero to provide length information**
	 * 
	 * Contains the actual data read from the block.
	 */
	brp_buf BlockData;
	/**
	 * Security status byte of the block.
	 */
	unsigned BlockSecData;
} brp_Iso15_ReadBlock_Data_Entry;
#endif  // BALTECH_SDK_INTERNAL
/**
 * 
 */
typedef struct {
	/**
	 * Content that shall be written to blocks starting at _BlockId_
	 */
	brp_buf WriteBlock;
	/**
	 * Length of **WriteBlock** (in bytes).
	 */
	size_t WriteBlock_len;
} brp_Iso15_WriteMultipleBlocks_WriteBlocks_Entry;
/**
 * 
 */
typedef struct {
	/**
	 * Contains the actual data read from a block.
	 */
	brp_buf RecvBlock;
	/**
	 * Length of **RecvBlock** (in bytes).
	 */
	size_t RecvBlock_len;
} brp_Iso15_ReadMultipleBlocks_RecvBlocks_Entry;
/**
 * Logical SAM-ID (LID)
 */
typedef enum {
	/**
	 * Use this value to select an _NXP MIFARE SAM AV2_ or _AV3_.
	 */
	brp_Iso78_OpenSam_LID_AV2 = 0,
	/**
	 * Use this value to select an _HID SE Processor_ (also known as _iClass SAM_).
	 */
	brp_Iso78_OpenSam_LID_HID = 1,
	/**
	 * Use this value to select a SAM different from those named above.
	 */
	brp_Iso78_OpenSam_LID_Gen1 = 16,
	/**
	 * Use this value only if the reader has 2 SAM slots, and both SAMs are different from those named above. In this case, use the values _Gen1_ and _Gen2_ in the following order: 
	 * 
	 *   * Use _Gen1_ to select the first SAM.
	 *   * Use _Gen2_ to select the second SAM.
	 */
	brp_Iso78_OpenSam_LID_Gen2 = 17,
	brp_Iso78_OpenSam_LID_undefined = -1
} brp_Iso78_OpenSam_LID;
static inline bool brp_Iso78_OpenSam_LID_is_valid(int val) {
	switch (val) {
		case 0: /* AV2*/
		case 1: /* HID*/
		case 16: /* Gen1*/
		case 17: /* Gen2*/
			return true;
		default:
			return false;
	}
}
#ifdef BALTECH_SDK_INTERNAL
/**
 * Error code of this operation
 */
typedef enum {
	/**
	 * Successful operation
	 */
	brp_Main_Bf2Upload_ResultCode_Success = 0,
	/**
	 * The checksum of the _line_ variable is invalid.
	 */
	brp_Main_Bf2Upload_ResultCode_InvalidChecksum = 1,
	/**
	 * Programming timeout; repeat operation (up to 3 times).
	 */
	brp_Main_Bf2Upload_ResultCode_ProgrammingTimeout = 2,
	/**
	 * Verify timeout; repeat operation (up to 3 times).
	 */
	brp_Main_Bf2Upload_ResultCode_VerifyTimeout = 3,
	/**
	 * Unsupported code type
	 */
	brp_Main_Bf2Upload_ResultCode_UnsupportedCodeType = 4,
	/**
	 * Protocol error
	 */
	brp_Main_Bf2Upload_ResultCode_ProtocolError = 5,
	/**
	 * Device is secured by a Config Security Code; perform a factory reset and repeat operation ([ learn more](https://docs.baltech.de/project-setup/security.html#config-security-code)).
	 */
	brp_Main_Bf2Upload_ResultCode_SecuredByConfigSecurityCode = 6,
	brp_Main_Bf2Upload_ResultCode_undefined = -1
} brp_Main_Bf2Upload_ResultCode;
static inline bool brp_Main_Bf2Upload_ResultCode_is_valid(int val) {
	switch (val) {
		case 0: /* Success*/
		case 1: /* InvalidChecksum*/
		case 2: /* ProgrammingTimeout*/
		case 3: /* VerifyTimeout*/
		case 4: /* UnsupportedCodeType*/
		case 5: /* ProtocolError*/
		case 6: /* SecuredByConfigSecurityCode*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * MCE will be enabled.
	 */
	brp_Mce_Enable_Mode_Disable = 0,
	/**
	 * MCE will be disabled.
	 */
	brp_Mce_Enable_Mode_Enable = 1,
	brp_Mce_Enable_Mode_undefined = -1
} brp_Mce_Enable_Mode;
static inline bool brp_Mce_Enable_Mode_is_valid(int val) {
	switch (val) {
		case 0: /* Disable*/
		case 1: /* Enable*/
			return true;
		default:
			return false;
	}
}
#endif  // BALTECH_SDK_INTERNAL
/**
 * Authentication Mode.
 */
typedef enum {
	/**
	 * Authenticate with Key A.
	 */
	brp_Mif_AuthE2_AuthMode_KeyA = 96,
	/**
	 * Authenticate with Key B.
	 */
	brp_Mif_AuthE2_AuthMode_KeyB = 97,
	brp_Mif_AuthE2_AuthMode_undefined = -1
} brp_Mif_AuthE2_AuthMode;
static inline bool brp_Mif_AuthE2_AuthMode_is_valid(int val) {
	switch (val) {
		case 96: /* KeyA*/
		case 97: /* KeyB*/
			return true;
		default:
			return false;
	}
}
/**
 * Authentication Mode.
 */
typedef enum {
	/**
	 * Authenticate with Key A.
	 */
	brp_Mif_AuthUser_AuthMode_KeyA = 96,
	/**
	 * Authenticate with Key B.
	 */
	brp_Mif_AuthUser_AuthMode_KeyB = 97,
	brp_Mif_AuthUser_AuthMode_undefined = -1
} brp_Mif_AuthUser_AuthMode;
static inline bool brp_Mif_AuthUser_AuthMode_is_valid(int val) {
	switch (val) {
		case 96: /* KeyA*/
		case 97: /* KeyB*/
			return true;
		default:
			return false;
	}
}
/**
 * Access mode.
 */
typedef enum {
	/**
	 * Decrement the value.
	 */
	brp_Mif_ChangeValue_Mode_Decrement = 0,
	/**
	 * Increment the value.
	 */
	brp_Mif_ChangeValue_Mode_Increment = 1,
	/**
	 * Restore/load the value.
	 */
	brp_Mif_ChangeValue_Mode_Restore = 2,
	brp_Mif_ChangeValue_Mode_undefined = -1
} brp_Mif_ChangeValue_Mode;
static inline bool brp_Mif_ChangeValue_Mode_is_valid(int val) {
	switch (val) {
		case 0: /* Decrement*/
		case 1: /* Increment*/
		case 2: /* Restore*/
			return true;
		default:
			return false;
	}
}
/**
 * Access mode.
 */
typedef enum {
	/**
	 * Decrement the value.
	 */
	brp_Mif_ChangeValueBackup_Mode_Decrement = 0,
	/**
	 * Increment the value.
	 */
	brp_Mif_ChangeValueBackup_Mode_Increment = 1,
	/**
	 * Restore/load the value.
	 */
	brp_Mif_ChangeValueBackup_Mode_Restore = 2,
	brp_Mif_ChangeValueBackup_Mode_undefined = -1
} brp_Mif_ChangeValueBackup_Mode;
static inline bool brp_Mif_ChangeValueBackup_Mode_is_valid(int val) {
	switch (val) {
		case 0: /* Decrement*/
		case 1: /* Increment*/
		case 2: /* Restore*/
			return true;
		default:
			return false;
	}
}
/**
 * Desired authentication level.
 */
typedef enum {
	/**
	 * AES SL1 authentication.
	 */
	brp_Mif_AuthE2Extended_AuthLevel_AesSl1 = 0,
	/**
	 * AES SL3 authentication.
	 */
	brp_Mif_AuthE2Extended_AuthLevel_AesSl3 = 2,
	/**
	 * MIFARE authentication.
	 */
	brp_Mif_AuthE2Extended_AuthLevel_Mifare = 3,
	brp_Mif_AuthE2Extended_AuthLevel_undefined = -1
} brp_Mif_AuthE2Extended_AuthLevel;
static inline bool brp_Mif_AuthE2Extended_AuthLevel_is_valid(int val) {
	switch (val) {
		case 0: /* AesSl1*/
		case 2: /* AesSl3*/
		case 3: /* Mifare*/
			return true;
		default:
			return false;
	}
}
/**
 * Desired authentication level.
 */
typedef enum {
	/**
	 * AES SL1 authentication.
	 */
	brp_Mif_AuthUserExtended_AuthLevel_AesSl1 = 0,
	/**
	 * AES SL3 authentication.
	 */
	brp_Mif_AuthUserExtended_AuthLevel_AesSl3 = 2,
	/**
	 * MIFARE authentication.
	 */
	brp_Mif_AuthUserExtended_AuthLevel_Mifare = 3,
	brp_Mif_AuthUserExtended_AuthLevel_undefined = -1
} brp_Mif_AuthUserExtended_AuthLevel;
static inline bool brp_Mif_AuthUserExtended_AuthLevel_is_valid(int val) {
	switch (val) {
		case 0: /* AesSl1*/
		case 2: /* AesSl3*/
		case 3: /* Mifare*/
			return true;
		default:
			return false;
	}
}
/**
 * Selects a value operation.
 */
typedef enum {
	/**
	 * Increments a value block by the given value and stores the result in the Transfer Buffer.
	 */
	brp_Mif_ValueSL3_Cmd_Increment = 0,
	/**
	 * Decrements a value block by the given value and stores the result in the Transfer Buffer.
	 */
	brp_Mif_ValueSL3_Cmd_Decrement = 1,
	/**
	 * Transfers the content of the Transfer Buffer to the specified address. Can only be executed after an Increment, Decrement, IncrementTransfer, DecrementTransfer, or Restore command.
	 */
	brp_Mif_ValueSL3_Cmd_Transfer = 2,
	/**
	 * Combined Increment and Transfer.
	 */
	brp_Mif_ValueSL3_Cmd_IncrementTransfer = 3,
	/**
	 * Combined Decrement and Transfer.
	 */
	brp_Mif_ValueSL3_Cmd_DecrementTransfer = 4,
	/**
	 * Copies the value block content to the TransferBuffer.
	 */
	brp_Mif_ValueSL3_Cmd_Restore = 5,
	brp_Mif_ValueSL3_Cmd_undefined = -1
} brp_Mif_ValueSL3_Cmd;
static inline bool brp_Mif_ValueSL3_Cmd_is_valid(int val) {
	switch (val) {
		case 0: /* Increment*/
		case 1: /* Decrement*/
		case 2: /* Transfer*/
		case 3: /* IncrementTransfer*/
		case 4: /* DecrementTransfer*/
		case 5: /* Restore*/
			return true;
		default:
			return false;
	}
}
/**
 * Type of File Control Information returned.
 */
typedef enum {
	/**
	 * Raw data.
	 */
	brp_Mif_VirtualCardSelect_FciType_RawData = 0,
	/**
	 * uid_len(1) and card type(1).
	 */
	brp_Mif_VirtualCardSelect_FciType_UidAndCardType = 1,
	/**
	 * uid_len(1), card type(1) and memory size(1).
	 */
	brp_Mif_VirtualCardSelect_FciType_UidCardTypeAndMemSize = 2,
	brp_Mif_VirtualCardSelect_FciType_undefined = -1
} brp_Mif_VirtualCardSelect_FciType;
static inline bool brp_Mif_VirtualCardSelect_FciType_is_valid(int val) {
	switch (val) {
		case 0: /* RawData*/
		case 1: /* UidAndCardType*/
		case 2: /* UidCardTypeAndMemSize*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * Block address of the sector that is switched to the targeted security level.
	 */
	unsigned BlockAddress;
	/**
	 * Crypto Memory Index (SAM or CryptoMemory) of the sector key. 
	 * 
	 *   * SAM: MSByte: Key version / LSByte: KeyIdx 
	 *   * Crypto Memory: MSByte: Page (0..15) / LSByte: KeyIdx (0x80-0xBF)
	 */
	unsigned SectorKeyIdx;
} brp_Mif_SectorSwitch_SectorSpec_Entry;
/**
 * Defines 14443-4 communication mode for MIFARE Plus EV1 cards.
 */
typedef enum {
	/**
	 * MIFARE native mode (default communication mode).
	 */
	brp_Mif_SetFraming_CommMode_MifareNative = 1,
	/**
	 * ISO 7816 compatible framing (only MIFARE Plus EV1)
	 */
	brp_Mif_SetFraming_CommMode_MifareISO = 2,
	brp_Mif_SetFraming_CommMode_undefined = -1
} brp_Mif_SetFraming_CommMode;
static inline bool brp_Mif_SetFraming_CommMode_is_valid(int val) {
	switch (val) {
		case 1: /* MifareNative*/
		case 2: /* MifareISO*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * Mobile ID is enabled.
	 */
	brp_MobileId_Enable_Mode_Disable = 0,
	/**
	 * Mobile ID is disabled.
	 */
	brp_MobileId_Enable_Mode_Enable = 1,
	brp_MobileId_Enable_Mode_undefined = -1
} brp_MobileId_Enable_Mode;
static inline bool brp_MobileId_Enable_Mode_is_valid(int val) {
	switch (val) {
		case 0: /* Disable*/
		case 1: /* Enable*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * The reader chip has not accepted the reader chip firmware included in the latest firmware update, because it was already running a higher firmware version. This is a security feature that prevents the reader chip firmware from being downgraded below a specific version. 
	 * 
	 * _Note:_ This only affects the reader chip, i.e. other reader components have accepted the latest firmware update. 
	 * 
	 * _Solution:_ Usually, this is not an issue. However, if you want to get rid of this boot status, upgrade to the previously deployed firmware version or above.
	 */
	bool NewerReaderChipFirmware;
	/**
	 * At least 1 unexpected reboot has occurred. For details, see Device/Statistics. 
	 * 
	 * This is a legacy boot status. It is not returned by newer firmware versions.
	 */
	bool UnexpectedRebootsLegacy;
	/**
	 * An error occurred during a factory reset, leaving the reader without any settings instead of restoring the factory settings.
	 */
	bool FactorySettings;
	/**
	 * The reader configuration is corrupted.   
	 * _Solution:_ Redeploy or update the reader configuration. 
	 * 
	 * This is a legacy boot status. It's only returned by old firmware versions that don't yet support transaction security mechanisms. Newer firmware versions use the _Configuration_ bit.
	 */
	bool ConfigurationInconsistent;
	/**
	 * The loaded firmware version is blacklisted. For details, see Device / Run / FirmwareVersionBlacklist.
	 */
	bool FirmwareVersionBlocked;
	/**
	 * The Bluetooth chip of the reader is defective, device out of order. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool Bluetooth;
	/**
	 * The WiFi chip of the reader is defective, device out of order. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool WiFi;
	/**
	 * The tamper alarm is defective. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool Tamper;
	/**
	 * The battery management system of the reader is defective, device out of order. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool BatteryManagement;
	/**
	 * The keyboard of the reader is defective, device out of order. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool Keyboard;
	/**
	 * The loaded firmware version is blacklisted. For details, see Device / Run / FirmwareVersionBlacklist. 
	 * 
	 * This is a legacy boot status. Newer firmware versions use the _FirmwareVersionBlocked_ bit.
	 */
	bool FirmwareVersionBlockedLegacy;
	/**
	 * The display of the reader is defective, device out of order. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool Display;
	/**
	 * You've run a VHL.Select command with _AcceptConfCard_ set to _true_ after presenting a [ConfigCard](https://docs.baltech.de/installation/deploy-config-via-configcard.html) to the reader and the reconfiguration of the reader failed. 
	 * 
	 * This is a legacy boot status. It is not returned by newer firmware versions. Use the VHL.CheckReconfigErr command to check the reconfiguration status.
	 */
	bool ConfCardPresented;
	/**
	 * The Ethernet interface of the reader is defective, device out of order. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool Ethernet;
	/**
	 * The RGB LED features of the reader are defective. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool ExtendedLED;
	/**
	 * The 125 kHz RFID interface of the reader is defective, device out of order. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool Rf125kHz;
	/**
	 * The 13.56 MHz RFID interface for ISO 14443/ISO 15693 card systems is defective, device out of order. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool Rf13MHz;
	/**
	 * The 13.56 Mhz RFID interface for LEGIC cards is defective, device out of order. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool Rf13MHzLegic;
	/**
	 * The 13.56 MHz RFID interface of the reader is defective, device out of order. 
	 * 
	 * This is a legacy boot status. Newer firmware versions use the _Rf13Mhz_ bit. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool Rf13MHzLegacy;
	/**
	 * A hardware options error occurred, device out of order. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool HWoptions;
	/**
	 * The real-time clock is defective, device out of order. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool RTC;
	/**
	 * The data flash chip is defective, device out of order. 
	 * 
	 * **Please[ get in touch](https://docs.baltech.de/support/contact-support.html) with us.**
	 */
	bool Dataflash;
	/**
	 * The reader configuration is corrupted.  
	 * _Solution:_ Redeploy or update the configuration.
	 */
	bool Configuration;
	/**
	 * The reader firmware is corrupted.  
	 * _Solution:_ Redeploy or update the firmware.
	 */
	bool CorruptFirmware;
	/**
	 * Due to an aborted upload, the firmware on the reader is incomplete and not fully functional.   
	 * _Solution:_ Repeat the firmware upload.
	 */
	bool IncompleteFirmware;
} brp_Sys_GetBootStatus_BootStatus;
#ifdef BALTECH_SDK_INTERNAL
/**
 * 
 */
typedef struct {
	/**
	 * ID of register to set
	 */
	unsigned ID;
	/**
	 * New value of register to set
	 */
	unsigned Value;
} brp_Sys_SetRegister_RegisterAssignments_Entry;
#endif  // BALTECH_SDK_INTERNAL
/**
 * 
 */
typedef struct {
	/**
	 * ID of statistics counter (Baltech internal use)
	 */
	unsigned ID;
	/**
	 * Value of counter (Baltech internal use)
	 */
	unsigned Value;
} brp_Sys_GetStatistics_CounterTuple_Entry;
/**
 * Defines the reader's behaviour on error/success
 */
typedef enum {
	/**
	 * Cancel the BEC transfer and undo all configuration changes since Sys.CfgLoadPrepare.
	 */
	brp_Sys_CfgLoadFinish_FinalizeAction_CancelCfgLoad = 0,
	/**
	 * Complete the BEC transfer, but don't reboot. 
	 * 
	 * **A reboot is necessary to ensure all configuration changes are activated. Thus, we recommend you only use this value if another operation is pending that requires a reboot as well (e.g. a firmware update).**
	 */
	brp_Sys_CfgLoadFinish_FinalizeAction_FinalizeCfgLoadWithoutReboot = 1,
	/**
	 * Complete the BEC transfer and do an implicit reboot. This requires reconnecting as described in Sys.Reset. 
	 * 
	 * **This is the value we generally recommend as the reboot ensures that all changes are activated.**
	 */
	brp_Sys_CfgLoadFinish_FinalizeAction_FinalizeCfgLoadWithReboot = 2,
	brp_Sys_CfgLoadFinish_FinalizeAction_undefined = -1
} brp_Sys_CfgLoadFinish_FinalizeAction;
static inline bool brp_Sys_CfgLoadFinish_FinalizeAction_is_valid(int val) {
	switch (val) {
		case 0: /* CancelCfgLoad*/
		case 1: /* FinalizeCfgLoadWithoutReboot*/
		case 2: /* FinalizeCfgLoadWithReboot*/
			return true;
		default:
			return false;
	}
}
#ifdef BALTECH_SDK_INTERNAL
/**
 * Decoder settings - for ID-engine Z use SMPL.
 */
typedef enum {
	/**
	 * 
	 */
	brp_TTF_ReadByteStream_RxMod_Manchester = 16,
	/**
	 * 
	 */
	brp_TTF_ReadByteStream_RxMod_Biphase = 32,
	/**
	 * 
	 */
	brp_TTF_ReadByteStream_RxMod_Ind = 48,
	/**
	 * 
	 */
	brp_TTF_ReadByteStream_RxMod_HIDP = 80,
	/**
	 * 
	 */
	brp_TTF_ReadByteStream_RxMod_PSK = 96,
	/**
	 * 
	 */
	brp_TTF_ReadByteStream_RxMod_SMPL = 112,
	brp_TTF_ReadByteStream_RxMod_undefined = -1
} brp_TTF_ReadByteStream_RxMod;
static inline bool brp_TTF_ReadByteStream_RxMod_is_valid(int val) {
	switch (val) {
		case 16: /* Manchester*/
		case 32: /* Biphase*/
		case 48: /* Ind*/
		case 80: /* HIDP*/
		case 96: /* PSK*/
		case 112: /* SMPL*/
			return true;
		default:
			return false;
	}
}
#endif  // BALTECH_SDK_INTERNAL
/**
 * Specifies diversification algorithm.
 */
typedef enum {
	/**
	 * No diversification.
	 */
	brp_Ultralight_AuthE2_DivMode_NoDiv = 0,
	/**
	 * SAM AV1 mode (1 encryption round for Tripple DES keys).
	 */
	brp_Ultralight_AuthE2_DivMode_SamAv1OneRound = 1,
	/**
	 * SAM AV1 mode (2 encryption rounds for Tripple DES keys).
	 */
	brp_Ultralight_AuthE2_DivMode_SamAv1TwoRounds = 2,
	/**
	 * SAM AV2 mode (AES according to NXP: AN 10922).
	 */
	brp_Ultralight_AuthE2_DivMode_SamAv2 = 3,
	brp_Ultralight_AuthE2_DivMode_undefined = -1
} brp_Ultralight_AuthE2_DivMode;
static inline bool brp_Ultralight_AuthE2_DivMode_is_valid(int val) {
	switch (val) {
		case 0: /* NoDiv*/
		case 1: /* SamAv1OneRound*/
		case 2: /* SamAv1TwoRounds*/
		case 3: /* SamAv2*/
			return true;
		default:
			return false;
	}
}
/**
 * Sets the encryption algorithm.
 */
typedef enum {
	/**
	 * For Ultralight-C authentication, a Tripple DES key has to be specified.
	 */
	brp_Ultralight_AuthUser_CryptoMode_TripleDES = 0,
	/**
	 * For Ultralight-EV1 password diversification (NXP AN12694), an AES key has to be specified.
	 */
	brp_Ultralight_AuthUser_CryptoMode_AES = 1,
	brp_Ultralight_AuthUser_CryptoMode_undefined = -1
} brp_Ultralight_AuthUser_CryptoMode;
static inline bool brp_Ultralight_AuthUser_CryptoMode_is_valid(int val) {
	switch (val) {
		case 0: /* TripleDES*/
		case 1: /* AES*/
			return true;
		default:
			return false;
	}
}
#ifdef BALTECH_SDK_INTERNAL
/**
 * Type of Pipe.
 */
typedef enum {
	/**
	 * 
	 */
	brp_UsbHost_SetupPipes_Type_Control = 0,
	/**
	 * 
	 */
	brp_UsbHost_SetupPipes_Type_Interrupt = 1,
	/**
	 * 
	 */
	brp_UsbHost_SetupPipes_Type_Bulk = 2,
	/**
	 * 
	 */
	brp_UsbHost_SetupPipes_Type_Isochronous = 3,
	brp_UsbHost_SetupPipes_Type_undefined = -1
} brp_UsbHost_SetupPipes_Type;
static inline bool brp_UsbHost_SetupPipes_Type_is_valid(int val) {
	switch (val) {
		case 0: /* Control*/
		case 1: /* Interrupt*/
		case 2: /* Bulk*/
		case 3: /* Isochronous*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * Number of Pipe.
	 */
	unsigned No;
	/**
	 * Type of Pipe.
	 */
	brp_UsbHost_SetupPipes_Type Type;
	/**
	 * Maximum Packet Size of Pipe. Possible Values are 8, 16, 32 and 64.
	 */
	unsigned FrameSize;
} brp_UsbHost_SetupPipes_Pipes_Entry;
#endif  // BALTECH_SDK_INTERNAL
/**
 * 
 */
typedef enum {
	/**
	 * The initial and final port state is disabled/inactive/low.
	 */
	brp_UI_Toggle_Polarity_Normal = 0,
	/**
	 * The initial and final port state is enabled/active/high.
	 */
	brp_UI_Toggle_Polarity_Inverted = 1,
	brp_UI_Toggle_Polarity_undefined = -1
} brp_UI_Toggle_Polarity;
static inline bool brp_UI_Toggle_Polarity_is_valid(int val) {
	switch (val) {
		case 0: /* Normal*/
		case 1: /* Inverted*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * The port is enabled/active/high.
	 */
	brp_UI_Sense_PortState_Enabled = 1,
	/**
	 * The port is disabled/inactive/low.
	 */
	brp_UI_Sense_PortState_Disabled = 0,
	brp_UI_Sense_PortState_undefined = -1
} brp_UI_Sense_PortState;
static inline bool brp_UI_Sense_PortState_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 1: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_HasMifareKey_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_HasMifareKey_Enabled = 6,
	brp_VHL_Setup_HasMifareKey_undefined = -1
} brp_VHL_Setup_HasMifareKey;
static inline bool brp_VHL_Setup_HasMifareKey_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 6: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_MifareHasAsKeyA_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_MifareHasAsKeyA_Enabled = 1,
	brp_VHL_Setup_MifareHasAsKeyA_undefined = -1
} brp_VHL_Setup_MifareHasAsKeyA;
static inline bool brp_VHL_Setup_MifareHasAsKeyA_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 1: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_MifareHasMadId_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_MifareHasMadId_Enabled = 2,
	brp_VHL_Setup_MifareHasMadId_undefined = -1
} brp_VHL_Setup_MifareHasMadId;
static inline bool brp_VHL_Setup_MifareHasMadId_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 2: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_DesfireHasAppId_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_DesfireHasAppId_Enabled = 4,
	brp_VHL_Setup_DesfireHasAppId_undefined = -1
} brp_VHL_Setup_DesfireHasAppId;
static inline bool brp_VHL_Setup_DesfireHasAppId_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 4: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_HasDesfireFileDesc_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_HasDesfireFileDesc_Enabled = 16,
	brp_VHL_Setup_HasDesfireFileDesc_undefined = -1
} brp_VHL_Setup_HasDesfireFileDesc;
static inline bool brp_VHL_Setup_HasDesfireFileDesc_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 16: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_LegicHasEnStamp_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_LegicHasEnStamp_Enabled = 1,
	brp_VHL_Setup_LegicHasEnStamp_undefined = -1
} brp_VHL_Setup_LegicHasEnStamp;
static inline bool brp_VHL_Setup_LegicHasEnStamp_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 1: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_LegicHasAdrMode_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_LegicHasAdrMode_Enabled = 1,
	brp_VHL_Setup_LegicHasAdrMode_undefined = -1
} brp_VHL_Setup_LegicHasAdrMode;
static inline bool brp_VHL_Setup_LegicHasAdrMode_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 1: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * Specifies the addressing mode. This parameter is only available on readers supporting LEGIC advant. LEGIC prime readers ignore it. 
 * 
 * **To allow for backward compatibility with LEGIC prime readers, omitting this parameter will _not_ result in the default value, but in the following behavior: VHL address 0 is mapped to protocol header address _25_ , starting with the first data byte after the longest possible LEGIC prime stamp.**
 */
typedef enum {
	/**
	 * To read the segment _stamp_ , use this mode. 
	 * 
	 * VHL address 0 corresponds to protocol header address 18, starting with the first stamp data byte. The stamp, which has a length between 1 and 12 bytes, is followed by the application data.
	 */
	brp_VHL_Setup_LegicAdrMode_ProtocolHeader = 0,
	/**
	 * To only read the _application data_ of the segment, use this mode. 
	 * 
	 * VHL address 0 corresponds to address 0 in the user-specific application data area ("DATA area" according to the LEGIC documentation). 
	 * 
	 * **
	 * 
	 * For _LEGIC prime_ cards, this addressing mode is available only with restrictions: Here, the stamp length is undefined - the card doesn't know it. So, when accessing the card using _VHL.Setup_ , the stamp in _LegicSegmentInfo_ with the given length will be applied.
	 * 
	 * If the actual stamp is longer, the reader assigns the remaining part of the stamp to the application data area (DATA). If the segment is accessed via segment number, no stamp length information is available at all. In this case, the application data area (DATA) contains the complete stamp (this is equivalent to the _ProtocolHeader_ addressing mode).
	 * 
	 * See the following table for examples.
	 * 
	 * **
	 * 
	 * _LegicSegmentInfo_ | _LegicEnStamp_ | _LegicAdrMode_ | Result of VHL.Read(Id=0xFF, Adr=0, Len=5)  
	 * ---|---|---|---  
	 * 1 | False | _ProtocolHeader_ | 0x11 22 33 44 01  
	 * 0x11 22 33 | True | _ProtocolHeader_ | 0x11 22 33 44 01  
	 * 1 | False | _Advant_ | 0x11 22 33 44 01  
	 * 0x11 22 33 44 | False | _Advant_ | 0x01 02 03 04 05  
	 * 0x11 22 | True | _Advant_ | 0x33 44 01 02 03
	 */
	brp_VHL_Setup_LegicAdrMode_Advant = 1,
	brp_VHL_Setup_LegicAdrMode_undefined = -1
} brp_VHL_Setup_LegicAdrMode;
static inline bool brp_VHL_Setup_LegicAdrMode_is_valid(int val) {
	switch (val) {
		case 0: /* ProtocolHeader*/
		case 1: /* Advant*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_Iso15HasFirstBlock_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_Iso15HasFirstBlock_Enabled = 1,
	brp_VHL_Setup_Iso15HasFirstBlock_undefined = -1
} brp_VHL_Setup_Iso15HasFirstBlock;
static inline bool brp_VHL_Setup_Iso15HasFirstBlock_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 1: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_Iso15HasBlockCount_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_Iso15HasBlockCount_Enabled = 1,
	brp_VHL_Setup_Iso15HasBlockCount_undefined = -1
} brp_VHL_Setup_Iso15HasBlockCount;
static inline bool brp_VHL_Setup_Iso15HasBlockCount_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 1: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_Iso15HasOptionFlag_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_Iso15HasOptionFlag_Enabled = 1,
	brp_VHL_Setup_Iso15HasOptionFlag_undefined = -1
} brp_VHL_Setup_Iso15HasOptionFlag;
static inline bool brp_VHL_Setup_Iso15HasOptionFlag_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 1: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * Option flag value for read/write operations
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_Iso15OptionFlag_OptFlagZero = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_Iso15OptionFlag_OptFlagOne = 1,
	/**
	 * 
	 */
	brp_VHL_Setup_Iso15OptionFlag_OptFlagAuto = 2,
	brp_VHL_Setup_Iso15OptionFlag_undefined = -1
} brp_VHL_Setup_Iso15OptionFlag;
static inline bool brp_VHL_Setup_Iso15OptionFlag_is_valid(int val) {
	switch (val) {
		case 0: /* OptFlagZero*/
		case 1: /* OptFlagOne*/
		case 2: /* OptFlagAuto*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_Iso15HasBlockSize_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_Iso15HasBlockSize_Enabled = 1,
	brp_VHL_Setup_Iso15HasBlockSize_undefined = -1
} brp_VHL_Setup_Iso15HasBlockSize;
static inline bool brp_VHL_Setup_Iso15HasBlockSize_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 1: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * The method to select the file
 */
typedef enum {
	/**
	 * Select the file by DF name
	 */
	brp_VHL_Setup_FileSpecifier_SelectByName = 0,
	/**
	 * Select the file by path, i.e. a list of 16-bit file IDs  
	 * If a single file ID is used, a MF, DF, or EF can be specified -> P1 is set to 0  
	 * If a list of file ID is used, the path without the MF has to be specified -> P1 is set to 8
	 */
	brp_VHL_Setup_FileSpecifier_SelectByPath = 1,
	/**
	 * Select the file using an APDU command
	 */
	brp_VHL_Setup_FileSpecifier_SelectByAPDU = 2,
	brp_VHL_Setup_FileSpecifier_undefined = -1
} brp_VHL_Setup_FileSpecifier;
static inline bool brp_VHL_Setup_FileSpecifier_is_valid(int val) {
	switch (val) {
		case 0: /* SelectByName*/
		case 1: /* SelectByPath*/
		case 2: /* SelectByAPDU*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef struct {
	/**
	 * The method to select the file
	 */
	brp_VHL_Setup_FileSpecifier FileSpecifier;
	/**
	 * The name of the DF to be selected (1..16 bytes)
	 */
	brp_buf Name;
	/**
	 * Length of **Name** (in bytes).
	 */
	size_t Name_len;
	/**
	 * A list of one or more 16-bit file IDs
	 */
	brp_buf Path;
	/**
	 * Length of **Path** (in bytes).
	 */
	size_t Path_len;
	/**
	 * APDU command by which to select the file
	 */
	brp_buf ApduCommand;
	/**
	 * Length of **ApduCommand** (in bytes).
	 */
	size_t ApduCommand_len;
} brp_VHL_Setup_Iso14SelectFileCmdList_Entry;
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_Iso14HasFileLen_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_Iso14HasFileLen_Enabled = 4,
	brp_VHL_Setup_Iso14HasFileLen_undefined = -1
} brp_VHL_Setup_Iso14HasFileLen;
static inline bool brp_VHL_Setup_Iso14HasFileLen_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 4: /* Enabled*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_VHL_Setup_Iso14HasApduTimeout_Disabled = 0,
	/**
	 * 
	 */
	brp_VHL_Setup_Iso14HasApduTimeout_Enabled = 2,
	brp_VHL_Setup_Iso14HasApduTimeout_undefined = -1
} brp_VHL_Setup_Iso14HasApduTimeout;
static inline bool brp_VHL_Setup_Iso14HasApduTimeout_is_valid(int val) {
	switch (val) {
		case 0: /* Disabled*/
		case 2: /* Enabled*/
			return true;
		default:
			return false;
	}
}
#ifdef BALTECH_SDK_INTERNAL
/**
 * There are four modes possible:
 */
typedef enum {
	/**
	 * The port is pushed to low level.
	 */
	brp_DHWCtrlLegacy_PortConfig_Mode_OutputLow = 0,
	/**
	 * The port is pushed to high level.
	 */
	brp_DHWCtrlLegacy_PortConfig_Mode_OutputHigh = 1,
	/**
	 * The port is in very high resistance mode.
	 */
	brp_DHWCtrlLegacy_PortConfig_Mode_InputTristate = 2,
	/**
	 * The port drives a positive voltage over a resistor.
	 */
	brp_DHWCtrlLegacy_PortConfig_Mode_InputPullup = 3,
	brp_DHWCtrlLegacy_PortConfig_Mode_undefined = -1
} brp_DHWCtrlLegacy_PortConfig_Mode;
static inline bool brp_DHWCtrlLegacy_PortConfig_Mode_is_valid(int val) {
	switch (val) {
		case 0: /* OutputLow*/
		case 1: /* OutputHigh*/
		case 2: /* InputTristate*/
		case 3: /* InputPullup*/
			return true;
		default:
			return false;
	}
}
/**
 * Drawing color.
 */
typedef enum {
	/**
	 * White color.
	 */
	brp_DHWCtrlLegacy_DispColor_Color_White = 0,
	/**
	 * Black color.
	 */
	brp_DHWCtrlLegacy_DispColor_Color_Black = 255,
	brp_DHWCtrlLegacy_DispColor_Color_undefined = -1
} brp_DHWCtrlLegacy_DispColor_Color;
static inline bool brp_DHWCtrlLegacy_DispColor_Color_is_valid(int val) {
	switch (val) {
		case 0: /* White*/
		case 255: /* Black*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_GetReaderChipType_ChipType_RC500 = 1,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_GetReaderChipType_ChipType_RC632 = 4,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_GetReaderChipType_ChipType_RC663 = 5,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_GetReaderChipType_ChipType_PN512 = 33,
	brp_DHWCtrlLegacy_GetReaderChipType_ChipType_undefined = -1
} brp_DHWCtrlLegacy_GetReaderChipType_ChipType;
static inline bool brp_DHWCtrlLegacy_GetReaderChipType_ChipType_is_valid(int val) {
	switch (val) {
		case 1: /* RC500*/
		case 4: /* RC632*/
		case 5: /* RC663*/
		case 33: /* PN512*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_GetSamType_ChipType_TDA8007C2 = 1,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_GetSamType_ChipType_TDA8007C3 = 2,
	brp_DHWCtrlLegacy_GetSamType_ChipType_undefined = -1
} brp_DHWCtrlLegacy_GetSamType_ChipType;
static inline bool brp_DHWCtrlLegacy_GetSamType_ChipType_is_valid(int val) {
	switch (val) {
		case 1: /* TDA8007C2*/
		case 2: /* TDA8007C3*/
			return true;
		default:
			return false;
	}
}
/**
 * HF subsystem to activate
 */
typedef enum {
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_HfAcquire_ModuleId_No = 0,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_HfAcquire_ModuleId_RC = 1,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_HfAcquire_ModuleId_Legic = 3,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_HfAcquire_ModuleId_PN = 17,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_HfAcquire_ModuleId_LegicAdvant = 19,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_HfAcquire_ModuleId_RC125 = 24,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_HfAcquire_ModuleId_PN2 = 26,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_HfAcquire_ModuleId_RC663 = 34,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_HfAcquire_ModuleId_HTRC110 = 36,
	brp_DHWCtrlLegacy_HfAcquire_ModuleId_undefined = -1
} brp_DHWCtrlLegacy_HfAcquire_ModuleId;
static inline bool brp_DHWCtrlLegacy_HfAcquire_ModuleId_is_valid(int val) {
	switch (val) {
		case 0: /* No*/
		case 1: /* RC*/
		case 3: /* Legic*/
		case 17: /* PN*/
		case 19: /* LegicAdvant*/
		case 24: /* RC125*/
		case 26: /* PN2*/
		case 34: /* RC663*/
		case 36: /* HTRC110*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_AesWrapKey_WrappedKeyNr_WrapNone = 0,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_AesWrapKey_WrappedKeyNr_WrapDHUK = 1,
	brp_DHWCtrlLegacy_AesWrapKey_WrappedKeyNr_undefined = -1
} brp_DHWCtrlLegacy_AesWrapKey_WrappedKeyNr;
static inline bool brp_DHWCtrlLegacy_AesWrapKey_WrappedKeyNr_is_valid(int val) {
	switch (val) {
		case 0: /* WrapNone*/
		case 1: /* WrapDHUK*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_AesEncrypt_WrappedKeyNr_WrapNone = 0,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_AesEncrypt_WrappedKeyNr_WrapDHUK = 1,
	brp_DHWCtrlLegacy_AesEncrypt_WrappedKeyNr_undefined = -1
} brp_DHWCtrlLegacy_AesEncrypt_WrappedKeyNr;
static inline bool brp_DHWCtrlLegacy_AesEncrypt_WrappedKeyNr_is_valid(int val) {
	switch (val) {
		case 0: /* WrapNone*/
		case 1: /* WrapDHUK*/
			return true;
		default:
			return false;
	}
}
/**
 * 
 */
typedef enum {
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_AesDecrypt_WrappedKeyNr_WrapNone = 0,
	/**
	 * 
	 */
	brp_DHWCtrlLegacy_AesDecrypt_WrappedKeyNr_WrapDHUK = 1,
	brp_DHWCtrlLegacy_AesDecrypt_WrappedKeyNr_undefined = -1
} brp_DHWCtrlLegacy_AesDecrypt_WrappedKeyNr;
static inline bool brp_DHWCtrlLegacy_AesDecrypt_WrappedKeyNr_is_valid(int val) {
	switch (val) {
		case 0: /* WrapNone*/
		case 1: /* WrapDHUK*/
			return true;
		default:
			return false;
	}
}
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */