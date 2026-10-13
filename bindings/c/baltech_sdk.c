#include "typedefs.h"
#include "baltech_sdk.h"
#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_ASK_SecuraKeyRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_ASK_SecuraKeyRead(brp_ASK_SecuraKeyRead_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 54);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_ASK_GproxRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_ASK_GproxRead(brp_ASK_GproxRead_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 54);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_ASK_CotagRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_ASK_CotagRead(brp_ASK_CotagRead_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 54);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_AR_SetMode(brp_protocol protocol, brp_AutoReadMode _input_Mode) {
#else
brp_errcode brp_AR_SetMode(brp_AR_SetMode_t params) {
	brp_protocol protocol = params.protocol;
	brp_AutoReadMode _input_Mode = params.Mode;
#endif
	brp_AutoReadMode* Mode = &_input_Mode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 1000);
	brp_frame_write_int8(_frame, (unsigned)(*Mode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_AR_GetMessage(brp_protocol protocol, brp_MessageType* MsgType, brp_buf* MsgData, size_t* MsgData_len, brp_mempool *mempool) {
#else
brp_errcode brp_AR_GetMessage(brp_AR_GetMessage_t params) {
	brp_protocol protocol = params.protocol;
	brp_MessageType* MsgType = params.MsgType;
	brp_buf* MsgData = params.MsgData;
	size_t* MsgData_len = params.MsgData_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _MsgData_len;
	if(MsgData_len == NULL) MsgData_len = &_MsgData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	int _MsgType_int_val = brp_frame_read_int8(&_reader);
	if (MsgType != NULL) {
		if (brp_MessageType_is_valid(_MsgType_int_val))
			(*MsgType) = (brp_MessageType)_MsgType_int_val;
		else
			(*MsgType) = brp_MessageType_undefined;
	}
	(*MsgData_len) = brp_frame_read_int8(&_reader);
	if (MsgData != NULL) {
		(*MsgData) = (brp_buf)brp_mempool_create_buf(mempool, (*MsgData_len));
		if((*MsgData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*MsgData), (*MsgData_len));
	} else
		brp_frame_skip(&_reader, (*MsgData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_AR_RunScript(brp_protocol protocol, brp_buf _input_Script, size_t _input_Script_len) {
#else
brp_errcode brp_AR_RunScript(brp_AR_RunScript_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_Script = params.Script;
	size_t _input_Script_len = params.Script_len;
#endif
	brp_buf* Script = &_input_Script;
	size_t* Script_len = &_input_Script_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Script_len));
	brp_frame_write(_frame, (brp_buf)(*Script), (*Script_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_AR_RestrictScanCardFamilies(brp_protocol protocol, brp_CardFamilies _input_CardFamiliesFilter) {
#else
brp_errcode brp_AR_RestrictScanCardFamilies(brp_AR_RestrictScanCardFamilies_t params) {
	brp_protocol protocol = params.protocol;
	brp_CardFamilies _input_CardFamiliesFilter = params.CardFamiliesFilter;
#endif
	brp_CardFamilies* CardFamiliesFilter = &_input_CardFamiliesFilter;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	unsigned _CardFamiliesFilter_int = 0;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->LEGICPrime & 0b1) << 11;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->BluetoothMce & 0b1) << 10;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Khz125Part2 & 0b1) << 9;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Srix & 0b1) << 8;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Khz125Part1 & 0b1) << 7;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Felica & 0b1) << 6;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->IClass & 0b1) << 5;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->IClassIso14B & 0b1) << 4;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Iso14443B & 0b1) << 3;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Iso15693 & 0b1) << 2;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Iso14443A & 0b1) << 0;
	brp_frame_write_int16(_frame, (unsigned)_CardFamiliesFilter_int);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_DefineService(brp_protocol protocol, brp_buf _input_ServiceUUID, size_t _input_ServiceUUID_len, brp_BlePeriph_DefineService_Characteristics_Entry* _input_Characteristics, size_t _input_Characteristics_len) {
#else
brp_errcode brp_BlePeriph_DefineService(brp_BlePeriph_DefineService_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_ServiceUUID = params.ServiceUUID;
	size_t _input_ServiceUUID_len = params.ServiceUUID_len;
	brp_BlePeriph_DefineService_Characteristics_Entry* _input_Characteristics = params.Characteristics;
	size_t _input_Characteristics_len = params.Characteristics_len;
#endif
	brp_buf* ServiceUUID = &_input_ServiceUUID;
	size_t* ServiceUUID_len = &_input_ServiceUUID_len;
	brp_BlePeriph_DefineService_Characteristics_Entry** Characteristics = &_input_Characteristics;
	size_t* Characteristics_len = &_input_Characteristics_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 75);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	unsigned char RFU[] = { 0x0 };
	brp_frame_write( _frame, RFU, 1);
	brp_frame_write_int8(_frame, (unsigned)(*ServiceUUID_len));
	brp_frame_write(_frame, (brp_buf)(*ServiceUUID), (*ServiceUUID_len));
	brp_frame_write_int8(_frame, (unsigned)(*Characteristics_len));
	for(size_t _Characteristics_ndx = 0;_Characteristics_ndx < (*Characteristics_len);_Characteristics_ndx++) {
		brp_BlePeriph_DefineService_Characteristics_Entry _Characteristics_Entry = (*Characteristics)[_Characteristics_ndx];
		brp_BlePeriph_DefineService_Characteristics_Entry* Characteristics_Entry = &_Characteristics_Entry;
		brp_buf _CharacteristicUUID = (Characteristics_Entry)->CharacteristicUUID;
		brp_buf* CharacteristicUUID = &_CharacteristicUUID;
		size_t _CharacteristicUUID_len = (Characteristics_Entry)->CharacteristicUUID_len;
		size_t* CharacteristicUUID_len = &_CharacteristicUUID_len;
		bool _SupportsIndicate = (Characteristics_Entry)->SupportsIndicate;
		bool* SupportsIndicate = &_SupportsIndicate;
		bool _SupportsNotify = (Characteristics_Entry)->SupportsNotify;
		bool* SupportsNotify = &_SupportsNotify;
		bool _SupportsWrite = (Characteristics_Entry)->SupportsWrite;
		bool* SupportsWrite = &_SupportsWrite;
		bool _SupportsWriteNoResponse = (Characteristics_Entry)->SupportsWriteNoResponse;
		bool* SupportsWriteNoResponse = &_SupportsWriteNoResponse;
		bool _SupportsRead = (Characteristics_Entry)->SupportsRead;
		bool* SupportsRead = &_SupportsRead;
		bool _VariableSize = (Characteristics_Entry)->VariableSize;
		bool* VariableSize = &_VariableSize;
		unsigned _Size = (Characteristics_Entry)->Size;
		unsigned* Size = &_Size;
		brp_frame_write_int8(_frame, (unsigned)(*CharacteristicUUID_len));
		brp_frame_write(_frame, (brp_buf)(*CharacteristicUUID), (*CharacteristicUUID_len));
		unsigned _bitmask_d69f = 0;
		_bitmask_d69f |= (*SupportsIndicate & 0b1) << 5;
		_bitmask_d69f |= (*SupportsNotify & 0b1) << 4;
		_bitmask_d69f |= (*SupportsWrite & 0b1) << 3;
		_bitmask_d69f |= (*SupportsWriteNoResponse & 0b1) << 2;
		_bitmask_d69f |= (*SupportsRead & 0b1) << 1;
		brp_frame_write_int16(_frame, (unsigned)_bitmask_d69f);
		unsigned _bitmask_c8fb = 0;
		_bitmask_c8fb |= (*VariableSize & 0b1) << 0;
		brp_frame_write_int8(_frame, (unsigned)_bitmask_c8fb);
		brp_frame_write_int16(_frame, (unsigned)(*Size));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_Enable(brp_protocol protocol, bool _input_Activate) {
#else
brp_errcode brp_BlePeriph_Enable(brp_BlePeriph_Enable_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_Activate = params.Activate;
#endif
	bool* Activate = &_input_Activate;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 75);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Activate));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_SetAdvertisingData(brp_protocol protocol, brp_buf _input_AdvertisingData, size_t _input_AdvertisingData_len, brp_buf _input_ScanResponseData, size_t _input_ScanResponseData_len) {
#else
brp_errcode brp_BlePeriph_SetAdvertisingData(brp_BlePeriph_SetAdvertisingData_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_AdvertisingData = params.AdvertisingData;
	size_t _input_AdvertisingData_len = params.AdvertisingData_len;
	brp_buf _input_ScanResponseData = params.ScanResponseData;
	size_t _input_ScanResponseData_len = params.ScanResponseData_len;
#endif
	brp_buf* AdvertisingData = &_input_AdvertisingData;
	size_t* AdvertisingData_len = &_input_AdvertisingData_len;
	brp_buf* ScanResponseData = &_input_ScanResponseData;
	size_t* ScanResponseData_len = &_input_ScanResponseData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 75);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*AdvertisingData_len));
	brp_frame_write(_frame, (brp_buf)(*AdvertisingData), (*AdvertisingData_len));
	brp_frame_write_int8(_frame, (unsigned)(*ScanResponseData_len));
	brp_frame_write(_frame, (brp_buf)(*ScanResponseData), (*ScanResponseData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_WriteCharacteristic(brp_protocol protocol, unsigned _input_CharacteristicNdx, brp_buf _input_WriteValue, size_t _input_WriteValue_len) {
#else
brp_errcode brp_BlePeriph_WriteCharacteristic(brp_BlePeriph_WriteCharacteristic_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_CharacteristicNdx = params.CharacteristicNdx;
	brp_buf _input_WriteValue = params.WriteValue;
	size_t _input_WriteValue_len = params.WriteValue_len;
#endif
	unsigned* CharacteristicNdx = &_input_CharacteristicNdx;
	brp_buf* WriteValue = &_input_WriteValue;
	size_t* WriteValue_len = &_input_WriteValue_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 75);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 1000);
	brp_frame_write_int8(_frame, (unsigned)(*CharacteristicNdx));
	brp_frame_write_int16(_frame, (unsigned)(*WriteValue_len));
	brp_frame_write(_frame, (brp_buf)(*WriteValue), (*WriteValue_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_ReadCharacteristic(brp_protocol protocol, unsigned _input_CharacteristicNdx, unsigned _input_ReadLength, brp_buf* ReadValue, size_t* ReadValue_len, brp_mempool *mempool) {
#else
brp_errcode brp_BlePeriph_ReadCharacteristic(brp_BlePeriph_ReadCharacteristic_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_CharacteristicNdx = params.CharacteristicNdx;
	unsigned _input_ReadLength = params.ReadLength;
	brp_buf* ReadValue = params.ReadValue;
	size_t* ReadValue_len = params.ReadValue_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* CharacteristicNdx = &_input_CharacteristicNdx;
	unsigned* ReadLength = &_input_ReadLength;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ReadValue_len;
	if(ReadValue_len == NULL) ReadValue_len = &_ReadValue_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 75);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*CharacteristicNdx));
	brp_frame_write_int16(_frame, (unsigned)(*ReadLength));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ReadValue_len) = brp_frame_read_int16(&_reader);
	if (ReadValue != NULL) {
		(*ReadValue) = (brp_buf)brp_mempool_create_buf(mempool, (*ReadValue_len));
		if((*ReadValue) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ReadValue), (*ReadValue_len));
	} else
		brp_frame_skip(&_reader, (*ReadValue_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_GetEvents(brp_protocol protocol, bool* ConnectionStatusChanged, bool* ValueChangedCharacteristicNdx4, bool* ValueChangedCharacteristicNdx3, bool* ValueChangedCharacteristicNdx2, bool* ValueChangedCharacteristicNdx1, bool* ValueChangedCharacteristicNdx0) {
#else
brp_errcode brp_BlePeriph_GetEvents(brp_BlePeriph_GetEvents_t params) {
	brp_protocol protocol = params.protocol;
	bool* ConnectionStatusChanged = params.ConnectionStatusChanged;
	bool* ValueChangedCharacteristicNdx4 = params.ValueChangedCharacteristicNdx4;
	bool* ValueChangedCharacteristicNdx3 = params.ValueChangedCharacteristicNdx3;
	bool* ValueChangedCharacteristicNdx2 = params.ValueChangedCharacteristicNdx2;
	bool* ValueChangedCharacteristicNdx1 = params.ValueChangedCharacteristicNdx1;
	bool* ValueChangedCharacteristicNdx0 = params.ValueChangedCharacteristicNdx0;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	bool _tmp_ConnectionStatusChanged;
	if (ConnectionStatusChanged == NULL) ConnectionStatusChanged = &_tmp_ConnectionStatusChanged;
	bool _tmp_ValueChangedCharacteristicNdx4;
	if (ValueChangedCharacteristicNdx4 == NULL) ValueChangedCharacteristicNdx4 = &_tmp_ValueChangedCharacteristicNdx4;
	bool _tmp_ValueChangedCharacteristicNdx3;
	if (ValueChangedCharacteristicNdx3 == NULL) ValueChangedCharacteristicNdx3 = &_tmp_ValueChangedCharacteristicNdx3;
	bool _tmp_ValueChangedCharacteristicNdx2;
	if (ValueChangedCharacteristicNdx2 == NULL) ValueChangedCharacteristicNdx2 = &_tmp_ValueChangedCharacteristicNdx2;
	bool _tmp_ValueChangedCharacteristicNdx1;
	if (ValueChangedCharacteristicNdx1 == NULL) ValueChangedCharacteristicNdx1 = &_tmp_ValueChangedCharacteristicNdx1;
	bool _tmp_ValueChangedCharacteristicNdx0;
	if (ValueChangedCharacteristicNdx0 == NULL) ValueChangedCharacteristicNdx0 = &_tmp_ValueChangedCharacteristicNdx0;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 75);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	unsigned _bitmask_6597 = brp_frame_read_int32(&_reader);
	if(ConnectionStatusChanged != NULL)
		(*ConnectionStatusChanged) = (_bitmask_6597>>31) & 0b1;
	if(ValueChangedCharacteristicNdx4 != NULL)
		(*ValueChangedCharacteristicNdx4) = (_bitmask_6597>>4) & 0b1;
	if(ValueChangedCharacteristicNdx3 != NULL)
		(*ValueChangedCharacteristicNdx3) = (_bitmask_6597>>3) & 0b1;
	if(ValueChangedCharacteristicNdx2 != NULL)
		(*ValueChangedCharacteristicNdx2) = (_bitmask_6597>>2) & 0b1;
	if(ValueChangedCharacteristicNdx1 != NULL)
		(*ValueChangedCharacteristicNdx1) = (_bitmask_6597>>1) & 0b1;
	if(ValueChangedCharacteristicNdx0 != NULL)
		(*ValueChangedCharacteristicNdx0) = (_bitmask_6597>>0) & 0b1;
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_IsConnected(brp_protocol protocol, brp_buf* Address, brp_BlePeriph_IsConnected_AddressType* AddressType, brp_mempool *mempool) {
#else
brp_errcode brp_BlePeriph_IsConnected(brp_BlePeriph_IsConnected_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Address = params.Address;
	brp_BlePeriph_IsConnected_AddressType* AddressType = params.AddressType;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 75);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _Address_len = 6;
	size_t* Address_len = &_Address_len;
	if (Address != NULL) {
		(*Address) = (brp_buf)brp_mempool_create_buf(mempool, (*Address_len));
		if((*Address) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Address), (*Address_len));
	} else
		brp_frame_skip(&_reader, (*Address_len));
	int _AddressType_int_val = brp_frame_read_int8(&_reader);
	if (! brp_BlePeriph_IsConnected_AddressType_is_valid(_AddressType_int_val))
		return BRP_ERR_PAYLOAD_FORMAT;
	if (AddressType != NULL)
		(*AddressType) = (brp_BlePeriph_IsConnected_AddressType)_AddressType_int_val;
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_GetRSSI(brp_protocol protocol, unsigned* AbsRSSI) {
#else
brp_errcode brp_BlePeriph_GetRSSI(brp_BlePeriph_GetRSSI_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* AbsRSSI = params.AbsRSSI;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_AbsRSSI;
	if (AbsRSSI == NULL) AbsRSSI = &_tmp_AbsRSSI;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 75);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*AbsRSSI) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_BlePeriph_CloseConnection(brp_protocol protocol) {
#else
brp_errcode brp_BlePeriph_CloseConnection(brp_BlePeriph_CloseConnection_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 75);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int32(_frame, 1000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_CardEmu_GetMaxFrameSize(brp_protocol protocol, unsigned* MaxFrameSize) {
#else
brp_errcode brp_CardEmu_GetMaxFrameSize(brp_CardEmu_GetMaxFrameSize_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* MaxFrameSize = params.MaxFrameSize;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_MaxFrameSize;
	if (MaxFrameSize == NULL) MaxFrameSize = &_tmp_MaxFrameSize;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 71);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*MaxFrameSize) = (unsigned)brp_frame_read_int16(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_CardEmu_StartEmu(brp_protocol protocol, brp_buf _input_Snr, unsigned _input_ATQA, unsigned _input_SAK, unsigned _input_Timeout, brp_buf* FirstCmd, size_t* FirstCmd_len, brp_mempool *mempool) {
#else
brp_errcode brp_CardEmu_StartEmu(brp_CardEmu_StartEmu_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_Snr = params.Snr;
	unsigned _input_ATQA = params.ATQA;
	unsigned _input_SAK = params.SAK;
	unsigned _input_Timeout = params.Timeout;
	brp_buf* FirstCmd = params.FirstCmd;
	size_t* FirstCmd_len = params.FirstCmd_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* Snr = &_input_Snr;
	unsigned* ATQA = &_input_ATQA;
	unsigned* SAK = &_input_SAK;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _FirstCmd_len;
	if(FirstCmd_len == NULL) FirstCmd_len = &_FirstCmd_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 71);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 1000);
	unsigned char Padding[] = { 0x0 };
	brp_frame_write( _frame, Padding, 1);
	size_t _Snr_len_val = 4;
	size_t* Snr_len = &_Snr_len_val;
	brp_frame_write(_frame, (brp_buf)(*Snr), (*Snr_len));
	brp_frame_write_int16(_frame, (unsigned)(*ATQA));
	brp_frame_write_int8(_frame, (unsigned)(*SAK));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*FirstCmd_len) = brp_frame_read_int16(&_reader);
	if (FirstCmd != NULL) {
		(*FirstCmd) = (brp_buf)brp_mempool_create_buf(mempool, (*FirstCmd_len));
		if((*FirstCmd) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*FirstCmd), (*FirstCmd_len));
	} else
		brp_frame_skip(&_reader, (*FirstCmd_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_CardEmu_TransparentCmd(brp_protocol protocol, brp_buf _input_Rsp, size_t _input_Rsp_len, unsigned _input_Timeout, brp_buf* Cmd, size_t* Cmd_len, brp_mempool *mempool) {
#else
brp_errcode brp_CardEmu_TransparentCmd(brp_CardEmu_TransparentCmd_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_Rsp = params.Rsp;
	size_t _input_Rsp_len = params.Rsp_len;
	unsigned _input_Timeout = params.Timeout;
	brp_buf* Cmd = params.Cmd;
	size_t* Cmd_len = params.Cmd_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* Rsp = &_input_Rsp;
	size_t* Rsp_len = &_input_Rsp_len;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Cmd_len;
	if(Cmd_len == NULL) Cmd_len = &_Cmd_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 71);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*Rsp_len));
	brp_frame_write(_frame, (brp_buf)(*Rsp), (*Rsp_len));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Cmd_len) = brp_frame_read_int16(&_reader);
	if (Cmd != NULL) {
		(*Cmd) = (brp_buf)brp_mempool_create_buf(mempool, (*Cmd_len));
		if((*Cmd) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Cmd), (*Cmd_len));
	} else
		brp_frame_skip(&_reader, (*Cmd_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_CardEmu_GetExternalHfStatus(brp_protocol protocol, unsigned* ExtFieldStat) {
#else
brp_errcode brp_CardEmu_GetExternalHfStatus(brp_CardEmu_GetExternalHfStatus_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* ExtFieldStat = params.ExtFieldStat;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_ExtFieldStat;
	if (ExtFieldStat == NULL) ExtFieldStat = &_tmp_ExtFieldStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 71);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ExtFieldStat) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_CardEmu_StartNfc(brp_protocol protocol, bool _input_NfcAPassiv, brp_buf _input_Snr, unsigned _input_ATQA, unsigned _input_SAK, unsigned _input_Timeout, brp_buf* FirstCmd, size_t* FirstCmd_len, brp_mempool *mempool) {
#else
brp_errcode brp_CardEmu_StartNfc(brp_CardEmu_StartNfc_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_NfcAPassiv = params.NfcAPassiv;
	brp_buf _input_Snr = params.Snr;
	unsigned _input_ATQA = params.ATQA;
	unsigned _input_SAK = params.SAK;
	unsigned _input_Timeout = params.Timeout;
	brp_buf* FirstCmd = params.FirstCmd;
	size_t* FirstCmd_len = params.FirstCmd_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* NfcAPassiv = &_input_NfcAPassiv;
	brp_buf* Snr = &_input_Snr;
	unsigned* ATQA = &_input_ATQA;
	unsigned* SAK = &_input_SAK;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _FirstCmd_len;
	if(FirstCmd_len == NULL) FirstCmd_len = &_FirstCmd_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 71);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 1000);
	unsigned _bitmask_d9fc = 0;
	_bitmask_d9fc |= (*NfcAPassiv & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_d9fc);
	size_t _Snr_len_val = 4;
	size_t* Snr_len = &_Snr_len_val;
	brp_frame_write(_frame, (brp_buf)(*Snr), (*Snr_len));
	brp_frame_write_int16(_frame, (unsigned)(*ATQA));
	brp_frame_write_int8(_frame, (unsigned)(*SAK));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*FirstCmd_len) = brp_frame_read_int16(&_reader);
	if (FirstCmd != NULL) {
		(*FirstCmd) = (brp_buf)brp_mempool_create_buf(mempool, (*FirstCmd_len));
		if((*FirstCmd) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*FirstCmd), (*FirstCmd_len));
	} else
		brp_frame_skip(&_reader, (*FirstCmd_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_EncryptBlock(brp_protocol protocol, unsigned _input_KeyIndex, brp_buf _input_KeyValue, brp_buf _input_Block, brp_buf* EncryptedBlock, brp_mempool *mempool) {
#else
brp_errcode brp_Crypto_EncryptBlock(brp_Crypto_EncryptBlock_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_KeyIndex = params.KeyIndex;
	brp_buf _input_KeyValue = params.KeyValue;
	brp_buf _input_Block = params.Block;
	brp_buf* EncryptedBlock = params.EncryptedBlock;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* KeyIndex = &_input_KeyIndex;
	brp_buf* KeyValue = &_input_KeyValue;
	brp_buf* Block = &_input_Block;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	if(!(*KeyIndex) && (KeyValue)) (*KeyIndex) = 0;
	brp_frame_write_int8(_frame, (unsigned)(*KeyIndex));
	if((*KeyIndex) == (0)) {
		size_t _KeyValue_len_val = 10;
		size_t* KeyValue_len = &_KeyValue_len_val;
		brp_frame_write(_frame, (brp_buf)(*KeyValue), (*KeyValue_len));
	}
	size_t _Block_len_val = 8;
	size_t* Block_len = &_Block_len_val;
	brp_frame_write(_frame, (brp_buf)(*Block), (*Block_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _EncryptedBlock_len = 8;
	size_t* EncryptedBlock_len = &_EncryptedBlock_len;
	if (EncryptedBlock != NULL) {
		(*EncryptedBlock) = (brp_buf)brp_mempool_create_buf(mempool, (*EncryptedBlock_len));
		if((*EncryptedBlock) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*EncryptedBlock), (*EncryptedBlock_len));
	} else
		brp_frame_skip(&_reader, (*EncryptedBlock_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_DecryptBlock(brp_protocol protocol, unsigned _input_KeyIndex, brp_buf _input_KeyValue, brp_buf _input_Block, brp_buf* UnencryptedBlock, brp_mempool *mempool) {
#else
brp_errcode brp_Crypto_DecryptBlock(brp_Crypto_DecryptBlock_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_KeyIndex = params.KeyIndex;
	brp_buf _input_KeyValue = params.KeyValue;
	brp_buf _input_Block = params.Block;
	brp_buf* UnencryptedBlock = params.UnencryptedBlock;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* KeyIndex = &_input_KeyIndex;
	brp_buf* KeyValue = &_input_KeyValue;
	brp_buf* Block = &_input_Block;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	if(!(*KeyIndex) && (KeyValue)) (*KeyIndex) = 0;
	brp_frame_write_int8(_frame, (unsigned)(*KeyIndex));
	if((*KeyIndex) == (0)) {
		size_t _KeyValue_len_val = 10;
		size_t* KeyValue_len = &_KeyValue_len_val;
		brp_frame_write(_frame, (brp_buf)(*KeyValue), (*KeyValue_len));
	}
	size_t _Block_len_val = 8;
	size_t* Block_len = &_Block_len_val;
	brp_frame_write(_frame, (brp_buf)(*Block), (*Block_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _UnencryptedBlock_len = 8;
	size_t* UnencryptedBlock_len = &_UnencryptedBlock_len;
	if (UnencryptedBlock != NULL) {
		(*UnencryptedBlock) = (brp_buf)brp_mempool_create_buf(mempool, (*UnencryptedBlock_len));
		if((*UnencryptedBlock) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*UnencryptedBlock), (*UnencryptedBlock_len));
	} else
		brp_frame_skip(&_reader, (*UnencryptedBlock_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_EncryptBuffer(brp_protocol protocol, unsigned _input_KeyIndex, brp_buf _input_KeyValue, brp_buf _input_InitialVector, brp_buf _input_Buffer, size_t _input_Buffer_len, brp_buf* NextInitialVector, brp_buf* EncryptedBuffer, size_t* EncryptedBuffer_len, brp_mempool *mempool) {
#else
brp_errcode brp_Crypto_EncryptBuffer(brp_Crypto_EncryptBuffer_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_KeyIndex = params.KeyIndex;
	brp_buf _input_KeyValue = params.KeyValue;
	brp_buf _input_InitialVector = params.InitialVector;
	brp_buf _input_Buffer = params.Buffer;
	size_t _input_Buffer_len = params.Buffer_len;
	brp_buf* NextInitialVector = params.NextInitialVector;
	brp_buf* EncryptedBuffer = params.EncryptedBuffer;
	size_t* EncryptedBuffer_len = params.EncryptedBuffer_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* KeyIndex = &_input_KeyIndex;
	brp_buf* KeyValue = &_input_KeyValue;
	brp_buf* InitialVector = &_input_InitialVector;
	brp_buf* Buffer = &_input_Buffer;
	size_t* Buffer_len = &_input_Buffer_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _EncryptedBuffer_len;
	if(EncryptedBuffer_len == NULL) EncryptedBuffer_len = &_EncryptedBuffer_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	if(!(*KeyIndex) && (KeyValue)) (*KeyIndex) = 0;
	brp_frame_write_int8(_frame, (unsigned)(*KeyIndex));
	if((*KeyIndex) == (0)) {
		size_t _KeyValue_len_val = 10;
		size_t* KeyValue_len = &_KeyValue_len_val;
		brp_frame_write(_frame, (brp_buf)(*KeyValue), (*KeyValue_len));
	}
	size_t _InitialVector_len_val = 8;
	size_t* InitialVector_len = &_InitialVector_len_val;
	brp_frame_write(_frame, (brp_buf)(*InitialVector), (*InitialVector_len));
	brp_frame_write_int8(_frame, (unsigned)(*Buffer_len));
	brp_frame_write(_frame, (brp_buf)(*Buffer), (*Buffer_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _NextInitialVector_len = 8;
	size_t* NextInitialVector_len = &_NextInitialVector_len;
	if (NextInitialVector != NULL) {
		(*NextInitialVector) = (brp_buf)brp_mempool_create_buf(mempool, (*NextInitialVector_len));
		if((*NextInitialVector) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*NextInitialVector), (*NextInitialVector_len));
	} else
		brp_frame_skip(&_reader, (*NextInitialVector_len));
	(*EncryptedBuffer_len) = brp_frame_read_int8(&_reader);
	if (EncryptedBuffer != NULL) {
		(*EncryptedBuffer) = (brp_buf)brp_mempool_create_buf(mempool, (*EncryptedBuffer_len));
		if((*EncryptedBuffer) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*EncryptedBuffer), (*EncryptedBuffer_len));
	} else
		brp_frame_skip(&_reader, (*EncryptedBuffer_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_DecryptBuffer(brp_protocol protocol, unsigned _input_KeyIndex, brp_buf _input_KeyValue, brp_buf _input_InitialVector, brp_buf _input_Buffer, size_t _input_Buffer_len, brp_buf* NextInitialVector, brp_buf* UnencryptedBuffer, size_t* UnencryptedBuffer_len, brp_mempool *mempool) {
#else
brp_errcode brp_Crypto_DecryptBuffer(brp_Crypto_DecryptBuffer_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_KeyIndex = params.KeyIndex;
	brp_buf _input_KeyValue = params.KeyValue;
	brp_buf _input_InitialVector = params.InitialVector;
	brp_buf _input_Buffer = params.Buffer;
	size_t _input_Buffer_len = params.Buffer_len;
	brp_buf* NextInitialVector = params.NextInitialVector;
	brp_buf* UnencryptedBuffer = params.UnencryptedBuffer;
	size_t* UnencryptedBuffer_len = params.UnencryptedBuffer_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* KeyIndex = &_input_KeyIndex;
	brp_buf* KeyValue = &_input_KeyValue;
	brp_buf* InitialVector = &_input_InitialVector;
	brp_buf* Buffer = &_input_Buffer;
	size_t* Buffer_len = &_input_Buffer_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _UnencryptedBuffer_len;
	if(UnencryptedBuffer_len == NULL) UnencryptedBuffer_len = &_UnencryptedBuffer_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	if(!(*KeyIndex) && (KeyValue)) (*KeyIndex) = 0;
	brp_frame_write_int8(_frame, (unsigned)(*KeyIndex));
	if((*KeyIndex) == (0)) {
		size_t _KeyValue_len_val = 10;
		size_t* KeyValue_len = &_KeyValue_len_val;
		brp_frame_write(_frame, (brp_buf)(*KeyValue), (*KeyValue_len));
	}
	size_t _InitialVector_len_val = 8;
	size_t* InitialVector_len = &_InitialVector_len_val;
	brp_frame_write(_frame, (brp_buf)(*InitialVector), (*InitialVector_len));
	brp_frame_write_int8(_frame, (unsigned)(*Buffer_len));
	brp_frame_write(_frame, (brp_buf)(*Buffer), (*Buffer_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _NextInitialVector_len = 8;
	size_t* NextInitialVector_len = &_NextInitialVector_len;
	if (NextInitialVector != NULL) {
		(*NextInitialVector) = (brp_buf)brp_mempool_create_buf(mempool, (*NextInitialVector_len));
		if((*NextInitialVector) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*NextInitialVector), (*NextInitialVector_len));
	} else
		brp_frame_skip(&_reader, (*NextInitialVector_len));
	(*UnencryptedBuffer_len) = brp_frame_read_int8(&_reader);
	if (UnencryptedBuffer != NULL) {
		(*UnencryptedBuffer) = (brp_buf)brp_mempool_create_buf(mempool, (*UnencryptedBuffer_len));
		if((*UnencryptedBuffer) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*UnencryptedBuffer), (*UnencryptedBuffer_len));
	} else
		brp_frame_skip(&_reader, (*UnencryptedBuffer_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_BalKeyEncryptBuffer(brp_protocol protocol, unsigned _input_KeyVersion, unsigned _input_EmbeddedKeyIndex, unsigned _input_EmbeddedKeyPos, brp_buf _input_Buffer, size_t _input_Buffer_len, brp_buf _input_InitialVector, size_t _input_InitialVector_len, brp_buf* EncryptedBuffer, size_t* EncryptedBuffer_len, brp_buf* NextInitialVector, size_t* NextInitialVector_len, brp_mempool *mempool) {
#else
brp_errcode brp_Crypto_BalKeyEncryptBuffer(brp_Crypto_BalKeyEncryptBuffer_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_KeyVersion = params.KeyVersion;
	unsigned _input_EmbeddedKeyIndex = params.EmbeddedKeyIndex;
	unsigned _input_EmbeddedKeyPos = params.EmbeddedKeyPos;
	brp_buf _input_Buffer = params.Buffer;
	size_t _input_Buffer_len = params.Buffer_len;
	brp_buf _input_InitialVector = params.InitialVector;
	size_t _input_InitialVector_len = params.InitialVector_len;
	brp_buf* EncryptedBuffer = params.EncryptedBuffer;
	size_t* EncryptedBuffer_len = params.EncryptedBuffer_len;
	brp_buf* NextInitialVector = params.NextInitialVector;
	size_t* NextInitialVector_len = params.NextInitialVector_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* KeyVersion = &_input_KeyVersion;
	unsigned* EmbeddedKeyIndex = &_input_EmbeddedKeyIndex;
	unsigned* EmbeddedKeyPos = &_input_EmbeddedKeyPos;
	brp_buf* Buffer = &_input_Buffer;
	size_t* Buffer_len = &_input_Buffer_len;
	brp_buf* InitialVector = &_input_InitialVector;
	size_t* InitialVector_len = &_input_InitialVector_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _EncryptedBuffer_len;
	if(EncryptedBuffer_len == NULL) EncryptedBuffer_len = &_EncryptedBuffer_len;
	size_t _NextInitialVector_len;
	if(NextInitialVector_len == NULL) NextInitialVector_len = &_NextInitialVector_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	if (_input_KeyVersion == 0) _input_KeyVersion = (unsigned)2;
	brp_frame_write_int8(_frame, (unsigned)(*KeyVersion));
	brp_frame_write_int8(_frame, (unsigned)(*EmbeddedKeyIndex));
	brp_frame_write_int8(_frame, (unsigned)(*EmbeddedKeyPos));
	brp_frame_write_int8(_frame, (unsigned)(*Buffer_len));
	brp_frame_write(_frame, (brp_buf)(*Buffer), (*Buffer_len));
	brp_frame_write_int8(_frame, (unsigned)(*InitialVector_len));
	brp_frame_write(_frame, (brp_buf)(*InitialVector), (*InitialVector_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*EncryptedBuffer_len) = brp_frame_read_int8(&_reader);
	if (EncryptedBuffer != NULL) {
		(*EncryptedBuffer) = (brp_buf)brp_mempool_create_buf(mempool, (*EncryptedBuffer_len));
		if((*EncryptedBuffer) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*EncryptedBuffer), (*EncryptedBuffer_len));
	} else
		brp_frame_skip(&_reader, (*EncryptedBuffer_len));
	(*NextInitialVector_len) = brp_frame_read_int8(&_reader);
	if (NextInitialVector != NULL) {
		(*NextInitialVector) = (brp_buf)brp_mempool_create_buf(mempool, (*NextInitialVector_len));
		if((*NextInitialVector) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*NextInitialVector), (*NextInitialVector_len));
	} else
		brp_frame_skip(&_reader, (*NextInitialVector_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_GetKeySig(brp_protocol protocol, unsigned _input_KeyIndex, brp_buf _input_KeyValue, unsigned* KeySignature) {
#else
brp_errcode brp_Crypto_GetKeySig(brp_Crypto_GetKeySig_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_KeyIndex = params.KeyIndex;
	brp_buf _input_KeyValue = params.KeyValue;
	unsigned* KeySignature = params.KeySignature;
#endif
	unsigned* KeyIndex = &_input_KeyIndex;
	brp_buf* KeyValue = &_input_KeyValue;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_KeySignature;
	if (KeySignature == NULL) KeySignature = &_tmp_KeySignature;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int32(_frame, 100);
	if(!(*KeyIndex) && (KeyValue)) (*KeyIndex) = 0;
	brp_frame_write_int8(_frame, (unsigned)(*KeyIndex));
	if((*KeyIndex) == (0)) {
		size_t _KeyValue_len_val = 10;
		size_t* KeyValue_len = &_KeyValue_len_val;
		brp_frame_write(_frame, (brp_buf)(*KeyValue), (*KeyValue_len));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*KeySignature) = (unsigned)brp_frame_read_int32(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Crypto_CopyConfigKey(brp_protocol protocol, unsigned _input_KeyIndex, bool _input_ForceDefaultKey) {
#else
brp_errcode brp_Crypto_CopyConfigKey(brp_Crypto_CopyConfigKey_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_KeyIndex = params.KeyIndex;
	bool _input_ForceDefaultKey = params.ForceDefaultKey;
#endif
	unsigned* KeyIndex = &_input_KeyIndex;
	bool* ForceDefaultKey = &_input_ForceDefaultKey;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int8(_frame, 17);
	brp_frame_write_int32(_frame, 2000);
	brp_frame_write_int8(_frame, (unsigned)(*KeyIndex));
	brp_frame_write_int8(_frame, (unsigned)(*ForceDefaultKey));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Dbg_ReadLogs(brp_protocol protocol, char** LogData, brp_mempool *mempool) {
#else
brp_errcode brp_Dbg_ReadLogs(brp_Dbg_ReadLogs_t params) {
	brp_protocol protocol = params.protocol;
	char** LogData = params.LogData;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 243);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _LogData_len = 0;
	size_t* LogData_len = &_LogData_len;
	(*LogData_len) = brp_frame_read_int16(&_reader);
	if (LogData != NULL) {
		(*LogData) = (char*)brp_mempool_create_buf(mempool, (*LogData_len));
		if((*LogData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*LogData), (*LogData_len));
	} else
		brp_frame_skip(&_reader, (*LogData_len));
	if(LogData != NULL) {
		(*LogData_len) += 1;
		(*LogData) = (char*)brp_mempool_resize_buf((brp_buf)(*LogData), (*LogData_len));
		if((*LogData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		(*LogData)[(*LogData_len)-1] = 0;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Dbg_RunCmd(brp_protocol protocol, char* _input_Cmd) {
#else
brp_errcode brp_Dbg_RunCmd(brp_Dbg_RunCmd_t params) {
	brp_protocol protocol = params.protocol;
	char* _input_Cmd = params.Cmd;
#endif
	char** Cmd = &_input_Cmd;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 243);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	size_t _Cmd_len_val = strlen(*Cmd);
	size_t* Cmd_len = &_Cmd_len_val;
	if((*Cmd_len) != 1)return BRP_ERR_INVALID_API_CALL;
	brp_frame_write(_frame, (brp_buf)(*Cmd), (*Cmd_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_ExecCommand(brp_protocol protocol, unsigned _input_Cmd, brp_buf _input_Header, size_t _input_Header_len, brp_buf _input_Param, size_t _input_Param_len, brp_Desfire_ExecCommand_CryptoMode _input_CryptoMode, unsigned _input_ResponseLen, brp_buf* Resp, size_t* Resp_len, brp_mempool *mempool) {
#else
brp_errcode brp_Desfire_ExecCommand(brp_Desfire_ExecCommand_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Cmd = params.Cmd;
	brp_buf _input_Header = params.Header;
	size_t _input_Header_len = params.Header_len;
	brp_buf _input_Param = params.Param;
	size_t _input_Param_len = params.Param_len;
	brp_Desfire_ExecCommand_CryptoMode _input_CryptoMode = params.CryptoMode;
	unsigned _input_ResponseLen = params.ResponseLen;
	brp_buf* Resp = params.Resp;
	size_t* Resp_len = params.Resp_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Cmd = &_input_Cmd;
	brp_buf* Header = &_input_Header;
	size_t* Header_len = &_input_Header_len;
	brp_buf* Param = &_input_Param;
	size_t* Param_len = &_input_Param_len;
	brp_Desfire_ExecCommand_CryptoMode* CryptoMode = &_input_CryptoMode;
	unsigned* ResponseLen = &_input_ResponseLen;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Resp_len;
	if(Resp_len == NULL) Resp_len = &_Resp_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 2000);
	brp_frame_write_int8(_frame, (unsigned)(*Cmd));
	brp_frame_write_int8(_frame, (unsigned)(*Header_len));
	brp_frame_write(_frame, (brp_buf)(*Header), (*Header_len));
	brp_frame_write_int16(_frame, (unsigned)(*Param_len));
	brp_frame_write(_frame, (brp_buf)(*Param), (*Param_len));
	brp_frame_write_int8(_frame, (unsigned)(*CryptoMode));
	brp_frame_write_int16(_frame, (unsigned)(*ResponseLen));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Resp_len) = brp_frame_read_int16(&_reader);
	if (Resp != NULL) {
		(*Resp) = (brp_buf)brp_mempool_create_buf(mempool, (*Resp_len));
		if((*Resp) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Resp), (*Resp_len));
	} else
		brp_frame_skip(&_reader, (*Resp_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_Authenticate(brp_protocol protocol, brp_Desfire_Authenticate_SecureMessaging _input_SecureMessaging, unsigned _input_DesKeynr, unsigned _input_KeyId, bool _input_KeyHasDivData, brp_Desfire_Authenticate_KeyDivMode _input_KeyDivMode, bool _input_KeyHasExtIdx, brp_buf _input_KeyDivData, size_t _input_KeyDivData_len, unsigned _input_KeyExtIdx) {
#else
brp_errcode brp_Desfire_Authenticate(brp_Desfire_Authenticate_t params) {
	brp_protocol protocol = params.protocol;
	brp_Desfire_Authenticate_SecureMessaging _input_SecureMessaging = params.SecureMessaging;
	unsigned _input_DesKeynr = params.DesKeynr;
	unsigned _input_KeyId = params.KeyId;
	bool _input_KeyHasDivData = params.KeyHasDivData;
	brp_Desfire_Authenticate_KeyDivMode _input_KeyDivMode = params.KeyDivMode;
	bool _input_KeyHasExtIdx = params.KeyHasExtIdx;
	brp_buf _input_KeyDivData = params.KeyDivData;
	size_t _input_KeyDivData_len = params.KeyDivData_len;
	unsigned _input_KeyExtIdx = params.KeyExtIdx;
#endif
	brp_Desfire_Authenticate_SecureMessaging* SecureMessaging = &_input_SecureMessaging;
	unsigned* DesKeynr = &_input_DesKeynr;
	unsigned* KeyId = &_input_KeyId;
	bool* KeyHasDivData = &_input_KeyHasDivData;
	brp_Desfire_Authenticate_KeyDivMode* KeyDivMode = &_input_KeyDivMode;
	bool* KeyHasExtIdx = &_input_KeyHasExtIdx;
	brp_buf* KeyDivData = &_input_KeyDivData;
	size_t* KeyDivData_len = &_input_KeyDivData_len;
	unsigned* KeyExtIdx = &_input_KeyExtIdx;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 2000);
	if(!(*KeyHasExtIdx) && (*KeyExtIdx)) (*KeyHasExtIdx) = true;
	if(!(*KeyHasDivData) && (KeyDivData)) (*KeyHasDivData) = true;
	brp_frame_write_int8(_frame, (unsigned)(*SecureMessaging));
	brp_frame_write_int8(_frame, (unsigned)(*DesKeynr));
	brp_frame_write_int8(_frame, (unsigned)(*KeyId));
	unsigned _bitmask_ac80 = 0;
	_bitmask_ac80 |= (*KeyHasDivData & 0b1) << 4;
	_bitmask_ac80 |= (*KeyDivMode & 0b111) << 1;
	_bitmask_ac80 |= (*KeyHasExtIdx & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_ac80);
	if(*KeyHasDivData) {
		brp_frame_write_int8(_frame, (unsigned)(*KeyDivData_len));
		brp_frame_write(_frame, (brp_buf)(*KeyDivData), (*KeyDivData_len));
	}
	if(*KeyHasExtIdx) {
		brp_frame_write_int8(_frame, (unsigned)(*KeyExtIdx));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_AuthExtKey(brp_protocol protocol, brp_Desfire_AuthExtKey_SecureMessaging _input_SecureMessaging, unsigned _input_DesKeyNr, brp_Desfire_AuthExtKey_CryptoMode _input_CryptoMode, brp_buf _input_Key, size_t _input_Key_len) {
#else
brp_errcode brp_Desfire_AuthExtKey(brp_Desfire_AuthExtKey_t params) {
	brp_protocol protocol = params.protocol;
	brp_Desfire_AuthExtKey_SecureMessaging _input_SecureMessaging = params.SecureMessaging;
	unsigned _input_DesKeyNr = params.DesKeyNr;
	brp_Desfire_AuthExtKey_CryptoMode _input_CryptoMode = params.CryptoMode;
	brp_buf _input_Key = params.Key;
	size_t _input_Key_len = params.Key_len;
#endif
	brp_Desfire_AuthExtKey_SecureMessaging* SecureMessaging = &_input_SecureMessaging;
	unsigned* DesKeyNr = &_input_DesKeyNr;
	brp_Desfire_AuthExtKey_CryptoMode* CryptoMode = &_input_CryptoMode;
	brp_buf* Key = &_input_Key;
	size_t* Key_len = &_input_Key_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 2000);
	if (_input_CryptoMode == 0) _input_CryptoMode = (brp_Desfire_AuthExtKey_CryptoMode)4;
	brp_frame_write_int8(_frame, (unsigned)(*SecureMessaging));
	brp_frame_write_int8(_frame, (unsigned)(*DesKeyNr));
	brp_frame_write_int8(_frame, (unsigned)(*CryptoMode));
	brp_frame_write_int8(_frame, (unsigned)(*Key_len));
	brp_frame_write(_frame, (brp_buf)(*Key), (*Key_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_SelectApplication(brp_protocol protocol, unsigned _input_AppId) {
#else
brp_errcode brp_Desfire_SelectApplication(brp_Desfire_SelectApplication_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_AppId = params.AppId;
#endif
	unsigned* AppId = &_input_AppId;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 2000);
	brp_frame_write_int32(_frame, (unsigned)(*AppId));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_ReadData(brp_protocol protocol, unsigned _input_FileId, unsigned _input_Adr, unsigned _input_Len, brp_Desfire_ReadData_Mode _input_Mode, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_Desfire_ReadData(brp_Desfire_ReadData_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_FileId = params.FileId;
	unsigned _input_Adr = params.Adr;
	unsigned _input_Len = params.Len;
	brp_Desfire_ReadData_Mode _input_Mode = params.Mode;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* FileId = &_input_FileId;
	unsigned* Adr = &_input_Adr;
	unsigned* Len = &_input_Len;
	brp_Desfire_ReadData_Mode* Mode = &_input_Mode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 3000);
	brp_frame_write_int8(_frame, (unsigned)(*FileId));
	brp_frame_write_int32(_frame, (unsigned)(*Adr));
	brp_frame_write_int16(_frame, (unsigned)(*Len));
	brp_frame_write_int8(_frame, (unsigned)(*Mode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int16(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_WriteData(brp_protocol protocol, unsigned _input_FileId, unsigned _input_Adr, brp_buf _input_Data, size_t _input_Data_len, brp_Desfire_WriteData_Mode _input_Mode) {
#else
brp_errcode brp_Desfire_WriteData(brp_Desfire_WriteData_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_FileId = params.FileId;
	unsigned _input_Adr = params.Adr;
	brp_buf _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
	brp_Desfire_WriteData_Mode _input_Mode = params.Mode;
#endif
	unsigned* FileId = &_input_FileId;
	unsigned* Adr = &_input_Adr;
	brp_buf* Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	brp_Desfire_WriteData_Mode* Mode = &_input_Mode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 3000);
	brp_frame_write_int8(_frame, (unsigned)(*FileId));
	brp_frame_write_int32(_frame, (unsigned)(*Adr));
	brp_frame_write_int16(_frame, (unsigned)(*Data_len));
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	brp_frame_write_int8(_frame, (unsigned)(*Mode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_ChangeExtKey(brp_protocol protocol, brp_Desfire_ChangeExtKey_MasterKeyType _input_MasterKeyType, bool _input_IsKeySet, bool _input_IsAesKey, bool _input_IsVersion, bool _input_IsChangeKey, unsigned _input_KeyNo, unsigned _input_KeyVersion, brp_buf _input_NewKey, size_t _input_NewKey_len, brp_buf _input_OldKey, size_t _input_OldKey_len, unsigned _input_KeySet) {
#else
brp_errcode brp_Desfire_ChangeExtKey(brp_Desfire_ChangeExtKey_t params) {
	brp_protocol protocol = params.protocol;
	brp_Desfire_ChangeExtKey_MasterKeyType _input_MasterKeyType = params.MasterKeyType;
	bool _input_IsKeySet = params.IsKeySet;
	bool _input_IsAesKey = params.IsAesKey;
	bool _input_IsVersion = params.IsVersion;
	bool _input_IsChangeKey = params.IsChangeKey;
	unsigned _input_KeyNo = params.KeyNo;
	unsigned _input_KeyVersion = params.KeyVersion;
	brp_buf _input_NewKey = params.NewKey;
	size_t _input_NewKey_len = params.NewKey_len;
	brp_buf _input_OldKey = params.OldKey;
	size_t _input_OldKey_len = params.OldKey_len;
	unsigned _input_KeySet = params.KeySet;
#endif
	brp_Desfire_ChangeExtKey_MasterKeyType* MasterKeyType = &_input_MasterKeyType;
	bool* IsKeySet = &_input_IsKeySet;
	bool* IsAesKey = &_input_IsAesKey;
	bool* IsVersion = &_input_IsVersion;
	bool* IsChangeKey = &_input_IsChangeKey;
	unsigned* KeyNo = &_input_KeyNo;
	unsigned* KeyVersion = &_input_KeyVersion;
	brp_buf* NewKey = &_input_NewKey;
	size_t* NewKey_len = &_input_NewKey_len;
	brp_buf* OldKey = &_input_OldKey;
	size_t* OldKey_len = &_input_OldKey_len;
	unsigned* KeySet = &_input_KeySet;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 2000);
	if(!(*IsVersion) && (*KeyVersion)) (*IsVersion) = true;
	if(!(*IsKeySet) && (*KeySet)) (*IsKeySet) = true;
	unsigned _bitmask_884d = 0;
	_bitmask_884d |= (*MasterKeyType & 0b11) << 6;
	_bitmask_884d |= (*IsKeySet & 0b1) << 3;
	_bitmask_884d |= (*IsAesKey & 0b1) << 2;
	_bitmask_884d |= (*IsVersion & 0b1) << 1;
	_bitmask_884d |= (*IsChangeKey & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_884d);
	brp_frame_write_int8(_frame, (unsigned)(*KeyNo));
	if(*IsVersion) {
		brp_frame_write_int8(_frame, (unsigned)(*KeyVersion));
	}
	brp_frame_write_int8(_frame, (unsigned)(*NewKey_len));
	brp_frame_write(_frame, (brp_buf)(*NewKey), (*NewKey_len));
	brp_frame_write_int8(_frame, (unsigned)(*OldKey_len));
	brp_frame_write(_frame, (brp_buf)(*OldKey), (*OldKey_len));
	if(*IsKeySet) {
		brp_frame_write_int8(_frame, (unsigned)(*KeySet));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_ChangeKey(brp_protocol protocol, bool _input_IsKeySet, bool _input_IsMasterKey, bool _input_IsChangeKey, unsigned _input_KeyNr, brp_Desfire_ChangeKey_NewKeyDivMode _input_NewKeyDivMode, bool _input_NewKeyHasDivData, bool _input_NewKeyHasExtIdx, unsigned _input_NewKeyIdx, brp_Desfire_ChangeKey_CurKeyDivMode _input_CurKeyDivMode, bool _input_CurKeyHasDivData, bool _input_CurKeyHasExtIdx, unsigned _input_CurKeyIdx, brp_buf _input_NewKeyDivData, size_t _input_NewKeyDivData_len, brp_buf _input_CurKeyDivData, size_t _input_CurKeyDivData_len, unsigned _input_NewKeyExtIdx, unsigned _input_CurKeyExtIdx, unsigned _input_KeySet) {
#else
brp_errcode brp_Desfire_ChangeKey(brp_Desfire_ChangeKey_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_IsKeySet = params.IsKeySet;
	bool _input_IsMasterKey = params.IsMasterKey;
	bool _input_IsChangeKey = params.IsChangeKey;
	unsigned _input_KeyNr = params.KeyNr;
	brp_Desfire_ChangeKey_NewKeyDivMode _input_NewKeyDivMode = params.NewKeyDivMode;
	bool _input_NewKeyHasDivData = params.NewKeyHasDivData;
	bool _input_NewKeyHasExtIdx = params.NewKeyHasExtIdx;
	unsigned _input_NewKeyIdx = params.NewKeyIdx;
	brp_Desfire_ChangeKey_CurKeyDivMode _input_CurKeyDivMode = params.CurKeyDivMode;
	bool _input_CurKeyHasDivData = params.CurKeyHasDivData;
	bool _input_CurKeyHasExtIdx = params.CurKeyHasExtIdx;
	unsigned _input_CurKeyIdx = params.CurKeyIdx;
	brp_buf _input_NewKeyDivData = params.NewKeyDivData;
	size_t _input_NewKeyDivData_len = params.NewKeyDivData_len;
	brp_buf _input_CurKeyDivData = params.CurKeyDivData;
	size_t _input_CurKeyDivData_len = params.CurKeyDivData_len;
	unsigned _input_NewKeyExtIdx = params.NewKeyExtIdx;
	unsigned _input_CurKeyExtIdx = params.CurKeyExtIdx;
	unsigned _input_KeySet = params.KeySet;
#endif
	bool* IsKeySet = &_input_IsKeySet;
	bool* IsMasterKey = &_input_IsMasterKey;
	bool* IsChangeKey = &_input_IsChangeKey;
	unsigned* KeyNr = &_input_KeyNr;
	brp_Desfire_ChangeKey_NewKeyDivMode* NewKeyDivMode = &_input_NewKeyDivMode;
	bool* NewKeyHasDivData = &_input_NewKeyHasDivData;
	bool* NewKeyHasExtIdx = &_input_NewKeyHasExtIdx;
	unsigned* NewKeyIdx = &_input_NewKeyIdx;
	brp_Desfire_ChangeKey_CurKeyDivMode* CurKeyDivMode = &_input_CurKeyDivMode;
	bool* CurKeyHasDivData = &_input_CurKeyHasDivData;
	bool* CurKeyHasExtIdx = &_input_CurKeyHasExtIdx;
	unsigned* CurKeyIdx = &_input_CurKeyIdx;
	brp_buf* NewKeyDivData = &_input_NewKeyDivData;
	size_t* NewKeyDivData_len = &_input_NewKeyDivData_len;
	brp_buf* CurKeyDivData = &_input_CurKeyDivData;
	size_t* CurKeyDivData_len = &_input_CurKeyDivData_len;
	unsigned* NewKeyExtIdx = &_input_NewKeyExtIdx;
	unsigned* CurKeyExtIdx = &_input_CurKeyExtIdx;
	unsigned* KeySet = &_input_KeySet;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int32(_frame, 2000);
	if(!(*CurKeyHasExtIdx) && (*CurKeyExtIdx)) (*CurKeyHasExtIdx) = true;
	if(!(*CurKeyHasDivData) && (CurKeyDivData)) (*CurKeyHasDivData) = true;
	if(!(*NewKeyHasExtIdx) && (*NewKeyExtIdx)) (*NewKeyHasExtIdx) = true;
	if(!(*NewKeyHasDivData) && (NewKeyDivData)) (*NewKeyHasDivData) = true;
	if(!(*IsKeySet) && (*KeySet)) (*IsKeySet) = true;
	unsigned _bitmask_d665 = 0;
	_bitmask_d665 |= (*IsKeySet & 0b1) << 2;
	_bitmask_d665 |= (*IsMasterKey & 0b1) << 1;
	_bitmask_d665 |= (*IsChangeKey & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_d665);
	brp_frame_write_int8(_frame, (unsigned)(*KeyNr));
	unsigned _bitmask_c32e = 0;
	_bitmask_c32e |= (*NewKeyDivMode & 0b11) << 3;
	_bitmask_c32e |= (*NewKeyHasDivData & 0b1) << 1;
	_bitmask_c32e |= (*NewKeyHasExtIdx & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_c32e);
	brp_frame_write_int8(_frame, (unsigned)(*NewKeyIdx));
	unsigned _bitmask_95be = 0;
	_bitmask_95be |= (*CurKeyDivMode & 0b11) << 3;
	_bitmask_95be |= (*CurKeyHasDivData & 0b1) << 1;
	_bitmask_95be |= (*CurKeyHasExtIdx & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_95be);
	brp_frame_write_int8(_frame, (unsigned)(*CurKeyIdx));
	if(*NewKeyHasDivData) {
		brp_frame_write_int8(_frame, (unsigned)(*NewKeyDivData_len));
		brp_frame_write(_frame, (brp_buf)(*NewKeyDivData), (*NewKeyDivData_len));
	}
	if(*CurKeyHasDivData) {
		brp_frame_write_int8(_frame, (unsigned)(*CurKeyDivData_len));
		brp_frame_write(_frame, (brp_buf)(*CurKeyDivData), (*CurKeyDivData_len));
	}
	if(*NewKeyHasExtIdx) {
		brp_frame_write_int8(_frame, (unsigned)(*NewKeyExtIdx));
	}
	if(*CurKeyHasExtIdx) {
		brp_frame_write_int8(_frame, (unsigned)(*CurKeyExtIdx));
	}
	if(*IsKeySet) {
		brp_frame_write_int8(_frame, (unsigned)(*KeySet));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_SetFraming(brp_protocol protocol, brp_Desfire_SetFraming_CommMode _input_CommMode) {
#else
brp_errcode brp_Desfire_SetFraming(brp_Desfire_SetFraming_t params) {
	brp_protocol protocol = params.protocol;
	brp_Desfire_SetFraming_CommMode _input_CommMode = params.CommMode;
#endif
	brp_Desfire_SetFraming_CommMode* CommMode = &_input_CommMode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int32(_frame, 100);
	if (_input_CommMode == 0) _input_CommMode = (brp_Desfire_SetFraming_CommMode)1;
	brp_frame_write_int8(_frame, (unsigned)(*CommMode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_ResetAuthentication(brp_protocol protocol) {
#else
brp_errcode brp_Desfire_ResetAuthentication(brp_Desfire_ResetAuthentication_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 17);
	brp_frame_write_int32(_frame, 2000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_CreateDam(brp_protocol protocol, unsigned _input_AppId, brp_buf _input_AppParams, size_t _input_AppParams_len, brp_buf _input_EncryptedDefaultDamKey, size_t _input_EncryptedDefaultDamKey_len, brp_buf _input_DamMacKey, size_t _input_DamMacKey_len) {
#else
brp_errcode brp_Desfire_CreateDam(brp_Desfire_CreateDam_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_AppId = params.AppId;
	brp_buf _input_AppParams = params.AppParams;
	size_t _input_AppParams_len = params.AppParams_len;
	brp_buf _input_EncryptedDefaultDamKey = params.EncryptedDefaultDamKey;
	size_t _input_EncryptedDefaultDamKey_len = params.EncryptedDefaultDamKey_len;
	brp_buf _input_DamMacKey = params.DamMacKey;
	size_t _input_DamMacKey_len = params.DamMacKey_len;
#endif
	unsigned* AppId = &_input_AppId;
	brp_buf* AppParams = &_input_AppParams;
	size_t* AppParams_len = &_input_AppParams_len;
	brp_buf* EncryptedDefaultDamKey = &_input_EncryptedDefaultDamKey;
	size_t* EncryptedDefaultDamKey_len = &_input_EncryptedDefaultDamKey_len;
	brp_buf* DamMacKey = &_input_DamMacKey;
	size_t* DamMacKey_len = &_input_DamMacKey_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int32(_frame, 2000);
	brp_frame_write_int32(_frame, (unsigned)(*AppId));
	brp_frame_write_int8(_frame, (unsigned)(*AppParams_len));
	brp_frame_write(_frame, (brp_buf)(*AppParams), (*AppParams_len));
	brp_frame_write_int8(_frame, (unsigned)(*EncryptedDefaultDamKey_len));
	brp_frame_write(_frame, (brp_buf)(*EncryptedDefaultDamKey), (*EncryptedDefaultDamKey_len));
	brp_frame_write_int8(_frame, (unsigned)(*DamMacKey_len));
	brp_frame_write(_frame, (brp_buf)(*DamMacKey), (*DamMacKey_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_GetOriginalitySignature(brp_protocol protocol, brp_buf* Signature, size_t* Signature_len, brp_mempool *mempool) {
#else
brp_errcode brp_Desfire_GetOriginalitySignature(brp_Desfire_GetOriginalitySignature_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Signature = params.Signature;
	size_t* Signature_len = params.Signature_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Signature_len;
	if(Signature_len == NULL) Signature_len = &_Signature_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int32(_frame, 2000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Signature_len) = brp_frame_read_int8(&_reader);
	if (Signature != NULL) {
		(*Signature) = (brp_buf)brp_mempool_create_buf(mempool, (*Signature_len));
		if((*Signature) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Signature), (*Signature_len));
	} else
		brp_frame_skip(&_reader, (*Signature_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_VirtualCardSelect(brp_protocol protocol, bool _input_ForceVcsAuthentication, bool _input_UseExtVcSelectKeys, unsigned _input_DiversifyMacKey, bool _input_DiversifyEncKey, bool _input_UseVcSelectKeys, brp_buf _input_IID, size_t _input_IID_len, unsigned _input_EncKeyIdx, unsigned _input_MacKeyIdx, brp_buf _input_DivData, size_t _input_DivData_len, brp_buf _input_EncKey, size_t _input_EncKey_len, brp_buf _input_MacKey, size_t _input_MacKey_len, unsigned* FciType, brp_buf* Fci, size_t* Fci_len, brp_mempool *mempool) {
#else
brp_errcode brp_Desfire_VirtualCardSelect(brp_Desfire_VirtualCardSelect_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_ForceVcsAuthentication = params.ForceVcsAuthentication;
	bool _input_UseExtVcSelectKeys = params.UseExtVcSelectKeys;
	unsigned _input_DiversifyMacKey = params.DiversifyMacKey;
	bool _input_DiversifyEncKey = params.DiversifyEncKey;
	bool _input_UseVcSelectKeys = params.UseVcSelectKeys;
	brp_buf _input_IID = params.IID;
	size_t _input_IID_len = params.IID_len;
	unsigned _input_EncKeyIdx = params.EncKeyIdx;
	unsigned _input_MacKeyIdx = params.MacKeyIdx;
	brp_buf _input_DivData = params.DivData;
	size_t _input_DivData_len = params.DivData_len;
	brp_buf _input_EncKey = params.EncKey;
	size_t _input_EncKey_len = params.EncKey_len;
	brp_buf _input_MacKey = params.MacKey;
	size_t _input_MacKey_len = params.MacKey_len;
	unsigned* FciType = params.FciType;
	brp_buf* Fci = params.Fci;
	size_t* Fci_len = params.Fci_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* ForceVcsAuthentication = &_input_ForceVcsAuthentication;
	bool* UseExtVcSelectKeys = &_input_UseExtVcSelectKeys;
	unsigned* DiversifyMacKey = &_input_DiversifyMacKey;
	bool* DiversifyEncKey = &_input_DiversifyEncKey;
	bool* UseVcSelectKeys = &_input_UseVcSelectKeys;
	brp_buf* IID = &_input_IID;
	size_t* IID_len = &_input_IID_len;
	unsigned* EncKeyIdx = &_input_EncKeyIdx;
	unsigned* MacKeyIdx = &_input_MacKeyIdx;
	brp_buf* DivData = &_input_DivData;
	size_t* DivData_len = &_input_DivData_len;
	brp_buf* EncKey = &_input_EncKey;
	size_t* EncKey_len = &_input_EncKey_len;
	brp_buf* MacKey = &_input_MacKey;
	size_t* MacKey_len = &_input_MacKey_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Fci_len;
	if(Fci_len == NULL) Fci_len = &_Fci_len;
	unsigned _tmp_FciType;
	if (FciType == NULL) FciType = &_tmp_FciType;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 11);
	brp_frame_write_int32(_frame, 2000);
	if(!(*UseVcSelectKeys) && (*EncKeyIdx || *MacKeyIdx)) (*UseVcSelectKeys) = true;
	if(!(*UseExtVcSelectKeys) && (EncKey || MacKey)) (*UseExtVcSelectKeys) = true;
	unsigned _bitmask_cf6a = 0;
	_bitmask_cf6a |= (*ForceVcsAuthentication & 0b1) << 5;
	_bitmask_cf6a |= (*UseExtVcSelectKeys & 0b1) << 4;
	_bitmask_cf6a |= (*DiversifyMacKey & 0b11) << 2;
	_bitmask_cf6a |= (*DiversifyEncKey & 0b1) << 1;
	_bitmask_cf6a |= (*UseVcSelectKeys & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_cf6a);
	brp_frame_write_int8(_frame, (unsigned)(*IID_len));
	brp_frame_write(_frame, (brp_buf)(*IID), (*IID_len));
	if(*UseVcSelectKeys) {
		brp_frame_write_int16(_frame, (unsigned)(*EncKeyIdx));
		brp_frame_write_int16(_frame, (unsigned)(*MacKeyIdx));
	}
	if(((((*DiversifyMacKey) == (1)) || ((*DiversifyMacKey) == (2))) || ((*DiversifyMacKey) == (3))) || (*DiversifyEncKey)) {
		brp_frame_write_int8(_frame, (unsigned)(*DivData_len));
		brp_frame_write(_frame, (brp_buf)(*DivData), (*DivData_len));
	}
	if(*UseExtVcSelectKeys) {
		brp_frame_write_int8(_frame, (unsigned)(*EncKey_len));
		brp_frame_write(_frame, (brp_buf)(*EncKey), (*EncKey_len));
		brp_frame_write_int8(_frame, (unsigned)(*MacKey_len));
		brp_frame_write(_frame, (brp_buf)(*MacKey), (*MacKey_len));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*FciType) = (unsigned)brp_frame_read_int8(&_reader);
	(*Fci_len) = brp_frame_read_int8(&_reader);
	if (Fci != NULL) {
		(*Fci) = (brp_buf)brp_mempool_create_buf(mempool, (*Fci_len));
		if((*Fci) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Fci), (*Fci_len));
	} else
		brp_frame_skip(&_reader, (*Fci_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_ProxCheck(brp_protocol protocol, unsigned _input_M, bool _input_UseExtProxKey, bool _input_DiversifyProxKey, bool _input_UseProxKey, unsigned _input_ProxKeyIdx, brp_buf _input_DivData, size_t _input_DivData_len, brp_buf _input_ProxKey, size_t _input_ProxKey_len) {
#else
brp_errcode brp_Desfire_ProxCheck(brp_Desfire_ProxCheck_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_M = params.M;
	bool _input_UseExtProxKey = params.UseExtProxKey;
	bool _input_DiversifyProxKey = params.DiversifyProxKey;
	bool _input_UseProxKey = params.UseProxKey;
	unsigned _input_ProxKeyIdx = params.ProxKeyIdx;
	brp_buf _input_DivData = params.DivData;
	size_t _input_DivData_len = params.DivData_len;
	brp_buf _input_ProxKey = params.ProxKey;
	size_t _input_ProxKey_len = params.ProxKey_len;
#endif
	unsigned* M = &_input_M;
	bool* UseExtProxKey = &_input_UseExtProxKey;
	bool* DiversifyProxKey = &_input_DiversifyProxKey;
	bool* UseProxKey = &_input_UseProxKey;
	unsigned* ProxKeyIdx = &_input_ProxKeyIdx;
	brp_buf* DivData = &_input_DivData;
	size_t* DivData_len = &_input_DivData_len;
	brp_buf* ProxKey = &_input_ProxKey;
	size_t* ProxKey_len = &_input_ProxKey_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 12);
	brp_frame_write_int32(_frame, 2000);
	if (_input_M == 0) _input_M = (unsigned)4;
	if(!(*UseProxKey) && (*ProxKeyIdx)) (*UseProxKey) = true;
	if(!(*UseExtProxKey) && (ProxKey)) (*UseExtProxKey) = true;
	unsigned _bitmask_08f2 = 0;
	_bitmask_08f2 |= (*M & 0b111) << 4;
	_bitmask_08f2 |= (*UseExtProxKey & 0b1) << 2;
	_bitmask_08f2 |= (*DiversifyProxKey & 0b1) << 1;
	_bitmask_08f2 |= (*UseProxKey & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_08f2);
	if(*UseProxKey) {
		brp_frame_write_int16(_frame, (unsigned)(*ProxKeyIdx));
	}
	if((*DiversifyProxKey) && (*UseProxKey)) {
		brp_frame_write_int8(_frame, (unsigned)(*DivData_len));
		brp_frame_write(_frame, (brp_buf)(*DivData), (*DivData_len));
	}
	if(*UseExtProxKey) {
		brp_frame_write_int8(_frame, (unsigned)(*ProxKey_len));
		brp_frame_write(_frame, (brp_buf)(*ProxKey), (*ProxKey_len));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Desfire_GetDfNames(brp_protocol protocol, brp_Desfire_GetDfNames_AppNr_Entry** AppNr, size_t* AppNr_len, brp_mempool *mempool) {
#else
brp_errcode brp_Desfire_GetDfNames(brp_Desfire_GetDfNames_t params) {
	brp_protocol protocol = params.protocol;
	brp_Desfire_GetDfNames_AppNr_Entry** AppNr = params.AppNr;
	size_t* AppNr_len = params.AppNr_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _AppNr_len;
	if(AppNr_len == NULL) AppNr_len = &_AppNr_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int8(_frame, 13);
	brp_frame_write_int32(_frame, 3000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*AppNr_len) = brp_frame_read_int8(&_reader);
	if (AppNr != NULL) {
		(*AppNr) = (brp_Desfire_GetDfNames_AppNr_Entry*)brp_mempool_create_buf(mempool, (*AppNr_len) * sizeof(brp_Desfire_GetDfNames_AppNr_Entry));
		if((*AppNr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _AppNr_ndx = 0;(_AppNr_ndx < (*AppNr_len)) & !brp_frame_read_err(&_reader);_AppNr_ndx++) {
		brp_Desfire_GetDfNames_AppNr_Entry _AppNr_Entry;
		brp_Desfire_GetDfNames_AppNr_Entry *AppNr_Entry = &_AppNr_Entry;
		unsigned _AppId;
		unsigned *AppId = &_AppId;
		unsigned _IsoFileId;
		unsigned *IsoFileId = &_IsoFileId;
		brp_buf _IsoDfName;
		brp_buf *IsoDfName = &_IsoDfName;
		size_t _IsoDfName_len;
		size_t *IsoDfName_len = &_IsoDfName_len;
		(*AppId) = (unsigned)brp_frame_read_int32(&_reader);
		(*IsoFileId) = (unsigned)brp_frame_read_int16(&_reader);
		(*IsoDfName_len) = brp_frame_read_int8(&_reader);
		if (IsoDfName != NULL) {
			(*IsoDfName) = (brp_buf)brp_mempool_create_buf(mempool, (*IsoDfName_len));
			if((*IsoDfName) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			brp_frame_read(&_reader, (brp_buf)(*IsoDfName), (*IsoDfName_len));
		} else
			brp_frame_skip(&_reader, (*IsoDfName_len));
		if(AppNr_Entry != NULL) {
			AppNr_Entry->AppId = *AppId;
			AppNr_Entry->IsoFileId = *IsoFileId;
			AppNr_Entry->IsoDfName = *IsoDfName;
			AppNr_Entry->IsoDfName_len = *IsoDfName_len;
		}
		if (AppNr != NULL)
			(*AppNr)[_AppNr_ndx] = *AppNr_Entry;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_EthActivate(brp_protocol protocol, brp_DHWCtrlPinMapEntry* _input_PinMap, size_t _input_PinMap_len, unsigned _input_PeripheralIndex, brp_buf _input_MacAddress) {
#else
brp_errcode brp_DHWCtrl_EthActivate(brp_DHWCtrl_EthActivate_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlPinMapEntry* _input_PinMap = params.PinMap;
	size_t _input_PinMap_len = params.PinMap_len;
	unsigned _input_PeripheralIndex = params.PeripheralIndex;
	brp_buf _input_MacAddress = params.MacAddress;
#endif
	brp_DHWCtrlPinMapEntry** PinMap = &_input_PinMap;
	size_t* PinMap_len = &_input_PinMap_len;
	unsigned* PeripheralIndex = &_input_PeripheralIndex;
	brp_buf* MacAddress = &_input_MacAddress;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*PinMap_len));
	for(size_t _PinMap_ndx = 0;_PinMap_ndx < (*PinMap_len);_PinMap_ndx++) {
		brp_DHWCtrlPinMapEntry _Entry = (*PinMap)[_PinMap_ndx];
		brp_DHWCtrlPinMapEntry* Entry = &_Entry;
		brp_DHWCtrlPinName _Name = (Entry)->Name;
		brp_DHWCtrlPinName* Name = &_Name;
		brp_DHWCtrlGpioPin _Pin = (Entry)->Pin;
		brp_DHWCtrlGpioPin* Pin = &_Pin;
		brp_frame_write_int8(_frame, (unsigned)(*Name));
		brp_DHWCtrlGpioPort _Port = (Pin)->Port;
		brp_DHWCtrlGpioPort* Port = &_Port;
		unsigned _Number = (Pin)->Number;
		unsigned* Number = &_Number;
		brp_frame_write_int8(_frame, (unsigned)(*Port));
		brp_frame_write_int8(_frame, (unsigned)(*Number));
	}
	brp_frame_write_int8(_frame, (unsigned)(*PeripheralIndex));
	size_t _MacAddress_len_val = 6;
	size_t* MacAddress_len = &_MacAddress_len_val;
	brp_frame_write(_frame, (brp_buf)(*MacAddress), (*MacAddress_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_EthDeactivate(brp_protocol protocol, unsigned _input_Index) {
#else
brp_errcode brp_DHWCtrl_EthDeactivate(brp_DHWCtrl_EthDeactivate_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
#endif
	unsigned* Index = &_input_Index;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_EthSendFrame(brp_protocol protocol, unsigned _input_Index, brp_buf _input_DstMac, brp_buf _input_SrcMac, brp_DHWCtrlEtherType _input_EtherType, brp_buf _input_Payload, size_t _input_Payload_len) {
#else
brp_errcode brp_DHWCtrl_EthSendFrame(brp_DHWCtrl_EthSendFrame_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	brp_buf _input_DstMac = params.DstMac;
	brp_buf _input_SrcMac = params.SrcMac;
	brp_DHWCtrlEtherType _input_EtherType = params.EtherType;
	brp_buf _input_Payload = params.Payload;
	size_t _input_Payload_len = params.Payload_len;
#endif
	unsigned* Index = &_input_Index;
	brp_buf* DstMac = &_input_DstMac;
	brp_buf* SrcMac = &_input_SrcMac;
	brp_DHWCtrlEtherType* EtherType = &_input_EtherType;
	brp_buf* Payload = &_input_Payload;
	size_t* Payload_len = &_input_Payload_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	size_t _DstMac_len_val = 6;
	size_t* DstMac_len = &_DstMac_len_val;
	brp_frame_write(_frame, (brp_buf)(*DstMac), (*DstMac_len));
	size_t _SrcMac_len_val = 6;
	size_t* SrcMac_len = &_SrcMac_len_val;
	brp_frame_write(_frame, (brp_buf)(*SrcMac), (*SrcMac_len));
	brp_frame_write_int16(_frame, (unsigned)(*EtherType));
	brp_frame_write(_frame, (brp_buf)(*Payload), (*Payload_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_EthRecvFrame(brp_protocol protocol, unsigned _input_Index, unsigned _input_TimeoutMs, unsigned* TimestampUs, unsigned* Seq, bool* RxOverflow, bool* CrcError, bool* Truncated, brp_buf* DstMac, brp_buf* SrcMac, brp_DHWCtrlEtherType* EtherType, brp_buf* Payload, size_t* Payload_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrl_EthRecvFrame(brp_DHWCtrl_EthRecvFrame_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	unsigned _input_TimeoutMs = params.TimeoutMs;
	unsigned* TimestampUs = params.TimestampUs;
	unsigned* Seq = params.Seq;
	bool* RxOverflow = params.RxOverflow;
	bool* CrcError = params.CrcError;
	bool* Truncated = params.Truncated;
	brp_buf* DstMac = params.DstMac;
	brp_buf* SrcMac = params.SrcMac;
	brp_DHWCtrlEtherType* EtherType = params.EtherType;
	brp_buf* Payload = params.Payload;
	size_t* Payload_len = params.Payload_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Index = &_input_Index;
	unsigned* TimeoutMs = &_input_TimeoutMs;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Payload_len;
	if(Payload_len == NULL) Payload_len = &_Payload_len;
	unsigned _tmp_TimestampUs;
	if (TimestampUs == NULL) TimestampUs = &_tmp_TimestampUs;
	unsigned _tmp_Seq;
	if (Seq == NULL) Seq = &_tmp_Seq;
	bool _tmp_RxOverflow;
	if (RxOverflow == NULL) RxOverflow = &_tmp_RxOverflow;
	bool _tmp_CrcError;
	if (CrcError == NULL) CrcError = &_tmp_CrcError;
	bool _tmp_Truncated;
	if (Truncated == NULL) Truncated = &_tmp_Truncated;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int16(_frame, (unsigned)(*TimeoutMs));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*TimestampUs) = (unsigned)brp_frame_read_int32(&_reader);
	(*Seq) = (unsigned)brp_frame_read_int32(&_reader);
	unsigned _bitmask_5a17 = brp_frame_read_int8(&_reader);
	if(RxOverflow != NULL)
		(*RxOverflow) = (_bitmask_5a17>>7) & 0b1;
	if(CrcError != NULL)
		(*CrcError) = (_bitmask_5a17>>6) & 0b1;
	if(Truncated != NULL)
		(*Truncated) = (_bitmask_5a17>>5) & 0b1;
	size_t _DstMac_len = 6;
	size_t* DstMac_len = &_DstMac_len;
	if (DstMac != NULL) {
		(*DstMac) = (brp_buf)brp_mempool_create_buf(mempool, (*DstMac_len));
		if((*DstMac) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*DstMac), (*DstMac_len));
	} else
		brp_frame_skip(&_reader, (*DstMac_len));
	size_t _SrcMac_len = 6;
	size_t* SrcMac_len = &_SrcMac_len;
	if (SrcMac != NULL) {
		(*SrcMac) = (brp_buf)brp_mempool_create_buf(mempool, (*SrcMac_len));
		if((*SrcMac) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*SrcMac), (*SrcMac_len));
	} else
		brp_frame_skip(&_reader, (*SrcMac_len));
	int _EtherType_int_val = brp_frame_read_int16(&_reader);
	if (EtherType != NULL) {
		if (brp_DHWCtrlEtherType_is_valid(_EtherType_int_val))
			(*EtherType) = (brp_DHWCtrlEtherType)_EtherType_int_val;
		else
			(*EtherType) = brp_DHWCtrlEtherType_undefined;
	}
	(*Payload_len) = brp_frame_rest( & _reader);
	if (Payload != NULL) {
		(*Payload) = (brp_buf)brp_mempool_create_buf(mempool, (*Payload_len));
		if((*Payload) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Payload), (*Payload_len));
	} else
		brp_frame_skip(&_reader, (*Payload_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_EthWaitLinkState(brp_protocol protocol, unsigned _input_Index, brp_DHWCtrlEthLinkState _input_State, unsigned _input_TimeoutMs) {
#else
brp_errcode brp_DHWCtrl_EthWaitLinkState(brp_DHWCtrl_EthWaitLinkState_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	brp_DHWCtrlEthLinkState _input_State = params.State;
	unsigned _input_TimeoutMs = params.TimeoutMs;
#endif
	unsigned* Index = &_input_Index;
	brp_DHWCtrlEthLinkState* State = &_input_State;
	unsigned* TimeoutMs = &_input_TimeoutMs;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int8(_frame, (unsigned)(*State));
	brp_frame_write_int16(_frame, (unsigned)(*TimeoutMs));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_EthGetCommMode(brp_protocol protocol, unsigned _input_Index, brp_DHWCtrl_EthGetCommMode_Speed* Speed, brp_DHWCtrl_EthGetCommMode_Duplex* Duplex) {
#else
brp_errcode brp_DHWCtrl_EthGetCommMode(brp_DHWCtrl_EthGetCommMode_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	brp_DHWCtrl_EthGetCommMode_Speed* Speed = params.Speed;
	brp_DHWCtrl_EthGetCommMode_Duplex* Duplex = params.Duplex;
#endif
	unsigned* Index = &_input_Index;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	int _Speed_int_val = brp_frame_read_int8(&_reader);
	if (! brp_DHWCtrl_EthGetCommMode_Speed_is_valid(_Speed_int_val))
		return BRP_ERR_PAYLOAD_FORMAT;
	if (Speed != NULL)
		(*Speed) = (brp_DHWCtrl_EthGetCommMode_Speed)_Speed_int_val;
	int _Duplex_int_val = brp_frame_read_int8(&_reader);
	if (! brp_DHWCtrl_EthGetCommMode_Duplex_is_valid(_Duplex_int_val))
		return BRP_ERR_PAYLOAD_FORMAT;
	if (Duplex != NULL)
		(*Duplex) = (brp_DHWCtrl_EthGetCommMode_Duplex)_Duplex_int_val;
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_GpioConfigure(brp_protocol protocol, brp_DHWCtrlGpioPin _input_Pin, brp_DHWCtrl_GpioConfigure_Mode _input_Mode) {
#else
brp_errcode brp_DHWCtrl_GpioConfigure(brp_DHWCtrl_GpioConfigure_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlGpioPin _input_Pin = params.Pin;
	brp_DHWCtrl_GpioConfigure_Mode _input_Mode = params.Mode;
#endif
	brp_DHWCtrlGpioPin* Pin = &_input_Pin;
	brp_DHWCtrl_GpioConfigure_Mode* Mode = &_input_Mode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int32(_frame, 100);
	brp_DHWCtrlGpioPort _Port = (Pin)->Port;
	brp_DHWCtrlGpioPort* Port = &_Port;
	unsigned _Number = (Pin)->Number;
	unsigned* Number = &_Number;
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_frame_write_int8(_frame, (unsigned)(*Number));
	brp_frame_write_int8(_frame, (unsigned)(*Mode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_GpioSetState(brp_protocol protocol, brp_DHWCtrlGpioPin _input_Pin, brp_DHWCtrlGpioLevel _input_Level) {
#else
brp_errcode brp_DHWCtrl_GpioSetState(brp_DHWCtrl_GpioSetState_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlGpioPin _input_Pin = params.Pin;
	brp_DHWCtrlGpioLevel _input_Level = params.Level;
#endif
	brp_DHWCtrlGpioPin* Pin = &_input_Pin;
	brp_DHWCtrlGpioLevel* Level = &_input_Level;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 17);
	brp_frame_write_int32(_frame, 100);
	brp_DHWCtrlGpioPort _Port = (Pin)->Port;
	brp_DHWCtrlGpioPort* Port = &_Port;
	unsigned _Number = (Pin)->Number;
	unsigned* Number = &_Number;
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_frame_write_int8(_frame, (unsigned)(*Number));
	brp_frame_write_int8(_frame, (unsigned)(*Level));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_GpioWaitState(brp_protocol protocol, brp_DHWCtrlGpioPin _input_Pin, brp_DHWCtrlGpioLevel _input_Level, unsigned _input_TimeoutMs) {
#else
brp_errcode brp_DHWCtrl_GpioWaitState(brp_DHWCtrl_GpioWaitState_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlGpioPin _input_Pin = params.Pin;
	brp_DHWCtrlGpioLevel _input_Level = params.Level;
	unsigned _input_TimeoutMs = params.TimeoutMs;
#endif
	brp_DHWCtrlGpioPin* Pin = &_input_Pin;
	brp_DHWCtrlGpioLevel* Level = &_input_Level;
	unsigned* TimeoutMs = &_input_TimeoutMs;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 18);
	brp_frame_write_int32(_frame, 100);
	brp_DHWCtrlGpioPort _Port = (Pin)->Port;
	brp_DHWCtrlGpioPort* Port = &_Port;
	unsigned _Number = (Pin)->Number;
	unsigned* Number = &_Number;
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_frame_write_int8(_frame, (unsigned)(*Number));
	brp_frame_write_int8(_frame, (unsigned)(*Level));
	brp_frame_write_int16(_frame, (unsigned)(*TimeoutMs));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostActivate(brp_protocol protocol, brp_DHWCtrlPinMapEntry* _input_PinMap, size_t _input_PinMap_len, unsigned _input_PeripheralIndex) {
#else
brp_errcode brp_DHWCtrl_UsbHostActivate(brp_DHWCtrl_UsbHostActivate_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlPinMapEntry* _input_PinMap = params.PinMap;
	size_t _input_PinMap_len = params.PinMap_len;
	unsigned _input_PeripheralIndex = params.PeripheralIndex;
#endif
	brp_DHWCtrlPinMapEntry** PinMap = &_input_PinMap;
	size_t* PinMap_len = &_input_PinMap_len;
	unsigned* PeripheralIndex = &_input_PeripheralIndex;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 32);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*PinMap_len));
	for(size_t _PinMap_ndx = 0;_PinMap_ndx < (*PinMap_len);_PinMap_ndx++) {
		brp_DHWCtrlPinMapEntry _Entry = (*PinMap)[_PinMap_ndx];
		brp_DHWCtrlPinMapEntry* Entry = &_Entry;
		brp_DHWCtrlPinName _Name = (Entry)->Name;
		brp_DHWCtrlPinName* Name = &_Name;
		brp_DHWCtrlGpioPin _Pin = (Entry)->Pin;
		brp_DHWCtrlGpioPin* Pin = &_Pin;
		brp_frame_write_int8(_frame, (unsigned)(*Name));
		brp_DHWCtrlGpioPort _Port = (Pin)->Port;
		brp_DHWCtrlGpioPort* Port = &_Port;
		unsigned _Number = (Pin)->Number;
		unsigned* Number = &_Number;
		brp_frame_write_int8(_frame, (unsigned)(*Port));
		brp_frame_write_int8(_frame, (unsigned)(*Number));
	}
	brp_frame_write_int8(_frame, (unsigned)(*PeripheralIndex));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostDeactivate(brp_protocol protocol, unsigned _input_Index) {
#else
brp_errcode brp_DHWCtrl_UsbHostDeactivate(brp_DHWCtrl_UsbHostDeactivate_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
#endif
	unsigned* Index = &_input_Index;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostBusReset(brp_protocol protocol, unsigned _input_Index) {
#else
brp_errcode brp_DHWCtrl_UsbHostBusReset(brp_DHWCtrl_UsbHostBusReset_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
#endif
	unsigned* Index = &_input_Index;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 34);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostBusSuspend(brp_protocol protocol, unsigned _input_Index) {
#else
brp_errcode brp_DHWCtrl_UsbHostBusSuspend(brp_DHWCtrl_UsbHostBusSuspend_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
#endif
	unsigned* Index = &_input_Index;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 35);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostBusResume(brp_protocol protocol, unsigned _input_Index) {
#else
brp_errcode brp_DHWCtrl_UsbHostBusResume(brp_DHWCtrl_UsbHostBusResume_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
#endif
	unsigned* Index = &_input_Index;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 36);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostWaitPortStatus(brp_protocol protocol, unsigned _input_Index, brp_DHWCtrlUsbPortState _input_State, unsigned _input_TimeoutMs, brp_DHWCtrl_UsbHostWaitPortStatus_Speed* Speed) {
#else
brp_errcode brp_DHWCtrl_UsbHostWaitPortStatus(brp_DHWCtrl_UsbHostWaitPortStatus_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	brp_DHWCtrlUsbPortState _input_State = params.State;
	unsigned _input_TimeoutMs = params.TimeoutMs;
	brp_DHWCtrl_UsbHostWaitPortStatus_Speed* Speed = params.Speed;
#endif
	unsigned* Index = &_input_Index;
	brp_DHWCtrlUsbPortState* State = &_input_State;
	unsigned* TimeoutMs = &_input_TimeoutMs;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 37);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int8(_frame, (unsigned)(*State));
	brp_frame_write_int16(_frame, (unsigned)(*TimeoutMs));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	int _Speed_int_val = brp_frame_read_int8(&_reader);
	if (! brp_DHWCtrl_UsbHostWaitPortStatus_Speed_is_valid(_Speed_int_val))
		return BRP_ERR_PAYLOAD_FORMAT;
	if (Speed != NULL)
		(*Speed) = (brp_DHWCtrl_UsbHostWaitPortStatus_Speed)_Speed_int_val;
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostTransferCtrlIn(brp_protocol protocol, unsigned _input_Index, unsigned _input_Addr, unsigned _input_Mps, brp_buf _input_Setup, unsigned _input_InLen, unsigned _input_TimeoutMs, brp_buf* InData, size_t* InData_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrl_UsbHostTransferCtrlIn(brp_DHWCtrl_UsbHostTransferCtrlIn_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	unsigned _input_Addr = params.Addr;
	unsigned _input_Mps = params.Mps;
	brp_buf _input_Setup = params.Setup;
	unsigned _input_InLen = params.InLen;
	unsigned _input_TimeoutMs = params.TimeoutMs;
	brp_buf* InData = params.InData;
	size_t* InData_len = params.InData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Index = &_input_Index;
	unsigned* Addr = &_input_Addr;
	unsigned* Mps = &_input_Mps;
	brp_buf* Setup = &_input_Setup;
	unsigned* InLen = &_input_InLen;
	unsigned* TimeoutMs = &_input_TimeoutMs;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _InData_len;
	if(InData_len == NULL) InData_len = &_InData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 38);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int8(_frame, (unsigned)(*Addr));
	brp_frame_write_int8(_frame, (unsigned)(*Mps));
	size_t _Setup_len_val = 8;
	size_t* Setup_len = &_Setup_len_val;
	brp_frame_write(_frame, (brp_buf)(*Setup), (*Setup_len));
	brp_frame_write_int16(_frame, (unsigned)(*InLen));
	brp_frame_write_int16(_frame, (unsigned)(*TimeoutMs));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*InData_len) = brp_frame_read_int16(&_reader);
	if (InData != NULL) {
		(*InData) = (brp_buf)brp_mempool_create_buf(mempool, (*InData_len));
		if((*InData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*InData), (*InData_len));
	} else
		brp_frame_skip(&_reader, (*InData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostTransferCtrlOut(brp_protocol protocol, unsigned _input_Index, unsigned _input_Addr, unsigned _input_Mps, brp_buf _input_Setup, brp_buf _input_OutData, size_t _input_OutData_len, unsigned _input_TimeoutMs) {
#else
brp_errcode brp_DHWCtrl_UsbHostTransferCtrlOut(brp_DHWCtrl_UsbHostTransferCtrlOut_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	unsigned _input_Addr = params.Addr;
	unsigned _input_Mps = params.Mps;
	brp_buf _input_Setup = params.Setup;
	brp_buf _input_OutData = params.OutData;
	size_t _input_OutData_len = params.OutData_len;
	unsigned _input_TimeoutMs = params.TimeoutMs;
#endif
	unsigned* Index = &_input_Index;
	unsigned* Addr = &_input_Addr;
	unsigned* Mps = &_input_Mps;
	brp_buf* Setup = &_input_Setup;
	brp_buf* OutData = &_input_OutData;
	size_t* OutData_len = &_input_OutData_len;
	unsigned* TimeoutMs = &_input_TimeoutMs;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 39);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int8(_frame, (unsigned)(*Addr));
	brp_frame_write_int8(_frame, (unsigned)(*Mps));
	size_t _Setup_len_val = 8;
	size_t* Setup_len = &_Setup_len_val;
	brp_frame_write(_frame, (brp_buf)(*Setup), (*Setup_len));
	brp_frame_write_int16(_frame, (unsigned)(*OutData_len));
	brp_frame_write(_frame, (brp_buf)(*OutData), (*OutData_len));
	brp_frame_write_int16(_frame, (unsigned)(*TimeoutMs));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostTransferIn(brp_protocol protocol, unsigned _input_Index, unsigned _input_Addr, unsigned _input_Ep, brp_DHWCtrlUsbTransferAttr _input_Attr, unsigned _input_Mps, unsigned _input_MaxLen, unsigned _input_TimeoutMs, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrl_UsbHostTransferIn(brp_DHWCtrl_UsbHostTransferIn_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	unsigned _input_Addr = params.Addr;
	unsigned _input_Ep = params.Ep;
	brp_DHWCtrlUsbTransferAttr _input_Attr = params.Attr;
	unsigned _input_Mps = params.Mps;
	unsigned _input_MaxLen = params.MaxLen;
	unsigned _input_TimeoutMs = params.TimeoutMs;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Index = &_input_Index;
	unsigned* Addr = &_input_Addr;
	unsigned* Ep = &_input_Ep;
	brp_DHWCtrlUsbTransferAttr* Attr = &_input_Attr;
	unsigned* Mps = &_input_Mps;
	unsigned* MaxLen = &_input_MaxLen;
	unsigned* TimeoutMs = &_input_TimeoutMs;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 40);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int8(_frame, (unsigned)(*Addr));
	brp_frame_write_int8(_frame, (unsigned)(*Ep));
	brp_frame_write_int8(_frame, (unsigned)(*Attr));
	brp_frame_write_int16(_frame, (unsigned)(*Mps));
	brp_frame_write_int16(_frame, (unsigned)(*MaxLen));
	brp_frame_write_int16(_frame, (unsigned)(*TimeoutMs));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int16(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostTransferOut(brp_protocol protocol, unsigned _input_Index, unsigned _input_Addr, unsigned _input_Ep, brp_DHWCtrlUsbTransferAttr _input_Attr, unsigned _input_Mps, brp_buf _input_Data, size_t _input_Data_len, unsigned _input_TimeoutMs) {
#else
brp_errcode brp_DHWCtrl_UsbHostTransferOut(brp_DHWCtrl_UsbHostTransferOut_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	unsigned _input_Addr = params.Addr;
	unsigned _input_Ep = params.Ep;
	brp_DHWCtrlUsbTransferAttr _input_Attr = params.Attr;
	unsigned _input_Mps = params.Mps;
	brp_buf _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
	unsigned _input_TimeoutMs = params.TimeoutMs;
#endif
	unsigned* Index = &_input_Index;
	unsigned* Addr = &_input_Addr;
	unsigned* Ep = &_input_Ep;
	brp_DHWCtrlUsbTransferAttr* Attr = &_input_Attr;
	unsigned* Mps = &_input_Mps;
	brp_buf* Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	unsigned* TimeoutMs = &_input_TimeoutMs;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 41);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int8(_frame, (unsigned)(*Addr));
	brp_frame_write_int8(_frame, (unsigned)(*Ep));
	brp_frame_write_int8(_frame, (unsigned)(*Attr));
	brp_frame_write_int16(_frame, (unsigned)(*Mps));
	brp_frame_write_int16(_frame, (unsigned)(*Data_len));
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	brp_frame_write_int16(_frame, (unsigned)(*TimeoutMs));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostTransferCancel(brp_protocol protocol, unsigned _input_Index, unsigned _input_Addr, unsigned _input_Ep) {
#else
brp_errcode brp_DHWCtrl_UsbHostTransferCancel(brp_DHWCtrl_UsbHostTransferCancel_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	unsigned _input_Addr = params.Addr;
	unsigned _input_Ep = params.Ep;
#endif
	unsigned* Index = &_input_Index;
	unsigned* Addr = &_input_Addr;
	unsigned* Ep = &_input_Ep;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 42);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int8(_frame, (unsigned)(*Addr));
	brp_frame_write_int8(_frame, (unsigned)(*Ep));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_UsbHostSofControl(brp_protocol protocol, unsigned _input_Index, bool _input_Enable) {
#else
brp_errcode brp_DHWCtrl_UsbHostSofControl(brp_DHWCtrl_UsbHostSofControl_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	bool _input_Enable = params.Enable;
#endif
	unsigned* Index = &_input_Index;
	bool* Enable = &_input_Enable;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 43);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int8(_frame, (unsigned)(*Enable));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_FlashActivate(brp_protocol protocol, brp_DHWCtrlPinMapEntry* _input_PinMap, size_t _input_PinMap_len, unsigned _input_PeripheralIndex, unsigned* SectorSize, unsigned* SectorCount) {
#else
brp_errcode brp_DHWCtrl_FlashActivate(brp_DHWCtrl_FlashActivate_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlPinMapEntry* _input_PinMap = params.PinMap;
	size_t _input_PinMap_len = params.PinMap_len;
	unsigned _input_PeripheralIndex = params.PeripheralIndex;
	unsigned* SectorSize = params.SectorSize;
	unsigned* SectorCount = params.SectorCount;
#endif
	brp_DHWCtrlPinMapEntry** PinMap = &_input_PinMap;
	size_t* PinMap_len = &_input_PinMap_len;
	unsigned* PeripheralIndex = &_input_PeripheralIndex;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_SectorSize;
	if (SectorSize == NULL) SectorSize = &_tmp_SectorSize;
	unsigned _tmp_SectorCount;
	if (SectorCount == NULL) SectorCount = &_tmp_SectorCount;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 48);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*PinMap_len));
	for(size_t _PinMap_ndx = 0;_PinMap_ndx < (*PinMap_len);_PinMap_ndx++) {
		brp_DHWCtrlPinMapEntry _Entry = (*PinMap)[_PinMap_ndx];
		brp_DHWCtrlPinMapEntry* Entry = &_Entry;
		brp_DHWCtrlPinName _Name = (Entry)->Name;
		brp_DHWCtrlPinName* Name = &_Name;
		brp_DHWCtrlGpioPin _Pin = (Entry)->Pin;
		brp_DHWCtrlGpioPin* Pin = &_Pin;
		brp_frame_write_int8(_frame, (unsigned)(*Name));
		brp_DHWCtrlGpioPort _Port = (Pin)->Port;
		brp_DHWCtrlGpioPort* Port = &_Port;
		unsigned _Number = (Pin)->Number;
		unsigned* Number = &_Number;
		brp_frame_write_int8(_frame, (unsigned)(*Port));
		brp_frame_write_int8(_frame, (unsigned)(*Number));
	}
	brp_frame_write_int8(_frame, (unsigned)(*PeripheralIndex));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*SectorSize) = (unsigned)brp_frame_read_int16(&_reader);
	(*SectorCount) = (unsigned)brp_frame_read_int32(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_FlashDeactivate(brp_protocol protocol, unsigned _input_Index) {
#else
brp_errcode brp_DHWCtrl_FlashDeactivate(brp_DHWCtrl_FlashDeactivate_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
#endif
	unsigned* Index = &_input_Index;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_FlashRead(brp_protocol protocol, unsigned _input_Index, unsigned _input_Sector, unsigned _input_Count, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrl_FlashRead(brp_DHWCtrl_FlashRead_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	unsigned _input_Sector = params.Sector;
	unsigned _input_Count = params.Count;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Index = &_input_Index;
	unsigned* Sector = &_input_Sector;
	unsigned* Count = &_input_Count;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 50);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int32(_frame, (unsigned)(*Sector));
	brp_frame_write_int16(_frame, (unsigned)(*Count));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int16(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_FlashWrite(brp_protocol protocol, unsigned _input_Index, unsigned _input_Sector, brp_buf _input_Data, size_t _input_Data_len) {
#else
brp_errcode brp_DHWCtrl_FlashWrite(brp_DHWCtrl_FlashWrite_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	unsigned _input_Sector = params.Sector;
	brp_buf _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
#endif
	unsigned* Index = &_input_Index;
	unsigned* Sector = &_input_Sector;
	brp_buf* Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 51);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int32(_frame, (unsigned)(*Sector));
	brp_frame_write_int16(_frame, (unsigned)(*Data_len));
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_FlashErase(brp_protocol protocol, unsigned _input_Index, unsigned _input_Sector, unsigned _input_Count) {
#else
brp_errcode brp_DHWCtrl_FlashErase(brp_DHWCtrl_FlashErase_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	unsigned _input_Sector = params.Sector;
	unsigned _input_Count = params.Count;
#endif
	unsigned* Index = &_input_Index;
	unsigned* Sector = &_input_Sector;
	unsigned* Count = &_input_Count;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 52);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int32(_frame, (unsigned)(*Sector));
	brp_frame_write_int32(_frame, (unsigned)(*Count));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_SpiActivate(brp_protocol protocol, brp_DHWCtrlPinMapEntry* _input_PinMap, size_t _input_PinMap_len, unsigned _input_PeripheralIndex, brp_DHWCtrlSpiSettings _input_Settings) {
#else
brp_errcode brp_DHWCtrl_SpiActivate(brp_DHWCtrl_SpiActivate_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlPinMapEntry* _input_PinMap = params.PinMap;
	size_t _input_PinMap_len = params.PinMap_len;
	unsigned _input_PeripheralIndex = params.PeripheralIndex;
	brp_DHWCtrlSpiSettings _input_Settings = params.Settings;
#endif
	brp_DHWCtrlPinMapEntry** PinMap = &_input_PinMap;
	size_t* PinMap_len = &_input_PinMap_len;
	unsigned* PeripheralIndex = &_input_PeripheralIndex;
	brp_DHWCtrlSpiSettings* Settings = &_input_Settings;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 64);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*PinMap_len));
	for(size_t _PinMap_ndx = 0;_PinMap_ndx < (*PinMap_len);_PinMap_ndx++) {
		brp_DHWCtrlPinMapEntry _Entry = (*PinMap)[_PinMap_ndx];
		brp_DHWCtrlPinMapEntry* Entry = &_Entry;
		brp_DHWCtrlPinName _Name = (Entry)->Name;
		brp_DHWCtrlPinName* Name = &_Name;
		brp_DHWCtrlGpioPin _Pin = (Entry)->Pin;
		brp_DHWCtrlGpioPin* Pin = &_Pin;
		brp_frame_write_int8(_frame, (unsigned)(*Name));
		brp_DHWCtrlGpioPort _Port = (Pin)->Port;
		brp_DHWCtrlGpioPort* Port = &_Port;
		unsigned _Number = (Pin)->Number;
		unsigned* Number = &_Number;
		brp_frame_write_int8(_frame, (unsigned)(*Port));
		brp_frame_write_int8(_frame, (unsigned)(*Number));
	}
	brp_frame_write_int8(_frame, (unsigned)(*PeripheralIndex));
	unsigned _ClockHz = (Settings)->ClockHz;
	unsigned* ClockHz = &_ClockHz;
	brp_DHWCtrl_SpiActivate_Cpol _Cpol = (Settings)->Cpol;
	brp_DHWCtrl_SpiActivate_Cpol* Cpol = &_Cpol;
	brp_DHWCtrl_SpiActivate_Cpha _Cpha = (Settings)->Cpha;
	brp_DHWCtrl_SpiActivate_Cpha* Cpha = &_Cpha;
	brp_DHWCtrlSpiSettings_BitOrder _BitOrder = (Settings)->BitOrder;
	brp_DHWCtrlSpiSettings_BitOrder* BitOrder = &_BitOrder;
	brp_frame_write_int32(_frame, (unsigned)(*ClockHz));
	unsigned _bitmask_0812 = 0;
	_bitmask_0812 |= (*Cpol & 0b1) << 1;
	_bitmask_0812 |= (*Cpha & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_0812);
	brp_frame_write_int8(_frame, (unsigned)(*BitOrder));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_SpiDeactivate(brp_protocol protocol, unsigned _input_Index) {
#else
brp_errcode brp_DHWCtrl_SpiDeactivate(brp_DHWCtrl_SpiDeactivate_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
#endif
	unsigned* Index = &_input_Index;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 65);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_SpiTransfer(brp_protocol protocol, unsigned _input_Index, brp_buf _input_DataOut, size_t _input_DataOut_len, brp_buf* DataIn, size_t* DataIn_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrl_SpiTransfer(brp_DHWCtrl_SpiTransfer_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Index = params.Index;
	brp_buf _input_DataOut = params.DataOut;
	size_t _input_DataOut_len = params.DataOut_len;
	brp_buf* DataIn = params.DataIn;
	size_t* DataIn_len = params.DataIn_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Index = &_input_Index;
	brp_buf* DataOut = &_input_DataOut;
	size_t* DataOut_len = &_input_DataOut_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _DataIn_len;
	if(DataIn_len == NULL) DataIn_len = &_DataIn_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 66);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Index));
	brp_frame_write_int16(_frame, (unsigned)(*DataOut_len));
	brp_frame_write(_frame, (brp_buf)(*DataOut), (*DataOut_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*DataIn_len) = brp_frame_read_int16(&_reader);
	if (DataIn != NULL) {
		(*DataIn) = (brp_buf)brp_mempool_create_buf(mempool, (*DataIn_len));
		if((*DataIn) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*DataIn), (*DataIn_len));
	} else
		brp_frame_skip(&_reader, (*DataIn_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrl_ListPeripherals(brp_protocol protocol, brp_DHWCtrlPeripheralCategory _input_Category, brp_DHWCtrlPinMapEntry* _input_PinMap, size_t _input_PinMap_len, unsigned** Indices, size_t* Indices_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrl_ListPeripherals(brp_DHWCtrl_ListPeripherals_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlPeripheralCategory _input_Category = params.Category;
	brp_DHWCtrlPinMapEntry* _input_PinMap = params.PinMap;
	size_t _input_PinMap_len = params.PinMap_len;
	unsigned** Indices = params.Indices;
	size_t* Indices_len = params.Indices_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_DHWCtrlPeripheralCategory* Category = &_input_Category;
	brp_DHWCtrlPinMapEntry** PinMap = &_input_PinMap;
	size_t* PinMap_len = &_input_PinMap_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Indices_len;
	if(Indices_len == NULL) Indices_len = &_Indices_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 225);
	brp_frame_write_int8(_frame, 240);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Category));
	brp_frame_write_int8(_frame, (unsigned)(*PinMap_len));
	for(size_t _PinMap_ndx = 0;_PinMap_ndx < (*PinMap_len);_PinMap_ndx++) {
		brp_DHWCtrlPinMapEntry _Entry = (*PinMap)[_PinMap_ndx];
		brp_DHWCtrlPinMapEntry* Entry = &_Entry;
		brp_DHWCtrlPinName _Name = (Entry)->Name;
		brp_DHWCtrlPinName* Name = &_Name;
		brp_DHWCtrlGpioPin _Pin = (Entry)->Pin;
		brp_DHWCtrlGpioPin* Pin = &_Pin;
		brp_frame_write_int8(_frame, (unsigned)(*Name));
		brp_DHWCtrlGpioPort _Port = (Pin)->Port;
		brp_DHWCtrlGpioPort* Port = &_Port;
		unsigned _Number = (Pin)->Number;
		unsigned* Number = &_Number;
		brp_frame_write_int8(_frame, (unsigned)(*Port));
		brp_frame_write_int8(_frame, (unsigned)(*Number));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Indices_len) = brp_frame_read_int8(&_reader);
	if (Indices != NULL) {
		(*Indices) = (unsigned*)brp_mempool_create_buf(mempool, (*Indices_len) * sizeof(unsigned));
		if((*Indices) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _Indices_ndx = 0;(_Indices_ndx < (*Indices_len)) & !brp_frame_read_err(&_reader);_Indices_ndx++) {
		unsigned _Index;
		unsigned *Index = &_Index;
		(*Index) = (unsigned)brp_frame_read_int8(&_reader);
		if (Indices != NULL)
			(*Indices)[_Indices_ndx] = *Index;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_DecodeCfg(brp_protocol protocol, brp_EM_DecodeCfg_RxMod _input_RxMod, unsigned _input_RxBaud) {
#else
brp_errcode brp_EM_DecodeCfg(brp_EM_DecodeCfg_t params) {
	brp_protocol protocol = params.protocol;
	brp_EM_DecodeCfg_RxMod _input_RxMod = params.RxMod;
	unsigned _input_RxBaud = params.RxBaud;
#endif
	brp_EM_DecodeCfg_RxMod* RxMod = &_input_RxMod;
	unsigned* RxBaud = &_input_RxBaud;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*RxMod));
	brp_frame_write_int8(_frame, (unsigned)(*RxBaud));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Read4100(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_EM_Read4100(brp_EM_Read4100_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Read4205(brp_protocol protocol, unsigned _input_Address, unsigned* Page) {
#else
brp_errcode brp_EM_Read4205(brp_EM_Read4205_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
	unsigned* Page = params.Page;
#endif
	unsigned* Address = &_input_Address;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_Page;
	if (Page == NULL) Page = &_tmp_Page;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Address));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Page) = (unsigned)brp_frame_read_int32(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Write4205(brp_protocol protocol, unsigned _input_Address, unsigned _input_Page) {
#else
brp_errcode brp_EM_Write4205(brp_EM_Write4205_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
	unsigned _input_Page = params.Page;
#endif
	unsigned* Address = &_input_Address;
	unsigned* Page = &_input_Page;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int8(_frame, 17);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Address));
	brp_frame_write_int32(_frame, (unsigned)(*Page));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Halt4205(brp_protocol protocol) {
#else
brp_errcode brp_EM_Halt4205(brp_EM_Halt4205_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int8(_frame, 18);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Login4205(brp_protocol protocol, unsigned _input_Password) {
#else
brp_errcode brp_EM_Login4205(brp_EM_Login4205_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Password = params.Password;
#endif
	unsigned* Password = &_input_Password;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*Password));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Protect4205(brp_protocol protocol, unsigned _input_ProtectMask) {
#else
brp_errcode brp_EM_Protect4205(brp_EM_Protect4205_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_ProtectMask = params.ProtectMask;
#endif
	unsigned* ProtectMask = &_input_ProtectMask;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int8(_frame, 20);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*ProtectMask));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Read4469(brp_protocol protocol, unsigned _input_Address, unsigned* Page) {
#else
brp_errcode brp_EM_Read4469(brp_EM_Read4469_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
	unsigned* Page = params.Page;
#endif
	unsigned* Address = &_input_Address;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_Page;
	if (Page == NULL) Page = &_tmp_Page;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int8(_frame, 24);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Address));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Page) = (unsigned)brp_frame_read_int32(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Write4469(brp_protocol protocol, unsigned _input_Address, unsigned _input_Page) {
#else
brp_errcode brp_EM_Write4469(brp_EM_Write4469_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
	unsigned _input_Page = params.Page;
#endif
	unsigned* Address = &_input_Address;
	unsigned* Page = &_input_Page;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int8(_frame, 25);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Address));
	brp_frame_write_int32(_frame, (unsigned)(*Page));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Halt4469(brp_protocol protocol) {
#else
brp_errcode brp_EM_Halt4469(brp_EM_Halt4469_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int8(_frame, 26);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Login4469(brp_protocol protocol, unsigned _input_Password) {
#else
brp_errcode brp_EM_Login4469(brp_EM_Login4469_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Password = params.Password;
#endif
	unsigned* Password = &_input_Password;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*Password));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_EM_Read4450(brp_protocol protocol, unsigned _input_StartAdr, unsigned _input_EndAdr, unsigned** PageNr, size_t* PageNr_len, brp_mempool *mempool) {
#else
brp_errcode brp_EM_Read4450(brp_EM_Read4450_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_StartAdr = params.StartAdr;
	unsigned _input_EndAdr = params.EndAdr;
	unsigned** PageNr = params.PageNr;
	size_t* PageNr_len = params.PageNr_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* StartAdr = &_input_StartAdr;
	unsigned* EndAdr = &_input_EndAdr;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _PageNr_len;
	if(PageNr_len == NULL) PageNr_len = &_PageNr_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int8(_frame, 32);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*StartAdr));
	brp_frame_write_int8(_frame, (unsigned)(*EndAdr));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*PageNr_len) = brp_frame_read_int8(&_reader);
	if (PageNr != NULL) {
		(*PageNr) = (unsigned*)brp_mempool_create_buf(mempool, (*PageNr_len) * sizeof(unsigned));
		if((*PageNr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _PageNr_ndx = 0;(_PageNr_ndx < (*PageNr_len)) & !brp_frame_read_err(&_reader);_PageNr_ndx++) {
		unsigned _Page;
		unsigned *Page = &_Page;
		(*Page) = (unsigned)brp_frame_read_int32(&_reader);
		if (PageNr != NULL)
			(*PageNr)[_PageNr_ndx] = *Page;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_GetMacAdr(brp_protocol protocol, brp_buf* MAC, brp_mempool *mempool) {
#else
brp_errcode brp_Eth_GetMacAdr(brp_Eth_GetMacAdr_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* MAC = params.MAC;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 69);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _MAC_len = 6;
	size_t* MAC_len = &_MAC_len;
	if (MAC != NULL) {
		(*MAC) = (brp_buf)brp_mempool_create_buf(mempool, (*MAC_len));
		if((*MAC) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*MAC), (*MAC_len));
	} else
		brp_frame_skip(&_reader, (*MAC_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_GetConnDevIP(brp_protocol protocol, brp_buf* IP, brp_mempool *mempool) {
#else
brp_errcode brp_Eth_GetConnDevIP(brp_Eth_GetConnDevIP_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* IP = params.IP;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 69);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _IP_len = 4;
	size_t* IP_len = &_IP_len;
	if (IP != NULL) {
		(*IP) = (brp_buf)brp_mempool_create_buf(mempool, (*IP_len));
		if((*IP) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*IP), (*IP_len));
	} else
		brp_frame_skip(&_reader, (*IP_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_CreateRecoveryPoint(brp_protocol protocol) {
#else
brp_errcode brp_Eth_CreateRecoveryPoint(brp_Eth_CreateRecoveryPoint_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 69);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_DelRecoveryPoint(brp_protocol protocol) {
#else
brp_errcode brp_Eth_DelRecoveryPoint(brp_Eth_DelRecoveryPoint_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 69);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_GetNetworkStatus(brp_protocol protocol, unsigned* PortStatus, brp_buf* StaticIPAdr, brp_buf* StaticIPNetmask, brp_buf* StaticIPGateway, brp_buf* DHCPAdr, brp_buf* DHCPNetmask, brp_buf* DHCPGateway, brp_buf* LinkLocalAdr, brp_buf* LinkLocalNetmask, brp_buf* LinkLocalGateway, brp_buf* DNSAdr, brp_buf* HostAdr, unsigned* HostPort, unsigned* AutocloseTimeout, brp_mempool *mempool) {
#else
brp_errcode brp_Eth_GetNetworkStatus(brp_Eth_GetNetworkStatus_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* PortStatus = params.PortStatus;
	brp_buf* StaticIPAdr = params.StaticIPAdr;
	brp_buf* StaticIPNetmask = params.StaticIPNetmask;
	brp_buf* StaticIPGateway = params.StaticIPGateway;
	brp_buf* DHCPAdr = params.DHCPAdr;
	brp_buf* DHCPNetmask = params.DHCPNetmask;
	brp_buf* DHCPGateway = params.DHCPGateway;
	brp_buf* LinkLocalAdr = params.LinkLocalAdr;
	brp_buf* LinkLocalNetmask = params.LinkLocalNetmask;
	brp_buf* LinkLocalGateway = params.LinkLocalGateway;
	brp_buf* DNSAdr = params.DNSAdr;
	brp_buf* HostAdr = params.HostAdr;
	unsigned* HostPort = params.HostPort;
	unsigned* AutocloseTimeout = params.AutocloseTimeout;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	unsigned _tmp_PortStatus;
	if (PortStatus == NULL) PortStatus = &_tmp_PortStatus;
	unsigned _tmp_HostPort;
	if (HostPort == NULL) HostPort = &_tmp_HostPort;
	unsigned _tmp_AutocloseTimeout;
	if (AutocloseTimeout == NULL) AutocloseTimeout = &_tmp_AutocloseTimeout;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 69);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*PortStatus) = (unsigned)brp_frame_read_int8(&_reader);
	size_t _StaticIPAdr_len = 4;
	size_t* StaticIPAdr_len = &_StaticIPAdr_len;
	if (StaticIPAdr != NULL) {
		(*StaticIPAdr) = (brp_buf)brp_mempool_create_buf(mempool, (*StaticIPAdr_len));
		if((*StaticIPAdr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*StaticIPAdr), (*StaticIPAdr_len));
	} else
		brp_frame_skip(&_reader, (*StaticIPAdr_len));
	size_t _StaticIPNetmask_len = 4;
	size_t* StaticIPNetmask_len = &_StaticIPNetmask_len;
	if (StaticIPNetmask != NULL) {
		(*StaticIPNetmask) = (brp_buf)brp_mempool_create_buf(mempool, (*StaticIPNetmask_len));
		if((*StaticIPNetmask) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*StaticIPNetmask), (*StaticIPNetmask_len));
	} else
		brp_frame_skip(&_reader, (*StaticIPNetmask_len));
	size_t _StaticIPGateway_len = 4;
	size_t* StaticIPGateway_len = &_StaticIPGateway_len;
	if (StaticIPGateway != NULL) {
		(*StaticIPGateway) = (brp_buf)brp_mempool_create_buf(mempool, (*StaticIPGateway_len));
		if((*StaticIPGateway) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*StaticIPGateway), (*StaticIPGateway_len));
	} else
		brp_frame_skip(&_reader, (*StaticIPGateway_len));
	size_t _DHCPAdr_len = 4;
	size_t* DHCPAdr_len = &_DHCPAdr_len;
	if (DHCPAdr != NULL) {
		(*DHCPAdr) = (brp_buf)brp_mempool_create_buf(mempool, (*DHCPAdr_len));
		if((*DHCPAdr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*DHCPAdr), (*DHCPAdr_len));
	} else
		brp_frame_skip(&_reader, (*DHCPAdr_len));
	size_t _DHCPNetmask_len = 4;
	size_t* DHCPNetmask_len = &_DHCPNetmask_len;
	if (DHCPNetmask != NULL) {
		(*DHCPNetmask) = (brp_buf)brp_mempool_create_buf(mempool, (*DHCPNetmask_len));
		if((*DHCPNetmask) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*DHCPNetmask), (*DHCPNetmask_len));
	} else
		brp_frame_skip(&_reader, (*DHCPNetmask_len));
	size_t _DHCPGateway_len = 4;
	size_t* DHCPGateway_len = &_DHCPGateway_len;
	if (DHCPGateway != NULL) {
		(*DHCPGateway) = (brp_buf)brp_mempool_create_buf(mempool, (*DHCPGateway_len));
		if((*DHCPGateway) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*DHCPGateway), (*DHCPGateway_len));
	} else
		brp_frame_skip(&_reader, (*DHCPGateway_len));
	size_t _LinkLocalAdr_len = 4;
	size_t* LinkLocalAdr_len = &_LinkLocalAdr_len;
	if (LinkLocalAdr != NULL) {
		(*LinkLocalAdr) = (brp_buf)brp_mempool_create_buf(mempool, (*LinkLocalAdr_len));
		if((*LinkLocalAdr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*LinkLocalAdr), (*LinkLocalAdr_len));
	} else
		brp_frame_skip(&_reader, (*LinkLocalAdr_len));
	size_t _LinkLocalNetmask_len = 4;
	size_t* LinkLocalNetmask_len = &_LinkLocalNetmask_len;
	if (LinkLocalNetmask != NULL) {
		(*LinkLocalNetmask) = (brp_buf)brp_mempool_create_buf(mempool, (*LinkLocalNetmask_len));
		if((*LinkLocalNetmask) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*LinkLocalNetmask), (*LinkLocalNetmask_len));
	} else
		brp_frame_skip(&_reader, (*LinkLocalNetmask_len));
	size_t _LinkLocalGateway_len = 4;
	size_t* LinkLocalGateway_len = &_LinkLocalGateway_len;
	if (LinkLocalGateway != NULL) {
		(*LinkLocalGateway) = (brp_buf)brp_mempool_create_buf(mempool, (*LinkLocalGateway_len));
		if((*LinkLocalGateway) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*LinkLocalGateway), (*LinkLocalGateway_len));
	} else
		brp_frame_skip(&_reader, (*LinkLocalGateway_len));
	size_t _DNSAdr_len = 4;
	size_t* DNSAdr_len = &_DNSAdr_len;
	if (DNSAdr != NULL) {
		(*DNSAdr) = (brp_buf)brp_mempool_create_buf(mempool, (*DNSAdr_len));
		if((*DNSAdr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*DNSAdr), (*DNSAdr_len));
	} else
		brp_frame_skip(&_reader, (*DNSAdr_len));
	size_t _HostAdr_len = 4;
	size_t* HostAdr_len = &_HostAdr_len;
	if (HostAdr != NULL) {
		(*HostAdr) = (brp_buf)brp_mempool_create_buf(mempool, (*HostAdr_len));
		if((*HostAdr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*HostAdr), (*HostAdr_len));
	} else
		brp_frame_skip(&_reader, (*HostAdr_len));
	(*HostPort) = (unsigned)brp_frame_read_int16(&_reader);
	(*AutocloseTimeout) = (unsigned)brp_frame_read_int16(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_GetMIBCounters(brp_protocol protocol, unsigned _input_Port, unsigned** MIBCounterList, size_t* MIBCounterList_len, brp_mempool *mempool) {
#else
brp_errcode brp_Eth_GetMIBCounters(brp_Eth_GetMIBCounters_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Port = params.Port;
	unsigned** MIBCounterList = params.MIBCounterList;
	size_t* MIBCounterList_len = params.MIBCounterList_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Port = &_input_Port;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _MIBCounterList_len;
	if(MIBCounterList_len == NULL) MIBCounterList_len = &_MIBCounterList_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 69);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*MIBCounterList_len) = brp_frame_read_int8(&_reader);
	if (MIBCounterList != NULL) {
		(*MIBCounterList) = (unsigned*)brp_mempool_create_buf(mempool, (*MIBCounterList_len) * sizeof(unsigned));
		if((*MIBCounterList) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _MIBCounterList_ndx = 0;(_MIBCounterList_ndx < (*MIBCounterList_len)) & !brp_frame_read_err(&_reader);_MIBCounterList_ndx++) {
		unsigned _Value;
		unsigned *Value = &_Value;
		(*Value) = (unsigned)brp_frame_read_int32(&_reader);
		if (MIBCounterList != NULL)
			(*MIBCounterList)[_MIBCounterList_ndx] = *Value;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_GetTcpConnectionStatus(brp_protocol protocol, brp_Eth_GetTcpConnectionStatus_Status* Status) {
#else
brp_errcode brp_Eth_GetTcpConnectionStatus(brp_Eth_GetTcpConnectionStatus_t params) {
	brp_protocol protocol = params.protocol;
	brp_Eth_GetTcpConnectionStatus_Status* Status = params.Status;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 69);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	int _Status_int_val = brp_frame_read_int8(&_reader);
	if (! brp_Eth_GetTcpConnectionStatus_Status_is_valid(_Status_int_val))
		return BRP_ERR_PAYLOAD_FORMAT;
	if (Status != NULL)
		(*Status) = (brp_Eth_GetTcpConnectionStatus_Status)_Status_int_val;
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_OpenTcpConnection(brp_protocol protocol, brp_Eth_OpenTcpConnection_ConnectionReason _input_ConnectionReason) {
#else
brp_errcode brp_Eth_OpenTcpConnection(brp_Eth_OpenTcpConnection_t params) {
	brp_protocol protocol = params.protocol;
	brp_Eth_OpenTcpConnection_ConnectionReason _input_ConnectionReason = params.ConnectionReason;
#endif
	brp_Eth_OpenTcpConnection_ConnectionReason* ConnectionReason = &_input_ConnectionReason;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 69);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*ConnectionReason));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Eth_CloseTcpConnection(brp_protocol protocol) {
#else
brp_errcode brp_Eth_CloseTcpConnection(brp_Eth_CloseTcpConnection_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 69);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Felica_GenericCmd(brp_protocol protocol, brp_Felica_GenericCmd_FastBaud _input_FastBaud, unsigned _input_Cmd, brp_buf _input_Param, size_t _input_Param_len, unsigned _input_Timeout, brp_buf* Resp, size_t* Resp_len, brp_mempool *mempool) {
#else
brp_errcode brp_Felica_GenericCmd(brp_Felica_GenericCmd_t params) {
	brp_protocol protocol = params.protocol;
	brp_Felica_GenericCmd_FastBaud _input_FastBaud = params.FastBaud;
	unsigned _input_Cmd = params.Cmd;
	brp_buf _input_Param = params.Param;
	size_t _input_Param_len = params.Param_len;
	unsigned _input_Timeout = params.Timeout;
	brp_buf* Resp = params.Resp;
	size_t* Resp_len = params.Resp_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_Felica_GenericCmd_FastBaud* FastBaud = &_input_FastBaud;
	unsigned* Cmd = &_input_Cmd;
	brp_buf* Param = &_input_Param;
	size_t* Param_len = &_input_Param_len;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Resp_len;
	if(Resp_len == NULL) Resp_len = &_Resp_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 28);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	if (_input_Timeout == 0) _input_Timeout = (unsigned)20;
	brp_frame_write_int8(_frame, (unsigned)(*FastBaud));
	brp_frame_write_int8(_frame, (unsigned)(*Cmd));
	brp_frame_write_int8(_frame, (unsigned)(*Param_len));
	brp_frame_write(_frame, (brp_buf)(*Param), (*Param_len));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Resp_len) = brp_frame_read_int8(&_reader);
	if (Resp != NULL) {
		(*Resp) = (brp_buf)brp_mempool_create_buf(mempool, (*Resp_len));
		if((*Resp) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Resp), (*Resp_len));
	} else
		brp_frame_skip(&_reader, (*Resp_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Felica_SetUID2(brp_protocol protocol, brp_buf _input_UID2) {
#else
brp_errcode brp_Felica_SetUID2(brp_Felica_SetUID2_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_UID2 = params.UID2;
#endif
	brp_buf* UID2 = &_input_UID2;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 28);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	size_t _UID2_len_val = 8;
	size_t* UID2_len = &_UID2_len_val;
	brp_frame_write(_frame, (brp_buf)(*UID2), (*UID2_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Felica_Request(brp_protocol protocol, brp_Felica_Request_FastBaud _input_FastBaud, unsigned _input_SystemCode, unsigned _input_RequestCode, unsigned* ColFlag, brp_Felica_Request_Labels_Entry** Labels, size_t* Labels_len, brp_mempool *mempool) {
#else
brp_errcode brp_Felica_Request(brp_Felica_Request_t params) {
	brp_protocol protocol = params.protocol;
	brp_Felica_Request_FastBaud _input_FastBaud = params.FastBaud;
	unsigned _input_SystemCode = params.SystemCode;
	unsigned _input_RequestCode = params.RequestCode;
	unsigned* ColFlag = params.ColFlag;
	brp_Felica_Request_Labels_Entry** Labels = params.Labels;
	size_t* Labels_len = params.Labels_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_Felica_Request_FastBaud* FastBaud = &_input_FastBaud;
	unsigned* SystemCode = &_input_SystemCode;
	unsigned* RequestCode = &_input_RequestCode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Labels_len;
	if(Labels_len == NULL) Labels_len = &_Labels_len;
	unsigned _tmp_ColFlag;
	if (ColFlag == NULL) ColFlag = &_tmp_ColFlag;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 28);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*FastBaud));
	brp_frame_write_int16(_frame, (unsigned)(*SystemCode));
	brp_frame_write_int8(_frame, (unsigned)(*RequestCode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ColFlag) = (unsigned)brp_frame_read_int8(&_reader);
	(*Labels_len) = brp_frame_read_int8(&_reader);
	if (Labels != NULL) {
		(*Labels) = (brp_Felica_Request_Labels_Entry*)brp_mempool_create_buf(mempool, (*Labels_len) * sizeof(brp_Felica_Request_Labels_Entry));
		if((*Labels) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _Labels_ndx = 0;(_Labels_ndx < (*Labels_len)) & !brp_frame_read_err(&_reader);_Labels_ndx++) {
		brp_Felica_Request_Labels_Entry _Labels_Entry;
		brp_Felica_Request_Labels_Entry *Labels_Entry = &_Labels_Entry;
		brp_buf _NFCID;
		brp_buf *NFCID = &_NFCID;
		size_t _NFCID_len;
		size_t *NFCID_len = &_NFCID_len;
		(*NFCID_len) = brp_frame_read_int8(&_reader);
		if (NFCID != NULL) {
			(*NFCID) = (brp_buf)brp_mempool_create_buf(mempool, (*NFCID_len));
			if((*NFCID) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			brp_frame_read(&_reader, (brp_buf)(*NFCID), (*NFCID_len));
		} else
			brp_frame_skip(&_reader, (*NFCID_len));
		if(Labels_Entry != NULL) {
			Labels_Entry->NFCID = *NFCID;
			Labels_Entry->NFCID_len = *NFCID_len;
		}
		if (Labels != NULL)
			(*Labels)[_Labels_ndx] = *Labels_Entry;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_IndalaRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_HID_IndalaRead(brp_HID_IndalaRead_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 51);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_ProxRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_HID_ProxRead(brp_HID_ProxRead_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 51);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_AwidRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_HID_AwidRead(brp_HID_AwidRead_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 51);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_IoProxRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_HID_IoProxRead(brp_HID_IoProxRead_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 51);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_Prox32Read(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_HID_Prox32Read(brp_HID_Prox32Read_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 51);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_PyramidRead(brp_protocol protocol, unsigned* Len, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_HID_PyramidRead(brp_HID_PyramidRead_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* Len = params.Len;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	unsigned _tmp_Len;
	if (Len == NULL) Len = &_tmp_Len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 51);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Len) = (unsigned)brp_frame_read_int8(&_reader);
	(*Data_len) = brp_frame_rest( & _reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_IndalaSecureRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_HID_IndalaSecureRead(brp_HID_IndalaSecureRead_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 51);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_HID_IdteckRead(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_HID_IdteckRead(brp_HID_IdteckRead_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 51);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Hitag_Request(brp_protocol protocol, brp_Hitag_Request_TagType _input_TagType, brp_Hitag_Request_Mode _input_Mode, unsigned* Snr) {
#else
brp_errcode brp_Hitag_Request(brp_Hitag_Request_t params) {
	brp_protocol protocol = params.protocol;
	brp_Hitag_Request_TagType _input_TagType = params.TagType;
	brp_Hitag_Request_Mode _input_Mode = params.Mode;
	unsigned* Snr = params.Snr;
#endif
	brp_Hitag_Request_TagType* TagType = &_input_TagType;
	brp_Hitag_Request_Mode* Mode = &_input_Mode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_Snr;
	if (Snr == NULL) Snr = &_tmp_Snr;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 48);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*TagType));
	brp_frame_write_int8(_frame, (unsigned)(*Mode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Snr) = (unsigned)brp_frame_read_int32(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Hitag_Select(brp_protocol protocol, brp_Hitag_Select_SelMode _input_SelMode, unsigned _input_Pwd, unsigned* Page1) {
#else
brp_errcode brp_Hitag_Select(brp_Hitag_Select_t params) {
	brp_protocol protocol = params.protocol;
	brp_Hitag_Select_SelMode _input_SelMode = params.SelMode;
	unsigned _input_Pwd = params.Pwd;
	unsigned* Page1 = params.Page1;
#endif
	brp_Hitag_Select_SelMode* SelMode = &_input_SelMode;
	unsigned* Pwd = &_input_Pwd;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_Page1;
	if (Page1 == NULL) Page1 = &_tmp_Page1;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 48);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	if(!(*SelMode) && (*Pwd)) (*SelMode) = brp_Hitag_Select_SelMode_H2AuthOnlyPwd;
	brp_frame_write_int8(_frame, (unsigned)(*SelMode));
	if((*SelMode) == (brp_Hitag_Select_SelMode_H2AuthOnlyPwd)) {
		brp_frame_write_int32(_frame, (unsigned)(*Pwd));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Page1) = (unsigned)brp_frame_read_int32(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Hitag_Halt(brp_protocol protocol) {
#else
brp_errcode brp_Hitag_Halt(brp_Hitag_Halt_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 48);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Hitag_Read(brp_protocol protocol, unsigned _input_Address, bool _input_InvRead, bool _input_KeyB, bool _input_Encrypt, bool _input_BlockRead, unsigned** PageNr, size_t* PageNr_len, brp_mempool *mempool) {
#else
brp_errcode brp_Hitag_Read(brp_Hitag_Read_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
	bool _input_InvRead = params.InvRead;
	bool _input_KeyB = params.KeyB;
	bool _input_Encrypt = params.Encrypt;
	bool _input_BlockRead = params.BlockRead;
	unsigned** PageNr = params.PageNr;
	size_t* PageNr_len = params.PageNr_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Address = &_input_Address;
	bool* InvRead = &_input_InvRead;
	bool* KeyB = &_input_KeyB;
	bool* Encrypt = &_input_Encrypt;
	bool* BlockRead = &_input_BlockRead;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _PageNr_len;
	if(PageNr_len == NULL) PageNr_len = &_PageNr_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 48);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Address));
	unsigned _bitmask_12d4 = 0;
	_bitmask_12d4 |= (*InvRead & 0b1) << 3;
	_bitmask_12d4 |= (*KeyB & 0b1) << 2;
	_bitmask_12d4 |= (*Encrypt & 0b1) << 1;
	_bitmask_12d4 |= (*BlockRead & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_12d4);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*PageNr_len) = brp_frame_read_int8(&_reader);
	if (PageNr != NULL) {
		(*PageNr) = (unsigned*)brp_mempool_create_buf(mempool, (*PageNr_len) * sizeof(unsigned));
		if((*PageNr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _PageNr_ndx = 0;(_PageNr_ndx < (*PageNr_len)) & !brp_frame_read_err(&_reader);_PageNr_ndx++) {
		unsigned _Page;
		unsigned *Page = &_Page;
		(*Page) = (unsigned)brp_frame_read_int32(&_reader);
		if (PageNr != NULL)
			(*PageNr)[_PageNr_ndx] = *Page;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Hitag_Write(brp_protocol protocol, unsigned _input_Address, bool _input_KeyB, bool _input_Encrypt, bool _input_BlockWrite, unsigned* _input_PageNr, size_t _input_PageNr_len) {
#else
brp_errcode brp_Hitag_Write(brp_Hitag_Write_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
	bool _input_KeyB = params.KeyB;
	bool _input_Encrypt = params.Encrypt;
	bool _input_BlockWrite = params.BlockWrite;
	unsigned* _input_PageNr = params.PageNr;
	size_t _input_PageNr_len = params.PageNr_len;
#endif
	unsigned* Address = &_input_Address;
	bool* KeyB = &_input_KeyB;
	bool* Encrypt = &_input_Encrypt;
	bool* BlockWrite = &_input_BlockWrite;
	unsigned** PageNr = &_input_PageNr;
	size_t* PageNr_len = &_input_PageNr_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 48);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Address));
	unsigned _bitmask_3037 = 0;
	_bitmask_3037 |= (*KeyB & 0b1) << 2;
	_bitmask_3037 |= (*Encrypt & 0b1) << 1;
	_bitmask_3037 |= (*BlockWrite & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_3037);
	brp_frame_write_int8(_frame, (unsigned)(*PageNr_len));
	for(size_t _PageNr_ndx = 0;_PageNr_ndx < (*PageNr_len);_PageNr_ndx++) {
		unsigned _Page = (*PageNr)[_PageNr_ndx];
		unsigned* Page = &_Page;
		brp_frame_write_int32(_frame, (unsigned)(*Page));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Hitag_PersonaliseHtg(brp_protocol protocol, bool _input_Reset, bool _input_HtgS, unsigned* _input_Len, size_t _input_Len_len) {
#else
brp_errcode brp_Hitag_PersonaliseHtg(brp_Hitag_PersonaliseHtg_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_Reset = params.Reset;
	bool _input_HtgS = params.HtgS;
	unsigned* _input_Len = params.Len;
	size_t _input_Len_len = params.Len_len;
#endif
	bool* Reset = &_input_Reset;
	bool* HtgS = &_input_HtgS;
	unsigned** Len = &_input_Len;
	size_t* Len_len = &_input_Len_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 48);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_daee = 0;
	_bitmask_daee |= (*Reset & 0b1) << 1;
	_bitmask_daee |= (*HtgS & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_daee);
	brp_frame_write_int8(_frame, (unsigned)(*Len_len));
	for(size_t _Len_ndx = 0;_Len_ndx < (*Len_len);_Len_ndx++) {
		unsigned _Data = (*Len)[_Len_ndx];
		unsigned* Data = &_Data;
		brp_frame_write_int32(_frame, (unsigned)(*Data));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_I2c_SetSpeed(brp_protocol protocol, bool _input_FastMode) {
#else
brp_errcode brp_I2c_SetSpeed(brp_I2c_SetSpeed_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_FastMode = params.FastMode;
#endif
	bool* FastMode = &_input_FastMode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*FastMode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_I2c_Read(brp_protocol protocol, unsigned _input_Address, unsigned _input_ReadLen, brp_buf* ReadData, size_t* ReadData_len, brp_mempool *mempool) {
#else
brp_errcode brp_I2c_Read(brp_I2c_Read_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
	unsigned _input_ReadLen = params.ReadLen;
	brp_buf* ReadData = params.ReadData;
	size_t* ReadData_len = params.ReadData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Address = &_input_Address;
	unsigned* ReadLen = &_input_ReadLen;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ReadData_len;
	if(ReadData_len == NULL) ReadData_len = &_ReadData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Address));
	brp_frame_write_int8(_frame, (unsigned)(*ReadLen));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ReadData_len) = brp_frame_read_int8(&_reader);
	if (ReadData != NULL) {
		(*ReadData) = (brp_buf)brp_mempool_create_buf(mempool, (*ReadData_len));
		if((*ReadData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ReadData), (*ReadData_len));
	} else
		brp_frame_skip(&_reader, (*ReadData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_I2c_Write(brp_protocol protocol, unsigned _input_Address, brp_buf _input_WriteData, size_t _input_WriteData_len) {
#else
brp_errcode brp_I2c_Write(brp_I2c_Write_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
	brp_buf _input_WriteData = params.WriteData;
	size_t _input_WriteData_len = params.WriteData_len;
#endif
	unsigned* Address = &_input_Address;
	brp_buf* WriteData = &_input_WriteData;
	size_t* WriteData_len = &_input_WriteData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Address));
	brp_frame_write_int8(_frame, (unsigned)(*WriteData_len));
	brp_frame_write(_frame, (brp_buf)(*WriteData), (*WriteData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_I2c_TxRx(brp_protocol protocol, unsigned _input_Address, brp_buf _input_CmdData, size_t _input_CmdData_len, unsigned _input_ReadLen, brp_buf* ReadData, size_t* ReadData_len, brp_mempool *mempool) {
#else
brp_errcode brp_I2c_TxRx(brp_I2c_TxRx_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
	brp_buf _input_CmdData = params.CmdData;
	size_t _input_CmdData_len = params.CmdData_len;
	unsigned _input_ReadLen = params.ReadLen;
	brp_buf* ReadData = params.ReadData;
	size_t* ReadData_len = params.ReadData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Address = &_input_Address;
	brp_buf* CmdData = &_input_CmdData;
	size_t* CmdData_len = &_input_CmdData_len;
	unsigned* ReadLen = &_input_ReadLen;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ReadData_len;
	if(ReadData_len == NULL) ReadData_len = &_ReadData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Address));
	brp_frame_write_int8(_frame, (unsigned)(*CmdData_len));
	brp_frame_write(_frame, (brp_buf)(*CmdData), (*CmdData_len));
	brp_frame_write_int8(_frame, (unsigned)(*ReadLen));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ReadData_len) = brp_frame_read_int8(&_reader);
	if (ReadData != NULL) {
		(*ReadData) = (brp_buf)brp_mempool_create_buf(mempool, (*ReadData_len));
		if((*ReadData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ReadData), (*ReadData_len));
	} else
		brp_frame_skip(&_reader, (*ReadData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_RequestLegacy(brp_protocol protocol, bool _input_ReqAll, brp_Iso14a_RequestLegacy_UIDSize* UIDSize, unsigned* Coll, unsigned* ProprietaryCoding) {
#else
brp_errcode brp_Iso14a_RequestLegacy(brp_Iso14a_RequestLegacy_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_ReqAll = params.ReqAll;
	brp_Iso14a_RequestLegacy_UIDSize* UIDSize = params.UIDSize;
	unsigned* Coll = params.Coll;
	unsigned* ProprietaryCoding = params.ProprietaryCoding;
#endif
	bool* ReqAll = &_input_ReqAll;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_Coll;
	if (Coll == NULL) Coll = &_tmp_Coll;
	unsigned _tmp_ProprietaryCoding;
	if (ProprietaryCoding == NULL) ProprietaryCoding = &_tmp_ProprietaryCoding;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_6acc = 0;
	_bitmask_6acc |= (*ReqAll & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_6acc);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	unsigned _bitmask_b587 = brp_frame_read_int16(&_reader);
	if(UIDSize != NULL)
		(*UIDSize) = (_bitmask_b587>>14) & 0b11;
	if(Coll != NULL)
		(*Coll) = (_bitmask_b587>>8) & 0b11111;
	if(ProprietaryCoding != NULL)
		(*ProprietaryCoding) = (_bitmask_b587>>0) & 0b1111;
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_Select(brp_protocol protocol, unsigned _input_CascLev, unsigned _input_BitCount, brp_buf _input_PreSelSer, size_t _input_PreSelSer_len, unsigned* SAK, brp_buf* Serial, size_t* Serial_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14a_Select(brp_Iso14a_Select_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_CascLev = params.CascLev;
	unsigned _input_BitCount = params.BitCount;
	brp_buf _input_PreSelSer = params.PreSelSer;
	size_t _input_PreSelSer_len = params.PreSelSer_len;
	unsigned* SAK = params.SAK;
	brp_buf* Serial = params.Serial;
	size_t* Serial_len = params.Serial_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* CascLev = &_input_CascLev;
	unsigned* BitCount = &_input_BitCount;
	brp_buf* PreSelSer = &_input_PreSelSer;
	size_t* PreSelSer_len = &_input_PreSelSer_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Serial_len;
	if(Serial_len == NULL) Serial_len = &_Serial_len;
	unsigned _tmp_SAK;
	if (SAK == NULL) SAK = &_tmp_SAK;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*CascLev));
	brp_frame_write_int8(_frame, (unsigned)(*BitCount));
	brp_frame_write(_frame, (brp_buf)(*PreSelSer), (*PreSelSer_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*SAK) = (unsigned)brp_frame_read_int8(&_reader);
	(*Serial_len) = brp_frame_read_int8(&_reader);
	if (Serial != NULL) {
		(*Serial) = (brp_buf)brp_mempool_create_buf(mempool, (*Serial_len));
		if((*Serial) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Serial), (*Serial_len));
	} else
		brp_frame_skip(&_reader, (*Serial_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_Halt(brp_protocol protocol) {
#else
brp_errcode brp_Iso14a_Halt(brp_Iso14a_Halt_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_RequestATS(brp_protocol protocol, brp_Iso14a_RequestATS_FSDI _input_FSDI, unsigned _input_CID, brp_buf* ATS, size_t* ATS_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14a_RequestATS(brp_Iso14a_RequestATS_t params) {
	brp_protocol protocol = params.protocol;
	brp_Iso14a_RequestATS_FSDI _input_FSDI = params.FSDI;
	unsigned _input_CID = params.CID;
	brp_buf* ATS = params.ATS;
	size_t* ATS_len = params.ATS_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_Iso14a_RequestATS_FSDI* FSDI = &_input_FSDI;
	unsigned* CID = &_input_CID;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ATS_len;
	if(ATS_len == NULL) ATS_len = &_ATS_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_8ece = 0;
	_bitmask_8ece |= (*FSDI & 0b1111) << 4;
	_bitmask_8ece |= (*CID & 0b1111) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_8ece);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ATS_len) = brp_frame_rest( & _reader);
	if (ATS != NULL) {
		(*ATS) = (brp_buf)brp_mempool_create_buf(mempool, (*ATS_len));
		if((*ATS) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ATS), (*ATS_len));
	} else
		brp_frame_skip(&_reader, (*ATS_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_PerformPPS(brp_protocol protocol, unsigned _input_CID, brp_DivisorInteger _input_DSI, brp_DivisorInteger _input_DRI) {
#else
brp_errcode brp_Iso14a_PerformPPS(brp_Iso14a_PerformPPS_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_CID = params.CID;
	brp_DivisorInteger _input_DSI = params.DSI;
	brp_DivisorInteger _input_DRI = params.DRI;
#endif
	unsigned* CID = &_input_CID;
	brp_DivisorInteger* DSI = &_input_DSI;
	brp_DivisorInteger* DRI = &_input_DRI;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*CID));
	unsigned _bitmask_0ef3 = 0;
	_bitmask_0ef3 |= (*DSI & 0b11) << 2;
	_bitmask_0ef3 |= (*DRI & 0b11) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_0ef3);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_Request(brp_protocol protocol, bool _input_ReqAll, brp_buf* ATQA, bool* Collision, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14a_Request(brp_Iso14a_Request_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_ReqAll = params.ReqAll;
	brp_buf* ATQA = params.ATQA;
	bool* Collision = params.Collision;
	brp_mempool *mempool = params.mempool;
#endif
	bool* ReqAll = &_input_ReqAll;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	bool _tmp_Collision;
	if (Collision == NULL) Collision = &_tmp_Collision;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_6acc = 0;
	_bitmask_6acc |= (*ReqAll & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_6acc);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _ATQA_len = 2;
	size_t* ATQA_len = &_ATQA_len;
	if (ATQA != NULL) {
		(*ATQA) = (brp_buf)brp_mempool_create_buf(mempool, (*ATQA_len));
		if((*ATQA) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ATQA), (*ATQA_len));
	} else
		brp_frame_skip(&_reader, (*ATQA_len));
	(*Collision) = (bool)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_RequestVasup(brp_protocol protocol, bool _input_ReqAll, unsigned _input_FormatVersion, bool _input_VasSupported, bool _input_AuthUserRequested, unsigned _input_TerminalTypeDataLength, unsigned _input_TerminalType, brp_buf _input_TCI, size_t _input_TCI_len, brp_buf* ATQA, bool* Collision, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14a_RequestVasup(brp_Iso14a_RequestVasup_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_ReqAll = params.ReqAll;
	unsigned _input_FormatVersion = params.FormatVersion;
	bool _input_VasSupported = params.VasSupported;
	bool _input_AuthUserRequested = params.AuthUserRequested;
	unsigned _input_TerminalTypeDataLength = params.TerminalTypeDataLength;
	unsigned _input_TerminalType = params.TerminalType;
	brp_buf _input_TCI = params.TCI;
	size_t _input_TCI_len = params.TCI_len;
	brp_buf* ATQA = params.ATQA;
	bool* Collision = params.Collision;
	brp_mempool *mempool = params.mempool;
#endif
	bool* ReqAll = &_input_ReqAll;
	unsigned* FormatVersion = &_input_FormatVersion;
	bool* VasSupported = &_input_VasSupported;
	bool* AuthUserRequested = &_input_AuthUserRequested;
	unsigned* TerminalTypeDataLength = &_input_TerminalTypeDataLength;
	unsigned* TerminalType = &_input_TerminalType;
	brp_buf* TCI = &_input_TCI;
	size_t* TCI_len = &_input_TCI_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	bool _tmp_Collision;
	if (Collision == NULL) Collision = &_tmp_Collision;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int32(_frame, 100);
	if (_input_FormatVersion == 0) _input_FormatVersion = (unsigned)2;
	unsigned _bitmask_6acc = 0;
	_bitmask_6acc |= (*ReqAll & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_6acc);
	brp_frame_write_int8(_frame, (unsigned)(*FormatVersion));
	unsigned _bitmask_acb8 = 0;
	_bitmask_acb8 |= (*VasSupported & 0b1) << 7;
	_bitmask_acb8 |= (*AuthUserRequested & 0b1) << 6;
	_bitmask_acb8 |= (*TerminalTypeDataLength & 0b1111) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_acb8);
	brp_frame_write_int16(_frame, (unsigned)(*TerminalType));
	brp_frame_write(_frame, (brp_buf)(*TCI), (*TCI_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _ATQA_len = 2;
	size_t* ATQA_len = &_ATQA_len;
	if (ATQA != NULL) {
		(*ATQA) = (brp_buf)brp_mempool_create_buf(mempool, (*ATQA_len));
		if((*ATQA) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ATQA), (*ATQA_len));
	} else
		brp_frame_skip(&_reader, (*ATQA_len));
	(*Collision) = (bool)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_Anticoll(brp_protocol protocol, unsigned _input_BitCount, brp_buf _input_PreSelectedSnr, brp_buf* SelectedSnr, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14a_Anticoll(brp_Iso14a_Anticoll_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_BitCount = params.BitCount;
	brp_buf _input_PreSelectedSnr = params.PreSelectedSnr;
	brp_buf* SelectedSnr = params.SelectedSnr;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* BitCount = &_input_BitCount;
	brp_buf* PreSelectedSnr = &_input_PreSelectedSnr;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int8(_frame, 24);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*BitCount));
	size_t _PreSelectedSnr_len_val = 4;
	size_t* PreSelectedSnr_len = &_PreSelectedSnr_len_val;
	brp_frame_write(_frame, (brp_buf)(*PreSelectedSnr), (*PreSelectedSnr_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _SelectedSnr_len = 4;
	size_t* SelectedSnr_len = &_SelectedSnr_len;
	if (SelectedSnr != NULL) {
		(*SelectedSnr) = (brp_buf)brp_mempool_create_buf(mempool, (*SelectedSnr_len));
		if((*SelectedSnr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*SelectedSnr), (*SelectedSnr_len));
	} else
		brp_frame_skip(&_reader, (*SelectedSnr_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_SelectOnly(brp_protocol protocol, brp_buf _input_Snr, unsigned* SAK) {
#else
brp_errcode brp_Iso14a_SelectOnly(brp_Iso14a_SelectOnly_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_Snr = params.Snr;
	unsigned* SAK = params.SAK;
#endif
	brp_buf* Snr = &_input_Snr;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_SAK;
	if (SAK == NULL) SAK = &_tmp_SAK;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int8(_frame, 25);
	brp_frame_write_int32(_frame, 100);
	size_t _Snr_len_val = 4;
	size_t* Snr_len = &_Snr_len_val;
	brp_frame_write(_frame, (brp_buf)(*Snr), (*Snr_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*SAK) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_TransparentCmd(brp_protocol protocol, bool _input_EnMifBwProt, bool _input_EnBitmode, bool _input_EnCRCRX, bool _input_EnCRCTX, bool _input_ParityMode, bool _input_EnParity, unsigned _input_SendDataLen, unsigned _input_Timeout, brp_DivisorInteger _input_DSI, brp_DivisorInteger _input_DRI, brp_buf _input_SendData, size_t _input_SendData_len, brp_buf* RcvData, size_t* RcvData_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14a_TransparentCmd(brp_Iso14a_TransparentCmd_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_EnMifBwProt = params.EnMifBwProt;
	bool _input_EnBitmode = params.EnBitmode;
	bool _input_EnCRCRX = params.EnCRCRX;
	bool _input_EnCRCTX = params.EnCRCTX;
	bool _input_ParityMode = params.ParityMode;
	bool _input_EnParity = params.EnParity;
	unsigned _input_SendDataLen = params.SendDataLen;
	unsigned _input_Timeout = params.Timeout;
	brp_DivisorInteger _input_DSI = params.DSI;
	brp_DivisorInteger _input_DRI = params.DRI;
	brp_buf _input_SendData = params.SendData;
	size_t _input_SendData_len = params.SendData_len;
	brp_buf* RcvData = params.RcvData;
	size_t* RcvData_len = params.RcvData_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* EnMifBwProt = &_input_EnMifBwProt;
	bool* EnBitmode = &_input_EnBitmode;
	bool* EnCRCRX = &_input_EnCRCRX;
	bool* EnCRCTX = &_input_EnCRCTX;
	bool* ParityMode = &_input_ParityMode;
	bool* EnParity = &_input_EnParity;
	unsigned* SendDataLen = &_input_SendDataLen;
	unsigned* Timeout = &_input_Timeout;
	brp_DivisorInteger* DSI = &_input_DSI;
	brp_DivisorInteger* DRI = &_input_DRI;
	brp_buf* SendData = &_input_SendData;
	size_t* SendData_len = &_input_SendData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _RcvData_len;
	if(RcvData_len == NULL) RcvData_len = &_RcvData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int8(_frame, 32);
	brp_frame_write_int32(_frame, 100);
	if (_input_Timeout == 0) _input_Timeout = (unsigned)26;
	unsigned _bitmask_ab2b = 0;
	_bitmask_ab2b |= (*EnMifBwProt & 0b1) << 7;
	_bitmask_ab2b |= (*EnBitmode & 0b1) << 4;
	_bitmask_ab2b |= (*EnCRCRX & 0b1) << 3;
	_bitmask_ab2b |= (*EnCRCTX & 0b1) << 2;
	_bitmask_ab2b |= (*ParityMode & 0b1) << 1;
	_bitmask_ab2b |= (*EnParity & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_ab2b);
	brp_frame_write_int16(_frame, (unsigned)(*SendDataLen));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	unsigned _bitmask_0ef3 = 0;
	_bitmask_0ef3 |= (*DSI & 0b11) << 2;
	_bitmask_0ef3 |= (*DRI & 0b11) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_0ef3);
	brp_frame_write(_frame, (brp_buf)(*SendData), (*SendData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*RcvData_len) = brp_frame_read_int16(&_reader);
	if (RcvData != NULL) {
		(*RcvData) = (brp_buf)brp_mempool_create_buf(mempool, (*RcvData_len));
		if((*RcvData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*RcvData), (*RcvData_len));
	} else
		brp_frame_skip(&_reader, (*RcvData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14a_TransparentCmdBitlen(brp_protocol protocol, bool _input_EnHighBaudOld, bool _input_EnParTx, unsigned _input_SendDataLen, unsigned _input_Timeout, brp_DivisorInteger _input_DSI, brp_DivisorInteger _input_DRI, brp_buf _input_SendData, size_t _input_SendData_len, unsigned* RecvDataLen, unsigned* CollisionPosition, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14a_TransparentCmdBitlen(brp_Iso14a_TransparentCmdBitlen_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_EnHighBaudOld = params.EnHighBaudOld;
	bool _input_EnParTx = params.EnParTx;
	unsigned _input_SendDataLen = params.SendDataLen;
	unsigned _input_Timeout = params.Timeout;
	brp_DivisorInteger _input_DSI = params.DSI;
	brp_DivisorInteger _input_DRI = params.DRI;
	brp_buf _input_SendData = params.SendData;
	size_t _input_SendData_len = params.SendData_len;
	unsigned* RecvDataLen = params.RecvDataLen;
	unsigned* CollisionPosition = params.CollisionPosition;
	brp_buf* RecvData = params.RecvData;
	size_t* RecvData_len = params.RecvData_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* EnHighBaudOld = &_input_EnHighBaudOld;
	bool* EnParTx = &_input_EnParTx;
	unsigned* SendDataLen = &_input_SendDataLen;
	unsigned* Timeout = &_input_Timeout;
	brp_DivisorInteger* DSI = &_input_DSI;
	brp_DivisorInteger* DRI = &_input_DRI;
	brp_buf* SendData = &_input_SendData;
	size_t* SendData_len = &_input_SendData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _RecvData_len;
	if(RecvData_len == NULL) RecvData_len = &_RecvData_len;
	unsigned _tmp_RecvDataLen;
	if (RecvDataLen == NULL) RecvDataLen = &_tmp_RecvDataLen;
	unsigned _tmp_CollisionPosition;
	if (CollisionPosition == NULL) CollisionPosition = &_tmp_CollisionPosition;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int8(_frame, 35);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_4e1b = 0;
	_bitmask_4e1b |= (*EnHighBaudOld & 0b1) << 6;
	_bitmask_4e1b |= (*EnParTx & 0b1) << 5;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_4e1b);
	brp_frame_write_int16(_frame, (unsigned)(*SendDataLen));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	unsigned _bitmask_0ef3 = 0;
	_bitmask_0ef3 |= (*DSI & 0b11) << 2;
	_bitmask_0ef3 |= (*DRI & 0b11) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_0ef3);
	brp_frame_write(_frame, (brp_buf)(*SendData), (*SendData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*RecvDataLen) = (unsigned)brp_frame_read_int16(&_reader);
	(*CollisionPosition) = (unsigned)brp_frame_read_int16(&_reader);
	(*RecvData_len) = brp_frame_rest( & _reader);
	if (RecvData != NULL) {
		(*RecvData) = (brp_buf)brp_mempool_create_buf(mempool, (*RecvData_len));
		if((*RecvData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*RecvData), (*RecvData_len));
	} else
		brp_frame_skip(&_reader, (*RecvData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14b_Request(brp_protocol protocol, bool _input_ExtendedATQB, bool _input_ReqAll, brp_Iso14b_Request_TimeSlots _input_TimeSlots, unsigned _input_AFI, brp_Iso14b_Request_ValueList_Entry** ValueList, size_t* ValueList_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14b_Request(brp_Iso14b_Request_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_ExtendedATQB = params.ExtendedATQB;
	bool _input_ReqAll = params.ReqAll;
	brp_Iso14b_Request_TimeSlots _input_TimeSlots = params.TimeSlots;
	unsigned _input_AFI = params.AFI;
	brp_Iso14b_Request_ValueList_Entry** ValueList = params.ValueList;
	size_t* ValueList_len = params.ValueList_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* ExtendedATQB = &_input_ExtendedATQB;
	bool* ReqAll = &_input_ReqAll;
	brp_Iso14b_Request_TimeSlots* TimeSlots = &_input_TimeSlots;
	unsigned* AFI = &_input_AFI;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ValueList_len;
	if(ValueList_len == NULL) ValueList_len = &_ValueList_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 20);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_c193 = 0;
	_bitmask_c193 |= (*ExtendedATQB & 0b1) << 4;
	_bitmask_c193 |= (*ReqAll & 0b1) << 3;
	_bitmask_c193 |= (*TimeSlots & 0b111) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_c193);
	brp_frame_write_int8(_frame, (unsigned)(*AFI));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ValueList_len) = brp_frame_read_int8(&_reader);
	if (ValueList != NULL) {
		(*ValueList) = (brp_Iso14b_Request_ValueList_Entry*)brp_mempool_create_buf(mempool, (*ValueList_len) * sizeof(brp_Iso14b_Request_ValueList_Entry));
		if((*ValueList) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _ValueList_ndx = 0;(_ValueList_ndx < (*ValueList_len)) & !brp_frame_read_err(&_reader);_ValueList_ndx++) {
		brp_Iso14b_Request_ValueList_Entry _ValueList_Entry;
		brp_Iso14b_Request_ValueList_Entry *ValueList_Entry = &_ValueList_Entry;
		brp_buf _PUPI;
		brp_buf *PUPI = &_PUPI;
		brp_buf _AppData;
		brp_buf *AppData = &_AppData;
		bool _Synced;
		bool *Synced = &_Synced;
		bool _Send848;
		bool *Send848 = &_Send848;
		bool _Send424;
		bool *Send424 = &_Send424;
		bool _Send212;
		bool *Send212 = &_Send212;
		bool _Recv848;
		bool *Recv848 = &_Recv848;
		bool _Recv424;
		bool *Recv424 = &_Recv424;
		bool _Recv212;
		bool *Recv212 = &_Recv212;
		brp_Iso14b_Request_FSCI _FSCI;
		brp_Iso14b_Request_FSCI *FSCI = &_FSCI;
		brp_Iso14b_Request_ProtType _ProtType;
		brp_Iso14b_Request_ProtType *ProtType = &_ProtType;
		brp_Iso14b_Request_FWI _FWI;
		brp_Iso14b_Request_FWI *FWI = &_FWI;
		unsigned _ADC;
		unsigned *ADC = &_ADC;
		bool _NAD;
		bool *NAD = &_NAD;
		bool _CID;
		bool *CID = &_CID;
		brp_Iso14b_Request_SFGI _SFGI;
		brp_Iso14b_Request_SFGI *SFGI = &_SFGI;
		size_t _PUPI_len = 4;
		size_t* PUPI_len = &_PUPI_len;
		if (PUPI != NULL) {
			(*PUPI) = (brp_buf)brp_mempool_create_buf(mempool, (*PUPI_len));
			if((*PUPI) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			brp_frame_read(&_reader, (brp_buf)(*PUPI), (*PUPI_len));
		} else
			brp_frame_skip(&_reader, (*PUPI_len));
		size_t _AppData_len = 4;
		size_t* AppData_len = &_AppData_len;
		if (AppData != NULL) {
			(*AppData) = (brp_buf)brp_mempool_create_buf(mempool, (*AppData_len));
			if((*AppData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			brp_frame_read(&_reader, (brp_buf)(*AppData), (*AppData_len));
		} else
			brp_frame_skip(&_reader, (*AppData_len));
		unsigned _bitmask_5da2 = brp_frame_read_int8(&_reader);
		if(Synced != NULL)
			(*Synced) = (_bitmask_5da2>>7) & 0b1;
		if(Send848 != NULL)
			(*Send848) = (_bitmask_5da2>>6) & 0b1;
		if(Send424 != NULL)
			(*Send424) = (_bitmask_5da2>>5) & 0b1;
		if(Send212 != NULL)
			(*Send212) = (_bitmask_5da2>>4) & 0b1;
		if(Recv848 != NULL)
			(*Recv848) = (_bitmask_5da2>>2) & 0b1;
		if(Recv424 != NULL)
			(*Recv424) = (_bitmask_5da2>>1) & 0b1;
		if(Recv212 != NULL)
			(*Recv212) = (_bitmask_5da2>>0) & 0b1;
		unsigned _bitmask_1753 = brp_frame_read_int16(&_reader);
		if(FSCI != NULL)
			(*FSCI) = (_bitmask_1753>>12) & 0b1111;
		if(ProtType != NULL)
			(*ProtType) = (_bitmask_1753>>8) & 0b1;
		if(FWI != NULL)
			(*FWI) = (_bitmask_1753>>4) & 0b1111;
		if(ADC != NULL)
			(*ADC) = (_bitmask_1753>>2) & 0b11;
		if(NAD != NULL)
			(*NAD) = (_bitmask_1753>>1) & 0b1;
		if(CID != NULL)
			(*CID) = (_bitmask_1753>>0) & 0b1;
		if(*ExtendedATQB) {
			unsigned _bitmask_1ded = brp_frame_read_int8(&_reader);
			if(SFGI != NULL)
				(*SFGI) = (_bitmask_1ded>>4) & 0b1111;
		}
		if(ValueList_Entry != NULL) {
			ValueList_Entry->PUPI = *PUPI;
			ValueList_Entry->AppData = *AppData;
			ValueList_Entry->Synced = *Synced;
			ValueList_Entry->Send848 = *Send848;
			ValueList_Entry->Send424 = *Send424;
			ValueList_Entry->Send212 = *Send212;
			ValueList_Entry->Recv848 = *Recv848;
			ValueList_Entry->Recv424 = *Recv424;
			ValueList_Entry->Recv212 = *Recv212;
			ValueList_Entry->FSCI = *FSCI;
			ValueList_Entry->ProtType = *ProtType;
			ValueList_Entry->FWI = *FWI;
			ValueList_Entry->ADC = *ADC;
			ValueList_Entry->NAD = *NAD;
			ValueList_Entry->CID = *CID;
			ValueList_Entry->SFGI = *SFGI;
		}
		if (ValueList != NULL)
			(*ValueList)[_ValueList_ndx] = *ValueList_Entry;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14b_Attrib(brp_protocol protocol, brp_buf _input_PUPI, brp_Iso14b_Attrib_TR0 _input_TR0, brp_Iso14b_Attrib_TR1 _input_TR1, brp_Iso14b_Attrib_EOF_ _input_EOF_, brp_Iso14b_Attrib_SOF _input_SOF, brp_DivisorInteger _input_DSI, brp_DivisorInteger _input_DRI, brp_Iso14b_Attrib_FSDI _input_FSDI, unsigned _input_ProtocolType, unsigned _input_CID, bool _input_EnHLR, bool _input_EnMBLI, bool _input_EnCID, unsigned* AssignedCID, unsigned* MBLI, brp_buf* HLR, size_t* HLR_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14b_Attrib(brp_Iso14b_Attrib_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_PUPI = params.PUPI;
	brp_Iso14b_Attrib_TR0 _input_TR0 = params.TR0;
	brp_Iso14b_Attrib_TR1 _input_TR1 = params.TR1;
	brp_Iso14b_Attrib_EOF_ _input_EOF_ = params.EOF_;
	brp_Iso14b_Attrib_SOF _input_SOF = params.SOF;
	brp_DivisorInteger _input_DSI = params.DSI;
	brp_DivisorInteger _input_DRI = params.DRI;
	brp_Iso14b_Attrib_FSDI _input_FSDI = params.FSDI;
	unsigned _input_ProtocolType = params.ProtocolType;
	unsigned _input_CID = params.CID;
	bool _input_EnHLR = params.EnHLR;
	bool _input_EnMBLI = params.EnMBLI;
	bool _input_EnCID = params.EnCID;
	unsigned* AssignedCID = params.AssignedCID;
	unsigned* MBLI = params.MBLI;
	brp_buf* HLR = params.HLR;
	size_t* HLR_len = params.HLR_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* PUPI = &_input_PUPI;
	brp_Iso14b_Attrib_TR0* TR0 = &_input_TR0;
	brp_Iso14b_Attrib_TR1* TR1 = &_input_TR1;
	brp_Iso14b_Attrib_EOF_* EOF_ = &_input_EOF_;
	brp_Iso14b_Attrib_SOF* SOF = &_input_SOF;
	brp_DivisorInteger* DSI = &_input_DSI;
	brp_DivisorInteger* DRI = &_input_DRI;
	brp_Iso14b_Attrib_FSDI* FSDI = &_input_FSDI;
	unsigned* ProtocolType = &_input_ProtocolType;
	unsigned* CID = &_input_CID;
	bool* EnHLR = &_input_EnHLR;
	bool* EnMBLI = &_input_EnMBLI;
	bool* EnCID = &_input_EnCID;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _HLR_len;
	if(HLR_len == NULL) HLR_len = &_HLR_len;
	unsigned _tmp_AssignedCID;
	if (AssignedCID == NULL) AssignedCID = &_tmp_AssignedCID;
	unsigned _tmp_MBLI;
	if (MBLI == NULL) MBLI = &_tmp_MBLI;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 20);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	size_t _PUPI_len_val = 4;
	size_t* PUPI_len = &_PUPI_len_val;
	brp_frame_write(_frame, (brp_buf)(*PUPI), (*PUPI_len));
	unsigned _bitmask_ad8b = 0;
	_bitmask_ad8b |= (*TR0 & 0b11) << 22;
	_bitmask_ad8b |= (*TR1 & 0b11) << 20;
	_bitmask_ad8b |= (*EOF_ & 0b1) << 19;
	_bitmask_ad8b |= (*SOF & 0b1) << 18;
	_bitmask_ad8b |= (*DSI & 0b11) << 14;
	_bitmask_ad8b |= (*DRI & 0b11) << 12;
	_bitmask_ad8b |= (*FSDI & 0b1111) << 8;
	_bitmask_ad8b |= (*ProtocolType & 0b1111) << 0;
	brp_frame_write_int24(_frame, (unsigned)_bitmask_ad8b);
	brp_frame_write_int8(_frame, (unsigned)(*CID));
	unsigned _bitmask_3a31 = 0;
	_bitmask_3a31 |= (*EnHLR & 0b1) << 2;
	_bitmask_3a31 |= (*EnMBLI & 0b1) << 1;
	_bitmask_3a31 |= (*EnCID & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_3a31);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(*EnCID) {
		(*AssignedCID) = (unsigned)brp_frame_read_int8(&_reader);
	}
	if(*EnMBLI) {
		(*MBLI) = (unsigned)brp_frame_read_int8(&_reader);
	}
	if(*EnHLR) {
		(*HLR_len) = brp_frame_read_int8(&_reader);
		if (HLR != NULL) {
			(*HLR) = (brp_buf)brp_mempool_create_buf(mempool, (*HLR_len));
			if((*HLR) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			brp_frame_read(&_reader, (brp_buf)(*HLR), (*HLR_len));
		} else
			brp_frame_skip(&_reader, (*HLR_len));
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14b_Halt(brp_protocol protocol, brp_buf _input_PUPI) {
#else
brp_errcode brp_Iso14b_Halt(brp_Iso14b_Halt_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_PUPI = params.PUPI;
#endif
	brp_buf* PUPI = &_input_PUPI;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 20);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	size_t _PUPI_len_val = 4;
	size_t* PUPI_len = &_PUPI_len_val;
	brp_frame_write(_frame, (brp_buf)(*PUPI), (*PUPI_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14b_TransparentCmd(brp_protocol protocol, bool _input_EnCRCRX, bool _input_EnCRCTX, unsigned _input_SendDataLen, unsigned _input_Timeout, brp_DivisorInteger _input_DSI, brp_DivisorInteger _input_DRI, brp_buf _input_SendData, size_t _input_SendData_len, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14b_TransparentCmd(brp_Iso14b_TransparentCmd_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_EnCRCRX = params.EnCRCRX;
	bool _input_EnCRCTX = params.EnCRCTX;
	unsigned _input_SendDataLen = params.SendDataLen;
	unsigned _input_Timeout = params.Timeout;
	brp_DivisorInteger _input_DSI = params.DSI;
	brp_DivisorInteger _input_DRI = params.DRI;
	brp_buf _input_SendData = params.SendData;
	size_t _input_SendData_len = params.SendData_len;
	brp_buf* RecvData = params.RecvData;
	size_t* RecvData_len = params.RecvData_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* EnCRCRX = &_input_EnCRCRX;
	bool* EnCRCTX = &_input_EnCRCTX;
	unsigned* SendDataLen = &_input_SendDataLen;
	unsigned* Timeout = &_input_Timeout;
	brp_DivisorInteger* DSI = &_input_DSI;
	brp_DivisorInteger* DRI = &_input_DRI;
	brp_buf* SendData = &_input_SendData;
	size_t* SendData_len = &_input_SendData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _RecvData_len;
	if(RecvData_len == NULL) RecvData_len = &_RecvData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 20);
	brp_frame_write_int8(_frame, 32);
	brp_frame_write_int32(_frame, 100);
	if (_input_Timeout == 0) _input_Timeout = (unsigned)10;
	unsigned _bitmask_b9e3 = 0;
	_bitmask_b9e3 |= (*EnCRCRX & 0b1) << 1;
	_bitmask_b9e3 |= (*EnCRCTX & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_b9e3);
	brp_frame_write_int16(_frame, (unsigned)(*SendDataLen));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	unsigned _bitmask_0ef3 = 0;
	_bitmask_0ef3 |= (*DSI & 0b11) << 2;
	_bitmask_0ef3 |= (*DRI & 0b11) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_0ef3);
	brp_frame_write(_frame, (brp_buf)(*SendData), (*SendData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*RecvData_len) = brp_frame_read_int16(&_reader);
	if (RecvData != NULL) {
		(*RecvData) = (brp_buf)brp_mempool_create_buf(mempool, (*RecvData_len));
		if((*RecvData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*RecvData), (*RecvData_len));
	} else
		brp_frame_skip(&_reader, (*RecvData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14L4_SetupAPDU(brp_protocol protocol, bool _input_EnDefault, bool _input_ToggleAB, bool _input_EnNAD, bool _input_EnCID, unsigned _input_CID, unsigned _input_NAD, brp_Iso14L4_SetupAPDU_FSCI _input_FSCI, brp_Iso14L4_SetupAPDU_FWI _input_FWI, brp_DivisorInteger _input_DSI, brp_DivisorInteger _input_DRI) {
#else
brp_errcode brp_Iso14L4_SetupAPDU(brp_Iso14L4_SetupAPDU_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_EnDefault = params.EnDefault;
	bool _input_ToggleAB = params.ToggleAB;
	bool _input_EnNAD = params.EnNAD;
	bool _input_EnCID = params.EnCID;
	unsigned _input_CID = params.CID;
	unsigned _input_NAD = params.NAD;
	brp_Iso14L4_SetupAPDU_FSCI _input_FSCI = params.FSCI;
	brp_Iso14L4_SetupAPDU_FWI _input_FWI = params.FWI;
	brp_DivisorInteger _input_DSI = params.DSI;
	brp_DivisorInteger _input_DRI = params.DRI;
#endif
	bool* EnDefault = &_input_EnDefault;
	bool* ToggleAB = &_input_ToggleAB;
	bool* EnNAD = &_input_EnNAD;
	bool* EnCID = &_input_EnCID;
	unsigned* CID = &_input_CID;
	unsigned* NAD = &_input_NAD;
	brp_Iso14L4_SetupAPDU_FSCI* FSCI = &_input_FSCI;
	brp_Iso14L4_SetupAPDU_FWI* FWI = &_input_FWI;
	brp_DivisorInteger* DSI = &_input_DSI;
	brp_DivisorInteger* DRI = &_input_DRI;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 22);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_b773 = 0;
	_bitmask_b773 |= (*EnDefault & 0b1) << 3;
	_bitmask_b773 |= (*ToggleAB & 0b1) << 2;
	_bitmask_b773 |= (*EnNAD & 0b1) << 1;
	_bitmask_b773 |= (*EnCID & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_b773);
	brp_frame_write_int8(_frame, (unsigned)(*CID));
	brp_frame_write_int8(_frame, (unsigned)(*NAD));
	unsigned _bitmask_1753 = 0;
	_bitmask_1753 |= (*FSCI & 0b1111) << 12;
	_bitmask_1753 |= (*FWI & 0b1111) << 8;
	_bitmask_1753 |= (*DSI & 0b11) << 2;
	_bitmask_1753 |= (*DRI & 0b11) << 0;
	brp_frame_write_int16(_frame, (unsigned)_bitmask_1753);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14L4_ExchangeAPDU(brp_protocol protocol, brp_buf _input_SendData, size_t _input_SendData_len, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14L4_ExchangeAPDU(brp_Iso14L4_ExchangeAPDU_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_SendData = params.SendData;
	size_t _input_SendData_len = params.SendData_len;
	brp_buf* RecvData = params.RecvData;
	size_t* RecvData_len = params.RecvData_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* SendData = &_input_SendData;
	size_t* SendData_len = &_input_SendData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _RecvData_len;
	if(RecvData_len == NULL) RecvData_len = &_RecvData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 22);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 60000);
	brp_frame_write_int16(_frame, (unsigned)(*SendData_len));
	brp_frame_write(_frame, (brp_buf)(*SendData), (*SendData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*RecvData_len) = brp_frame_read_int16(&_reader);
	if (RecvData != NULL) {
		(*RecvData) = (brp_buf)brp_mempool_create_buf(mempool, (*RecvData_len));
		if((*RecvData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*RecvData), (*RecvData_len));
	} else
		brp_frame_skip(&_reader, (*RecvData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14L4_Deselect(brp_protocol protocol) {
#else
brp_errcode brp_Iso14L4_Deselect(brp_Iso14L4_Deselect_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 22);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 2000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14CE_ActivateCardAPDU(brp_protocol protocol, bool _input_SpecifyTimeoutApdu, bool _input_AutoWTX, unsigned _input_ATQA, brp_buf _input_Snr, bool _input_DSEqualToDR, bool _input_DS8, bool _input_DS4, bool _input_DS2, bool _input_DR8, bool _input_DR4, bool _input_DR2, unsigned _input_FWT, unsigned _input_TimeoutPCD, unsigned _input_TimeoutApdu, brp_buf _input_ATS, size_t _input_ATS_len, brp_buf* FirstCmd, size_t* FirstCmd_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14CE_ActivateCardAPDU(brp_Iso14CE_ActivateCardAPDU_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_SpecifyTimeoutApdu = params.SpecifyTimeoutApdu;
	bool _input_AutoWTX = params.AutoWTX;
	unsigned _input_ATQA = params.ATQA;
	brp_buf _input_Snr = params.Snr;
	bool _input_DSEqualToDR = params.DSEqualToDR;
	bool _input_DS8 = params.DS8;
	bool _input_DS4 = params.DS4;
	bool _input_DS2 = params.DS2;
	bool _input_DR8 = params.DR8;
	bool _input_DR4 = params.DR4;
	bool _input_DR2 = params.DR2;
	unsigned _input_FWT = params.FWT;
	unsigned _input_TimeoutPCD = params.TimeoutPCD;
	unsigned _input_TimeoutApdu = params.TimeoutApdu;
	brp_buf _input_ATS = params.ATS;
	size_t _input_ATS_len = params.ATS_len;
	brp_buf* FirstCmd = params.FirstCmd;
	size_t* FirstCmd_len = params.FirstCmd_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* SpecifyTimeoutApdu = &_input_SpecifyTimeoutApdu;
	bool* AutoWTX = &_input_AutoWTX;
	unsigned* ATQA = &_input_ATQA;
	brp_buf* Snr = &_input_Snr;
	bool* DSEqualToDR = &_input_DSEqualToDR;
	bool* DS8 = &_input_DS8;
	bool* DS4 = &_input_DS4;
	bool* DS2 = &_input_DS2;
	bool* DR8 = &_input_DR8;
	bool* DR4 = &_input_DR4;
	bool* DR2 = &_input_DR2;
	unsigned* FWT = &_input_FWT;
	unsigned* TimeoutPCD = &_input_TimeoutPCD;
	unsigned* TimeoutApdu = &_input_TimeoutApdu;
	brp_buf* ATS = &_input_ATS;
	size_t* ATS_len = &_input_ATS_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _FirstCmd_len;
	if(FirstCmd_len == NULL) FirstCmd_len = &_FirstCmd_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 74);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 2000);
	if(!(*SpecifyTimeoutApdu) && (*TimeoutApdu)) (*SpecifyTimeoutApdu) = true;
	unsigned _bitmask_4f88 = 0;
	_bitmask_4f88 |= (*SpecifyTimeoutApdu & 0b1) << 1;
	_bitmask_4f88 |= (*AutoWTX & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_4f88);
	brp_frame_write_int16(_frame, (unsigned)(*ATQA));
	size_t _Snr_len_val = 4;
	size_t* Snr_len = &_Snr_len_val;
	brp_frame_write(_frame, (brp_buf)(*Snr), (*Snr_len));
	unsigned _bitmask_2555 = 0;
	_bitmask_2555 |= (*DSEqualToDR & 0b1) << 7;
	_bitmask_2555 |= (*DS8 & 0b1) << 6;
	_bitmask_2555 |= (*DS4 & 0b1) << 5;
	_bitmask_2555 |= (*DS2 & 0b1) << 4;
	_bitmask_2555 |= (*DR8 & 0b1) << 2;
	_bitmask_2555 |= (*DR4 & 0b1) << 1;
	_bitmask_2555 |= (*DR2 & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_2555);
	brp_frame_write_int16(_frame, (unsigned)(*FWT));
	brp_frame_write_int16(_frame, (unsigned)(*TimeoutPCD));
	if(*SpecifyTimeoutApdu) {
		brp_frame_write_int16(_frame, (unsigned)(*TimeoutApdu));
	}
	brp_frame_write_int8(_frame, (unsigned)(*ATS_len));
	brp_frame_write(_frame, (brp_buf)(*ATS), (*ATS_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*FirstCmd_len) = brp_frame_read_int16(&_reader);
	if (FirstCmd != NULL) {
		(*FirstCmd) = (brp_buf)brp_mempool_create_buf(mempool, (*FirstCmd_len));
		if((*FirstCmd) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*FirstCmd), (*FirstCmd_len));
	} else
		brp_frame_skip(&_reader, (*FirstCmd_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14CE_ExchangeCardAPDU(brp_protocol protocol, brp_buf _input_Rsp, size_t _input_Rsp_len, unsigned _input_Timeout, brp_buf* Cmd, size_t* Cmd_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso14CE_ExchangeCardAPDU(brp_Iso14CE_ExchangeCardAPDU_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_Rsp = params.Rsp;
	size_t _input_Rsp_len = params.Rsp_len;
	unsigned _input_Timeout = params.Timeout;
	brp_buf* Cmd = params.Cmd;
	size_t* Cmd_len = params.Cmd_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* Rsp = &_input_Rsp;
	size_t* Rsp_len = &_input_Rsp_len;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Cmd_len;
	if(Cmd_len == NULL) Cmd_len = &_Cmd_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 74);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 1000);
	brp_frame_write_int16(_frame, (unsigned)(*Rsp_len));
	brp_frame_write(_frame, (brp_buf)(*Rsp), (*Rsp_len));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Cmd_len) = brp_frame_read_int16(&_reader);
	if (Cmd != NULL) {
		(*Cmd) = (brp_buf)brp_mempool_create_buf(mempool, (*Cmd_len));
		if((*Cmd) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Cmd), (*Cmd_len));
	} else
		brp_frame_skip(&_reader, (*Cmd_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14CE_ExtendWaitingTime(brp_protocol protocol, unsigned _input_WaitingTimeout, unsigned _input_WTXM, unsigned _input_RefreshTimeRatio) {
#else
brp_errcode brp_Iso14CE_ExtendWaitingTime(brp_Iso14CE_ExtendWaitingTime_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_WaitingTimeout = params.WaitingTimeout;
	unsigned _input_WTXM = params.WTXM;
	unsigned _input_RefreshTimeRatio = params.RefreshTimeRatio;
#endif
	unsigned* WaitingTimeout = &_input_WaitingTimeout;
	unsigned* WTXM = &_input_WTXM;
	unsigned* RefreshTimeRatio = &_input_RefreshTimeRatio;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 74);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 1000);
	brp_frame_write_int16(_frame, (unsigned)(*WaitingTimeout));
	brp_frame_write_int8(_frame, (unsigned)(*WTXM));
	brp_frame_write_int8(_frame, (unsigned)(*RefreshTimeRatio));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso14CE_GetExternalHfStatus(brp_protocol protocol, unsigned* ExtFieldStat) {
#else
brp_errcode brp_Iso14CE_GetExternalHfStatus(brp_Iso14CE_GetExternalHfStatus_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* ExtFieldStat = params.ExtFieldStat;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_ExtFieldStat;
	if (ExtFieldStat == NULL) ExtFieldStat = &_tmp_ExtFieldStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 74);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ExtFieldStat) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_SetParam(brp_protocol protocol, bool _input_ModulationIndex, bool _input_TXMode, bool _input_HighDataRate, bool _input_DualSubcarrier) {
#else
brp_errcode brp_Iso15_SetParam(brp_Iso15_SetParam_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_ModulationIndex = params.ModulationIndex;
	bool _input_TXMode = params.TXMode;
	bool _input_HighDataRate = params.HighDataRate;
	bool _input_DualSubcarrier = params.DualSubcarrier;
#endif
	bool* ModulationIndex = &_input_ModulationIndex;
	bool* TXMode = &_input_TXMode;
	bool* HighDataRate = &_input_HighDataRate;
	bool* DualSubcarrier = &_input_DualSubcarrier;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_1a19 = 0;
	_bitmask_1a19 |= (*ModulationIndex & 0b1) << 3;
	_bitmask_1a19 |= (*TXMode & 0b1) << 2;
	_bitmask_1a19 |= (*HighDataRate & 0b1) << 1;
	_bitmask_1a19 |= (*DualSubcarrier & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_1a19);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_GetParam(brp_protocol protocol, bool* ModulationIndex, bool* TXMode, bool* HighDataRate, bool* DualSubcarrier) {
#else
brp_errcode brp_Iso15_GetParam(brp_Iso15_GetParam_t params) {
	brp_protocol protocol = params.protocol;
	bool* ModulationIndex = params.ModulationIndex;
	bool* TXMode = params.TXMode;
	bool* HighDataRate = params.HighDataRate;
	bool* DualSubcarrier = params.DualSubcarrier;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	bool _tmp_ModulationIndex;
	if (ModulationIndex == NULL) ModulationIndex = &_tmp_ModulationIndex;
	bool _tmp_TXMode;
	if (TXMode == NULL) TXMode = &_tmp_TXMode;
	bool _tmp_HighDataRate;
	if (HighDataRate == NULL) HighDataRate = &_tmp_HighDataRate;
	bool _tmp_DualSubcarrier;
	if (DualSubcarrier == NULL) DualSubcarrier = &_tmp_DualSubcarrier;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	unsigned _bitmask_1a19 = brp_frame_read_int8(&_reader);
	if(ModulationIndex != NULL)
		(*ModulationIndex) = (_bitmask_1a19>>3) & 0b1;
	if(TXMode != NULL)
		(*TXMode) = (_bitmask_1a19>>2) & 0b1;
	if(HighDataRate != NULL)
		(*HighDataRate) = (_bitmask_1a19>>1) & 0b1;
	if(DualSubcarrier != NULL)
		(*DualSubcarrier) = (_bitmask_1a19>>0) & 0b1;
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_GetUIDList(brp_protocol protocol, bool _input_EnAFI, bool _input_NextBlock, bool _input_AutoQuiet, bool _input_EnDSFID, bool _input_En16Slots, unsigned _input_AFI, unsigned* More, brp_Iso15_GetUIDList_Labels_Entry** Labels, size_t* Labels_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso15_GetUIDList(brp_Iso15_GetUIDList_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_EnAFI = params.EnAFI;
	bool _input_NextBlock = params.NextBlock;
	bool _input_AutoQuiet = params.AutoQuiet;
	bool _input_EnDSFID = params.EnDSFID;
	bool _input_En16Slots = params.En16Slots;
	unsigned _input_AFI = params.AFI;
	unsigned* More = params.More;
	brp_Iso15_GetUIDList_Labels_Entry** Labels = params.Labels;
	size_t* Labels_len = params.Labels_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* EnAFI = &_input_EnAFI;
	bool* NextBlock = &_input_NextBlock;
	bool* AutoQuiet = &_input_AutoQuiet;
	bool* EnDSFID = &_input_EnDSFID;
	bool* En16Slots = &_input_En16Slots;
	unsigned* AFI = &_input_AFI;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Labels_len;
	if(Labels_len == NULL) Labels_len = &_Labels_len;
	unsigned _tmp_More;
	if (More == NULL) More = &_tmp_More;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	if(!(*EnAFI) && (*AFI)) (*EnAFI) = true;
	unsigned _bitmask_0e86 = 0;
	_bitmask_0e86 |= (*EnAFI & 0b1) << 4;
	_bitmask_0e86 |= (*NextBlock & 0b1) << 3;
	_bitmask_0e86 |= (*AutoQuiet & 0b1) << 2;
	_bitmask_0e86 |= (*EnDSFID & 0b1) << 1;
	_bitmask_0e86 |= (*En16Slots & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_0e86);
	if(*EnAFI) {
		brp_frame_write_int8(_frame, (unsigned)(*AFI));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*More) = (unsigned)brp_frame_read_int8(&_reader);
	(*Labels_len) = brp_frame_read_int8(&_reader);
	if (Labels != NULL) {
		(*Labels) = (brp_Iso15_GetUIDList_Labels_Entry*)brp_mempool_create_buf(mempool, (*Labels_len) * sizeof(brp_Iso15_GetUIDList_Labels_Entry));
		if((*Labels) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _Labels_ndx = 0;(_Labels_ndx < (*Labels_len)) & !brp_frame_read_err(&_reader);_Labels_ndx++) {
		brp_Iso15_GetUIDList_Labels_Entry _Labels_Entry;
		brp_Iso15_GetUIDList_Labels_Entry *Labels_Entry = &_Labels_Entry;
		brp_buf _UID;
		brp_buf *UID = &_UID;
		unsigned _DSFID;
		unsigned *DSFID = &_DSFID;
		size_t _UID_len = 8;
		size_t* UID_len = &_UID_len;
		if (UID != NULL) {
			(*UID) = (brp_buf)brp_mempool_create_buf(mempool, (*UID_len));
			if((*UID) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			brp_frame_read(&_reader, (brp_buf)(*UID), (*UID_len));
		} else
			brp_frame_skip(&_reader, (*UID_len));
		if(*EnDSFID) {
			(*DSFID) = (unsigned)brp_frame_read_int8(&_reader);
		}
		if(Labels_Entry != NULL) {
			Labels_Entry->UID = *UID;
			Labels_Entry->DSFID = *DSFID;
		}
		if (Labels != NULL)
			(*Labels)[_Labels_ndx] = *Labels_Entry;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_SetMode(brp_protocol protocol, brp_Iso15_SetMode_Mode _input_Mode, brp_buf _input_UID) {
#else
brp_errcode brp_Iso15_SetMode(brp_Iso15_SetMode_t params) {
	brp_protocol protocol = params.protocol;
	brp_Iso15_SetMode_Mode _input_Mode = params.Mode;
	brp_buf _input_UID = params.UID;
#endif
	brp_Iso15_SetMode_Mode* Mode = &_input_Mode;
	brp_buf* UID = &_input_UID;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Mode));
	if((*Mode) != (brp_Iso15_SetMode_Mode_Unaddressed)) {
		size_t _UID_len_val = 8;
		size_t* UID_len = &_UID_len_val;
		brp_frame_write(_frame, (brp_buf)(*UID), (*UID_len));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_StayQuiet(brp_protocol protocol) {
#else
brp_errcode brp_Iso15_StayQuiet(brp_Iso15_StayQuiet_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_ReadBlock(brp_protocol protocol, unsigned _input_BlockID, unsigned _input_BlockNum, bool _input_EnBlockSec, unsigned* LabelStat, unsigned* BlockLen, brp_Iso15_ReadBlock_Data_Entry** Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso15_ReadBlock(brp_Iso15_ReadBlock_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_BlockID = params.BlockID;
	unsigned _input_BlockNum = params.BlockNum;
	bool _input_EnBlockSec = params.EnBlockSec;
	unsigned* LabelStat = params.LabelStat;
	unsigned* BlockLen = params.BlockLen;
	brp_Iso15_ReadBlock_Data_Entry** Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* BlockID = &_input_BlockID;
	unsigned* BlockNum = &_input_BlockNum;
	bool* EnBlockSec = &_input_EnBlockSec;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	unsigned _tmp_BlockLen;
	if (BlockLen == NULL) BlockLen = &_tmp_BlockLen;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*BlockID));
	brp_frame_write_int8(_frame, (unsigned)(*BlockNum));
	brp_frame_write_int8(_frame, (unsigned)(*EnBlockSec));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if((*LabelStat) == (0)) {
		(*BlockLen) = (unsigned)brp_frame_read_int8(&_reader);
		(*Data_len) = brp_frame_rest( & _reader);
		if (Data != NULL) {
			(*Data) = (brp_Iso15_ReadBlock_Data_Entry*)brp_mempool_create_buf(mempool, 0);
			if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		}
		for(size_t _Data_ndx = 1;!(brp_frame_read_eof(&_reader) | brp_frame_read_err(&_reader));_Data_ndx++) {
			brp_Iso15_ReadBlock_Data_Entry _Data_Entry;
			brp_Iso15_ReadBlock_Data_Entry *Data_Entry = &_Data_Entry;
			brp_buf _BlockData;
			brp_buf *BlockData = &_BlockData;
			unsigned _BlockSecData;
			unsigned *BlockSecData = &_BlockSecData;
			size_t _BlockData_len = 0;
			size_t* BlockData_len = &_BlockData_len;
			if (BlockData != NULL) {
				(*BlockData) = (brp_buf)brp_mempool_create_buf(mempool, (*BlockData_len));
				if((*BlockData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
				brp_frame_read(&_reader, (brp_buf)(*BlockData), (*BlockData_len));
			} else
				brp_frame_skip(&_reader, (*BlockData_len));
			if(*EnBlockSec) {
				(*BlockSecData) = (unsigned)brp_frame_read_int8(&_reader);
			}
			if(Data_Entry != NULL) {
				Data_Entry->BlockData = *BlockData;
				Data_Entry->BlockSecData = *BlockSecData;
			}
			if (Data != NULL) {
				(*Data) = (brp_Iso15_ReadBlock_Data_Entry*)brp_mempool_resize_buf((brp_buf)(*Data), (_Data_ndx * sizeof(brp_Iso15_ReadBlock_Data_Entry)));
				if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
				(*Data)[_Data_ndx-1] = *Data_Entry;
			}
			(*Data_len) = _Data_ndx;
		}
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_WriteBlock(brp_protocol protocol, unsigned _input_BlockID, unsigned _input_BlockNum, unsigned _input_BlockLen, bool _input_OptionFlag, brp_buf* _input_Data, size_t _input_Data_len, unsigned* LabelStat) {
#else
brp_errcode brp_Iso15_WriteBlock(brp_Iso15_WriteBlock_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_BlockID = params.BlockID;
	unsigned _input_BlockNum = params.BlockNum;
	unsigned _input_BlockLen = params.BlockLen;
	bool _input_OptionFlag = params.OptionFlag;
	brp_buf* _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
	unsigned* LabelStat = params.LabelStat;
#endif
	unsigned* BlockID = &_input_BlockID;
	unsigned* BlockNum = &_input_BlockNum;
	unsigned* BlockLen = &_input_BlockLen;
	bool* OptionFlag = &_input_OptionFlag;
	brp_buf** Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*BlockID));
	brp_frame_write_int8(_frame, (unsigned)(*BlockNum));
	brp_frame_write_int8(_frame, (unsigned)(*BlockLen));
	brp_frame_write_int8(_frame, (unsigned)(*OptionFlag));
	for(size_t _Data_ndx = 0;_Data_ndx < (*Data_len);_Data_ndx++) {
		brp_buf _SingleBlock = (*Data)[_Data_ndx];
		brp_buf* SingleBlock = &_SingleBlock;
		size_t _SingleBlock_len_val = 0;
		size_t* SingleBlock_len = &_SingleBlock_len_val;
		brp_frame_write(_frame, (brp_buf)(*SingleBlock), (*SingleBlock_len));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_LockBlock(brp_protocol protocol, unsigned _input_BlockID, bool _input_OptionFlag, unsigned* LabelStat) {
#else
brp_errcode brp_Iso15_LockBlock(brp_Iso15_LockBlock_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_BlockID = params.BlockID;
	bool _input_OptionFlag = params.OptionFlag;
	unsigned* LabelStat = params.LabelStat;
#endif
	unsigned* BlockID = &_input_BlockID;
	bool* OptionFlag = &_input_OptionFlag;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*BlockID));
	brp_frame_write_int8(_frame, (unsigned)(*OptionFlag));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_ResetToReady(brp_protocol protocol, unsigned* LabelStat) {
#else
brp_errcode brp_Iso15_ResetToReady(brp_Iso15_ResetToReady_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* LabelStat = params.LabelStat;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_WriteAFI(brp_protocol protocol, unsigned _input_AFI, bool _input_OptionFlag, unsigned* LabelStat) {
#else
brp_errcode brp_Iso15_WriteAFI(brp_Iso15_WriteAFI_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_AFI = params.AFI;
	bool _input_OptionFlag = params.OptionFlag;
	unsigned* LabelStat = params.LabelStat;
#endif
	unsigned* AFI = &_input_AFI;
	bool* OptionFlag = &_input_OptionFlag;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*AFI));
	brp_frame_write_int8(_frame, (unsigned)(*OptionFlag));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_LockAFI(brp_protocol protocol, bool _input_OptionFlag, unsigned* LabelStat) {
#else
brp_errcode brp_Iso15_LockAFI(brp_Iso15_LockAFI_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_OptionFlag = params.OptionFlag;
	unsigned* LabelStat = params.LabelStat;
#endif
	bool* OptionFlag = &_input_OptionFlag;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*OptionFlag));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_WriteDSFID(brp_protocol protocol, unsigned _input_DSFID, bool _input_OptionFlag, unsigned* LabelStat) {
#else
brp_errcode brp_Iso15_WriteDSFID(brp_Iso15_WriteDSFID_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_DSFID = params.DSFID;
	bool _input_OptionFlag = params.OptionFlag;
	unsigned* LabelStat = params.LabelStat;
#endif
	unsigned* DSFID = &_input_DSFID;
	bool* OptionFlag = &_input_OptionFlag;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 11);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*DSFID));
	brp_frame_write_int8(_frame, (unsigned)(*OptionFlag));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_LockDSFID(brp_protocol protocol, bool _input_OptionFlag, unsigned* LabelStat) {
#else
brp_errcode brp_Iso15_LockDSFID(brp_Iso15_LockDSFID_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_OptionFlag = params.OptionFlag;
	unsigned* LabelStat = params.LabelStat;
#endif
	bool* OptionFlag = &_input_OptionFlag;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 12);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*OptionFlag));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_GetSystemInformation(brp_protocol protocol, unsigned* LabelStat, bool* EnICRef, bool* EnMemSize, bool* EnAFI, bool* EnDSFID, brp_buf* SNR, unsigned* DSFID, unsigned* AFI, unsigned* BlockNum, unsigned* BlockSize, unsigned* ICRef, brp_mempool *mempool) {
#else
brp_errcode brp_Iso15_GetSystemInformation(brp_Iso15_GetSystemInformation_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* LabelStat = params.LabelStat;
	bool* EnICRef = params.EnICRef;
	bool* EnMemSize = params.EnMemSize;
	bool* EnAFI = params.EnAFI;
	bool* EnDSFID = params.EnDSFID;
	brp_buf* SNR = params.SNR;
	unsigned* DSFID = params.DSFID;
	unsigned* AFI = params.AFI;
	unsigned* BlockNum = params.BlockNum;
	unsigned* BlockSize = params.BlockSize;
	unsigned* ICRef = params.ICRef;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	bool _tmp_EnICRef;
	if (EnICRef == NULL) EnICRef = &_tmp_EnICRef;
	bool _tmp_EnMemSize;
	if (EnMemSize == NULL) EnMemSize = &_tmp_EnMemSize;
	bool _tmp_EnAFI;
	if (EnAFI == NULL) EnAFI = &_tmp_EnAFI;
	bool _tmp_EnDSFID;
	if (EnDSFID == NULL) EnDSFID = &_tmp_EnDSFID;
	unsigned _tmp_DSFID;
	if (DSFID == NULL) DSFID = &_tmp_DSFID;
	unsigned _tmp_AFI;
	if (AFI == NULL) AFI = &_tmp_AFI;
	unsigned _tmp_BlockNum;
	if (BlockNum == NULL) BlockNum = &_tmp_BlockNum;
	unsigned _tmp_BlockSize;
	if (BlockSize == NULL) BlockSize = &_tmp_BlockSize;
	unsigned _tmp_ICRef;
	if (ICRef == NULL) ICRef = &_tmp_ICRef;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 13);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if((*LabelStat) == (0)) {
		unsigned _bitmask_10ab = brp_frame_read_int8(&_reader);
		if(EnICRef != NULL)
			(*EnICRef) = (_bitmask_10ab>>3) & 0b1;
		if(EnMemSize != NULL)
			(*EnMemSize) = (_bitmask_10ab>>2) & 0b1;
		if(EnAFI != NULL)
			(*EnAFI) = (_bitmask_10ab>>1) & 0b1;
		if(EnDSFID != NULL)
			(*EnDSFID) = (_bitmask_10ab>>0) & 0b1;
		size_t _SNR_len = 8;
		size_t* SNR_len = &_SNR_len;
		if (SNR != NULL) {
			(*SNR) = (brp_buf)brp_mempool_create_buf(mempool, (*SNR_len));
			if((*SNR) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			brp_frame_read(&_reader, (brp_buf)(*SNR), (*SNR_len));
		} else
			brp_frame_skip(&_reader, (*SNR_len));
	}
	if(((*LabelStat) == (0)) && (*EnDSFID)) {
		(*DSFID) = (unsigned)brp_frame_read_int8(&_reader);
	}
	if(((*LabelStat) == (0)) && (*EnAFI)) {
		(*AFI) = (unsigned)brp_frame_read_int8(&_reader);
	}
	if(((*LabelStat) == (0)) && (*EnMemSize)) {
		(*BlockNum) = (unsigned)brp_frame_read_int8(&_reader);
		(*BlockSize) = (unsigned)brp_frame_read_int8(&_reader);
	}
	if(((*LabelStat) == (0)) && (*EnICRef)) {
		(*ICRef) = (unsigned)brp_frame_read_int8(&_reader);
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_GetSecurityStatus(brp_protocol protocol, unsigned _input_BlockID, unsigned _input_BlockNum, unsigned* LabelStat, unsigned** BlockStat, size_t* BlockStat_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso15_GetSecurityStatus(brp_Iso15_GetSecurityStatus_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_BlockID = params.BlockID;
	unsigned _input_BlockNum = params.BlockNum;
	unsigned* LabelStat = params.LabelStat;
	unsigned** BlockStat = params.BlockStat;
	size_t* BlockStat_len = params.BlockStat_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* BlockID = &_input_BlockID;
	unsigned* BlockNum = &_input_BlockNum;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _BlockStat_len;
	if(BlockStat_len == NULL) BlockStat_len = &_BlockStat_len;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 14);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*BlockID));
	brp_frame_write_int8(_frame, (unsigned)(*BlockNum));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	(*BlockStat_len) = brp_frame_rest( & _reader);
	if (BlockStat != NULL) {
		(*BlockStat) = (unsigned*)brp_mempool_create_buf(mempool, 0);
		if((*BlockStat) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _BlockStat_ndx = 1;!(brp_frame_read_eof(&_reader) | brp_frame_read_err(&_reader));_BlockStat_ndx++) {
		unsigned _Status;
		unsigned *Status = &_Status;
		(*Status) = (unsigned)brp_frame_read_int8(&_reader);
		if (BlockStat != NULL) {
			(*BlockStat) = (unsigned*)brp_mempool_resize_buf((brp_buf)(*BlockStat), (_BlockStat_ndx * sizeof(unsigned)));
			if((*BlockStat) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			(*BlockStat)[_BlockStat_ndx-1] = *Status;
		}
		(*BlockStat_len) = _BlockStat_ndx;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_CustomCommand(brp_protocol protocol, unsigned _input_Cmd, unsigned _input_Opt, unsigned _input_MFC, unsigned _input_TO, brp_buf _input_RequestData, size_t _input_RequestData_len, unsigned* LabelStat, brp_buf* ResponseData, size_t* ResponseData_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso15_CustomCommand(brp_Iso15_CustomCommand_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Cmd = params.Cmd;
	unsigned _input_Opt = params.Opt;
	unsigned _input_MFC = params.MFC;
	unsigned _input_TO = params.TO;
	brp_buf _input_RequestData = params.RequestData;
	size_t _input_RequestData_len = params.RequestData_len;
	unsigned* LabelStat = params.LabelStat;
	brp_buf* ResponseData = params.ResponseData;
	size_t* ResponseData_len = params.ResponseData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Cmd = &_input_Cmd;
	unsigned* Opt = &_input_Opt;
	unsigned* MFC = &_input_MFC;
	unsigned* TO = &_input_TO;
	brp_buf* RequestData = &_input_RequestData;
	size_t* RequestData_len = &_input_RequestData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ResponseData_len;
	if(ResponseData_len == NULL) ResponseData_len = &_ResponseData_len;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 15);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Cmd));
	brp_frame_write_int8(_frame, (unsigned)(*Opt));
	brp_frame_write_int8(_frame, (unsigned)(*MFC));
	brp_frame_write_int8(_frame, (unsigned)(*TO));
	brp_frame_write_int16(_frame, (unsigned)(*RequestData_len));
	brp_frame_write(_frame, (brp_buf)(*RequestData), (*RequestData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if((*LabelStat) == (0)) {
		(*ResponseData_len) = brp_frame_read_int16(&_reader);
		if (ResponseData != NULL) {
			(*ResponseData) = (brp_buf)brp_mempool_create_buf(mempool, (*ResponseData_len));
			if((*ResponseData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			brp_frame_read(&_reader, (brp_buf)(*ResponseData), (*ResponseData_len));
		} else
			brp_frame_skip(&_reader, (*ResponseData_len));
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_ReadSingleBlock(brp_protocol protocol, unsigned _input_BlockID, bool _input_EnBlockSec, unsigned* LabelStat, brp_buf* Payload, size_t* Payload_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso15_ReadSingleBlock(brp_Iso15_ReadSingleBlock_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_BlockID = params.BlockID;
	bool _input_EnBlockSec = params.EnBlockSec;
	unsigned* LabelStat = params.LabelStat;
	brp_buf* Payload = params.Payload;
	size_t* Payload_len = params.Payload_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* BlockID = &_input_BlockID;
	bool* EnBlockSec = &_input_EnBlockSec;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Payload_len;
	if(Payload_len == NULL) Payload_len = &_Payload_len;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 17);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*BlockID));
	brp_frame_write_int8(_frame, (unsigned)(*EnBlockSec));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if((*LabelStat) == (0)) {
		(*Payload_len) = brp_frame_read_int8(&_reader);
		if (Payload != NULL) {
			(*Payload) = (brp_buf)brp_mempool_create_buf(mempool, (*Payload_len));
			if((*Payload) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			brp_frame_read(&_reader, (brp_buf)(*Payload), (*Payload_len));
		} else
			brp_frame_skip(&_reader, (*Payload_len));
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_WriteSingleBlock(brp_protocol protocol, unsigned _input_BlockID, unsigned _input_BlockLen, bool _input_OptionFlag, brp_buf _input_SingleBlockData, size_t _input_SingleBlockData_len, unsigned* LabelStat) {
#else
brp_errcode brp_Iso15_WriteSingleBlock(brp_Iso15_WriteSingleBlock_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_BlockID = params.BlockID;
	unsigned _input_BlockLen = params.BlockLen;
	bool _input_OptionFlag = params.OptionFlag;
	brp_buf _input_SingleBlockData = params.SingleBlockData;
	size_t _input_SingleBlockData_len = params.SingleBlockData_len;
	unsigned* LabelStat = params.LabelStat;
#endif
	unsigned* BlockID = &_input_BlockID;
	unsigned* BlockLen = &_input_BlockLen;
	bool* OptionFlag = &_input_OptionFlag;
	brp_buf* SingleBlockData = &_input_SingleBlockData;
	size_t* SingleBlockData_len = &_input_SingleBlockData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 18);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*BlockID));
	brp_frame_write_int8(_frame, (unsigned)(*BlockLen));
	brp_frame_write_int8(_frame, (unsigned)(*OptionFlag));
	brp_frame_write(_frame, (brp_buf)(*SingleBlockData), (*SingleBlockData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_TransparentCmdLegacy(brp_protocol protocol, bool _input_EnRxWait, bool _input_EnCRCRX, bool _input_EnCRCTX, unsigned _input_Len, unsigned _input_Timeout, brp_buf _input_Data, unsigned _input_RxWait, brp_buf* LabelData, size_t* LabelData_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso15_TransparentCmdLegacy(brp_Iso15_TransparentCmdLegacy_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_EnRxWait = params.EnRxWait;
	bool _input_EnCRCRX = params.EnCRCRX;
	bool _input_EnCRCTX = params.EnCRCTX;
	unsigned _input_Len = params.Len;
	unsigned _input_Timeout = params.Timeout;
	brp_buf _input_Data = params.Data;
	unsigned _input_RxWait = params.RxWait;
	brp_buf* LabelData = params.LabelData;
	size_t* LabelData_len = params.LabelData_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* EnRxWait = &_input_EnRxWait;
	bool* EnCRCRX = &_input_EnCRCRX;
	bool* EnCRCTX = &_input_EnCRCTX;
	unsigned* Len = &_input_Len;
	unsigned* Timeout = &_input_Timeout;
	brp_buf* Data = &_input_Data;
	unsigned* RxWait = &_input_RxWait;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _LabelData_len;
	if(LabelData_len == NULL) LabelData_len = &_LabelData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 32);
	brp_frame_write_int32(_frame, 100);
	if(!(*EnRxWait) && (*RxWait)) (*EnRxWait) = true;
	unsigned _bitmask_2620 = 0;
	_bitmask_2620 |= (*EnRxWait & 0b1) << 4;
	_bitmask_2620 |= (*EnCRCRX & 0b1) << 3;
	_bitmask_2620 |= (*EnCRCTX & 0b1) << 2;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_2620);
	brp_frame_write_int16(_frame, (unsigned)(*Len));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	size_t _Data_len_val = 0;
	size_t* Data_len = &_Data_len_val;
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	if(*EnRxWait) {
		brp_frame_write_int16(_frame, (unsigned)(*RxWait));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelData_len) = brp_frame_read_int16(&_reader);
	if (LabelData != NULL) {
		(*LabelData) = (brp_buf)brp_mempool_create_buf(mempool, (*LabelData_len));
		if((*LabelData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*LabelData), (*LabelData_len));
	} else
		brp_frame_skip(&_reader, (*LabelData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_WriteMultipleBlocks(brp_protocol protocol, unsigned _input_FirstBlockId, brp_Iso15_WriteMultipleBlocks_WriteBlocks_Entry* _input_WriteBlocks, size_t _input_WriteBlocks_len, bool _input_OptionFlag, unsigned* LabelStat) {
#else
brp_errcode brp_Iso15_WriteMultipleBlocks(brp_Iso15_WriteMultipleBlocks_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_FirstBlockId = params.FirstBlockId;
	brp_Iso15_WriteMultipleBlocks_WriteBlocks_Entry* _input_WriteBlocks = params.WriteBlocks;
	size_t _input_WriteBlocks_len = params.WriteBlocks_len;
	bool _input_OptionFlag = params.OptionFlag;
	unsigned* LabelStat = params.LabelStat;
#endif
	unsigned* FirstBlockId = &_input_FirstBlockId;
	brp_Iso15_WriteMultipleBlocks_WriteBlocks_Entry** WriteBlocks = &_input_WriteBlocks;
	size_t* WriteBlocks_len = &_input_WriteBlocks_len;
	bool* OptionFlag = &_input_OptionFlag;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*FirstBlockId));
	brp_frame_write_int16(_frame, (unsigned)(*WriteBlocks_len));
	for(size_t _WriteBlocks_ndx = 0;_WriteBlocks_ndx < (*WriteBlocks_len);_WriteBlocks_ndx++) {
		brp_Iso15_WriteMultipleBlocks_WriteBlocks_Entry _WriteBlocks_Entry = (*WriteBlocks)[_WriteBlocks_ndx];
		brp_Iso15_WriteMultipleBlocks_WriteBlocks_Entry* WriteBlocks_Entry = &_WriteBlocks_Entry;
		brp_buf _WriteBlock = (WriteBlocks_Entry)->WriteBlock;
		brp_buf* WriteBlock = &_WriteBlock;
		size_t _WriteBlock_len = (WriteBlocks_Entry)->WriteBlock_len;
		size_t* WriteBlock_len = &_WriteBlock_len;
		brp_frame_write_int8(_frame, (unsigned)(*WriteBlock_len));
		brp_frame_write(_frame, (brp_buf)(*WriteBlock), (*WriteBlock_len));
	}
	brp_frame_write_int8(_frame, (unsigned)(*OptionFlag));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_ReadMultipleBlocks(brp_protocol protocol, unsigned _input_FirstBlockId, unsigned _input_BlockCount, bool _input_EnBlockSec, unsigned* LabelStat, brp_Iso15_ReadMultipleBlocks_RecvBlocks_Entry** RecvBlocks, size_t* RecvBlocks_len, unsigned** BlocksSecData, size_t* BlocksSecData_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso15_ReadMultipleBlocks(brp_Iso15_ReadMultipleBlocks_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_FirstBlockId = params.FirstBlockId;
	unsigned _input_BlockCount = params.BlockCount;
	bool _input_EnBlockSec = params.EnBlockSec;
	unsigned* LabelStat = params.LabelStat;
	brp_Iso15_ReadMultipleBlocks_RecvBlocks_Entry** RecvBlocks = params.RecvBlocks;
	size_t* RecvBlocks_len = params.RecvBlocks_len;
	unsigned** BlocksSecData = params.BlocksSecData;
	size_t* BlocksSecData_len = params.BlocksSecData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* FirstBlockId = &_input_FirstBlockId;
	unsigned* BlockCount = &_input_BlockCount;
	bool* EnBlockSec = &_input_EnBlockSec;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _RecvBlocks_len;
	if(RecvBlocks_len == NULL) RecvBlocks_len = &_RecvBlocks_len;
	size_t _BlocksSecData_len;
	if(BlocksSecData_len == NULL) BlocksSecData_len = &_BlocksSecData_len;
	unsigned _tmp_LabelStat;
	if (LabelStat == NULL) LabelStat = &_tmp_LabelStat;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 34);
	brp_frame_write_int32(_frame, 100);
	if (_input_BlockCount == 0) _input_BlockCount = (unsigned)1;
	brp_frame_write_int8(_frame, (unsigned)(*FirstBlockId));
	brp_frame_write_int16(_frame, (unsigned)(*BlockCount));
	brp_frame_write_int8(_frame, (unsigned)(*EnBlockSec));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LabelStat) = (unsigned)brp_frame_read_int8(&_reader);
	(*RecvBlocks_len) = brp_frame_read_int16(&_reader);
	if (RecvBlocks != NULL) {
		(*RecvBlocks) = (brp_Iso15_ReadMultipleBlocks_RecvBlocks_Entry*)brp_mempool_create_buf(mempool, (*RecvBlocks_len) * sizeof(brp_Iso15_ReadMultipleBlocks_RecvBlocks_Entry));
		if((*RecvBlocks) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _RecvBlocks_ndx = 0;(_RecvBlocks_ndx < (*RecvBlocks_len)) & !brp_frame_read_err(&_reader);_RecvBlocks_ndx++) {
		brp_Iso15_ReadMultipleBlocks_RecvBlocks_Entry _RecvBlocks_Entry;
		brp_Iso15_ReadMultipleBlocks_RecvBlocks_Entry *RecvBlocks_Entry = &_RecvBlocks_Entry;
		brp_buf _RecvBlock;
		brp_buf *RecvBlock = &_RecvBlock;
		size_t _RecvBlock_len;
		size_t *RecvBlock_len = &_RecvBlock_len;
		(*RecvBlock_len) = brp_frame_read_int8(&_reader);
		if (RecvBlock != NULL) {
			(*RecvBlock) = (brp_buf)brp_mempool_create_buf(mempool, (*RecvBlock_len));
			if((*RecvBlock) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			brp_frame_read(&_reader, (brp_buf)(*RecvBlock), (*RecvBlock_len));
		} else
			brp_frame_skip(&_reader, (*RecvBlock_len));
		if(RecvBlocks_Entry != NULL) {
			RecvBlocks_Entry->RecvBlock = *RecvBlock;
			RecvBlocks_Entry->RecvBlock_len = *RecvBlock_len;
		}
		if (RecvBlocks != NULL)
			(*RecvBlocks)[_RecvBlocks_ndx] = *RecvBlocks_Entry;
	}
	(*BlocksSecData_len) = brp_frame_read_int16(&_reader);
	if (BlocksSecData != NULL) {
		(*BlocksSecData) = (unsigned*)brp_mempool_create_buf(mempool, (*BlocksSecData_len) * sizeof(unsigned));
		if((*BlocksSecData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _BlocksSecData_ndx = 0;(_BlocksSecData_ndx < (*BlocksSecData_len)) & !brp_frame_read_err(&_reader);_BlocksSecData_ndx++) {
		unsigned _BlockSecData;
		unsigned *BlockSecData = &_BlockSecData;
		(*BlockSecData) = (unsigned)brp_frame_read_int8(&_reader);
		if (BlocksSecData != NULL)
			(*BlocksSecData)[_BlocksSecData_ndx] = *BlockSecData;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso15_TransparentCmd(brp_protocol protocol, brp_buf _input_SendData, size_t _input_SendData_len, unsigned _input_Timeout, bool _input_EnCrcRx, bool _input_EnCrcTx, unsigned _input_RxWait, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso15_TransparentCmd(brp_Iso15_TransparentCmd_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_SendData = params.SendData;
	size_t _input_SendData_len = params.SendData_len;
	unsigned _input_Timeout = params.Timeout;
	bool _input_EnCrcRx = params.EnCrcRx;
	bool _input_EnCrcTx = params.EnCrcTx;
	unsigned _input_RxWait = params.RxWait;
	brp_buf* RecvData = params.RecvData;
	size_t* RecvData_len = params.RecvData_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* SendData = &_input_SendData;
	size_t* SendData_len = &_input_SendData_len;
	unsigned* Timeout = &_input_Timeout;
	bool* EnCrcRx = &_input_EnCrcRx;
	bool* EnCrcTx = &_input_EnCrcTx;
	unsigned* RxWait = &_input_RxWait;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _RecvData_len;
	if(RecvData_len == NULL) RecvData_len = &_RecvData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int8(_frame, 35);
	brp_frame_write_int32(_frame, 100);
	if (_input_Timeout == 0) _input_Timeout = (unsigned)26;
	brp_frame_write_int16(_frame, (unsigned)(*SendData_len));
	brp_frame_write(_frame, (brp_buf)(*SendData), (*SendData_len));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_frame_write_int8(_frame, (unsigned)(*EnCrcRx));
	brp_frame_write_int8(_frame, (unsigned)(*EnCrcTx));
	brp_frame_write_int16(_frame, (unsigned)(*RxWait));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*RecvData_len) = brp_frame_read_int16(&_reader);
	if (RecvData != NULL) {
		(*RecvData) = (brp_buf)brp_mempool_create_buf(mempool, (*RecvData_len));
		if((*RecvData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*RecvData), (*RecvData_len));
	} else
		brp_frame_skip(&_reader, (*RecvData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_SelectSlot(brp_protocol protocol, unsigned _input_SlotIndex) {
#else
brp_errcode brp_Iso78_SelectSlot(brp_Iso78_SelectSlot_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_SlotIndex = params.SlotIndex;
#endif
	unsigned* SlotIndex = &_input_SlotIndex;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 64);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*SlotIndex));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_OpenSamLegacy(brp_protocol protocol, brp_buf* ATR, size_t* ATR_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso78_OpenSamLegacy(brp_Iso78_OpenSamLegacy_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* ATR = params.ATR;
	size_t* ATR_len = params.ATR_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ATR_len;
	if(ATR_len == NULL) ATR_len = &_ATR_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 64);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 1200);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ATR_len) = brp_frame_read_int8(&_reader);
	if (ATR != NULL) {
		(*ATR) = (brp_buf)brp_mempool_create_buf(mempool, (*ATR_len));
		if((*ATR) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ATR), (*ATR_len));
	} else
		brp_frame_skip(&_reader, (*ATR_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_CloseSamLegacy(brp_protocol protocol) {
#else
brp_errcode brp_Iso78_CloseSamLegacy(brp_Iso78_CloseSamLegacy_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 64);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_ExchangeApduLegacy(brp_protocol protocol, brp_buf _input_SendData, size_t _input_SendData_len, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso78_ExchangeApduLegacy(brp_Iso78_ExchangeApduLegacy_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_SendData = params.SendData;
	size_t _input_SendData_len = params.SendData_len;
	brp_buf* RecvData = params.RecvData;
	size_t* RecvData_len = params.RecvData_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* SendData = &_input_SendData;
	size_t* SendData_len = &_input_SendData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _RecvData_len;
	if(RecvData_len == NULL) RecvData_len = &_RecvData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 64);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*SendData_len));
	brp_frame_write(_frame, (brp_buf)(*SendData), (*SendData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*RecvData_len) = brp_frame_read_int16(&_reader);
	if (RecvData != NULL) {
		(*RecvData) = (brp_buf)brp_mempool_create_buf(mempool, (*RecvData_len));
		if((*RecvData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*RecvData), (*RecvData_len));
	} else
		brp_frame_skip(&_reader, (*RecvData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_OpenSam(brp_protocol protocol, brp_Iso78_OpenSam_LID _input_LID, unsigned* SamHandle, brp_buf* ATR, size_t* ATR_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso78_OpenSam(brp_Iso78_OpenSam_t params) {
	brp_protocol protocol = params.protocol;
	brp_Iso78_OpenSam_LID _input_LID = params.LID;
	unsigned* SamHandle = params.SamHandle;
	brp_buf* ATR = params.ATR;
	size_t* ATR_len = params.ATR_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_Iso78_OpenSam_LID* LID = &_input_LID;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ATR_len;
	if(ATR_len == NULL) ATR_len = &_ATR_len;
	unsigned _tmp_SamHandle;
	if (SamHandle == NULL) SamHandle = &_tmp_SamHandle;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 64);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*LID));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*SamHandle) = (unsigned)brp_frame_read_int8(&_reader);
	(*ATR_len) = brp_frame_read_int8(&_reader);
	if (ATR != NULL) {
		(*ATR) = (brp_buf)brp_mempool_create_buf(mempool, (*ATR_len));
		if((*ATR) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ATR), (*ATR_len));
	} else
		brp_frame_skip(&_reader, (*ATR_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_CloseSam(brp_protocol protocol, unsigned _input_SamHandle) {
#else
brp_errcode brp_Iso78_CloseSam(brp_Iso78_CloseSam_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_SamHandle = params.SamHandle;
#endif
	unsigned* SamHandle = &_input_SamHandle;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 64);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*SamHandle));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Iso78_ExchangeApdu(brp_protocol protocol, unsigned _input_SamHandle, brp_buf _input_SendData, size_t _input_SendData_len, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool) {
#else
brp_errcode brp_Iso78_ExchangeApdu(brp_Iso78_ExchangeApdu_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_SamHandle = params.SamHandle;
	brp_buf _input_SendData = params.SendData;
	size_t _input_SendData_len = params.SendData_len;
	brp_buf* RecvData = params.RecvData;
	size_t* RecvData_len = params.RecvData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* SamHandle = &_input_SamHandle;
	brp_buf* SendData = &_input_SendData;
	size_t* SendData_len = &_input_SendData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _RecvData_len;
	if(RecvData_len == NULL) RecvData_len = &_RecvData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 64);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*SamHandle));
	brp_frame_write_int16(_frame, (unsigned)(*SendData_len));
	brp_frame_write(_frame, (brp_buf)(*SendData), (*SendData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*RecvData_len) = brp_frame_read_int16(&_reader);
	if (RecvData != NULL) {
		(*RecvData) = (brp_buf)brp_mempool_create_buf(mempool, (*RecvData_len));
		if((*RecvData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*RecvData), (*RecvData_len));
	} else
		brp_frame_skip(&_reader, (*RecvData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Legic_TransparentCommand4000(brp_protocol protocol, unsigned _input_CmdCode, brp_buf _input_CmdParams, size_t _input_CmdParams_len, unsigned _input_Timeout, unsigned* Status, brp_buf* Resp, size_t* Resp_len, brp_mempool *mempool) {
#else
brp_errcode brp_Legic_TransparentCommand4000(brp_Legic_TransparentCommand4000_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_CmdCode = params.CmdCode;
	brp_buf _input_CmdParams = params.CmdParams;
	size_t _input_CmdParams_len = params.CmdParams_len;
	unsigned _input_Timeout = params.Timeout;
	unsigned* Status = params.Status;
	brp_buf* Resp = params.Resp;
	size_t* Resp_len = params.Resp_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* CmdCode = &_input_CmdCode;
	brp_buf* CmdParams = &_input_CmdParams;
	size_t* CmdParams_len = &_input_CmdParams_len;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Resp_len;
	if(Resp_len == NULL) Resp_len = &_Resp_len;
	unsigned _tmp_Status;
	if (Status == NULL) Status = &_tmp_Status;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 30);
	brp_frame_write_int8(_frame, 32);
	brp_frame_write_int32(_frame, 3000);
	brp_frame_write_int8(_frame, (unsigned)(*CmdCode));
	brp_frame_write_int8(_frame, (unsigned)(*CmdParams_len));
	brp_frame_write(_frame, (brp_buf)(*CmdParams), (*CmdParams_len));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Status) = (unsigned)brp_frame_read_int8(&_reader);
	(*Resp_len) = brp_frame_read_int8(&_reader);
	if (Resp != NULL) {
		(*Resp) = (brp_buf)brp_mempool_create_buf(mempool, (*Resp_len));
		if((*Resp) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Resp), (*Resp_len));
	} else
		brp_frame_skip(&_reader, (*Resp_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Legic_TransparentCommand6000(brp_protocol protocol, unsigned _input_CmdCode, brp_buf _input_CmdParams, size_t _input_CmdParams_len, unsigned _input_Timeout, unsigned* Status, brp_buf* Resp, size_t* Resp_len, brp_mempool *mempool) {
#else
brp_errcode brp_Legic_TransparentCommand6000(brp_Legic_TransparentCommand6000_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_CmdCode = params.CmdCode;
	brp_buf _input_CmdParams = params.CmdParams;
	size_t _input_CmdParams_len = params.CmdParams_len;
	unsigned _input_Timeout = params.Timeout;
	unsigned* Status = params.Status;
	brp_buf* Resp = params.Resp;
	size_t* Resp_len = params.Resp_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* CmdCode = &_input_CmdCode;
	brp_buf* CmdParams = &_input_CmdParams;
	size_t* CmdParams_len = &_input_CmdParams_len;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Resp_len;
	if(Resp_len == NULL) Resp_len = &_Resp_len;
	unsigned _tmp_Status;
	if (Status == NULL) Status = &_tmp_Status;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 30);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int32(_frame, 3000);
	brp_frame_write_int8(_frame, (unsigned)(*CmdCode));
	brp_frame_write_int8(_frame, (unsigned)(*CmdParams_len));
	brp_frame_write(_frame, (brp_buf)(*CmdParams), (*CmdParams_len));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Status) = (unsigned)brp_frame_read_int8(&_reader);
	(*Resp_len) = brp_frame_read_int8(&_reader);
	if (Resp != NULL) {
		(*Resp) = (brp_buf)brp_mempool_create_buf(mempool, (*Resp_len));
		if((*Resp) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Resp), (*Resp_len));
	} else
		brp_frame_skip(&_reader, (*Resp_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Lga_TransparentCommand(brp_protocol protocol, unsigned _input_CmdCode, brp_buf _input_CmdParams, size_t _input_CmdParams_len, unsigned _input_Timeout, unsigned* Status, brp_buf* Resp, size_t* Resp_len, brp_mempool *mempool) {
#else
brp_errcode brp_Lga_TransparentCommand(brp_Lga_TransparentCommand_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_CmdCode = params.CmdCode;
	brp_buf _input_CmdParams = params.CmdParams;
	size_t _input_CmdParams_len = params.CmdParams_len;
	unsigned _input_Timeout = params.Timeout;
	unsigned* Status = params.Status;
	brp_buf* Resp = params.Resp;
	size_t* Resp_len = params.Resp_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* CmdCode = &_input_CmdCode;
	brp_buf* CmdParams = &_input_CmdParams;
	size_t* CmdParams_len = &_input_CmdParams_len;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Resp_len;
	if(Resp_len == NULL) Resp_len = &_Resp_len;
	unsigned _tmp_Status;
	if (Status == NULL) Status = &_tmp_Status;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 18);
	brp_frame_write_int8(_frame, 32);
	brp_frame_write_int32(_frame, 3000);
	brp_frame_write_int8(_frame, (unsigned)(*CmdCode));
	brp_frame_write_int8(_frame, (unsigned)(*CmdParams_len));
	brp_frame_write(_frame, (brp_buf)(*CmdParams), (*CmdParams_len));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Status) = (unsigned)brp_frame_read_int8(&_reader);
	(*Resp_len) = brp_frame_read_int8(&_reader);
	if (Resp != NULL) {
		(*Resp) = (brp_buf)brp_mempool_create_buf(mempool, (*Resp_len));
		if((*Resp) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Resp), (*Resp_len));
	} else
		brp_frame_skip(&_reader, (*Resp_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Lic_GetLicenses(brp_protocol protocol, brp_LicenseBitMask* LicenseBitMask) {
#else
brp_errcode brp_Lic_GetLicenses(brp_Lic_GetLicenses_t params) {
	brp_protocol protocol = params.protocol;
	brp_LicenseBitMask* LicenseBitMask = params.LicenseBitMask;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 11);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	unsigned _LicenseBitMask_int = brp_frame_read_int32(&_reader);
	if(LicenseBitMask != NULL) {
		(LicenseBitMask->Ble) = (_LicenseBitMask_int>>3) & 0b1;
		(LicenseBitMask->BleLicRequired) = (_LicenseBitMask_int>>2) & 0b1;
		(LicenseBitMask->HidOnlyForSE) = (_LicenseBitMask_int>>1) & 0b1;
		(LicenseBitMask->Hid) = (_LicenseBitMask_int>>0) & 0b1;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Lic_ReadLicCard(brp_protocol protocol) {
#else
brp_errcode brp_Lic_ReadLicCard(brp_Lic_ReadLicCard_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 11);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 2000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Main_Bf2Upload(brp_protocol protocol, brp_buf _input_Bf2Line, size_t _input_Bf2Line_len, brp_Main_Bf2Upload_ResultCode* ResultCode, unsigned* InvertedResultCode) {
#else
brp_errcode brp_Main_Bf2Upload(brp_Main_Bf2Upload_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_Bf2Line = params.Bf2Line;
	size_t _input_Bf2Line_len = params.Bf2Line_len;
	brp_Main_Bf2Upload_ResultCode* ResultCode = params.ResultCode;
	unsigned* InvertedResultCode = params.InvertedResultCode;
#endif
	brp_buf* Bf2Line = &_input_Bf2Line;
	size_t* Bf2Line_len = &_input_Bf2Line_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_InvertedResultCode;
	if (InvertedResultCode == NULL) InvertedResultCode = &_tmp_InvertedResultCode;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 240);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 5000);
	brp_frame_write(_frame, (brp_buf)(*Bf2Line), (*Bf2Line_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	int _ResultCode_int_val = brp_frame_read_int8(&_reader);
	if (ResultCode != NULL) {
		if (brp_Main_Bf2Upload_ResultCode_is_valid(_ResultCode_int_val))
			(*ResultCode) = (brp_Main_Bf2Upload_ResultCode)_ResultCode_int_val;
		else
			(*ResultCode) = brp_Main_Bf2Upload_ResultCode_undefined;
	}
	(*InvertedResultCode) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Main_SwitchFW(brp_protocol protocol) {
#else
brp_errcode brp_Main_SwitchFW(brp_Main_SwitchFW_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 240);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 5000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Main_MatchPlatformId2(brp_protocol protocol, brp_buf _input_Filter, size_t _input_Filter_len, bool* Matches) {
#else
brp_errcode brp_Main_MatchPlatformId2(brp_Main_MatchPlatformId2_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_Filter = params.Filter;
	size_t _input_Filter_len = params.Filter_len;
	bool* Matches = params.Matches;
#endif
	brp_buf* Filter = &_input_Filter;
	size_t* Filter_len = &_input_Filter_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	bool _tmp_Matches;
	if (Matches == NULL) Matches = &_tmp_Matches;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 240);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write(_frame, (brp_buf)(*Filter), (*Filter_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Matches) = (bool)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Main_IsFirmwareUpToDate(brp_protocol protocol, brp_buf _input_VersionDesc, size_t _input_VersionDesc_len) {
#else
brp_errcode brp_Main_IsFirmwareUpToDate(brp_Main_IsFirmwareUpToDate_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_VersionDesc = params.VersionDesc;
	size_t _input_VersionDesc_len = params.VersionDesc_len;
#endif
	brp_buf* VersionDesc = &_input_VersionDesc;
	size_t* VersionDesc_len = &_input_VersionDesc_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 240);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 5000);
	brp_frame_write_int8(_frame, (unsigned)(*VersionDesc_len));
	brp_frame_write(_frame, (brp_buf)(*VersionDesc), (*VersionDesc_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Main_Bf3UploadStart(brp_protocol protocol, unsigned* ReqDataAdr, unsigned* ReqDataLen) {
#else
brp_errcode brp_Main_Bf3UploadStart(brp_Main_Bf3UploadStart_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* ReqDataAdr = params.ReqDataAdr;
	unsigned* ReqDataLen = params.ReqDataLen;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_ReqDataAdr;
	if (ReqDataAdr == NULL) ReqDataAdr = &_tmp_ReqDataAdr;
	unsigned _tmp_ReqDataLen;
	if (ReqDataLen == NULL) ReqDataLen = &_tmp_ReqDataLen;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 240);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ReqDataAdr) = (unsigned)brp_frame_read_int32(&_reader);
	(*ReqDataLen) = (unsigned)brp_frame_read_int16(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Main_Bf3UploadContinue(brp_protocol protocol, unsigned _input_DataAdr, brp_buf _input_Data, size_t _input_Data_len, bool* Reconnect, bool* Continue, unsigned* ReqDataAdr, unsigned* ReqDataLen, bool* ContainsEstimation, bool* ContainsReconnectRetryTimeout, unsigned* ReconnectRetryTimeout, unsigned* EstimatedNumberOfBytes, unsigned* EstimatedTimeOverhead) {
#else
brp_errcode brp_Main_Bf3UploadContinue(brp_Main_Bf3UploadContinue_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_DataAdr = params.DataAdr;
	brp_buf _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
	bool* Reconnect = params.Reconnect;
	bool* Continue = params.Continue;
	unsigned* ReqDataAdr = params.ReqDataAdr;
	unsigned* ReqDataLen = params.ReqDataLen;
	bool* ContainsEstimation = params.ContainsEstimation;
	bool* ContainsReconnectRetryTimeout = params.ContainsReconnectRetryTimeout;
	unsigned* ReconnectRetryTimeout = params.ReconnectRetryTimeout;
	unsigned* EstimatedNumberOfBytes = params.EstimatedNumberOfBytes;
	unsigned* EstimatedTimeOverhead = params.EstimatedTimeOverhead;
#endif
	unsigned* DataAdr = &_input_DataAdr;
	brp_buf* Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	bool _tmp_Reconnect;
	if (Reconnect == NULL) Reconnect = &_tmp_Reconnect;
	bool _tmp_Continue;
	if (Continue == NULL) Continue = &_tmp_Continue;
	unsigned _tmp_ReqDataAdr;
	if (ReqDataAdr == NULL) ReqDataAdr = &_tmp_ReqDataAdr;
	unsigned _tmp_ReqDataLen;
	if (ReqDataLen == NULL) ReqDataLen = &_tmp_ReqDataLen;
	bool _tmp_ContainsEstimation;
	if (ContainsEstimation == NULL) ContainsEstimation = &_tmp_ContainsEstimation;
	bool _tmp_ContainsReconnectRetryTimeout;
	if (ContainsReconnectRetryTimeout == NULL) ContainsReconnectRetryTimeout = &_tmp_ContainsReconnectRetryTimeout;
	unsigned _tmp_ReconnectRetryTimeout;
	if (ReconnectRetryTimeout == NULL) ReconnectRetryTimeout = &_tmp_ReconnectRetryTimeout;
	unsigned _tmp_EstimatedNumberOfBytes;
	if (EstimatedNumberOfBytes == NULL) EstimatedNumberOfBytes = &_tmp_EstimatedNumberOfBytes;
	unsigned _tmp_EstimatedTimeOverhead;
	if (EstimatedTimeOverhead == NULL) EstimatedTimeOverhead = &_tmp_EstimatedTimeOverhead;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 240);
	brp_frame_write_int8(_frame, 17);
	brp_frame_write_int32(_frame, 1000);
	brp_frame_write_int32(_frame, (unsigned)(*DataAdr));
	brp_frame_write_int16(_frame, (unsigned)(*Data_len));
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	unsigned _bitmask_bf8a = brp_frame_read_int8(&_reader);
	if(Reconnect != NULL)
		(*Reconnect) = (_bitmask_bf8a>>1) & 0b1;
	if(Continue != NULL)
		(*Continue) = (_bitmask_bf8a>>0) & 0b1;
	(*ReqDataAdr) = (unsigned)brp_frame_read_int32(&_reader);
	(*ReqDataLen) = (unsigned)brp_frame_read_int16(&_reader);
	unsigned _bitmask_8336 = brp_frame_read_int8(&_reader);
	if(ContainsEstimation != NULL)
		(*ContainsEstimation) = (_bitmask_8336>>1) & 0b1;
	if(ContainsReconnectRetryTimeout != NULL)
		(*ContainsReconnectRetryTimeout) = (_bitmask_8336>>0) & 0b1;
	if(*ContainsReconnectRetryTimeout) {
		(*ReconnectRetryTimeout) = (unsigned)brp_frame_read_int32(&_reader);
	}
	if(*ContainsEstimation) {
		(*EstimatedNumberOfBytes) = (unsigned)brp_frame_read_int32(&_reader);
		(*EstimatedTimeOverhead) = (unsigned)brp_frame_read_int32(&_reader);
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mce_Enable(brp_protocol protocol, brp_Mce_Enable_Mode _input_Mode) {
#else
brp_errcode brp_Mce_Enable(brp_Mce_Enable_t params) {
	brp_protocol protocol = params.protocol;
	brp_Mce_Enable_Mode _input_Mode = params.Mode;
#endif
	brp_Mce_Enable_Mode* Mode = &_input_Mode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 77);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Mode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mce_Request(brp_protocol protocol, brp_buf* Snr, size_t* Snr_len, brp_mempool *mempool) {
#else
brp_errcode brp_Mce_Request(brp_Mce_Request_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Snr = params.Snr;
	size_t* Snr_len = params.Snr_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Snr_len;
	if(Snr_len == NULL) Snr_len = &_Snr_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 77);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Snr_len) = brp_frame_read_int8(&_reader);
	if (Snr != NULL) {
		(*Snr) = (brp_buf)brp_mempool_create_buf(mempool, (*Snr_len));
		if((*Snr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Snr), (*Snr_len));
	} else
		brp_frame_skip(&_reader, (*Snr_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_LoadKey(brp_protocol protocol, unsigned _input_KeyIdx, brp_buf _input_Key) {
#else
brp_errcode brp_Mif_LoadKey(brp_Mif_LoadKey_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_KeyIdx = params.KeyIdx;
	brp_buf _input_Key = params.Key;
#endif
	unsigned* KeyIdx = &_input_KeyIdx;
	brp_buf* Key = &_input_Key;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*KeyIdx));
	size_t _Key_len_val = 6;
	size_t* Key_len = &_Key_len_val;
	brp_frame_write(_frame, (brp_buf)(*Key), (*Key_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_Request(brp_protocol protocol, bool _input_ReqAll, unsigned* ATQA) {
#else
brp_errcode brp_Mif_Request(brp_Mif_Request_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_ReqAll = params.ReqAll;
	unsigned* ATQA = params.ATQA;
#endif
	bool* ReqAll = &_input_ReqAll;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_ATQA;
	if (ATQA == NULL) ATQA = &_tmp_ATQA;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_6acc = 0;
	_bitmask_6acc |= (*ReqAll & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_6acc);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ATQA) = (unsigned)brp_frame_read_int16(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_Anticoll(brp_protocol protocol, unsigned _input_BitCount, brp_buf _input_PreSelSer, brp_buf* Snr, brp_mempool *mempool) {
#else
brp_errcode brp_Mif_Anticoll(brp_Mif_Anticoll_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_BitCount = params.BitCount;
	brp_buf _input_PreSelSer = params.PreSelSer;
	brp_buf* Snr = params.Snr;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* BitCount = &_input_BitCount;
	brp_buf* PreSelSer = &_input_PreSelSer;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*BitCount));
	size_t _PreSelSer_len_val = 4;
	size_t* PreSelSer_len = &_PreSelSer_len_val;
	brp_frame_write(_frame, (brp_buf)(*PreSelSer), (*PreSelSer_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _Snr_len = 4;
	size_t* Snr_len = &_Snr_len;
	if (Snr != NULL) {
		(*Snr) = (brp_buf)brp_mempool_create_buf(mempool, (*Snr_len));
		if((*Snr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Snr), (*Snr_len));
	} else
		brp_frame_skip(&_reader, (*Snr_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_Select(brp_protocol protocol, brp_buf _input_Snr, unsigned* SAK) {
#else
brp_errcode brp_Mif_Select(brp_Mif_Select_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_Snr = params.Snr;
	unsigned* SAK = params.SAK;
#endif
	brp_buf* Snr = &_input_Snr;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_SAK;
	if (SAK == NULL) SAK = &_tmp_SAK;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	size_t _Snr_len_val = 4;
	size_t* Snr_len = &_Snr_len_val;
	brp_frame_write(_frame, (brp_buf)(*Snr), (*Snr_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*SAK) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_AuthE2(brp_protocol protocol, brp_Mif_AuthE2_AuthMode _input_AuthMode, unsigned _input_Block, unsigned _input_KeyIdx) {
#else
brp_errcode brp_Mif_AuthE2(brp_Mif_AuthE2_t params) {
	brp_protocol protocol = params.protocol;
	brp_Mif_AuthE2_AuthMode _input_AuthMode = params.AuthMode;
	unsigned _input_Block = params.Block;
	unsigned _input_KeyIdx = params.KeyIdx;
#endif
	brp_Mif_AuthE2_AuthMode* AuthMode = &_input_AuthMode;
	unsigned* Block = &_input_Block;
	unsigned* KeyIdx = &_input_KeyIdx;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	if (_input_AuthMode == 0) _input_AuthMode = (brp_Mif_AuthE2_AuthMode)96;
	brp_frame_write_int8(_frame, (unsigned)(*AuthMode));
	brp_frame_write_int8(_frame, (unsigned)(*Block));
	brp_frame_write_int8(_frame, (unsigned)(*KeyIdx));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_AuthUser(brp_protocol protocol, brp_Mif_AuthUser_AuthMode _input_AuthMode, unsigned _input_Block, brp_buf _input_Key) {
#else
brp_errcode brp_Mif_AuthUser(brp_Mif_AuthUser_t params) {
	brp_protocol protocol = params.protocol;
	brp_Mif_AuthUser_AuthMode _input_AuthMode = params.AuthMode;
	unsigned _input_Block = params.Block;
	brp_buf _input_Key = params.Key;
#endif
	brp_Mif_AuthUser_AuthMode* AuthMode = &_input_AuthMode;
	unsigned* Block = &_input_Block;
	brp_buf* Key = &_input_Key;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	if (_input_AuthMode == 0) _input_AuthMode = (brp_Mif_AuthUser_AuthMode)96;
	brp_frame_write_int8(_frame, (unsigned)(*AuthMode));
	brp_frame_write_int8(_frame, (unsigned)(*Block));
	size_t _Key_len_val = 6;
	size_t* Key_len = &_Key_len_val;
	brp_frame_write(_frame, (brp_buf)(*Key), (*Key_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_Read(brp_protocol protocol, unsigned _input_Block, brp_buf* BlockData, brp_mempool *mempool) {
#else
brp_errcode brp_Mif_Read(brp_Mif_Read_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Block = params.Block;
	brp_buf* BlockData = params.BlockData;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Block = &_input_Block;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Block));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _BlockData_len = 16;
	size_t* BlockData_len = &_BlockData_len;
	if (BlockData != NULL) {
		(*BlockData) = (brp_buf)brp_mempool_create_buf(mempool, (*BlockData_len));
		if((*BlockData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*BlockData), (*BlockData_len));
	} else
		brp_frame_skip(&_reader, (*BlockData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_Write(brp_protocol protocol, unsigned _input_Block, brp_buf _input_BlockData) {
#else
brp_errcode brp_Mif_Write(brp_Mif_Write_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Block = params.Block;
	brp_buf _input_BlockData = params.BlockData;
#endif
	unsigned* Block = &_input_Block;
	brp_buf* BlockData = &_input_BlockData;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Block));
	size_t _BlockData_len_val = 16;
	size_t* BlockData_len = &_BlockData_len_val;
	brp_frame_write(_frame, (brp_buf)(*BlockData), (*BlockData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ChangeValue(brp_protocol protocol, brp_Mif_ChangeValue_Mode _input_Mode, unsigned _input_Block, unsigned _input_Value) {
#else
brp_errcode brp_Mif_ChangeValue(brp_Mif_ChangeValue_t params) {
	brp_protocol protocol = params.protocol;
	brp_Mif_ChangeValue_Mode _input_Mode = params.Mode;
	unsigned _input_Block = params.Block;
	unsigned _input_Value = params.Value;
#endif
	brp_Mif_ChangeValue_Mode* Mode = &_input_Mode;
	unsigned* Block = &_input_Block;
	unsigned* Value = &_input_Value;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Mode));
	brp_frame_write_int8(_frame, (unsigned)(*Block));
	brp_frame_write_int32(_frame, (unsigned)(*Value));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ChangeValueBackup(brp_protocol protocol, brp_Mif_ChangeValueBackup_Mode _input_Mode, unsigned _input_Block, unsigned _input_Value) {
#else
brp_errcode brp_Mif_ChangeValueBackup(brp_Mif_ChangeValueBackup_t params) {
	brp_protocol protocol = params.protocol;
	brp_Mif_ChangeValueBackup_Mode _input_Mode = params.Mode;
	unsigned _input_Block = params.Block;
	unsigned _input_Value = params.Value;
#endif
	brp_Mif_ChangeValueBackup_Mode* Mode = &_input_Mode;
	unsigned* Block = &_input_Block;
	unsigned* Value = &_input_Value;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Mode));
	brp_frame_write_int8(_frame, (unsigned)(*Block));
	brp_frame_write_int32(_frame, (unsigned)(*Value));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_TransferBlock(brp_protocol protocol, unsigned _input_Block) {
#else
brp_errcode brp_Mif_TransferBlock(brp_Mif_TransferBlock_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Block = params.Block;
#endif
	unsigned* Block = &_input_Block;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Block));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_Halt(brp_protocol protocol) {
#else
brp_errcode brp_Mif_Halt(brp_Mif_Halt_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 11);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_AuthE2Extended(brp_protocol protocol, brp_Mif_AuthE2Extended_AuthLevel _input_AuthLevel, bool _input_KeyHasExtIdx, bool _input_EV1Mode, bool _input_IsKeyB, unsigned _input_Block, unsigned _input_KeyIdx, unsigned _input_KeyExtIdx, brp_buf _input_DivData, size_t _input_DivData_len) {
#else
brp_errcode brp_Mif_AuthE2Extended(brp_Mif_AuthE2Extended_t params) {
	brp_protocol protocol = params.protocol;
	brp_Mif_AuthE2Extended_AuthLevel _input_AuthLevel = params.AuthLevel;
	bool _input_KeyHasExtIdx = params.KeyHasExtIdx;
	bool _input_EV1Mode = params.EV1Mode;
	bool _input_IsKeyB = params.IsKeyB;
	unsigned _input_Block = params.Block;
	unsigned _input_KeyIdx = params.KeyIdx;
	unsigned _input_KeyExtIdx = params.KeyExtIdx;
	brp_buf _input_DivData = params.DivData;
	size_t _input_DivData_len = params.DivData_len;
#endif
	brp_Mif_AuthE2Extended_AuthLevel* AuthLevel = &_input_AuthLevel;
	bool* KeyHasExtIdx = &_input_KeyHasExtIdx;
	bool* EV1Mode = &_input_EV1Mode;
	bool* IsKeyB = &_input_IsKeyB;
	unsigned* Block = &_input_Block;
	unsigned* KeyIdx = &_input_KeyIdx;
	unsigned* KeyExtIdx = &_input_KeyExtIdx;
	brp_buf* DivData = &_input_DivData;
	size_t* DivData_len = &_input_DivData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int32(_frame, 100);
	if(!(*KeyHasExtIdx) && (*KeyExtIdx)) (*KeyHasExtIdx) = true;
	unsigned _bitmask_18f4 = 0;
	_bitmask_18f4 |= (*AuthLevel & 0b11) << 6;
	_bitmask_18f4 |= (*KeyHasExtIdx & 0b1) << 2;
	_bitmask_18f4 |= (*EV1Mode & 0b1) << 1;
	_bitmask_18f4 |= (*IsKeyB & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_18f4);
	brp_frame_write_int16(_frame, (unsigned)(*Block));
	brp_frame_write_int8(_frame, (unsigned)(*KeyIdx));
	if(*KeyHasExtIdx) {
		brp_frame_write_int8(_frame, (unsigned)(*KeyExtIdx));
	}
	brp_frame_write_int8(_frame, (unsigned)(*DivData_len));
	brp_frame_write(_frame, (brp_buf)(*DivData), (*DivData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_AuthUserExtended(brp_protocol protocol, brp_Mif_AuthUserExtended_AuthLevel _input_AuthLevel, bool _input_EV1Mode, bool _input_KeyB, unsigned _input_Block, brp_buf _input_Key, size_t _input_Key_len) {
#else
brp_errcode brp_Mif_AuthUserExtended(brp_Mif_AuthUserExtended_t params) {
	brp_protocol protocol = params.protocol;
	brp_Mif_AuthUserExtended_AuthLevel _input_AuthLevel = params.AuthLevel;
	bool _input_EV1Mode = params.EV1Mode;
	bool _input_KeyB = params.KeyB;
	unsigned _input_Block = params.Block;
	brp_buf _input_Key = params.Key;
	size_t _input_Key_len = params.Key_len;
#endif
	brp_Mif_AuthUserExtended_AuthLevel* AuthLevel = &_input_AuthLevel;
	bool* EV1Mode = &_input_EV1Mode;
	bool* KeyB = &_input_KeyB;
	unsigned* Block = &_input_Block;
	brp_buf* Key = &_input_Key;
	size_t* Key_len = &_input_Key_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 17);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_18f4 = 0;
	_bitmask_18f4 |= (*AuthLevel & 0b11) << 6;
	_bitmask_18f4 |= (*EV1Mode & 0b1) << 1;
	_bitmask_18f4 |= (*KeyB & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_18f4);
	brp_frame_write_int16(_frame, (unsigned)(*Block));
	brp_frame_write(_frame, (brp_buf)(*Key), (*Key_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ResetAuth(brp_protocol protocol) {
#else
brp_errcode brp_Mif_ResetAuth(brp_Mif_ResetAuth_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 18);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ReadSL3(brp_protocol protocol, bool _input_NoMacOnCmd, bool _input_PlainData, bool _input_NoMacOnResp, unsigned _input_Block, unsigned _input_BlockNr, brp_buf* BlockData, size_t* BlockData_len, brp_mempool *mempool) {
#else
brp_errcode brp_Mif_ReadSL3(brp_Mif_ReadSL3_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_NoMacOnCmd = params.NoMacOnCmd;
	bool _input_PlainData = params.PlainData;
	bool _input_NoMacOnResp = params.NoMacOnResp;
	unsigned _input_Block = params.Block;
	unsigned _input_BlockNr = params.BlockNr;
	brp_buf* BlockData = params.BlockData;
	size_t* BlockData_len = params.BlockData_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* NoMacOnCmd = &_input_NoMacOnCmd;
	bool* PlainData = &_input_PlainData;
	bool* NoMacOnResp = &_input_NoMacOnResp;
	unsigned* Block = &_input_Block;
	unsigned* BlockNr = &_input_BlockNr;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _BlockData_len;
	if(BlockData_len == NULL) BlockData_len = &_BlockData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_d2aa = 0;
	_bitmask_d2aa |= (*NoMacOnCmd & 0b1) << 2;
	_bitmask_d2aa |= (*PlainData & 0b1) << 1;
	_bitmask_d2aa |= (*NoMacOnResp & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_d2aa);
	brp_frame_write_int16(_frame, (unsigned)(*Block));
	brp_frame_write_int8(_frame, (unsigned)(*BlockNr));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*BlockData_len) = brp_frame_read_int16(&_reader);
	if (BlockData != NULL) {
		(*BlockData) = (brp_buf)brp_mempool_create_buf(mempool, (*BlockData_len));
		if((*BlockData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*BlockData), (*BlockData_len));
	} else
		brp_frame_skip(&_reader, (*BlockData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_WriteSL3(brp_protocol protocol, bool _input_PlainData, bool _input_NoMacOnResp, unsigned _input_Block, brp_buf _input_BlockData, size_t _input_BlockData_len) {
#else
brp_errcode brp_Mif_WriteSL3(brp_Mif_WriteSL3_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_PlainData = params.PlainData;
	bool _input_NoMacOnResp = params.NoMacOnResp;
	unsigned _input_Block = params.Block;
	brp_buf _input_BlockData = params.BlockData;
	size_t _input_BlockData_len = params.BlockData_len;
#endif
	bool* PlainData = &_input_PlainData;
	bool* NoMacOnResp = &_input_NoMacOnResp;
	unsigned* Block = &_input_Block;
	brp_buf* BlockData = &_input_BlockData;
	size_t* BlockData_len = &_input_BlockData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 20);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_3dfe = 0;
	_bitmask_3dfe |= (*PlainData & 0b1) << 1;
	_bitmask_3dfe |= (*NoMacOnResp & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_3dfe);
	brp_frame_write_int16(_frame, (unsigned)(*Block));
	brp_frame_write_int16(_frame, (unsigned)(*BlockData_len));
	brp_frame_write(_frame, (brp_buf)(*BlockData), (*BlockData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ChangeAESKey(brp_protocol protocol, bool _input_KeyHasExtIdx, bool _input_NoMacOnResp, unsigned _input_Block, unsigned _input_KeyIdx, unsigned _input_KeyExtIdx, brp_buf _input_DivData, size_t _input_DivData_len) {
#else
brp_errcode brp_Mif_ChangeAESKey(brp_Mif_ChangeAESKey_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_KeyHasExtIdx = params.KeyHasExtIdx;
	bool _input_NoMacOnResp = params.NoMacOnResp;
	unsigned _input_Block = params.Block;
	unsigned _input_KeyIdx = params.KeyIdx;
	unsigned _input_KeyExtIdx = params.KeyExtIdx;
	brp_buf _input_DivData = params.DivData;
	size_t _input_DivData_len = params.DivData_len;
#endif
	bool* KeyHasExtIdx = &_input_KeyHasExtIdx;
	bool* NoMacOnResp = &_input_NoMacOnResp;
	unsigned* Block = &_input_Block;
	unsigned* KeyIdx = &_input_KeyIdx;
	unsigned* KeyExtIdx = &_input_KeyExtIdx;
	brp_buf* DivData = &_input_DivData;
	size_t* DivData_len = &_input_DivData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 21);
	brp_frame_write_int32(_frame, 100);
	if(!(*KeyHasExtIdx) && (*KeyExtIdx)) (*KeyHasExtIdx) = true;
	unsigned _bitmask_b6ac = 0;
	_bitmask_b6ac |= (*KeyHasExtIdx & 0b1) << 3;
	_bitmask_b6ac |= (*NoMacOnResp & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_b6ac);
	brp_frame_write_int16(_frame, (unsigned)(*Block));
	brp_frame_write_int8(_frame, (unsigned)(*KeyIdx));
	if(*KeyHasExtIdx) {
		brp_frame_write_int8(_frame, (unsigned)(*KeyExtIdx));
	}
	brp_frame_write_int8(_frame, (unsigned)(*DivData_len));
	brp_frame_write(_frame, (brp_buf)(*DivData), (*DivData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ValueSL3(brp_protocol protocol, bool _input_NoMacOnResp, brp_Mif_ValueSL3_Cmd _input_Cmd, unsigned _input_Block, unsigned _input_DestBlock, unsigned _input_Value, brp_buf* TMCounterTMValue, size_t* TMCounterTMValue_len, brp_mempool *mempool) {
#else
brp_errcode brp_Mif_ValueSL3(brp_Mif_ValueSL3_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_NoMacOnResp = params.NoMacOnResp;
	brp_Mif_ValueSL3_Cmd _input_Cmd = params.Cmd;
	unsigned _input_Block = params.Block;
	unsigned _input_DestBlock = params.DestBlock;
	unsigned _input_Value = params.Value;
	brp_buf* TMCounterTMValue = params.TMCounterTMValue;
	size_t* TMCounterTMValue_len = params.TMCounterTMValue_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* NoMacOnResp = &_input_NoMacOnResp;
	brp_Mif_ValueSL3_Cmd* Cmd = &_input_Cmd;
	unsigned* Block = &_input_Block;
	unsigned* DestBlock = &_input_DestBlock;
	unsigned* Value = &_input_Value;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _TMCounterTMValue_len;
	if(TMCounterTMValue_len == NULL) TMCounterTMValue_len = &_TMCounterTMValue_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 22);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_864f = 0;
	_bitmask_864f |= (*NoMacOnResp & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_864f);
	brp_frame_write_int8(_frame, (unsigned)(*Cmd));
	brp_frame_write_int16(_frame, (unsigned)(*Block));
	if(((*Cmd) == (brp_Mif_ValueSL3_Cmd_IncrementTransfer)) || ((*Cmd) == (brp_Mif_ValueSL3_Cmd_DecrementTransfer))) {
		brp_frame_write_int16(_frame, (unsigned)(*DestBlock));
	}
	if(((((*Cmd) == (brp_Mif_ValueSL3_Cmd_Increment)) || ((*Cmd) == (brp_Mif_ValueSL3_Cmd_Decrement))) || ((*Cmd) == (brp_Mif_ValueSL3_Cmd_IncrementTransfer))) || ((*Cmd) == (brp_Mif_ValueSL3_Cmd_DecrementTransfer))) {
		brp_frame_write_int32(_frame, (unsigned)(*Value));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*TMCounterTMValue_len) = brp_frame_read_int8(&_reader);
	if (TMCounterTMValue != NULL) {
		(*TMCounterTMValue) = (brp_buf)brp_mempool_create_buf(mempool, (*TMCounterTMValue_len));
		if((*TMCounterTMValue) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*TMCounterTMValue), (*TMCounterTMValue_len));
	} else
		brp_frame_skip(&_reader, (*TMCounterTMValue_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ProxCheck(brp_protocol protocol, unsigned _input_M, bool _input_DisableIsoWrapping, bool _input_UseExtProxKey, bool _input_DiversifyProxKey, bool _input_UseProxKey, unsigned _input_ProxKeyIdx, brp_buf _input_DivData, size_t _input_DivData_len, brp_buf _input_ProxKey, size_t _input_ProxKey_len) {
#else
brp_errcode brp_Mif_ProxCheck(brp_Mif_ProxCheck_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_M = params.M;
	bool _input_DisableIsoWrapping = params.DisableIsoWrapping;
	bool _input_UseExtProxKey = params.UseExtProxKey;
	bool _input_DiversifyProxKey = params.DiversifyProxKey;
	bool _input_UseProxKey = params.UseProxKey;
	unsigned _input_ProxKeyIdx = params.ProxKeyIdx;
	brp_buf _input_DivData = params.DivData;
	size_t _input_DivData_len = params.DivData_len;
	brp_buf _input_ProxKey = params.ProxKey;
	size_t _input_ProxKey_len = params.ProxKey_len;
#endif
	unsigned* M = &_input_M;
	bool* DisableIsoWrapping = &_input_DisableIsoWrapping;
	bool* UseExtProxKey = &_input_UseExtProxKey;
	bool* DiversifyProxKey = &_input_DiversifyProxKey;
	bool* UseProxKey = &_input_UseProxKey;
	unsigned* ProxKeyIdx = &_input_ProxKeyIdx;
	brp_buf* DivData = &_input_DivData;
	size_t* DivData_len = &_input_DivData_len;
	brp_buf* ProxKey = &_input_ProxKey;
	size_t* ProxKey_len = &_input_ProxKey_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 23);
	brp_frame_write_int32(_frame, 100);
	if (_input_M == 0) _input_M = (unsigned)4;
	if(!(*UseProxKey) && (*ProxKeyIdx)) (*UseProxKey) = true;
	if(!(*UseExtProxKey) && (ProxKey)) (*UseExtProxKey) = true;
	unsigned _bitmask_08f2 = 0;
	_bitmask_08f2 |= (*M & 0b111) << 4;
	_bitmask_08f2 |= (*DisableIsoWrapping & 0b1) << 3;
	_bitmask_08f2 |= (*UseExtProxKey & 0b1) << 2;
	_bitmask_08f2 |= (*DiversifyProxKey & 0b1) << 1;
	_bitmask_08f2 |= (*UseProxKey & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_08f2);
	if(*UseProxKey) {
		brp_frame_write_int16(_frame, (unsigned)(*ProxKeyIdx));
	}
	if((*DiversifyProxKey) && (*UseProxKey)) {
		brp_frame_write_int8(_frame, (unsigned)(*DivData_len));
		brp_frame_write(_frame, (brp_buf)(*DivData), (*DivData_len));
	}
	if(*UseExtProxKey) {
		brp_frame_write_int8(_frame, (unsigned)(*ProxKey_len));
		brp_frame_write(_frame, (brp_buf)(*ProxKey), (*ProxKey_len));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_GetCardVersion(brp_protocol protocol, brp_buf* CardVersion, size_t* CardVersion_len, brp_mempool *mempool) {
#else
brp_errcode brp_Mif_GetCardVersion(brp_Mif_GetCardVersion_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* CardVersion = params.CardVersion;
	size_t* CardVersion_len = params.CardVersion_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _CardVersion_len;
	if(CardVersion_len == NULL) CardVersion_len = &_CardVersion_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 24);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*CardVersion_len) = brp_frame_read_int8(&_reader);
	if (CardVersion != NULL) {
		(*CardVersion) = (brp_buf)brp_mempool_create_buf(mempool, (*CardVersion_len));
		if((*CardVersion) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*CardVersion), (*CardVersion_len));
	} else
		brp_frame_skip(&_reader, (*CardVersion_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_ReadSig(brp_protocol protocol, brp_buf* NxpSignature, size_t* NxpSignature_len, brp_mempool *mempool) {
#else
brp_errcode brp_Mif_ReadSig(brp_Mif_ReadSig_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* NxpSignature = params.NxpSignature;
	size_t* NxpSignature_len = params.NxpSignature_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _NxpSignature_len;
	if(NxpSignature_len == NULL) NxpSignature_len = &_NxpSignature_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 25);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*NxpSignature_len) = brp_frame_read_int8(&_reader);
	if (NxpSignature != NULL) {
		(*NxpSignature) = (brp_buf)brp_mempool_create_buf(mempool, (*NxpSignature_len));
		if((*NxpSignature) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*NxpSignature), (*NxpSignature_len));
	} else
		brp_frame_skip(&_reader, (*NxpSignature_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_VirtualCardSelect(brp_protocol protocol, bool _input_ForceVcsAuthentication, bool _input_UseExtVcSelectKeys, unsigned _input_DiversifyMacKey, bool _input_DiversifyEncKey, bool _input_UseVcSelectKeys, brp_buf _input_IID, size_t _input_IID_len, unsigned _input_EncKeyIdx, unsigned _input_MacKeyIdx, brp_buf _input_DivData, size_t _input_DivData_len, brp_buf _input_EncKey, size_t _input_EncKey_len, brp_buf _input_MacKey, size_t _input_MacKey_len, brp_Mif_VirtualCardSelect_FciType* FciType, brp_buf* Fci, size_t* Fci_len, brp_mempool *mempool) {
#else
brp_errcode brp_Mif_VirtualCardSelect(brp_Mif_VirtualCardSelect_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_ForceVcsAuthentication = params.ForceVcsAuthentication;
	bool _input_UseExtVcSelectKeys = params.UseExtVcSelectKeys;
	unsigned _input_DiversifyMacKey = params.DiversifyMacKey;
	bool _input_DiversifyEncKey = params.DiversifyEncKey;
	bool _input_UseVcSelectKeys = params.UseVcSelectKeys;
	brp_buf _input_IID = params.IID;
	size_t _input_IID_len = params.IID_len;
	unsigned _input_EncKeyIdx = params.EncKeyIdx;
	unsigned _input_MacKeyIdx = params.MacKeyIdx;
	brp_buf _input_DivData = params.DivData;
	size_t _input_DivData_len = params.DivData_len;
	brp_buf _input_EncKey = params.EncKey;
	size_t _input_EncKey_len = params.EncKey_len;
	brp_buf _input_MacKey = params.MacKey;
	size_t _input_MacKey_len = params.MacKey_len;
	brp_Mif_VirtualCardSelect_FciType* FciType = params.FciType;
	brp_buf* Fci = params.Fci;
	size_t* Fci_len = params.Fci_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* ForceVcsAuthentication = &_input_ForceVcsAuthentication;
	bool* UseExtVcSelectKeys = &_input_UseExtVcSelectKeys;
	unsigned* DiversifyMacKey = &_input_DiversifyMacKey;
	bool* DiversifyEncKey = &_input_DiversifyEncKey;
	bool* UseVcSelectKeys = &_input_UseVcSelectKeys;
	brp_buf* IID = &_input_IID;
	size_t* IID_len = &_input_IID_len;
	unsigned* EncKeyIdx = &_input_EncKeyIdx;
	unsigned* MacKeyIdx = &_input_MacKeyIdx;
	brp_buf* DivData = &_input_DivData;
	size_t* DivData_len = &_input_DivData_len;
	brp_buf* EncKey = &_input_EncKey;
	size_t* EncKey_len = &_input_EncKey_len;
	brp_buf* MacKey = &_input_MacKey;
	size_t* MacKey_len = &_input_MacKey_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Fci_len;
	if(Fci_len == NULL) Fci_len = &_Fci_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 26);
	brp_frame_write_int32(_frame, 100);
	if(!(*UseVcSelectKeys) && (*EncKeyIdx || *MacKeyIdx)) (*UseVcSelectKeys) = true;
	if(!(*UseExtVcSelectKeys) && (EncKey || MacKey)) (*UseExtVcSelectKeys) = true;
	unsigned _bitmask_cf6a = 0;
	_bitmask_cf6a |= (*ForceVcsAuthentication & 0b1) << 5;
	_bitmask_cf6a |= (*UseExtVcSelectKeys & 0b1) << 4;
	_bitmask_cf6a |= (*DiversifyMacKey & 0b11) << 2;
	_bitmask_cf6a |= (*DiversifyEncKey & 0b1) << 1;
	_bitmask_cf6a |= (*UseVcSelectKeys & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_cf6a);
	brp_frame_write_int8(_frame, (unsigned)(*IID_len));
	brp_frame_write(_frame, (brp_buf)(*IID), (*IID_len));
	if(*UseVcSelectKeys) {
		brp_frame_write_int16(_frame, (unsigned)(*EncKeyIdx));
		brp_frame_write_int16(_frame, (unsigned)(*MacKeyIdx));
	}
	if(((((*DiversifyMacKey) == (1)) || ((*DiversifyMacKey) == (2))) || ((*DiversifyMacKey) == (3))) || (*DiversifyEncKey)) {
		brp_frame_write_int8(_frame, (unsigned)(*DivData_len));
		brp_frame_write(_frame, (brp_buf)(*DivData), (*DivData_len));
	}
	if(*UseExtVcSelectKeys) {
		brp_frame_write_int8(_frame, (unsigned)(*EncKey_len));
		brp_frame_write(_frame, (brp_buf)(*EncKey), (*EncKey_len));
		brp_frame_write_int8(_frame, (unsigned)(*MacKey_len));
		brp_frame_write(_frame, (brp_buf)(*MacKey), (*MacKey_len));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	int _FciType_int_val = brp_frame_read_int8(&_reader);
	if (! brp_Mif_VirtualCardSelect_FciType_is_valid(_FciType_int_val))
		return BRP_ERR_PAYLOAD_FORMAT;
	if (FciType != NULL)
		(*FciType) = (brp_Mif_VirtualCardSelect_FciType)_FciType_int_val;
	(*Fci_len) = brp_frame_read_int8(&_reader);
	if (Fci != NULL) {
		(*Fci) = (brp_buf)brp_mempool_create_buf(mempool, (*Fci_len));
		if((*Fci) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Fci), (*Fci_len));
	} else
		brp_frame_skip(&_reader, (*Fci_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_SectorSwitch(brp_protocol protocol, bool _input_L3SectorSwitch, unsigned _input_SectorSwitchKeyIdx, brp_buf _input_SectorSwitchKeyDivData, size_t _input_SectorSwitchKeyDivData_len, brp_Mif_SectorSwitch_SectorSpec_Entry* _input_SectorSpec, size_t _input_SectorSpec_len, brp_buf _input_SectorKeysDivData, size_t _input_SectorKeysDivData_len) {
#else
brp_errcode brp_Mif_SectorSwitch(brp_Mif_SectorSwitch_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_L3SectorSwitch = params.L3SectorSwitch;
	unsigned _input_SectorSwitchKeyIdx = params.SectorSwitchKeyIdx;
	brp_buf _input_SectorSwitchKeyDivData = params.SectorSwitchKeyDivData;
	size_t _input_SectorSwitchKeyDivData_len = params.SectorSwitchKeyDivData_len;
	brp_Mif_SectorSwitch_SectorSpec_Entry* _input_SectorSpec = params.SectorSpec;
	size_t _input_SectorSpec_len = params.SectorSpec_len;
	brp_buf _input_SectorKeysDivData = params.SectorKeysDivData;
	size_t _input_SectorKeysDivData_len = params.SectorKeysDivData_len;
#endif
	bool* L3SectorSwitch = &_input_L3SectorSwitch;
	unsigned* SectorSwitchKeyIdx = &_input_SectorSwitchKeyIdx;
	brp_buf* SectorSwitchKeyDivData = &_input_SectorSwitchKeyDivData;
	size_t* SectorSwitchKeyDivData_len = &_input_SectorSwitchKeyDivData_len;
	brp_Mif_SectorSwitch_SectorSpec_Entry** SectorSpec = &_input_SectorSpec;
	size_t* SectorSpec_len = &_input_SectorSpec_len;
	brp_buf* SectorKeysDivData = &_input_SectorKeysDivData;
	size_t* SectorKeysDivData_len = &_input_SectorKeysDivData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_ea84 = 0;
	_bitmask_ea84 |= (*L3SectorSwitch & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_ea84);
	brp_frame_write_int16(_frame, (unsigned)(*SectorSwitchKeyIdx));
	brp_frame_write_int8(_frame, (unsigned)(*SectorSwitchKeyDivData_len));
	brp_frame_write(_frame, (brp_buf)(*SectorSwitchKeyDivData), (*SectorSwitchKeyDivData_len));
	brp_frame_write_int8(_frame, (unsigned)(*SectorSpec_len));
	for(size_t _SectorSpec_ndx = 0;_SectorSpec_ndx < (*SectorSpec_len);_SectorSpec_ndx++) {
		brp_Mif_SectorSwitch_SectorSpec_Entry _SectorSpec_Entry = (*SectorSpec)[_SectorSpec_ndx];
		brp_Mif_SectorSwitch_SectorSpec_Entry* SectorSpec_Entry = &_SectorSpec_Entry;
		unsigned _BlockAddress = (SectorSpec_Entry)->BlockAddress;
		unsigned* BlockAddress = &_BlockAddress;
		unsigned _SectorKeyIdx = (SectorSpec_Entry)->SectorKeyIdx;
		unsigned* SectorKeyIdx = &_SectorKeyIdx;
		brp_frame_write_int16(_frame, (unsigned)(*BlockAddress));
		brp_frame_write_int16(_frame, (unsigned)(*SectorKeyIdx));
	}
	brp_frame_write_int8(_frame, (unsigned)(*SectorKeysDivData_len));
	brp_frame_write(_frame, (brp_buf)(*SectorKeysDivData), (*SectorKeysDivData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_CommitReaderID(brp_protocol protocol, unsigned _input_Block, brp_buf* EncTRI, size_t* EncTRI_len, brp_mempool *mempool) {
#else
brp_errcode brp_Mif_CommitReaderID(brp_Mif_CommitReaderID_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Block = params.Block;
	brp_buf* EncTRI = params.EncTRI;
	size_t* EncTRI_len = params.EncTRI_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Block = &_input_Block;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _EncTRI_len;
	if(EncTRI_len == NULL) EncTRI_len = &_EncTRI_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 29);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*Block));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*EncTRI_len) = brp_frame_read_int8(&_reader);
	if (EncTRI != NULL) {
		(*EncTRI) = (brp_buf)brp_mempool_create_buf(mempool, (*EncTRI_len));
		if((*EncTRI) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*EncTRI), (*EncTRI_len));
	} else
		brp_frame_skip(&_reader, (*EncTRI_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Mif_SetFraming(brp_protocol protocol, brp_Mif_SetFraming_CommMode _input_CommMode) {
#else
brp_errcode brp_Mif_SetFraming(brp_Mif_SetFraming_t params) {
	brp_protocol protocol = params.protocol;
	brp_Mif_SetFraming_CommMode _input_CommMode = params.CommMode;
#endif
	brp_Mif_SetFraming_CommMode* CommMode = &_input_CommMode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int8(_frame, 28);
	brp_frame_write_int32(_frame, 100);
	if (_input_CommMode == 0) _input_CommMode = (brp_Mif_SetFraming_CommMode)1;
	brp_frame_write_int8(_frame, (unsigned)(*CommMode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_MobileId_Enable(brp_protocol protocol, brp_MobileId_Enable_Mode _input_Mode) {
#else
brp_errcode brp_MobileId_Enable(brp_MobileId_Enable_t params) {
	brp_protocol protocol = params.protocol;
	brp_MobileId_Enable_Mode _input_Mode = params.Mode;
#endif
	brp_MobileId_Enable_Mode* Mode = &_input_Mode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 76);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Mode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_MobileId_GetVirtualCredentialId(brp_protocol protocol, brp_buf* CredentialId, size_t* CredentialId_len, brp_mempool *mempool) {
#else
brp_errcode brp_MobileId_GetVirtualCredentialId(brp_MobileId_GetVirtualCredentialId_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* CredentialId = params.CredentialId;
	size_t* CredentialId_len = params.CredentialId_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _CredentialId_len;
	if(CredentialId_len == NULL) CredentialId_len = &_CredentialId_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 76);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*CredentialId_len) = brp_frame_read_int8(&_reader);
	if (CredentialId != NULL) {
		(*CredentialId) = (brp_buf)brp_mempool_create_buf(mempool, (*CredentialId_len));
		if((*CredentialId) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*CredentialId), (*CredentialId_len));
	} else
		brp_frame_skip(&_reader, (*CredentialId_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_SetHfMode(brp_protocol protocol, unsigned _input_HfMode) {
#else
brp_errcode brp_Pico_SetHfMode(brp_Pico_SetHfMode_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_HfMode = params.HfMode;
#endif
	unsigned* HfMode = &_input_HfMode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 26);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*HfMode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_RequestAnticoll(brp_protocol protocol, brp_buf* ASNB, size_t* ASNB_len, brp_mempool *mempool) {
#else
brp_errcode brp_Pico_RequestAnticoll(brp_Pico_RequestAnticoll_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* ASNB = params.ASNB;
	size_t* ASNB_len = params.ASNB_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ASNB_len;
	if(ASNB_len == NULL) ASNB_len = &_ASNB_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 26);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ASNB_len) = brp_frame_read_int8(&_reader);
	if (ASNB != NULL) {
		(*ASNB) = (brp_buf)brp_mempool_create_buf(mempool, (*ASNB_len));
		if((*ASNB) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ASNB), (*ASNB_len));
	} else
		brp_frame_skip(&_reader, (*ASNB_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_Select(brp_protocol protocol, brp_buf _input_ASNB, size_t _input_ASNB_len, brp_buf* Serial, size_t* Serial_len, brp_mempool *mempool) {
#else
brp_errcode brp_Pico_Select(brp_Pico_Select_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_ASNB = params.ASNB;
	size_t _input_ASNB_len = params.ASNB_len;
	brp_buf* Serial = params.Serial;
	size_t* Serial_len = params.Serial_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* ASNB = &_input_ASNB;
	size_t* ASNB_len = &_input_ASNB_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Serial_len;
	if(Serial_len == NULL) Serial_len = &_Serial_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 26);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*ASNB_len));
	brp_frame_write(_frame, (brp_buf)(*ASNB), (*ASNB_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Serial_len) = brp_frame_read_int8(&_reader);
	if (Serial != NULL) {
		(*Serial) = (brp_buf)brp_mempool_create_buf(mempool, (*Serial_len));
		if((*Serial) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Serial), (*Serial_len));
	} else
		brp_frame_skip(&_reader, (*Serial_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_Halt(brp_protocol protocol) {
#else
brp_errcode brp_Pico_Halt(brp_Pico_Halt_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 26);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_SelectBookPage(brp_protocol protocol, unsigned _input_Book, unsigned _input_Page, brp_buf* Page1, size_t* Page1_len, brp_mempool *mempool) {
#else
brp_errcode brp_Pico_SelectBookPage(brp_Pico_SelectBookPage_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Book = params.Book;
	unsigned _input_Page = params.Page;
	brp_buf* Page1 = params.Page1;
	size_t* Page1_len = params.Page1_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Book = &_input_Book;
	unsigned* Page = &_input_Page;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Page1_len;
	if(Page1_len == NULL) Page1_len = &_Page1_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 26);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Book));
	brp_frame_write_int8(_frame, (unsigned)(*Page));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Page1_len) = brp_frame_read_int8(&_reader);
	if (Page1 != NULL) {
		(*Page1) = (brp_buf)brp_mempool_create_buf(mempool, (*Page1_len));
		if((*Page1) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Page1), (*Page1_len));
	} else
		brp_frame_skip(&_reader, (*Page1_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_Authenticate(brp_protocol protocol, bool _input_IsDebitKey, unsigned _input_KeyIdx) {
#else
brp_errcode brp_Pico_Authenticate(brp_Pico_Authenticate_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_IsDebitKey = params.IsDebitKey;
	unsigned _input_KeyIdx = params.KeyIdx;
#endif
	bool* IsDebitKey = &_input_IsDebitKey;
	unsigned* KeyIdx = &_input_KeyIdx;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 26);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*IsDebitKey));
	brp_frame_write_int16(_frame, (unsigned)(*KeyIdx));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_Read(brp_protocol protocol, unsigned _input_PageAdr, unsigned _input_PageNr, brp_buf* PageData, size_t* PageData_len, brp_mempool *mempool) {
#else
brp_errcode brp_Pico_Read(brp_Pico_Read_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_PageAdr = params.PageAdr;
	unsigned _input_PageNr = params.PageNr;
	brp_buf* PageData = params.PageData;
	size_t* PageData_len = params.PageData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* PageAdr = &_input_PageAdr;
	unsigned* PageNr = &_input_PageNr;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _PageData_len;
	if(PageData_len == NULL) PageData_len = &_PageData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 26);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*PageAdr));
	brp_frame_write_int8(_frame, (unsigned)(*PageNr));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*PageData_len) = brp_frame_read_int8(&_reader);
	if (PageData != NULL) {
		(*PageData) = (brp_buf)brp_mempool_create_buf(mempool, (*PageData_len));
		if((*PageData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*PageData), (*PageData_len));
	} else
		brp_frame_skip(&_reader, (*PageData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pico_Write(brp_protocol protocol, unsigned _input_PageAdr, brp_buf _input_PageData, size_t _input_PageData_len) {
#else
brp_errcode brp_Pico_Write(brp_Pico_Write_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_PageAdr = params.PageAdr;
	brp_buf _input_PageData = params.PageData;
	size_t _input_PageData_len = params.PageData_len;
#endif
	unsigned* PageAdr = &_input_PageAdr;
	brp_buf* PageData = &_input_PageData;
	size_t* PageData_len = &_input_PageData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 26);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*PageAdr));
	brp_frame_write_int8(_frame, (unsigned)(*PageData_len));
	brp_frame_write(_frame, (brp_buf)(*PageData), (*PageData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pki_PfsGenKey(brp_protocol protocol, brp_buf _input_TmpHostPubKey, size_t _input_TmpHostPubKey_len, brp_buf* TmpRdrPubKey, size_t* TmpRdrPubKey_len, brp_mempool *mempool) {
#else
brp_errcode brp_Pki_PfsGenKey(brp_Pki_PfsGenKey_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_TmpHostPubKey = params.TmpHostPubKey;
	size_t _input_TmpHostPubKey_len = params.TmpHostPubKey_len;
	brp_buf* TmpRdrPubKey = params.TmpRdrPubKey;
	size_t* TmpRdrPubKey_len = params.TmpRdrPubKey_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* TmpHostPubKey = &_input_TmpHostPubKey;
	size_t* TmpHostPubKey_len = &_input_TmpHostPubKey_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _TmpRdrPubKey_len;
	if(TmpRdrPubKey_len == NULL) TmpRdrPubKey_len = &_TmpRdrPubKey_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 16000);
	brp_frame_write_int16(_frame, (unsigned)(*TmpHostPubKey_len));
	brp_frame_write(_frame, (brp_buf)(*TmpHostPubKey), (*TmpHostPubKey_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*TmpRdrPubKey_len) = brp_frame_read_int16(&_reader);
	if (TmpRdrPubKey != NULL) {
		(*TmpRdrPubKey) = (brp_buf)brp_mempool_create_buf(mempool, (*TmpRdrPubKey_len));
		if((*TmpRdrPubKey) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*TmpRdrPubKey), (*TmpRdrPubKey_len));
	} else
		brp_frame_skip(&_reader, (*TmpRdrPubKey_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pki_PfsAuthHostCert(brp_protocol protocol, brp_buf _input_EncryptedPayload, size_t _input_EncryptedPayload_len) {
#else
brp_errcode brp_Pki_PfsAuthHostCert(brp_Pki_PfsAuthHostCert_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_EncryptedPayload = params.EncryptedPayload;
	size_t _input_EncryptedPayload_len = params.EncryptedPayload_len;
#endif
	brp_buf* EncryptedPayload = &_input_EncryptedPayload;
	size_t* EncryptedPayload_len = &_input_EncryptedPayload_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 16000);
	brp_frame_write_int16(_frame, (unsigned)(*EncryptedPayload_len));
	brp_frame_write(_frame, (brp_buf)(*EncryptedPayload), (*EncryptedPayload_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pki_PfsAuthRdrCert(brp_protocol protocol, brp_buf* EncryptedResponse, size_t* EncryptedResponse_len, brp_mempool *mempool) {
#else
brp_errcode brp_Pki_PfsAuthRdrCert(brp_Pki_PfsAuthRdrCert_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* EncryptedResponse = params.EncryptedResponse;
	size_t* EncryptedResponse_len = params.EncryptedResponse_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _EncryptedResponse_len;
	if(EncryptedResponse_len == NULL) EncryptedResponse_len = &_EncryptedResponse_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 16000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*EncryptedResponse_len) = brp_frame_read_int16(&_reader);
	if (EncryptedResponse != NULL) {
		(*EncryptedResponse) = (brp_buf)brp_mempool_create_buf(mempool, (*EncryptedResponse_len));
		if((*EncryptedResponse) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*EncryptedResponse), (*EncryptedResponse_len));
	} else
		brp_frame_skip(&_reader, (*EncryptedResponse_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pki_Tunnel2(brp_protocol protocol, unsigned _input_SequenceCounter, brp_buf _input_CmdHMAC, brp_buf _input_EncryptedCmd, size_t _input_EncryptedCmd_len, brp_buf* RspHMAC, brp_buf* EncryptedRsp, size_t* EncryptedRsp_len, brp_mempool *mempool) {
#else
brp_errcode brp_Pki_Tunnel2(brp_Pki_Tunnel2_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_SequenceCounter = params.SequenceCounter;
	brp_buf _input_CmdHMAC = params.CmdHMAC;
	brp_buf _input_EncryptedCmd = params.EncryptedCmd;
	size_t _input_EncryptedCmd_len = params.EncryptedCmd_len;
	brp_buf* RspHMAC = params.RspHMAC;
	brp_buf* EncryptedRsp = params.EncryptedRsp;
	size_t* EncryptedRsp_len = params.EncryptedRsp_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* SequenceCounter = &_input_SequenceCounter;
	brp_buf* CmdHMAC = &_input_CmdHMAC;
	brp_buf* EncryptedCmd = &_input_EncryptedCmd;
	size_t* EncryptedCmd_len = &_input_EncryptedCmd_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _EncryptedRsp_len;
	if(EncryptedRsp_len == NULL) EncryptedRsp_len = &_EncryptedRsp_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*SequenceCounter));
	size_t _CmdHMAC_len_val = 16;
	size_t* CmdHMAC_len = &_CmdHMAC_len_val;
	brp_frame_write(_frame, (brp_buf)(*CmdHMAC), (*CmdHMAC_len));
	brp_frame_write_int16(_frame, (unsigned)(*EncryptedCmd_len));
	brp_frame_write(_frame, (brp_buf)(*EncryptedCmd), (*EncryptedCmd_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _RspHMAC_len = 16;
	size_t* RspHMAC_len = &_RspHMAC_len;
	if (RspHMAC != NULL) {
		(*RspHMAC) = (brp_buf)brp_mempool_create_buf(mempool, (*RspHMAC_len));
		if((*RspHMAC) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*RspHMAC), (*RspHMAC_len));
	} else
		brp_frame_skip(&_reader, (*RspHMAC_len));
	(*EncryptedRsp_len) = brp_frame_read_int16(&_reader);
	if (EncryptedRsp != NULL) {
		(*EncryptedRsp) = (brp_buf)brp_mempool_create_buf(mempool, (*EncryptedRsp_len));
		if((*EncryptedRsp) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*EncryptedRsp), (*EncryptedRsp_len));
	} else
		brp_frame_skip(&_reader, (*EncryptedRsp_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pki_GetX509Csr(brp_protocol protocol, brp_buf* Csr, size_t* Csr_len, brp_mempool *mempool) {
#else
brp_errcode brp_Pki_GetX509Csr(brp_Pki_GetX509Csr_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Csr = params.Csr;
	size_t* Csr_len = params.Csr_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Csr_len;
	if(Csr_len == NULL) Csr_len = &_Csr_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int32(_frame, 16000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Csr_len) = brp_frame_read_int16(&_reader);
	if (Csr != NULL) {
		(*Csr) = (brp_buf)brp_mempool_create_buf(mempool, (*Csr_len));
		if((*Csr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Csr), (*Csr_len));
	} else
		brp_frame_skip(&_reader, (*Csr_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pki_StoreX509Cert(brp_protocol protocol, unsigned _input_SecLevel, brp_buf _input_Cert, size_t _input_Cert_len) {
#else
brp_errcode brp_Pki_StoreX509Cert(brp_Pki_StoreX509Cert_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_SecLevel = params.SecLevel;
	brp_buf _input_Cert = params.Cert;
	size_t _input_Cert_len = params.Cert_len;
#endif
	unsigned* SecLevel = &_input_SecLevel;
	brp_buf* Cert = &_input_Cert;
	size_t* Cert_len = &_input_Cert_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int8(_frame, 17);
	brp_frame_write_int32(_frame, 16000);
	brp_frame_write_int8(_frame, (unsigned)(*SecLevel));
	brp_frame_write_int16(_frame, (unsigned)(*Cert_len));
	brp_frame_write(_frame, (brp_buf)(*Cert), (*Cert_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Pki_StoreX509RootCert(brp_protocol protocol, unsigned _input_SecLevel, brp_buf _input_Cert, size_t _input_Cert_len) {
#else
brp_errcode brp_Pki_StoreX509RootCert(brp_Pki_StoreX509RootCert_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_SecLevel = params.SecLevel;
	brp_buf _input_Cert = params.Cert;
	size_t _input_Cert_len = params.Cert_len;
#endif
	unsigned* SecLevel = &_input_SecLevel;
	brp_buf* Cert = &_input_Cert;
	size_t* Cert_len = &_input_Cert_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int8(_frame, 18);
	brp_frame_write_int32(_frame, 16000);
	brp_frame_write_int8(_frame, (unsigned)(*SecLevel));
	brp_frame_write_int16(_frame, (unsigned)(*Cert_len));
	brp_frame_write(_frame, (brp_buf)(*Cert), (*Cert_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_QKey_Read(brp_protocol protocol, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_QKey_Read(brp_QKey_Read_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 53);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Rtc_GetTime(brp_protocol protocol, unsigned _input_ClockId, unsigned* Now) {
#else
brp_errcode brp_Rtc_GetTime(brp_Rtc_GetTime_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_ClockId = params.ClockId;
	unsigned* Now = params.Now;
#endif
	unsigned* ClockId = &_input_ClockId;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_Now;
	if (Now == NULL) Now = &_tmp_Now;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*ClockId));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Now) = (unsigned)brp_frame_read_int32(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Rtc_SetTime(brp_protocol protocol, unsigned _input_ClockId, unsigned _input_Now) {
#else
brp_errcode brp_Rtc_SetTime(brp_Rtc_SetTime_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_ClockId = params.ClockId;
	unsigned _input_Now = params.Now;
#endif
	unsigned* ClockId = &_input_ClockId;
	unsigned* Now = &_input_Now;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*ClockId));
	brp_frame_write_int32(_frame, (unsigned)(*Now));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_GetAcMask(brp_protocol protocol, unsigned _input_SecLevel, brp_HostSecurityAccessConditionBits* AcMask) {
#else
brp_errcode brp_Sec_GetAcMask(brp_Sec_GetAcMask_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_SecLevel = params.SecLevel;
	brp_HostSecurityAccessConditionBits* AcMask = params.AcMask;
#endif
	unsigned* SecLevel = &_input_SecLevel;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*SecLevel));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	unsigned _AcMask_int = brp_frame_read_int32(&_reader);
	if(AcMask != NULL) {
		(AcMask->HostToHostAccess) = (_AcMask_int>>28) & 0b1;
		(AcMask->AutoreadAccess) = (_AcMask_int>>27) & 0b1;
		(AcMask->CryptoAccess) = (_AcMask_int>>26) & 0b1;
		(AcMask->Bf2Upload) = (_AcMask_int>>25) & 0b1;
		(AcMask->ExtendedAccess) = (_AcMask_int>>24) & 0b1;
		(AcMask->FlashFileSystemWrite) = (_AcMask_int>>23) & 0b1;
		(AcMask->FlashFileSystemRead) = (_AcMask_int>>22) & 0b1;
		(AcMask->RtcWrite) = (_AcMask_int>>21) & 0b1;
		(AcMask->VhlExchangeapdu) = (_AcMask_int>>20) & 0b1;
		(AcMask->VhlFormat) = (_AcMask_int>>19) & 0b1;
		(AcMask->VhlWrite) = (_AcMask_int>>18) & 0b1;
		(AcMask->VhlRead) = (_AcMask_int>>17) & 0b1;
		(AcMask->VhlSelect) = (_AcMask_int>>16) & 0b1;
		(AcMask->ExtSamAccess) = (_AcMask_int>>15) & 0b1;
		(AcMask->HfLowlevelAccess) = (_AcMask_int>>14) & 0b1;
		(AcMask->GuiAccess) = (_AcMask_int>>13) & 0b1;
		(AcMask->IoPortWrite) = (_AcMask_int>>12) & 0b1;
		(AcMask->IoPortRead) = (_AcMask_int>>11) & 0b1;
		(AcMask->ConfigReset) = (_AcMask_int>>10) & 0b1;
		(AcMask->ConfigWrite) = (_AcMask_int>>9) & 0b1;
		(AcMask->ConfigRead) = (_AcMask_int>>8) & 0b1;
		(AcMask->SysReset) = (_AcMask_int>>7) & 0b1;
		(AcMask->SetAccessConditionMask2) = (_AcMask_int>>6) & 0b1;
		(AcMask->SetAccessConditionMask1) = (_AcMask_int>>5) & 0b1;
		(AcMask->SetAccessConditionMask0) = (_AcMask_int>>4) & 0b1;
		(AcMask->SetKey3) = (_AcMask_int>>3) & 0b1;
		(AcMask->SetKey2) = (_AcMask_int>>2) & 0b1;
		(AcMask->SetKey1) = (_AcMask_int>>1) & 0b1;
		(AcMask->FactoryReset) = (_AcMask_int>>0) & 0b1;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_SetAcMask(brp_protocol protocol, unsigned _input_SecLevel, brp_HostSecurityAccessConditionBits _input_AcMask) {
#else
brp_errcode brp_Sec_SetAcMask(brp_Sec_SetAcMask_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_SecLevel = params.SecLevel;
	brp_HostSecurityAccessConditionBits _input_AcMask = params.AcMask;
#endif
	unsigned* SecLevel = &_input_SecLevel;
	brp_HostSecurityAccessConditionBits* AcMask = &_input_AcMask;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 1000);
	brp_frame_write_int8(_frame, (unsigned)(*SecLevel));
	unsigned _AcMask_int = 0;
	_AcMask_int |= (AcMask->HostToHostAccess & 0b1) << 28;
	_AcMask_int |= (AcMask->AutoreadAccess & 0b1) << 27;
	_AcMask_int |= (AcMask->CryptoAccess & 0b1) << 26;
	_AcMask_int |= (AcMask->Bf2Upload & 0b1) << 25;
	_AcMask_int |= (AcMask->ExtendedAccess & 0b1) << 24;
	_AcMask_int |= (AcMask->FlashFileSystemWrite & 0b1) << 23;
	_AcMask_int |= (AcMask->FlashFileSystemRead & 0b1) << 22;
	_AcMask_int |= (AcMask->RtcWrite & 0b1) << 21;
	_AcMask_int |= (AcMask->VhlExchangeapdu & 0b1) << 20;
	_AcMask_int |= (AcMask->VhlFormat & 0b1) << 19;
	_AcMask_int |= (AcMask->VhlWrite & 0b1) << 18;
	_AcMask_int |= (AcMask->VhlRead & 0b1) << 17;
	_AcMask_int |= (AcMask->VhlSelect & 0b1) << 16;
	_AcMask_int |= (AcMask->ExtSamAccess & 0b1) << 15;
	_AcMask_int |= (AcMask->HfLowlevelAccess & 0b1) << 14;
	_AcMask_int |= (AcMask->GuiAccess & 0b1) << 13;
	_AcMask_int |= (AcMask->IoPortWrite & 0b1) << 12;
	_AcMask_int |= (AcMask->IoPortRead & 0b1) << 11;
	_AcMask_int |= (AcMask->ConfigReset & 0b1) << 10;
	_AcMask_int |= (AcMask->ConfigWrite & 0b1) << 9;
	_AcMask_int |= (AcMask->ConfigRead & 0b1) << 8;
	_AcMask_int |= (AcMask->SysReset & 0b1) << 7;
	_AcMask_int |= (AcMask->SetAccessConditionMask2 & 0b1) << 6;
	_AcMask_int |= (AcMask->SetAccessConditionMask1 & 0b1) << 5;
	_AcMask_int |= (AcMask->SetAccessConditionMask0 & 0b1) << 4;
	_AcMask_int |= (AcMask->SetKey3 & 0b1) << 3;
	_AcMask_int |= (AcMask->SetKey2 & 0b1) << 2;
	_AcMask_int |= (AcMask->SetKey1 & 0b1) << 1;
	_AcMask_int |= (AcMask->FactoryReset & 0b1) << 0;
	brp_frame_write_int32(_frame, (unsigned)_AcMask_int);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_SetKey(brp_protocol protocol, bool _input_ContinuousIV, bool _input_Encrypted, bool _input_MACed, bool _input_SessionKey, unsigned _input_DeriveKey, unsigned _input_SecLevel, brp_buf _input_Key) {
#else
brp_errcode brp_Sec_SetKey(brp_Sec_SetKey_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_ContinuousIV = params.ContinuousIV;
	bool _input_Encrypted = params.Encrypted;
	bool _input_MACed = params.MACed;
	bool _input_SessionKey = params.SessionKey;
	unsigned _input_DeriveKey = params.DeriveKey;
	unsigned _input_SecLevel = params.SecLevel;
	brp_buf _input_Key = params.Key;
#endif
	bool* ContinuousIV = &_input_ContinuousIV;
	bool* Encrypted = &_input_Encrypted;
	bool* MACed = &_input_MACed;
	bool* SessionKey = &_input_SessionKey;
	unsigned* DeriveKey = &_input_DeriveKey;
	unsigned* SecLevel = &_input_SecLevel;
	brp_buf* Key = &_input_Key;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 1000);
	unsigned _bitmask_c846 = 0;
	_bitmask_c846 |= (*ContinuousIV & 0b1) << 7;
	_bitmask_c846 |= (*Encrypted & 0b1) << 6;
	_bitmask_c846 |= (*MACed & 0b1) << 5;
	_bitmask_c846 |= (*SessionKey & 0b1) << 4;
	_bitmask_c846 |= (*DeriveKey & 0b11) << 2;
	_bitmask_c846 |= (*SecLevel & 0b11) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_c846);
	size_t _Key_len_val = 16;
	size_t* Key_len = &_Key_len_val;
	brp_frame_write(_frame, (brp_buf)(*Key), (*Key_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_AuthPhase1(brp_protocol protocol, unsigned _input_SecLevel, brp_buf _input_RndA, brp_buf* EncRndA, brp_buf* RndB, bool* ContinuousIV, bool* Encrypted, bool* MACed, bool* SessionKey, brp_mempool *mempool) {
#else
brp_errcode brp_Sec_AuthPhase1(brp_Sec_AuthPhase1_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_SecLevel = params.SecLevel;
	brp_buf _input_RndA = params.RndA;
	brp_buf* EncRndA = params.EncRndA;
	brp_buf* RndB = params.RndB;
	bool* ContinuousIV = params.ContinuousIV;
	bool* Encrypted = params.Encrypted;
	bool* MACed = params.MACed;
	bool* SessionKey = params.SessionKey;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* SecLevel = &_input_SecLevel;
	brp_buf* RndA = &_input_RndA;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	bool _tmp_ContinuousIV;
	if (ContinuousIV == NULL) ContinuousIV = &_tmp_ContinuousIV;
	bool _tmp_Encrypted;
	if (Encrypted == NULL) Encrypted = &_tmp_Encrypted;
	bool _tmp_MACed;
	if (MACed == NULL) MACed = &_tmp_MACed;
	bool _tmp_SessionKey;
	if (SessionKey == NULL) SessionKey = &_tmp_SessionKey;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*SecLevel));
	size_t _RndA_len_val = 16;
	size_t* RndA_len = &_RndA_len_val;
	brp_frame_write(_frame, (brp_buf)(*RndA), (*RndA_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _EncRndA_len = 16;
	size_t* EncRndA_len = &_EncRndA_len;
	if (EncRndA != NULL) {
		(*EncRndA) = (brp_buf)brp_mempool_create_buf(mempool, (*EncRndA_len));
		if((*EncRndA) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*EncRndA), (*EncRndA_len));
	} else
		brp_frame_skip(&_reader, (*EncRndA_len));
	size_t _RndB_len = 16;
	size_t* RndB_len = &_RndB_len;
	if (RndB != NULL) {
		(*RndB) = (brp_buf)brp_mempool_create_buf(mempool, (*RndB_len));
		if((*RndB) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*RndB), (*RndB_len));
	} else
		brp_frame_skip(&_reader, (*RndB_len));
	unsigned _bitmask_c846 = brp_frame_read_int8(&_reader);
	if(ContinuousIV != NULL)
		(*ContinuousIV) = (_bitmask_c846>>7) & 0b1;
	if(Encrypted != NULL)
		(*Encrypted) = (_bitmask_c846>>6) & 0b1;
	if(MACed != NULL)
		(*MACed) = (_bitmask_c846>>5) & 0b1;
	if(SessionKey != NULL)
		(*SessionKey) = (_bitmask_c846>>4) & 0b1;
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_AuthPhase2(brp_protocol protocol, brp_buf _input_EncRndB) {
#else
brp_errcode brp_Sec_AuthPhase2(brp_Sec_AuthPhase2_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_EncRndB = params.EncRndB;
#endif
	brp_buf* EncRndB = &_input_EncRndB;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	size_t _EncRndB_len_val = 16;
	size_t* EncRndB_len = &_EncRndB_len_val;
	brp_frame_write(_frame, (brp_buf)(*EncRndB), (*EncRndB_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_Tunnel(brp_protocol protocol, bool _input_ContinuousIV, bool _input_Encrypted, bool _input_MACed, bool _input_SessionKey, unsigned _input_SecLevel, brp_buf _input_TunnelledCmd, size_t _input_TunnelledCmd_len, brp_buf* TunnelledResp, size_t* TunnelledResp_len, brp_mempool *mempool) {
#else
brp_errcode brp_Sec_Tunnel(brp_Sec_Tunnel_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_ContinuousIV = params.ContinuousIV;
	bool _input_Encrypted = params.Encrypted;
	bool _input_MACed = params.MACed;
	bool _input_SessionKey = params.SessionKey;
	unsigned _input_SecLevel = params.SecLevel;
	brp_buf _input_TunnelledCmd = params.TunnelledCmd;
	size_t _input_TunnelledCmd_len = params.TunnelledCmd_len;
	brp_buf* TunnelledResp = params.TunnelledResp;
	size_t* TunnelledResp_len = params.TunnelledResp_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* ContinuousIV = &_input_ContinuousIV;
	bool* Encrypted = &_input_Encrypted;
	bool* MACed = &_input_MACed;
	bool* SessionKey = &_input_SessionKey;
	unsigned* SecLevel = &_input_SecLevel;
	brp_buf* TunnelledCmd = &_input_TunnelledCmd;
	size_t* TunnelledCmd_len = &_input_TunnelledCmd_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _TunnelledResp_len;
	if(TunnelledResp_len == NULL) TunnelledResp_len = &_TunnelledResp_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_c846 = 0;
	_bitmask_c846 |= (*ContinuousIV & 0b1) << 7;
	_bitmask_c846 |= (*Encrypted & 0b1) << 6;
	_bitmask_c846 |= (*MACed & 0b1) << 5;
	_bitmask_c846 |= (*SessionKey & 0b1) << 4;
	_bitmask_c846 |= (*SecLevel & 0b11) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_c846);
	brp_frame_write(_frame, (brp_buf)(*TunnelledCmd), (*TunnelledCmd_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*TunnelledResp_len) = brp_frame_rest( & _reader);
	if (TunnelledResp != NULL) {
		(*TunnelledResp) = (brp_buf)brp_mempool_create_buf(mempool, (*TunnelledResp_len));
		if((*TunnelledResp) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*TunnelledResp), (*TunnelledResp_len));
	} else
		brp_frame_skip(&_reader, (*TunnelledResp_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_Reset(brp_protocol protocol) {
#else
brp_errcode brp_Sec_Reset(brp_Sec_Reset_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int32(_frame, 10000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_LockReset(brp_protocol protocol, unsigned _input_SecLevel) {
#else
brp_errcode brp_Sec_LockReset(brp_Sec_LockReset_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_SecLevel = params.SecLevel;
#endif
	unsigned* SecLevel = &_input_SecLevel;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int32(_frame, 1000);
	brp_frame_write_int8(_frame, (unsigned)(*SecLevel));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sec_GetCurAcMask(brp_protocol protocol, brp_HostSecurityAccessConditionBits* AcMask) {
#else
brp_errcode brp_Sec_GetCurAcMask(brp_Sec_GetCurAcMask_t params) {
	brp_protocol protocol = params.protocol;
	brp_HostSecurityAccessConditionBits* AcMask = params.AcMask;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	unsigned _AcMask_int = brp_frame_read_int32(&_reader);
	if(AcMask != NULL) {
		(AcMask->HostToHostAccess) = (_AcMask_int>>28) & 0b1;
		(AcMask->AutoreadAccess) = (_AcMask_int>>27) & 0b1;
		(AcMask->CryptoAccess) = (_AcMask_int>>26) & 0b1;
		(AcMask->Bf2Upload) = (_AcMask_int>>25) & 0b1;
		(AcMask->ExtendedAccess) = (_AcMask_int>>24) & 0b1;
		(AcMask->FlashFileSystemWrite) = (_AcMask_int>>23) & 0b1;
		(AcMask->FlashFileSystemRead) = (_AcMask_int>>22) & 0b1;
		(AcMask->RtcWrite) = (_AcMask_int>>21) & 0b1;
		(AcMask->VhlExchangeapdu) = (_AcMask_int>>20) & 0b1;
		(AcMask->VhlFormat) = (_AcMask_int>>19) & 0b1;
		(AcMask->VhlWrite) = (_AcMask_int>>18) & 0b1;
		(AcMask->VhlRead) = (_AcMask_int>>17) & 0b1;
		(AcMask->VhlSelect) = (_AcMask_int>>16) & 0b1;
		(AcMask->ExtSamAccess) = (_AcMask_int>>15) & 0b1;
		(AcMask->HfLowlevelAccess) = (_AcMask_int>>14) & 0b1;
		(AcMask->GuiAccess) = (_AcMask_int>>13) & 0b1;
		(AcMask->IoPortWrite) = (_AcMask_int>>12) & 0b1;
		(AcMask->IoPortRead) = (_AcMask_int>>11) & 0b1;
		(AcMask->ConfigReset) = (_AcMask_int>>10) & 0b1;
		(AcMask->ConfigWrite) = (_AcMask_int>>9) & 0b1;
		(AcMask->ConfigRead) = (_AcMask_int>>8) & 0b1;
		(AcMask->SysReset) = (_AcMask_int>>7) & 0b1;
		(AcMask->SetAccessConditionMask2) = (_AcMask_int>>6) & 0b1;
		(AcMask->SetAccessConditionMask1) = (_AcMask_int>>5) & 0b1;
		(AcMask->SetAccessConditionMask0) = (_AcMask_int>>4) & 0b1;
		(AcMask->SetKey3) = (_AcMask_int>>3) & 0b1;
		(AcMask->SetKey2) = (_AcMask_int>>2) & 0b1;
		(AcMask->SetKey1) = (_AcMask_int>>1) & 0b1;
		(AcMask->FactoryReset) = (_AcMask_int>>0) & 0b1;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Srix_Select(brp_protocol protocol, brp_buf* Snr, size_t* Snr_len, brp_mempool *mempool) {
#else
brp_errcode brp_Srix_Select(brp_Srix_Select_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Snr = params.Snr;
	size_t* Snr_len = params.Snr_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Snr_len;
	if(Snr_len == NULL) Snr_len = &_Snr_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 36);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Snr_len) = brp_frame_read_int8(&_reader);
	if (Snr != NULL) {
		(*Snr) = (brp_buf)brp_mempool_create_buf(mempool, (*Snr_len));
		if((*Snr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Snr), (*Snr_len));
	} else
		brp_frame_skip(&_reader, (*Snr_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Srix_Read(brp_protocol protocol, unsigned _input_Adr, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_Srix_Read(brp_Srix_Read_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Adr = params.Adr;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Adr = &_input_Adr;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 36);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Adr));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Srix_Write(brp_protocol protocol, unsigned _input_Adr, brp_buf _input_Data, size_t _input_Data_len) {
#else
brp_errcode brp_Srix_Write(brp_Srix_Write_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Adr = params.Adr;
	brp_buf _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
#endif
	unsigned* Adr = &_input_Adr;
	brp_buf* Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 36);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Adr));
	brp_frame_write_int8(_frame, (unsigned)(*Data_len));
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetBufferSize(brp_protocol protocol, unsigned* MaxSendSize, unsigned* MaxRecvSize, unsigned* TotalSize) {
#else
brp_errcode brp_Sys_GetBufferSize(brp_Sys_GetBufferSize_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* MaxSendSize = params.MaxSendSize;
	unsigned* MaxRecvSize = params.MaxRecvSize;
	unsigned* TotalSize = params.TotalSize;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_MaxSendSize;
	if (MaxSendSize == NULL) MaxSendSize = &_tmp_MaxSendSize;
	unsigned _tmp_MaxRecvSize;
	if (MaxRecvSize == NULL) MaxRecvSize = &_tmp_MaxRecvSize;
	unsigned _tmp_TotalSize;
	if (TotalSize == NULL) TotalSize = &_tmp_TotalSize;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 50);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*MaxSendSize) = (unsigned)brp_frame_read_int16(&_reader);
	(*MaxRecvSize) = (unsigned)brp_frame_read_int16(&_reader);
	(*TotalSize) = (unsigned)brp_frame_read_int16(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_HFReset(brp_protocol protocol, unsigned _input_OffDuration) {
#else
brp_errcode brp_Sys_HFReset(brp_Sys_HFReset_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_OffDuration = params.OffDuration;
#endif
	unsigned* OffDuration = &_input_OffDuration;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 2000);
	brp_frame_write_int8(_frame, (unsigned)(*OffDuration));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_Reset(brp_protocol protocol) {
#else
brp_errcode brp_Sys_Reset(brp_Sys_Reset_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetInfo(brp_protocol protocol, char** Info, brp_mempool *mempool) {
#else
brp_errcode brp_Sys_GetInfo(brp_Sys_GetInfo_t params) {
	brp_protocol protocol = params.protocol;
	char** Info = params.Info;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _Info_len = 0;
	size_t* Info_len = &_Info_len;
	if (Info != NULL) {
		(*Info) = (char*)brp_mempool_create_buf(mempool, 0);
		if((*Info) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(char _char = brp_frame_read_int8(&_reader); !((_char == 0x00) | brp_frame_read_err(&_reader));_char = brp_frame_read_int8(&_reader)) {
		if(Info != NULL) {
			(*Info_len) += 1;
			(*Info) = (char*)brp_mempool_resize_buf((brp_buf)(*Info), (*Info_len));
			if((*Info) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			(*Info)[(*Info_len)-1] = _char;
		}
	}
	if(Info != NULL) {
		(*Info_len) += 1;
		(*Info) = (char*)brp_mempool_resize_buf((brp_buf)(*Info), (*Info_len));
		if((*Info) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		(*Info)[(*Info_len)-1] = 0;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetBootStatus(brp_protocol protocol, brp_Sys_GetBootStatus_BootStatus* BootStatus) {
#else
brp_errcode brp_Sys_GetBootStatus(brp_Sys_GetBootStatus_t params) {
	brp_protocol protocol = params.protocol;
	brp_Sys_GetBootStatus_BootStatus* BootStatus = params.BootStatus;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 50);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	unsigned _BootStatus_int = brp_frame_read_int32(&_reader);
	if(BootStatus != NULL) {
		(BootStatus->NewerReaderChipFirmware) = (_BootStatus_int>>31) & 0b1;
		(BootStatus->UnexpectedRebootsLegacy) = (_BootStatus_int>>30) & 0b1;
		(BootStatus->FactorySettings) = (_BootStatus_int>>29) & 0b1;
		(BootStatus->ConfigurationInconsistent) = (_BootStatus_int>>28) & 0b1;
		(BootStatus->FirmwareVersionBlocked) = (_BootStatus_int>>27) & 0b1;
		(BootStatus->Bluetooth) = (_BootStatus_int>>23) & 0b1;
		(BootStatus->WiFi) = (_BootStatus_int>>22) & 0b1;
		(BootStatus->Tamper) = (_BootStatus_int>>21) & 0b1;
		(BootStatus->BatteryManagement) = (_BootStatus_int>>20) & 0b1;
		(BootStatus->Keyboard) = (_BootStatus_int>>19) & 0b1;
		(BootStatus->FirmwareVersionBlockedLegacy) = (_BootStatus_int>>18) & 0b1;
		(BootStatus->Display) = (_BootStatus_int>>17) & 0b1;
		(BootStatus->ConfCardPresented) = (_BootStatus_int>>16) & 0b1;
		(BootStatus->Ethernet) = (_BootStatus_int>>15) & 0b1;
		(BootStatus->ExtendedLED) = (_BootStatus_int>>14) & 0b1;
		(BootStatus->Rf125kHz) = (_BootStatus_int>>12) & 0b1;
		(BootStatus->Rf13MHz) = (_BootStatus_int>>10) & 0b1;
		(BootStatus->Rf13MHzLegic) = (_BootStatus_int>>9) & 0b1;
		(BootStatus->Rf13MHzLegacy) = (_BootStatus_int>>8) & 0b1;
		(BootStatus->HWoptions) = (_BootStatus_int>>7) & 0b1;
		(BootStatus->RTC) = (_BootStatus_int>>5) & 0b1;
		(BootStatus->Dataflash) = (_BootStatus_int>>4) & 0b1;
		(BootStatus->Configuration) = (_BootStatus_int>>2) & 0b1;
		(BootStatus->CorruptFirmware) = (_BootStatus_int>>1) & 0b1;
		(BootStatus->IncompleteFirmware) = (_BootStatus_int>>0) & 0b1;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetPort(brp_protocol protocol, brp_IoPortBitmask* PortMask) {
#else
brp_errcode brp_Sys_GetPort(brp_Sys_GetPort_t params) {
	brp_protocol protocol = params.protocol;
	brp_IoPortBitmask* PortMask = params.PortMask;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	unsigned _PortMask_int = brp_frame_read_int16(&_reader);
	if(PortMask != NULL) {
		(PortMask->Gpio7) = (_PortMask_int>>15) & 0b1;
		(PortMask->Gpio6) = (_PortMask_int>>14) & 0b1;
		(PortMask->Gpio5) = (_PortMask_int>>13) & 0b1;
		(PortMask->Gpio4) = (_PortMask_int>>12) & 0b1;
		(PortMask->Gpio3) = (_PortMask_int>>11) & 0b1;
		(PortMask->Gpio2) = (_PortMask_int>>10) & 0b1;
		(PortMask->Gpio1) = (_PortMask_int>>9) & 0b1;
		(PortMask->Gpio0) = (_PortMask_int>>8) & 0b1;
		(PortMask->TamperAlarm) = (_PortMask_int>>7) & 0b1;
		(PortMask->BlueLed) = (_PortMask_int>>6) & 0b1;
		(PortMask->Input1) = (_PortMask_int>>5) & 0b1;
		(PortMask->Input0) = (_PortMask_int>>4) & 0b1;
		(PortMask->Relay) = (_PortMask_int>>3) & 0b1;
		(PortMask->Beeper) = (_PortMask_int>>2) & 0b1;
		(PortMask->RedLed) = (_PortMask_int>>1) & 0b1;
		(PortMask->GreenLed) = (_PortMask_int>>0) & 0b1;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_SetPort(brp_protocol protocol, brp_IoPortBitmask _input_PortMask) {
#else
brp_errcode brp_Sys_SetPort(brp_Sys_SetPort_t params) {
	brp_protocol protocol = params.protocol;
	brp_IoPortBitmask _input_PortMask = params.PortMask;
#endif
	brp_IoPortBitmask* PortMask = &_input_PortMask;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int32(_frame, 100);
	unsigned _PortMask_int = 0;
	_PortMask_int |= (PortMask->Gpio7 & 0b1) << 15;
	_PortMask_int |= (PortMask->Gpio6 & 0b1) << 14;
	_PortMask_int |= (PortMask->Gpio5 & 0b1) << 13;
	_PortMask_int |= (PortMask->Gpio4 & 0b1) << 12;
	_PortMask_int |= (PortMask->Gpio3 & 0b1) << 11;
	_PortMask_int |= (PortMask->Gpio2 & 0b1) << 10;
	_PortMask_int |= (PortMask->Gpio1 & 0b1) << 9;
	_PortMask_int |= (PortMask->Gpio0 & 0b1) << 8;
	_PortMask_int |= (PortMask->TamperAlarm & 0b1) << 7;
	_PortMask_int |= (PortMask->BlueLed & 0b1) << 6;
	_PortMask_int |= (PortMask->Input1 & 0b1) << 5;
	_PortMask_int |= (PortMask->Input0 & 0b1) << 4;
	_PortMask_int |= (PortMask->Relay & 0b1) << 3;
	_PortMask_int |= (PortMask->Beeper & 0b1) << 2;
	_PortMask_int |= (PortMask->RedLed & 0b1) << 1;
	_PortMask_int |= (PortMask->GreenLed & 0b1) << 0;
	brp_frame_write_int16(_frame, (unsigned)_PortMask_int);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgGetValue(brp_protocol protocol, unsigned _input_Key, unsigned _input_Value, brp_buf* Content, size_t* Content_len, brp_mempool *mempool) {
#else
brp_errcode brp_Sys_CfgGetValue(brp_Sys_CfgGetValue_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Key = params.Key;
	unsigned _input_Value = params.Value;
	brp_buf* Content = params.Content;
	size_t* Content_len = params.Content_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Key = &_input_Key;
	unsigned* Value = &_input_Value;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Content_len;
	if(Content_len == NULL) Content_len = &_Content_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*Key));
	brp_frame_write_int8(_frame, (unsigned)(*Value));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Content_len) = brp_frame_read_int8(&_reader);
	if (Content != NULL) {
		(*Content) = (brp_buf)brp_mempool_create_buf(mempool, (*Content_len));
		if((*Content) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Content), (*Content_len));
	} else
		brp_frame_skip(&_reader, (*Content_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgSetValue(brp_protocol protocol, unsigned _input_Key, unsigned _input_Value, brp_buf _input_Content, size_t _input_Content_len) {
#else
brp_errcode brp_Sys_CfgSetValue(brp_Sys_CfgSetValue_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Key = params.Key;
	unsigned _input_Value = params.Value;
	brp_buf _input_Content = params.Content;
	size_t _input_Content_len = params.Content_len;
#endif
	unsigned* Key = &_input_Key;
	unsigned* Value = &_input_Value;
	brp_buf* Content = &_input_Content;
	size_t* Content_len = &_input_Content_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int32(_frame, 10000);
	brp_frame_write_int16(_frame, (unsigned)(*Key));
	brp_frame_write_int8(_frame, (unsigned)(*Value));
	brp_frame_write_int8(_frame, (unsigned)(*Content_len));
	brp_frame_write(_frame, (brp_buf)(*Content), (*Content_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgDelValues(brp_protocol protocol, unsigned _input_Key, unsigned _input_Value) {
#else
brp_errcode brp_Sys_CfgDelValues(brp_Sys_CfgDelValues_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Key = params.Key;
	unsigned _input_Value = params.Value;
#endif
	unsigned* Key = &_input_Key;
	unsigned* Value = &_input_Value;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int32(_frame, 10000);
	brp_frame_write_int16(_frame, (unsigned)(*Key));
	brp_frame_write_int8(_frame, (unsigned)(*Value));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgGetKeyList(brp_protocol protocol, unsigned** KeyList, size_t* KeyList_len, brp_mempool *mempool) {
#else
brp_errcode brp_Sys_CfgGetKeyList(brp_Sys_CfgGetKeyList_t params) {
	brp_protocol protocol = params.protocol;
	unsigned** KeyList = params.KeyList;
	size_t* KeyList_len = params.KeyList_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _KeyList_len;
	if(KeyList_len == NULL) KeyList_len = &_KeyList_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 11);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*KeyList_len) = brp_frame_read_int8(&_reader);
	if (KeyList != NULL) {
		(*KeyList) = (unsigned*)brp_mempool_create_buf(mempool, (*KeyList_len) * sizeof(unsigned));
		if((*KeyList) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _KeyList_ndx = 0;(_KeyList_ndx < (*KeyList_len)) & !brp_frame_read_err(&_reader);_KeyList_ndx++) {
		unsigned _Key;
		unsigned *Key = &_Key;
		(*Key) = (unsigned)brp_frame_read_int16(&_reader);
		if (KeyList != NULL)
			(*KeyList)[_KeyList_ndx] = *Key;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgGetValueList(brp_protocol protocol, unsigned _input_Key, unsigned** ValueList, size_t* ValueList_len, brp_mempool *mempool) {
#else
brp_errcode brp_Sys_CfgGetValueList(brp_Sys_CfgGetValueList_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Key = params.Key;
	unsigned** ValueList = params.ValueList;
	size_t* ValueList_len = params.ValueList_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Key = &_input_Key;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ValueList_len;
	if(ValueList_len == NULL) ValueList_len = &_ValueList_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 12);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*Key));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ValueList_len) = brp_frame_read_int8(&_reader);
	if (ValueList != NULL) {
		(*ValueList) = (unsigned*)brp_mempool_create_buf(mempool, (*ValueList_len) * sizeof(unsigned));
		if((*ValueList) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _ValueList_ndx = 0;(_ValueList_ndx < (*ValueList_len)) & !brp_frame_read_err(&_reader);_ValueList_ndx++) {
		unsigned _Value;
		unsigned *Value = &_Value;
		(*Value) = (unsigned)brp_frame_read_int8(&_reader);
		if (ValueList != NULL)
			(*ValueList)[_ValueList_ndx] = *Value;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgWriteTlvSector(brp_protocol protocol, brp_buf _input_TlvBlock, size_t _input_TlvBlock_len) {
#else
brp_errcode brp_Sys_CfgWriteTlvSector(brp_Sys_CfgWriteTlvSector_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_TlvBlock = params.TlvBlock;
	size_t _input_TlvBlock_len = params.TlvBlock_len;
#endif
	brp_buf* TlvBlock = &_input_TlvBlock;
	size_t* TlvBlock_len = &_input_TlvBlock_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 13);
	brp_frame_write_int32(_frame, 10000);
	brp_frame_write(_frame, (brp_buf)(*TlvBlock), (*TlvBlock_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgCheck(brp_protocol protocol, unsigned* TotalSize, unsigned* FreeSize) {
#else
brp_errcode brp_Sys_CfgCheck(brp_Sys_CfgCheck_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* TotalSize = params.TotalSize;
	unsigned* FreeSize = params.FreeSize;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_TotalSize;
	if (TotalSize == NULL) TotalSize = &_tmp_TotalSize;
	unsigned _tmp_FreeSize;
	if (FreeSize == NULL) FreeSize = &_tmp_FreeSize;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*TotalSize) = (unsigned)brp_frame_read_int16(&_reader);
	(*FreeSize) = (unsigned)brp_frame_read_int16(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_ConfigPort(brp_protocol protocol, brp_IoPortBitmask _input_InpOutp, brp_IoPortBitmask _input_DefaultState) {
#else
brp_errcode brp_Sys_ConfigPort(brp_Sys_ConfigPort_t params) {
	brp_protocol protocol = params.protocol;
	brp_IoPortBitmask _input_InpOutp = params.InpOutp;
	brp_IoPortBitmask _input_DefaultState = params.DefaultState;
#endif
	brp_IoPortBitmask* InpOutp = &_input_InpOutp;
	brp_IoPortBitmask* DefaultState = &_input_DefaultState;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 14);
	brp_frame_write_int32(_frame, 100);
	unsigned _InpOutp_int = 0;
	_InpOutp_int |= (InpOutp->Gpio7 & 0b1) << 15;
	_InpOutp_int |= (InpOutp->Gpio6 & 0b1) << 14;
	_InpOutp_int |= (InpOutp->Gpio5 & 0b1) << 13;
	_InpOutp_int |= (InpOutp->Gpio4 & 0b1) << 12;
	_InpOutp_int |= (InpOutp->Gpio3 & 0b1) << 11;
	_InpOutp_int |= (InpOutp->Gpio2 & 0b1) << 10;
	_InpOutp_int |= (InpOutp->Gpio1 & 0b1) << 9;
	_InpOutp_int |= (InpOutp->Gpio0 & 0b1) << 8;
	_InpOutp_int |= (InpOutp->TamperAlarm & 0b1) << 7;
	_InpOutp_int |= (InpOutp->BlueLed & 0b1) << 6;
	_InpOutp_int |= (InpOutp->Input1 & 0b1) << 5;
	_InpOutp_int |= (InpOutp->Input0 & 0b1) << 4;
	_InpOutp_int |= (InpOutp->Relay & 0b1) << 3;
	_InpOutp_int |= (InpOutp->Beeper & 0b1) << 2;
	_InpOutp_int |= (InpOutp->RedLed & 0b1) << 1;
	_InpOutp_int |= (InpOutp->GreenLed & 0b1) << 0;
	brp_frame_write_int16(_frame, (unsigned)_InpOutp_int);
	unsigned _DefaultState_int = 0;
	_DefaultState_int |= (DefaultState->Gpio7 & 0b1) << 15;
	_DefaultState_int |= (DefaultState->Gpio6 & 0b1) << 14;
	_DefaultState_int |= (DefaultState->Gpio5 & 0b1) << 13;
	_DefaultState_int |= (DefaultState->Gpio4 & 0b1) << 12;
	_DefaultState_int |= (DefaultState->Gpio3 & 0b1) << 11;
	_DefaultState_int |= (DefaultState->Gpio2 & 0b1) << 10;
	_DefaultState_int |= (DefaultState->Gpio1 & 0b1) << 9;
	_DefaultState_int |= (DefaultState->Gpio0 & 0b1) << 8;
	_DefaultState_int |= (DefaultState->TamperAlarm & 0b1) << 7;
	_DefaultState_int |= (DefaultState->BlueLed & 0b1) << 6;
	_DefaultState_int |= (DefaultState->Input1 & 0b1) << 5;
	_DefaultState_int |= (DefaultState->Input0 & 0b1) << 4;
	_DefaultState_int |= (DefaultState->Relay & 0b1) << 3;
	_DefaultState_int |= (DefaultState->Beeper & 0b1) << 2;
	_DefaultState_int |= (DefaultState->RedLed & 0b1) << 1;
	_DefaultState_int |= (DefaultState->GreenLed & 0b1) << 0;
	brp_frame_write_int16(_frame, (unsigned)_DefaultState_int);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_SetRegister(brp_protocol protocol, bool _input_ResetRegister, brp_Sys_SetRegister_RegisterAssignments_Entry* _input_RegisterAssignments, size_t _input_RegisterAssignments_len) {
#else
brp_errcode brp_Sys_SetRegister(brp_Sys_SetRegister_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_ResetRegister = params.ResetRegister;
	brp_Sys_SetRegister_RegisterAssignments_Entry* _input_RegisterAssignments = params.RegisterAssignments;
	size_t _input_RegisterAssignments_len = params.RegisterAssignments_len;
#endif
	bool* ResetRegister = &_input_ResetRegister;
	brp_Sys_SetRegister_RegisterAssignments_Entry** RegisterAssignments = &_input_RegisterAssignments;
	size_t* RegisterAssignments_len = &_input_RegisterAssignments_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 15);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*ResetRegister));
	brp_frame_write_int8(_frame, (unsigned)(*RegisterAssignments_len));
	for(size_t _RegisterAssignments_ndx = 0;_RegisterAssignments_ndx < (*RegisterAssignments_len);_RegisterAssignments_ndx++) {
		brp_Sys_SetRegister_RegisterAssignments_Entry _RegisterAssignments_Entry = (*RegisterAssignments)[_RegisterAssignments_ndx];
		brp_Sys_SetRegister_RegisterAssignments_Entry* RegisterAssignments_Entry = &_RegisterAssignments_Entry;
		unsigned _ID = (RegisterAssignments_Entry)->ID;
		unsigned* ID = &_ID;
		unsigned _Value = (RegisterAssignments_Entry)->Value;
		unsigned* Value = &_Value;
		brp_frame_write_int16(_frame, (unsigned)(*ID));
		brp_frame_write_int16(_frame, (unsigned)(*Value));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetRegister(brp_protocol protocol, unsigned _input_ID, unsigned* Value) {
#else
brp_errcode brp_Sys_GetRegister(brp_Sys_GetRegister_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_ID = params.ID;
	unsigned* Value = params.Value;
#endif
	unsigned* ID = &_input_ID;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_Value;
	if (Value == NULL) Value = &_tmp_Value;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*ID));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Value) = (unsigned)brp_frame_read_int16(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_PowerDown(brp_protocol protocol) {
#else
brp_errcode brp_Sys_PowerDown(brp_Sys_PowerDown_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 17);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_SelectProtocol(brp_protocol protocol, brp_ProtocolID _input_Protocol) {
#else
brp_errcode brp_Sys_SelectProtocol(brp_Sys_SelectProtocol_t params) {
	brp_protocol protocol = params.protocol;
	brp_ProtocolID _input_Protocol = params.Protocol;
#endif
	brp_ProtocolID* Protocol = &_input_Protocol;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 18);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Protocol));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_SetCommParam(brp_protocol protocol, brp_Baudrate _input_NewBaudrate, brp_Parity _input_NewParity, unsigned _input_CWT) {
#else
brp_errcode brp_Sys_SetCommParam(brp_Sys_SetCommParam_t params) {
	brp_protocol protocol = params.protocol;
	brp_Baudrate _input_NewBaudrate = params.NewBaudrate;
	brp_Parity _input_NewParity = params.NewParity;
	unsigned _input_CWT = params.CWT;
#endif
	brp_Baudrate* NewBaudrate = &_input_NewBaudrate;
	brp_Parity* NewParity = &_input_NewParity;
	unsigned* CWT = &_input_CWT;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 20);
	brp_frame_write_int32(_frame, 100);
	if (_input_NewBaudrate == 0) _input_NewBaudrate = (brp_Baudrate)1152;
	brp_frame_write_int16(_frame, (unsigned)(*NewBaudrate));
	brp_frame_write_int8(_frame, (unsigned)(*NewParity));
	brp_frame_write_int8(_frame, (unsigned)(*CWT));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgLoadBlock(brp_protocol protocol, unsigned _input_Version, brp_buf _input_Data, size_t _input_Data_len) {
#else
brp_errcode brp_Sys_CfgLoadBlock(brp_Sys_CfgLoadBlock_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Version = params.Version;
	brp_buf _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
#endif
	unsigned* Version = &_input_Version;
	brp_buf* Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 22);
	brp_frame_write_int32(_frame, 10000);
	brp_frame_write_int8(_frame, (unsigned)(*Version));
	brp_frame_write_int8(_frame, (unsigned)(*Data_len));
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetPlatformId(brp_protocol protocol, brp_buf* PlatformId, unsigned* BootloaderId, unsigned* BootloaderMajor, unsigned* BootloaderMinor, unsigned* BootloaderBuild, brp_mempool *mempool) {
#else
brp_errcode brp_Sys_GetPlatformId(brp_Sys_GetPlatformId_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* PlatformId = params.PlatformId;
	unsigned* BootloaderId = params.BootloaderId;
	unsigned* BootloaderMajor = params.BootloaderMajor;
	unsigned* BootloaderMinor = params.BootloaderMinor;
	unsigned* BootloaderBuild = params.BootloaderBuild;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	unsigned _tmp_BootloaderId;
	if (BootloaderId == NULL) BootloaderId = &_tmp_BootloaderId;
	unsigned _tmp_BootloaderMajor;
	if (BootloaderMajor == NULL) BootloaderMajor = &_tmp_BootloaderMajor;
	unsigned _tmp_BootloaderMinor;
	if (BootloaderMinor == NULL) BootloaderMinor = &_tmp_BootloaderMinor;
	unsigned _tmp_BootloaderBuild;
	if (BootloaderBuild == NULL) BootloaderBuild = &_tmp_BootloaderBuild;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 23);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _PlatformId_len = 5;
	size_t* PlatformId_len = &_PlatformId_len;
	if (PlatformId != NULL) {
		(*PlatformId) = (brp_buf)brp_mempool_create_buf(mempool, (*PlatformId_len));
		if((*PlatformId) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*PlatformId), (*PlatformId_len));
	} else
		brp_frame_skip(&_reader, (*PlatformId_len));
	(*BootloaderId) = (unsigned)brp_frame_read_int8(&_reader);
	(*BootloaderMajor) = (unsigned)brp_frame_read_int8(&_reader);
	(*BootloaderMinor) = (unsigned)brp_frame_read_int8(&_reader);
	(*BootloaderBuild) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgReset(brp_protocol protocol) {
#else
brp_errcode brp_Sys_CfgReset(brp_Sys_CfgReset_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 24);
	brp_frame_write_int32(_frame, 10000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_StopProtocol(brp_protocol protocol, brp_ProtocolID _input_Protocol) {
#else
brp_errcode brp_Sys_StopProtocol(brp_Sys_StopProtocol_t params) {
	brp_protocol protocol = params.protocol;
	brp_ProtocolID _input_Protocol = params.Protocol;
#endif
	brp_ProtocolID* Protocol = &_input_Protocol;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 25);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Protocol));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_SendMessage(brp_protocol protocol, brp_ProtocolID _input_Protocol, brp_MessageType _input_MsgType, brp_buf _input_Message, size_t _input_Message_len) {
#else
brp_errcode brp_Sys_SendMessage(brp_Sys_SendMessage_t params) {
	brp_protocol protocol = params.protocol;
	brp_ProtocolID _input_Protocol = params.Protocol;
	brp_MessageType _input_MsgType = params.MsgType;
	brp_buf _input_Message = params.Message;
	size_t _input_Message_len = params.Message_len;
#endif
	brp_ProtocolID* Protocol = &_input_Protocol;
	brp_MessageType* MsgType = &_input_MsgType;
	brp_buf* Message = &_input_Message;
	size_t* Message_len = &_input_Message_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 26);
	brp_frame_write_int32(_frame, 1000);
	brp_frame_write_int8(_frame, (unsigned)(*Protocol));
	brp_frame_write_int8(_frame, (unsigned)(*MsgType));
	brp_frame_write_int8(_frame, (unsigned)(*Message_len));
	brp_frame_write(_frame, (brp_buf)(*Message), (*Message_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgGetId(brp_protocol protocol, char** ConfigId, char** ConfigName, brp_mempool *mempool) {
#else
brp_errcode brp_Sys_CfgGetId(brp_Sys_CfgGetId_t params) {
	brp_protocol protocol = params.protocol;
	char** ConfigId = params.ConfigId;
	char** ConfigName = params.ConfigName;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 32);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _ConfigId_len = 0;
	size_t* ConfigId_len = &_ConfigId_len;
	(*ConfigId_len) = brp_frame_read_int8(&_reader);
	if (ConfigId != NULL) {
		(*ConfigId) = (char*)brp_mempool_create_buf(mempool, (*ConfigId_len));
		if((*ConfigId) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ConfigId), (*ConfigId_len));
	} else
		brp_frame_skip(&_reader, (*ConfigId_len));
	if(ConfigId != NULL) {
		(*ConfigId_len) += 1;
		(*ConfigId) = (char*)brp_mempool_resize_buf((brp_buf)(*ConfigId), (*ConfigId_len));
		if((*ConfigId) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		(*ConfigId)[(*ConfigId_len)-1] = 0;
	}
	size_t _ConfigName_len = 0;
	size_t* ConfigName_len = &_ConfigName_len;
	(*ConfigName_len) = brp_frame_read_int8(&_reader);
	if (ConfigName != NULL) {
		(*ConfigName) = (char*)brp_mempool_create_buf(mempool, (*ConfigName_len));
		if((*ConfigName) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ConfigName), (*ConfigName_len));
	} else
		brp_frame_skip(&_reader, (*ConfigName_len));
	if(ConfigName != NULL) {
		(*ConfigName_len) += 1;
		(*ConfigName) = (char*)brp_mempool_resize_buf((brp_buf)(*ConfigName), (*ConfigName_len));
		if((*ConfigName) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		(*ConfigName)[(*ConfigName_len)-1] = 0;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgGetDeviceSettingsId(brp_protocol protocol, char** ConfigId, char** ConfigName, brp_mempool *mempool) {
#else
brp_errcode brp_Sys_CfgGetDeviceSettingsId(brp_Sys_CfgGetDeviceSettingsId_t params) {
	brp_protocol protocol = params.protocol;
	char** ConfigId = params.ConfigId;
	char** ConfigName = params.ConfigName;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _ConfigId_len = 0;
	size_t* ConfigId_len = &_ConfigId_len;
	(*ConfigId_len) = brp_frame_read_int8(&_reader);
	if (ConfigId != NULL) {
		(*ConfigId) = (char*)brp_mempool_create_buf(mempool, (*ConfigId_len));
		if((*ConfigId) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ConfigId), (*ConfigId_len));
	} else
		brp_frame_skip(&_reader, (*ConfigId_len));
	if(ConfigId != NULL) {
		(*ConfigId_len) += 1;
		(*ConfigId) = (char*)brp_mempool_resize_buf((brp_buf)(*ConfigId), (*ConfigId_len));
		if((*ConfigId) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		(*ConfigId)[(*ConfigId_len)-1] = 0;
	}
	size_t _ConfigName_len = 0;
	size_t* ConfigName_len = &_ConfigName_len;
	(*ConfigName_len) = brp_frame_read_int8(&_reader);
	if (ConfigName != NULL) {
		(*ConfigName) = (char*)brp_mempool_create_buf(mempool, (*ConfigName_len));
		if((*ConfigName) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ConfigName), (*ConfigName_len));
	} else
		brp_frame_skip(&_reader, (*ConfigName_len));
	if(ConfigName != NULL) {
		(*ConfigName_len) += 1;
		(*ConfigName) = (char*)brp_mempool_resize_buf((brp_buf)(*ConfigName), (*ConfigName_len));
		if((*ConfigName) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		(*ConfigName)[(*ConfigName_len)-1] = 0;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_FactoryResetLegacy(brp_protocol protocol) {
#else
brp_errcode brp_Sys_FactoryResetLegacy(brp_Sys_FactoryResetLegacy_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 34);
	brp_frame_write_int32(_frame, 30000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetStatistics(brp_protocol protocol, bool _input_DeleteCounters, brp_Sys_GetStatistics_CounterTuple_Entry** CounterTuple, size_t* CounterTuple_len, brp_mempool *mempool) {
#else
brp_errcode brp_Sys_GetStatistics(brp_Sys_GetStatistics_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_DeleteCounters = params.DeleteCounters;
	brp_Sys_GetStatistics_CounterTuple_Entry** CounterTuple = params.CounterTuple;
	size_t* CounterTuple_len = params.CounterTuple_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* DeleteCounters = &_input_DeleteCounters;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _CounterTuple_len;
	if(CounterTuple_len == NULL) CounterTuple_len = &_CounterTuple_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 35);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*DeleteCounters));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*CounterTuple_len) = brp_frame_read_int8(&_reader);
	if (CounterTuple != NULL) {
		(*CounterTuple) = (brp_Sys_GetStatistics_CounterTuple_Entry*)brp_mempool_create_buf(mempool, (*CounterTuple_len) * sizeof(brp_Sys_GetStatistics_CounterTuple_Entry));
		if((*CounterTuple) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _CounterTuple_ndx = 0;(_CounterTuple_ndx < (*CounterTuple_len)) & !brp_frame_read_err(&_reader);_CounterTuple_ndx++) {
		brp_Sys_GetStatistics_CounterTuple_Entry _CounterTuple_Entry;
		brp_Sys_GetStatistics_CounterTuple_Entry *CounterTuple_Entry = &_CounterTuple_Entry;
		unsigned _ID;
		unsigned *ID = &_ID;
		unsigned _Value;
		unsigned *Value = &_Value;
		(*ID) = (unsigned)brp_frame_read_int8(&_reader);
		(*Value) = (unsigned)brp_frame_read_int8(&_reader);
		if(CounterTuple_Entry != NULL) {
			CounterTuple_Entry->ID = *ID;
			CounterTuple_Entry->Value = *Value;
		}
		if (CounterTuple != NULL)
			(*CounterTuple)[_CounterTuple_ndx] = *CounterTuple_Entry;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetFeatures(brp_protocol protocol, brp_FeatureID** FeatureList, size_t* FeatureList_len, brp_FeatureID* MaxFeatureID, brp_mempool *mempool) {
#else
brp_errcode brp_Sys_GetFeatures(brp_Sys_GetFeatures_t params) {
	brp_protocol protocol = params.protocol;
	brp_FeatureID** FeatureList = params.FeatureList;
	size_t* FeatureList_len = params.FeatureList_len;
	brp_FeatureID* MaxFeatureID = params.MaxFeatureID;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _FeatureList_len;
	if(FeatureList_len == NULL) FeatureList_len = &_FeatureList_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 36);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*FeatureList_len) = brp_frame_read_int8(&_reader);
	if (FeatureList != NULL) {
		(*FeatureList) = (brp_FeatureID*)brp_mempool_create_buf(mempool, (*FeatureList_len) * sizeof(brp_FeatureID));
		if((*FeatureList) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _FeatureList_ndx = 0;(_FeatureList_ndx < (*FeatureList_len)) & !brp_frame_read_err(&_reader);_FeatureList_ndx++) {
		brp_FeatureID _SupportedFeatureID;
		brp_FeatureID *SupportedFeatureID = &_SupportedFeatureID;
		int _SupportedFeatureID_int_val = brp_frame_read_int16(&_reader);
		if (SupportedFeatureID != NULL) {
			if (brp_FeatureID_is_valid(_SupportedFeatureID_int_val))
				(*SupportedFeatureID) = (brp_FeatureID)_SupportedFeatureID_int_val;
			else
				(*SupportedFeatureID) = brp_FeatureID_undefined;
		}
		if (FeatureList != NULL)
			(*FeatureList)[_FeatureList_ndx] = *SupportedFeatureID;
	}
	int _MaxFeatureID_int_val = brp_frame_read_int16(&_reader);
	if (MaxFeatureID != NULL) {
		if (brp_FeatureID_is_valid(_MaxFeatureID_int_val))
			(*MaxFeatureID) = (brp_FeatureID)_MaxFeatureID_int_val;
		else
			(*MaxFeatureID) = brp_FeatureID_undefined;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetPartNumber(brp_protocol protocol, char** PartNo, char** HwRevNo, brp_mempool *mempool) {
#else
brp_errcode brp_Sys_GetPartNumber(brp_Sys_GetPartNumber_t params) {
	brp_protocol protocol = params.protocol;
	char** PartNo = params.PartNo;
	char** HwRevNo = params.HwRevNo;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 37);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _PartNo_len = 0;
	size_t* PartNo_len = &_PartNo_len;
	(*PartNo_len) = brp_frame_read_int8(&_reader);
	if (PartNo != NULL) {
		(*PartNo) = (char*)brp_mempool_create_buf(mempool, (*PartNo_len));
		if((*PartNo) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*PartNo), (*PartNo_len));
	} else
		brp_frame_skip(&_reader, (*PartNo_len));
	if(PartNo != NULL) {
		(*PartNo_len) += 1;
		(*PartNo) = (char*)brp_mempool_resize_buf((brp_buf)(*PartNo), (*PartNo_len));
		if((*PartNo) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		(*PartNo)[(*PartNo_len)-1] = 0;
	}
	size_t _HwRevNo_len = 0;
	size_t* HwRevNo_len = &_HwRevNo_len;
	(*HwRevNo_len) = brp_frame_read_int8(&_reader);
	if (HwRevNo != NULL) {
		(*HwRevNo) = (char*)brp_mempool_create_buf(mempool, (*HwRevNo_len));
		if((*HwRevNo) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*HwRevNo), (*HwRevNo_len));
	} else
		brp_frame_skip(&_reader, (*HwRevNo_len));
	if(HwRevNo != NULL) {
		(*HwRevNo_len) += 1;
		(*HwRevNo) = (char*)brp_mempool_resize_buf((brp_buf)(*HwRevNo), (*HwRevNo_len));
		if((*HwRevNo) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		(*HwRevNo)[(*HwRevNo_len)-1] = 0;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgLoadPrepare(brp_protocol protocol, brp_AuthReqUpload _input_AuthReq) {
#else
brp_errcode brp_Sys_CfgLoadPrepare(brp_Sys_CfgLoadPrepare_t params) {
	brp_protocol protocol = params.protocol;
	brp_AuthReqUpload _input_AuthReq = params.AuthReq;
#endif
	brp_AuthReqUpload* AuthReq = &_input_AuthReq;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 38);
	brp_frame_write_int32(_frame, 10000);
	brp_frame_write_int8(_frame, (unsigned)(*AuthReq));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_CfgLoadFinish(brp_protocol protocol, brp_Sys_CfgLoadFinish_FinalizeAction _input_FinalizeAction) {
#else
brp_errcode brp_Sys_CfgLoadFinish(brp_Sys_CfgLoadFinish_t params) {
	brp_protocol protocol = params.protocol;
	brp_Sys_CfgLoadFinish_FinalizeAction _input_FinalizeAction = params.FinalizeAction;
#endif
	brp_Sys_CfgLoadFinish_FinalizeAction* FinalizeAction = &_input_FinalizeAction;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 39);
	brp_frame_write_int32(_frame, 10000);
	brp_frame_write_int8(_frame, (unsigned)(*FinalizeAction));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_FactoryReset(brp_protocol protocol, bool _input_PerformReboot) {
#else
brp_errcode brp_Sys_FactoryReset(brp_Sys_FactoryReset_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_PerformReboot = params.PerformReboot;
#endif
	bool* PerformReboot = &_input_PerformReboot;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 40);
	brp_frame_write_int32(_frame, 30000);
	brp_frame_write_int8(_frame, (unsigned)(*PerformReboot));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetLicenses(brp_protocol protocol, brp_LicenseBitMask* LicenseBitMask) {
#else
brp_errcode brp_Sys_GetLicenses(brp_Sys_GetLicenses_t params) {
	brp_protocol protocol = params.protocol;
	brp_LicenseBitMask* LicenseBitMask = params.LicenseBitMask;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 41);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	unsigned _LicenseBitMask_int = brp_frame_read_int32(&_reader);
	if(LicenseBitMask != NULL) {
		(LicenseBitMask->Ble) = (_LicenseBitMask_int>>3) & 0b1;
		(LicenseBitMask->BleLicRequired) = (_LicenseBitMask_int>>2) & 0b1;
		(LicenseBitMask->HidOnlyForSE) = (_LicenseBitMask_int>>1) & 0b1;
		(LicenseBitMask->Hid) = (_LicenseBitMask_int>>0) & 0b1;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Sys_GetFwCrc(brp_protocol protocol, unsigned* CRC) {
#else
brp_errcode brp_Sys_GetFwCrc(brp_Sys_GetFwCrc_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* CRC = params.CRC;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_CRC;
	if (CRC == NULL) CRC = &_tmp_CRC;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 127);
	brp_frame_write_int32(_frame, 1000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*CRC) = (unsigned)brp_frame_read_int32(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_TTF_ReadByteStream(brp_protocol protocol, bool _input_ResetDataPtr, unsigned _input_SamplingTime, unsigned _input_Rxlen, brp_TTF_ReadByteStream_RxMod _input_RxMod, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_TTF_ReadByteStream(brp_TTF_ReadByteStream_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_ResetDataPtr = params.ResetDataPtr;
	unsigned _input_SamplingTime = params.SamplingTime;
	unsigned _input_Rxlen = params.Rxlen;
	brp_TTF_ReadByteStream_RxMod _input_RxMod = params.RxMod;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* ResetDataPtr = &_input_ResetDataPtr;
	unsigned* SamplingTime = &_input_SamplingTime;
	unsigned* Rxlen = &_input_Rxlen;
	brp_TTF_ReadByteStream_RxMod* RxMod = &_input_RxMod;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 52);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	if (_input_RxMod == 0) _input_RxMod = (brp_TTF_ReadByteStream_RxMod)112;
	unsigned _bitmask_c6ce = 0;
	_bitmask_c6ce |= (*ResetDataPtr & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_c6ce);
	brp_frame_write_int8(_frame, (unsigned)(*SamplingTime));
	brp_frame_write_int16(_frame, (unsigned)(*Rxlen));
	brp_frame_write_int8(_frame, (unsigned)(*RxMod));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int16(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Ultralight_ExecCmd(brp_protocol protocol, unsigned _input_Cmd, brp_buf _input_Param, size_t _input_Param_len, brp_buf* Response, size_t* Response_len, brp_mempool *mempool) {
#else
brp_errcode brp_Ultralight_ExecCmd(brp_Ultralight_ExecCmd_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Cmd = params.Cmd;
	brp_buf _input_Param = params.Param;
	size_t _input_Param_len = params.Param_len;
	brp_buf* Response = params.Response;
	size_t* Response_len = params.Response_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Cmd = &_input_Cmd;
	brp_buf* Param = &_input_Param;
	size_t* Param_len = &_input_Param_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Response_len;
	if(Response_len == NULL) Response_len = &_Response_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 37);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Cmd));
	brp_frame_write_int8(_frame, (unsigned)(*Param_len));
	brp_frame_write(_frame, (brp_buf)(*Param), (*Param_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Response_len) = brp_frame_read_int8(&_reader);
	if (Response != NULL) {
		(*Response) = (brp_buf)brp_mempool_create_buf(mempool, (*Response_len));
		if((*Response) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Response), (*Response_len));
	} else
		brp_frame_skip(&_reader, (*Response_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Ultralight_Read(brp_protocol protocol, unsigned _input_PageAdr, brp_buf* PageData, brp_mempool *mempool) {
#else
brp_errcode brp_Ultralight_Read(brp_Ultralight_Read_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_PageAdr = params.PageAdr;
	brp_buf* PageData = params.PageData;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* PageAdr = &_input_PageAdr;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 37);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*PageAdr));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	size_t _PageData_len = 16;
	size_t* PageData_len = &_PageData_len;
	if (PageData != NULL) {
		(*PageData) = (brp_buf)brp_mempool_create_buf(mempool, (*PageData_len));
		if((*PageData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*PageData), (*PageData_len));
	} else
		brp_frame_skip(&_reader, (*PageData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Ultralight_Write(brp_protocol protocol, unsigned _input_PageAdr, brp_buf _input_PageData) {
#else
brp_errcode brp_Ultralight_Write(brp_Ultralight_Write_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_PageAdr = params.PageAdr;
	brp_buf _input_PageData = params.PageData;
#endif
	unsigned* PageAdr = &_input_PageAdr;
	brp_buf* PageData = &_input_PageData;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 37);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*PageAdr));
	size_t _PageData_len_val = 4;
	size_t* PageData_len = &_PageData_len_val;
	brp_frame_write(_frame, (brp_buf)(*PageData), (*PageData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Ultralight_AuthE2(brp_protocol protocol, brp_Ultralight_AuthE2_DivMode _input_DivMode, bool _input_HasExtIdx, unsigned _input_KeyIdx, brp_buf _input_DivData, size_t _input_DivData_len, unsigned _input_KeyExtIdx) {
#else
brp_errcode brp_Ultralight_AuthE2(brp_Ultralight_AuthE2_t params) {
	brp_protocol protocol = params.protocol;
	brp_Ultralight_AuthE2_DivMode _input_DivMode = params.DivMode;
	bool _input_HasExtIdx = params.HasExtIdx;
	unsigned _input_KeyIdx = params.KeyIdx;
	brp_buf _input_DivData = params.DivData;
	size_t _input_DivData_len = params.DivData_len;
	unsigned _input_KeyExtIdx = params.KeyExtIdx;
#endif
	brp_Ultralight_AuthE2_DivMode* DivMode = &_input_DivMode;
	bool* HasExtIdx = &_input_HasExtIdx;
	unsigned* KeyIdx = &_input_KeyIdx;
	brp_buf* DivData = &_input_DivData;
	size_t* DivData_len = &_input_DivData_len;
	unsigned* KeyExtIdx = &_input_KeyExtIdx;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 37);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	if(!(*HasExtIdx) && (*KeyExtIdx)) (*HasExtIdx) = true;
	unsigned _bitmask_cfa3 = 0;
	_bitmask_cfa3 |= (*DivMode & 0b11) << 1;
	_bitmask_cfa3 |= (*HasExtIdx & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_cfa3);
	brp_frame_write_int8(_frame, (unsigned)(*KeyIdx));
	brp_frame_write_int8(_frame, (unsigned)(*DivData_len));
	brp_frame_write(_frame, (brp_buf)(*DivData), (*DivData_len));
	if(*HasExtIdx) {
		brp_frame_write_int8(_frame, (unsigned)(*KeyExtIdx));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Ultralight_AuthUser(brp_protocol protocol, brp_Ultralight_AuthUser_CryptoMode _input_CryptoMode, brp_buf _input_Key, size_t _input_Key_len) {
#else
brp_errcode brp_Ultralight_AuthUser(brp_Ultralight_AuthUser_t params) {
	brp_protocol protocol = params.protocol;
	brp_Ultralight_AuthUser_CryptoMode _input_CryptoMode = params.CryptoMode;
	brp_buf _input_Key = params.Key;
	size_t _input_Key_len = params.Key_len;
#endif
	brp_Ultralight_AuthUser_CryptoMode* CryptoMode = &_input_CryptoMode;
	brp_buf* Key = &_input_Key;
	size_t* Key_len = &_input_Key_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 37);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	unsigned _bitmask_2253 = 0;
	_bitmask_2253 |= (*CryptoMode & 0b11) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_2253);
	brp_frame_write_int8(_frame, (unsigned)(*Key_len));
	brp_frame_write(_frame, (brp_buf)(*Key), (*Key_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_Ultralight_SectorSwitch(brp_protocol protocol, unsigned _input_SectorNumber) {
#else
brp_errcode brp_Ultralight_SectorSwitch(brp_Ultralight_SectorSwitch_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_SectorNumber = params.SectorNumber;
#endif
	unsigned* SectorNumber = &_input_SectorNumber;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 37);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*SectorNumber));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_Enable(brp_protocol protocol, bool _input_Enable) {
#else
brp_errcode brp_UsbHost_Enable(brp_UsbHost_Enable_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_Enable = params.Enable;
#endif
	bool* Enable = &_input_Enable;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Enable));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_IsConnected(brp_protocol protocol, bool* Connected) {
#else
brp_errcode brp_UsbHost_IsConnected(brp_UsbHost_IsConnected_t params) {
	brp_protocol protocol = params.protocol;
	bool* Connected = params.Connected;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	bool _tmp_Connected;
	if (Connected == NULL) Connected = &_tmp_Connected;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Connected) = (bool)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_SetupPipes(brp_protocol protocol, brp_UsbHost_SetupPipes_Pipes_Entry* _input_Pipes, size_t _input_Pipes_len) {
#else
brp_errcode brp_UsbHost_SetupPipes(brp_UsbHost_SetupPipes_t params) {
	brp_protocol protocol = params.protocol;
	brp_UsbHost_SetupPipes_Pipes_Entry* _input_Pipes = params.Pipes;
	size_t _input_Pipes_len = params.Pipes_len;
#endif
	brp_UsbHost_SetupPipes_Pipes_Entry** Pipes = &_input_Pipes;
	size_t* Pipes_len = &_input_Pipes_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Pipes_len));
	for(size_t _Pipes_ndx = 0;_Pipes_ndx < (*Pipes_len);_Pipes_ndx++) {
		brp_UsbHost_SetupPipes_Pipes_Entry _Pipes_Entry = (*Pipes)[_Pipes_ndx];
		brp_UsbHost_SetupPipes_Pipes_Entry* Pipes_Entry = &_Pipes_Entry;
		unsigned _No = (Pipes_Entry)->No;
		unsigned* No = &_No;
		brp_UsbHost_SetupPipes_Type _Type = (Pipes_Entry)->Type;
		brp_UsbHost_SetupPipes_Type* Type = &_Type;
		unsigned _FrameSize = (Pipes_Entry)->FrameSize;
		unsigned* FrameSize = &_FrameSize;
		brp_frame_write_int8(_frame, (unsigned)(*No));
		brp_frame_write_int8(_frame, (unsigned)(*Type));
		brp_frame_write_int8(_frame, (unsigned)(*FrameSize));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_SetAddr(brp_protocol protocol, unsigned _input_Address) {
#else
brp_errcode brp_UsbHost_SetAddr(brp_UsbHost_SetAddr_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
#endif
	unsigned* Address = &_input_Address;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Address));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_Reset(brp_protocol protocol) {
#else
brp_errcode brp_UsbHost_Reset(brp_UsbHost_Reset_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_TransRawSetup(brp_protocol protocol, brp_buf _input_SetupData, unsigned _input_PipeNo, unsigned _input_Timeout) {
#else
brp_errcode brp_UsbHost_TransRawSetup(brp_UsbHost_TransRawSetup_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_SetupData = params.SetupData;
	unsigned _input_PipeNo = params.PipeNo;
	unsigned _input_Timeout = params.Timeout;
#endif
	brp_buf* SetupData = &_input_SetupData;
	unsigned* PipeNo = &_input_PipeNo;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 100);
	size_t _SetupData_len_val = 8;
	size_t* SetupData_len = &_SetupData_len_val;
	brp_frame_write(_frame, (brp_buf)(*SetupData), (*SetupData_len));
	brp_frame_write_int8(_frame, (unsigned)(*PipeNo));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_TransSetupIn(brp_protocol protocol, brp_buf _input_SetupData, unsigned _input_PipeNo, unsigned _input_Timeout, brp_buf* InData, size_t* InData_len, brp_mempool *mempool) {
#else
brp_errcode brp_UsbHost_TransSetupIn(brp_UsbHost_TransSetupIn_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_SetupData = params.SetupData;
	unsigned _input_PipeNo = params.PipeNo;
	unsigned _input_Timeout = params.Timeout;
	brp_buf* InData = params.InData;
	size_t* InData_len = params.InData_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* SetupData = &_input_SetupData;
	unsigned* PipeNo = &_input_PipeNo;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _InData_len;
	if(InData_len == NULL) InData_len = &_InData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int32(_frame, 100);
	size_t _SetupData_len_val = 8;
	size_t* SetupData_len = &_SetupData_len_val;
	brp_frame_write(_frame, (brp_buf)(*SetupData), (*SetupData_len));
	brp_frame_write_int8(_frame, (unsigned)(*PipeNo));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*InData_len) = brp_frame_read_int16(&_reader);
	if (InData != NULL) {
		(*InData) = (brp_buf)brp_mempool_create_buf(mempool, (*InData_len));
		if((*InData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*InData), (*InData_len));
	} else
		brp_frame_skip(&_reader, (*InData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_TransSetupOut(brp_protocol protocol, brp_buf _input_SetupData, brp_buf _input_OutData, size_t _input_OutData_len, unsigned _input_PipeNo, unsigned _input_Timeout) {
#else
brp_errcode brp_UsbHost_TransSetupOut(brp_UsbHost_TransSetupOut_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_SetupData = params.SetupData;
	brp_buf _input_OutData = params.OutData;
	size_t _input_OutData_len = params.OutData_len;
	unsigned _input_PipeNo = params.PipeNo;
	unsigned _input_Timeout = params.Timeout;
#endif
	brp_buf* SetupData = &_input_SetupData;
	brp_buf* OutData = &_input_OutData;
	size_t* OutData_len = &_input_OutData_len;
	unsigned* PipeNo = &_input_PipeNo;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int32(_frame, 100);
	size_t _SetupData_len_val = 8;
	size_t* SetupData_len = &_SetupData_len_val;
	brp_frame_write(_frame, (brp_buf)(*SetupData), (*SetupData_len));
	brp_frame_write_int16(_frame, (unsigned)(*OutData_len));
	brp_frame_write(_frame, (brp_buf)(*OutData), (*OutData_len));
	brp_frame_write_int8(_frame, (unsigned)(*PipeNo));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_TransIn(brp_protocol protocol, unsigned _input_PipeNo, unsigned _input_Timeout, brp_buf* InData, size_t* InData_len, brp_mempool *mempool) {
#else
brp_errcode brp_UsbHost_TransIn(brp_UsbHost_TransIn_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_PipeNo = params.PipeNo;
	unsigned _input_Timeout = params.Timeout;
	brp_buf* InData = params.InData;
	size_t* InData_len = params.InData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* PipeNo = &_input_PipeNo;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _InData_len;
	if(InData_len == NULL) InData_len = &_InData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*PipeNo));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*InData_len) = brp_frame_read_int16(&_reader);
	if (InData != NULL) {
		(*InData) = (brp_buf)brp_mempool_create_buf(mempool, (*InData_len));
		if((*InData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*InData), (*InData_len));
	} else
		brp_frame_skip(&_reader, (*InData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_TransOut(brp_protocol protocol, brp_buf _input_OutData, size_t _input_OutData_len, unsigned _input_PipeNo, bool _input_Continue, unsigned _input_Timeout) {
#else
brp_errcode brp_UsbHost_TransOut(brp_UsbHost_TransOut_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_OutData = params.OutData;
	size_t _input_OutData_len = params.OutData_len;
	unsigned _input_PipeNo = params.PipeNo;
	bool _input_Continue = params.Continue;
	unsigned _input_Timeout = params.Timeout;
#endif
	brp_buf* OutData = &_input_OutData;
	size_t* OutData_len = &_input_OutData_len;
	unsigned* PipeNo = &_input_PipeNo;
	bool* Continue = &_input_Continue;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*OutData_len));
	brp_frame_write(_frame, (brp_buf)(*OutData), (*OutData_len));
	brp_frame_write_int8(_frame, (unsigned)(*PipeNo));
	brp_frame_write_int8(_frame, (unsigned)(*Continue));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_Suspend(brp_protocol protocol) {
#else
brp_errcode brp_UsbHost_Suspend(brp_UsbHost_Suspend_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int8(_frame, 11);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UsbHost_Resume(brp_protocol protocol) {
#else
brp_errcode brp_UsbHost_Resume(brp_UsbHost_Resume_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int8(_frame, 12);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UI_Enable(brp_protocol protocol, brp_IoPort _input_Port) {
#else
brp_errcode brp_UI_Enable(brp_UI_Enable_t params) {
	brp_protocol protocol = params.protocol;
	brp_IoPort _input_Port = params.Port;
#endif
	brp_IoPort* Port = &_input_Port;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UI_Disable(brp_protocol protocol, brp_IoPort _input_Port) {
#else
brp_errcode brp_UI_Disable(brp_UI_Disable_t params) {
	brp_protocol protocol = params.protocol;
	brp_IoPort _input_Port = params.Port;
#endif
	brp_IoPort* Port = &_input_Port;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UI_Toggle(brp_protocol protocol, brp_IoPort _input_Port, unsigned _input_ToggleCount, unsigned _input_Timespan1, unsigned _input_Timespan2, brp_UI_Toggle_Polarity _input_Polarity) {
#else
brp_errcode brp_UI_Toggle(brp_UI_Toggle_t params) {
	brp_protocol protocol = params.protocol;
	brp_IoPort _input_Port = params.Port;
	unsigned _input_ToggleCount = params.ToggleCount;
	unsigned _input_Timespan1 = params.Timespan1;
	unsigned _input_Timespan2 = params.Timespan2;
	brp_UI_Toggle_Polarity _input_Polarity = params.Polarity;
#endif
	brp_IoPort* Port = &_input_Port;
	unsigned* ToggleCount = &_input_ToggleCount;
	unsigned* Timespan1 = &_input_Timespan1;
	unsigned* Timespan2 = &_input_Timespan2;
	brp_UI_Toggle_Polarity* Polarity = &_input_Polarity;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_frame_write_int8(_frame, (unsigned)(*ToggleCount));
	brp_frame_write_int16(_frame, (unsigned)(*Timespan1));
	brp_frame_write_int16(_frame, (unsigned)(*Timespan2));
	brp_frame_write_int8(_frame, (unsigned)(*Polarity));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UI_Sense(brp_protocol protocol, brp_IoPort _input_Port, brp_UI_Sense_PortState* PortState) {
#else
brp_errcode brp_UI_Sense(brp_UI_Sense_t params) {
	brp_protocol protocol = params.protocol;
	brp_IoPort _input_Port = params.Port;
	brp_UI_Sense_PortState* PortState = params.PortState;
#endif
	brp_IoPort* Port = &_input_Port;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	int _PortState_int_val = brp_frame_read_int8(&_reader);
	if (! brp_UI_Sense_PortState_is_valid(_PortState_int_val))
		return BRP_ERR_PAYLOAD_FORMAT;
	if (PortState != NULL)
		(*PortState) = (brp_UI_Sense_PortState)_PortState_int_val;
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UI_SetRgbLed(brp_protocol protocol, brp_LedBitMask _input_LedState, unsigned _input_RgbColor, unsigned _input_TransitionTime) {
#else
brp_errcode brp_UI_SetRgbLed(brp_UI_SetRgbLed_t params) {
	brp_protocol protocol = params.protocol;
	brp_LedBitMask _input_LedState = params.LedState;
	unsigned _input_RgbColor = params.RgbColor;
	unsigned _input_TransitionTime = params.TransitionTime;
#endif
	brp_LedBitMask* LedState = &_input_LedState;
	unsigned* RgbColor = &_input_RgbColor;
	unsigned* TransitionTime = &_input_TransitionTime;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int8(_frame, 32);
	brp_frame_write_int32(_frame, 100);
	unsigned _LedState_int = 0;
	_LedState_int |= (LedState->LeftLed & 0b1) << 2;
	_LedState_int |= (LedState->RightLed & 0b1) << 1;
	_LedState_int |= (LedState->SingleLed & 0b1) << 0;
	brp_frame_write_int16(_frame, (unsigned)_LedState_int);
	brp_frame_write_int32(_frame, (unsigned)(*RgbColor));
	brp_frame_write_int16(_frame, (unsigned)(*TransitionTime));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_UI_PulseRgbLed(brp_protocol protocol, brp_LedBitMask _input_LedState, unsigned _input_RgbColor1, unsigned _input_RgbColor2, unsigned _input_TransitionTime, unsigned _input_Period) {
#else
brp_errcode brp_UI_PulseRgbLed(brp_UI_PulseRgbLed_t params) {
	brp_protocol protocol = params.protocol;
	brp_LedBitMask _input_LedState = params.LedState;
	unsigned _input_RgbColor1 = params.RgbColor1;
	unsigned _input_RgbColor2 = params.RgbColor2;
	unsigned _input_TransitionTime = params.TransitionTime;
	unsigned _input_Period = params.Period;
#endif
	brp_LedBitMask* LedState = &_input_LedState;
	unsigned* RgbColor1 = &_input_RgbColor1;
	unsigned* RgbColor2 = &_input_RgbColor2;
	unsigned* TransitionTime = &_input_TransitionTime;
	unsigned* Period = &_input_Period;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int32(_frame, 100);
	unsigned _LedState_int = 0;
	_LedState_int |= (LedState->LeftLed & 0b1) << 2;
	_LedState_int |= (LedState->RightLed & 0b1) << 1;
	_LedState_int |= (LedState->SingleLed & 0b1) << 0;
	brp_frame_write_int16(_frame, (unsigned)_LedState_int);
	brp_frame_write_int32(_frame, (unsigned)(*RgbColor1));
	brp_frame_write_int32(_frame, (unsigned)(*RgbColor2));
	brp_frame_write_int16(_frame, (unsigned)(*TransitionTime));
	brp_frame_write_int16(_frame, (unsigned)(*Period));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_Select(brp_protocol protocol, brp_CardFamilies _input_CardFamiliesFilter, bool _input_Reselect, bool _input_AcceptConfCard, brp_CardType* SelectedCardType) {
#else
brp_errcode brp_VHL_Select(brp_VHL_Select_t params) {
	brp_protocol protocol = params.protocol;
	brp_CardFamilies _input_CardFamiliesFilter = params.CardFamiliesFilter;
	bool _input_Reselect = params.Reselect;
	bool _input_AcceptConfCard = params.AcceptConfCard;
	brp_CardType* SelectedCardType = params.SelectedCardType;
#endif
	brp_CardFamilies* CardFamiliesFilter = &_input_CardFamiliesFilter;
	bool* Reselect = &_input_Reselect;
	bool* AcceptConfCard = &_input_AcceptConfCard;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 3000);
	unsigned _CardFamiliesFilter_int = 0;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->LEGICPrime & 0b1) << 11;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->BluetoothMce & 0b1) << 10;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Khz125Part2 & 0b1) << 9;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Srix & 0b1) << 8;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Khz125Part1 & 0b1) << 7;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Felica & 0b1) << 6;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->IClass & 0b1) << 5;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->IClassIso14B & 0b1) << 4;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Iso14443B & 0b1) << 3;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Iso15693 & 0b1) << 2;
	_CardFamiliesFilter_int |= (CardFamiliesFilter->Iso14443A & 0b1) << 0;
	brp_frame_write_int16(_frame, (unsigned)_CardFamiliesFilter_int);
	brp_frame_write_int8(_frame, (unsigned)(*Reselect));
	brp_frame_write_int8(_frame, (unsigned)(*AcceptConfCard));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	int _SelectedCardType_int_val = brp_frame_read_int8(&_reader);
	if (SelectedCardType != NULL) {
		if (brp_CardType_is_valid(_SelectedCardType_int_val))
			(*SelectedCardType) = (brp_CardType)_SelectedCardType_int_val;
		else
			(*SelectedCardType) = brp_CardType_undefined;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_GetSnr(brp_protocol protocol, brp_buf* Snr, size_t* Snr_len, brp_mempool *mempool) {
#else
brp_errcode brp_VHL_GetSnr(brp_VHL_GetSnr_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* Snr = params.Snr;
	size_t* Snr_len = params.Snr_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Snr_len;
	if(Snr_len == NULL) Snr_len = &_Snr_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 1000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Snr_len) = brp_frame_rest( & _reader);
	if (Snr != NULL) {
		(*Snr) = (brp_buf)brp_mempool_create_buf(mempool, (*Snr_len));
		if((*Snr) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Snr), (*Snr_len));
	} else
		brp_frame_skip(&_reader, (*Snr_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_Read(brp_protocol protocol, unsigned _input_Id, unsigned _input_Adr, unsigned _input_Len, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_VHL_Read(brp_VHL_Read_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Id = params.Id;
	unsigned _input_Adr = params.Adr;
	unsigned _input_Len = params.Len;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Id = &_input_Id;
	unsigned* Adr = &_input_Adr;
	unsigned* Len = &_input_Len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 3000);
	brp_frame_write_int8(_frame, (unsigned)(*Id));
	brp_frame_write_int16(_frame, (unsigned)(*Adr));
	brp_frame_write_int16(_frame, (unsigned)(*Len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_rest( & _reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_Write(brp_protocol protocol, unsigned _input_Id, unsigned _input_Adr, brp_buf _input_Data, size_t _input_Data_len) {
#else
brp_errcode brp_VHL_Write(brp_VHL_Write_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Id = params.Id;
	unsigned _input_Adr = params.Adr;
	brp_buf _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
#endif
	unsigned* Id = &_input_Id;
	unsigned* Adr = &_input_Adr;
	brp_buf* Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 3000);
	brp_frame_write_int8(_frame, (unsigned)(*Id));
	brp_frame_write_int16(_frame, (unsigned)(*Adr));
	brp_frame_write_int16(_frame, (unsigned)(*Data_len));
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_IsSelected(brp_protocol protocol) {
#else
brp_errcode brp_VHL_IsSelected(brp_VHL_IsSelected_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 3000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_GetLegacyATR(brp_protocol protocol, brp_buf* ATR, size_t* ATR_len, brp_mempool *mempool) {
#else
brp_errcode brp_VHL_GetLegacyATR(brp_VHL_GetLegacyATR_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* ATR = params.ATR;
	size_t* ATR_len = params.ATR_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ATR_len;
	if(ATR_len == NULL) ATR_len = &_ATR_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 1000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ATR_len) = brp_frame_read_int8(&_reader);
	if (ATR != NULL) {
		(*ATR) = (brp_buf)brp_mempool_create_buf(mempool, (*ATR_len));
		if((*ATR) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ATR), (*ATR_len));
	} else
		brp_frame_skip(&_reader, (*ATR_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_ExchangeAPDU(brp_protocol protocol, brp_CardType _input_AssumedCardType, brp_buf _input_Cmd, size_t _input_Cmd_len, brp_buf* Resp, size_t* Resp_len, brp_mempool *mempool) {
#else
brp_errcode brp_VHL_ExchangeAPDU(brp_VHL_ExchangeAPDU_t params) {
	brp_protocol protocol = params.protocol;
	brp_CardType _input_AssumedCardType = params.AssumedCardType;
	brp_buf _input_Cmd = params.Cmd;
	size_t _input_Cmd_len = params.Cmd_len;
	brp_buf* Resp = params.Resp;
	size_t* Resp_len = params.Resp_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_CardType* AssumedCardType = &_input_AssumedCardType;
	brp_buf* Cmd = &_input_Cmd;
	size_t* Cmd_len = &_input_Cmd_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Resp_len;
	if(Resp_len == NULL) Resp_len = &_Resp_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 60000);
	brp_frame_write_int8(_frame, (unsigned)(*AssumedCardType));
	brp_frame_write_int16(_frame, (unsigned)(*Cmd_len));
	brp_frame_write(_frame, (brp_buf)(*Cmd), (*Cmd_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Resp_len) = brp_frame_read_int16(&_reader);
	if (Resp != NULL) {
		(*Resp) = (brp_buf)brp_mempool_create_buf(mempool, (*Resp_len));
		if((*Resp) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Resp), (*Resp_len));
	} else
		brp_frame_skip(&_reader, (*Resp_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_Setup(brp_protocol protocol, brp_CardType _input_ConsideredCardType, brp_VHL_Setup_HasMifareKey _input_HasMifareKey, brp_buf _input_MifareKey, brp_VHL_Setup_MifareHasAsKeyA _input_MifareHasAsKeyA, bool _input_MifareAsKeyA, brp_VHL_Setup_MifareHasMadId _input_MifareHasMadId, unsigned _input_MifareMadId, brp_VHL_Setup_DesfireHasAppId _input_DesfireHasAppId, unsigned _input_DesfireAppId, brp_VHL_Setup_HasDesfireFileDesc _input_HasDesfireFileDesc, brp_DesfireFileDescription _input_DesfireFileDesc, brp_buf _input_DesfireKey, size_t _input_DesfireKey_len, brp_buf _input_LegicSegmentInfo, size_t _input_LegicSegmentInfo_len, brp_VHL_Setup_LegicHasEnStamp _input_LegicHasEnStamp, bool _input_LegicEnStamp, brp_VHL_Setup_LegicHasAdrMode _input_LegicHasAdrMode, brp_VHL_Setup_LegicAdrMode _input_LegicAdrMode, brp_VHL_Setup_Iso15HasFirstBlock _input_Iso15HasFirstBlock, unsigned _input_Iso15FirstBlock, brp_VHL_Setup_Iso15HasBlockCount _input_Iso15HasBlockCount, unsigned _input_Iso15BlockCount, brp_VHL_Setup_Iso15HasOptionFlag _input_Iso15HasOptionFlag, brp_VHL_Setup_Iso15OptionFlag _input_Iso15OptionFlag, brp_VHL_Setup_Iso15HasBlockSize _input_Iso15HasBlockSize, unsigned _input_Iso15BlockSize, unsigned _input_Iso14SelectFileCmdListLen, brp_VHL_Setup_Iso14SelectFileCmdList_Entry* _input_Iso14SelectFileCmdList, size_t _input_Iso14SelectFileCmdList_len, brp_VHL_Setup_Iso14HasFileLen _input_Iso14HasFileLen, unsigned _input_Iso14FileLen, brp_VHL_Setup_Iso14HasApduTimeout _input_Iso14HasApduTimeout, unsigned _input_Iso14ApduTimeout) {
#else
brp_errcode brp_VHL_Setup(brp_VHL_Setup_t params) {
	brp_protocol protocol = params.protocol;
	brp_CardType _input_ConsideredCardType = params.ConsideredCardType;
	brp_VHL_Setup_HasMifareKey _input_HasMifareKey = params.HasMifareKey;
	brp_buf _input_MifareKey = params.MifareKey;
	brp_VHL_Setup_MifareHasAsKeyA _input_MifareHasAsKeyA = params.MifareHasAsKeyA;
	bool _input_MifareAsKeyA = params.MifareAsKeyA;
	brp_VHL_Setup_MifareHasMadId _input_MifareHasMadId = params.MifareHasMadId;
	unsigned _input_MifareMadId = params.MifareMadId;
	brp_VHL_Setup_DesfireHasAppId _input_DesfireHasAppId = params.DesfireHasAppId;
	unsigned _input_DesfireAppId = params.DesfireAppId;
	brp_VHL_Setup_HasDesfireFileDesc _input_HasDesfireFileDesc = params.HasDesfireFileDesc;
	brp_DesfireFileDescription _input_DesfireFileDesc = params.DesfireFileDesc;
	brp_buf _input_DesfireKey = params.DesfireKey;
	size_t _input_DesfireKey_len = params.DesfireKey_len;
	brp_buf _input_LegicSegmentInfo = params.LegicSegmentInfo;
	size_t _input_LegicSegmentInfo_len = params.LegicSegmentInfo_len;
	brp_VHL_Setup_LegicHasEnStamp _input_LegicHasEnStamp = params.LegicHasEnStamp;
	bool _input_LegicEnStamp = params.LegicEnStamp;
	brp_VHL_Setup_LegicHasAdrMode _input_LegicHasAdrMode = params.LegicHasAdrMode;
	brp_VHL_Setup_LegicAdrMode _input_LegicAdrMode = params.LegicAdrMode;
	brp_VHL_Setup_Iso15HasFirstBlock _input_Iso15HasFirstBlock = params.Iso15HasFirstBlock;
	unsigned _input_Iso15FirstBlock = params.Iso15FirstBlock;
	brp_VHL_Setup_Iso15HasBlockCount _input_Iso15HasBlockCount = params.Iso15HasBlockCount;
	unsigned _input_Iso15BlockCount = params.Iso15BlockCount;
	brp_VHL_Setup_Iso15HasOptionFlag _input_Iso15HasOptionFlag = params.Iso15HasOptionFlag;
	brp_VHL_Setup_Iso15OptionFlag _input_Iso15OptionFlag = params.Iso15OptionFlag;
	brp_VHL_Setup_Iso15HasBlockSize _input_Iso15HasBlockSize = params.Iso15HasBlockSize;
	unsigned _input_Iso15BlockSize = params.Iso15BlockSize;
	unsigned _input_Iso14SelectFileCmdListLen = params.Iso14SelectFileCmdListLen;
	brp_VHL_Setup_Iso14SelectFileCmdList_Entry* _input_Iso14SelectFileCmdList = params.Iso14SelectFileCmdList;
	size_t _input_Iso14SelectFileCmdList_len = params.Iso14SelectFileCmdList_len;
	brp_VHL_Setup_Iso14HasFileLen _input_Iso14HasFileLen = params.Iso14HasFileLen;
	unsigned _input_Iso14FileLen = params.Iso14FileLen;
	brp_VHL_Setup_Iso14HasApduTimeout _input_Iso14HasApduTimeout = params.Iso14HasApduTimeout;
	unsigned _input_Iso14ApduTimeout = params.Iso14ApduTimeout;
#endif
	brp_CardType* ConsideredCardType = &_input_ConsideredCardType;
	brp_VHL_Setup_HasMifareKey* HasMifareKey = &_input_HasMifareKey;
	brp_buf* MifareKey = &_input_MifareKey;
	brp_VHL_Setup_MifareHasAsKeyA* MifareHasAsKeyA = &_input_MifareHasAsKeyA;
	bool* MifareAsKeyA = &_input_MifareAsKeyA;
	brp_VHL_Setup_MifareHasMadId* MifareHasMadId = &_input_MifareHasMadId;
	unsigned* MifareMadId = &_input_MifareMadId;
	brp_VHL_Setup_DesfireHasAppId* DesfireHasAppId = &_input_DesfireHasAppId;
	unsigned* DesfireAppId = &_input_DesfireAppId;
	brp_VHL_Setup_HasDesfireFileDesc* HasDesfireFileDesc = &_input_HasDesfireFileDesc;
	brp_DesfireFileDescription* DesfireFileDesc = &_input_DesfireFileDesc;
	brp_buf* DesfireKey = &_input_DesfireKey;
	size_t* DesfireKey_len = &_input_DesfireKey_len;
	brp_buf* LegicSegmentInfo = &_input_LegicSegmentInfo;
	size_t* LegicSegmentInfo_len = &_input_LegicSegmentInfo_len;
	brp_VHL_Setup_LegicHasEnStamp* LegicHasEnStamp = &_input_LegicHasEnStamp;
	bool* LegicEnStamp = &_input_LegicEnStamp;
	brp_VHL_Setup_LegicHasAdrMode* LegicHasAdrMode = &_input_LegicHasAdrMode;
	brp_VHL_Setup_LegicAdrMode* LegicAdrMode = &_input_LegicAdrMode;
	brp_VHL_Setup_Iso15HasFirstBlock* Iso15HasFirstBlock = &_input_Iso15HasFirstBlock;
	unsigned* Iso15FirstBlock = &_input_Iso15FirstBlock;
	brp_VHL_Setup_Iso15HasBlockCount* Iso15HasBlockCount = &_input_Iso15HasBlockCount;
	unsigned* Iso15BlockCount = &_input_Iso15BlockCount;
	brp_VHL_Setup_Iso15HasOptionFlag* Iso15HasOptionFlag = &_input_Iso15HasOptionFlag;
	brp_VHL_Setup_Iso15OptionFlag* Iso15OptionFlag = &_input_Iso15OptionFlag;
	brp_VHL_Setup_Iso15HasBlockSize* Iso15HasBlockSize = &_input_Iso15HasBlockSize;
	unsigned* Iso15BlockSize = &_input_Iso15BlockSize;
	unsigned* Iso14SelectFileCmdListLen = &_input_Iso14SelectFileCmdListLen;
	brp_VHL_Setup_Iso14SelectFileCmdList_Entry** Iso14SelectFileCmdList = &_input_Iso14SelectFileCmdList;
	size_t* Iso14SelectFileCmdList_len = &_input_Iso14SelectFileCmdList_len;
	brp_VHL_Setup_Iso14HasFileLen* Iso14HasFileLen = &_input_Iso14HasFileLen;
	unsigned* Iso14FileLen = &_input_Iso14FileLen;
	brp_VHL_Setup_Iso14HasApduTimeout* Iso14HasApduTimeout = &_input_Iso14HasApduTimeout;
	unsigned* Iso14ApduTimeout = &_input_Iso14ApduTimeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int32(_frame, 100);
	if(!(*Iso14HasApduTimeout) && (*Iso14ApduTimeout)) (*Iso14HasApduTimeout) = brp_VHL_Setup_Iso14HasApduTimeout_Enabled;
	if(!(*Iso14HasFileLen) && (*Iso14FileLen)) (*Iso14HasFileLen) = brp_VHL_Setup_Iso14HasFileLen_Enabled;
	if(!(*Iso15HasBlockSize) && (*Iso15BlockSize)) (*Iso15HasBlockSize) = brp_VHL_Setup_Iso15HasBlockSize_Enabled;
	if(!(*Iso15HasOptionFlag) && (*Iso15OptionFlag)) (*Iso15HasOptionFlag) = brp_VHL_Setup_Iso15HasOptionFlag_Enabled;
	if(!(*Iso15HasBlockCount) && (*Iso15BlockCount)) (*Iso15HasBlockCount) = brp_VHL_Setup_Iso15HasBlockCount_Enabled;
	if(!(*Iso15HasFirstBlock) && (*Iso15FirstBlock)) (*Iso15HasFirstBlock) = brp_VHL_Setup_Iso15HasFirstBlock_Enabled;
	if(!(*LegicHasAdrMode) && (*LegicAdrMode)) (*LegicHasAdrMode) = brp_VHL_Setup_LegicHasAdrMode_Enabled;
	if(!(*LegicHasEnStamp) && (*LegicEnStamp)) (*LegicHasEnStamp) = brp_VHL_Setup_LegicHasEnStamp_Enabled;
	if(!(*DesfireHasAppId) && (*DesfireAppId)) (*DesfireHasAppId) = brp_VHL_Setup_DesfireHasAppId_Enabled;
	if(!(*MifareHasMadId) && (*MifareMadId)) (*MifareHasMadId) = brp_VHL_Setup_MifareHasMadId_Enabled;
	if(!(*MifareHasAsKeyA) && (*MifareAsKeyA)) (*MifareHasAsKeyA) = brp_VHL_Setup_MifareHasAsKeyA_Enabled;
	if(!(*HasMifareKey) && (MifareKey)) (*HasMifareKey) = brp_VHL_Setup_HasMifareKey_Enabled;
	int _autoset_ConsideredCardType = 0;
	if(*HasMifareKey || *MifareHasAsKeyA || *MifareHasMadId) _autoset_ConsideredCardType++;
	if(*DesfireHasAppId || *HasDesfireFileDesc || DesfireKey) _autoset_ConsideredCardType++;
	if(*Iso15HasFirstBlock || *Iso15HasBlockCount || *Iso15HasOptionFlag || *Iso15HasBlockSize) _autoset_ConsideredCardType++;
	if(*Iso14SelectFileCmdListLen || Iso14SelectFileCmdList || *Iso14HasFileLen || *Iso14HasApduTimeout) _autoset_ConsideredCardType++;
	if(!(*ConsideredCardType) && _autoset_ConsideredCardType > 1) return BRP_ERR_INVALID_API_CALL;
	if(!(*ConsideredCardType) && (*HasMifareKey || *MifareHasAsKeyA || *MifareHasMadId)) (*ConsideredCardType) = brp_CardType_MifareClassic;
	if(!(*ConsideredCardType) && (*DesfireHasAppId || *HasDesfireFileDesc || DesfireKey)) (*ConsideredCardType) = brp_CardType_MifareDesfire;
	if(!(*ConsideredCardType) && (*Iso15HasFirstBlock || *Iso15HasBlockCount || *Iso15HasOptionFlag || *Iso15HasBlockSize)) (*ConsideredCardType) = brp_CardType_Iso15693;
	if(!(*ConsideredCardType) && (*Iso14SelectFileCmdListLen || Iso14SelectFileCmdList || *Iso14HasFileLen || *Iso14HasApduTimeout)) (*ConsideredCardType) = brp_CardType_Iso14443aIntIndustry;
	brp_frame_write_int8(_frame, (unsigned)(*ConsideredCardType));
	unsigned char RFU[] = { 0x0 };
	brp_frame_write( _frame, RFU, 1);
	if((*ConsideredCardType) == (brp_CardType_MifareClassic)) {
		brp_frame_write_int8(_frame, (unsigned)(*HasMifareKey));
		if((*HasMifareKey) == (brp_VHL_Setup_HasMifareKey_Enabled)) {
			size_t _MifareKey_len_val = 6;
			size_t* MifareKey_len = &_MifareKey_len_val;
			brp_frame_write(_frame, (brp_buf)(*MifareKey), (*MifareKey_len));
		}
		brp_frame_write_int8(_frame, (unsigned)(*MifareHasAsKeyA));
		if((*MifareHasAsKeyA) == (brp_VHL_Setup_MifareHasAsKeyA_Enabled)) {
			brp_frame_write_int8(_frame, (unsigned)(*MifareAsKeyA));
		}
		brp_frame_write_int8(_frame, (unsigned)(*MifareHasMadId));
		if((*MifareHasMadId) == (brp_VHL_Setup_MifareHasMadId_Enabled)) {
			brp_frame_write_int16(_frame, (unsigned)(*MifareMadId));
		}
	}
	if((*ConsideredCardType) == (brp_CardType_MifareDesfire)) {
		brp_frame_write_int8(_frame, (unsigned)(*DesfireHasAppId));
		if((*DesfireHasAppId) == (brp_VHL_Setup_DesfireHasAppId_Enabled)) {
			brp_frame_write_int32(_frame, (unsigned)(*DesfireAppId));
		}
		brp_frame_write_int8(_frame, (unsigned)(*HasDesfireFileDesc));
		if((*HasDesfireFileDesc) == (brp_VHL_Setup_HasDesfireFileDesc_Enabled)) {
			unsigned _FileNo = (DesfireFileDesc)->FileNo;
			unsigned* FileNo = &_FileNo;
			brp_DesfireFileDescription_FileCommunicationSecurity _FileCommunicationSecurity = (DesfireFileDesc)->FileCommunicationSecurity;
			brp_DesfireFileDescription_FileCommunicationSecurity* FileCommunicationSecurity = &_FileCommunicationSecurity;
			brp_DesfireFileDescription_FileType _FileType = (DesfireFileDesc)->FileType;
			brp_DesfireFileDescription_FileType* FileType = &_FileType;
			unsigned _ReadKeyNo = (DesfireFileDesc)->ReadKeyNo;
			unsigned* ReadKeyNo = &_ReadKeyNo;
			unsigned _WriteKeyNo = (DesfireFileDesc)->WriteKeyNo;
			unsigned* WriteKeyNo = &_WriteKeyNo;
			unsigned _Offset = (DesfireFileDesc)->Offset;
			unsigned* Offset = &_Offset;
			unsigned _Length = (DesfireFileDesc)->Length;
			unsigned* Length = &_Length;
			unsigned _ReadKeyIdx = (DesfireFileDesc)->ReadKeyIdx;
			unsigned* ReadKeyIdx = &_ReadKeyIdx;
			unsigned _WriteKeyIdx = (DesfireFileDesc)->WriteKeyIdx;
			unsigned* WriteKeyIdx = &_WriteKeyIdx;
			unsigned _AccessRightsLowByte = (DesfireFileDesc)->AccessRightsLowByte;
			unsigned* AccessRightsLowByte = &_AccessRightsLowByte;
			unsigned _ChangeKeyIdx = (DesfireFileDesc)->ChangeKeyIdx;
			unsigned* ChangeKeyIdx = &_ChangeKeyIdx;
			unsigned _FileSize = (DesfireFileDesc)->FileSize;
			unsigned* FileSize = &_FileSize;
			unsigned _IsoFid = (DesfireFileDesc)->IsoFid;
			unsigned* IsoFid = &_IsoFid;
			brp_frame_write_int8(_frame, (unsigned)(*FileNo));
			brp_frame_write_int8(_frame, (unsigned)(*FileCommunicationSecurity));
			brp_frame_write_int8(_frame, (unsigned)(*FileType));
			brp_frame_write_int8(_frame, (unsigned)(*ReadKeyNo));
			brp_frame_write_int8(_frame, (unsigned)(*WriteKeyNo));
			brp_frame_write_int16(_frame, (unsigned)(*Offset));
			brp_frame_write_int16(_frame, (unsigned)(*Length));
			brp_frame_write_int8(_frame, (unsigned)(*ReadKeyIdx));
			brp_frame_write_int8(_frame, (unsigned)(*WriteKeyIdx));
			brp_frame_write_int8(_frame, (unsigned)(*AccessRightsLowByte));
			brp_frame_write_int8(_frame, (unsigned)(*ChangeKeyIdx));
			brp_frame_write_int16(_frame, (unsigned)(*FileSize));
			brp_frame_write_int16(_frame, (unsigned)(*IsoFid));
		}
		brp_frame_write_int8(_frame, (unsigned)(*DesfireKey_len));
		brp_frame_write(_frame, (brp_buf)(*DesfireKey), (*DesfireKey_len));
	}
	if((((*ConsideredCardType) == (brp_CardType_LEGICPrimeLegacy)) || ((*ConsideredCardType) == (brp_CardType_LEGICAdvantLegacy))) || (((*ConsideredCardType) == (brp_CardType_LEGICPrime)) || (((*ConsideredCardType) == (brp_CardType_LEGICAdvantIso14443a)) || ((*ConsideredCardType) == (brp_CardType_LEGICAdvantIso15693))))) {
		brp_frame_write_int8(_frame, (unsigned)(*LegicSegmentInfo_len));
		brp_frame_write(_frame, (brp_buf)(*LegicSegmentInfo), (*LegicSegmentInfo_len));
		brp_frame_write_int8(_frame, (unsigned)(*LegicHasEnStamp));
		if((*LegicHasEnStamp) == (brp_VHL_Setup_LegicHasEnStamp_Enabled)) {
			brp_frame_write_int8(_frame, (unsigned)(*LegicEnStamp));
		}
		brp_frame_write_int8(_frame, (unsigned)(*LegicHasAdrMode));
		if((*LegicHasAdrMode) == (brp_VHL_Setup_LegicHasAdrMode_Enabled)) {
			brp_frame_write_int8(_frame, (unsigned)(*LegicAdrMode));
		}
	}
	if((*ConsideredCardType) == (brp_CardType_Iso15693)) {
		brp_frame_write_int8(_frame, (unsigned)(*Iso15HasFirstBlock));
		if((*Iso15HasFirstBlock) == (brp_VHL_Setup_Iso15HasFirstBlock_Enabled)) {
			brp_frame_write_int8(_frame, (unsigned)(*Iso15FirstBlock));
		}
		brp_frame_write_int8(_frame, (unsigned)(*Iso15HasBlockCount));
		if((*Iso15HasBlockCount) == (brp_VHL_Setup_Iso15HasBlockCount_Enabled)) {
			brp_frame_write_int8(_frame, (unsigned)(*Iso15BlockCount));
		}
		brp_frame_write_int8(_frame, (unsigned)(*Iso15HasOptionFlag));
		if((*Iso15HasOptionFlag) == (brp_VHL_Setup_Iso15HasOptionFlag_Enabled)) {
			brp_frame_write_int8(_frame, (unsigned)(*Iso15OptionFlag));
		}
		brp_frame_write_int8(_frame, (unsigned)(*Iso15HasBlockSize));
		if((*Iso15HasBlockSize) == (brp_VHL_Setup_Iso15HasBlockSize_Enabled)) {
			brp_frame_write_int8(_frame, (unsigned)(*Iso15BlockSize));
		}
	}
	if((*ConsideredCardType) == (brp_CardType_Iso14443aIntIndustry)) {
		brp_frame_write_int8(_frame, (unsigned)(*Iso14SelectFileCmdListLen));
		brp_frame_write_int8(_frame, (unsigned)(*Iso14SelectFileCmdList_len));
		for(size_t _Iso14SelectFileCmdList_ndx = 0;_Iso14SelectFileCmdList_ndx < (*Iso14SelectFileCmdList_len);_Iso14SelectFileCmdList_ndx++) {
			brp_VHL_Setup_Iso14SelectFileCmdList_Entry _Iso14SelectFileCmdList_Entry = (*Iso14SelectFileCmdList)[_Iso14SelectFileCmdList_ndx];
			brp_VHL_Setup_Iso14SelectFileCmdList_Entry* Iso14SelectFileCmdList_Entry = &_Iso14SelectFileCmdList_Entry;
			brp_VHL_Setup_FileSpecifier _FileSpecifier = (Iso14SelectFileCmdList_Entry)->FileSpecifier;
			brp_VHL_Setup_FileSpecifier* FileSpecifier = &_FileSpecifier;
			brp_buf _Name = (Iso14SelectFileCmdList_Entry)->Name;
			brp_buf* Name = &_Name;
			size_t _Name_len = (Iso14SelectFileCmdList_Entry)->Name_len;
			size_t* Name_len = &_Name_len;
			brp_buf _Path = (Iso14SelectFileCmdList_Entry)->Path;
			brp_buf* Path = &_Path;
			size_t _Path_len = (Iso14SelectFileCmdList_Entry)->Path_len;
			size_t* Path_len = &_Path_len;
			brp_buf _ApduCommand = (Iso14SelectFileCmdList_Entry)->ApduCommand;
			brp_buf* ApduCommand = &_ApduCommand;
			size_t _ApduCommand_len = (Iso14SelectFileCmdList_Entry)->ApduCommand_len;
			size_t* ApduCommand_len = &_ApduCommand_len;
			int _autoset_FileSpecifier = 0;
			if(Name) _autoset_FileSpecifier++;
			if(Path) _autoset_FileSpecifier++;
			if(ApduCommand) _autoset_FileSpecifier++;
			if(!(*FileSpecifier) && _autoset_FileSpecifier > 1) return BRP_ERR_INVALID_API_CALL;
			if(!(*FileSpecifier) && (Name)) (*FileSpecifier) = brp_VHL_Setup_FileSpecifier_SelectByName;
			if(!(*FileSpecifier) && (Path)) (*FileSpecifier) = brp_VHL_Setup_FileSpecifier_SelectByPath;
			if(!(*FileSpecifier) && (ApduCommand)) (*FileSpecifier) = brp_VHL_Setup_FileSpecifier_SelectByAPDU;
			brp_frame_write_int8(_frame, (unsigned)(*FileSpecifier));
			if((*FileSpecifier) == (brp_VHL_Setup_FileSpecifier_SelectByName)) {
				brp_frame_write_int8(_frame, (unsigned)(*Name_len));
				brp_frame_write(_frame, (brp_buf)(*Name), (*Name_len));
			}
			if((*FileSpecifier) == (brp_VHL_Setup_FileSpecifier_SelectByPath)) {
				brp_frame_write_int8(_frame, (unsigned)(*Path_len));
				brp_frame_write(_frame, (brp_buf)(*Path), (*Path_len));
			}
			if((*FileSpecifier) == (brp_VHL_Setup_FileSpecifier_SelectByAPDU)) {
				brp_frame_write_int8(_frame, (unsigned)(*ApduCommand_len));
				brp_frame_write(_frame, (brp_buf)(*ApduCommand), (*ApduCommand_len));
			}
		}
		brp_frame_write_int8(_frame, (unsigned)(*Iso14HasFileLen));
		if((*Iso14HasFileLen) == (brp_VHL_Setup_Iso14HasFileLen_Enabled)) {
			brp_frame_write_int32(_frame, (unsigned)(*Iso14FileLen));
		}
		brp_frame_write_int8(_frame, (unsigned)(*Iso14HasApduTimeout));
		if((*Iso14HasApduTimeout) == (brp_VHL_Setup_Iso14HasApduTimeout_Enabled)) {
			brp_frame_write_int16(_frame, (unsigned)(*Iso14ApduTimeout));
		}
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_SetupMifare(brp_protocol protocol, bool _input_CustomKey, bool _input_KeyA, brp_buf _input_Key) {
#else
brp_errcode brp_VHL_SetupMifare(brp_VHL_SetupMifare_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_CustomKey = params.CustomKey;
	bool _input_KeyA = params.KeyA;
	brp_buf _input_Key = params.Key;
#endif
	bool* CustomKey = &_input_CustomKey;
	bool* KeyA = &_input_KeyA;
	brp_buf* Key = &_input_Key;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int32(_frame, 100);
	if(!(*CustomKey) && (Key)) (*CustomKey) = true;
	unsigned _bitmask_5501 = 0;
	_bitmask_5501 |= (*CustomKey & 0b1) << 1;
	_bitmask_5501 |= (*KeyA & 0b1) << 0;
	brp_frame_write_int8(_frame, (unsigned)_bitmask_5501);
	if(*CustomKey) {
		size_t _Key_len_val = 6;
		size_t* Key_len = &_Key_len_val;
		brp_frame_write(_frame, (brp_buf)(*Key), (*Key_len));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_SetupLegic(brp_protocol protocol, unsigned _input_StampLen, unsigned _input_SegmentID, brp_buf _input_Stamp, size_t _input_Stamp_len) {
#else
brp_errcode brp_VHL_SetupLegic(brp_VHL_SetupLegic_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_StampLen = params.StampLen;
	unsigned _input_SegmentID = params.SegmentID;
	brp_buf _input_Stamp = params.Stamp;
	size_t _input_Stamp_len = params.Stamp_len;
#endif
	unsigned* StampLen = &_input_StampLen;
	unsigned* SegmentID = &_input_SegmentID;
	brp_buf* Stamp = &_input_Stamp;
	size_t* Stamp_len = &_input_Stamp_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 9);
	brp_frame_write_int32(_frame, 100);
	if(!(*StampLen) && (*SegmentID)) (*StampLen) = 0;
	brp_frame_write_int8(_frame, (unsigned)(*StampLen));
	if((*StampLen) == (0)) {
		brp_frame_write_int8(_frame, (unsigned)(*SegmentID));
	}
	if((*StampLen) > (0)) {
		brp_frame_write(_frame, (brp_buf)(*Stamp), (*Stamp_len));
	}
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_SetupISO15(brp_protocol protocol, unsigned _input_FirstBlock, unsigned _input_BlockCount, bool _input_OptionFlag) {
#else
brp_errcode brp_VHL_SetupISO15(brp_VHL_SetupISO15_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_FirstBlock = params.FirstBlock;
	unsigned _input_BlockCount = params.BlockCount;
	bool _input_OptionFlag = params.OptionFlag;
#endif
	unsigned* FirstBlock = &_input_FirstBlock;
	unsigned* BlockCount = &_input_BlockCount;
	bool* OptionFlag = &_input_OptionFlag;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 10);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*FirstBlock));
	brp_frame_write_int8(_frame, (unsigned)(*BlockCount));
	brp_frame_write_int8(_frame, (unsigned)(*OptionFlag));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_CheckReconfigErr(brp_protocol protocol, bool* Failed) {
#else
brp_errcode brp_VHL_CheckReconfigErr(brp_VHL_CheckReconfigErr_t params) {
	brp_protocol protocol = params.protocol;
	bool* Failed = params.Failed;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	bool _tmp_Failed;
	if (Failed == NULL) Failed = &_tmp_Failed;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 11);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Failed) = (bool)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_ExchangeLongAPDU(brp_protocol protocol, brp_CardType _input_AssumedCardType, bool _input_Reset, bool _input_ContinueCmd, brp_buf _input_Cmd, size_t _input_Cmd_len, bool* ContinueResp, brp_buf* Resp, size_t* Resp_len, brp_mempool *mempool) {
#else
brp_errcode brp_VHL_ExchangeLongAPDU(brp_VHL_ExchangeLongAPDU_t params) {
	brp_protocol protocol = params.protocol;
	brp_CardType _input_AssumedCardType = params.AssumedCardType;
	bool _input_Reset = params.Reset;
	bool _input_ContinueCmd = params.ContinueCmd;
	brp_buf _input_Cmd = params.Cmd;
	size_t _input_Cmd_len = params.Cmd_len;
	bool* ContinueResp = params.ContinueResp;
	brp_buf* Resp = params.Resp;
	size_t* Resp_len = params.Resp_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_CardType* AssumedCardType = &_input_AssumedCardType;
	bool* Reset = &_input_Reset;
	bool* ContinueCmd = &_input_ContinueCmd;
	brp_buf* Cmd = &_input_Cmd;
	size_t* Cmd_len = &_input_Cmd_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Resp_len;
	if(Resp_len == NULL) Resp_len = &_Resp_len;
	bool _tmp_ContinueResp;
	if (ContinueResp == NULL) ContinueResp = &_tmp_ContinueResp;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 12);
	brp_frame_write_int32(_frame, 60000);
	brp_frame_write_int8(_frame, (unsigned)(*AssumedCardType));
	brp_frame_write_int8(_frame, (unsigned)(*Reset));
	brp_frame_write_int8(_frame, (unsigned)(*ContinueCmd));
	brp_frame_write_int16(_frame, (unsigned)(*Cmd_len));
	brp_frame_write(_frame, (brp_buf)(*Cmd), (*Cmd_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ContinueResp) = (bool)brp_frame_read_int8(&_reader);
	(*Resp_len) = brp_frame_read_int16(&_reader);
	if (Resp != NULL) {
		(*Resp) = (brp_buf)brp_mempool_create_buf(mempool, (*Resp_len));
		if((*Resp) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Resp), (*Resp_len));
	} else
		brp_frame_skip(&_reader, (*Resp_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_GetFileInfo(brp_protocol protocol, unsigned _input_Id, unsigned* Len, unsigned* BlockSize) {
#else
brp_errcode brp_VHL_GetFileInfo(brp_VHL_GetFileInfo_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Id = params.Id;
	unsigned* Len = params.Len;
	unsigned* BlockSize = params.BlockSize;
#endif
	unsigned* Id = &_input_Id;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_Len;
	if (Len == NULL) Len = &_tmp_Len;
	unsigned _tmp_BlockSize;
	if (BlockSize == NULL) BlockSize = &_tmp_BlockSize;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 13);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Id));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Len) = (unsigned)brp_frame_read_int16(&_reader);
	(*BlockSize) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_GetATR(brp_protocol protocol, brp_buf* ATR, size_t* ATR_len, brp_mempool *mempool) {
#else
brp_errcode brp_VHL_GetATR(brp_VHL_GetATR_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* ATR = params.ATR;
	size_t* ATR_len = params.ATR_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ATR_len;
	if(ATR_len == NULL) ATR_len = &_ATR_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 14);
	brp_frame_write_int32(_frame, 1000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ATR_len) = brp_frame_read_int8(&_reader);
	if (ATR != NULL) {
		(*ATR) = (brp_buf)brp_mempool_create_buf(mempool, (*ATR_len));
		if((*ATR) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ATR), (*ATR_len));
	} else
		brp_frame_skip(&_reader, (*ATR_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_Format(brp_protocol protocol, unsigned _input_Id) {
#else
brp_errcode brp_VHL_Format(brp_VHL_Format_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Id = params.Id;
#endif
	unsigned* Id = &_input_Id;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 15);
	brp_frame_write_int32(_frame, 4000);
	brp_frame_write_int8(_frame, (unsigned)(*Id));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_ResolveFilename(brp_protocol protocol, char* _input_FileName, unsigned* Id) {
#else
brp_errcode brp_VHL_ResolveFilename(brp_VHL_ResolveFilename_t params) {
	brp_protocol protocol = params.protocol;
	char* _input_FileName = params.FileName;
	unsigned* Id = params.Id;
#endif
	char** FileName = &_input_FileName;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_Id;
	if (Id == NULL) Id = &_tmp_Id;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int32(_frame, 100);
	size_t _FileName_len_val = strlen(*FileName);
	size_t* FileName_len = &_FileName_len_val;
	brp_frame_write_int8(_frame, (unsigned)(*FileName_len));
	brp_frame_write(_frame, (brp_buf)(*FileName), (*FileName_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Id) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_VHL_GetCardType(brp_protocol protocol, brp_CardType* SelectedCardType) {
#else
brp_errcode brp_VHL_GetCardType(brp_VHL_GetCardType_t params) {
	brp_protocol protocol = params.protocol;
	brp_CardType* SelectedCardType = params.SelectedCardType;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int8(_frame, 17);
	brp_frame_write_int32(_frame, 3000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	int _SelectedCardType_int_val = brp_frame_read_int8(&_reader);
	if (SelectedCardType != NULL) {
		if (brp_CardType_is_valid(_SelectedCardType_int_val))
			(*SelectedCardType) = (brp_CardType)_SelectedCardType_int_val;
		else
			(*SelectedCardType) = brp_CardType_undefined;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BALTECH_SDK_INTERNAL
#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PortConfig(brp_protocol protocol, unsigned _input_Port, brp_DHWCtrlLegacy_PortConfig_Mode _input_Mode) {
#else
brp_errcode brp_DHWCtrlLegacy_PortConfig(brp_DHWCtrlLegacy_PortConfig_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Port = params.Port;
	brp_DHWCtrlLegacy_PortConfig_Mode _input_Mode = params.Mode;
#endif
	unsigned* Port = &_input_Port;
	brp_DHWCtrlLegacy_PortConfig_Mode* Mode = &_input_Mode;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_frame_write_int8(_frame, (unsigned)(*Mode));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PortGet(brp_protocol protocol, unsigned _input_Port, bool* Level) {
#else
brp_errcode brp_DHWCtrlLegacy_PortGet(brp_DHWCtrlLegacy_PortGet_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Port = params.Port;
	bool* Level = params.Level;
#endif
	unsigned* Port = &_input_Port;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	bool _tmp_Level;
	if (Level == NULL) Level = &_tmp_Level;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 1);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Level) = (bool)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PortSet(brp_protocol protocol, unsigned _input_Port, bool _input_Level) {
#else
brp_errcode brp_DHWCtrlLegacy_PortSet(brp_DHWCtrlLegacy_PortSet_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Port = params.Port;
	bool _input_Level = params.Level;
#endif
	unsigned* Port = &_input_Port;
	bool* Level = &_input_Level;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 2);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_frame_write_int8(_frame, (unsigned)(*Level));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PortWait(brp_protocol protocol, unsigned _input_Port, bool _input_Level, unsigned _input_Timeout, unsigned* ReactionTime) {
#else
brp_errcode brp_DHWCtrlLegacy_PortWait(brp_DHWCtrlLegacy_PortWait_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Port = params.Port;
	bool _input_Level = params.Level;
	unsigned _input_Timeout = params.Timeout;
	unsigned* ReactionTime = params.ReactionTime;
#endif
	unsigned* Port = &_input_Port;
	bool* Level = &_input_Level;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_ReactionTime;
	if (ReactionTime == NULL) ReactionTime = &_tmp_ReactionTime;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 5);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_frame_write_int8(_frame, (unsigned)(*Level));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ReactionTime) = (unsigned)brp_frame_read_int16(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_GetResetCause(brp_protocol protocol, unsigned* ResetCause) {
#else
brp_errcode brp_DHWCtrlLegacy_GetResetCause(brp_DHWCtrlLegacy_GetResetCause_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* ResetCause = params.ResetCause;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_ResetCause;
	if (ResetCause == NULL) ResetCause = &_tmp_ResetCause;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 6);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ResetCause) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_APortMeasure(brp_protocol protocol, unsigned _input_Port, unsigned _input_Count, unsigned** Voltages, size_t* Voltages_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_APortMeasure(brp_DHWCtrlLegacy_APortMeasure_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Port = params.Port;
	unsigned _input_Count = params.Count;
	unsigned** Voltages = params.Voltages;
	size_t* Voltages_len = params.Voltages_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Port = &_input_Port;
	unsigned* Count = &_input_Count;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Voltages_len;
	if(Voltages_len == NULL) Voltages_len = &_Voltages_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 7);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_frame_write_int8(_frame, (unsigned)(*Count));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Voltages_len) = brp_frame_rest( & _reader);
	if (Voltages != NULL) {
		(*Voltages) = (unsigned*)brp_mempool_create_buf(mempool, 0);
		if((*Voltages) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _Voltages_ndx = 1;!(brp_frame_read_eof(&_reader) | brp_frame_read_err(&_reader));_Voltages_ndx++) {
		unsigned _Voltage;
		unsigned *Voltage = &_Voltage;
		(*Voltage) = (unsigned)brp_frame_read_int16(&_reader);
		if (Voltages != NULL) {
			(*Voltages) = (unsigned*)brp_mempool_resize_buf((brp_buf)(*Voltages), (_Voltages_ndx * sizeof(unsigned)));
			if((*Voltages) == NULL) return BRP_ERR_OUT_OF_MEMORY;
			(*Voltages)[_Voltages_ndx-1] = *Voltage;
		}
		(*Voltages_len) = _Voltages_ndx;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_SRAMTest(brp_protocol protocol, unsigned _input_SramSize, bool* Success) {
#else
brp_errcode brp_DHWCtrlLegacy_SRAMTest(brp_DHWCtrlLegacy_SRAMTest_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_SramSize = params.SramSize;
	bool* Success = params.Success;
#endif
	unsigned* SramSize = &_input_SramSize;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	bool _tmp_Success;
	if (Success == NULL) Success = &_tmp_Success;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 4);
	brp_frame_write_int32(_frame, 1000);
	brp_frame_write_int16(_frame, (unsigned)(*SramSize));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Success) = (bool)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_SetBaudrate(brp_protocol protocol, brp_Baudrate _input_NewBaudrate) {
#else
brp_errcode brp_DHWCtrlLegacy_SetBaudrate(brp_DHWCtrlLegacy_SetBaudrate_t params) {
	brp_protocol protocol = params.protocol;
	brp_Baudrate _input_NewBaudrate = params.NewBaudrate;
#endif
	brp_Baudrate* NewBaudrate = &_input_NewBaudrate;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 3);
	brp_frame_write_int32(_frame, 100);
	if (_input_NewBaudrate == 0) _input_NewBaudrate = (brp_Baudrate)1152;
	brp_frame_write_int16(_frame, (unsigned)(*NewBaudrate));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_MirrorData(brp_protocol protocol, brp_buf _input_Data, size_t _input_Data_len, brp_buf* MirroredData, size_t* MirroredData_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_MirrorData(brp_DHWCtrlLegacy_MirrorData_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
	brp_buf* MirroredData = params.MirroredData;
	size_t* MirroredData_len = params.MirroredData_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _MirroredData_len;
	if(MirroredData_len == NULL) MirroredData_len = &_MirroredData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 8);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*Data_len));
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*MirroredData_len) = brp_frame_read_int16(&_reader);
	if (MirroredData != NULL) {
		(*MirroredData) = (brp_buf)brp_mempool_create_buf(mempool, (*MirroredData_len));
		if((*MirroredData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*MirroredData), (*MirroredData_len));
	} else
		brp_frame_skip(&_reader, (*MirroredData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DispEnable(brp_protocol protocol, bool _input_Enable) {
#else
brp_errcode brp_DHWCtrlLegacy_DispEnable(brp_DHWCtrlLegacy_DispEnable_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_Enable = params.Enable;
#endif
	bool* Enable = &_input_Enable;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 16);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Enable));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DispBacklight(brp_protocol protocol, bool _input_Backlight) {
#else
brp_errcode brp_DHWCtrlLegacy_DispBacklight(brp_DHWCtrlLegacy_DispBacklight_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_Backlight = params.Backlight;
#endif
	bool* Backlight = &_input_Backlight;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 17);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Backlight));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DispColor(brp_protocol protocol, brp_DHWCtrlLegacy_DispColor_Color _input_Color) {
#else
brp_errcode brp_DHWCtrlLegacy_DispColor(brp_DHWCtrlLegacy_DispColor_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlLegacy_DispColor_Color _input_Color = params.Color;
#endif
	brp_DHWCtrlLegacy_DispColor_Color* Color = &_input_Color;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 18);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Color));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DispContrast(brp_protocol protocol, unsigned _input_Contrast) {
#else
brp_errcode brp_DHWCtrlLegacy_DispContrast(brp_DHWCtrlLegacy_DispContrast_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Contrast = params.Contrast;
#endif
	unsigned* Contrast = &_input_Contrast;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 19);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Contrast));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DispBox(brp_protocol protocol, unsigned _input_X, unsigned _input_Y, unsigned _input_Width, unsigned _input_Height) {
#else
brp_errcode brp_DHWCtrlLegacy_DispBox(brp_DHWCtrlLegacy_DispBox_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_X = params.X;
	unsigned _input_Y = params.Y;
	unsigned _input_Width = params.Width;
	unsigned _input_Height = params.Height;
#endif
	unsigned* X = &_input_X;
	unsigned* Y = &_input_Y;
	unsigned* Width = &_input_Width;
	unsigned* Height = &_input_Height;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 20);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*X));
	brp_frame_write_int8(_frame, (unsigned)(*Y));
	brp_frame_write_int8(_frame, (unsigned)(*Width));
	brp_frame_write_int8(_frame, (unsigned)(*Height));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Ser2Ctrl(brp_protocol protocol, unsigned _input_InterfaceID, bool _input_Enable, brp_Baudrate _input_NewBaudrate, brp_Parity _input_NewParity, unsigned _input_Stopbits) {
#else
brp_errcode brp_DHWCtrlLegacy_Ser2Ctrl(brp_DHWCtrlLegacy_Ser2Ctrl_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_InterfaceID = params.InterfaceID;
	bool _input_Enable = params.Enable;
	brp_Baudrate _input_NewBaudrate = params.NewBaudrate;
	brp_Parity _input_NewParity = params.NewParity;
	unsigned _input_Stopbits = params.Stopbits;
#endif
	unsigned* InterfaceID = &_input_InterfaceID;
	bool* Enable = &_input_Enable;
	brp_Baudrate* NewBaudrate = &_input_NewBaudrate;
	brp_Parity* NewParity = &_input_NewParity;
	unsigned* Stopbits = &_input_Stopbits;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 21);
	brp_frame_write_int32(_frame, 100);
	if (_input_NewBaudrate == 0) _input_NewBaudrate = (brp_Baudrate)1152;
	brp_frame_write_int8(_frame, (unsigned)(*InterfaceID));
	brp_frame_write_int8(_frame, (unsigned)(*Enable));
	brp_frame_write_int16(_frame, (unsigned)(*NewBaudrate));
	brp_frame_write_int8(_frame, (unsigned)(*NewParity));
	brp_frame_write_int8(_frame, (unsigned)(*Stopbits));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Ser2WriteRead(brp_protocol protocol, unsigned _input_MaxReadCount, unsigned _input_Timeout, brp_buf _input_WriteData, size_t _input_WriteData_len, brp_buf* ReadData, size_t* ReadData_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_Ser2WriteRead(brp_DHWCtrlLegacy_Ser2WriteRead_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_MaxReadCount = params.MaxReadCount;
	unsigned _input_Timeout = params.Timeout;
	brp_buf _input_WriteData = params.WriteData;
	size_t _input_WriteData_len = params.WriteData_len;
	brp_buf* ReadData = params.ReadData;
	size_t* ReadData_len = params.ReadData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* MaxReadCount = &_input_MaxReadCount;
	unsigned* Timeout = &_input_Timeout;
	brp_buf* WriteData = &_input_WriteData;
	size_t* WriteData_len = &_input_WriteData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ReadData_len;
	if(ReadData_len == NULL) ReadData_len = &_ReadData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 22);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*MaxReadCount));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_frame_write_int16(_frame, (unsigned)(*WriteData_len));
	brp_frame_write(_frame, (brp_buf)(*WriteData), (*WriteData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ReadData_len) = brp_frame_read_int16(&_reader);
	if (ReadData != NULL) {
		(*ReadData) = (brp_buf)brp_mempool_create_buf(mempool, (*ReadData_len));
		if((*ReadData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ReadData), (*ReadData_len));
	} else
		brp_frame_skip(&_reader, (*ReadData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Ser2Flush(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_Ser2Flush(brp_DHWCtrlLegacy_Ser2Flush_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 32);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Delay1ms(brp_protocol protocol, unsigned _input_Delay) {
#else
brp_errcode brp_DHWCtrlLegacy_Delay1ms(brp_DHWCtrlLegacy_Delay1ms_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Delay = params.Delay;
#endif
	unsigned* Delay = &_input_Delay;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 23);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*Delay));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Delay10us(brp_protocol protocol, unsigned _input_Delay) {
#else
brp_errcode brp_DHWCtrlLegacy_Delay10us(brp_DHWCtrlLegacy_Delay10us_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Delay = params.Delay;
#endif
	unsigned* Delay = &_input_Delay;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 24);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Delay));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PowermgrSuspend(brp_protocol protocol, unsigned _input_Delay, bool _input_KeyboardWakeup) {
#else
brp_errcode brp_DHWCtrlLegacy_PowermgrSuspend(brp_DHWCtrlLegacy_PowermgrSuspend_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Delay = params.Delay;
	bool _input_KeyboardWakeup = params.KeyboardWakeup;
#endif
	unsigned* Delay = &_input_Delay;
	bool* KeyboardWakeup = &_input_KeyboardWakeup;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 25);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*Delay));
	brp_frame_write_int8(_frame, (unsigned)(*KeyboardWakeup));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ScanMatrix(brp_protocol protocol, unsigned _input_Bitmask) {
#else
brp_errcode brp_DHWCtrlLegacy_ScanMatrix(brp_DHWCtrlLegacy_ScanMatrix_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Bitmask = params.Bitmask;
#endif
	unsigned* Bitmask = &_input_Bitmask;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 26);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Bitmask));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_GetReaderChipType(brp_protocol protocol, brp_DHWCtrlLegacy_GetReaderChipType_ChipType* ChipType) {
#else
brp_errcode brp_DHWCtrlLegacy_GetReaderChipType(brp_DHWCtrlLegacy_GetReaderChipType_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlLegacy_GetReaderChipType_ChipType* ChipType = params.ChipType;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 27);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	int _ChipType_int_val = brp_frame_read_int8(&_reader);
	if (! brp_DHWCtrlLegacy_GetReaderChipType_ChipType_is_valid(_ChipType_int_val))
		return BRP_ERR_PAYLOAD_FORMAT;
	if (ChipType != NULL)
		(*ChipType) = (brp_DHWCtrlLegacy_GetReaderChipType_ChipType)_ChipType_int_val;
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_SelectAntenna(brp_protocol protocol, unsigned _input_Ant) {
#else
brp_errcode brp_DHWCtrlLegacy_SelectAntenna(brp_DHWCtrlLegacy_SelectAntenna_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Ant = params.Ant;
#endif
	unsigned* Ant = &_input_Ant;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 28);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Ant));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_GetSamType(brp_protocol protocol, brp_DHWCtrlLegacy_GetSamType_ChipType* ChipType) {
#else
brp_errcode brp_DHWCtrlLegacy_GetSamType(brp_DHWCtrlLegacy_GetSamType_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlLegacy_GetSamType_ChipType* ChipType = params.ChipType;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 29);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	int _ChipType_int_val = brp_frame_read_int8(&_reader);
	if (! brp_DHWCtrlLegacy_GetSamType_ChipType_is_valid(_ChipType_int_val))
		return BRP_ERR_PAYLOAD_FORMAT;
	if (ChipType != NULL)
		(*ChipType) = (brp_DHWCtrlLegacy_GetSamType_ChipType)_ChipType_int_val;
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_HfAcquire(brp_protocol protocol, brp_DHWCtrlLegacy_HfAcquire_ModuleId _input_ModuleId) {
#else
brp_errcode brp_DHWCtrlLegacy_HfAcquire(brp_DHWCtrlLegacy_HfAcquire_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlLegacy_HfAcquire_ModuleId _input_ModuleId = params.ModuleId;
#endif
	brp_DHWCtrlLegacy_HfAcquire_ModuleId* ModuleId = &_input_ModuleId;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 30);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*ModuleId));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_EepromWrite(brp_protocol protocol, unsigned _input_Address, brp_buf _input_Data, size_t _input_Data_len) {
#else
brp_errcode brp_DHWCtrlLegacy_EepromWrite(brp_DHWCtrlLegacy_EepromWrite_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
	brp_buf _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
#endif
	unsigned* Address = &_input_Address;
	brp_buf* Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 33);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*Address));
	brp_frame_write_int16(_frame, (unsigned)(*Data_len));
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DataflashGetSize(brp_protocol protocol, unsigned _input_Device, unsigned* PageCount, unsigned* PageSize) {
#else
brp_errcode brp_DHWCtrlLegacy_DataflashGetSize(brp_DHWCtrlLegacy_DataflashGetSize_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Device = params.Device;
	unsigned* PageCount = params.PageCount;
	unsigned* PageSize = params.PageSize;
#endif
	unsigned* Device = &_input_Device;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_PageCount;
	if (PageCount == NULL) PageCount = &_tmp_PageCount;
	unsigned _tmp_PageSize;
	if (PageSize == NULL) PageSize = &_tmp_PageSize;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 34);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Device));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*PageCount) = (unsigned)brp_frame_read_int16(&_reader);
	(*PageSize) = (unsigned)brp_frame_read_int16(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DataflashErasePages(brp_protocol protocol, unsigned _input_Device, unsigned _input_StartPage, unsigned _input_Len) {
#else
brp_errcode brp_DHWCtrlLegacy_DataflashErasePages(brp_DHWCtrlLegacy_DataflashErasePages_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Device = params.Device;
	unsigned _input_StartPage = params.StartPage;
	unsigned _input_Len = params.Len;
#endif
	unsigned* Device = &_input_Device;
	unsigned* StartPage = &_input_StartPage;
	unsigned* Len = &_input_Len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 35);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Device));
	brp_frame_write_int16(_frame, (unsigned)(*StartPage));
	brp_frame_write_int16(_frame, (unsigned)(*Len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DataflashRead(brp_protocol protocol, unsigned _input_Device, unsigned _input_Page, unsigned _input_StartAdr, unsigned _input_Len, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_DataflashRead(brp_DHWCtrlLegacy_DataflashRead_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Device = params.Device;
	unsigned _input_Page = params.Page;
	unsigned _input_StartAdr = params.StartAdr;
	unsigned _input_Len = params.Len;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Device = &_input_Device;
	unsigned* Page = &_input_Page;
	unsigned* StartAdr = &_input_StartAdr;
	unsigned* Len = &_input_Len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 36);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Device));
	brp_frame_write_int16(_frame, (unsigned)(*Page));
	brp_frame_write_int16(_frame, (unsigned)(*StartAdr));
	brp_frame_write_int16(_frame, (unsigned)(*Len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int16(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_DataflashWrite(brp_protocol protocol, unsigned _input_Device, unsigned _input_Mode, unsigned _input_Page, unsigned _input_StartAdr, brp_buf _input_Data, size_t _input_Data_len) {
#else
brp_errcode brp_DHWCtrlLegacy_DataflashWrite(brp_DHWCtrlLegacy_DataflashWrite_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Device = params.Device;
	unsigned _input_Mode = params.Mode;
	unsigned _input_Page = params.Page;
	unsigned _input_StartAdr = params.StartAdr;
	brp_buf _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
#endif
	unsigned* Device = &_input_Device;
	unsigned* Mode = &_input_Mode;
	unsigned* Page = &_input_Page;
	unsigned* StartAdr = &_input_StartAdr;
	brp_buf* Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 37);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Device));
	brp_frame_write_int8(_frame, (unsigned)(*Mode));
	brp_frame_write_int16(_frame, (unsigned)(*Page));
	brp_frame_write_int16(_frame, (unsigned)(*StartAdr));
	brp_frame_write_int16(_frame, (unsigned)(*Data_len));
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_EepromRead(brp_protocol protocol, unsigned _input_StartAdr, unsigned _input_Len, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_EepromRead(brp_DHWCtrlLegacy_EepromRead_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_StartAdr = params.StartAdr;
	unsigned _input_Len = params.Len;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* StartAdr = &_input_StartAdr;
	unsigned* Len = &_input_Len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 38);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*StartAdr));
	brp_frame_write_int16(_frame, (unsigned)(*Len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int16(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_SecurityAndConfigReset(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_SecurityAndConfigReset(brp_DHWCtrlLegacy_SecurityAndConfigReset_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 39);
	brp_frame_write_int32(_frame, 10000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PulseGenerate(brp_protocol protocol, unsigned _input_Port, unsigned _input_Frequency) {
#else
brp_errcode brp_DHWCtrlLegacy_PulseGenerate(brp_DHWCtrlLegacy_PulseGenerate_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Port = params.Port;
	unsigned _input_Frequency = params.Frequency;
#endif
	unsigned* Port = &_input_Port;
	unsigned* Frequency = &_input_Frequency;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 40);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Port));
	brp_frame_write_int16(_frame, (unsigned)(*Frequency));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitSer2(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitSer2(brp_DHWCtrlLegacy_InitSer2_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 49);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitRtc(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitRtc(brp_DHWCtrlLegacy_InitRtc_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 50);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitLcdDrv(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitLcdDrv(brp_DHWCtrlLegacy_InitLcdDrv_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 51);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitRc(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitRc(brp_DHWCtrlLegacy_InitRc_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 52);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitMf(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitMf(brp_DHWCtrlLegacy_InitMf_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 53);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitIso14A(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitIso14A(brp_DHWCtrlLegacy_InitIso14A_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 54);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitIso14B(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitIso14B(brp_DHWCtrlLegacy_InitIso14B_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 55);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitIso15(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitIso15(brp_DHWCtrlLegacy_InitIso15_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 56);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitLg(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitLg(brp_DHWCtrlLegacy_InitLg_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 57);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitLga(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitLga(brp_DHWCtrlLegacy_InitLga_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 58);
	brp_frame_write_int32(_frame, 3000);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitDf(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitDf(brp_DHWCtrlLegacy_InitDf_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 59);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitRc125(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitRc125(brp_DHWCtrlLegacy_InitRc125_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 60);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitCc(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitCc(brp_DHWCtrlLegacy_InitCc_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 61);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitUsbHost(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitUsbHost(brp_DHWCtrlLegacy_InitUsbHost_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 62);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitNic(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitNic(brp_DHWCtrlLegacy_InitNic_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 63);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_BohEnable(brp_protocol protocol, bool _input_Enable, bool _input_Bug6WorkaroundEnabled) {
#else
brp_errcode brp_DHWCtrlLegacy_BohEnable(brp_DHWCtrlLegacy_BohEnable_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_Enable = params.Enable;
	bool _input_Bug6WorkaroundEnabled = params.Bug6WorkaroundEnabled;
#endif
	bool* Enable = &_input_Enable;
	bool* Bug6WorkaroundEnabled = &_input_Bug6WorkaroundEnabled;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 65);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Enable));
	brp_frame_write_int8(_frame, (unsigned)(*Bug6WorkaroundEnabled));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_NicEnable(brp_protocol protocol, bool _input_Enable) {
#else
brp_errcode brp_DHWCtrlLegacy_NicEnable(brp_DHWCtrlLegacy_NicEnable_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_Enable = params.Enable;
#endif
	bool* Enable = &_input_Enable;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 66);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Enable));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_NicGetChipType(brp_protocol protocol, brp_buf* ChipType, size_t* ChipType_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_NicGetChipType(brp_DHWCtrlLegacy_NicGetChipType_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* ChipType = params.ChipType;
	size_t* ChipType_len = params.ChipType_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ChipType_len;
	if(ChipType_len == NULL) ChipType_len = &_ChipType_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 67);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ChipType_len) = brp_frame_read_int8(&_reader);
	if (ChipType != NULL) {
		(*ChipType) = (brp_buf)brp_mempool_create_buf(mempool, (*ChipType_len));
		if((*ChipType) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ChipType), (*ChipType_len));
	} else
		brp_frame_skip(&_reader, (*ChipType_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_NicGetLinkStatus(brp_protocol protocol, unsigned* LinkStatus) {
#else
brp_errcode brp_DHWCtrlLegacy_NicGetLinkStatus(brp_DHWCtrlLegacy_NicGetLinkStatus_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* LinkStatus = params.LinkStatus;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_LinkStatus;
	if (LinkStatus == NULL) LinkStatus = &_tmp_LinkStatus;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 68);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LinkStatus) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_NicSend(brp_protocol protocol, brp_buf _input_SendData, size_t _input_SendData_len) {
#else
brp_errcode brp_DHWCtrlLegacy_NicSend(brp_DHWCtrlLegacy_NicSend_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_SendData = params.SendData;
	size_t _input_SendData_len = params.SendData_len;
#endif
	brp_buf* SendData = &_input_SendData;
	size_t* SendData_len = &_input_SendData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 69);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*SendData_len));
	brp_frame_write(_frame, (brp_buf)(*SendData), (*SendData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_NicReceive(brp_protocol protocol, unsigned _input_Timeout, brp_buf* RecvData, size_t* RecvData_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_NicReceive(brp_DHWCtrlLegacy_NicReceive_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Timeout = params.Timeout;
	brp_buf* RecvData = params.RecvData;
	size_t* RecvData_len = params.RecvData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _RecvData_len;
	if(RecvData_len == NULL) RecvData_len = &_RecvData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 70);
	brp_frame_write_int32(_frame, 1000);
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*RecvData_len) = brp_frame_read_int16(&_reader);
	if (RecvData != NULL) {
		(*RecvData) = (brp_buf)brp_mempool_create_buf(mempool, (*RecvData_len));
		if((*RecvData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*RecvData), (*RecvData_len));
	} else
		brp_frame_skip(&_reader, (*RecvData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_NicSetMAC(brp_protocol protocol, brp_buf _input_MAC) {
#else
brp_errcode brp_DHWCtrlLegacy_NicSetMAC(brp_DHWCtrlLegacy_NicSetMAC_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_MAC = params.MAC;
#endif
	brp_buf* MAC = &_input_MAC;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 71);
	brp_frame_write_int32(_frame, 100);
	size_t _MAC_len_val = 6;
	size_t* MAC_len = &_MAC_len_val;
	brp_frame_write(_frame, (brp_buf)(*MAC), (*MAC_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ApspiSetSpeed(brp_protocol protocol, unsigned _input_Speed) {
#else
brp_errcode brp_DHWCtrlLegacy_ApspiSetSpeed(brp_DHWCtrlLegacy_ApspiSetSpeed_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Speed = params.Speed;
#endif
	unsigned* Speed = &_input_Speed;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 80);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*Speed));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ApspiEnable(brp_protocol protocol, bool _input_Enable) {
#else
brp_errcode brp_DHWCtrlLegacy_ApspiEnable(brp_DHWCtrlLegacy_ApspiEnable_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_Enable = params.Enable;
#endif
	bool* Enable = &_input_Enable;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 81);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Enable));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ApspiSingleSend(brp_protocol protocol, unsigned _input_CmdCode, unsigned _input_Address, unsigned _input_CmdData, unsigned _input_Delay) {
#else
brp_errcode brp_DHWCtrlLegacy_ApspiSingleSend(brp_DHWCtrlLegacy_ApspiSingleSend_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_CmdCode = params.CmdCode;
	unsigned _input_Address = params.Address;
	unsigned _input_CmdData = params.CmdData;
	unsigned _input_Delay = params.Delay;
#endif
	unsigned* CmdCode = &_input_CmdCode;
	unsigned* Address = &_input_Address;
	unsigned* CmdData = &_input_CmdData;
	unsigned* Delay = &_input_Delay;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 82);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*CmdCode));
	brp_frame_write_int16(_frame, (unsigned)(*Address));
	brp_frame_write_int8(_frame, (unsigned)(*CmdData));
	brp_frame_write_int16(_frame, (unsigned)(*Delay));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ApspiSingleRecv(brp_protocol protocol, unsigned _input_CmdCode, unsigned _input_Address, unsigned* CmdData) {
#else
brp_errcode brp_DHWCtrlLegacy_ApspiSingleRecv(brp_DHWCtrlLegacy_ApspiSingleRecv_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_CmdCode = params.CmdCode;
	unsigned _input_Address = params.Address;
	unsigned* CmdData = params.CmdData;
#endif
	unsigned* CmdCode = &_input_CmdCode;
	unsigned* Address = &_input_Address;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_CmdData;
	if (CmdData == NULL) CmdData = &_tmp_CmdData;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 83);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*CmdCode));
	brp_frame_write_int16(_frame, (unsigned)(*Address));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*CmdData) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ApspiAlternateSend(brp_protocol protocol, unsigned _input_CmdCodeA, unsigned _input_CmdCodeB, unsigned _input_Address, brp_buf _input_CmdData, size_t _input_CmdData_len, unsigned _input_Delay) {
#else
brp_errcode brp_DHWCtrlLegacy_ApspiAlternateSend(brp_DHWCtrlLegacy_ApspiAlternateSend_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_CmdCodeA = params.CmdCodeA;
	unsigned _input_CmdCodeB = params.CmdCodeB;
	unsigned _input_Address = params.Address;
	brp_buf _input_CmdData = params.CmdData;
	size_t _input_CmdData_len = params.CmdData_len;
	unsigned _input_Delay = params.Delay;
#endif
	unsigned* CmdCodeA = &_input_CmdCodeA;
	unsigned* CmdCodeB = &_input_CmdCodeB;
	unsigned* Address = &_input_Address;
	brp_buf* CmdData = &_input_CmdData;
	size_t* CmdData_len = &_input_CmdData_len;
	unsigned* Delay = &_input_Delay;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 84);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*CmdCodeA));
	brp_frame_write_int8(_frame, (unsigned)(*CmdCodeB));
	brp_frame_write_int16(_frame, (unsigned)(*Address));
	brp_frame_write_int16(_frame, (unsigned)(*CmdData_len));
	brp_frame_write(_frame, (brp_buf)(*CmdData), (*CmdData_len));
	brp_frame_write_int16(_frame, (unsigned)(*Delay));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_ApspiAlternateRecv(brp_protocol protocol, unsigned _input_CmdCodeA, unsigned _input_CmdCodeB, unsigned _input_Address, unsigned _input_CmdDataLen, brp_buf* CmdData, size_t* CmdData_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_ApspiAlternateRecv(brp_DHWCtrlLegacy_ApspiAlternateRecv_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_CmdCodeA = params.CmdCodeA;
	unsigned _input_CmdCodeB = params.CmdCodeB;
	unsigned _input_Address = params.Address;
	unsigned _input_CmdDataLen = params.CmdDataLen;
	brp_buf* CmdData = params.CmdData;
	size_t* CmdData_len = params.CmdData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* CmdCodeA = &_input_CmdCodeA;
	unsigned* CmdCodeB = &_input_CmdCodeB;
	unsigned* Address = &_input_Address;
	unsigned* CmdDataLen = &_input_CmdDataLen;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _CmdData_len;
	if(CmdData_len == NULL) CmdData_len = &_CmdData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 85);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*CmdCodeA));
	brp_frame_write_int8(_frame, (unsigned)(*CmdCodeB));
	brp_frame_write_int16(_frame, (unsigned)(*Address));
	brp_frame_write_int16(_frame, (unsigned)(*CmdDataLen));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*CmdData_len) = brp_frame_read_int16(&_reader);
	if (CmdData != NULL) {
		(*CmdData) = (brp_buf)brp_mempool_create_buf(mempool, (*CmdData_len));
		if((*CmdData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*CmdData), (*CmdData_len));
	} else
		brp_frame_skip(&_reader, (*CmdData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiEnable(brp_protocol protocol, bool _input_Enable) {
#else
brp_errcode brp_DHWCtrlLegacy_PdiEnable(brp_DHWCtrlLegacy_PdiEnable_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_Enable = params.Enable;
#endif
	bool* Enable = &_input_Enable;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 86);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Enable));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiEraseDevice(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_PdiEraseDevice(brp_DHWCtrlLegacy_PdiEraseDevice_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 87);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiReadFlash(brp_protocol protocol, unsigned _input_Adr, unsigned _input_ReadLen, brp_buf* ReadData, size_t* ReadData_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_PdiReadFlash(brp_DHWCtrlLegacy_PdiReadFlash_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Adr = params.Adr;
	unsigned _input_ReadLen = params.ReadLen;
	brp_buf* ReadData = params.ReadData;
	size_t* ReadData_len = params.ReadData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Adr = &_input_Adr;
	unsigned* ReadLen = &_input_ReadLen;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ReadData_len;
	if(ReadData_len == NULL) ReadData_len = &_ReadData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 88);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*Adr));
	brp_frame_write_int16(_frame, (unsigned)(*ReadLen));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ReadData_len) = brp_frame_read_int16(&_reader);
	if (ReadData != NULL) {
		(*ReadData) = (brp_buf)brp_mempool_create_buf(mempool, (*ReadData_len));
		if((*ReadData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ReadData), (*ReadData_len));
	} else
		brp_frame_skip(&_reader, (*ReadData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiEraseFlashPage(brp_protocol protocol, unsigned _input_Adr) {
#else
brp_errcode brp_DHWCtrlLegacy_PdiEraseFlashPage(brp_DHWCtrlLegacy_PdiEraseFlashPage_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Adr = params.Adr;
#endif
	unsigned* Adr = &_input_Adr;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 89);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*Adr));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiWriteFlashPage(brp_protocol protocol, unsigned _input_Adr, brp_buf _input_WriteData, size_t _input_WriteData_len) {
#else
brp_errcode brp_DHWCtrlLegacy_PdiWriteFlashPage(brp_DHWCtrlLegacy_PdiWriteFlashPage_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Adr = params.Adr;
	brp_buf _input_WriteData = params.WriteData;
	size_t _input_WriteData_len = params.WriteData_len;
#endif
	unsigned* Adr = &_input_Adr;
	brp_buf* WriteData = &_input_WriteData;
	size_t* WriteData_len = &_input_WriteData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 90);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*Adr));
	brp_frame_write_int16(_frame, (unsigned)(*WriteData_len));
	brp_frame_write(_frame, (brp_buf)(*WriteData), (*WriteData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiProgramFlashPage(brp_protocol protocol, unsigned _input_Adr) {
#else
brp_errcode brp_DHWCtrlLegacy_PdiProgramFlashPage(brp_DHWCtrlLegacy_PdiProgramFlashPage_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Adr = params.Adr;
#endif
	unsigned* Adr = &_input_Adr;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 91);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*Adr));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiReadEeprom(brp_protocol protocol, unsigned _input_Adr, unsigned _input_ReadLen, brp_buf* ReadData, size_t* ReadData_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_PdiReadEeprom(brp_DHWCtrlLegacy_PdiReadEeprom_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Adr = params.Adr;
	unsigned _input_ReadLen = params.ReadLen;
	brp_buf* ReadData = params.ReadData;
	size_t* ReadData_len = params.ReadData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Adr = &_input_Adr;
	unsigned* ReadLen = &_input_ReadLen;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ReadData_len;
	if(ReadData_len == NULL) ReadData_len = &_ReadData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 92);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*Adr));
	brp_frame_write_int16(_frame, (unsigned)(*ReadLen));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ReadData_len) = brp_frame_read_int16(&_reader);
	if (ReadData != NULL) {
		(*ReadData) = (brp_buf)brp_mempool_create_buf(mempool, (*ReadData_len));
		if((*ReadData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ReadData), (*ReadData_len));
	} else
		brp_frame_skip(&_reader, (*ReadData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiProgramEepromPage(brp_protocol protocol, unsigned _input_Adr, brp_buf _input_WriteData, size_t _input_WriteData_len) {
#else
brp_errcode brp_DHWCtrlLegacy_PdiProgramEepromPage(brp_DHWCtrlLegacy_PdiProgramEepromPage_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Adr = params.Adr;
	brp_buf _input_WriteData = params.WriteData;
	size_t _input_WriteData_len = params.WriteData_len;
#endif
	unsigned* Adr = &_input_Adr;
	brp_buf* WriteData = &_input_WriteData;
	size_t* WriteData_len = &_input_WriteData_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 93);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*Adr));
	brp_frame_write_int16(_frame, (unsigned)(*WriteData_len));
	brp_frame_write(_frame, (brp_buf)(*WriteData), (*WriteData_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiReadFuses(brp_protocol protocol, unsigned _input_Adr, unsigned _input_ReadLen, brp_buf* ReadData, size_t* ReadData_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_PdiReadFuses(brp_DHWCtrlLegacy_PdiReadFuses_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Adr = params.Adr;
	unsigned _input_ReadLen = params.ReadLen;
	brp_buf* ReadData = params.ReadData;
	size_t* ReadData_len = params.ReadData_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Adr = &_input_Adr;
	unsigned* ReadLen = &_input_ReadLen;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ReadData_len;
	if(ReadData_len == NULL) ReadData_len = &_ReadData_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 94);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*Adr));
	brp_frame_write_int16(_frame, (unsigned)(*ReadLen));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ReadData_len) = brp_frame_read_int16(&_reader);
	if (ReadData != NULL) {
		(*ReadData) = (brp_buf)brp_mempool_create_buf(mempool, (*ReadData_len));
		if((*ReadData) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ReadData), (*ReadData_len));
	} else
		brp_frame_skip(&_reader, (*ReadData_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_PdiWriteFuse(brp_protocol protocol, unsigned _input_Adr, unsigned _input_Fuse) {
#else
brp_errcode brp_DHWCtrlLegacy_PdiWriteFuse(brp_DHWCtrlLegacy_PdiWriteFuse_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Adr = params.Adr;
	unsigned _input_Fuse = params.Fuse;
#endif
	unsigned* Adr = &_input_Adr;
	unsigned* Fuse = &_input_Fuse;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 95);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*Adr));
	brp_frame_write_int8(_frame, (unsigned)(*Fuse));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_FlashGetPageSize(brp_protocol protocol, unsigned* PageSize) {
#else
brp_errcode brp_DHWCtrlLegacy_FlashGetPageSize(brp_DHWCtrlLegacy_FlashGetPageSize_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* PageSize = params.PageSize;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_PageSize;
	if (PageSize == NULL) PageSize = &_tmp_PageSize;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 96);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*PageSize) = (unsigned)brp_frame_read_int16(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_FlashErasePage(brp_protocol protocol, unsigned _input_StartAdr, unsigned _input_Len) {
#else
brp_errcode brp_DHWCtrlLegacy_FlashErasePage(brp_DHWCtrlLegacy_FlashErasePage_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_StartAdr = params.StartAdr;
	unsigned _input_Len = params.Len;
#endif
	unsigned* StartAdr = &_input_StartAdr;
	unsigned* Len = &_input_Len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 97);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*StartAdr));
	brp_frame_write_int32(_frame, (unsigned)(*Len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_FlashRead(brp_protocol protocol, unsigned _input_StartAdr, unsigned _input_Len, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_FlashRead(brp_DHWCtrlLegacy_FlashRead_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_StartAdr = params.StartAdr;
	unsigned _input_Len = params.Len;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* StartAdr = &_input_StartAdr;
	unsigned* Len = &_input_Len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 98);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*StartAdr));
	brp_frame_write_int16(_frame, (unsigned)(*Len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int16(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_FlashWritePage(brp_protocol protocol, unsigned _input_StartAdr, brp_buf _input_Data, size_t _input_Data_len) {
#else
brp_errcode brp_DHWCtrlLegacy_FlashWritePage(brp_DHWCtrlLegacy_FlashWritePage_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_StartAdr = params.StartAdr;
	brp_buf _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
#endif
	unsigned* StartAdr = &_input_StartAdr;
	brp_buf* Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 99);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*StartAdr));
	brp_frame_write_int16(_frame, (unsigned)(*Data_len));
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_FlashProgramPage(brp_protocol protocol, unsigned _input_StartAdr) {
#else
brp_errcode brp_DHWCtrlLegacy_FlashProgramPage(brp_DHWCtrlLegacy_FlashProgramPage_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_StartAdr = params.StartAdr;
#endif
	unsigned* StartAdr = &_input_StartAdr;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 100);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*StartAdr));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_RegisterRead(brp_protocol protocol, unsigned _input_RegAdr, unsigned* RegValue) {
#else
brp_errcode brp_DHWCtrlLegacy_RegisterRead(brp_DHWCtrlLegacy_RegisterRead_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_RegAdr = params.RegAdr;
	unsigned* RegValue = params.RegValue;
#endif
	unsigned* RegAdr = &_input_RegAdr;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_RegValue;
	if (RegValue == NULL) RegValue = &_tmp_RegValue;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 101);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*RegAdr));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*RegValue) = (unsigned)brp_frame_read_int32(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_RegisterWrite(brp_protocol protocol, unsigned _input_RegAdr, unsigned _input_RegValue) {
#else
brp_errcode brp_DHWCtrlLegacy_RegisterWrite(brp_DHWCtrlLegacy_RegisterWrite_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_RegAdr = params.RegAdr;
	unsigned _input_RegValue = params.RegValue;
#endif
	unsigned* RegAdr = &_input_RegAdr;
	unsigned* RegValue = &_input_RegValue;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 102);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int32(_frame, (unsigned)(*RegAdr));
	brp_frame_write_int32(_frame, (unsigned)(*RegValue));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_AesWrapKey(brp_protocol protocol, brp_DHWCtrlLegacy_AesWrapKey_WrappedKeyNr _input_WrappedKeyNr, brp_buf _input_Key, size_t _input_Key_len, brp_buf* WrappedKey, size_t* WrappedKey_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_AesWrapKey(brp_DHWCtrlLegacy_AesWrapKey_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlLegacy_AesWrapKey_WrappedKeyNr _input_WrappedKeyNr = params.WrappedKeyNr;
	brp_buf _input_Key = params.Key;
	size_t _input_Key_len = params.Key_len;
	brp_buf* WrappedKey = params.WrappedKey;
	size_t* WrappedKey_len = params.WrappedKey_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_DHWCtrlLegacy_AesWrapKey_WrappedKeyNr* WrappedKeyNr = &_input_WrappedKeyNr;
	brp_buf* Key = &_input_Key;
	size_t* Key_len = &_input_Key_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _WrappedKey_len;
	if(WrappedKey_len == NULL) WrappedKey_len = &_WrappedKey_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 104);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*WrappedKeyNr));
	brp_frame_write_int8(_frame, (unsigned)(*Key_len));
	brp_frame_write(_frame, (brp_buf)(*Key), (*Key_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*WrappedKey_len) = brp_frame_read_int8(&_reader);
	if (WrappedKey != NULL) {
		(*WrappedKey) = (brp_buf)brp_mempool_create_buf(mempool, (*WrappedKey_len));
		if((*WrappedKey) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*WrappedKey), (*WrappedKey_len));
	} else
		brp_frame_skip(&_reader, (*WrappedKey_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_AesEncrypt(brp_protocol protocol, brp_DHWCtrlLegacy_AesEncrypt_WrappedKeyNr _input_WrappedKeyNr, brp_buf _input_Block, size_t _input_Block_len, brp_buf _input_Key, size_t _input_Key_len, brp_buf* EncBlock, size_t* EncBlock_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_AesEncrypt(brp_DHWCtrlLegacy_AesEncrypt_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlLegacy_AesEncrypt_WrappedKeyNr _input_WrappedKeyNr = params.WrappedKeyNr;
	brp_buf _input_Block = params.Block;
	size_t _input_Block_len = params.Block_len;
	brp_buf _input_Key = params.Key;
	size_t _input_Key_len = params.Key_len;
	brp_buf* EncBlock = params.EncBlock;
	size_t* EncBlock_len = params.EncBlock_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_DHWCtrlLegacy_AesEncrypt_WrappedKeyNr* WrappedKeyNr = &_input_WrappedKeyNr;
	brp_buf* Block = &_input_Block;
	size_t* Block_len = &_input_Block_len;
	brp_buf* Key = &_input_Key;
	size_t* Key_len = &_input_Key_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _EncBlock_len;
	if(EncBlock_len == NULL) EncBlock_len = &_EncBlock_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 105);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*WrappedKeyNr));
	brp_frame_write_int8(_frame, (unsigned)(*Block_len));
	brp_frame_write(_frame, (brp_buf)(*Block), (*Block_len));
	brp_frame_write_int8(_frame, (unsigned)(*Key_len));
	brp_frame_write(_frame, (brp_buf)(*Key), (*Key_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*EncBlock_len) = brp_frame_read_int8(&_reader);
	if (EncBlock != NULL) {
		(*EncBlock) = (brp_buf)brp_mempool_create_buf(mempool, (*EncBlock_len));
		if((*EncBlock) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*EncBlock), (*EncBlock_len));
	} else
		brp_frame_skip(&_reader, (*EncBlock_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_AesDecrypt(brp_protocol protocol, brp_DHWCtrlLegacy_AesDecrypt_WrappedKeyNr _input_WrappedKeyNr, brp_buf _input_EncBlock, size_t _input_EncBlock_len, brp_buf _input_Key, size_t _input_Key_len, brp_buf* Block, size_t* Block_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_AesDecrypt(brp_DHWCtrlLegacy_AesDecrypt_t params) {
	brp_protocol protocol = params.protocol;
	brp_DHWCtrlLegacy_AesDecrypt_WrappedKeyNr _input_WrappedKeyNr = params.WrappedKeyNr;
	brp_buf _input_EncBlock = params.EncBlock;
	size_t _input_EncBlock_len = params.EncBlock_len;
	brp_buf _input_Key = params.Key;
	size_t _input_Key_len = params.Key_len;
	brp_buf* Block = params.Block;
	size_t* Block_len = params.Block_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_DHWCtrlLegacy_AesDecrypt_WrappedKeyNr* WrappedKeyNr = &_input_WrappedKeyNr;
	brp_buf* EncBlock = &_input_EncBlock;
	size_t* EncBlock_len = &_input_EncBlock_len;
	brp_buf* Key = &_input_Key;
	size_t* Key_len = &_input_Key_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Block_len;
	if(Block_len == NULL) Block_len = &_Block_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 106);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*WrappedKeyNr));
	brp_frame_write_int8(_frame, (unsigned)(*EncBlock_len));
	brp_frame_write(_frame, (brp_buf)(*EncBlock), (*EncBlock_len));
	brp_frame_write_int8(_frame, (unsigned)(*Key_len));
	brp_frame_write(_frame, (brp_buf)(*Key), (*Key_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Block_len) = brp_frame_read_int8(&_reader);
	if (Block != NULL) {
		(*Block) = (brp_buf)brp_mempool_create_buf(mempool, (*Block_len));
		if((*Block) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Block), (*Block_len));
	} else
		brp_frame_skip(&_reader, (*Block_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_GetPlatformId2(brp_protocol protocol, unsigned** HWCIdLst, size_t* HWCIdLst_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_GetPlatformId2(brp_DHWCtrlLegacy_GetPlatformId2_t params) {
	brp_protocol protocol = params.protocol;
	unsigned** HWCIdLst = params.HWCIdLst;
	size_t* HWCIdLst_len = params.HWCIdLst_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _HWCIdLst_len;
	if(HWCIdLst_len == NULL) HWCIdLst_len = &_HWCIdLst_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 123);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*HWCIdLst_len) = brp_frame_read_int8(&_reader);
	if (HWCIdLst != NULL) {
		(*HWCIdLst) = (unsigned*)brp_mempool_create_buf(mempool, (*HWCIdLst_len) * sizeof(unsigned));
		if((*HWCIdLst) == NULL) return BRP_ERR_OUT_OF_MEMORY;
	}
	for(size_t _HWCIdLst_ndx = 0;(_HWCIdLst_ndx < (*HWCIdLst_len)) & !brp_frame_read_err(&_reader);_HWCIdLst_ndx++) {
		unsigned _HWCId;
		unsigned *HWCId = &_HWCId;
		(*HWCId) = (unsigned)brp_frame_read_int16(&_reader);
		if (HWCIdLst != NULL)
			(*HWCIdLst)[_HWCIdLst_ndx] = *HWCId;
	}
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_GetProdLoader(brp_protocol protocol, unsigned* LoaderBaudrate) {
#else
brp_errcode brp_DHWCtrlLegacy_GetProdLoader(brp_DHWCtrlLegacy_GetProdLoader_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* LoaderBaudrate = params.LoaderBaudrate;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	unsigned _tmp_LoaderBaudrate;
	if (LoaderBaudrate == NULL) LoaderBaudrate = &_tmp_LoaderBaudrate;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 124);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*LoaderBaudrate) = (unsigned)brp_frame_read_int8(&_reader);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_StartProdLoader(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_StartProdLoader(brp_DHWCtrlLegacy_StartProdLoader_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 125);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Run(brp_protocol protocol, brp_buf _input_CommandList, size_t _input_CommandList_len, unsigned* Status, brp_buf* Response, size_t* Response_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_Run(brp_DHWCtrlLegacy_Run_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_CommandList = params.CommandList;
	size_t _input_CommandList_len = params.CommandList_len;
	unsigned* Status = params.Status;
	brp_buf* Response = params.Response;
	size_t* Response_len = params.Response_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* CommandList = &_input_CommandList;
	size_t* CommandList_len = &_input_CommandList_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Response_len;
	if(Response_len == NULL) Response_len = &_Response_len;
	unsigned _tmp_Status;
	if (Status == NULL) Status = &_tmp_Status;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 127);
	brp_frame_write_int32(_frame, 20000);
	brp_frame_write(_frame, (brp_buf)(*CommandList), (*CommandList_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Status) = (unsigned)brp_frame_read_int8(&_reader);
	(*Response_len) = brp_frame_read_int16(&_reader);
	if (Response != NULL) {
		(*Response) = (brp_buf)brp_mempool_create_buf(mempool, (*Response_len));
		if((*Response) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Response), (*Response_len));
	} else
		brp_frame_skip(&_reader, (*Response_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_GetStartupRun(brp_protocol protocol, unsigned* Status, brp_buf* Response, size_t* Response_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_GetStartupRun(brp_DHWCtrlLegacy_GetStartupRun_t params) {
	brp_protocol protocol = params.protocol;
	unsigned* Status = params.Status;
	brp_buf* Response = params.Response;
	size_t* Response_len = params.Response_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Response_len;
	if(Response_len == NULL) Response_len = &_Response_len;
	unsigned _tmp_Status;
	if (Status == NULL) Status = &_tmp_Status;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 126);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Status) = (unsigned)brp_frame_read_int8(&_reader);
	(*Response_len) = brp_frame_read_int16(&_reader);
	if (Response != NULL) {
		(*Response) = (brp_buf)brp_mempool_create_buf(mempool, (*Response_len));
		if((*Response) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Response), (*Response_len));
	} else
		brp_frame_skip(&_reader, (*Response_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_InitBgm(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_InitBgm(brp_DHWCtrlLegacy_InitBgm_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 128);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_BgmExec(brp_protocol protocol, brp_buf _input_Cmd, size_t _input_Cmd_len, unsigned _input_Timeout, brp_buf* Rsp, size_t* Rsp_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_BgmExec(brp_DHWCtrlLegacy_BgmExec_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf _input_Cmd = params.Cmd;
	size_t _input_Cmd_len = params.Cmd_len;
	unsigned _input_Timeout = params.Timeout;
	brp_buf* Rsp = params.Rsp;
	size_t* Rsp_len = params.Rsp_len;
	brp_mempool *mempool = params.mempool;
#endif
	brp_buf* Cmd = &_input_Cmd;
	size_t* Cmd_len = &_input_Cmd_len;
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Rsp_len;
	if(Rsp_len == NULL) Rsp_len = &_Rsp_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 129);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*Cmd_len));
	brp_frame_write(_frame, (brp_buf)(*Cmd), (*Cmd_len));
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Rsp_len) = brp_frame_read_int8(&_reader);
	if (Rsp != NULL) {
		(*Rsp) = (brp_buf)brp_mempool_create_buf(mempool, (*Rsp_len));
		if((*Rsp) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Rsp), (*Rsp_len));
	} else
		brp_frame_skip(&_reader, (*Rsp_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Sm4x00BootloaderStart(brp_protocol protocol, brp_buf* BootloaderString, size_t* BootloaderString_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_Sm4x00BootloaderStart(brp_DHWCtrlLegacy_Sm4x00BootloaderStart_t params) {
	brp_protocol protocol = params.protocol;
	brp_buf* BootloaderString = params.BootloaderString;
	size_t* BootloaderString_len = params.BootloaderString_len;
	brp_mempool *mempool = params.mempool;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _BootloaderString_len;
	if(BootloaderString_len == NULL) BootloaderString_len = &_BootloaderString_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 130);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*BootloaderString_len) = brp_frame_read_int8(&_reader);
	if (BootloaderString != NULL) {
		(*BootloaderString) = (brp_buf)brp_mempool_create_buf(mempool, (*BootloaderString_len));
		if((*BootloaderString) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*BootloaderString), (*BootloaderString_len));
	} else
		brp_frame_skip(&_reader, (*BootloaderString_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Sm4x00EraseFlash(brp_protocol protocol) {
#else
brp_errcode brp_DHWCtrlLegacy_Sm4x00EraseFlash(brp_DHWCtrlLegacy_Sm4x00EraseFlash_t params) {
	brp_protocol protocol = params.protocol;
#endif
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 131);
	brp_frame_write_int32(_frame, 100);
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Sm4x00WaitForFlashErase(brp_protocol protocol, unsigned _input_Timeout, brp_buf* EraseResponse, size_t* EraseResponse_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_Sm4x00WaitForFlashErase(brp_DHWCtrlLegacy_Sm4x00WaitForFlashErase_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Timeout = params.Timeout;
	brp_buf* EraseResponse = params.EraseResponse;
	size_t* EraseResponse_len = params.EraseResponse_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _EraseResponse_len;
	if(EraseResponse_len == NULL) EraseResponse_len = &_EraseResponse_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 132);
	brp_frame_write_int32(_frame, 1500);
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*EraseResponse_len) = brp_frame_read_int8(&_reader);
	if (EraseResponse != NULL) {
		(*EraseResponse) = (brp_buf)brp_mempool_create_buf(mempool, (*EraseResponse_len));
		if((*EraseResponse) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*EraseResponse), (*EraseResponse_len));
	} else
		brp_frame_skip(&_reader, (*EraseResponse_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Sm4x00ProgramBlock(brp_protocol protocol, bool _input_IsLast, brp_buf _input_FwBlock, size_t _input_FwBlock_len, brp_buf* ProgramResponse, size_t* ProgramResponse_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_Sm4x00ProgramBlock(brp_DHWCtrlLegacy_Sm4x00ProgramBlock_t params) {
	brp_protocol protocol = params.protocol;
	bool _input_IsLast = params.IsLast;
	brp_buf _input_FwBlock = params.FwBlock;
	size_t _input_FwBlock_len = params.FwBlock_len;
	brp_buf* ProgramResponse = params.ProgramResponse;
	size_t* ProgramResponse_len = params.ProgramResponse_len;
	brp_mempool *mempool = params.mempool;
#endif
	bool* IsLast = &_input_IsLast;
	brp_buf* FwBlock = &_input_FwBlock;
	size_t* FwBlock_len = &_input_FwBlock_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _ProgramResponse_len;
	if(ProgramResponse_len == NULL) ProgramResponse_len = &_ProgramResponse_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 133);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int8(_frame, (unsigned)(*IsLast));
	brp_frame_write_int8(_frame, (unsigned)(*FwBlock_len));
	brp_frame_write(_frame, (brp_buf)(*FwBlock), (*FwBlock_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*ProgramResponse_len) = brp_frame_read_int8(&_reader);
	if (ProgramResponse != NULL) {
		(*ProgramResponse) = (brp_buf)brp_mempool_create_buf(mempool, (*ProgramResponse_len));
		if((*ProgramResponse) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*ProgramResponse), (*ProgramResponse_len));
	} else
		brp_frame_skip(&_reader, (*ProgramResponse_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_BgmRead(brp_protocol protocol, unsigned _input_Timeout, brp_buf* Rsp, size_t* Rsp_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_BgmRead(brp_DHWCtrlLegacy_BgmRead_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Timeout = params.Timeout;
	brp_buf* Rsp = params.Rsp;
	size_t* Rsp_len = params.Rsp_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Timeout = &_input_Timeout;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Rsp_len;
	if(Rsp_len == NULL) Rsp_len = &_Rsp_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 134);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*Timeout));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Rsp_len) = brp_frame_read_int16(&_reader);
	if (Rsp != NULL) {
		(*Rsp) = (brp_buf)brp_mempool_create_buf(mempool, (*Rsp_len));
		if((*Rsp) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Rsp), (*Rsp_len));
	} else
		brp_frame_skip(&_reader, (*Rsp_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Rc5180EepromRead(brp_protocol protocol, unsigned _input_Address, unsigned _input_Length, brp_buf* Data, size_t* Data_len, brp_mempool *mempool) {
#else
brp_errcode brp_DHWCtrlLegacy_Rc5180EepromRead(brp_DHWCtrlLegacy_Rc5180EepromRead_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
	unsigned _input_Length = params.Length;
	brp_buf* Data = params.Data;
	size_t* Data_len = params.Data_len;
	brp_mempool *mempool = params.mempool;
#endif
	unsigned* Address = &_input_Address;
	unsigned* Length = &_input_Length;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	if(mempool == NULL) {
		mempool = &protocol->mempool;
		brp_mempool_free(mempool);
	}
	size_t _Data_len;
	if(Data_len == NULL) Data_len = &_Data_len;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 144);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*Address));
	brp_frame_write_int8(_frame, (unsigned)(*Length));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	(*Data_len) = brp_frame_read_int8(&_reader);
	if (Data != NULL) {
		(*Data) = (brp_buf)brp_mempool_create_buf(mempool, (*Data_len));
		if((*Data) == NULL) return BRP_ERR_OUT_OF_MEMORY;
		brp_frame_read(&_reader, (brp_buf)(*Data), (*Data_len));
	} else
		brp_frame_skip(&_reader, (*Data_len));
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#ifdef BRP_SUPPORT_LEGACY_METHODS
brp_errcode brp_DHWCtrlLegacy_Rc5180EepromWrite(brp_protocol protocol, unsigned _input_Address, brp_buf _input_Data, size_t _input_Data_len) {
#else
brp_errcode brp_DHWCtrlLegacy_Rc5180EepromWrite(brp_DHWCtrlLegacy_Rc5180EepromWrite_t params) {
	brp_protocol protocol = params.protocol;
	unsigned _input_Address = params.Address;
	brp_buf _input_Data = params.Data;
	size_t _input_Data_len = params.Data_len;
#endif
	unsigned* Address = &_input_Address;
	brp_buf* Data = &_input_Data;
	size_t* Data_len = &_input_Data_len;
	if(protocol == NULL) return BRP_ERR_INVALID_API_CALL;
	brp_frame _frame = &protocol->send_frame;;
	brp_frame_write_start(_frame);
	brp_frame_write_int8(_frame, 0);
	brp_frame_write_int8(_frame, 224);
	brp_frame_write_int8(_frame, 145);
	brp_frame_write_int32(_frame, 100);
	brp_frame_write_int16(_frame, (unsigned)(*Address));
	brp_frame_write_int8(_frame, (unsigned)(*Data_len));
	brp_frame_write(_frame, (brp_buf)(*Data), (*Data_len));
	brp_errcode _status_code = brp_send_frame(protocol);
	if (_status_code != BRP_OK) return _status_code;
	
	_status_code = brp_recv_any_frame(protocol, BRP_INFINITE);
	if(_status_code != BRP_OK) return _status_code;
	brp_frame_reader _reader;
	brp_frame_read_start(&_reader, &protocol->recv_frame);
	if(brp_frame_read_err(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	if(!brp_frame_read_eof(&_reader)) return BRP_ERR_PAYLOAD_FORMAT;
	return BRP_OK;
}

#endif  // BALTECH_SDK_INTERNAL