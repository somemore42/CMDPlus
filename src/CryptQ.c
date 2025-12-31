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
int lengthC(const char *c) {
	int i = 0;
	int counter = 0;
	while (c[i] != '\0') {
		i++;
		if (i == 32767) { i = -1; break; }
		counter++;
	}
	return counter;
}
int length(char *c) {
	int i = 0;
	int counter = 0;
	while (c[i] != '\0') {
		i++;
		if (i == 32767) { i = -1; break; }
		counter++;
	}
	return counter;
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
	char file[255] = { 0 };
	char outf[255] = "Decode_file.txt";
	int binsize=0;
	int fi=0;
	int x=0;
	char byte[2]={0};
	int keyLen=0;
	char *key=0;
	int v=0;
	char defaultKey[100]="SomeMore42@dream";
	if(argc==1){
	warning("[COMMAND] CryptQ [Target file path] \\[Key String] \\[Output path]");
	return 0;
	}
	else if (argc ==2) {
		//outf[0]=0;
		strlink(file, argv[1]);
		keyLen=length(defaultKey);
		key=defaultKey;
		//strlink(outf, argv[3]);
	}
	else if (argc ==3) {
		//outf[0]=0;
		strlink(file, argv[1]);
		keyLen=length(argv[2]);
		key=argv[2];
		//strlink(outf, argv[3]);
	}
	else if (argc ==4) {
		outf[0]=0;
		strlink(file, argv[1]);
		keyLen=length(argv[2]);
		key=argv[2];
		strlink(outf, argv[3]);
	}else{warning("Too many arguments! Should no more than 3 arguments.");return 0;}
	if ((sourcefile=fopen(file, "rb"))==0)
	{
		warning("打开目标文件失败！");pause();return 0;
	}
	if ((destfile=fopen(outf, "wb+"))==0)
	{
		warning("写入目标文件失败！");pause();return 0;
	}
	binsize=getBinSize(file);
	if(!binsize){
	warning("目标文件为空！");return 0;
	}
	log("Processing....");
	while(fi<binsize){
		byte[0]='\0';
		fread(byte, sizeof(unsigned char), sizeof(byte)-1, sourcefile);
		x=byte[0];
		x=x^(*(key+v));
		v++;
		if(v>=keyLen){v=0;}
		byte[0]=x;
		fwrite(byte,sizeof(unsigned char),1,destfile);
		fi++;
	}
	log("完成！\a");
	fclose(sourcefile); fclose(destfile);
	return 0;
}