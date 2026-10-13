#include "reader_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#define strcasecmp _stricmp
#else
#include <strings.h>
#endif

#ifdef BALTECH_HAVE_LIBXML2
#include <errno.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#endif

static void print_usage(const char *program)
{
	printf("Usage: %s [--serial SERIAL] [--yes] [--check] FILE\n", program);
	printf("Uploads .bec configuration or BEC2/BF3 firmware/configuration to a BALTECH USB/HID reader.\n");
	printf("Use --check with a .bec file to validate its XML blocks without connecting to a reader.\n");
#ifndef BALTECH_HAVE_LIBXML2
	printf("Legacy .bec support requires a build with libxml2.\n");
#endif
}

#ifdef BALTECH_HAVE_LIBXML2
typedef struct
{
	unsigned version;
	unsigned char *data;
	size_t data_length;
} bec_block;

typedef struct
{
	bec_block *items;
	size_t count;
} bec_block_list;

static xmlChar *get_bec_attribute(xmlNodePtr node, const char *lower, const char *upper)
{
	xmlChar *value = xmlGetProp(node, BAD_CAST lower);
	return value != NULL ? value : xmlGetProp(node, BAD_CAST upper);
}

static int decode_bec_hex(const xmlChar *text, unsigned char **data, size_t *data_length)
{
	size_t digits = 0;
	size_t output_index = 0;
	int high_nibble = -1;
	size_t index;
	unsigned char *decoded;

	for (index = 0; text[index] != '\0'; index++)
	{
		if (text[index] == ' ' || text[index] == '\t' || text[index] == '\r' || text[index] == '\n')
			continue;
		if (!((text[index] >= '0' && text[index] <= '9') ||
			(text[index] >= 'a' && text[index] <= 'f') ||
			(text[index] >= 'A' && text[index] <= 'F')))
			return 0;
		digits++;
	}
	if (digits == 0 || digits % 2 != 0)
		return 0;
	decoded = malloc(digits / 2);
	if (decoded == NULL)
		return 0;
	for (index = 0; text[index] != '\0'; index++)
	{
		int value;
		if (text[index] == ' ' || text[index] == '\t' || text[index] == '\r' || text[index] == '\n')
			continue;
		if (text[index] >= '0' && text[index] <= '9') value = text[index] - '0';
		else if (text[index] >= 'a' && text[index] <= 'f') value = text[index] - 'a' + 10;
		else value = text[index] - 'A' + 10;
		if (high_nibble < 0)
			high_nibble = value;
		else
		{
			decoded[output_index++] = (unsigned char)((high_nibble << 4) | value);
			high_nibble = -1;
		}
	}
	*data = decoded;
	*data_length = output_index;
	return 1;
}

static void free_bec_blocks(bec_block_list *blocks)
{
	size_t index;
	for (index = 0; index < blocks->count; index++)
		free(blocks->items[index].data);
	free(blocks->items);
	blocks->items = NULL;
	blocks->count = 0;
}

static int collect_bec_blocks(xmlNodePtr node, bec_block_list *blocks, char *error_text, size_t error_text_size)
{
	for (; node != NULL; node = node->next)
	{
		if (node->type != XML_ELEMENT_NODE)
			continue;
		if (xmlStrcasecmp(node->name, BAD_CAST "block") == 0)
		{
			xmlChar *version_text = get_bec_attribute(node, "version", "Version");
			xmlChar *data_text = get_bec_attribute(node, "content", "Content");
			char *end = NULL;
			unsigned long version;
			unsigned char *data = NULL;
			size_t data_length = 0;
			bec_block *resized;

			if (data_text == NULL)
				data_text = get_bec_attribute(node, "data", "Data");
			if (version_text == NULL || data_text == NULL)
			{
				snprintf(error_text, error_text_size, "BEC block is missing version or content/data attribute");
				xmlFree(version_text);
				xmlFree(data_text);
				return 0;
			}
			errno = 0;
			version = strtoul((const char *)version_text, &end, 10);
			if (errno != 0 || end == (char *)version_text || *end != '\0' || version > 255)
			{
				snprintf(error_text, error_text_size, "BEC block has an invalid version attribute");
				xmlFree(version_text);
				xmlFree(data_text);
				return 0;
			}
			if (!decode_bec_hex(data_text, &data, &data_length) || data_length > 255)
			{
				snprintf(error_text, error_text_size, "BEC block content is not valid hex or exceeds 255 bytes");
				free(data);
				xmlFree(version_text);
				xmlFree(data_text);
				return 0;
			}
			resized = realloc(blocks->items, (blocks->count + 1) * sizeof(*blocks->items));
			if (resized == NULL)
			{
				snprintf(error_text, error_text_size, "Out of memory while reading BEC blocks");
				free(data);
				xmlFree(version_text);
				xmlFree(data_text);
				return 0;
			}
			blocks->items = resized;
			blocks->items[blocks->count].version = (unsigned)version;
			blocks->items[blocks->count].data = data;
			blocks->items[blocks->count].data_length = data_length;
			blocks->count++;
			xmlFree(version_text);
			xmlFree(data_text);
		}
		if (!collect_bec_blocks(node->children, blocks, error_text, error_text_size))
			return 0;
	}
	return 1;
}

static int parse_bec_file(const char *filepath, bec_block_list *blocks, char *error_text, size_t error_text_size)
{
	xmlDocPtr document = xmlReadFile(filepath, NULL,
		XML_PARSE_NONET | XML_PARSE_NOBLANKS | XML_PARSE_NOERROR | XML_PARSE_NOWARNING | XML_PARSE_COMPACT);
	int success;
	if (document == NULL)
	{
		snprintf(error_text, error_text_size, "The .bec file is not valid XML");
		return 0;
	}
	if (document->intSubset != NULL || document->extSubset != NULL)
	{
		snprintf(error_text, error_text_size, "BEC document type declarations are not accepted");
		xmlFreeDoc(document);
		return 0;
	}
	success = collect_bec_blocks(xmlDocGetRootElement(document), blocks, error_text, error_text_size);
	xmlFreeDoc(document);
	if (success && blocks->count == 0)
	{
		snprintf(error_text, error_text_size, "The .bec file contains no block elements");
		return 0;
	}
	return success;
}

static brp_errcode upload_bec_config(brp_protocol reader, const char *filepath)
{
	char error_text[256] = "";
	bec_block_list blocks = {NULL, 0};
	brp_errcode error;
	size_t index;
	int transfer_started = 0;

	if (!parse_bec_file(filepath, &blocks, error_text, sizeof(error_text)))
	{
		fprintf(stderr, "BEC validation failed: %s\n", error_text);
		free_bec_blocks(&blocks);
		return BRP_ERR_PAYLOAD_FORMAT;
	}

	error = brp_Sys_CfgLoadPrepare((brp_Sys_CfgLoadPrepare_t){reader, brp_AuthReqUpload_Default});
	if (error != BRP_OK)
	{
		free_bec_blocks(&blocks);
		return error;
	}
	transfer_started = 1;
	for (index = 0; index < blocks.count; index++)
	{
		printf("Uploading BEC block %zu / %zu\r", index + 1, blocks.count);
		fflush(stdout);
		error = brp_Sys_CfgLoadBlock((brp_Sys_CfgLoadBlock_t){
			reader, blocks.items[index].version, blocks.items[index].data, blocks.items[index].data_length});
		if (error != BRP_OK)
			break;
	}
	printf("\n");
	if (transfer_started && error != BRP_OK)
	{
		brp_errcode cancel_error = brp_Sys_CfgLoadFinish((brp_Sys_CfgLoadFinish_t){
			reader, brp_Sys_CfgLoadFinish_FinalizeAction_CancelCfgLoad});
		if (cancel_error != BRP_OK)
			reader_report_error("Cancelling failed BEC transfer", cancel_error);
	}
	else if (error == BRP_OK)
	{
		error = brp_Sys_CfgLoadFinish((brp_Sys_CfgLoadFinish_t){
			reader, brp_Sys_CfgLoadFinish_FinalizeAction_FinalizeCfgLoadWithReboot});
	}
	free_bec_blocks(&blocks);
	return error;
}
#endif

static int parse_serial(const char *text, long long *serial)
{
	char *end = NULL;
	long long value;

	value = strtoll(text, &end, 10);
	if (end == text || *end != '\0' || value <= 0)
		return 0;
	*serial = value;
	return 1;
}

static int has_bec_extension(const char *filepath)
{
	const char *extension = strrchr(filepath, '.');
	return extension != NULL && strcasecmp(extension, ".bec") == 0;
}

static void show_progress(unsigned transferred_bytes, unsigned estimated_total,
		unsigned progress_percent, unsigned estimated_time_overhead,
		bool reconnecting)
{
	(void)estimated_time_overhead;
	if (reconnecting)
		printf("\nReader reconnecting after firmware transfer...\n");
	else if (estimated_total != 0)
		printf("\rUploading: %3u%% (%u / %u bytes)", progress_percent,
			transferred_bytes, estimated_total);
	else
		printf("\rUploading: %u bytes", transferred_bytes);
	fflush(stdout);
}

int main(int argc, char **argv)
{
	long long requested_serial = 0;
	long long selected_serial;
	const char *firmware_path = NULL;
	int assume_yes = 0;
	int check_only = 0;
	int is_bec;
	int index;
	FILE *firmware;
	char answer[32];
	brp_protocol reader;
	brp_errcode error;

	for (index = 1; index < argc; index++)
	{
		if (strcmp(argv[index], "--help") == 0 || strcmp(argv[index], "-h") == 0)
		{
			print_usage(argv[0]);
			return EXIT_SUCCESS;
		}
		if (strcmp(argv[index], "--yes") == 0)
		{
			assume_yes = 1;
			continue;
		}
		if (strcmp(argv[index], "--check") == 0)
		{
			check_only = 1;
			continue;
		}
		if (strcmp(argv[index], "--serial") == 0 && index + 1 < argc)
		{
			if (!parse_serial(argv[++index], &requested_serial))
			{
				fprintf(stderr, "Invalid reader serial number.\n");
				return EXIT_FAILURE;
			}
			continue;
		}
		if (firmware_path == NULL && argv[index][0] != '-')
		{
			firmware_path = argv[index];
			continue;
		}
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	if (firmware_path == NULL)
	{
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}
	is_bec = has_bec_extension(firmware_path);
	firmware = fopen(firmware_path, "rb");
	if (firmware == NULL)
	{
		perror("Unable to open firmware file");
		return EXIT_FAILURE;
	}
	fclose(firmware);
	if (check_only)
	{
		if (!is_bec)
		{
			fprintf(stderr, "--check currently validates legacy .bec files only.\n");
			return EXIT_FAILURE;
		}
#ifdef BALTECH_HAVE_LIBXML2
		{
			bec_block_list blocks = {NULL, 0};
			char validation_error[256] = "";
			if (!parse_bec_file(firmware_path, &blocks, validation_error, sizeof(validation_error)))
			{
				fprintf(stderr, "BEC validation failed: %s\n", validation_error);
				free_bec_blocks(&blocks);
				return EXIT_FAILURE;
			}
			printf("BEC validation passed: %zu block(s). No reader was contacted.\n", blocks.count);
			free_bec_blocks(&blocks);
			return EXIT_SUCCESS;
		}
#else
		fprintf(stderr, "Legacy .bec validation is unavailable in this build; rebuild with libxml2.\n");
		return EXIT_FAILURE;
#endif
	}

	if (!reader_select_serial(requested_serial, &selected_serial))
		return EXIT_FAILURE;
	if (!assume_yes)
	{
		printf("Upload '%s' to reader SN %08lld? [y/N] ", firmware_path, selected_serial);
		if (fgets(answer, sizeof(answer), stdin) == NULL ||
			(answer[0] != 'y' && answer[0] != 'Y'))
		{
			printf("Upload cancelled.\n");
			return EXIT_SUCCESS;
		}
	}

	reader = reader_open(selected_serial);
	if (reader == NULL)
		return EXIT_FAILURE;
	if (!reader_print_info(reader))
	{
		brp_destroy(reader);
		return EXIT_FAILURE;
	}

	if (is_bec)
	{
#ifdef BALTECH_HAVE_LIBXML2
		error = upload_bec_config(reader, firmware_path);
		if (error != BRP_OK)
		{
			reader_report_error("Legacy BEC upload failed", error);
			brp_destroy(reader);
			return EXIT_FAILURE;
		}
		printf("Legacy BEC configuration applied; reader is rebooting.\n");
		brp_destroy(reader);
		return EXIT_SUCCESS;
#else
		fprintf(stderr, "Legacy .bec support is unavailable in this build; rebuild with libxml2 development headers.\n");
		brp_destroy(reader);
		return EXIT_FAILURE;
#endif
	}

	error = brp_update_reader(reader, firmware_path, show_progress);
	if (error != BRP_OK)
	{
		printf("\n");
		reader_report_error("Firmware upload failed", error);
		brp_destroy(reader);
		return EXIT_FAILURE;
	}
	printf("\nFirmware upload completed.\n");
	reader_print_info(reader);
	brp_destroy(reader);
	return EXIT_SUCCESS;
}