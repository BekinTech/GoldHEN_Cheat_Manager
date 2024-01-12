/* 
	Cheats Manager PS4 main.c
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#include <orbis/Sysmodule.h>
#include <orbis/AudioOut.h>
#include <orbis/CommonDialog.h>
#include <orbis/Sysmodule.h>
#include <orbis/SystemService.h>

#include <curl/curl.h>
#include <orbis/NetCtl.h>
#include <orbis/libkernel.h>
#include "cheats.h"

#define SUCCESS 	1
#define HTTP_SUCCESS 	1
#define HTTP_FAILED	 	0
#define HTTP_USER_AGENT "Mozilla/5.0 (PLAYSTATION 4; 1.00)"
#include <stdarg.h>
inline static void KernelPrintOut(const char* FMT, ...)
{
    char MessageBuf[1024];
    va_list args;
    va_start(args, FMT);
    vsprintf(MessageBuf, FMT, args);
    va_end(args);

    sceKernelDebugOutText(0, MessageBuf);
	sceKernelDebugOutText(0, "\n");
}


int curlDownloadFile(const char* url, const char* filename)
{
	OrbisNetCtlInfo proxy_info;
	char full_url[1024];
	CURL* curl;
	CURLcode res;
	FILE* fd;

	curl = curl_easy_init();
	if (!curl)
	{
        KernelPrintOut("ERROR: CURL INIT\n");
		return HTTP_FAILED;
	}

	fd = fopen(filename, "wb");
	if (!fd) {
        KernelPrintOut("fopen Error: File path '%s'\n", filename);
		return HTTP_FAILED;
	}


    KernelPrintOut("URL: %s >> %s\n", filename, url);

	curl_easy_setopt(curl, CURLOPT_URL, url);
	// Set user agent string
		curl_easy_setopt(curl, CURLOPT_USERAGENT, HTTP_USER_AGENT);
	// not sure how to use this when enabled
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	// not sure how to use this when enabled
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	// Set SSL VERSION to TLS 1.2
	curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
	// Set timeout for the connection to build
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
	// Follow redirects (?)
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	// The function that will be used to write the data 
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
	// The data filedescriptor which will be written to
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd);
	// maximum number of redirects allowed
	curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 20L);
	// Fail the request if the HTTP code returned is equal to or larger than 400
	curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
	// request using SSL for the FTP transfer if available
	curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);


	// Perform the request
	res = curl_easy_perform(curl);
	// close file descriptor
	fclose(fd);
	// cleanup
	curl_easy_cleanup(curl);



	if (res != CURLE_OK)
	{
        KernelPrintOut("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        remove(filename);
		return HTTP_FAILED;
	}

	return HTTP_SUCCESS;
}


static void terminate(void)
{
	KernelPrintOut("Exiting...");

	terminate_jbc();
	sceSystemServiceLoadExec("exit", NULL);
}

static int initInternal(void)
{
    // load common modules
    int ret = sceSysmoduleLoadModuleInternal(ORBIS_SYSMODULE_INTERNAL_SYSTEM_SERVICE);
    if (ret != SUCCESS) {
        KernelPrintOut("load module failed: SYSTEM_SERVICE (0x%08x)\n", ret);
        return 0;
    }

    ret = sceSysmoduleLoadModuleInternal(ORBIS_SYSMODULE_INTERNAL_USER_SERVICE);
    if (ret != SUCCESS) {
        KernelPrintOut("load module failed: USER_SERVICE (0x%08x)\n", ret);
        return 0;
    }

    ret = sceSysmoduleLoadModuleInternal(ORBIS_SYSMODULE_INTERNAL_SAVE_DATA);
    if (ret != SUCCESS) {
        KernelPrintOut("load module failed: SAVE_DATA (0x%08x)\n", ret);
        return 0;
    }

    return 1;
}


/*
	Program start
*/
int main(int argc, const char* argv[])
{



	initInternal();
	http_init();
	

	
curlDownloadFile("https://download.samplelib.com/mp4/sample-30s.mp4", "/data/GoldHEN/plugins/test.mp4");
   
	 bool finished = false;

 // Play the song in a loop
 while (!finished)
 {

 }
	http_end();
	orbisPadFinish();
	return 0;
}
