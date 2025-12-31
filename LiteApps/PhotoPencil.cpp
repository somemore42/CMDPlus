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
const double PI = acos(-1.0);
const double delta = 1.5;
const int pic_Dis = 3;
double P[pic_Dis][pic_Dis];
int FileDialog(char* path);
void GetP();            // 获取高斯滤波算子

class Algorithm
{
public:
    Algorithm(IMAGE* img, int width, int heigth);
    void Histogram();        // 类似直方图均衡化
    void Gray();          // 灰度处理
    void Film();          // 负片处理
    void Blur();          // 高斯模糊化处理
    void Sketch();         // 素描算法

private:
    IMAGE* pimg;
    int WIDTH;
    int HEIGHT;
};

Algorithm::Algorithm(IMAGE* img, int width, int height)
{
    pimg = img;
    WIDTH = width;
    HEIGHT = height;
};

void Algorithm::Film()
{
    DWORD* pMem = GetImageBuffer(pimg);
    for (int i = pimg->getwidth() * pimg->getheight() - 1; i >= 0; i--)
        pMem[i] = (~pMem[i]) & 0x00FFFFFF;
}

void Algorithm::Sketch()    // 素描
{
    IMAGE* gray, * guassian;
    Histogram();        // 直方图
    Gray();            // 灰度处理
    gray = new IMAGE();
    guassian = new IMAGE();
    *gray = *pimg;
    Film();            //底片处理

    // 这里需要考虑的是模糊化处理的次数
    for (int i = 0; i < 10; i++)
    {
        Blur();  //模糊算法
    }
    *guassian = *pimg;
    *pimg = *gray;
    DWORD* pMem = GetImageBuffer(pimg);
    DWORD* Gray = GetImageBuffer(gray);
    DWORD* Guassian = GetImageBuffer(guassian);

    int R, G, B;
    int RR, GG, BB;
    for (int i = WIDTH * HEIGHT - 1; i >= 0; i--)
    {
        R = GetRValue(Gray[i]);
        B = GetBValue(Gray[i]);
        G = GetGValue(Gray[i]);
        RR = GetRValue(Guassian[i]);
        BB = GetBValue(Guassian[i]);
        GG = GetGValue(Guassian[i]);
        int r = min(R + (R * RR) / (255 - RR), 255);
        int g = min(G + (G * GG) / (255 - GG), 255);
        int b = min(B + (B * BB) / (255 - BB), 255);
        pMem[i] = RGB(r, g, b);
    }
    delete (gray);
    delete(guassian);
}


void Algorithm::Histogram()    // 类似直方图
{
    DWORD* p_data = GetImageBuffer(pimg);
    int height = HEIGHT;
    int wide = WIDTH;
    int pr[256], pg[256], pb[256];
    int size = HEIGHT * WIDTH;
    for (int p = 0; p <= 255; p++)
    {
        int nr = 0, ng = 0, nb = 0;
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < wide; i++)
            {
                if (p == GetRValue(p_data[j * wide + i]))
                {
                    nr++;
                }
                if (p == GetGValue(p_data[j * wide + i]))
                {
                    ng++;
                }
                if (p == GetBValue(p_data[j * wide + i]))
                {
                    nb++;
                }
            }
        }
        pr[p] = nr;
        pg[p] = ng;
        pb[p] = nb;
    }
    double sr[256] = { 0 }, sg[256] = { 0 }, sb[256] = { 0 };
    double aver = 0;
    double aveg = 0;
    double aveb = 0;
    bool T = true;
    bool K = true;
    bool P = true;
    int numr, numg, numb;
    for (int i = 0; i <= 255; i++)
    {
        if (T)
        {
            aver += pr[i] / double(size);
            sr[i] = aver;
            if (aver == 1)
            {
                numr = i;
                T = false;
            }
        }
        if (K)
        {
            aveg += pg[i] / double(size);
            sg[i] = aveg;
            if (aveg == 1)
            {
                numg = i;
                K = false;
            }
        }
        if (P)
        {
            aveb += pb[i] / double(size);
            sb[i] = aveb;
            if (aveb == 1)
            {
                numb = i;
                P = false;
            }
        }
    }
    int ssr[256] = { 0 }, ssg[256] = { 0 }, ssb[256] = { 0 };
    int rx = 0, gx = 0, bx = 0;
    for (int i = 0; i <= 255; i++)
    {
        if (i == 0)
        {
            ssr[i] = 0;
            ssg[i] = 0;
            ssb[i] = 0;
        }
        ssr[i] = (int)(255 * sr[i]);
        ssg[i] = (int)(255 * sg[i]);
        ssb[i] = (int)(255 * sb[i]);
    }

    int r = 0, g = 0, b = 0;
    double myr = 0, myg = 0, myb = 0;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < wide; i++)
        {
            myr = ssr[GetRValue(p_data[j * wide + i])];
            myg = ssg[GetGValue(p_data[j * wide + i])];
            myb = ssb[GetBValue(p_data[j * wide + i])];
            p_data[j * wide + i] = RGB(myr, myg, myb);
        }
    }
};

void Algorithm::Gray()
{
    DWORD* p = GetImageBuffer(pimg);
    COLORREF c;
    for (int i = pimg->getwidth() * pimg->getheight() - 1; i >= 0; i--)
    {
        c = BGR(p[i]);
        c = (GetRValue(c) * 299 + GetGValue(c) * 587 + GetBValue(c) * 114 + 500) / 1000;
        p[i] = RGB(c, c, c);    // 由于是灰度值，无需再执行 BGR 转换
    }
}
void Algorithm::Blur()
{
    GetP();
    BYTE* R;
    BYTE* G;
    BYTE* B;
    int size = HEIGHT * WIDTH;
    R = (BYTE*)calloc(size, sizeof(BYTE));
    G = (BYTE*)calloc(size, sizeof(BYTE));
    B = (BYTE*)calloc(size, sizeof(BYTE));

    DWORD* pMem = GetImageBuffer(pimg);

    for (int i = 0; i < size; i++)
    {
        R[i] = GetRValue(pMem[i]);
        G[i] = GetGValue(pMem[i]);
        B[i] = GetBValue(pMem[i]);
    }

    for (int i = WIDTH; i < WIDTH * (HEIGHT - 1); i++)
    {
        if (i % 500 != 0 || (i + 1) % 500 != 0)
        {
            pMem[i] = RGB(R[i - (WIDTH + 1)] * P[0][0] + R[i - WIDTH] * P[0][1] + R[i - (WIDTH - 1)] * P[0][2] + R[i - 1] * P[1][0] + R[i] * P[1][1] + R[i + 1] * P[1][2] + R[i + (WIDTH - 1)] * P[2][0] + R[i + WIDTH] * P[2][1] + R[i + (WIDTH + 1)] * P[2][2],
                G[i - (WIDTH + 1)] * P[0][0] + G[i - WIDTH] * P[0][1] + G[i - (WIDTH - 1)] * P[0][2] + G[i - 1] * P[1][0] + G[i] * P[1][1] + G[i + 1] * P[1][2] + G[i + (WIDTH - 1)] * P[2][0] + G[i + WIDTH] * P[2][1] + G[i + (WIDTH + 1)] * P[2][2],
                B[i - (WIDTH + 1)] * P[0][0] + B[i - WIDTH] * P[0][1] + B[i - (WIDTH - 1)] * P[0][2] + B[i - 1] * P[1][0] + B[i] * P[1][1] + B[i + 1] * P[1][2] + B[i + (WIDTH - 1)] * P[2][0] + B[i + WIDTH] * P[2][1] + B[i + (WIDTH + 1)] * P[2][2]);
        }
    }
    free(R);
    free(G);
    free(B);
    R = G = B = NULL;
}

int main()
{
    int  width = 0;
    int  height = 0;
    char szFile[MAX_PATH] = { 0 };
    while (true)
    {
        if (!FileDialog(szFile))
        {
            MessageBox(NULL, _T("不合法路径"), _T("错误"), MB_OK);
        }
        else
        {
            break;
        }
    }
    IMAGE g_img,gg_img;
    loadimage(&gg_img, szFile);  // 加载图片
    width = gg_img.getwidth();
    height = gg_img.getheight();
    double tran = 0;
    double size = 0;
    double Size = 0;
    int x;
    Size = (double)Width / (double)Height;
    size = (double)width / (double)height;
    if (width >= (Width*0.8) || height >= (Height*0.8)) {
            if (Size <= size) {
                tran =( (double)width / (double)(Width * 0.8));
                width = int((double)Width * 0.8);
                height = (double)height/tran;
            }
            else {
                tran = (double)height / (double)(Height * 0.8);
                height = int((double)Height * 0.8);
                width =(double)width/ tran;
            }
    }
    /*
    if (width>=Width||height>=Height) {
        if (width >= (Width*0.8)) {
            tran = (double)Width / (double)width;
            tran * 0.75;
            height = int((double)height*tran);
            width = int((double)width*tran);
        }else
        if (height >= (Height*0.8)) {
            tran = (double)Height / (double)height;
            tran * 0.75;
            height = int((double)height * tran);
            width =int((double)width* tran);
        }
        else {


        }
    }
    */
    loadimage(&g_img, szFile,width,height);
    initgraph(width, height);
    putimage(0, 0, &g_img);
    x=_getch();
    Algorithm myA(&g_img, width, height);
    myA.Sketch();
    putimage(0, 0, &g_img);
    saveimage(_T("test.jpg"));
    x=_getch();
    return 0;
}

void GetP()
{
    for (int i = 0; i < pic_Dis; i++)
    {
        for (int j = 0; j < pic_Dis; j++)
        {
            int d = (i - 1) * (i - 1) + (j - 1) * (j - 1);
            double x = 1 / (2 * PI * delta);
            P[i][j] = x * exp(-d / (2 * delta));
        }
    }

    double pn = 0;

    for (int i = 0; i < pic_Dis; i++)
    {
        for (int j = 0; j < pic_Dis; j++)
        {
            pn += P[i][j];
        }
    }

    for (int i = 0; i < pic_Dis; i++)
    {
        for (int j = 0; j < pic_Dis; j++)
        {
            P[i][j] = P[i][j] / pn;
        }
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