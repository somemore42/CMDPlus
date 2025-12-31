//tcc编译时，附加命令：-luser32 ，否则MessageBoxA报错
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<winuser.h>
#pragma comment(lib,"User32.lib")
int C2N(char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 10;
}
int Number(char c[]) {
	int n = 0;
	int i = 0;
	while (c[i] != 0) {
		n *= 10;
		n += C2N(c[i]);
		i++;
	}
	return n;
}
int length(char c[]) {
	int len = 0;
	for (int i = 0;i<25585; i++) {
		if (c[i] == '\0')break;
		len++;
	}
	return len;
}
int _length(const char c[]) {
	int len = 0;
	for (int i = 0; i < 25585; i++) {
		if (c[i] == '\0')break;
		len++;
	}
	return len;
}
int _min(int a, int b) {
	if (a > b)return b;
	if (a < b)return a;
	return a;
}
int _strcmp(char t[], const char o[]) {
	int hex = 'a' - 'A';
	int len = 0;
	if (length(t) <_length(o)) { return 0; }
	int sup = _min(length(t), _length(o));
	for (int i = 0;i<sup; i++) {
		if (t[i] == 0 || o[i] == 0)break;
		if (t[i] >= 'A' && t[i] <= 'Z') {
			if (t[i] == o[i] || (t[i] + hex) == o[i])continue;
			else return 0;
		}
		else if (t[i] >= 'a' && t[i] <= 'z') {
			if (t[i] == o[i] || (t[i] - hex) == o[i])continue;
			else return 0;
		}
		else {
			if (t[i] == o[i])continue;
			else return 0;
		}
	}
	return 1;
}
void pause() {
	printf("已停止，按任意键继续运行\n");
	while (1) {
		if (_kbhit()) { break; }
	}
}
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
int streqa(char *a,char *b){
int i=0,L=0;
if(length(a)!=length(b)){return 0;}
else{
	L=length(a);
	for(;i<L;i++){
	if(a[i]==b[i]){continue;}
	else{return 0;}
	}
}
return 1;
}
int main(int argc, char* argv[]){
int result=0;
char fixer=0;
char cmdl[2048] = "";
	if (argc == 1) { 
		while (1) {
			printf("运行：>>");
			scanf("%[^\n]", &cmdl);
			fixer=getchar();//修复不认换行符的毛病
			//std::cin.getline(cmdl,1023);
			if (streqa(cmdl,"end")) { return 0; }
			if (streqa(cmdl, "stop")) { pause(); continue; }
			if (_strcmp(cmdl, "sleep ")) { Sleep(Number(cmdl+6)); continue; }
			if (_strcmp(cmdl, "open ")) { result=system(cmdl + 5);printf("程序已退出，返回值为%d.\n",result); 					continue; }
			if (_strcmp(cmdl, "alert ")) { MessageBoxA(0, (cmdl + 6),"消息",MB_OK); continue; }
			result=system(cmdl);
			printf("程序已退出，返回值为%d.\n",result);
		}
	}
	if (argc > 1) {
		result=system(argv[1]);
		printf("程序已退出，返回值为%d.\n",result);
	}
}