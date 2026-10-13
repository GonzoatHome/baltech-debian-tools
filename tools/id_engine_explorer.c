#include "reader_helpers.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESPONSE_CAPACITY 4096

static void print_usage(const char *program)
{
	printf("Usage: %s [--serial SERIAL]\n", program);
	printf("Connects to a BALTECH reader and opens an interactive BRP command prompt.\n");
}

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

static int parse_command_code(const char *text, unsigned *code)
{
	char *end = NULL;
	unsigned long value;

	if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X'))
		text += 2;
	value = strtoul(text, &end, 16);
	if (end == text || *end != '\0' || value > 0xFFFF)
		return 0;
	*code = (unsigned)value;
	return 1;
}

static int parse_hex_payload(const char *text, unsigned char **payload, size_t *payload_size)
{
	size_t capacity = strlen(text) / 2 + 1;
	size_t count = 0;
	int high_nibble = -1;
	unsigned char *bytes = malloc(capacity);

	if (bytes == NULL)
		return 0;
	while (*text != '\0')
	{
		int value;
		if (isspace((unsigned char)*text) || *text == ':' || *text == '-')
		{
			text++;
			continue;
		}
		if (*text >= '0' && *text <= '9')
			value = *text - '0';
		else if (*text >= 'a' && *text <= 'f')
			value = *text - 'a' + 10;
		else if (*text >= 'A' && *text <= 'F')
			value = *text - 'A' + 10;
		else
		{
			free(bytes);
			return 0;
		}
		if (high_nibble < 0)
			high_nibble = value;
		else
		{
			bytes[count++] = (unsigned char)((high_nibble << 4) | value);
			high_nibble = -1;
		}
		text++;
	}
	if (high_nibble >= 0)
	{
		free(bytes);
		return 0;
	}
	*payload = bytes;
	*payload_size = count;
	return 1;
}

static void print_help(void)
{
	printf("Commands:\n");
	printf("  info                         Read the reader firmware string\n");
	printf("  cmd <CODE> [HEX_BYTES]       Send a raw BRP command (timeout: 1000 ms)\n");
	printf("  help                         Show this help\n");
	printf("  quit                         Disconnect and exit\n");
	printf("\nExamples (command IDs are hexadecimal):\n");
	printf("  cmd 0x0004                 Sys.GetInfo (reader information)\n");
	printf("  cmd 0x0024                 Sys.GetFeatures (supported feature IDs)\n");
	printf("  cmd 0x0500 02              AR.SetMode EnableOnce (starts one scan)\n");
	printf("  cmd 0x0501                 AR.GetMessage (get a buffered Autoread result)\n");
	printf("Command families include Sys, VHL, AR, Mif, Iso14a, Sec, UI and I2c.\n");
	printf("HEX_BYTES are command-specific payload bytes; use the command reference for their format.\n");
	printf("Raw commands can change reader state or configuration. Reference: https://docs.baltech.de/refman/cmds/\n");
}

static void execute_command(brp_protocol reader, unsigned code, const char *parameter_text)
{
	unsigned char *parameters = NULL;
	size_t parameter_size = 0;
	unsigned char response[RESPONSE_CAPACITY];
	size_t response_size = 0;
	brp_errcode error;
	size_t index;

	if (!parse_hex_payload(parameter_text, &parameters, &parameter_size))
	{
		fprintf(stderr, "Parameters must be complete hexadecimal byte pairs.\n");
		return;
	}

	error = brp_exec_cmd(reader, (int)code, parameters, parameter_size,
			response, sizeof(response), &response_size, (brp_time)1000);
	free(parameters);
	if (error != BRP_OK)
	{
		reader_report_error("Executing BRP command", error);
		return;
	}

	printf("Response to 0x%04X (%zu bytes):\n", code, response_size);
	for (index = 0; index < response_size; index++)
		printf("%02X%s", response[index], index + 1 == response_size ? "\n" : " ");
	if (response_size == 0)
		printf("<empty>\n");
}

int main(int argc, char **argv)
{
	long long requested_serial = 0;
	long long selected_serial;
	int index;
	brp_protocol reader;
	char input[4096];

	for (index = 1; index < argc; index++)
	{
		if (strcmp(argv[index], "--help") == 0 || strcmp(argv[index], "-h") == 0)
		{
			print_usage(argv[0]);
			return EXIT_SUCCESS;
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
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	if (!reader_select_serial(requested_serial, &selected_serial))
		return EXIT_FAILURE;
	reader = reader_open(selected_serial);
	if (reader == NULL)
		return EXIT_FAILURE;

	printf("Connected to reader SN %08lld.\n", selected_serial);
	if (!reader_print_info(reader))
	{
		brp_destroy(reader);
		return EXIT_FAILURE;
	}
	print_help();

	while (1)
	{
		char command[32] = {0};
		char code_text[32] = {0};
		int payload_offset = 0;
		unsigned code;

		printf("brp> ");
		fflush(stdout);
		if (fgets(input, sizeof(input), stdin) == NULL)
			break;
		input[strcspn(input, "\r\n")] = '\0';
		if (sscanf(input, "%31s", command) != 1)
			continue;
		if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0)
			break;
		if (strcmp(command, "help") == 0)
		{
			print_help();
			continue;
		}
		if (strcmp(command, "info") == 0)
		{
			reader_print_info(reader);
			continue;
		}
		if (strcmp(command, "cmd") != 0 ||
			sscanf(input, "%*s %31s %n", code_text, &payload_offset) < 1 ||
			!parse_command_code(code_text, &code))
		{
			fprintf(stderr, "Use 'cmd <CODE> [HEX_BYTES]', 'info', 'help' or 'quit'.\n");
			continue;
		}
		execute_command(reader, code, input + payload_offset);
	}

	brp_destroy(reader);
	return EXIT_SUCCESS;
}