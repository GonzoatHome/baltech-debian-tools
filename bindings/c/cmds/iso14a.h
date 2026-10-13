/**
 * @file
 * This command group implements the low-level ISO 14443-3 (Type A) commands according to the [ISO 14443-3 (Type A) standard](https://www.iso.org/standard/50942.html). 
 * 
 * A PICC compliant to ISO 14443-3 (Type A) is always in one of five states: 
 * 
 *   1. Power off state 
 *   2. Idle state 
 *   3. Ready state 
 *   4. Active state 
 *   5. Halt state 
 * 
 * 
 * 
 * As long as the PICC is not present in the HF field, it is in _power off_ state. When the PICC gets into the field of the antenna, it automatically switches to the _idle state_. Once the Iso14a.Request command is invoked, PICCs in idle state will switch to the _ready state_. From there, a certain PICC, only one at the same time, may be switched to the _active state_ via the Iso14a.Select command. This mechanism is identical for all ISO 14443 Type A PICCs. 
 * 
 * PICC communication by means of APDU exchanges is subject to the ISO 14443-4 standard which is explained in detail in the _Iso14L4_ command group documentation. Only PICCs which are compliant to ISO 14443-4 are able to execute commands transmitted according to ISO 14443-4, providing these PICCs are in the active state. However, before the first APDU exchange can be performed, the command Iso14a.RequestATS has to be executed in order to enable the ISO 14443-4 mode in the PICC. The command Iso14a.PerformPPS can be optionally invoked after Iso14a.RequestATS in order to increase communication speed. 
 * 
 * For proprietary PICCs that are not compliant to the [ISO 14443-4 standard](http://www.iso.org/iso/home/store/catalogue_tc/catalogue_detail.htm?csnumber=70172), the command Iso14a.TransparentCmd should be used for communication. It provides a raw communication channel between application and PICC, without any interpretation of the transferred data within the reader, and therewith allows to send/receive arbitrary command/response data to/from the PICC. 
 * 
 * After data exchange is completed, the PICC may be switched to the halt state so that it will not respond to any command which may follow. Depending on the PICC being in 14443-4 mode or not, either a special command of the ISO 14443-4 command group or the Iso14a.Halt command have to be used for this purpose. PICCs in halt state can only be reactivated by setting as special flag in the Iso14a.Request command.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_ISO14A_H__
#define __BRP_BALTECH_SDK_CMDS_ISO14A_H__
#include "../typedefs.h"
/**
 * No card in field of antenna or card in field of antenna does not match the given VHL-file.
 */
#define BRP_Iso14a_ErrNoTag BRP_ERR_STATUS(0x1300, 0x01)
/**
 * More than one PICC answered in the same time slot and none of them could therefore be requested correctly. 
 * 
 * **In case this status code is returned by the Iso14a.Request command, when two or more ISO 14443 Type A PICCs of different types (e.g. one Mifare Classic card and one Mifare DESFire card) are present in the HF field of the reader, the AQTA response will still be returned and the card selection procedure can be continued normally with the Iso14a.Select command.**
 */
#define BRP_Iso14a_ErrCollision BRP_ERR_STATUS(0x1300, 0x02)
/**
 * General HF error.
 */
#define BRP_Iso14a_ErrHf BRP_ERR_STATUS(0x1300, 0x04)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Key error (Only triggered by Mifare authentication).
 */
#define BRP_Iso14a_ErrKey BRP_ERR_STATUS(0x1300, 0x06)
#endif  // BALTECH_SDK_INTERNAL
/**
 * Bit error, Parity error or Frame error (start/stop bit).
 */
#define BRP_Iso14a_ErrFrame BRP_ERR_STATUS(0x1300, 0x07)
/**
 * CRC checksum error.
 */
#define BRP_Iso14a_ErrCrc BRP_ERR_STATUS(0x1300, 0x08)
/**
 * Error in communication with reader chip.
 */
#define BRP_Iso14a_ErrCom BRP_ERR_STATUS(0x1300, 0x10)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Error accessing EEPROM of the reader chip.
 */
#define BRP_Iso14a_ErrEeprom BRP_ERR_STATUS(0x1300, 0x21)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Reader chip does not support card type.
 */
#define BRP_Iso14a_ErrCardNotSupported BRP_ERR_STATUS(0x1300, 0x22)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Command not supported by hardware.
 */
#define BRP_Iso14a_ErrHwNotSupported BRP_ERR_STATUS(0x1300, 0x23)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
/**
 * Command has been interrupted.
 */
#define BRP_Iso14a_BreakErr BRP_ERR_STATUS(0x1300, 0x30)
#endif  // BALTECH_SDK_INTERNAL
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	bool ReqAll;
	brp_Iso14a_RequestLegacy_UIDSize* UIDSize;
	unsigned* Coll;
	unsigned* ProprietaryCoding;
} brp_Iso14a_RequestLegacy_t;
/**
 * This commands scans for ISO 14443-3 (Type A) compliant PICCs in the field of the antenna. 
 * 
 * If the _ReqAll_ parameter flag is set, both PICCs in idle state and PICCs in halt state will be switched to ready state. If this flag is not set, only PICCs in idle state will be switched to ready state. 
 * 
 * **Only PICCs in ready state may be selected via the Iso14a.Select command.**
 * 
 * **This command may return the Iso14a.ErrCollision status code when executed successfully, in case two or more PICCs of different types are present in the HF field of the reader. In this case, the selection PICC procedure can be carried out normally with the Iso14a.Select command.**
 * 
 * This command covers the commands REQA and WAKE-UP as specified by the ISO 14443-3 standard. 
 * 
 * **For new applications, the command Iso14a.Request should be used instead.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ReqAll** (in) If enabled, all PICCs (even those in halt state) will be requested.
 *   - **UIDSize** (out) Length of "Unique IDentifier" (UID). The UID may be either a fixed number or a number generated randomly by the PICC (and therefore not unique!).
 *   - **Coll** (out) If any bit set, a collision occurred
 *   - **ProprietaryCoding** (out) Proprietary coding.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_RequestLegacy(brp_protocol protocol, bool _input_ReqAll, brp_Iso14a_RequestLegacy_UIDSize* UIDSize, unsigned* Coll, unsigned* ProprietaryCoding);
#else
brp_errcode brp_Iso14a_RequestLegacy(brp_Iso14a_RequestLegacy_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned CascLev;
	unsigned BitCount;
	brp_buf PreSelSer;
	size_t PreSelSer_len;
	unsigned* SAK;
	brp_buf* Serial;
	size_t* Serial_len;
	brp_mempool *mempool;
} brp_Iso14a_Select_t;
/**
 * This command Performs the anti-collision and selection sequence of a PICC in the field of the antenna. The PICC has to be in ready state (see Iso14a.Request command) for this command to succeed. 
 * 
 * PICCs exist with three different lengths of serial numbers: 
 * 
 *   * Four bytes (single size) 
 *   * Seven bytes (double size) 
 *   * Ten bytes (triple size) 
 * 
 * 
 * 
 * In manual anti-collision mode, the Iso14a.Select command can only return 4 Bytes of the serial number at a time, in the _Serial_ returned variable. Iso14a.Select therefore needs to be called one, two or three times to read serial numbers of single, double or triple size, respectively. Each call of the Iso14a.Select command is associated to a specific _cascade level_ , specified by the _CascLev_ parameter. The first call of Iso14a.Select is associated to cascade level 1, the second call to cascade level 2, and the third call to cascade level 3. 
 * 
 * The fact that a serial number has not been completely returned by the Iso14a.Select command is indicated by a _cascade tag_ (CT, 0x88), in the first byte of the returned _Serial_ variable. In this case, the Iso14a.Select command needs to be called with the next higher cascade level (for instance _CascLev_ = 2 if Iso14a.Select was called with _CascLev_ = 1). The complete serial number of a PICC consists then of the concatenation of the (up to 3) returned values of _Serial_ , after removing the cascade tags(s) from these values. A completed selection flow is signaled by the _Casc_ flag in the _SAK_ byte and by the missing cascade tag in the returned serial number. 
 * 
 * Using the _PreSelSer_ parameter, the serial number (or an initial part of it) of a given PICC can be specified to be selected within a specific cascade level (up to four bytes) in order to speed up the anti-collision sequence. The CT must be included in _PreSelSer_ if it belongs to non-final parts of the serial number. 
 * 
 * For convenience reasons, an automatic anti-collision mode has been implemented. This mode can be activated by setting the _CascLev_ parameter to 0. In this case, the PICC can be selected with a single call of Iso14a.Select and the returned _Serial_ variable contains the complete serial number, without cascade tag(s). 
 * 
 * **In this case, cascade tags must be manually added to the _PreSelSer_ parameter to be able to use the preselection feature.**
 * 
 * This command combines the commands ANTICOLL and SELECT as specified in the ISO 14443-3 (Type A) standard.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CascLev** (in) Selects cascade level of anti-collision sequence:     * 0: complete serial number    * 1, 2 or 3: cascade level 1, 2 or 3
 *   - **BitCount** (in) Number of valid bits in _PreSelSer_ (0 - 96).
 *   - **PreSelSer** (in) Part of serial number (beginning at its head), which will be used for the preselection of a PICC.
 *   - **PreSelSer_len** (in) Length of **PreSelSer** (in bytes).
 *   - **SAK** (out) Select Acknowledge (SAK), according to the ISO 14443-3 (Type A) standard.
 *   - **Serial** (out) Serial number of selected label.
 *   - **Serial_len** (out) Length of **Serial** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_Select(brp_protocol protocol, unsigned _input_CascLev, unsigned _input_BitCount, brp_buf _input_PreSelSer, size_t _input_PreSelSer_len, unsigned* SAK, brp_buf* Serial, size_t* Serial_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso14a_Select(brp_Iso14a_Select_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Iso14a_Halt_t;
/**
 * Switch PICC to halt state. 
 * 
 * The PICC has to be selected before it may be switched to halt state. 
 * 
 * **This command only works for PICCs that are, though in active state, not in ISO 14443-4 mode. For such PICCs, the Iso14L4.Deselect command should be used instead.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_Halt(brp_protocol protocol);
#else
brp_errcode brp_Iso14a_Halt(brp_Iso14a_Halt_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Iso14a_RequestATS_FSDI FSDI;
	unsigned CID;
	brp_buf* ATS;
	size_t* ATS_len;
	brp_mempool *mempool;
} brp_Iso14a_RequestATS_t;
/**
 * This command requests the Answer to Select (ATS) of the PICC according to the ISO 14443-3 (Type A) standard. 
 * 
 * RequestATS has to be called by the PCD (reader) directly after a successful call of the Iso14a.Select command if 
 * 
 *   1. The selected PICC is ISO 14443-4 compliant (according to _SAK_ byte) and 
 *   2. communication as specified by ISO 14443-4 shall be performed via the Iso14L4.ExchangeAPDU command. 
 * 
 * 
 * 
 * Since it is possible to keep several PICCs in active state at the same time according to ISO 14443-4, a unique CID has to be assigned to each of them. However, if you only want to communicate with a single label at a given time, the value 0 should be assigned to the _CID_ variable. In this case, it is possible to call the Iso14L4.ExchangeAPDU command without bothering about CIDs. 
 * 
 * Please refer to the Iso14a.PerformPPS and Iso14L4.ExchangeAPDU command descriptions for more information about frame sizes and timing issues. 
 * 
 * After successful execution of this command, the communication parameters can be tuned with the Iso14a.PerformPPS command.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **FSDI** (in) _Frame Size proximity coupling Device Integer_ (FSDI) value. This value is mapped to the Frame Size proximity coupling Device (FSD) value, which indicates the maximum frame size accepted by the PCD.   **The current Baltech reader supports FSD of at least up to 64 bytes (FSDI=0x05). It is not recommended to use a smaller FSDI. Future versions of the Baltech reader might support higher FSDI values.**
 *   - **CID** (in) Channel ID which shall be assigned to this PICC. Possible values:     * 0x00: PICC will also respond to ISO 14443-4 commands with CID disabled. Should fit for most PICCs    * 0x01-0x0E: valid CID value.    * 0x0F-0xFF: RFU
 *   - **ATS** (out) Answer To Selection (ATS) of the PICC. This field has a variable length of up to 32 bytes. According to the ISO 14443-4 standard (chapter 5.2), it has the following format (bits not specified are RFU and have to be 0):    * TL byte. Specifies the length of the ATS in bytes. This includes TL up to Tk.    * T0 byte. Has the following meaning:      * Bit 0-3 (0x0F): FSCI = maximum accepted frame size of PICC. Has the same encoding as the FSDI parameter of this command or the FSCI parameter of the SetupAPDU command.      * Bit 4 (0x10): If 1, then TA(1) field is included in ATS.      * Bit 5 (0x20): If 1, then TB(1) field is included in ATS.      * Bit 6 (0x40): If 1, then TC(1) field is included in ATS.    * TA(1) byte (optional; see T0 byte). Specifies the values supported by the PICC of the DRI and DSI parameters of the PerformPPS command. If TA(1) is omitted, no values > Kbps106 are supported.      * Bit 0 (0x01): If 1, then _DRI_ may be _Kbps212_.     * Bit 1 (0x02): If 1, then _DRI_ may be _Kbps424_.     * Bit 2 (0x04): If 1, then _DRI_ may be _Kbps848_.     * Bit 4 (0x10): If 1, then _DSI_ may be _Kbps212_.     * Bit 5 (0x20): If 1, then _DSI_ may be _Kbps424_.     * Bit 6 (0x40): If 1, then _DSI_ may be _Kbps848_.     * Bit 7 (0x80): If 1, then _DSI_ and _DRI_ must be identical   * TB(1) byte (optional; see T0 byte). This byte contains the following values. If TB(1) is omitted, minimum values are assumed.      * Bit 0-3 (0x0F): SFGI (time PCD has to wait before sending packet after receiving ATS)     * Bit 4-7 (0xF0): FWI (timeout for response frame from the PICC) Both values specify a time value which has to be encoded according to the following table:      * 0: no delay needed     * 1: 0.6ms     * 2: 1.2ms     * 3: 2.4ms     * 4: 4.8ms     * 5: 9.7ms     * 6: 19.3ms     * 7: 38.7ms     * 8: 77.3ms     * 9: 154.7ms     * 10: 309.3ms     * 11: 618.6ms     * 12: 1237.3ms     * 13: 2474.5ms     * 14: 4949.0ms   * TC(1) byte (optional; see T0 byte). If TC(1) is omitted, CID is supported and NAD is not supported.      * Bit 0 (0x01): If 1, then NAD (node address) is supported     * Bit 1 (0x02): If 1, then CID (card identifier) is supported. This allows you to access multiple cards in parallel.   * T1 ... Tk: historical bytes (not defined in ISO14443-4 standard)
 *   - **ATS_len** (out) Length of **ATS** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_RequestATS(brp_protocol protocol, brp_Iso14a_RequestATS_FSDI _input_FSDI, unsigned _input_CID, brp_buf* ATS, size_t* ATS_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso14a_RequestATS(brp_Iso14a_RequestATS_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned CID;
	brp_DivisorInteger DSI;
	brp_DivisorInteger DRI;
} brp_Iso14a_PerformPPS_t;
/**
 * This command sets up the communication parameters for ISO 14443-4 commands. 
 * 
 * Iso14a.PerformPPS may be used to change the default communication parameters in order to achieve faster HF communication. This command has to be executed directly after the Iso14a.RequestATS command but it is not necessary to execute it at all. 
 * 
 * This command covers the PPS command as specified by ISO 14443-3 (type A). 
 * 
 * The _PPS1_ bit mask is only sent to the PICC if DSI or DRI differ from the current settings.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CID** (in) _Channel ID_ (CID) assigned to this PICC.   Possible values:     * 0x00: PICC will respond to ISO 14443-4 commands with CID disabled.    * 0x01-0x0E: valid CID value.    * 0x0F-0xFF: rfu.
 *   - **DSI** (in) _Divisor Send/Receive Integer_ (DSI/DRI)   This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 *   - **DRI** (in) _Divisor Send/Receive Integer_ (DSI/DRI)   This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_PerformPPS(brp_protocol protocol, unsigned _input_CID, brp_DivisorInteger _input_DSI, brp_DivisorInteger _input_DRI);
#else
brp_errcode brp_Iso14a_PerformPPS(brp_Iso14a_PerformPPS_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool ReqAll;
	brp_buf* ATQA;
	bool* Collision;
	brp_mempool *mempool;
} brp_Iso14a_Request_t;
/**
 * This commands scans for ISO 14443-3 (Type A) compliant PICCs in the field of the antenna. 
 * 
 * If the _ReqAll_ parameter flag is set, both PICCs in idle state and PICCs in halt state will be switched to ready state. If this flag is not set, only PICCs in idle state will be switched to ready state. 
 * 
 * **Only PICCs in ready state may be selected via the Iso14a.Select command.**
 * 
 * This command covers the commands REQA and WAKE-UP as specified by the ISO 14443-3 standard.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ReqAll** (in) If enabled, all PICCs (even those in halt state) will be requested.
 *   - **ATQA** (out) Answer to request of type A (ATQA), according to the ISO 14443-3 standard.
 *   - **Collision** (out) True if a Collision was detected.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_Request(brp_protocol protocol, bool _input_ReqAll, brp_buf* ATQA, bool* Collision, brp_mempool *mempool);
#else
brp_errcode brp_Iso14a_Request(brp_Iso14a_Request_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool ReqAll;
	unsigned FormatVersion;
	bool VasSupported;
	bool AuthUserRequested;
	unsigned TerminalTypeDataLength;
	unsigned TerminalType;
	brp_buf TCI;
	size_t TCI_len;
	brp_buf* ATQA;
	bool* Collision;
	brp_mempool *mempool;
} brp_Iso14a_RequestVasup_t;
/**
 * This commands scans for ISO 14443-3 (Type A) compliant PICCs in the field of the antenna and enhances polling with the VASUP-A command (required for ECP support). 
 * 
 * If the _ReqAll_ parameter flag is set, both PICCs in idle state and PICCs in halt state will be switched to ready state. If this flag is not set, only PICCs in idle state will be switched to ready state. 
 * 
 * **Only PICCs in ready state may be selected via the Iso14a.Select command.**
 * 
 * This command covers the commands REQA and WAKE-UP as specified by the ISO 14443-3 standard.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ReqAll** (in) If enabled, all PICCs (even those in halt state) will be requested.
 *   - **FormatVersion** (in) Based on the format version, the VASUP frame definition is given in the following parameters. Currently, only format version 2 is supported.
 *   - **VasSupported** (in) VAS is supported.
 *   - **AuthUserRequested** (in) Requests user authentication.
 *   - **TerminalTypeDataLength** (in) Length of terminal type data field (0-15)
 *   - **TerminalType** (in) Terminal type (MSB) and subtype (LSB) values defined by Apple
 *   - **TCI** (in) Terminal Capabilities Identifier (TCI) or terminal type data
 *   - **TCI_len** (in) Length of **TCI** (in bytes).
 *   - **ATQA** (out) Answer to request of type A (ATQA), according to the ISO 14443-3 standard.
 *   - **Collision** (out) True if a collision has been detected.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_RequestVasup(brp_protocol protocol, bool _input_ReqAll, unsigned _input_FormatVersion, bool _input_VasSupported, bool _input_AuthUserRequested, unsigned _input_TerminalTypeDataLength, unsigned _input_TerminalType, brp_buf _input_TCI, size_t _input_TCI_len, brp_buf* ATQA, bool* Collision, brp_mempool *mempool);
#else
brp_errcode brp_Iso14a_RequestVasup(brp_Iso14a_RequestVasup_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned BitCount;
	brp_buf PreSelectedSnr;
	brp_buf* SelectedSnr;
	brp_mempool *mempool;
} brp_Iso14a_Anticoll_t;
/**
 * This command performs an anti-collision sequence.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **BitCount** (in) Number of preselected bits.
 *   - **PreSelectedSnr** (in) Part of serial number which will be used for a preselection of cards.
 *   - **SelectedSnr** (out) Serial number of selected label.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_Anticoll(brp_protocol protocol, unsigned _input_BitCount, brp_buf _input_PreSelectedSnr, brp_buf* SelectedSnr, brp_mempool *mempool);
#else
brp_errcode brp_Iso14a_Anticoll(brp_Iso14a_Anticoll_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf Snr;
	unsigned* SAK;
} brp_Iso14a_SelectOnly_t;
/**
 * This command selects a PICC with a 4 Byte serial number.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Snr** (in) Serial number of card.
 *   - **SAK** (out) Select Acknowledge (SAK), according to the ISO 14443-3 (Type A) standard.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_SelectOnly(brp_protocol protocol, brp_buf _input_Snr, unsigned* SAK);
#else
brp_errcode brp_Iso14a_SelectOnly(brp_Iso14a_SelectOnly_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	bool EnMifBwProt;
	bool EnBitmode;
	bool EnCRCRX;
	bool EnCRCTX;
	bool ParityMode;
	bool EnParity;
	unsigned SendDataLen;
	unsigned Timeout;
	brp_DivisorInteger DSI;
	brp_DivisorInteger DRI;
	brp_buf SendData;
	size_t SendData_len;
	brp_buf* RcvData;
	size_t* RcvData_len;
	brp_mempool *mempool;
} brp_Iso14a_TransparentCmd_t;
/**
 * This command sends a data stream to a card and returns the communication status and the received card data stream to the host.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **EnMifBwProt** (in) Enables Mifare backwards compatibility protocol:     * Data bytes sent to the card are counted in Bytes, and bits 0..3 of _Mode_ bit mask are taken into account.    * Data bytes received from the card are counted in Bytes, 4 bit error codes (Mifare, Mifare+) are counted as one byte.    * First data byte in answer (byte 2) specifies data type: 0x00 for normal data, 0x01 for 4 bit error codes.
 *   - **EnBitmode** (in) Enable bit mode used for anti-collision sequence (send single bits instead of whole bytes). When this flag is set, the _EnParity_ , _ParityMode_ , _EnCRCTX_ , and _EnCRCRX_ flags will be automatically disabled by the reader and therefore will have no effect. _SendDataLen_ and _RcvDataLen_ are interpreted in bits instead of bytes.
 *   - **EnCRCRX** (in) Enable CRC check over received data.
 *   - **EnCRCTX** (in) Enable CRC check over transmitted data.
 *   - **ParityMode** (in) Toggle even/odd parity mode. ISO 14443 (Type A) uses odd parity. Possible values are 0 (even parity) and 1 (odd parity).
 *   - **EnParity** (in) Parity generation is enabled when this flag is set.
 *   - **SendDataLen** (in) Number of bytes to send.
 *   - **Timeout** (in) Timeout in ms between sending the last bit to the card and receiving the first bit from the card.
 *   - **DSI** (in) _Divisor Send/Receive Integer_ (DSI/DRI)   This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 *   - **DRI** (in) _Divisor Send/Receive Integer_ (DSI/DRI)   This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 *   - **SendData** (in) Data to send   **Bits will always be transferred LSB first.**
 *   - **SendData_len** (in) Length of **SendData** (in bytes).
 *   - **RcvData** (out) Returned data
 *   - **RcvData_len** (out) Length of **RcvData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_TransparentCmd(brp_protocol protocol, bool _input_EnMifBwProt, bool _input_EnBitmode, bool _input_EnCRCRX, bool _input_EnCRCTX, bool _input_ParityMode, bool _input_EnParity, unsigned _input_SendDataLen, unsigned _input_Timeout, brp_DivisorInteger _input_DSI, brp_DivisorInteger _input_DRI, brp_buf _input_SendData, size_t _input_SendData_len, brp_buf* RcvData, size_t* RcvData_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso14a_TransparentCmd(brp_Iso14a_TransparentCmd_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	bool EnHighBaudOld;
	bool EnParTx;
	unsigned SendDataLen;
	unsigned Timeout;
	brp_DivisorInteger DSI;
	brp_DivisorInteger DRI;
	brp_buf SendData;
	size_t SendData_len;
	unsigned* RecvDataLen;
	unsigned* CollisionPosition;
	brp_buf* RecvData;
	size_t* RecvData_len;
	brp_mempool *mempool;
} brp_Iso14a_TransparentCmdBitlen_t;
/**
 * This command is similar to _Iso14a.TransparentCmd_. The difference is that the length of data to send is given in bits instead of bytes.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **EnHighBaudOld** (in) Use high bit rates type A as specified in [ISO 14443-2 Amendment Part 2](https://www.iso.org/obp/ui/#iso:std:iso-iec:14443:-2:ed-2:v1:amd:2:v1:en).
 *   - **EnParTx** (in) If this bit is set in combination with _EnBitMode_ , parity generation in Tx direction (PCD to PICC) will be done by the PCD.
 *   - **SendDataLen** (in) Number of bits to send
 *   - **Timeout** (in) Timeout in ms between sending the last bit to the card and receiving the first bit from the card.
 *   - **DSI** (in) _Divisor Send/Receive Integer_ (DSI/DRI)   This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 *   - **DRI** (in) _Divisor Send/Receive Integer_ (DSI/DRI)   This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 *   - **SendData** (in) Data to send   **Bits will always be transferred LSB first.**
 *   - **SendData_len** (in) Length of **SendData** (in bytes).
 *   - **RecvDataLen** (out) Returned data length in bit.
 *   - **CollisionPosition** (out) Position of bit where first collision occurred.
 *   - **RecvData** (out) Data to send   **Bits will always be transferred LSB first.**
 *   - **RecvData_len** (out) Length of **RecvData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_TransparentCmdBitlen(brp_protocol protocol, bool _input_EnHighBaudOld, bool _input_EnParTx, unsigned _input_SendDataLen, unsigned _input_Timeout, brp_DivisorInteger _input_DSI, brp_DivisorInteger _input_DRI, brp_buf _input_SendData, size_t _input_SendData_len, unsigned* RecvDataLen, unsigned* CollisionPosition, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso14a_TransparentCmdBitlen(brp_Iso14a_TransparentCmdBitlen_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
#endif
/**
 * @}
 */