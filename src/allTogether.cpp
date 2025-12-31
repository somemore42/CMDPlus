#undef UNICODE
#undef _UNICODE
#include<stdio.h>
#include<windows.h>
int C2N(char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 10;
	return 0;
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
/*
void moveWindow(int x, int y,HWND hwnd) {
	RECT rect;
	GetWindowRect(hwnd, &rect);
	if (x < 0||x>1000)x = 0;
	if (y < 0 || y>900)y = 0;
	MoveWindow(hwnd, x, y, rect.right-rect.left, rect.bottom-rect.top, TRUE);
}
void reSizeWindow(int w, int h, HWND hwnd) {
	RECT rect;
	GetWindowRect(hwnd, &rect);
	if (w < 80 || h>900)return;
	if (h < 10 || h>1000)return;
	MoveWindow(hwnd, rect.left, rect.top, w, h, TRUE);
}
void titleWindow(char t[], HWND hwnd) {
	SetWindowTextA(hwnd, t);
}
int query(HWND h,char c) {
	POINT point;
	GetCursorPos(&point);
	if (c == 'x') {
		return point.x;
	}
	if (c == 'y') {
		return point.y;
	}
	RECT rect;
	HWND WFP = WindowFromPoint(point);
	if (WFP == 0)return 0;
	GetWindowRect(WFP, &rect);
	if (c == 'w') {
		return rect.right - rect.left;
	}
	if (c == 'h') {
		return rect.bottom - rect.top;
	}
}
*/
/*
void setTextColorByName(char c[]) { 
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_strcmp(c, "purple") || _strcmp(c, "6")) {
		SetConsoleTextAttribute(hand, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//purple
	}else 
		if (_strcmp(c, "cuilv") || _strcmp(c, "5")) {
			SetConsoleTextAttribute(hand, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);//cuilv
		}
		else if (_strcmp(c, "white") || _strcmp(c, "0")) {
			SetConsoleTextAttribute(hand, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//white
		}
		else if (_strcmp(c, "blue") || _strcmp(c, "3")) {
			SetConsoleTextAttribute(hand, FOREGROUND_INTENSITY | FOREGROUND_BLUE);//blue
		}else
			if (_strcmp(c, "yellow") || _strcmp(c, "2")) {
				SetConsoleTextAttribute(hand, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);//yellow
			}
			else if (_strcmp(c, "red") || _strcmp(c, "1")) {
				SetConsoleTextAttribute(hand, FOREGROUND_INTENSITY | FOREGROUND_RED);//red
			}
			else if (_strcmp(c, "green") || _strcmp(c, "4")) {
				SetConsoleTextAttribute(hand, FOREGROUND_INTENSITY | FOREGROUND_GREEN);//green
			}
}
void setBackColorByName(char c[]) {
	
	BACKGROUND_BLUE;//背景颜色包含蓝色
	BACKGROUND_GREEN;//	背景颜色包含绿色
	BACKGROUND_RED;	//背景颜色包含红色
	BACKGROUND_INTENSITY;//
	
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_strcmp(c, "purple") || _strcmp(c, "6"))
		SetConsoleTextAttribute(hand, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE);//purple
	else if (_strcmp(c, "cuilv") || _strcmp(c, "5"))
		SetConsoleTextAttribute(hand, BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);//cuilv
	else if (_strcmp(c, "white") || _strcmp(c, "0"))
		SetConsoleTextAttribute(hand, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);//white
	else if (_strcmp(c, "blue") || _strcmp(c, "3"))
		SetConsoleTextAttribute(hand, BACKGROUND_INTENSITY | BACKGROUND_BLUE);//blue
	else if (_strcmp(c, "yellow") || _strcmp(c, "2"))
		SetConsoleTextAttribute(hand, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);//yellow
	else if (_strcmp(c, "red") || _strcmp(c, "1"))
		SetConsoleTextAttribute(hand, BACKGROUND_INTENSITY | BACKGROUND_RED);//red
	else if (_strcmp(c, "green") || _strcmp(c, "4"))
		SetConsoleTextAttribute(hand, BACKGROUND_INTENSITY | BACKGROUND_GREEN);//green
}
void setTextColorByNumber(int c) {
	if (c <= 0 || c >= 255) { c += 1; c %= 255; }
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, c);
}*/
int closeWindow(char name[]) {
	HWND hwnd = FindWindow(NULL, name);
	if (hwnd == NULL) {
		return 0;
	}
	else {
		SendMessage(hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
		return 1;
	}
	
}
int closeForeWindow() {
	HWND hwnd = GetForegroundWindow();
	if (hwnd == NULL) {
		return 0;
	}
	else {
		SendMessage(hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
		return 1;
	}

}
BOOL CALLBACK EnumWindowsProc(HWND hwnd,char title[])
{
	char wtitle[512];
	GetWindowText(hwnd, wtitle, sizeof(wtitle));
	if (strstr(wtitle, title))
	{
		::SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
	return (true);
}


VOID ManagerRun(LPCSTR exe, LPCSTR param, INT nShow = SW_SHOW)
{ //注意：会跳出提示。
	SHELLEXECUTEINFO ShExecInfo;
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = "runas";
	ShExecInfo.lpFile = exe;
	ShExecInfo.lpParameters = param;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = nShow;
	ShExecInfo.hInstApp = NULL;
	BOOL ret = ShellExecuteEx(&ShExecInfo);
	//等不及了，不等了。
	CloseHandle(ShExecInfo.hProcess);
	return;
}


bool IsProcessRunAsAdmin()
{
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;
	BOOL b = AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&AdministratorsGroup);
	if (b)
	{
		CheckTokenMembership(NULL, AdministratorsGroup, &b);
		FreeSid(AdministratorsGroup);
	}
	return b == TRUE;
}
short GetAdmin(LPCSTR Param, int Showcmd)
{
	if (IsProcessRunAsAdmin())
		return 0;
	TCHAR Path[MAX_PATH];
	ZeroMemory(Path, MAX_PATH);
	::GetModuleFileName(NULL, Path, MAX_PATH);           //获取程序路径
	HINSTANCE res;
	res = ShellExecute(NULL, "runas", Path, Param, NULL, Showcmd);
	if ((int)res > 32)
		return 1;
	else
		return 0;
}
void hideConsole() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}
int main(int argc, char* argv[], char* envp[]) {
	if (IsProcessRunAsAdmin()) {
		printf("\n本程序已经以管理员权限运行\n");
	}
	else {
		printf("\n正在申请管理员权限\n");
		GetAdmin(argv[0],0);
	}
	if (argc == 1) { 
		//hideConsole();
		//if (closeForeWindow()) { printf("已向当前窗口发送关闭消息\n"); }
		//else { printf("没有找到当前窗口 \n"); }
		//printf("\n参数：closeForeWindow \\[延迟执行时间]\n");
	}
	if (argc == 2) {
		
		//HWND hwnd = GetForegroundWindow();
		//printf("\n%d\n",query(hwnd, argv[1][0]));
		//titleWindow(argv[1], hwnd);
		//setBackColorByName(argv[1]);
		//setTextColorByNumber(Number(argv[1]));
		//if (closeWindow(argv[1])) { printf("已向窗口 %s 发送关闭消息\n", argv[1]); }
		//else { printf("没有找到窗口 %s \n",argv[1]); }
		//Sleep(Number(argv[1]));
		//hideConsole();
		//if (closeForeWindow()) { printf("已向当前窗口发送关闭消息\n"); }
		//else{ printf("没有找到当前窗口 \n"); }
	}
	if (argc >2) {
		//printf("\n参数：closeForeWindow \\[延迟执行时间]\n");
		//Sleep(Number(argv[2]));
		//HWND hwnd = GetForegroundWindow();
		//printf("\n%d\n", query(hwnd, argv[1][0]));
		//titleWindow(argv[1], hwnd);
		//setBackColorByName(argv[1]);
		//(Number(argv[1]));
		//if (closeWindow(argv[1])) { printf("已向窗口 %s 发送关闭消息\n", argv[1]); }
		//else { printf("没有找到窗口 %s \n",argv[1]); }
		//printf("\n参数：hideConsole \\[延迟执行时间]\n");
	}
	return 0;
}