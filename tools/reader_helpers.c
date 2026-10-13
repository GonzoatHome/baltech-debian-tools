#include "reader_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reader_report_error(const char *action, brp_errcode error)
{
	char *name = brp_map_errcode(error);
	if (name != NULL)
		fprintf(stderr, "%s: %s (0x%08X)\n", action, name, error);
	else
		fprintf(stderr, "%s: SDK error 0x%08X\n", action, error);
}

int reader_enumerate_devices(reader_entry **entries, size_t *entry_count)
{
	brp_ioiter iterator = brp_ioiter_create_usb_hid();
	reader_entry *items = NULL;
	size_t count = 0;
	brp_errcode error = BRP_OK;

	if (iterator == NULL)
	{
		fprintf(stderr, "Unable to create USB/HID device iterator.\n");
		return 0;
	}

	while (1)
	{
		brp_protocol io_protocol = NULL;
		char *interface_name = NULL;
		char *friendly_name = NULL;
		char *end = NULL;
		struct brp_frame_t instance_id;
		long long serial;
		reader_entry *resized;

		error = brp_ioiter_next(iterator, &io_protocol);
		if (error != BRP_OK || io_protocol == NULL)
			break;

		brp_frame_init(&instance_id);
		error = brp_get_io_id(io_protocol, &interface_name, &instance_id);
		if (error == BRP_OK && instance_id.ptr != NULL)
		{
			serial = strtoll((char *)instance_id.ptr, &end, 10);
			if (end != (char *)instance_id.ptr && *end == '\0')
			{
				resized = realloc(items, (count + 1) * sizeof(*items));
				if (resized == NULL)
				{
					brp_frame_deinit(&instance_id);
					brp_destroy(io_protocol);
					brp_ioiter_destroy(&iterator);
					free(items);
					fprintf(stderr, "Out of memory while listing readers.\n");
					return 0;
				}
				items = resized;
				items[count].serial = serial;
				if (brp_get_friendly_name(io_protocol, &friendly_name) == BRP_OK && friendly_name != NULL)
					snprintf(items[count].name, sizeof(items[count].name), "%s", friendly_name);
				else
					snprintf(items[count].name, sizeof(items[count].name), "BALTECH Reader");
				count++;
			}
		}
		brp_frame_deinit(&instance_id);
		brp_destroy(io_protocol);
		if (error != BRP_OK)
			break;
	}
	brp_ioiter_destroy(&iterator);
	if (error != BRP_OK)
	{
		reader_report_error("Enumerating USB/HID readers", error);
		free(items);
		return 0;
	}

	*entries = items;
	*entry_count = count;
	return 1;
}

void reader_free_devices(reader_entry *entries)
{
	free(entries);
}

int reader_select_serial(long long requested_serial, long long *selected_serial)
{
	reader_entry *entries = NULL;
	size_t count = 0;
	size_t index;
	size_t selected_index = 0;
	char input[64];
	char *end = NULL;
	unsigned long long selection;

	if (selected_serial == NULL || !reader_enumerate_devices(&entries, &count))
		return 0;
	if (count == 0)
	{
		fprintf(stderr, "No BALTECH USB/HID readers found.\n");
		free(entries);
		return 0;
	}

	printf("BALTECH USB/HID readers:\n");
	for (index = 0; index < count; index++)
		printf("  [%zu] %s | SN %08lld\n", index, entries[index].name, entries[index].serial);

	if (requested_serial != 0)
	{
		for (index = 0; index < count; index++)
		{
			if (entries[index].serial == requested_serial)
			{
				*selected_serial = requested_serial;
				free(entries);
				return 1;
			}
		}
		fprintf(stderr, "Reader with serial number %lld was not found.\n", requested_serial);
		free(entries);
		return 0;
	}

	if (count == 1)
	{
		selected_index = 0;
	}
	else
	{
		printf("Select reader number: ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			free(entries);
			return 0;
		}
		selection = strtoull(input, &end, 10);
		if (end == input || selection >= count)
		{
			fprintf(stderr, "Invalid reader selection.\n");
			free(entries);
			return 0;
		}
		selected_index = (size_t)selection;
	}

	*selected_serial = entries[selected_index].serial;
	free(entries);
	return 1;
}

brp_protocol reader_open(long long serial)
{
	brp_protocol reader = brp_create();
	brp_protocol io_protocol;
	brp_errcode error;

	if (reader == NULL)
	{
		fprintf(stderr, "Unable to create BRP protocol.\n");
		return NULL;
	}
	io_protocol = brp_create_usb_hid(serial);
	if (io_protocol == NULL)
	{
		fprintf(stderr, "Unable to create USB/HID protocol.\n");
		brp_destroy(reader);
		return NULL;
	}
	error = brp_set_io(reader, io_protocol);
	if (error != BRP_OK)
	{
		reader_report_error("Setting USB/HID protocol", error);
		brp_destroy(reader);
		return NULL;
	}
	error = brp_open(reader);
	if (error != BRP_OK)
	{
		reader_report_error("Opening reader", error);
		brp_destroy(reader);
		return NULL;
	}
	return reader;
}

int reader_print_info(brp_protocol reader)
{
	char *info = NULL;
	brp_errcode error = brp_Sys_GetInfo((brp_Sys_GetInfo_t){reader, &info, NULL});
	if (error != BRP_OK)
	{
		reader_report_error("Reading reader information", error);
		return 0;
	}
	printf("Firmware: %s\n", info != NULL ? info : "unknown");
	return 1;
}

void reader_close(reader_handle reader)
{
	if (reader != NULL)
		brp_destroy(reader);
}

static void append_boot_status(char *buffer, size_t buffer_size, size_t *used, const char *description)
{
	int written;
	if (*used >= buffer_size)
		return;
	written = snprintf(buffer + *used, buffer_size - *used, "%s%s",
		*used == 0 ? "" : "\n", description);
	if (written < 0)
		return;
	if ((size_t)written >= buffer_size - *used)
		*used = buffer_size - 1;
	else
		*used += (size_t)written;
}

unsigned reader_read_details(reader_handle reader, reader_details *details)
{
	char *firmware = NULL;
	char *config_id = NULL;
	char *config_name = NULL;
	char *device_settings_id = NULL;
	char *device_settings_name = NULL;
	char *part_number = NULL;
	char *hardware_revision = NULL;
	brp_Sys_GetBootStatus_BootStatus boot_status = {0};
	brp_errcode error;
	char faults[sizeof(details->health)] = "";
	char rfid_faults[sizeof(details->rfid_status)] = "";
	size_t used = 0;
	size_t rfid_used = 0;

	if (reader == NULL || details == NULL)
		return BRP_ERR_INVALID_API_CALL;
	memset(details, 0, sizeof(*details));
	error = brp_Sys_GetInfo((brp_Sys_GetInfo_t){reader, &firmware, NULL});
	if (error != BRP_OK)
		return error;
	snprintf(details->firmware, sizeof(details->firmware), "%s", firmware != NULL ? firmware : "Unavailable");

	if (brp_Sys_CfgGetId((brp_Sys_CfgGetId_t){reader, &config_id, &config_name, NULL}) == BRP_OK)
		snprintf(details->configuration, sizeof(details->configuration), "%s %s",
			config_name != NULL ? config_name : "", config_id != NULL ? config_id : "");
	else
		snprintf(details->configuration, sizeof(details->configuration), "Unavailable");

	if (brp_Sys_GetPartNumber((brp_Sys_GetPartNumber_t){reader, &part_number, &hardware_revision, NULL}) == BRP_OK)
	{
		snprintf(details->part_number, sizeof(details->part_number), "%s", part_number != NULL ? part_number : "Unavailable");
		snprintf(details->hardware_revision, sizeof(details->hardware_revision), "%s", hardware_revision != NULL ? hardware_revision : "");
	}
	else
		snprintf(details->part_number, sizeof(details->part_number), "Unavailable");

	error = brp_Sys_GetBootStatus((brp_Sys_GetBootStatus_t){reader, &boot_status});
	if (error != BRP_OK)
		return error;
	if (brp_Sys_CfgGetDeviceSettingsId((brp_Sys_CfgGetDeviceSettingsId_t){reader, &device_settings_id, &device_settings_name, NULL}) == BRP_OK)
		snprintf(details->device_settings, sizeof(details->device_settings), "%s %s",
			device_settings_name != NULL ? device_settings_name : "", device_settings_id != NULL ? device_settings_id : "");
	else
		snprintf(details->device_settings, sizeof(details->device_settings), "Same as RFID configuration or unavailable");

	if (boot_status.NewerReaderChipFirmware) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Reader chip firmware was not accepted (version protection)");
	if (boot_status.UnexpectedRebootsLegacy) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Unexpected reboot recorded (legacy status)");
	if (boot_status.FactorySettings) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Factory settings restore error");
	if (boot_status.ConfigurationInconsistent) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Configuration inconsistent");
	if (boot_status.FirmwareVersionBlocked || boot_status.FirmwareVersionBlockedLegacy) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Firmware version blocked");
	if (boot_status.Bluetooth) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Bluetooth hardware fault");
	if (boot_status.WiFi) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Wi-Fi hardware fault");
	if (boot_status.Tamper) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Tamper alarm fault");
	if (boot_status.BatteryManagement) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Battery-management fault");
	if (boot_status.Keyboard) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Keyboard hardware fault");
	if (boot_status.Display) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Display hardware fault");
	if (boot_status.ConfCardPresented) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "ConfigCard reconfiguration error");
	if (boot_status.Ethernet) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Ethernet hardware fault");
	if (boot_status.ExtendedLED) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "RGB LED hardware fault");
	if (boot_status.HWoptions) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Hardware options error");
	if (boot_status.RTC) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Real-time clock fault");
	if (boot_status.Dataflash) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Dataflash fault");
	if (boot_status.Configuration) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Configuration fault");
	if (boot_status.CorruptFirmware) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Firmware corrupt");
	if (boot_status.IncompleteFirmware) append_boot_status(details->boot_status, sizeof(details->boot_status), &used, "Firmware incomplete");
	if (details->boot_status[0] == '\0')
		snprintf(details->boot_status, sizeof(details->boot_status), "All reported boot-status flags are clear");
	used = 0;
	if (boot_status.Configuration) used += (size_t)snprintf(faults + used, sizeof(faults) - used, "Configuration; ");
	if (boot_status.ConfigurationInconsistent) used += (size_t)snprintf(faults + used, sizeof(faults) - used, "Configuration inconsistent; ");
	if (boot_status.CorruptFirmware) used += (size_t)snprintf(faults + used, sizeof(faults) - used, "Firmware corrupt; ");
	if (boot_status.IncompleteFirmware) used += (size_t)snprintf(faults + used, sizeof(faults) - used, "Firmware incomplete; ");
	if (boot_status.Rf125kHz)
	{
		used += (size_t)snprintf(faults + used, sizeof(faults) - used, "125 kHz RF; ");
		rfid_used += (size_t)snprintf(rfid_faults + rfid_used, sizeof(rfid_faults) - rfid_used, "125 kHz; ");
	}
	if (boot_status.Rf13MHz || boot_status.Rf13MHzLegacy)
	{
		used += (size_t)snprintf(faults + used, sizeof(faults) - used, "13.56 MHz RF; ");
		rfid_used += (size_t)snprintf(rfid_faults + rfid_used, sizeof(rfid_faults) - rfid_used, "13.56 MHz; ");
	}
	if (boot_status.Rf13MHzLegic)
	{
		used += (size_t)snprintf(faults + used, sizeof(faults) - used, "LEGIC RF; ");
		rfid_used += (size_t)snprintf(rfid_faults + rfid_used, sizeof(rfid_faults) - rfid_used, "LEGIC; ");
	}
	if (used == 0)
		snprintf(details->health, sizeof(details->health), "Healthy");
	else
	{
		if (used >= 2)
			faults[used - 2] = '\0';
		snprintf(details->health, sizeof(details->health), "%s", faults);
	}
	if (rfid_used == 0)
		snprintf(details->rfid_status, sizeof(details->rfid_status), "No RF fault flags");
	else
	{
		if (rfid_used >= 2)
			rfid_faults[rfid_used - 2] = '\0';
		snprintf(details->rfid_status, sizeof(details->rfid_status), "%s", rfid_faults);
	}
	return BRP_OK;
}

unsigned reader_read_features(reader_handle reader, char *output, size_t output_size)
{
	typedef struct
	{
		unsigned id;
		const char *name;
	} feature_name;
	static const feature_name names[] = {
		{1, "Green LED"}, {2, "Red LED"}, {3, "Beeper"}, {4, "Relay"},
		{5, "13.56 MHz RFID"}, {6, "125 kHz RFID"}, {7, "ISO 14443A"},
		{8, "ISO 14443A UID only"}, {9, "ISO 14443B"}, {10, "ISO 14443B UID only"},
		{11, "ISO 15693"}, {12, "ISO 15693 UID only"}, {13, "FeliCa"}, {14, "FeliCa UID only"},
		{15, "LEGIC"}, {16, "SAM"}, {17, "SAM AV2"}, {18, "HID SAM"}, {19, "PicoPass"},
		{35, "MIFARE Classic"}, {36, "MIFARE Plus EV0"}, {37, "MIFARE DESFire EV1"},
		{38, "SRIX"}, {39, "Jewel"}, {40, "ISO 14443-4"}, {41, "Interindustry"},
		{42, "EM4205"}, {43, "EM4100"}, {44, "EM4450"}, {45, "Farpointe Pyramid"},
		{46, "HID Prox32"}, {47, "HID AWID"}, {48, "HID Prox"}, {49, "HID ioProx"},
		{50, "Indala"}, {51, "Keri"}, {52, "Indala Secure"}, {53, "QuadraKey"},
		{54, "SecuraKey"}, {55, "G-Prox"}, {56, "HITAG 1 / S"}, {57, "HITAG 2 Manchester"},
		{58, "HITAG 2 Biphase"}, {59, "Blue LED"}, {60, "Cotag"}, {61, "PicoPass UID only"},
		{62, "IDTECK"}, {63, "Tamper alarm"},
		{64, "HF baud rate limited to 106 kbps (LEGIC)"},
		{65, "HF baud rate limited to 212 kbps (LEGIC)"},
		{66, "HF baud rate limited to 424 kbps (LEGIC)"},
		{67, "Firmware loader"},
		{68, "Firmware upload via serial BRP"}, {69, "AES host encryption"},
		{70, "PKI host encryption"}, {71, "HID iCLASS"}, {72, "HID iCLASS SR"},
		{73, "HID iCLASS SE / Seos"}, {74, "MIFARE Ultralight"}, {75, "ISO 14443-4 card emulation"},
		{76, "MIFARE DESFire EV2"}, {77, "MIFARE Plus EV1"}, {78, "SAM AV3"},
		{79, "OSDP 2.17"}, {80, "Bluetooth LE"}, {81, "Customizable RGB LED"},
		{82, "Limited RGB LED"}, {83, "BEC2 upload"}, {84, "MIFARE DESFire EV3"},
		{85, "Mobile ID"}, {86, "Mobile card emulation"}, {87, "BLE HCI"}, {88, "BLE peripheral"}
	};
	brp_FeatureID *features = NULL;
	brp_FeatureID max_feature = 0;
	size_t count = 0;
	size_t used = 0;
	size_t index;
	brp_errcode error;

	if (reader == NULL || output == NULL || output_size == 0)
		return BRP_ERR_INVALID_API_CALL;
	output[0] = '\0';
	error = brp_Sys_GetFeatures((brp_Sys_GetFeatures_t){reader, &features, &count, &max_feature, NULL});
	if (error != BRP_OK)
		return error;
	for (index = 0; index < count && used < output_size; index++)
	{
		unsigned feature_id = (unsigned)features[index];
		const char *feature_label = "Unknown feature";
		size_t name_index;
		int written;
		for (name_index = 0; name_index < sizeof(names) / sizeof(names[0]); name_index++)
		{
			if (names[name_index].id == feature_id)
			{
				feature_label = names[name_index].name;
				break;
			}
		}
		written = snprintf(output + used, output_size - used, "%3u  %s\n", feature_id, feature_label);
		if (written < 0)
			break;
		if ((size_t)written >= output_size - used)
		{
			used = output_size - 1;
			break;
		}
		used += (size_t)written;
	}
	return BRP_OK;
}

static const char *reader_card_type_name(brp_CardType card_type)
{
	switch (card_type)
	{
	case brp_CardType_MifareClassic: return "MIFARE Classic";
	case brp_CardType_Iso14443aGeneric: return "ISO 14443A";
	case brp_CardType_MifareUltraLight: return "MIFARE Ultralight";
	case brp_CardType_MifareDesfire: return "MIFARE DESFire";
	case brp_CardType_LEGICAdvantIso14443a: return "LEGIC advant (ISO 14443A)";
	case brp_CardType_LEGICPrimeLegacy: return "LEGIC Prime";
	case brp_CardType_Iso15693: return "ISO 15693";
	case brp_CardType_IClass: return "iCLASS";
	case brp_CardType_Felica: return "FeliCa";
	case brp_CardType_EM4100: return "EM4100";
	case brp_CardType_HidProx: return "HID Prox";
	case brp_CardType_LEGICPrime: return "LEGIC Prime";
	default: return "Other / unknown card type";
	}
}

unsigned reader_analyze_sample_card(reader_handle reader, reader_card_info *card_info)
{
	brp_CardFamilies families = {0};
	brp_CardType card_type = brp_CardType_Default;
	brp_buf uid = NULL;
	size_t uid_len = 0;
	size_t used = 0;
	size_t index;
	brp_errcode error;

	if (reader == NULL || card_info == NULL)
		return BRP_ERR_INVALID_API_CALL;
	memset(card_info, 0, sizeof(*card_info));
	families.LEGICPrime = true;
	families.Khz125Part2 = true;
	families.Srix = true;
	families.Khz125Part1 = true;
	families.Felica = true;
	families.IClass = true;
	families.IClassIso14B = true;
	families.Iso14443B = true;
	families.Iso15693 = true;
	families.Iso14443A = true;
	families.BluetoothMce = true;

	error = brp_VHL_Select((brp_VHL_Select_t){reader, families, true, false, &card_type});
	if (error != BRP_OK)
	{
		char *name = brp_map_errcode(error);
		snprintf(card_info->error, sizeof(card_info->error), "%s", name != NULL ? name : "Card selection failed");
		return error;
	}

	error = brp_VHL_GetSnr((brp_VHL_GetSnr_t){reader, &uid, &uid_len, NULL});
	if (error != BRP_OK)
	{
		char *name = brp_map_errcode(error);
		snprintf(card_info->error, sizeof(card_info->error), "%s", name != NULL ? name : "Reading card UID failed");
		return error;
	}

	snprintf(card_info->card_type, sizeof(card_info->card_type), "%s", reader_card_type_name(card_type));
	for (index = 0; index < uid_len && used + 3 < sizeof(card_info->uid); index++)
		used += (size_t)snprintf(card_info->uid + used, sizeof(card_info->uid) - used,
			"%02X%s", uid[index], index + 1 == uid_len ? "" : " ");
	return BRP_OK;
}

unsigned reader_factory_reset(reader_handle reader)
{
	return brp_Sys_FactoryReset((brp_Sys_FactoryReset_t){reader, true});
}

unsigned reader_enable_autoread_once(reader_handle reader)
{
	return brp_AR_SetMode((brp_AR_SetMode_t){reader, brp_AutoReadMode_EnableOnce});
}

unsigned reader_get_autoread_message(reader_handle reader, char *message, size_t message_capacity, size_t *message_length, int *message_available)
{
	brp_buf data = NULL;
	size_t data_length = 0;
	size_t copy_length;
	brp_errcode error;

	if (reader == NULL || message == NULL || message_capacity == 0 || message_length == NULL || message_available == NULL)
		return BRP_ERR_INVALID_API_CALL;

	*message_length = 0;
	*message_available = 0;
	message[0] = '\0';
	error = brp_AR_GetMessage((brp_AR_GetMessage_t){reader, .MsgData=&data, .MsgData_len=&data_length});
	if (error == BRP_AR_ErrNoMessage)
		return BRP_OK;
	if (error != BRP_OK)
		return error;

	copy_length = data_length < message_capacity - 1 ? data_length : message_capacity - 1;
	if (copy_length > 0)
		memcpy(message, data, copy_length);
	message[copy_length] = '\0';
	*message_length = copy_length;
	*message_available = 1;
	return BRP_OK;
}