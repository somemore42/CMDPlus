#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include<stdio.h>
#include<conio.h>
#include<windows.h>
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
	for (int i = 0; i < 25585; i++) {
		if (c[i] == '\0')break;
		len++;
	}
	return len;
}
int length(const char c[]) {
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
int _abs(int d) {
	if (d == 0)return 0;
	if (d > 0)return d;
	if (d < 0)return -d;
	return -1;
}
int _strcmp(char t[], const char o[]) {
	int hex = 'a' - 'A';
	int len = 0;
	if (length(t) < length(o)) { return 0; }
	int sup = _min(length(t), length(o));
	for (int i = 0; i < sup; i++) {
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
	printf("\n已停止，按任意键继续运行\n");
	while (1) {
		if (_kbhit()) { break; }
	}
}
int main(int argc, char* argv[], char* envp[]) {
	int mode = 0;
	if (argc == 1) {
		printf("\n参数：MessageBox [TEXT_CONTENT] \\[模式] \\[TITLE]\n模式可选：\n0:仅文本\n1:信息\n2:警告\n3:错误\n4:取消重试继续\n");
		pause();
	}
	if (argc == 2) {
		MessageBoxA(0, argv[1], "提示", MB_OK);
	}
	if (argc == 3) {
		mode = Number(argv[2]);
		if(mode<0||mode>4)
			MessageBoxA(0, argv[1], "提示", MB_OK | MB_RIGHT);
		if(mode==0)
		    MessageBoxA(0, argv[1], "提示", MB_OK);
		if(mode==3)
			MessageBoxA(0, argv[1], "错误", MB_OK | MB_ICONERROR);
		if(mode==2)
			MessageBoxA(0, argv[1], "警告", MB_OK | MB_ICONWARNING);
		if(mode==1)
			MessageBoxA(0, argv[1], "信息", MB_OK | MB_ICONINFORMATION);
		if(mode==4)
			MessageBoxA(0, argv[1], "选择", MB_OK | MB_CANCELTRYCONTINUE);
	}
	if (argc > 3) {
		mode = Number(argv[2]);
		if (mode < 0 || mode>4)
			MessageBoxA(0, argv[1], argv[3], MB_OK | MB_RIGHT);
		if (mode == 0)
			MessageBoxA(0, argv[1], argv[3], MB_OK);
		if (mode == 3)
			MessageBoxA(0, argv[1], argv[3], MB_OK | MB_ICONERROR);
		if (mode == 2)
			MessageBoxA(0, argv[1], argv[3], MB_OK | MB_ICONWARNING);
		if (mode == 1)
			MessageBoxA(0, argv[1], argv[3], MB_OK | MB_ICONINFORMATION);
		if (mode == 4)
			MessageBoxA(0, argv[1], argv[3], MB_OK | MB_CANCELTRYCONTINUE);
	}
	return 0;
}