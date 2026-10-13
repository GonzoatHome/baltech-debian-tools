/**
 * @file
 * This command group implements the low-level ISO 14443-4 commands according to the [ISO 14443-4 standard](http://www.iso.org/iso/home/store/catalogue_ics/catalogue_detail_ics.htm?csnumber=70172). While the ISO 14443-3 Type A and Type B standards define request and selection mechanisms for PICCs, the ISO 14443-4 standard defines a protocol capable of transferring so-called _application layer data units_ (APDUs) with previously selected labels. 
 * 
 * Please refer to the ISO 14443-3 (Type A) command group documentation or to the ISO 14443-3 (Type B) command group documentation for more information on how to put ISO 14443-3 (Type A) or ISO 14443-3 (Type B) PICCs into the _active state_. 
 * 
 * APDUs can be transmitted and received to/from a PICC using the Iso14L4.ExchangeAPDU command, provided the PICC is in active state. Before calling the Iso14L4.ExchangeAPDU command, the target PICC has to be selected using the Iso14L4.SetupAPDU command. The Iso14L4.SetupAPDU command furthermore enables to change the communication parameters of the reader to match the capabilities of the target PICC. These communication parameters apply to all following calls of the Iso14L4.ExchangeAPDU and Iso14L4.Deselect commands, until the Iso14L4.SetupAPDU command is called with different parameters. The Iso14L4.Deselect command is used to switch a PICC to halt state after exchange with this PICC has been completed. 
 * 
 * **PICCs can also be put to the halt state using the Iso14a.Halt command or the Iso14b.Halt command. However these commands only work for PICCs which are not in ISO 14443-4 mode (when considering Type A PICCs) or for PICCs in ready state, not in active state (when considering Type B PICCs). In other situations, the Iso14L4.Deselect command should be used.**
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_ISO14L4_H__
#define __BRP_BALTECH_SDK_CMDS_ISO14L4_H__
#include "../typedefs.h"
/**
 * No card in field of antenna or card in field of antenna does not match given VHL-file.
 */
#define BRP_Iso14L4_ErrNoTag BRP_ERR_STATUS(0x1600, 0x01)
/**
 * General HF error.
 */
#define BRP_Iso14L4_ErrHf BRP_ERR_STATUS(0x1600, 0x04)
/**
 * PICC corrupt or behaves unspecified.
 */
#define BRP_Iso14L4_ErrCard BRP_ERR_STATUS(0x1600, 0x05)
/**
 * Error in communication to reader chip.
 */
#define BRP_Iso14L4_ErrCom BRP_ERR_STATUS(0x1600, 0x10)
/**
 * Command and/or parameters invalid.
 */
#define BRP_Iso14L4_ErrCmd BRP_ERR_STATUS(0x1600, 0x23)
typedef struct {
	brp_protocol protocol;
	bool EnDefault;
	bool ToggleAB;
	bool EnNAD;
	bool EnCID;
	unsigned CID;
	unsigned NAD;
	brp_Iso14L4_SetupAPDU_FSCI FSCI;
	brp_Iso14L4_SetupAPDU_FWI FWI;
	brp_DivisorInteger DSI;
	brp_DivisorInteger DRI;
} brp_Iso14L4_SetupAPDU_t;
/**
 * Setup communication parameters and select a certain PICC for APDU exchange. The chosen settings will be applied to all subsequent calls of the Iso14L4.ExchangeAPDU and Iso14L4.Deselect commands. 
 * 
 * The _FrameParam_ and _Bitrate_ parameters have to be chosen according to the PICC's capabilities. 
 * 
 * In some cases, the _CID_ of the label to select has to be passed as a parameter. This is the case if the label supports the feature of being assigned a CID, and if a CID value has been previously assigned to the PICC using the Iso14a.RequestATS command (for ISO 14443 Type A labels) or by the or the Iso14b.Attrib command (for ISO 14443 Type B labels). Otherwise, the CID functionality should be disabled, by clearing the _EnCID_ flag. 
 * 
 * PICCs which do not support a CID (for which the returned _CID_ value from the Iso14a.RequestATS command, or from the Iso14b.Request command, is 0x00) will only respond to the Iso14L4.ExchangeAPDU and Iso14L4.Deselect commands if the CID functionality is disabled. 
 * 
 * A PICC, which supports a CID, will 
 * 
 *   1. respond to the Iso14L4.ExchangeAPDU and Iso14L4.Deselect commands only if the CID functionality is enabled and if the specified CID value matches the PICC's own CID value. 
 *   2. ignore the Iso14L4.ExchangeAPDU and Iso14L4.Deselect commands if a different CID value is specified. 
 *   3. also respond to Iso14L4.ExchangeAPDU and Iso14L4.Deselect commands with a disabled CID functionality, if its own CID value is 0. 
 * 
 * 
 * 
 * The _NAD_ parameter may be used to select a certain logical application (node) on the target PICC, if these are supported by this PICC.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **EnDefault** (in) If this flag is set, the default settings for _FrameParam_ and _Bitrate_ will be applied instead of the given parameter values.
 *   - **ToggleAB** (in) If this flag is set, communication with the PICC will be performed according to the ISO 14443 Type B standard. Otherwise, communication will be performed according to the ISO 14443 Type A standard.
 *   - **EnNAD** (in) Enables the _NAD_ functionality.
 *   - **EnCID** (in) Enables the _CID_ functionality.
 *   - **CID** (in) Specifies a _CID_ value, which shall be used for all subsequent calls of the Iso14L4.ExchangeAPDU and Iso14L4.Deselect commands. If _EnCID_ is not set, this parameter will be ignored and the CID functionality will be disabled.
 *   - **NAD** (in) Specifies a _NAD_ value, which shall be used for all subsequent calls of the Iso14L4.ExchangeAPDU command. If _EnNAD_ is not set, this parameter will be ignored and the NAD functionality will be disabled.
 *   - **FSCI** (in) _Frame Size proximity Card Integer_ (FSCI). This value is mapped to the Frame Size proximity Card (FSC) value, which indicates the maximum frame size accepted by the PICC. The possible FSC values (mapped to the FSCI index) are listed below.
 *   - **FWI** (in) _Frame Waiting time Integer_ (FWI). This value is necessary for calculation of the _Frame Waiting Time_ (FWT) value, representing the maximum time needed by the PICC between receiving a frame and sending the corresponding answer. FWT is calculated by:   FWT = (256 * 16 / 13.56 MHz) * 2 ^ FWI   The FWT values given here (mapped to the FWI index) are approximate.
 *   - **DSI** (in) _Divisor Send/Receive Integer_ (DSI/DRI)   This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 *   - **DRI** (in) _Divisor Send/Receive Integer_ (DSI/DRI)   This parameter is mapped to the _Divisor Send/Receive_ (DS/DI) value, which determines bit rate for sending data from PICC to PCD. The possible DS/DR values (mapped to the DSI/DRI index) are listed below.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14L4_SetupAPDU(brp_protocol protocol, bool _input_EnDefault, bool _input_ToggleAB, bool _input_EnNAD, bool _input_EnCID, unsigned _input_CID, unsigned _input_NAD, brp_Iso14L4_SetupAPDU_FSCI _input_FSCI, brp_Iso14L4_SetupAPDU_FWI _input_FWI, brp_DivisorInteger _input_DSI, brp_DivisorInteger _input_DRI);
#else
brp_errcode brp_Iso14L4_SetupAPDU(brp_Iso14L4_SetupAPDU_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf SendData;
	size_t SendData_len;
	brp_buf* RecvData;
	size_t* RecvData_len;
	brp_mempool *mempool;
} brp_Iso14L4_ExchangeAPDU_t;
/**
 * This command allows to transmit/receive _Application Protocol Data Units_ (APDUs) according to the ISO 14443-4 standard. 
 * 
 * The Iso14L4.SetupAPDU command must be run before Iso14L4.ExchangeAPDU in order to select the required PICC and set the appropriate communication parameters. If an error occurs during the execution of Iso14L4.ExchangeAPDU, it is mandatory to reselect the PICC. The Iso14L4.SetupAPDU command can be called anew if communication parameters with the PICC should be changed.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SendData** (in) APDU information which shall be sent to the PICC.
 *   - **SendData_len** (in) Length of **SendData** (in bytes).
 *   - **RecvData** (out) APDU response received from the PICC.
 *   - **RecvData_len** (out) Length of **RecvData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14L4_ExchangeAPDU(brp_protocol protocol, brp_buf _input_SendData, size_t _input_SendData_len, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso14L4_ExchangeAPDU(brp_Iso14L4_ExchangeAPDU_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Iso14L4_Deselect_t;
/**
 * This command switches one or multiple PICC(s) to halt state. 
 * 
 * **This command only works for certain types of PICCs (see command group description above). For other types of PICCs, the Iso14a.Halt command or the Iso14b.Halt command should be used instead.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14L4_Deselect(brp_protocol protocol);
#else
brp_errcode brp_Iso14L4_Deselect(brp_Iso14L4_Deselect_t params);
#endif
#endif
/**
 * @}
 */