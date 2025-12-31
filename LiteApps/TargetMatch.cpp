#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<graphics.h>
#include <math.h>
#include <time.h>
const int Width = 1024;
const int Height = 800;
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
double Simg_num[1024][800];
double Bimg_num[1024][800];
//double** ser = new double*[Width];
void  ColorToBig(IMAGE* pimg)
{
    DWORD* p = GetImageBuffer(pimg); // 获取显示缓冲区指针
    COLORREF c;

    for (int i = 0; i < pimg->getwidth(); i++)
    {
        for (int j = 0; j < pimg->getheight(); j++)
        {
            c = BGR(p[j * (pimg->getwidth()) + i]);
            Bimg_num[i][j] = (GetRValue(c) * 299 + GetGValue(c) * 587 + GetBValue(c) * 114 + 500) / 1000;
        }
    }
}

void  ColorToSmall(IMAGE* pimg)
{
    DWORD* p = GetImageBuffer(pimg); // 获取显示缓冲区指针
    COLORREF c;

    for (int i = 0; i < pimg->getwidth(); i++)
    {
        for (int j = 0; j < pimg->getheight(); j++)
        {
            c = BGR(p[j * (pimg->getwidth()) + i]);
            Simg_num[i][j] = (GetRValue(c) * 299 + GetGValue(c) * 587 + GetBValue(c) * 114 + 500) / 1000;
        }
    }
}

int main()
{
    int x = 0;
    char o[255] = "";
    char t[255] = "";
    int width=0;        // 图像宽度
    int height=0;
    int tw = 0;
    int th = 0;
    double tran = 1.0;
    printf("请选择原始图像\n");
    x = FileDialog(o);
    if (x) {
        IMAGE* ter = new IMAGE;
        loadimage(ter, o);
        
        double size = 0;
        double Size = 0;

        width = ter->getwidth();
        height = ter->getheight();
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
        delete ter;
    }
    else { return -1; }
    printf("请选择目标图像\n");
    x = FileDialog(t);
    if (!t) { return -2; }
    else {
        IMAGE* ter = new IMAGE;
        loadimage(ter, t);
        tw = ter->getwidth();
        th = ter->getheight();
        tw = (double)tw / tran;
        th = (double)th / tran;
        delete ter;
    }
    
    IMAGE img1, img2;
    loadimage(&img1, o,width,height);
    loadimage(&img2, t,tw,th);
    initgraph(width, height);
    // 显示原始图像
    putimage(0, 0, &img1);
    // 按任意键转换为灰度图像
    x=_getch();
    // 处理图像为灰度
    ColorToBig(&img1);//大图的读取
    ColorToSmall(&img2);//小图
    double N = tw * th;
    double mm = 0;
    // 已经读取结束

    int xx = 0;
    int yy = 0;
    for (int i = 0; i < width - tw; i++)
    {
        for (int j = 0; j < height - th; j++)
        {
            // 开始进入小循
            // 开始设置一些小的过程量
            int SXD = 0;
            int SXX = 0;
            int SDD = 0;
            int SX = 0;
            int SD = 0;
            for (int x = 0; x < tw; x++)
            {
                for (int y = 0; y < th; y++)
                {
                    SXD += (Bimg_num[i + x][j + y] * Simg_num[x][y]);
                    SXX += (Simg_num[x][y] * Simg_num[x][y]);
                    SDD += (Bimg_num[i + x][j + y] * Bimg_num[i + x][j + y]);
                    SX += (Simg_num[x][y]);
                    SD += (Simg_num[x][y]);
                }
            }
            // 计算结束开始整合
            double RO = (SXD - (SX * SD) / N * 1.0) / (sqrt((SXX - (SX * SX) / N * 1.0) * (SDD - (SD * SD) / N * 1.0)));
            if (mm < RO)
            {
                mm = RO;
                xx = i;
                yy = j;
            }
        }
    }
    // 显示处理后的图像
    putimage(0, 0, &img1);
    setlinecolor(YELLOW);
    rectangle(xx, yy, xx + tw, yy + th);
    x=_getch();
    return x;
}