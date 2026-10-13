#include "brp_lib/names.h"
#include "namelists.h"

#define ERRCODES_SIZE   sizeof(errcodes) / sizeof(brp_errcode)
#define CMDCODES_SIZE   sizeof(cmdcodes) / sizeof(unsigned)

static int search_code(unsigned search_val, unsigned *arr, int arrsize)
{
	int min = 0;
	int max = arrsize;
	while (min < max)
	{
		int mid = (min + max) / 2;
		if (search_val < arr[mid])
			max = mid;
		else if (search_val > arr[mid])
			min = mid + 1;
		else
			return mid;
	}
	return -1;
}


char * brp_map_errcode(brp_errcode errcode)
{
	int ndx = search_code(errcode, errcodes, ERRCODES_SIZE);
	if (ndx == -1)
		return NULL;
	else
		return ec_names[ndx];
}


char * brp_map_errcode_to_desc(brp_errcode errcode)
{
	int ndx = search_code(errcode, errcodes, ERRCODES_SIZE);
	if (ndx == -1)
		return NULL;
	else
		return ec_descs[ndx];
}


char * brp_map_errcode_to_docurl(brp_errcode errcode)
{
	int ndx = search_code(errcode, errcodes, ERRCODES_SIZE);
	if (ndx == -1)
		return NULL;
	else
		return ec_urls[ec_url_map[ndx]];
}


char * brp_map_cmdcode(unsigned cmd_code)
{
	int ndx = search_code(cmd_code, cmdcodes, CMDCODES_SIZE);
	if (ndx == -1)
		return NULL;
	else
		return cc_names[ndx];
}


char * brp_map_cmdcode_to_docurl(unsigned cmd_code)
{
	int ndx = search_code(cmd_code, cmdcodes, CMDCODES_SIZE);
	if (ndx == -1)
		return NULL;
	else
		return cc_urls[ndx];
}
