#include<stdio.h>
#include<windows.h>
//#include<winuser.h>
//Common Finction
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
const char index[40] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char* String(int num, char* str, int radix) {
		unsigned unum; int i = 0, j, k;
		if (radix == 10 && num < 0) { unum = (unsigned)-num; str[i++] = '-'; }
		else unum = (unsigned)num; do { str[i++] = index[unum % (unsigned)radix]; unum /= radix; } while (unum);
		str[i] = '\0'; if (str[0] == '-') k = 1; else k = 0; char temp;
		for (j = k; j <= (i - 1) / 2; j++) { temp = str[j]; str[j] = str[i - 1 + k - j]; str[i - 1 + k - j] = temp; }return str;
}
void strcopy(char* target, char* origin) {
	int i = 0;
	for (i = 0; origin[i] != 0; i++) {
		target[i] = origin[i];
	}
	target[i] = '\0';
}
void strcopyc(char* target, const char* origin) {
	int i = 0;
	for (i = 0; origin[i] != 0; i++) {
		target[i] = origin[i];
	}
	target[i] = '\0';
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
int strmac(char* t,const char* o) {
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
void Frametransparent(HWND hwnd, int frame)
{
    long style = GetWindowLong(hwnd, GWL_STYLE);
    if (frame)
    {
        style |= WS_CAPTION;              //加上边框
    }
    else
    {
        style &= ~WS_CAPTION;              //去掉边框
    }
    SetWindowLong(hwnd, GWL_STYLE, style);        //设置完成 
//SetLayeredWindowAttributes(hwnd,RGB(255,255,255),0,LWA_COLORKEY);
}
int argc=0;
char cmdtemp[1024]="";
char argv[15][128];
char safetyBuffer[20]="";
int split(char *cmd,char *cpp) {
	int i = 0;
	int j = 0;
	int lastpace = 0;
	int now = 0;
	if (cmd[0] == ' ') { lastpace = 1;  }
	if(cmd[0]=='\0'){cpp[0]='\0';return 0;}
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
void prase(char* clk, char* temp) {
	int x = 0;
	int end=length(clk)-1;
//去除命令行收尾的冒号
//if(clk[0]=='"'){clk[0]=' ';}
//if(clk[end]=='"'){clk[end]='\0';}
	x = split(clk, temp);
	argc=x;
	int l = 0;
	char* poc = temp;
	for (int d = 0; d < x; d++) {
	if (d >=15) {
			printf("Command Warring:Command Line has %d paramers.That is to much.\n", x);
			break;
		}
		strcopy(argv[d], poc + l);
		l += length(poc + l);
		l++;
	}
}
//.data
char WinBoxName[50] = "MotoBoard_micro"; // The name of this application
char WinBoxTitle[50] = "MotoBoard"; // The title bar text
char Moto[255]="";
int Width=750;
int Height=300;
int WinBoxX=0;
int WinBoxY=0;
char isAllowResize=1;
char isAllowQuit=1;
char isWithFrame=1;
char isBoxCenter=1;
HWND hwnd;
HGDIOBJ hPen,hBrush;
PAINTSTRUCT	ps;
HDC	hdc;
RECT	rc;
struct boardColor{
	char r;
	char g;
	char b;
}rgb;
const char option[4][10]={"noFrame","noClose","top","center"};
//.text
void DrawMain(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    hdc = BeginPaint(hwnd, &ps);
    hBrush = CreateSolidBrush(RGB(rgb.r,rgb.g,rgb.b));
    GetClientRect(hwnd, &rc);
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkColor(hdc,RGB(rgb.r,rgb.g,rgb.b));
    SetBkMode(hdc, TRANSPARENT);

	FillRect(hdc,&rc,hBrush);
	DrawText(hdc, Moto, -1, &rc, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
	//TextOut(hdc, Width/2, Height/2, Moto, length(Moto));

    DeleteObject(hBrush);
    EndPaint(hwnd, &ps);
}
void CreatMain(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

if(isBoxCenter==1){
    HWND hwnd_parent;
    RECT rw_self, rc_parent, rw_parent;
    hwnd_parent = GetParent(hwnd);
    if (NULL == hwnd_parent){ hwnd_parent = GetDesktopWindow();}
    GetWindowRect(hwnd_parent, &rw_parent);
    GetClientRect(hwnd_parent, &rc_parent);
    GetWindowRect(hwnd, &rw_self);
   WinBoxX = rw_parent.left + (rc_parent.right + rw_self.left - rw_self.right) / 2;
   WinBoxY= rw_parent.top + (rc_parent.bottom + rw_self.top - rw_self.bottom) / 2;
}
if(isAllowResize==1){SetWindowPos(hwnd, NULL,WinBoxX, WinBoxY, 0, 0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);}
else{SetWindowPos(hwnd, HWND_TOPMOST,WinBoxX, WinBoxY, 0, 0,SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);}

}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        // ----------------------- first and last
    case WM_CREATE:
        CreatMain(hwnd, message, wParam, lParam);
        break;
    case WM_CLOSE:
	if(isAllowQuit==1){DestroyWindow(hwnd);}
	break;
    case WM_DESTROY:
       {
	if(isAllowQuit==1){PostQuitMessage(0);}
	break;
	}
        // ----------------------- get out of it...
/*    case WM_RBUTTONUP:
        break;
    case WM_MOUSEMOVE:
        break;
    case WM_KEYDOWN:
        break;
*/
        // ----------------------- display our minimal info
    case WM_PAINT:
    {
        DrawMain(hwnd, message, wParam, lParam);
        break;
    }
    // ----------------------- let windows do all other stuff
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
//首先将命令行解析并装载参数
//[COMMAND]:MOTOBOARD TextContent  /width*height /x,y /red,green,blue /option:f=noFrame;c=noExit;t=topMost;
prase(lpCmdLine,cmdtemp);
if(argc==0){
strcopyc(Moto,"[COMMAND]:MotoBoard [text] [width] [height] [x] [y] [red] [green] [blue] [option:noFrame noClose top center]");
}
if(argc>=1){
strcopy(Moto,argv[0]);
}
if(argc>=3){
Width=Number(argv[1]);
Height=Number(argv[2]);
}
if(argc>=5){
isBoxCenter=0;
WinBoxX=Number(argv[3]);
WinBoxY=Number(argv[4]);
}
if(argc>=8){
rgb.r=Number(argv[5]);
rgb.g=Number(argv[6]);
rgb.b=Number(argv[7]);
}else{
rgb.r=255;
rgb.g=255;
rgb.b=255;
}
for(int i=9;i<=argc;i++){
if(strmac(argv[i-1],option[0])){isWithFrame=0;}
if(strmac(argv[i-1],option[1])){isAllowQuit=0;}
if(strmac(argv[i-1],option[2])){isAllowResize=0;}
if(strmac(argv[i-1],option[3])){isBoxCenter=1;}
}
    MSG msg;
    WNDCLASS wc;
//Start of NOCHANGE part!
    ZeroMemory(&wc, sizeof(wc));
    wc.hInstance = hInstance;
    wc.lpszClassName = WinBoxName;
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);
    hwnd = CreateWindow(
       WinBoxName,
        WinBoxTitle,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        Width,//CW_USEDEFAULT
        Height,//CW_USEDEFAULT
        0,
        0,
        hInstance,
        0);
if(hwnd==0){return 500;}
SetActiveWindow(hwnd);
SetForegroundWindow(hwnd);
if(isAllowResize!=1){LockSetForegroundWindow(LSFW_LOCK);}
if(isWithFrame!=1){Frametransparent(hwnd, 0);}

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
//end of NOCHANGE part
}