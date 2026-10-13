#include "brp_lib/version.h"
#include "release.h"

char * brp_get_version(void)
{
	static char version_str[] = RELEASE_STR;
	return version_str;
}
