#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<graphics.h>
#include <math.h>
#include <time.h>
//#define Width W
//#define Height H
const int Width = GetSystemMetrics(SM_CXSCREEN);
const int Height = GetSystemMetrics(SM_CYSCREEN);

int FileDialog(char* path);      // 获取图片地址
char szFile[MAX_PATH] = { 0 };
void AddPhoto(char szFile[]);    // 添加照片

class Algorithm
{
public:
    Algorithm(IMAGE* img, int width, int heigth);
    void Fakecolor();    // 假彩色
private:
    IMAGE* pimg;
    int WIDTH;
    int HEIGHT;
};
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
char* String(int num, char* str, int radix = 10) {
    char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; unsigned unum; int i = 0, j, k;
    if (radix == 10 && num < 0) { unum = (unsigned)-num; str[i++] = '-'; }
    else unum = (unsigned)num; do { str[i++] = index[unum % (unsigned)radix]; unum /= radix; } while (unum);
    str[i] = '\0'; if (str[0] == '-') k = 1; else k = 0; char temp;
    for (j = k; j <= (i - 1) / 2; j++) { temp = str[j]; str[j] = str[i - 1 + k - j]; str[i - 1 + k - j] = temp; }return str;
}
int main()
{
    initgraph(640, 480);
    RECT r = { 0, 0, 640,480 };
    settextcolor(YELLOW);
    settextstyle(50, 0, _T("楷体"));
    drawtext(_T("鼠标左键选择图片"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    char szFile[MAX_PATH] = { 0 };
    AddPhoto(szFile);    // 获取图片路径后
    IMAGE *img=new IMAGE;        // 备份
    IMAGE img1;        // 操作

    int width;        // 图像宽度
    int height;        // 图像高度

    loadimage(img, szFile);
   

   /* 
   // 这里可以写一个防止图片过大而显示不全
    double n = width * 1.0 / height;
    if (width > (W) || height > (H))
    {
        if (width > (W))
        {

            width = W - 60;
            height = width / n;
            if (height > (H))
            {
                height = H;
                width = height * n;
            }
        }
        else
        {
            height = H;
            width = height * n;
            if (width > W)
            {
                width = W;
                height = width / n;
            }
        }
    }
    closegraph();
    if (height < 480)
    {
        initgraph(width, 480);
    }
    else
    {
        initgraph(width, height);
    }
    */
    ;
    
    double tran = 0;
    double size = 0;
    double Size = 0;

    width = img->getwidth();
    height = img->getheight();
    Size = (double)Width / (double)Height;
    size = (double)width / (double)height;
    if (width >= (Width * 0.8) || height >= (Height * 0.8)) {
        if (Size <= size) {
            tran = ((double)width / (double)(Width * 0.8));
            width = int((double)Width * 0.8);
            height = (double)height / tran;
        }
        else {
            tran = (double)height / (double)(Height * 0.8);
            height = int((double)Height * 0.8);
            width = (double)width / tran;
        }
    }
    delete img;



    loadimage(&img1, szFile, width, height);
    closegraph();
    initgraph(width,height);
    IMAGE work(width, height);
    SetWorkingImage(&work);
    putimage(0, 0, &img1);
    SetWorkingImage();
    putimage(0, 0, &work);

    Algorithm myA(&work, width, height);    // 建立一个图片对象

    ExMessage m;    // 定义消息变量
    bool OK = false;
    while (true)
    {
        // 获取一条鼠标或按键消息
        m = getmessage(EX_MOUSE | EX_KEY);

        switch (m.message)
        {
        case WM_LBUTTONDOWN:
            myA.Fakecolor();
            OK = true;
            break;

        case WM_KEYDOWN:
            if (m.vkcode == VK_ESCAPE)
                return 0;  // 按 ESC 键退出程序
            break;
        }
        if (OK)
        {
            putimage(0, 0, &work);  // 处理过后的图像
            break;
        }
    }
    time_t npp;
    npp = time(&npp);
    strlink(String(npp, szFile), ".jpg");
    saveimage(szFile);
    // 关闭图形窗口
    
    return _getch();
}
int FileDialog(char* path)
{
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn); // 结构大小
    //ofn.lpstrFile = path; // 路径
    ofn.lpstrFile = path;
    ofn.nMaxFile = MAX_PATH; // 路径大小
    ofn.lpstrFilter = TEXT("图片文件(bmp;jpg;png)\0*.bmp;*.jpg;*.png;*.tiff;*.gif;*.tif;*jpeg\0\0"); // 文件类型
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    return GetOpenFileName(&ofn);
}

void AddPhoto(char szFile[])
{
    bool T = true;
    ExMessage m;    // 定义消息变量
    while (T)
    {
        // 获取一条鼠标或按键消息
        m = getmessage(EX_MOUSE | EX_KEY);
        switch (m.message)
        {
        case WM_LBUTTONDOWN:
            if (!FileDialog(szFile))
            {
                MessageBox(NULL, _T("不合法路径"), _T("错误"), MB_OK);
            }
            else
            {
                T = false;
            }
            break;
        }
    }
}

Algorithm::Algorithm(IMAGE* img, int width, int height)
{
    pimg = img;
    WIDTH = width;
    HEIGHT = height;
}

void Algorithm::Fakecolor()
{
    DWORD* p = GetImageBuffer(pimg);
    COLORREF c;
    int r, g, b;
    // 逐个像素点读取计算
    for (int i = pimg->getwidth() * pimg->getheight() - 1; i >= 0; i--)
    {
        c = BGR(p[i]);
        c = (GetRValue(c) * 299 + GetGValue(c) * 587 + GetBValue(c) * 114 + 500) / 1000;
        if (c >= 0 && c < 63)
        {
            r = 0;
            g = 254 - 4 * c;
            b = 255;
        }
        if (c >= 64 && c < 127)
        {
            r = 0;
            g = 4 * c - 254;
            b = 510 - 4 * c;
        }
        if (c >= 128 && c < 191)
        {
            r = 4 * c - 510;
            g = 255;
            b = 0;
        }
        if (c >= 192 && c <= 255)
        {
            r = 255;
            g = 1022 - 4 * c;
            b = 0;
        }
        p[i] = RGB(r, g, b);  // 由于是灰度值，无需再执行 BGR 转换
    }
}