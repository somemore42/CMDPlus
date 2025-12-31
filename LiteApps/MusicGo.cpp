#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<graphics.h>
#include <math.h>
#include <time.h>
#pragma comment(lib, "Winmm.lib")

void ZT();       // 暂停
void BF1();      // 播放1
void BF2();      // 播放2
void BF3();      // 播放3
void menu();    // 总得
void locate(int a, int b, int c, int d, int e, LPCTSTR text);
void locate(int a, int b, int c, int d, int e, LPCTSTR text, COLORREF color);
void play(char* path);
int Return();
char cmd[1024] = "";
void strlink(char* p, char str[]) {
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
    p[e + i] = '\0';
}
void strlink(char* p, char str) {
    int e = 0;
    while (1) {
        if (p[e] == '\0') { break; }
        e++;
    }
    p[e] = str;
    p[e + 1] = '\0';
}
void Frametransparent(HWND hwnd, bool frame=0)      //去掉边框，只需调用EFrame(0);
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
}
int FileDialog_(char* path)
{
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn); // 结构大小
    //ofn.lpstrFile = path; // 路径
    ofn.lpstrFile = path;
    ofn.nMaxFile = MAX_PATH; // 路径大小
    ofn.lpstrFilter = TEXT("音频文件(mp3;avi)\0*.mp3;*.avi;*.mp4;*.wav;*.ape;*.wma;*flac\0\0"); // 文件类型
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    return GetOpenFileName(&ofn);
}
bool keep = 1;
char path[524] = "";
void aexit() {
    keep = 0;
}
void reSelect(char *c) {
    c[0] = '\0';
    FileDialog_(c);
}
bool SetWindowTransparent(HWND hwnd, COLORREF crkcolor, BYTE bAlpha, DWORD dwFlags)
{
    HINSTANCE hm = GetModuleHandle(_T("USER32.DLL"));
    if (hm)
    {
        FARPROC fun = GetProcAddress(hm, "SetLayeredWindowAttributes");
        bool (WINAPI * SetLayeredWindowAttributes)(HWND, COLORREF, BYTE, DWORD) = (bool (WINAPI*) (HWND, COLORREF, BYTE, DWORD))fun;

        if (SetLayeredWindowAttributes)
        {
            LONG ret = GetWindowLong(hwnd, GWL_EXSTYLE);
            ret |= WS_EX_LAYERED;
            SetWindowLong(hwnd, GWL_EXSTYLE, ret);
            SetLayeredWindowAttributes(hwnd, crkcolor, bAlpha, dwFlags);
        }
        FreeLibrary(hm);
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    initgraph(640, 280);
    setbkcolor(BLACK);
    cleardevice();
    HWND hwnd = GetHWnd();        // 获取窗口句柄
    Frametransparent(hwnd);
    
    //Frametransparent(hwnd, 0);
    SetActiveWindow(hwnd);
    SetForegroundWindow(hwnd);
    LockSetForegroundWindow(LSFW_LOCK);
    SetWindowTransparent(hwnd, BLACK, 100, 0x1);
    //SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);//hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE
    setfillcolor(BLUE);
    settextstyle(20, 0, _T("黑体"));
    setbkmode(TRANSPARENT);
    solidrectangle(200, 80, 440, 260);
    outtextxy(220, 230, _T("Music Player"));
    HDC d;
    RECT rect;
    LPSTR list[10] = {IDI_APPLICATION,IDI_ERROR,IDI_INFORMATION,IDI_QUESTION,IDI_WARNING,IDI_WINLOGO, IDI_EXCLAMATION ,IDI_HAND , IDI_SHIELD ,IDI_ASTERISK};
    HICON icohdc[10] = {};
    for (int i = 0; i < 10; i++) {
        icohdc[i] = LoadIcon(0, list[i]);
    }
        
       //DrawMenuBar
           //DrawAnimatedRects
   //Draw
       // IDI_SHIELD;
      // WHITE_
    //DrawText(IDI_ERROR);
    //DrawIcon(d,0,0,IDI_WINLOGO);
    //WHITE
    //SetBkColor(d,WHITE);
    //SetWindowsHook(NULL,NULL);
    //SetB
    //FileDialog_(path);
    while (keep)
    {
        int A = Return();    // 鼠标选择;
        switch (A)
        {
        case 0:ZT(); break;
        case 1:ZT(); play(path); break;
        case 2:reSelect(path); break;
        case 3:aexit(); break;
        }
    }
    closegraph();
    return 0;
}

void ZT()      // 暂停
{
    mciSendString(_T("stop mymusic"), NULL, 0, NULL);
    mciSendString(_T("close mymusic"), NULL, 0, NULL);
}
void play(char *path) {
    cmd[0] = '\0';
    strlink(cmd ,"open ");
    strlink(cmd,path);
    strlink(cmd, " alias mymusic");
    mciSendString(cmd, NULL, 0, NULL);
    //mciSendString(_T("open 1.mp3 alias mymusic"), NULL, 0, NULL);
    cmd[0] = '\0';
    strlink(cmd,"play mymusic");
    mciSendString(cmd, NULL, 0, NULL);
    //mciSendString(_T("play mymusic"), NULL, 0, NULL);
}

int Return()
{
    menu();
    MOUSEMSG m1;
    //BeginBatchDraw();
    while (1)
    {
        m1 = GetMouseMsg();
        switch (m1.uMsg)
        {
        case WM_MOUSEMOVE:

            menu();
            if (m1.x >= 220 && m1.x <= 420 && m1.y >= 100 && m1.y <= 130)
            {
                menu();
                locate(220, 100, 420, 130, 30, _T("暂停/结束"), RED);
                break;
            }

            if (m1.x >= 220 && m1.x <= 420 && m1.y >= 130 && m1.y <= 160)
            {
                menu();
                locate(220, 130, 420, 160, 30, _T("播放音乐"), RED);
                break;
            }

            if (m1.x >= 220 && m1.x <= 420 && m1.y >= 160 && m1.y <= 190)
            {
                menu();
                locate(220, 160, 420, 190, 30, _T("选择音乐"), RED);
            }
            if (m1.x >= 220 && m1.x <= 420 && m1.y >= 190 && m1.y <= 220)
            {
                menu();
                locate(220, 190, 420, 220, 30, _T("退出程序"), RED);
            }

        }

        if (m1.x >= 220 && m1.x <= 420 && m1.y >= 100 && m1.y <= 130)
        {
            locate(220, 100, 420, 130, 30, _T("暂停/结束"), RED);
            if (m1.uMsg == WM_LBUTTONDOWN)
            {
                return 0;
            }
        }

        if (m1.x >= 220 && m1.x <= 420 && m1.y >= 130 && m1.y <= 160)
        {
            if (m1.uMsg == WM_LBUTTONDOWN)
            {
                return 1;      // 
            }
        }
        if (m1.x >= 220 && m1.x <= 420 && m1.y >= 160 && m1.y <= 190)
        {
            if (m1.uMsg == WM_LBUTTONDOWN)
            {
                return 2;
            }
        }
        if (m1.x >= 220 && m1.x <= 420 && m1.y >= 190 && m1.y <= 220)
        {
            if (m1.uMsg == WM_LBUTTONDOWN)
            {
                return 3;
            }
        }
    }

}

void locate(int a, int b, int c, int d, int e, LPCTSTR text, COLORREF color)
{
   // HCURSOR hcur = LoadCursor(NULL, IDC_CROSS);      // 加载系统预置的鼠标样式
    HWND hwnd = GetHWnd();                // 获取绘图窗口句柄
    //SetClassLongPtr(hwnd, GCLP_HCURSOR, (long)hcur);  // 设置窗口类的鼠标样式
    setlinecolor(color);
    setfillcolor(BLUE);
    roundrect(a, b, c, d, e, e);
    settextcolor(color);
    settextstyle(20, 0, _T("黑体"));
    setbkmode(TRANSPARENT);
    char arr[50] = "按钮";
    RECT r = { a, b, c, d };
    drawtext(text, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void locate(int a, int b, int c, int d, int e, LPCTSTR text)
{
    setlinecolor(WHITE);
    setfillcolor(BLUE);
    roundrect(a, b, c, d, e, e);
    settextcolor(YELLOW);
    settextstyle(20, 0, _T("黑体"));
    setbkmode(TRANSPARENT);
    char arr[50] = "按钮";
    RECT r = { a, b, c, d };
    drawtext(text, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void menu()
{
    //HCURSOR hcur = LoadCursor(NULL, IDC_ARROW);      // 加载系统预置的鼠标样式
    HWND hwnd = GetHWnd();                // 获取绘图窗口句柄
    //SetClassLongPtr(hwnd, GCLP_HCURSOR, (long)hcur);  // 设置窗口类的鼠标样式
    
    //outtextxy(200, 230, _T(path));
    locate(220, 100, 420, 130, 30, _T("暂停/结束"));
    locate(220, 130, 420, 160, 30, _T("播放音乐"));
    locate(220, 160, 420, 190, 30, _T("选择音乐"));
    locate(220, 190, 420, 220, 30, _T("退出程序"));
}