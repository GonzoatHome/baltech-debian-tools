#ifndef BALTECH_TOOL_READER_HELPERS_H
#define BALTECH_TOOL_READER_HELPERS_H

#include <stddef.h>

#ifdef __cplusplus
typedef void *reader_handle;
extern "C" {
#else
#include <baltech_sdk.h>
typedef brp_protocol reader_handle;
#endif

typedef struct
{
	long long serial;
	char name[128];
} reader_entry;

typedef struct
{
	char firmware[64];
	char configuration[160];
	char device_settings[160];
	char part_number[64];
	char hardware_revision[32];
	char rfid_status[128];
	char health[256];
	char boot_status[512];
} reader_details;

typedef struct
{
	char card_type[64];
	char uid[128];
	char error[192];
} reader_card_info;

int reader_enumerate_devices(reader_entry **entries, size_t *entry_count);
void reader_free_devices(reader_entry *entries);
int reader_select_serial(long long requested_serial, long long *selected_serial);
reader_handle reader_open(long long serial);
void reader_close(reader_handle reader);
unsigned reader_read_details(reader_handle reader, reader_details *details);
unsigned reader_read_features(reader_handle reader, char *output, size_t output_size);
unsigned reader_analyze_sample_card(reader_handle reader, reader_card_info *card_info);
unsigned reader_factory_reset(reader_handle reader);
unsigned reader_enable_autoread_once(reader_handle reader);
unsigned reader_get_autoread_message(reader_handle reader, char *message, size_t message_capacity, size_t *message_length, int *message_available);

#ifndef __cplusplus
int reader_print_info(reader_handle reader);
void reader_report_error(const char *action, brp_errcode error);
#endif

#ifdef __cplusplus
}
#endif

#endif