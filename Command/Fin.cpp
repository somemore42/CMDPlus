#include<stdio.h>
#include<conio.h>
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
int main(int argc, char* argv[], char* envp[]) {
	int mode = 0;
	if(argc==1){ printf("\n%s", "��������رմ˳���..."); }
	if (argc > 1) {
		mode = Number(argv[1]);
		if (mode > 2 || mode < 0) { printf("\n�������˳�������ֵΪ%d",mode); }
		if(mode==0){ printf("\n%s", "��������������β���..."); }
		if(mode==1){ printf("\n%s", "Press Any Key to finish this operate."); }
		if (mode == 2) { printf("\n%s", "������ɣ���������˳���"); }
	}
	//"Press Any Key to finish this operate.";
	while (1) {
		if (_kbhit()) { return 0; }
	}
	return 0;
}