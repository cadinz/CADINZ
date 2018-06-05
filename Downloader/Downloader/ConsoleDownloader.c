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

		printf("\r�ٿ�ε���...");
		Sleep(100);
		printf("\r�ٿ�ε���.....");
		Sleep(100);
		printf("\r�ٿ�ε���........");
		Sleep(100);
		printf("\r�ٿ�ε���............");
		Sleep(100);

		if (dl == S_OK)
		{
			sprintf(buffer, "\n�ٿ�ε� �Ϸ� : %s \n", destination);
			printf(buffer);
			return 10;
		}
		else if (dl == E_OUTOFMEMORY)
		{
			sprintf(buffer, "\n�޸𸮰� �����մϴ�. \n");
			printf(buffer);
			return 0;
		}
		else
		{
			sprintf(buffer, "\n�� �� ���� ����. \n");
			printf(buffer);
			return 0;
		}
			
	}

}

int count_file_line(char *filename) {
	FILE *fp;
	int count = 0;
	char c;

	fp = fopen(filename, "r");

	if (fp == NULL)
	{
		puts("���Ͽ� ������ �����ϴ�.");
		return 0;
	}

	for (c = getc(fp); c != EOF; c = getc(fp))
		if (c == '\n')
			count = count + 1;

	fclose(fp);
	return count;
}

typedef struct UrlData{

	char *name;
	char *filename;
	char *url;
	int data;
	
}URLDATA;


void printUsage(){
	printf("Example usage : \n");
	printf("\tjin list\n");
	printf("\tjin info\n");
	printf("\tjin update\n");
	printf("\tjin download [name]\n");
}

void insert_urldata(URLDATA *urldata,int index) {

	FILE *fp;
	char s[1000];
	int i = 0;
	fp = fopen("command.txt", "r");  // ���� ����

	while(!feof(fp))
	{
		fgets(s, 1000, fp);

		char *ptr = strtok(s, " ");      // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ

			
			strcpy(&(urldata[i].name), ptr);
			printf("%s \n", &(urldata[i].name));
			ptr = strtok(NULL, " ");
			
			strcpy(&(urldata[i].filename), ptr);
			printf("%s \n", &(urldata[i].filename));
			ptr = strtok(NULL, " ");

			strcpy(&(urldata[i].url), ptr);
			printf("%s \n", &(urldata[i].url));

			urldata[i].data = i;
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
	char cmdUrl[] = "http://blogattach.naver.net/e87df44f506362d4f8127a427394e39334689808/20180605_191_blogfile/cadinz_1528182778515_BQKr67_txt/command.txt";
	char cmdFileName[] = "command.txt";

	puts("�ʿ��� ������ �ٿ�ε��մϴ�.");
	FileDownload(cmdUrl, cmdFileName);

	int index = count_file_line("command.txt");

	URLDATA *urldata = (URLDATA*)malloc(sizeof(URLDATA)*index);

	insert_urldata(urldata, index);
	
	printf("%s \n", &urldata[0].name);


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

		if (strcmp(jin, "jin") == 0){

			if (strcmp(cmd, "-download") == 0)
			{
				if (strcmp(name, "") == 0){
					printUsage();
					printf("\tERROR: UnKnown command : %s \n", jin);
				}
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
				FileDownload(cmdUrl, cmdFileName);
				puts("Made by Sejin");
			}




		}// if jin

	}// for

}//main