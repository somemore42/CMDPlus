#undef UNICODE
#undef _UNICODE
//#define _WIN32_WINNT 0x0500
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<winuser.h>
#include<time.h>
#define BlankTime 50
//tcc requires use 0 instead of NULL!
//HWND __stdcall GetConsoleWindow(void);
//extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow ();
//#include<wincon.h>
//#include<ConsoleApi3.h>
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址
struct operation {
	int v1;
	int v2;
	char name[25];
	char argv1[40];
	char argv2[20];
	char argv3[20];
	
}obj;
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
int strcopy(char* target, char* origin) {
	int i = 0;
	for (i = 0; origin[i] != 0; i++) {
		target[i] = origin[i];
	}
	//i++;
	target[i] = '\0';
	return i;
}
void strlink(char* p, char* str) {
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
	p[e + i] = '\0';
}
void strlinkc(char* p, const char* str) {
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
	p[e + i] = '\0';
}
void moveForeWindow(int x, int y) {
	RECT rect;
	HWND d =GetForegroundWindow();
	GetWindowRect(d, &rect);
	MoveWindow(d, x, y, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}
void moveWindow(HWND hq,int x, int y) {
	RECT rect;
	GetWindowRect(hq, &rect);
	MoveWindow(hq, x, y, rect.right-rect.left, rect.bottom-rect.top, TRUE);
}

void vLClick(int x, int y) {
	//int x, y;
	//POINT vevent;
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	//GetCursorPos(&vevent);
	Sleep(BlankTime);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
void vRClick(int x, int y) {
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	Sleep(BlankTime);
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}
void vMClick(int x, int y) {
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
	Sleep(BlankTime);
	mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
}
void vWheelUp(int dd) {
	mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120 * dd, 0);
}
void vWheelDown(int dd) {
	mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -120 * dd, 0);
}
void moveTo(int x, int y) {
	SetCursorPos(x, y);
}
void moveBy(int dx, int dy) {
	mouse_event(MOUSEEVENTF_MOVE, dx, dy, 0, 0);
}

int closeWindowByName(char *name) {
	HWND hwnd = FindWindow(0, name);
	if (hwnd == 0) {
		return 0;
	}
	else {
		SendMessage(hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
		return 1;
	}

}
int closeForeWindow() {
	HWND hwnd = GetForegroundWindow();
	if (hwnd == 0) {
		return 0;
	}
	else {
		SendMessage(hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
		return 1;
	}

}
void reSizeWindow(HWND hwnd,int w, int h) {
	RECT rect;
	GetWindowRect(hwnd, &rect);
	MoveWindow(hwnd, rect.left, rect.top, w, h, TRUE);
}
void titleWindow(HWND hwnd,char t[]) {
	SetWindowTextA(hwnd, t);
}
void closeWindow(HWND hwnd) {
	if(hwnd!=0)SendMessage(hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
}

int split(char *cmd,char *cpp) {
	int i = 0;
	int j = 0;
	int lastpace = 0;
	int now = 0;
	if (cmd[0] == ' ') { lastpace = 1;  }
	while (cmd[i] != '\0') {
		if (cmd[i]==' ') {
			if (lastpace) {
				i++;
				lastpace = 1;
			}
			else {
				cpp[j] = '\0';
				j++;
				lastpace = 1;
				i++;
				now++;
			}
		}
		else {
				cpp[j] = cmd[i];
				j++;
				lastpace = 0;
				i++;
		}
	}
	cpp[j] = '\0';
	if(!lastpace)now++;
	return now;
}
int length(char c[]) {
	int len = 0;
	for (int i = 0; i < 25585; i++) {
		if (c[i] == '\0')break;
		len++;
	}
	return len;
}
int lengthc(const char c[]) {
	int len = 0;
	for (int i = 0; i < 25585; i++) {
		if (c[i] == '\0')break;
		len++;
	}
	return len;
}
int strmac(char t[], const char o[]) {
	int hex = 'a' - 'A';
	int len = 0;
	if (length(t) != lengthc(o)) { return 0; }
	int sup = length(t);
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
int streqa(char* a, char* b) {
	int i = 0, L = 0;
	if (length(a) != length(b)) { return 0; }
	else {
		L = length(a);
		for (; i < L; i++) {
			if (a[i] == b[i]) { continue; }
			else { return 0; }
		}
	}
	return 1;
}
void prase(char *clk,char *temp,int line) {
	int x = 0;
	x = split(clk, temp);
	int l = 0;
	char* poc = temp;
	for (int d = 0; d < x; d++) {
		if (d == 0) {
			strcopy(obj.name, poc+l);
			//obj.name[0] = 0;
			//strlink(obj.name,poc+l);
		}
		if (d == 1) {
			strcopy(obj.argv1, poc+l);
		}
		if (d == 2) {
			strcopy(obj.argv2, poc+l);
		}
		if (d == 3) {
			strcopy(obj.argv3, poc+l);
		}
		if (d > 3) {
			printf("Fatal Error:Line %d has %d paramers.\n", line, x);
			break;
		}
		l += length(poc+l);
		l++;
		//poc++;
	}
	
}
void SetKeyBig(BOOL big)
{
	// 判断键盘CapsLock键是否开启状态,开启状态则为大写,否则为小写
	if (GetKeyState(VK_CAPITAL))
	{
		// 如果当前键盘状态为大写,要求改小写,则模拟按键CapsLock切换状态
		if (!big)
		{
			keybd_event(VK_CAPITAL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
			keybd_event(VK_CAPITAL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		}
	}
	else
	{
		// 如果当前键盘状态为小写,要求改大写,则模拟按键CapsLock切换状态
		if (big)
		{
			keybd_event(VK_CAPITAL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
			keybd_event(VK_CAPITAL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		}
	}
}
void AnalogKey(char* str)
{
	int iLen = 0;
	char* tmp = 0;
	INPUT* keys = 0;
	BOOL bOldState = FALSE;

	// 保存此操作前的键盘状态
	bOldState = (BOOL)GetKeyState(VK_CAPITAL);
	iLen = length(str);
	tmp = (char*)malloc(iLen);
	memmove(tmp, str, iLen);
	for (int i = 0; i < iLen; i++)
	{
		// 某些符号非直属键盘按键,这里只过滤转换两个,以后用到其它字符自行添加过滤
		if (tmp[i] == ' ')
		{
			// 产生一个击键消息步骤:按下->抬起
			keybd_event(VK_SPACE, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
			keybd_event(VK_SPACE, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		}
		else if (tmp[i] == ',')
		{
			keybd_event(VK_OEM_COMMA, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
			keybd_event(VK_OEM_COMMA, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		}
		else if (tmp[i] >= 'a' && tmp[i] <= 'z')
		{ // 根据字符大小写切换键盘大小写状态
			SetKeyBig(0);
			// keybd_event只识别大写
			keybd_event((BYTE)tmp[i] - 32, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
			keybd_event((BYTE)tmp[i] - 32, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		}
		else if ((tmp[i] >= 'A' && tmp[i] <= 'Z') || (tmp[i] >= '0' && tmp[i] <= '9'))
		{
			SetKeyBig(1);
			keybd_event((BYTE)tmp[i], 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
			keybd_event((BYTE)tmp[i], 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		}
		else
		{
			keybd_event((BYTE)tmp[i] + 64, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
			keybd_event((BYTE)tmp[i] + 64, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		}
	}
	// 恢复此操作之前的键盘状态
	SetKeyBig(bOldState);
	free(tmp);
}
int main(int argc, char* argv[]) {
	int x = 0;
	int y = 0;
	int type = 0;
	int line = 0;//记录操作码读取到哪一行了
	char isShowCode = 0;//是否输出操作码
	char operate = 0;
	char commandline[255] = "";
	char temp[255] = "";
	HWND hwnd = 0;
	FILE *code;
	if (argc == 1) {
		printf("[COMMAND] VirtualEvent [Virsual_Mouse Operation-Code File path(*.voc)]\n");
		//VirtualEvent [operation:L|M|R|W|T|B|F] [values:x y|number]\n
		//char clk[] = "    MoveWindowByName    Release   120    0 ";
		//prase(clk,temp,1);
		//obj.v1 = Number(obj.argv2);
		//printf("%d\n",obj.v1);
		//char clk2[] = "    MoveWindowByName    Release   20    0 ";
		//obj.v1 = Number(obj.argv2);
		//printf("%d\n", obj.v1);
		//if (strmac(obj.name, "MoveWindowByName")) { printf("Mac!\n"); }
		//Sleep(1000);
		return 1;
	}
	if (argc >= 2) {
		if (argc == 2) {
			if ((code = fopen(argv[1], "r")) == 0)
			{
				printf("打开操作码文件失败！\n"); return 1;
			}
			while (fgets(commandline, 255, code) != 0) {
				line++;

				type = length(commandline);
				if (commandline[type - 1] == '\n') {//BUG：2024-6-25 13:45:22防止末行指令读取少字节
					commandline[type - 1] = '\0';
				}
				//BUG2024年6月24日18:21:26修复
				//Fuck!
				// fget获得的字符
				//串最后一个竟然是换行符，
				// 导致最后一个数字字符串参数转换为整数是总是出错！
				// 浪费我几个小时的生命！！！MD
				
				obj.name[0] = '\0'; 
				obj.argv1[0] = '\0'; obj.argv2[0] = '\0'; obj.argv3[0] = '\0';
				obj.v1 = 0; obj.v2 = 0;
				temp[0] = 0;

				prase(commandline,temp,line);

				if(strmac(obj.name,"Click")) {//左键单击
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					vLClick(obj.v1,obj.v2);
					//printf("Click\n");
				}
				if (strmac(obj.name, "MiddleClick")) {//中键单击
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					vMClick(obj.v1, obj.v2);
				}
				if (strmac(obj.name, "RightClick")) {//右键单击
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					vRClick(obj.v1, obj.v2);
				}
				if (strmac(obj.name, "WheelUp")) {//滚轮滚动
					obj.v1 = Number(obj.argv1);
					vWheelUp(obj.v1);
				}
				if (strmac(obj.name, "WheelDown")) {//滚轮滚动
					obj.v1 = Number(obj.argv1);
					vWheelDown(obj.v1);
				}
				if (strmac(obj.name, "CloseWindow")) {//关闭句柄所指向的窗口
					closeWindow(hwnd);
				}
				if (strmac(obj.name, "GetForeWindow")) {//让句柄指向当前的窗口
					//getForeWindow(hwnd);
					hwnd=GetForegroundWindow();
				}
				if (strmac(obj.name, "GetWindowByTitle")) {//句柄指向有该标题的窗口
					hwnd= FindWindow(0, obj.argv1);
					if (!hwnd) { printf("窗口%s没有找到。\n", obj.argv1); hwnd = GetForegroundWindow(); }
				}
				if (strmac(obj.name, "SizeWindow")) {//改变句柄所指向的窗口尺寸
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					reSizeWindow(hwnd,obj.v1,obj.v2);
				}
				if (strmac(obj.name, "MoveWindow")) {//移动句柄所指向的窗口
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					moveWindow(hwnd, obj.v1, obj.v2);
				}
				if (strmac(obj.name, "GOTO")) {//将光标挪到（x,y）处
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					moveTo( obj.v1, obj.v2);
				}
				if (strmac(obj.name, "GOBY")) {//按变化量改变光标位置
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					moveBy(obj.v1, obj.v2);
				}
				if (strmac(obj.name, "Sleep")) {//改变句柄所指向的窗口尺寸
					obj.v1 = Number(obj.argv1);
					Sleep(obj.v1);
				}
				if (strmac(obj.name, "Titlewindow")) {//改变句柄所指向的窗口标题
					SetWindowTextA(hwnd, obj.argv1 );
				}
				if (strmac(obj.name, "MouseMove")) {//鼠标移动
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					mouse_event(MOUSEEVENTF_MOVE, obj.v1, obj.v2, 0, 0);
				}
				if (strmac(obj.name, "MouseDown")) {//鼠标按下
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					mouse_event(MOUSEEVENTF_LEFTDOWN, obj.v1, obj.v2, 0, 0);
				}
				if (strmac(obj.name, "MouseUp")) {//鼠标松开
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					mouse_event(MOUSEEVENTF_LEFTUP, obj.v1, obj.v2, 0, 0);
				}
				if (strmac(obj.name, "MouseRightDown")) {//右键按下
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					mouse_event(MOUSEEVENTF_RIGHTDOWN, obj.v1, obj.v2, 0, 0);
				}
				if (strmac(obj.name, "MouseRightUp")) {//右键松开
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					mouse_event(MOUSEEVENTF_RIGHTUP, obj.v1, obj.v2, 0, 0);
				}
				if (strmac(obj.name, "MouseMiddleDown")) {//滚轮按下
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					mouse_event(MOUSEEVENTF_MIDDLEDOWN, obj.v1, obj.v2, 0, 0);
				}
				if (strmac(obj.name, "MouseMiddleUp")) {//滚轮松开
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					mouse_event(MOUSEEVENTF_MIDDLEUP, obj.v1, obj.v2, 0, 0);
				}
				if (strmac(obj.name, "EchoOn")) {//滚轮松开
					isShowCode = 1;
				}
				if (strmac(obj.name, "EchoOff")) {//滚轮松开
					isShowCode = 0;
				}
				if (strmac(obj.name, "Rem")) {//滚轮松开
					
				}
				if (isShowCode == 1)printf("<< %s\n", commandline);
				if (strmac(obj.name, "HideRun")) {//不显示DOSbox
					ShowWindow(GetConsoleWindow(), SW_HIDE);
				}
				if (strmac(obj.name, "ShowRun")) {//显示DOSbox
					ShowWindow(GetConsoleWindow(),SW_SHOW);
				}
				if (strmac(obj.name, "setKeyboardBig")) {//键盘大写
					SetKeyBig(1);
				}
				if (strmac(obj.name, "setKeyboardSmall")) {//键盘小写
					SetKeyBig(0);
				}
				if (strmac(obj.name, "keyBoard")) {//模拟键盘输入
					AnalogKey(obj.argv1);
				}
				if (strmac(obj.name, "MessageBox")) {//模拟键盘输入
					obj.v1 = Number(obj.argv3);
					if (obj.v1 == 5) {
						MessageBoxA(0, obj.argv1, obj.argv2, MB_OK | MB_RIGHT);
					}
					else if (obj.v1 == 0)
						MessageBoxA(0, obj.argv1, obj.argv2, MB_OK);
					else if (obj.v1 == 3)
						MessageBoxA(0, obj.argv1, obj.argv2, MB_OK | MB_ICONERROR);
					else if (obj.v1 == 2)
						MessageBoxA(0, obj.argv1, obj.argv2, MB_OK | MB_ICONWARNING);
					else if (obj.v1 == 1)
						MessageBoxA(0, obj.argv1, obj.argv2, MB_OK | MB_ICONINFORMATION);
					else if (obj.v1 == 4)
						MessageBoxA(0, obj.argv1, obj.argv2, MB_OK | MB_CANCELTRYCONTINUE);
					else MessageBoxA(0, obj.argv1, obj.argv2, MB_OK);
				}
				if (strmac(obj.name, "system")) {//模拟键盘输入
					temp[0] = '\0';
					if (obj.argv1[0] != '\0') { 
						strlink(temp, obj.argv1);
					}
					if (obj.argv2[0] != '\0') {
						strlinkc(temp, " ");
						strlink(temp, obj.argv2);
					}
					if (obj.argv3[0] != '\0') {
						strlinkc(temp, " ");
						strlink(temp, obj.argv3);
					}
					type=system(temp);
					if (isShowCode) { printf("进程已退出，返回值为%d.\n",type); }
				}
				//printf(">>%s %s %s %s \n", obj.name, obj.argv1, obj.argv2, obj.argv3);
			};
		}
	}
	return 0;
}
/*
参数介绍：
dwFlags：标志位集，指定点击按钮和鼠标动作的多种情况。
　　MOOSEEVENTF_MOVE：		移动。
　　MOOSEEVENTF_LEFTDOWN：	按下鼠标左键。
　　MOOSEEVENTF_LEFTUP：		松开鼠标左键。
　　MOOSEEVENTF_RIGHTDOWN：	按下鼠标右键。
　　MOOSEEVENTF_RIGHTUP：	松开鼠标右键。
　　MOOSEEVENTF_MIDDLEDOWN：	按下鼠标中键。
　　MOOSEEVENTF_MIDDLEUP：	松开鼠标中键。
　　MOOSEEVENTF_WHEEL：在Windows NT中如果鼠标有一个轮，表明鼠标轮被移动。移动的数量由dwData给出。
dx：指定鼠标沿x轴的绝对位置或者从上次鼠标事件产生以来移动的数量，依赖于MOOSEEVENTF_ABSOLOTE的设置。给出的绝对数据作为鼠标的实际X坐标；给出的相对数据作为移动的mickeys数。一个mickey表示鼠标移动的数量，表明鼠标已经移动。
dy：指定鼠标沿y轴的绝对位置或者从上次鼠标事件产生以来移动的数量，依赖于MOOSEEVENTF_ABSOLVTE的设置。给出的绝对数据作为鼠标的实际y坐标，给出的相对数据作为移动的mickeys数。
dwData：如果dwFlags为MOOSEEVENTF_WHEEL，则dwData指定鼠标轮移动的数量。正值表明鼠标轮向前转动，即远离用户的方向；负值表明鼠标轮向后转动，即朝向用户。一个轮击定义为WHEEL_DELTA，即120。如果dwFlagsS不是MOOSEEVENTF_WHEEL，则dWData应为零。
dwExtralnfo：指定与鼠标事件相关的附加32位值。应用程序调用函数GetMessgeExtrajnfo来获得此附加信息。
*/