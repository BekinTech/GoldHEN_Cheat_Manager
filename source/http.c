#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "curl/curl.h"
#include <orbis/Sysmodule.h>

#include "common.h"
#include "cheats.h"

#define HTTP_SUCCESS 	1
#define HTTP_FAILED	 	0
#define HTTP_USER_AGENT "Mozilla/5.0 (PLAYSTATION 4; 1.00)"


int http_init(void)
{
	if(sceSysmoduleLoadModuleInternal(ORBIS_SYSMODULE_INTERNAL_NET) < 0)
		return HTTP_FAILED;

	if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK)
		return HTTP_FAILED;

	return HTTP_SUCCESS;
}


void http_end(void)
{
	curl_global_cleanup();
}
