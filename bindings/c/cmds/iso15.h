/**
 * @file
 * The _ISO 15693_ command group contains commands for communication with labels compatible to the ISO 15693 standard. This document does not replace the [official ISO 15693 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467). It is rather meant to be used in combination with it. 
 * 
 * The Baltech reader understands the so-called _mandatory_ and _optional commands_ as well as _custom commands_ for some label types. However, custom commands are not documented in this page. 
 * 
 * In order to communicate with an ISO 15693 compatible label, it is necessary to know its UID. Every command sent to the reader uses the UID to address the label. This is very important to guarantee that only one label reacts to the command. A command may also be executed without specifying a UID if it is certain that only one label is present in the reader's HF field. However, it is most of the time difficult to know how many labels are present within the antenna's field at a given time. Thus, it is advisable to execute the Iso15.GetUIDList command before starting to communicate with the label. This command returns a list of available labels along with their UIDs. 
 * 
 * The Iso15.StayQuiet command may be used to set a certain label to _quiet-state_ , i.e. to keep the label from answering to subsequent calls of the Iso15.GetUIDList command. This may be useful when a label has been fully processed and the application wants to scan for other labels that may also be available in the reader's HF field at the same time. The opposite command which sets a label back to _ready-state_ is Iso15.ResetToReady. The addressed label will then answer again to subsequent calls of Iso15.GetUIDList. 
 * 
 * Once the UID of a specific label is known (e.g. by executing Iso15.GetUIDList), there are three options to communicate with this label. The communication mode needs to be chosen using the Iso15.SetMode command. All subsequent commands performing communication with the label will then use this mode. If a different label must be addressed, Iso15.SetMode has to be called again. The three possible communication modes are: 
 * 
 *   * _Addressed mode_ : The 8 byte UID of the label is used to address a distinct label. In this mode, the UID is included in each command frame sent to the label. 
 *   * _Selected mode_ : A label in selected mode responds to commands received from the reader without the need to transfer the UID in each command. Attention: This mode is optional and not supported by all types of ISO 15693 labels. 
 *   * _Unaddressed mode_ : If it is sure that only one label is in the field of the antennas you may execute commands in the unaddressed mode as well. Attention: All labels currently in the reader's antenna field will respond to commands when using this mode. 
 * 
 * 
 * 
 * The memory of labels compliant to ISO 15693 is organized as a sequence of blocks where the block-size is fixed for a certain type of label. The default length of a block is four byte. Each block can be directly accessed and the available commands for data exchange, mainly ReadBlock and WriteBlock, are generally designed to handle one block per call. GetSystemInformation retrieves general information about a specific label.
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_ISO15_H__
#define __BRP_BALTECH_SDK_CMDS_ISO15_H__
#include "../typedefs.h"
/**
 * No label in field of antenna.
 */
#define BRP_Iso15_ErrNoTag BRP_ERR_STATUS(0x2100, 0x01)
/**
 * This status code is triggered by two events: 
 * 
 *   * A collision between two or more labels occurred. 
 *   * DSFID different - cannot resolve collision.
 */
#define BRP_Iso15_ErrCollision BRP_ERR_STATUS(0x2100, 0x02)
/**
 * General HF Error.
 */
#define BRP_Iso15_ErrHf BRP_ERR_STATUS(0x2100, 0x04)
/**
 * Label status error.
 */
#define BRP_Iso15_ErrLabel BRP_ERR_STATUS(0x2100, 0x05)
/**
 * Error in communication to reader chip.
 */
#define BRP_Iso15_ErrCom BRP_ERR_STATUS(0x2100, 0x10)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Command and/or parameters invalid.
 */
#define BRP_Iso15_ErrCmd BRP_ERR_STATUS(0x2100, 0x20)
#endif  // BALTECH_SDK_INTERNAL
/**
 * Reader chip does not support label type parameters.
 */
#define BRP_Iso15_ErrParamNotSupported BRP_ERR_STATUS(0x2100, 0x23)
/**
 * Either internal list of labels or response buffer full.
 */
#define BRP_Iso15_ErrMem BRP_ERR_STATUS(0x2100, 0x24)
/**
 * The blocks requested are not equal in size (Read multiple blocks).
 */
#define BRP_Iso15_ErrLabelBlocksize BRP_ERR_STATUS(0x2100, 0x25)
#ifdef BALTECH_SDK_INTERNAL
/**
 * Command not supported by hardware.
 */
#define BRP_Iso15_ErrHwNotSupported BRP_ERR_STATUS(0x2100, 0x26)
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	bool ModulationIndex;
	bool TXMode;
	bool HighDataRate;
	bool DualSubcarrier;
} brp_Iso15_SetParam_t;
/**
 * This command configures the reader chip. If a parameter is not supported, a status message is returned.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ModulationIndex** (in) Toggle modulation index 100% (0) /10% (1)
 *   - **TXMode** (in) Toggle 1 out of 256 (0) / 1 out of 4 (1) TX mode
 *   - **HighDataRate** (in) Toggle low (0) /high (1) data rate VICC
 *   - **DualSubcarrier** (in) Toggle single (0) /dual (1) subcarrier VICC
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_SetParam(brp_protocol protocol, bool _input_ModulationIndex, bool _input_TXMode, bool _input_HighDataRate, bool _input_DualSubcarrier);
#else
brp_errcode brp_Iso15_SetParam(brp_Iso15_SetParam_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool* ModulationIndex;
	bool* TXMode;
	bool* HighDataRate;
	bool* DualSubcarrier;
} brp_Iso15_GetParam_t;
/**
 * This command reads the configuration of the reader chip.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ModulationIndex** (out) Toggle modulation index 100% (0) /10% (1)
 *   - **TXMode** (out) Toggle 1 out of 256 (0) / 1 out of 4 (1) TX mode
 *   - **HighDataRate** (out) Toggle low (0) /high (1) data rate VICC
 *   - **DualSubcarrier** (out) Toggle single (0) /dual (1) subcarrier VICC
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_GetParam(brp_protocol protocol, bool* ModulationIndex, bool* TXMode, bool* HighDataRate, bool* DualSubcarrier);
#else
brp_errcode brp_Iso15_GetParam(brp_Iso15_GetParam_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool EnAFI;
	bool NextBlock;
	bool AutoQuiet;
	bool EnDSFID;
	bool En16Slots;
	unsigned AFI;
	unsigned* More;
	brp_Iso15_GetUIDList_Labels_Entry** Labels;
	size_t* Labels_len;
	brp_mempool *mempool;
} brp_Iso15_GetUIDList_t;
/**
 * This command scans for ISO 15693 labels which are in the field of the readers antenna and which are not in _quiet-state_. The list of UIDs is returned in the response frame. Furthermore, the DSFID is send back if the _DSFID_ flag in _Mode_ is set. 
 * 
 * If the _More_ response value is different from zero, there are more tags to scan, and Iso15.GetUIDList has to be called again with the _NextBlock_ flag set to get the rest of the labels which have not been transferred within this frame. 
 * 
 * To optimize the label scanning time, the reader should be told if there are many labels (more than 2 or 3) in the antenna's field. In this case, the _En16Slots_ flag should be set. This bit will tell Iso15.GetUIDList to send the inventory with 16 time slots instead of one. 
 * 
 * Furthermore the _Autoquiet_ flag can be set to put every label into _quiet-state_ after a successful scan. This will result in a kind of incremental behaviour from Iso15.GetUIDList since after the first successful Iso15.GetUIDList call, all following Iso15.GetUIDList calls will only return labels which came into the field of the antenna after the last call.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **EnAFI** (in) EnAFI (bool): AFI byte shall be transmitted
 *   - **NextBlock** (in) NextBlock (bool): Scan for additional labels in HF field
 *   - **AutoQuiet** (in) AutoQuiet (bool): Enable auto-quiet mode
 *   - **EnDSFID** (in) DSFID (bool): Enable DSFID see response
 *   - **En16Slots** (in) 16Slots (bool): Enable 16 time-slots
 *   - **AFI** (in) Application Family Identifier. EnAFI flag in _Mode_ Byte has to be set, if AFI shall be used.
 *   - **More** (out) If set, then more than Num labels are in the field of antenna.
 *   - **Labels** (out) 
 *   - **Labels_len** (out) Number of elements in **Labels**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_GetUIDList(brp_protocol protocol, bool _input_EnAFI, bool _input_NextBlock, bool _input_AutoQuiet, bool _input_EnDSFID, bool _input_En16Slots, unsigned _input_AFI, unsigned* More, brp_Iso15_GetUIDList_Labels_Entry** Labels, size_t* Labels_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso15_GetUIDList(brp_Iso15_GetUIDList_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_Iso15_SetMode_Mode Mode;
	brp_buf UID;
} brp_Iso15_SetMode_t;
/**
 * This command configures the mode to address a label. 
 * 
 *   * _Unaddressed mode_ : The following label commands are sent to the label without an UID (broadcast). This implies that not more than one label should be in the antenna's field because every label is responding in this mode which would result in a collision. 
 *   * _Addressed mode_ : The following label commands are sent to the label including the UID given in _UID_. To talk to one distinct label among others, the Iso15.SetMode command has to be called with a value of 0x01 in the _Mode_ byte before execution of other label commands. 
 *   * _Selected mode_ : Useful if a lot of operations need to be performed with the same label since the UID is not transferred to the label over and over again. A Iso15.SetMode command with _Mode_ 0x02 implicitly executes a _Select_ command with the corresponding UID as parameter (see the [ISO 1593-3 standard](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467) for details). A previously selected label will be deselected automatically if a Iso15.SetMode command with Mode 0x02 and a different UID or a Iso15.SetMode command with Mode unequal 0x02 is executed. If a Iso15.SetMode command with Mode 0x02 fails, the reader remains in the unaddressed mode. 
 * 
 * 
 * 
 * **Please be aware that not all label types support all modes.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Mode** (in) Communication mode for label addressing.
 *   - **UID** (in) Unique ID of label; only for addressed -/selected mode.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_SetMode(brp_protocol protocol, brp_Iso15_SetMode_Mode _input_Mode, brp_buf _input_UID);
#else
brp_errcode brp_Iso15_SetMode(brp_Iso15_SetMode_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_Iso15_StayQuiet_t;
/**
 * This command puts a label into the _quiet-state_. This command shall always be executed in addressed mode (see the Iso15.SetMode command). After executing this command, the label will not response to any Iso15.GetUIDList command until its state machine is reset (either by a physical HF-reset (i.e. switching off the field of the antenna or taking the label out of the field) or by executing the commands Iso15.ResetToReady or Iso15.SetMode (using selected mode).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_StayQuiet(brp_protocol protocol);
#else
brp_errcode brp_Iso15_StayQuiet(brp_Iso15_StayQuiet_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned BlockID;
	unsigned BlockNum;
	bool EnBlockSec;
	unsigned* LabelStat;
	unsigned* BlockLen;
	brp_Iso15_ReadBlock_Data_Entry** Data;
	size_t* Data_len;
	brp_mempool *mempool;
} brp_Iso15_ReadBlock_t;
/**
 * **For new applications please use Iso15.WriteMultipleBlocks as this command is deprecated and may be removed in future.**
 * 
 * This command reads one or multiple blocks from a label. 
 * 
 * This command implements the "read single block" and "read multiple blocks" optional commands from the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **BlockID** (in) ID of first block to read.
 *   - **BlockNum** (in) Number of blocks to read:     * 0x00: 1 block    * 0xFF: 256 blocks
 *   - **EnBlockSec** (in) Enable/Disable _BlockSecStat_ Byte in response frame.
 *   - **LabelStat** (out) Status code returned from label. The following bytes will only be returned, if _LabelStat_ is OK.
 *   - **BlockLen** (out) Amount of bytes to read in one block.
 *   - **Data** (out) 
 *   - **Data_len** (out) Number of elements in **Data**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_ReadBlock(brp_protocol protocol, unsigned _input_BlockID, unsigned _input_BlockNum, bool _input_EnBlockSec, unsigned* LabelStat, unsigned* BlockLen, brp_Iso15_ReadBlock_Data_Entry** Data, size_t* Data_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso15_ReadBlock(brp_Iso15_ReadBlock_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned BlockID;
	unsigned BlockNum;
	unsigned BlockLen;
	bool OptionFlag;
	brp_buf* Data;
	size_t Data_len;
	unsigned* LabelStat;
} brp_Iso15_WriteBlock_t;
/**
 * **For new applications please use Iso15.WriteMultipleBlocks as this command is deprecated and may be removed in future.**
 * 
 * This command writes one or multiple blocks to a label. 
 * 
 * This command implements the "write multiple blocks" optional commands from the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **BlockID** (in) ID of first block to write.
 *   - **BlockNum** (in) Number of blocks to write:     * 0x00: 1 block    * 0xFF: 256 blocks
 *   - **BlockLen** (in) Length of each block (The length of the first block is considered to be representative).
 *   - **OptionFlag** (in) Option Flag according to the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 *   - **Data** (in) 
 *   - **Data_len** (in) Number of elements in **Data**.
 *   - **LabelStat** (out) Status code returned from label.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_WriteBlock(brp_protocol protocol, unsigned _input_BlockID, unsigned _input_BlockNum, unsigned _input_BlockLen, bool _input_OptionFlag, brp_buf* _input_Data, size_t _input_Data_len, unsigned* LabelStat);
#else
brp_errcode brp_Iso15_WriteBlock(brp_Iso15_WriteBlock_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned BlockID;
	bool OptionFlag;
	unsigned* LabelStat;
} brp_Iso15_LockBlock_t;
/**
 * This command permanently locks the block with ID _BlockID_. 
 * 
 * **This command is an _optional command_ .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **BlockID** (in) ID of the block to be locked.
 *   - **OptionFlag** (in) Option Flag according to the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 *   - **LabelStat** (out) Status code returned from label. The following Bytes will only be returned, if _LabelStat_ is OK.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_LockBlock(brp_protocol protocol, unsigned _input_BlockID, bool _input_OptionFlag, unsigned* LabelStat);
#else
brp_errcode brp_Iso15_LockBlock(brp_Iso15_LockBlock_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned* LabelStat;
} brp_Iso15_ResetToReady_t;
/**
 * This command puts a label into _ready-state_ , according to the VICC state transition diagram from the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467). 
 * 
 * **This command is an _optional command_ .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **LabelStat** (out) Status code returned from label. The following Bytes will only be returned, if _LabelStat_ is OK.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_ResetToReady(brp_protocol protocol, unsigned* LabelStat);
#else
brp_errcode brp_Iso15_ResetToReady(brp_Iso15_ResetToReady_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned AFI;
	bool OptionFlag;
	unsigned* LabelStat;
} brp_Iso15_WriteAFI_t;
/**
 * This commands writes the _AFI_ value into the label's memory. 
 * 
 * **This commands is an _optional command_ .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **AFI** (in) AFI
 *   - **OptionFlag** (in) Option Flag according to the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 *   - **LabelStat** (out) Status code returned from label. The following Bytes will only be returned, if _LabelStat_ is OK.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_WriteAFI(brp_protocol protocol, unsigned _input_AFI, bool _input_OptionFlag, unsigned* LabelStat);
#else
brp_errcode brp_Iso15_WriteAFI(brp_Iso15_WriteAFI_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool OptionFlag;
	unsigned* LabelStat;
} brp_Iso15_LockAFI_t;
/**
 * This command locks the _AFI_ value permanently into the reader's memory. 
 * 
 * **This commands is an _optional command_ .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **OptionFlag** (in) Option Flag according to the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 *   - **LabelStat** (out) Status code returned from label. The following Bytes will only be returned, if _LabelStat_ is OK.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_LockAFI(brp_protocol protocol, bool _input_OptionFlag, unsigned* LabelStat);
#else
brp_errcode brp_Iso15_LockAFI(brp_Iso15_LockAFI_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned DSFID;
	bool OptionFlag;
	unsigned* LabelStat;
} brp_Iso15_WriteDSFID_t;
/**
 * This commands writes the _DSFID_ value into the label's memory. 
 * 
 * **This commands is an _optional command_ .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **DSFID** (in) DSFID
 *   - **OptionFlag** (in) Option Flag according to the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 *   - **LabelStat** (out) Status code returned from label. The following Bytes will only be returned, if _LabelStat_ is OK.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_WriteDSFID(brp_protocol protocol, unsigned _input_DSFID, bool _input_OptionFlag, unsigned* LabelStat);
#else
brp_errcode brp_Iso15_WriteDSFID(brp_Iso15_WriteDSFID_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool OptionFlag;
	unsigned* LabelStat;
} brp_Iso15_LockDSFID_t;
/**
 * This command locks the _DSFID_ value permanently into the reader's memory. 
 * 
 * **This commands is an _optional command_ .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **OptionFlag** (in) Option Flag according to the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 *   - **LabelStat** (out) Status code returned from label. The following Bytes will only be returned, if _LabelStat_ is OK.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_LockDSFID(brp_protocol protocol, bool _input_OptionFlag, unsigned* LabelStat);
#else
brp_errcode brp_Iso15_LockDSFID(brp_Iso15_LockDSFID_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned* LabelStat;
	bool* EnICRef;
	bool* EnMemSize;
	bool* EnAFI;
	bool* EnDSFID;
	brp_buf* SNR;
	unsigned* DSFID;
	unsigned* AFI;
	unsigned* BlockNum;
	unsigned* BlockSize;
	unsigned* ICRef;
	brp_mempool *mempool;
} brp_Iso15_GetSystemInformation_t;
/**
 * This command gets the system information of a VICC. 
 * 
 * **This commands is an _optional command_ .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **LabelStat** (out) Status code returned from label. The following Bytes will only be returned, if _LabelStat_ is OK.
 *   - **EnICRef** (out) IC reference present / supported.
 *   - **EnMemSize** (out) Memory size present / supported.
 *   - **EnAFI** (out) AFI present / supported.
 *   - **EnDSFID** (out) DSFID present / supported.
 *   - **SNR** (out) 
 *   - **DSFID** (out) 
 *   - **AFI** (out) 
 *   - **BlockNum** (out) Number of blocks - 1 (e.g. _BlockNum_ = 0 means 1 block is present).
 *   - **BlockSize** (out) Block size - 1 in Byte (e.g. _BlockSize_ = 0 means a block size of 1 Byte).
 *   - **ICRef** (out) 
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_GetSystemInformation(brp_protocol protocol, unsigned* LabelStat, bool* EnICRef, bool* EnMemSize, bool* EnAFI, bool* EnDSFID, brp_buf* SNR, unsigned* DSFID, unsigned* AFI, unsigned* BlockNum, unsigned* BlockSize, unsigned* ICRef, brp_mempool *mempool);
#else
brp_errcode brp_Iso15_GetSystemInformation(brp_Iso15_GetSystemInformation_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned BlockID;
	unsigned BlockNum;
	unsigned* LabelStat;
	unsigned** BlockStat;
	size_t* BlockStat_len;
	brp_mempool *mempool;
} brp_Iso15_GetSecurityStatus_t;
/**
 * This command retrieves the block security status of a label. 
 * 
 * **This command is an _optional command_ .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **BlockID** (in) ID of first block to read.
 *   - **BlockNum** (in) Number of blocks to write:     * 0x00: 1 block    * 0xFF: 256 blocks
 *   - **LabelStat** (out) Status code returned from label. The following Bytes will only be returned, if _LabelStat_ is OK.
 *   - **BlockStat** (out) 
 *   - **BlockStat_len** (out) Number of elements in **BlockStat**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_GetSecurityStatus(brp_protocol protocol, unsigned _input_BlockID, unsigned _input_BlockNum, unsigned* LabelStat, unsigned** BlockStat, size_t* BlockStat_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso15_GetSecurityStatus(brp_Iso15_GetSecurityStatus_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned Cmd;
	unsigned Opt;
	unsigned MFC;
	unsigned TO;
	brp_buf RequestData;
	size_t RequestData_len;
	unsigned* LabelStat;
	brp_buf* ResponseData;
	size_t* ResponseData_len;
	brp_mempool *mempool;
} brp_Iso15_CustomCommand_t;
/**
 * This command executes any ISO 15693 manufacturer proprietary commands, so-called _custom-commands_. 
 * 
 * By default, the same label is addressed as in the last regular ISO 15693 command.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Cmd** (in) Custom ISO 15693 command code.
 *   - **Opt** (in) Enables the usage of option flag Byte.
 *   - **MFC** (in) Manufacturer Code.
 *   - **TO** (in) Timeout in ms for label answer after it has fully received the command.
 *   - **RequestData** (in) Data block (request).
 *   - **RequestData_len** (in) Length of **RequestData** (in bytes).
 *   - **LabelStat** (out) Status code returned from label. The following bytes will only be returned, if _LabelStat_ is OK.
 *   - **ResponseData** (out) Data block (response).
 *   - **ResponseData_len** (out) Length of **ResponseData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_CustomCommand(brp_protocol protocol, unsigned _input_Cmd, unsigned _input_Opt, unsigned _input_MFC, unsigned _input_TO, brp_buf _input_RequestData, size_t _input_RequestData_len, unsigned* LabelStat, brp_buf* ResponseData, size_t* ResponseData_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso15_CustomCommand(brp_Iso15_CustomCommand_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned BlockID;
	bool EnBlockSec;
	unsigned* LabelStat;
	brp_buf* Payload;
	size_t* Payload_len;
	brp_mempool *mempool;
} brp_Iso15_ReadSingleBlock_t;
/**
 * This command reads a single block from a label. 
 * 
 * This command implements the "read single block" optional command from the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **BlockID** (in) ID of block to read.
 *   - **EnBlockSec** (in) Disable _BlockSecStat_ byte in answer.
 *   - **LabelStat** (out) Status code returned from label. The following bytes will only be returned, if _LabelStat_ is OK.
 *   - **Payload** (out) Payload data which are stored in the requested block.
 *   - **Payload_len** (out) Length of **Payload** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_ReadSingleBlock(brp_protocol protocol, unsigned _input_BlockID, bool _input_EnBlockSec, unsigned* LabelStat, brp_buf* Payload, size_t* Payload_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso15_ReadSingleBlock(brp_Iso15_ReadSingleBlock_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned BlockID;
	unsigned BlockLen;
	bool OptionFlag;
	brp_buf SingleBlockData;
	size_t SingleBlockData_len;
	unsigned* LabelStat;
} brp_Iso15_WriteSingleBlock_t;
/**
 * This command writes a single block to a label. 
 * 
 * This command implements the "write single block" optional command from the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **BlockID** (in) ID of block to write
 *   - **BlockLen** (in) Length of each block (The length of the first block is considered to be representative).
 *   - **OptionFlag** (in) Option Flag according to the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 *   - **SingleBlockData** (in) Block to write.
 *   - **SingleBlockData_len** (in) Length of **SingleBlockData** (in bytes).
 *   - **LabelStat** (out) Status code returned from label. The following bytes will only be returned, if _LabelStat_ is OK.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_WriteSingleBlock(brp_protocol protocol, unsigned _input_BlockID, unsigned _input_BlockLen, bool _input_OptionFlag, brp_buf _input_SingleBlockData, size_t _input_SingleBlockData_len, unsigned* LabelStat);
#else
brp_errcode brp_Iso15_WriteSingleBlock(brp_Iso15_WriteSingleBlock_t params);
#endif
#ifdef BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	bool EnRxWait;
	bool EnCRCRX;
	bool EnCRCTX;
	unsigned Len;
	unsigned Timeout;
	brp_buf Data;
	unsigned RxWait;
	brp_buf* LabelData;
	size_t* LabelData_len;
	brp_mempool *mempool;
} brp_Iso15_TransparentCmdLegacy_t;
/**
 * **For new applications please use Iso15.TransparentCmd as this command is deprecated and may be removed in future.**
 * 
 * This command sends a data stream to a label and returns the communication status and the received label data stream to the host. If no bytes are sent and the CRC check is disabled, only an EOF is sent to the label. After execution of this command, the _Mode_ parameter is reset to default. 
 * 
 * **Please be aware that the _flag_ Byte (see the[ ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467) , 2001 p.9) is not generated by the reader. This flag has to be transmitted as part of the _data_ string.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **EnRxWait** (in) If _true_ , param _RxWait_ is transmitted to the reader.
 *   - **EnCRCRX** (in) Enable CRC check over received data.
 *   - **EnCRCTX** (in) Enable CRC over transmitted data.
 *   - **Len** (in) Number of bytes to send.
 *   - **Timeout** (in) Timeout in ms between sending last bit to label and receiving first bit from label.
 *   - **Data** (in) **Length is greater than 0! It was set to zero to provide length information**
 *   - **RxWait** (in) After data transmission to the label, the receiver is delayed for a _RxWait_ time, measured in Rx bitclock steps. After execution of the command, _RxWait_ is reset to the default value.
 *   - **LabelData** (out) 
 *   - **LabelData_len** (out) Length of **LabelData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_TransparentCmdLegacy(brp_protocol protocol, bool _input_EnRxWait, bool _input_EnCRCRX, bool _input_EnCRCTX, unsigned _input_Len, unsigned _input_Timeout, brp_buf _input_Data, unsigned _input_RxWait, brp_buf* LabelData, size_t* LabelData_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso15_TransparentCmdLegacy(brp_Iso15_TransparentCmdLegacy_t params);
#endif
#endif  // BALTECH_SDK_INTERNAL
typedef struct {
	brp_protocol protocol;
	unsigned FirstBlockId;
	brp_Iso15_WriteMultipleBlocks_WriteBlocks_Entry* WriteBlocks;
	size_t WriteBlocks_len;
	bool OptionFlag;
	unsigned* LabelStat;
} brp_Iso15_WriteMultipleBlocks_t;
/**
 * Sends the "WriteMultipleBlocks" to the card to store the data passed in _WriteBlocks_ to the data blocks of the presented card starting at block with id _Blockid_. For more information about this command please refer to the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **FirstBlockId** (in) Index (starting at 0) of first block to write.
 *   - **WriteBlocks** (in) 
 *   - **WriteBlocks_len** (in) Number of elements in **WriteBlocks**.
 *   - **OptionFlag** (in) Option Flag according to the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 *   - **LabelStat** (out) Status code returned from label.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_WriteMultipleBlocks(brp_protocol protocol, unsigned _input_FirstBlockId, brp_Iso15_WriteMultipleBlocks_WriteBlocks_Entry* _input_WriteBlocks, size_t _input_WriteBlocks_len, bool _input_OptionFlag, unsigned* LabelStat);
#else
brp_errcode brp_Iso15_WriteMultipleBlocks(brp_Iso15_WriteMultipleBlocks_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned FirstBlockId;
	unsigned BlockCount;
	bool EnBlockSec;
	unsigned* LabelStat;
	brp_Iso15_ReadMultipleBlocks_RecvBlocks_Entry** RecvBlocks;
	size_t* RecvBlocks_len;
	unsigned** BlocksSecData;
	size_t* BlocksSecData_len;
	brp_mempool *mempool;
} brp_Iso15_ReadMultipleBlocks_t;
/**
 * This command reads one or multiple blocks from a label. 
 * 
 * This command implements the (optional) "ReadMultipleBlocks" command from the [ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467).
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **FirstBlockId** (in) Index (starting at 0) of first block to read.
 *   - **BlockCount** (in) Number of blocks to read.
 *   - **EnBlockSec** (in) Enable/Disable _BlockSecStat_ Byte in response frame.
 *   - **LabelStat** (out) Status code returned from label. Is 0 if everything was OK, else an error code is returned.
 *   - **RecvBlocks** (out) if _LabelStat_ is not 0 (=error), this array will always be if size 0.
 *   - **RecvBlocks_len** (out) Number of elements in **RecvBlocks**.
 *   - **BlocksSecData** (out) this array will always be of size 0 if LabelStat is not 0 (=error) or EnBlockSec was not set.
 *   - **BlocksSecData_len** (out) Number of elements in **BlocksSecData**.
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_ReadMultipleBlocks(brp_protocol protocol, unsigned _input_FirstBlockId, unsigned _input_BlockCount, bool _input_EnBlockSec, unsigned* LabelStat, brp_Iso15_ReadMultipleBlocks_RecvBlocks_Entry** RecvBlocks, size_t* RecvBlocks_len, unsigned** BlocksSecData, size_t* BlocksSecData_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso15_ReadMultipleBlocks(brp_Iso15_ReadMultipleBlocks_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf SendData;
	size_t SendData_len;
	unsigned Timeout;
	bool EnCrcRx;
	bool EnCrcTx;
	unsigned RxWait;
	brp_buf* RecvData;
	size_t* RecvData_len;
	brp_mempool *mempool;
} brp_Iso15_TransparentCmd_t;
/**
 * This command sends a data stream to a label and returns the communication status and the received label data stream to the host. If no bytes are sent and the CRC check is disabled, only an EOF is sent to the label. After execution of this command, the _Mode_ parameter is reset to default. 
 * 
 * **Please be aware that the _flag_ Byte (see the[ ISO 15693-3 specification](http://www.iso.org/iso/catalogue_detail.htm?csnumber=43467) , 2001 p.9) is not generated by the reader. This flag has to be transmitted as part of the _data_ string.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **SendData** (in) 
 *   - **SendData_len** (in) Length of **SendData** (in bytes).
 *   - **Timeout** (in) Timeout in ms between sending last bit to label and receiving first bit from label.
 *   - **EnCrcRx** (in) Check CRC on _RecvData_ and remove it before returning it.
 *   - **EnCrcTx** (in) Add CRC to _SendData_ before transmitting it to card.
 *   - **RxWait** (in) After data transmission to the label, the receiver is delayed for a _RxWait_ time, measured in Rx bitclock steps. If this value is 0, no delay is added.
 *   - **RecvData** (out) 
 *   - **RecvData_len** (out) Length of **RecvData** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_TransparentCmd(brp_protocol protocol, brp_buf _input_SendData, size_t _input_SendData_len, unsigned _input_Timeout, bool _input_EnCrcRx, bool _input_EnCrcTx, unsigned _input_RxWait, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool);
#else
brp_errcode brp_Iso15_TransparentCmd(brp_Iso15_TransparentCmd_t params);
#endif
#endif
/**
 * @}
 */