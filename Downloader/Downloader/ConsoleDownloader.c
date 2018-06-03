#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 512

int FileDownload(char *downLoadUrl , char *filename){
	char url[MAX_LINE];
	char destination[MAX_LINE];
	char buffer[MAX_LINE];

	strcpy(url, downLoadUrl);
	strcpy(destination, filename);
	HRESULT    dl;

	typedef HRESULT(WINAPI * URLDownloadToFileA_t)(LPUNKNOWN pCaller, LPCSTR szURL, LPCSTR szFileName, DWORD dwReserved, void * lpfnCB);
	URLDownloadToFileA_t xURLDownloadToFileA;
	xURLDownloadToFileA = (URLDownloadToFileA_t)GetProcAddress(LoadLibraryA("urlmon"), "URLDownloadToFileA");

	dl = xURLDownloadToFileA(NULL, url, destination, 0, NULL);

	for (;;){

		printf("\r다운로드중...");
		Sleep(100);
		printf("\r다운로드중.....");
		Sleep(100);
		printf("\r다운로드중........");
		Sleep(100);
		printf("\r다운로드중............");
		Sleep(100);

		if (dl == S_OK)
		{
			sprintf(buffer, "\n다운로드 완료 : %s \n", destination);
			printf(buffer);
			return 10;
		}
		else if (dl == E_OUTOFMEMORY)
		{
			sprintf(buffer, "\n메모리가 부족합니다. \n");
			printf(buffer);
			return 0;
		}
		else
		{
			sprintf(buffer, "\n알 수 없는 오류. \n");
			printf(buffer);
			return 0;
		}
			
	}

}

typedef struct UrlData{

	char *url;
	char *name;

}URLDATA;

void printUsage(){
	printf("Example usage : \n");
	printf("\tjin list\n");
	printf("\tjin info\n");
	printf("\tjin update\n");
	printf("\tjin download [name]\n");
}
int main(){

	puts("        ....                               +.");
	puts("     =@@#**%@                        +@   .%=");
	puts("    .@+                              +@");
	puts("     %@+         %@#*%@:             +@   .@=  .@*##*%@*");
	puts("      .*@@#:    @+    :@:            +@   .@:   @#    .@=");
	puts("          =@@  *@#%%%%#%= .%%%%%.    =@   .@:   @=     @+");
	puts("            @+ :@:                   #@   .@:   @=     @+");
	puts("    :@%***#@*   =@%+=+##         .#*%@.   .@=  .@=     @+");
	puts("      .:::         :::            ::       .    .      .");
	puts("============================================================");
	char cmdUrl[] = "https://raw.githubusercontent.com/cadinz/CDowner/master/Downloader/command";
	char cmdFileName[] = "command.txt";

	puts("필요한 파일을 다운로드합니다.");
	FileDownload(cmdUrl, cmdFileName);


	char command[100];
	char *jin = "0", *cmd = "0", *name = "0";

	for (;;){

		gets(command);

		if (command[0] != '\0'){
			jin = strtok(command, " ");
			cmd = strtok(NULL, " ");
			name = strtok(NULL, " ");
		}

		if (strcmp(jin, "jin") != 0 && strcmp(jin, "\n") != 0){
			printUsage();
			printf("\tERROR: UnKnown command : %s \n", jin);
		}

		if (strcmp(jin, "jin") == 0){

			if (strcmp(cmd, "-download") == 0)
			{
				if (strcmp(name, "") == 0){}
			}


			if (strcmp(cmd, "-list") == 0)
			{

			}


			if (strcmp(cmd, "-info") == 0)
			{
				puts("Made by Sejin");
			}

			if (strcmp(cmd, "-update") == 0)
			{
				puts("Made by Sejin");
			}




		}// if jin

	}// for

}//main