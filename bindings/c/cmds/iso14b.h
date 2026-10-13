/**
 * @file
 * This command group implements the low-level ISO 14443-3 (Type B) commands according to the [ISO 14443-3 (Type B) standard](https://www.iso.org/standard/50942.html)
 * 
 * A PICC compliant to ISO 14443-3 (Type B) is always in one of five states: 
 * 
 *   1. Power off state 
 *   2. Idle state 
 *   3. Ready state 
 *   4. Active state 
 *   5. Halt state 
 * 
 * 
 * 
 * As long as the PICC is not present in the HF field of an antenna, it is in _power off_ state. When the PICC gets into the HF field, it will switch to _idle state_ automatically. The Iso14b.Request command scans for PICCs in idle state and returns necessary information about them to the host. Furthermore, this command will change the state of the detected PICCs to _ready state_. The Iso14b.Halt command can be used to set PICCs from ready state to _halt state_ so that they do not respond to conventional Iso14b.Request commands any longer. PICCs in halt state can only be reactivated by setting a special parameter flag in the Iso14b.Request command. 
 * 
 * From ready state, one or more PICCs may be switched to the _active state_ via the Iso14b.Attrib command. Not all PICCs support being in active state while other PICCs are at the same time: such PICCs need to be selected exclusively instead. 
 * 
 * Communication with the PICC by means of APDU exchanges is subject to the ISO 14443-4 standard which is explained in detail in the _Iso14L4_ command group documentation. Only PICCs in active state are able to execute ISO 14443-4 commands. For proprietary PICCs which are not compliant to the ISO 14443-4 standard, Iso14b.TransparentCmd should be used instead. It provides a raw communication channel between the application and the PICC, without any interpretation of the transferred data within the reader, thereby allowing to send/receive arbitrary request/response data to/from the PICC. 
 * 
 * After data exchange is completed, the PICC may automatically be switched to halt state so that it does not respond to any command which may follow. Depending on the PICC being compliant to the ISO 14443-4 standard or not, either a special command of the _Iso14L4_ command group or a proprietary card command transmitted via Iso14b.TransparentCmd have to be used for this purpose. PICCs in halt state can only be reactivated by setting as special parameter flag in the Iso14b.Request command.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_ISO14B_H__
#define __BRP_BALTECH_SDK_CMDS_ISO14B_H__
#include "../typedefs.h"
/**
 * No card in field of antenna or card in field of antenna does not match given VHL-file.
 */
#define BRP_Iso14b_ErrNoTag BRP_ERR_STATUS(0x1400, 0x01)
/**
 * More than one PICC answered in the same time slot and none of them could therefore be requested correctly. The Iso14b.Request command needs to be called again, maybe with more time slots.
 */
#define BRP_Iso14b_ErrCollision BRP_ERR_STATUS(0x1400, 0x02)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Authentication error.
 */
#define BRP_Iso14b_ErrAuth BRP_ERR_STATUS(0x1400, 0x03)
#endif  // BALTECH_SDK_INTERNAL
/**
 * General HF error.
 */
#define BRP_Iso14b_ErrHf BRP_ERR_STATUS(0x1400, 0x04)
/**
 * Bit error, parity error or frame error (start/stop bit).
 */
#define BRP_Iso14b_ErrFrame BRP_ERR_STATUS(0x1400, 0x07)
#ifdef BALTECH_SDK_INTERNAL
/**
 * CRC checksum error.
 */
#define BRP_Iso14b_ErrCrc BRP_ERR_STATUS(0x1400, 0x08)
#endif  // BALTECH_SDK_INTERNAL
/**
 * Error in communication with reader chip.
 */
#define BRP_Iso14b_ErrCom BRP_ERR_STATUS(0x1400, 0x10)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Error accessing EEPROM of the reader chip.
 */
#define BRP_Iso14b_ErrEeprom BRP_ERR_STATUS(0x1400, 0x21)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Reader chip does not support card type.
 */
#define BRP_Iso14b_ErrCardNotSupported BRP_ERR_STATUS(0x1400, 0x22)
#endif  // BALTECH_SDK_INTERNAL
/**
 * Either internal list of labels or response buffer full.
 */
#define BRP_Iso14b_ErrMem BRP_ERR_STATUS(0x1400, 0x23)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Command not supported by hardware.
 */
#define BRP_Iso14b_ErrHwNotSupported BRP_ERR_STATUS(0x1400, 0x24)
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	bool ExtendedATQB;
	bool ReqAll;
	brp_Iso14b_Request_TimeSlots TimeSlots;
	unsigned AFI;
	brp_Iso14b_Request_ValueList_Entry** ValueList;
	size_t* ValueList_len;
	brp_mempool *mempool;
} brp_Iso14b_Request_t;
/**
 * Scan for ISO 14443 (Type B) compliant PICCs in the field of the antenna. 
 * 
 * If a collision occurred in at least one time slot (signaled by status code ISO14B_COLLISION_ERR), this command needs to be called again with an increased number of time slots so that more PICCs can be detected. 
 * 
 * The ISO14B_MEM_ERR status code signals that more PICCs are available than can be handled with the buffer provided by the reader for BRP communication. The Iso14b.Halt command can be used to disable undesired PICCs before calling the Iso14b.Request command again. 
 * 
 * PICCs that have been returned by this command may subsequently be switched to the active state via the Iso14b.Attrib command.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ExtendedATQB** (in) If set, the PICC may send the extended ATQB format.
 *   - **ReqAll** (in) If set, all PICCs (even those in halt state) will be requested.
 *   - **TimeSlots** (in) Number of time slots which should be used for requesting PICCs. The more PICCs are expected, the higher this value should be. In one time slot, at most one PICC may answer.
 *   - **AFI** (in) _Application Family Id_ (AFI)   Possible values: 0x00 .. 0x8F   The high nibble specifies the _application family_ , the low nibble the _sub-family_. Use 0x00 when scanning operations should detect all PICCs regardless of their AFI.   Possible values for the application family:     * 0x0: all    * 0x1: transport    * 0x2: financial    * 0x3: identification    * 0x4: telecommunication    * 0x5: medical    * 0x6: multimedia    * 0x7: gaming    * 0x8: data storage    * 0x9-0xF: rfu     Possible values for sub-family:     * 0x0: all sub-families    * 0x1 .. 0xF: specified sub-family
 *   - **ValueList** (out) 
 *   - **ValueList_len** (out) Number of elements in **ValueList**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14b_Request(brp_protocol protocol, bool _input_ExtendedATQB, bool _input_ReqAll, brp_Iso14b_Request_TimeSlots _input_TimeSlots, unsigned _input_AFI, brp_Iso14b_Request_ValueList_Entry** ValueList, size_t* ValueList_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso14b_Request(brp_Iso14b_Request_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf PUPI;
	brp_Iso14b_Attrib_TR0 TR0;
	brp_Iso14b_Attrib_TR1 TR1;
	brp_Iso14b_Attrib_EOF_ EOF_;
	brp_Iso14b_Attrib_SOF SOF;
	brp_DivisorInteger DSI;
	brp_DivisorInteger DRI;
	brp_Iso14b_Attrib_FSDI FSDI;
	unsigned ProtocolType;
	unsigned CID;
	bool EnHLR;
	bool EnMBLI;
	bool EnCID;
	unsigned* AssignedCID;
	unsigned* MBLI;
	brp_buf* HLR;
	size_t* HLR_len;
	brp_mempool *mempool;
} brp_Iso14b_Attrib_t;
/**
 * Select the PICC with given _PUPI_ serial number for further communication. The desired PICC must have been reported by the Iso14b.Request command before. 
 * 
 * The parameters given in the _Param_ bit mask have to match both the supported communication parameters of the reader and of the current PICC, according to the _ProtInfo_ bit mask returned by the Iso14b.Request command. These parameters will be applied for all ISO 14443-4 APDUs that will be exchanged via the Iso14L4.ExchangeAPDU command. 
 * 
 * Furthermore, a unique communication channel ID (CID) has to be assigned, which identifies the PICC and which will also be needed by the ISO 14443-4 commands. 
 * 
 * Normally, there may be up to 14 PICCs in active state at the same time and each PICC will be uniquely identified by its CID. However, there are exist PICCs which do no support being assigned a CID. Only one of these PICCs may be in active state at the same time (along with other PICCs supporting the CID feature). The same restriction also holds for PICCs which are assigned a CID of 0x00 with this command.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PUPI** (in) _Pseudo-Unique PICC Identifier_ (PUPI), serial number of targeted PICC.
 *   - **TR0** (in) PICC's minimum delay before responding after the end of a command sent by PCD. The values introduced in this parameter need to be divided by the ISO 14443 subcarrier frequency (abbreviated as _fs_).
 *   - **TR1** (in) Minimum delay between subcarrier modulation start and beginning of data transmission. The values introduced in this parameter need to be divided by the ISO 14443 subcarrier frequency (abbreviated as _fs_).
 *   - **EOF_** (in) _End Of Frame_ (EOF) flag for sending data to reader.
 *   - **SOF** (in) _Start Of Frame_ (SOF) flag for sending data to reader.
 *   - **DSI** (in) _Divisor Send/Receive Integer_ (DSI/DRI)   This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 *   - **DRI** (in) _Divisor Send/Receive Integer_ (DSI/DRI)   This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 *   - **FSDI** (in) _Frame Size proximity coupling Device Integer_ (FSDI) value. This value is mapped to the Frame Size proximity coupling Device (FSD) value, which indicates the maximum frame size accepted by the PCD.   **The current Baltech reader supports FSD of at least up to 64 bytes (FSDI=0x05). It is not recommended to use a smaller FSDI. Future versions of the Baltech reader might support higher FSDI values.**
 *   - **ProtocolType** (in) Protocol Type supported by the PICC. Possible values:     * 0x00: PICC not compliant with ISO/IEC 14443-4    * 0x01: PICC compliant with ISO/IEC 14443-4    * 0x02-0x0F: rfu
 *   - **CID** (in) _Channel ID_ (CID) which should be assigned to this PICC. Possible values:     * 0x00: PICC will respond also to ISO 14443-4 commands with CID disabled    * 0x01-0x0E: valid CID value    * 0x0F-0xFF: rfu
 *   - **EnHLR** (in) If this flag is set, the _High Layer Response_ (HLR) variable will be returned by this command.
 *   - **EnMBLI** (in) If this flag is set, the _Maximum Buffer Length Index_ (MBLI) variable will be returned by this command.
 *   - **EnCID** (in) If this flag is set, the CID of the PICC will be returned by this command.
 *   - **AssignedCID** (out) _Channel ID_ (CID) which has been assigned to the PICC. If the PICC does not support the feature of being assigned a CID, 0x00 will be returned instead. Possible values:     * 0x00: PICC will respond also to ISO 14443-4 commands with CID disabled    * 0x01-0x0E: valid CID value    * 0x0F-0xFF: rfu
 *   - **MBLI** (out) _Maximum Buffer Length Index_ (MBLI) of PICC. This value is necessary to compute the _Maximum Buffer Length_ (MBL) value, describing the length of the PICC's internal buffer to receive chained frames. MBL is computed using MBLI using the following formula:   MBL = FSC * 2 ^ (MBLI-1)   The FSC variable is determined by the FSCI value returned by the Iso14b.Request command.   The amount of data transferred with one call of the Iso14L4.ExchangeAPDU command should never exceed MBL.   Possible values:     * 0x00: PICC does not provide MBLI    * 0x01-0x0F: valid MBLI value    * 0x10-0xFF: rfu
 *   - **HLR** (out) _Higher Layer Response_ (HLR) or PICC.   **The HLR is not available from PICCs fully compliant to the ISO 14443-3 standard.**
 *   - **HLR_len** (out) Length of **HLR** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14b_Attrib(brp_protocol protocol, brp_buf _input_PUPI, brp_Iso14b_Attrib_TR0 _input_TR0, brp_Iso14b_Attrib_TR1 _input_TR1, brp_Iso14b_Attrib_EOF_ _input_EOF_, brp_Iso14b_Attrib_SOF _input_SOF, brp_DivisorInteger _input_DSI, brp_DivisorInteger _input_DRI, brp_Iso14b_Attrib_FSDI _input_FSDI, unsigned _input_ProtocolType, unsigned _input_CID, bool _input_EnHLR, bool _input_EnMBLI, bool _input_EnCID, unsigned* AssignedCID, unsigned* MBLI, brp_buf* HLR, size_t* HLR_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso14b_Attrib(brp_Iso14b_Attrib_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf PUPI;
} brp_Iso14b_Halt_t;
/**
 * Switch the PICC with the given _PUPI_ serial number into halt state, so that it will not answer to further Iso14b.Request commands, except when the _ReqAll_ flag parameter of the Iso14b.Request command is set. The memory occupied by this PICC's information will also be freed, which makes it is available for future calls of the Iso14b.Request command. Use this command in order to deactivate some of the PICCs in case the Iso14b.ErrMem status code has been returned by the last call of Iso14b.Request. 
 * 
 * **This command only works for PICCs in ready state. For PICCs in active state, the Iso14L4.Deselect command should be used instead.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **PUPI** (in) _Pseudo-Unique PICC Identifier_ (PUPI) of the tag that should go into halt mode.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14b_Halt(brp_protocol protocol, brp_buf _input_PUPI);
#else
brp_errcode brp_Iso14b_Halt(brp_Iso14b_Halt_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool EnCRCRX;
	bool EnCRCTX;
	unsigned SendDataLen;
	unsigned Timeout;
	brp_DivisorInteger DSI;
	brp_DivisorInteger DRI;
	brp_buf SendData;
	size_t SendData_len;
	brp_buf* RecvData;
	size_t* RecvData_len;
	brp_mempool *mempool;
} brp_Iso14b_TransparentCmd_t;
/**
 * This command sends a data stream to a card and returns the communication status and the received card data stream to the host.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **EnCRCRX** (in) Enable CRC check over received data.
 *   - **EnCRCTX** (in) Enable CRC over transmitted data.
 *   - **SendDataLen** (in) Number of bytes to send.
 *   - **Timeout** (in) Timeout in ms between sending the last bit to the card and receiving the first bit from the card.
 *   - **DSI** (in) _Divisor Send/Receive Integer_ (DSI/DRI)   This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 *   - **DRI** (in) _Divisor Send/Receive Integer_ (DSI/DRI)   This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 *   - **SendData** (in) Data to transmit.   **Bits will always be transferred LSB first.**
 *   - **SendData_len** (in) Length of **SendData** (in bytes).
 *   - **RecvData** (out) Returned data.
 *   - **RecvData_len** (out) Length of **RecvData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14b_TransparentCmd(brp_protocol protocol, bool _input_EnCRCRX, bool _input_EnCRCTX, unsigned _input_SendDataLen, unsigned _input_Timeout, brp_DivisorInteger _input_DSI, brp_DivisorInteger _input_DRI, brp_buf _input_SendData, size_t _input_SendData_len, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso14b_TransparentCmd(brp_Iso14b_TransparentCmd_t params);
#endif
#endif
/**
 * @}
 */