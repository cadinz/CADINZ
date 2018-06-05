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

	char *url;
	char *filename;
	char *name;
	
}URLDATA;


void printUsage(){
	printf("Example usage : \n");
	printf("\tjin list\n");
	printf("\tjin info\n");
	printf("\tjin update\n");
	printf("\tjin download [name]\n");
}

void insert_urldata(URLDATA *urldata, int index) {

	FILE *fp;

	char s[300];
	int i = 0;
	fp = fopen("command.txt", "r");  // ���� ����

	for (;i<index;)  // ������ ���� �ƴ϶��

	{
		printf("���");
		fgets(s, 300, fp);
		char *ptr = strtok(s, " ");      // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ
		while (ptr != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
		{
			printf("%s", ptr);          // �ڸ� ���ڿ� ���
			ptr = strtok(NULL, " ");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
		}
		
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
	char cmdUrl[] = "https://raw.githubusercontent.com/cadinz/CDowner/master/command";
	char cmdFileName[] = "command.txt";

	puts("�ʿ��� ������ �ٿ�ε��մϴ�.");
	FileDownload(cmdUrl, cmdFileName);

	int index = count_file_line("command.txt");

	URLDATA *urldata = (URLDATA*)malloc(sizeof(URLDATA)*index);

	insert_urldata(urldata,2);
	


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