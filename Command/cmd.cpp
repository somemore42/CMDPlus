#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<fstream>
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
	for (int i = 0;i<25585; i++) {
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
	if (length(t) <length(o)) { return 0; }
	int sup = _min(length(t), length(o));
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
int main(int argc, char* argv[], char* envp[]) {
	int mode = 0;
	char cmdl[1024] = "";
	if (argc == 1) { 
		while (1) {
			printf("运行：>>");
			//scanf("%s", &cmdl);
			std::cin.getline(cmdl,1023);
			if (_strcmp(cmdl,"end")) { return 0; }
			if (_strcmp(cmdl, "stop")) { pause(); continue; }
			if (_strcmp(cmdl, "sleep")) { Sleep(Number(cmdl+6)); continue; }
			if (_strcmp(cmdl, "open")) { system(cmdl + 5); continue; }
			if (_strcmp(cmdl, "alert")) { MessageBoxA(0, (cmdl + 6),"提示",MB_OK); continue; }
			system(cmdl);
		}
	}
	if (argc > 1) {
		mode = Number(argv[1]);
		std::ifstream cmd;
		cmd.open(argv[1]);
		while (cmd.eof()==0) {
			cmd.getline(cmdl, 1023);
			if (_strcmp(cmdl, "end")) { return 0; }
			if (_strcmp(cmdl, "stop")) { pause(); continue; }
			if (_strcmp(cmdl, "sleep")) { Sleep(Number(cmdl + 6)); continue; }
			if (_strcmp(cmdl, "open")) { system(cmdl + 5); continue; }
			if (_strcmp(cmdl, "alert")) { MessageBoxA(0, (cmdl + 6), "提示", MB_OK); continue; }
			system(cmdl);
		}
		cmd.close();
	}
	pause();
	return 0;
}