#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<graphics.h>
#include <math.h>
#include <time.h>
//const int Width = GetSystemMetrics(SM_CXSCREEN);
//const int Height = GetSystemMetrics(SM_CYSCREEN);
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
#define PI acos(-1.0)
#define Width 600
#define Height 600

bool SetWindowTransparent(HWND hwnd, COLORREF crkcolor, BYTE bAlpha, DWORD dwFlags);
void SetWindowsForm(HWND hWnd);
// str代表绘制的字符串
// variable 代表每次的变量
// fors 每次需要循环的次数总数
// R 该圈的半径
// Long 刻度的长度
void DrawCircle(TCHAR str[25], int variable, int fors, int R);        // 绘制一圈字符  
void DrawKD(int variable, int fors, int R, int Long);            // 绘制刻度
void DrawProtractor();                            // 绘制量角器          
void OutputDegrees(int x, int y);                      // 输出刻度
double Distance(int x, int y);
double Azimuth(int star_x, int star_y, int end_x, int end_y);        // 计算方位角
void RadianToAngle(double Radian, int* Degree, int* Minute, int* Seconds);  // 弧度转角度

int main()
{
    initgraph(Width, Height);      // 初始化图形窗口
    HWND hWnd = GetHWnd();        // 获取窗口句柄
    SetWindowsForm(hWnd);        // 设置为窗口为圆形并透明
    DrawProtractor();          // 绘画量角器

    ExMessage m;            // 定义鼠标消息
    while (true)
    {
        m = getmessage(EM_MOUSE);    // 获取一条鼠标消息
        switch (m.message)
        {
        case WM_LBUTTONDOWN:
            // 如果左键按下，欺骗 windows 点在了标题栏上
            PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(m.x, m.y));
            if (Distance(m.x, m.y) >= (Height / 2 - 29) && Distance(m.x, m.y) <= (Height / 2 - 15))
            {
                cleardevice();
                DrawProtractor();
                OutputDegrees(m.x, m.y);
            }
            break;
        case WM_RBUTTONUP:        // 按鼠标右键退出程序
            closegraph();
            return 0;
        }
    }
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

void SetWindowsForm(HWND hWnd)
{
    setbkcolor(WHITE);
    cleardevice();
    // 获取窗口边框宽高
    RECT rcClient, rcWind;
    GetClientRect(hWnd, &rcClient);
    GetWindowRect(hWnd, &rcWind);
    int cx = ((rcWind.right - rcWind.left) - rcClient.right) / 2;
    int cy = ((rcWind.bottom - rcWind.top + GetSystemMetrics(SM_CYCAPTION)) - rcClient.bottom) / 2;
    // 设置圆形区域
    HRGN rgn = CreateEllipticRgn(0 + cx, 0 + cy, Width + cx, Height + cy);
    SetWindowRgn(hWnd, rgn, true);
    SetWindowTransparent(hWnd, WHITE, 100, 0x1);
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void DrawCircle(TCHAR str[25], int variable, int fors, int R)
{
    settextcolor(RED);
    double a, x0, y0, w, h, x1, y1;
    int x, y;
    settextstyle(22, 0, "微软雅黑", variable * 3600 / fors, variable * 3600 / fors, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
    a = variable * PI * 2 / fors;
    w = textwidth(str);                                      // 计算字符串宽 w、高 h
    h = textheight(str);
    x1 = R * cos(a);                                      // 计算输出字符串的左上角位置
    y1 = R * sin(a);
    x0 = x1 * cos(-a) - y1 * sin(-a);                              // 将字符串绕原点顺时针旋转 a 弧度
    y0 = y1 * cos(-a) + x1 * sin(-a);
    x0 -= w / 2;                                        // 将字符串向左上偏移 w/2、h/2
    y0 += h / 2;                                        // 绘图坐标向下为正
    x = (int)(x0 * cos(a) - y0 * sin(a));                            // 将字符串绕原点逆时针旋转 a 弧度
    y = (int)(y0 * cos(a) + x0 * sin(a));
    outtextxy(int(Width / 2 + x + 0.5), int(Height / 2 - y + 0.5), str);            // 绘图坐标向下为正
}

void DrawKD(int variable, int fors, int R, int Long)
{
    setlinecolor(RED);
    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 1);
    double a, x0, y0, x1, y1;
    double star_x, star_y;
    double end_x, end_y;
    a = variable * PI * 2 / fors;
    x1 = R * cos(a);
    y1 = R * sin(a);
    x0 = x1 * cos(-a) - y1 * sin(-a);
    y0 = y1 * cos(-a) + x1 * sin(-a);
    star_x = (x0 * cos(a) - y0 * sin(a));
    star_y = (y0 * cos(a) + x0 * sin(a));
    x1 = (R - Long) * cos(a);
    y1 = (R - Long) * sin(a);
    x0 = x1 * cos(-a) - y1 * sin(-a);
    y0 = y1 * cos(-a) + x1 * sin(-a);
    end_x = (x0 * cos(a) - y0 * sin(a));
    end_y = (y0 * cos(a) + x0 * sin(a));
    line((int)(Width / 2 + star_x), (int)(Width / 2 + star_y), (int)(Width / 2 + end_x), (int)(Width / 2 + end_y));
}

void DrawProtractor()
{
    setlinestyle(PS_SOLID, 2);
    setlinecolor(BLACK);
    circle(Width / 2, Height / 2, Height / 2 - 10);
    setlinestyle(PS_SOLID, 30);
    setlinecolor(LIGHTRED);
    circle(Width / 2, Height / 2, 90);
    setlinestyle(PS_SOLID, 14);
    circle(Width / 2, Height / 2, Height / 2 - 22);
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 1);
    line(10, Height / 2, Width / 2 - 2, Height / 2);
    line(Width / 2 + 2, Height / 2, Width - 10, Height / 2);
    line(Width / 2, Height / 2 - 50, Width / 2, Height / 2 - 2);
    line(Width / 2, Height / 2 + 2, Width / 2, Height / 2 + 50);
    circle(Width / 2, Height / 2, 2);
    circle(Width / 2, Height / 2, 150);
    circle(Width / 2, Height / 2, 50);

    TCHAR str[25];
    for (int i = 0; i < 360; i++)
    {
        if (i % 10 == 0)
        {
            DrawKD(i / 10, 36, Height / 2 - 30, 30);
            DrawKD(i / 10, 36, 165, 30);
            DrawKD(i / 10, 36, 65, 15);
            _stprintf_s(str, _T("%d"), i);
            DrawCircle(str, i / 10, 36, Height / 2 - 75);
            continue;
        }
        if (i % 5 == 0)
        {
            DrawKD(i / 5, 72, Height / 2 - 30, 15);
            continue;
        }
        DrawKD(i, 360, Height / 2 - 30, 10);
    }
}

double Distance(int x, int y)
{
    return sqrt((double)((Width / 2.0 - x) * (Width / 2.0 - x) + (Height / 2.0 - y) * (Height / 2.0 - y)));
}

void OutputDegrees(int x, int y)
{
    setlinecolor(RED);
    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 1);
    line(x, y, Width / 2, Height / 2);
    double Radian = Azimuth(x, y, Width / 2, Height / 2);
    int Degree, Minute, Seconds;
    RadianToAngle(Radian, &Degree, &Minute, &Seconds);
    TCHAR str[20];
    settextcolor(BLACK);
    settextstyle(22, 0, "微软雅黑", 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
    _stprintf_s(str, _T("%d°%d′%d″"), Degree, Minute, Seconds);
    setbkmode(TRANSPARENT);
    outtextxy(Width / 2 + 5, Height / 2 - 20, str);
    _stprintf_s(str, _T("%lfπ"), Radian);
    outtextxy(Width / 2 + 5, Height / 2, str);
}
double Azimuth(int star_x, int star_y, int end_x, int end_y)
{
    double radian, x, y;
    y = end_y - star_y;
    x = end_x - star_x;
    if (y == 0 && end_x > star_x) radian = PI;
    else if (y == 0 && end_x < star_x) radian = 0;
    else if (x == 0 && end_y > star_y) radian = PI / 2;
    else if (x == 0 && end_y < star_y) radian = 3 * PI / 2;
    else if (x > 0 && y > 0) radian = PI - atan(fabs(y) / fabs(x));
    else if (x < 0 && y > 0) radian = atan(fabs(y) / fabs(x));
    else if (x < 0 && y < 0) radian = 2 * PI - atan(fabs(y) / fabs(x));
    else if (x > 0 && y < 0) radian = PI + atan(fabs(y) / fabs(x));
    return radian;
}

void RadianToAngle(double Radian, int* Degree, int* Minute, int* Seconds)
{
    *Degree = int(Radian * 180 / PI);
    *Minute = int((Radian * 180 / PI - *Degree) * 60);
    *Seconds = int(((Radian * 180 / PI - *Degree) * 60 - *Minute) * 60);
}