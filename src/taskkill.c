#include<stdio.h>
#include<windows.h>
int C2N(char c){
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
	int sign=1;
if(c[0]=='-'){sign=-1;}
	while (c[i] != 0) {
		n *= 10;
		n += C2N(c[i]);
		i++;
	}
	return n*sign;
}
int KillProcess(DWORD ProcessId) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, ProcessId);
    if (hProcess == NULL)
        return -1;
    if (!TerminateProcess(hProcess, 0)) {
        printf("TerminateProcess failure!");
        return -1;
    }
    return 0;
}
int main(int argc, char* argv[]){
int c=0;
int r=0;
if(argc==1){
printf("Input the PID of target process>>");
scanf("%d",&c);
}
if(argc==2){
c=Number(argv[1]);
}
if(argc>2){
return 1;
}
r=KillProcess((DWORD)c);
return r;
}