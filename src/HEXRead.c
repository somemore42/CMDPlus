#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<windows.h>

void warning(const char* c) {HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hand, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);  printf("%s", "[Warning]:"); printf("%s\n", c); }
void log(const char* c) {HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hand, FOREGROUND_INTENSITY | FOREGROUND_BLUE); printf("%s", "[Info]:"); printf("%s\n", c); };
void _strlink(char *p,const char str[]) {
	int i = 0; int e = 0;
	while (1) {
	if(p[e]=='\0'){break;}
		e++;
	}
	while (1) {
	if(str[i]=='\0'){break;}
		p[e + i] = str[i];
		i++;
	}
	p[e + i ] = '\0';
}
void strlink(char *p,char str[]) {
	int i = 0; int e = 0;
	while (1) {
	if(p[e]=='\0'){break;}
		e++;
	}
	while (1) {
	if(str[i]=='\0'){break;}
		p[e + i] = str[i];
		i++;
	}
	p[e + i ] = '\0';
}
void pause(){
while (1) {
		if (_kbhit()) { return; }
	}
}
const char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
void toHex(char byt,char *str){

unsigned radix=16;
int num=(int)byt;
unsigned unum=(unsigned) num;
str[0]=0;
if(unum==0){
strlink(str,"00");
}else{
str[1]=index[unum%16];
unum/=16;
str[0]=index[unum%16];
str[2]=0;
}
}
int getBinSize(char* path)
{
	int  size = 0;
	FILE* file;
	errno_t err = fopen_s(&file, path, "rb");
	if (!err)
	{
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fclose(file);
	}
	return size;
}
int main(int argc, char* argv[], char* envp[]) {
	FILE* sourcefile;
	FILE* destfile;
	char byte[2]={0};
	char hex[8] = { 0 };
	char outf[255] = "Hex_Text.txt";
	char inf[255]="";
	char x=0;

	int fi=0;int binsize=0;
if (argc == 1) {
		warning("COMMAND: HexRead [source file path] /[output file path]");
		pause();
		return 0;
	}
if (argc == 2) {
		inf[0]='\0';
		strlink(inf, argv[1]);
	}
if (argc == 3) { 
		inf[0]='\0';
		outf[0]='\0';
		strlink(inf, argv[1]);
		strlink(outf, argv[2]);
	}
	if ((sourcefile=fopen(inf, "rb"))==0)
	{
		warning("打开目标文件失败！");return 0;
	}
	if ((destfile=fopen(outf, "w+"))==0)
	{
		warning("写入目标文件失败！");return 0;
	}
binsize=getBinSize(inf);
if(!binsize){
	warning("目标文件为空！");return 0;
}

printf("文件大小：%d\n",binsize);
//fread(byte, sizeof(unsigned char), binsize, sourcefile);
while(fi<binsize){
		hex[0]='\0';
		
		fread(byte, sizeof(unsigned char), sizeof(byte)-1, sourcefile);
		x=byte[0];
		toHex(x,hex);
		strlink(hex," ");
		fputs(hex, destfile);
		fi++;
		}
log("完成！\a");
fclose(sourcefile); fclose(destfile);
return 0;
}