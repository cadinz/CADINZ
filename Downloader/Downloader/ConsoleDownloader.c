#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 512


int FileDownload(char *urlurl, char *filename){
	char url[MAX_LINE];
	char destination[MAX_LINE];
	char buffer[MAX_LINE];

	strcpy(url, urlurl);
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

int count_file_line(char *filename) {
	FILE *fp;
	int count = 1;
	char c;

	fp = fopen(filename, "r");

	if (fp == NULL)
	{
		puts("파일에 내용이 없습니다.");
		return 0;
	}

	for (c = getc(fp); c != EOF; c = getc(fp))
		if (c == '\n')
			count = count + 1;

	fclose(fp);
	return count;
}

typedef struct UrlData{

	char name[50];
	char filename[50];
	char url[100];
	
}URLDATA;


void printUsage(){
	printf("Example usage : \n");
	printf("\tjin list\n");
	printf("\tjin info\n");
	printf("\tjin update\n");
	printf("\tjin download [name]\n");
}

void insert_urldata(URLDATA *urldata) {

	FILE *fp;
	char s[1000];
	int i = 0;
	fp = fopen("command.txt", "r");  // 파일 열기

	while(!feof(fp))
	{
		fscanf(fp, "%s %s %s", urldata[i].name, urldata[i].filename, urldata[i].url);

			i++;
	}

	fclose(fp);
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
	char cmdUrl[] = "http://imgdb.kr/dJsr.dn";
	char cmdFileName[] = "command.txt";
	puts("필요한 파일을 다운로드합니다.");
	
	if (!FileDownload(cmdUrl, cmdFileName)){
		return 0;
	}

	int index = count_file_line("command.txt");


	URLDATA *urldata = (URLDATA*)malloc(sizeof(URLDATA));

	insert_urldata(urldata);

	char command[100];
	char *jin = "0", *cmd = "0", *name = "0";

	for (;;){
		printf("se-jin>");
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

		if (!strcmp(jin, "jin")){

			if (!strcmp(cmd, "download"))
			{
				if (!strcmp(name, "")){
					printUsage();
					printf("\tERROR: UnKnown command : %s \n", jin);
					return;
				}

				for (int i = 0; i < index; i++){
					if (!strcmp(name, urldata[i].name)){
						FileDownload(urldata[i].url, urldata[i].filename);
					}
				}
			}


			if (!strcmp(cmd, "list"))
			{
				for (int i = 0; i < index; i++){
					printf("%s\n", urldata[i].name);
				}
			}


			if (!strcmp(cmd, "info"))
			{
				puts("Made by Sejin");
			}

			if (!strcmp(cmd, "update"))
			{
				FileDownload(cmdUrl, cmdFileName);
			}




		}// if jin


	}// for

}//main
