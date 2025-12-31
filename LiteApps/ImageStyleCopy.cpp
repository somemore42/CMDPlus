#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<graphics.h>
#include <math.h>
#include <time.h>
const int Width = GetSystemMetrics(SM_CXSCREEN);
const int Height = GetSystemMetrics(SM_CYSCREEN);
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
// 计算每一种 DN 值在整个像片中所占的比例
void Hist(IMAGE* pimg, double num[][256])
{
    DWORD* p = GetImageBuffer(pimg);
    for (int j = 0; j < 256; j++)
    {
        double sumr = 0.0;
        double sumg = 0.0;
        double sumb = 0.0;
        for (int i = pimg->getwidth() * pimg->getheight() - 1; i >= 0; i--)
        {
            if (j == GetRValue(p[i]))
            {
                sumr++;
            }
            if (j == GetGValue(p[i]))
            {
                sumg++;
            }
            if (j == GetBValue(p[i]))
            {
                sumb++;
            }
        }
        num[0][j] = sumr / (pimg->getwidth() * pimg->getheight());
        num[1][j] = sumg / (pimg->getwidth() * pimg->getheight());
        num[2][j] = sumb / (pimg->getwidth() * pimg->getheight());
    }
}

// 累计直方图
void HistTOsum(double Hist[][256], double Sum[][256])
{
    for (int j = 0; j < 3; j++)
    {
        double mysum = 0;
        for (int i = 0; i < 256; i++)
        {
            mysum += Hist[j][i];
            Sum[j][i] = mysum;
        }
    }
}

// 通过累计直方图进行计算 DN 值
void HistTOmark(int DN[][256], double numa[][256], double numb[][256])
{
    double mymin;
    for (int rgb = 0; rgb < 3; rgb++)
    {
        for (int i = 0; i < 256; i++)
        {
            int DNnum = 0;
            mymin = 255;
            for (int j = 0; j < 256; j++)
            {
                if (mymin > fabs(numa[rgb][i] - numb[rgb][j]))
                {
                    mymin = fabs(numa[rgb][i] - numb[rgb][j]);
                    DNnum = j;
                }
            }
            DN[rgb][i] = DNnum;
        }
    }
}

// 将 DN 值进行映射显示
void TurnToShow(IMAGE* pimg, int DN[][256])
{
    DWORD* p = GetImageBuffer(pimg);
    for (int i = pimg->getwidth() * pimg->getheight() - 1; i >= 0; i--)
    {
        p[i] = RGB(DN[0][GetRValue(p[i])], DN[1][GetGValue(p[i])], DN[2][GetBValue(p[i])]);
    }
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
int main()
{
    int  width = 0;
    int  height = 0;
    IMAGE imgpolt,imgpol ,imgTM;
    char o[255] = "";
    char r[255] = "";
    printf("请选择原图片\n");
    if (FileDialog(o)) {
        loadimage(&imgpol, o);
        
    }
    else { MessageBox(NULL, _T("不合法路径"), _T("错误"), MB_OK); return -1; }// 加载原图
    

    width = imgpol.getwidth();
    height = imgpol.getheight();

    double tran = 0;
    double size = 0;
    double Size = 0;
    int x;
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
    printf("请选择要模仿的图片\n");
    if (FileDialog(r)) {
        loadimage(&imgTM, r,width,height);
    }
    else { MessageBox(NULL, _T("不合法路径"), _T("错误"), MB_OK); return -2; }


    loadimage(&imgpolt, o,width,height);
    initgraph(width, height);
    putimage(0, 0, &imgpolt);
    x=_getch();
    //loadimage(&imgTM,r);      // 加载规定化图
    double HistPO[3][256];            // 原图像的频率
    double HistTM[3][256];            // TM图像的频率
    double HistPOsum[3][256];          // 原累计直方图
    double HistTMsum[3][256];          // TM累计直方图
    int DNnumber[3][256];            // 储存 DN 值

    Hist(&imgpolt, HistPO);            // 计算原图的直方图
    Hist(&imgTM, HistTM);            // 计算规定化图片的直方图

    HistTOsum(HistPO, HistPOsum);        // 计算原图的累计直方图
    HistTOsum(HistTM, HistTMsum);        // 计算规定化图片的累计直方图

    HistTOmark(DNnumber, HistPOsum, HistTMsum);  // 计算 DN 值
    TurnToShow(&imgpolt, DNnumber);        // 替换 DN 值

    putimage(0, 0, &imgpolt);
    saveimage(_T("test.jpg"));
    x=_getch();
    return 0;
}