/**
 * @file
 * **This command group is available in our standard firmware since version 2.13.**
 * 
 * With this command group, you can implement your own BLE peripheral protocol, i.e. your own BLE service (with its own characteristics), which will be advertised by the reader. 
 * 
 * Before BLE can be activated via BlePeriph.Enable, you have to define your service via BlePeriph.DefineService. This will create an internal database of characteristics that can be accessed from the BRP host with the commands BlePeriph.WriteCharacteristic and BlePeriph.ReadCharacteristic. 
 * 
 * As soon as BLE is activated via BlePeriph.Enable and a BLE Central connects to your reader, it also has access to this internal database of characteristcs. If it connects to the reader, disconnects, or modifies a characteristic, you'll be informed via BlePeriph.GetEvents. 
 * 
 * **If the BLE peripheral functionality is used in parallel with Mobile ID: It is not possible to use the Mobile ID app and the app to interact with the BLE peripheral on a mobile device simultaneously! If you want to use the BLE peripheral app to interact with the reader, you have to disable the Mobile ID app (e.g. via the _Disable app_ option in _Settings_ ) or vice versa.**
 */
/**
 * @file
 * @defgroup baltech_sdk Wrapper functions
 * @{
 */
#ifndef __BRP_BALTECH_SDK_CMDS_BLEPERIPH_H__
#define __BRP_BALTECH_SDK_CMDS_BLEPERIPH_H__
#include "../typedefs.h"
/**
 * The command could not be executed because BLE is currently not enabled.
 */
#define BRP_BlePeriph_ErrNotEnabled BRP_ERR_STATUS(0x4B00, 0x01)
/**
 * The reader is currently not connected with a BLE central.
 */
#define BRP_BlePeriph_ErrNotConnected BRP_ERR_STATUS(0x4B00, 0x02)
/**
 * The given characteristic index is invalid.
 */
#define BRP_BlePeriph_ErrInvalidCharacteristicNdx BRP_ERR_STATUS(0x4B00, 0x03)
/**
 * The characteristic value could not be written because the given offset or length exceeds the characteristic size.
 */
#define BRP_BlePeriph_ErrWriteCharacteristic BRP_ERR_STATUS(0x4B00, 0x04)
typedef struct {
	brp_protocol protocol;
	brp_buf ServiceUUID;
	size_t ServiceUUID_len;
	brp_BlePeriph_DefineService_Characteristics_Entry* Characteristics;
	size_t Characteristics_len;
} brp_BlePeriph_DefineService_t;
/**
 * This command registers a new BLE service. When a BLE Central tries to discover services, this service will be amongst the available ones. 
 * 
 * If currently enabled, this method disables BLE implicitly. To start the service, call BlePeriph.Enable(true) afterwards. 
 * 
 * **A maximum of 5 characteristics may be defined for the BLE service. The total size of all characteristics may not exceed 1536 bytes.**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ServiceUUID** (in) Specifies the UUID (16 or 128 bits) of the BLE service
 *   - **ServiceUUID_len** (in) Length of **ServiceUUID** (in bytes).
 *   - **Characteristics** (in) List of characteristics (max. 5)
 *   - **Characteristics_len** (in) Number of elements in **Characteristics**.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_DefineService(brp_protocol protocol, brp_buf _input_ServiceUUID, size_t _input_ServiceUUID_len, brp_BlePeriph_DefineService_Characteristics_Entry* _input_Characteristics, size_t _input_Characteristics_len);
#else
brp_errcode brp_BlePeriph_DefineService(brp_BlePeriph_DefineService_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool Activate;
} brp_BlePeriph_Enable_t;
/**
 * This command starts/stops the advertisement of the reader as a BLE Peripheral, so you can respond to connection and other requests.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Activate** (in) 
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_Enable(brp_protocol protocol, bool _input_Activate);
#else
brp_errcode brp_BlePeriph_Enable(brp_BlePeriph_Enable_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf AdvertisingData;
	size_t AdvertisingData_len;
	brp_buf ScanResponseData;
	size_t ScanResponseData_len;
} brp_BlePeriph_SetAdvertisingData_t;
/**
 * This command defines the data to be advertised by the reader. If advertisement is currently enabled, the new data will be used immediately.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **AdvertisingData** (in) Specifies the advertising data (max. 31 bytes)
 *   - **AdvertisingData_len** (in) Length of **AdvertisingData** (in bytes).
 *   - **ScanResponseData** (in) Specifies the optional scan response data (max. 31 bytes)
 *   - **ScanResponseData_len** (in) Length of **ScanResponseData** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_SetAdvertisingData(brp_protocol protocol, brp_buf _input_AdvertisingData, size_t _input_AdvertisingData_len, brp_buf _input_ScanResponseData, size_t _input_ScanResponseData_len);
#else
brp_errcode brp_BlePeriph_SetAdvertisingData(brp_BlePeriph_SetAdvertisingData_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned CharacteristicNdx;
	brp_buf WriteValue;
	size_t WriteValue_len;
} brp_BlePeriph_WriteCharacteristic_t;
/**
 * This command changes the value of a characteristic. All future reads from the Central or BlePeriph.ReadCharacteristic from the BRP host will return the new value. 
 * 
 * If the Central has registered a notification/indication for this characteristic, the reader will automatically send a corresponding message to the Central. 
 * 
 * **A characteristic can only be written when BLE is enabled .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CharacteristicNdx** (in) The index of the characteristic to modify in the _Characteristics_ array passed to BlePeriph.DefineService, starting with 0
 *   - **WriteValue** (in) 
 *   - **WriteValue_len** (in) Length of **WriteValue** (in bytes).
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_WriteCharacteristic(brp_protocol protocol, unsigned _input_CharacteristicNdx, brp_buf _input_WriteValue, size_t _input_WriteValue_len);
#else
brp_errcode brp_BlePeriph_WriteCharacteristic(brp_BlePeriph_WriteCharacteristic_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned CharacteristicNdx;
	unsigned ReadLength;
	brp_buf* ReadValue;
	size_t* ReadValue_len;
	brp_mempool *mempool;
} brp_BlePeriph_ReadCharacteristic_t;
/**
 * This command retrieves the current value of a characteristic. A characteristic will be initialized to _00 00 ... 00_ when calling BlePeriph.Enable and will be modified by either the BRP host (BlePeriph.WriteCharacteristic) or the BLE Central (via a write to the characteristic). 
 * 
 * **A characteristic can only be read when BLE is enabled .**
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **CharacteristicNdx** (in) The index of the characteristic to be read in the _Characteristics_ array passed to BlePeriph.DefineService, starting with 0
 *   - **ReadLength** (in) Number of bytes to read from characteristic   **This value may exceed the actual characteristic size, but only the available data is returned in the response.**
 *   - **ReadValue** (out) 
 *   - **ReadValue_len** (out) Length of **ReadValue** (in bytes).
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_ReadCharacteristic(brp_protocol protocol, unsigned _input_CharacteristicNdx, unsigned _input_ReadLength, brp_buf* ReadValue, size_t* ReadValue_len, brp_mempool *mempool);
#else
brp_errcode brp_BlePeriph_ReadCharacteristic(brp_BlePeriph_ReadCharacteristic_t params);
#endif
typedef struct {
	brp_protocol protocol;
	bool* ConnectionStatusChanged;
	bool* ValueChangedCharacteristicNdx4;
	bool* ValueChangedCharacteristicNdx3;
	bool* ValueChangedCharacteristicNdx2;
	bool* ValueChangedCharacteristicNdx1;
	bool* ValueChangedCharacteristicNdx0;
} brp_BlePeriph_GetEvents_t;
/**
 * This command returns a bitmask of all events that have occurred since the last call of _BlePeriph.GetEvents_.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **ConnectionStatusChanged** (out) Use BlePeriph.IsConnected to check the current connection status.
 *   - **ValueChangedCharacteristicNdx4** (out) Use BlePeriph.ReadCharacteristic to read the changed characteristic value.
 *   - **ValueChangedCharacteristicNdx3** (out) Use BlePeriph.ReadCharacteristic to read the changed characteristic value.
 *   - **ValueChangedCharacteristicNdx2** (out) Use BlePeriph.ReadCharacteristic to read the changed characteristic value.
 *   - **ValueChangedCharacteristicNdx1** (out) Use BlePeriph.ReadCharacteristic to read the changed characteristic value.
 *   - **ValueChangedCharacteristicNdx0** (out) Use BlePeriph.ReadCharacteristic to read the changed characteristic value.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_GetEvents(brp_protocol protocol, bool* ConnectionStatusChanged, bool* ValueChangedCharacteristicNdx4, bool* ValueChangedCharacteristicNdx3, bool* ValueChangedCharacteristicNdx2, bool* ValueChangedCharacteristicNdx1, bool* ValueChangedCharacteristicNdx0);
#else
brp_errcode brp_BlePeriph_GetEvents(brp_BlePeriph_GetEvents_t params);
#endif
typedef struct {
	brp_protocol protocol;
	brp_buf* Address;
	brp_BlePeriph_IsConnected_AddressType* AddressType;
	brp_mempool *mempool;
} brp_BlePeriph_IsConnected_t;
/**
 * This command is used to check the current connection status. If connected, it returns the device address of the connected BLE central.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **Address** (out) Remote device address
 *   - **AddressType** (out) Remote device address type
 *   - **mempool** (in) is used to store response data. Maybe NULL to use an internal mempool, in this case the data is only available until another command uses the internal mempool
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_IsConnected(brp_protocol protocol, brp_buf* Address, brp_BlePeriph_IsConnected_AddressType* AddressType, brp_mempool *mempool);
#else
brp_errcode brp_BlePeriph_IsConnected(brp_BlePeriph_IsConnected_t params);
#endif
typedef struct {
	brp_protocol protocol;
	unsigned* AbsRSSI;
} brp_BlePeriph_GetRSSI_t;
/**
 * This command returns the RSSI value of the connected BLE Central.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 *   - **AbsRSSI** (out) The absolute value of the RSSI. As the RSSI value is usually negative, the corresponding positive value will be returned.
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_GetRSSI(brp_protocol protocol, unsigned* AbsRSSI);
#else
brp_errcode brp_BlePeriph_GetRSSI(brp_BlePeriph_GetRSSI_t params);
#endif
typedef struct {
	brp_protocol protocol;
} brp_BlePeriph_CloseConnection_t;
/**
 * This command closes the active connection with a BLE Central.
 * 
 * @param[in] params Struct with the following fields:
 *   - **protocol** used to execute the command
 */
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_CloseConnection(brp_protocol protocol);
#else
brp_errcode brp_BlePeriph_CloseConnection(brp_BlePeriph_CloseConnection_t params);
#endif
#endif
/**
 * @}
 */