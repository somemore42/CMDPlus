#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<graphics.h>
//#include <math.h>
//#include <time.h>
const int W = GetSystemMetrics(SM_CXSCREEN);
const int H = GetSystemMetrics(SM_CYSCREEN);
int FileDialog(char* path);      // 获取图片地址
char szFile[MAX_PATH] = { 0 };
void AddPhoto(char szFile[]);    // 添加照片

class Algorithm
{
public:
    Algorithm(IMAGE* img, int width, int heigth);
    void Smooth();      // 平滑          
private:
    IMAGE* pimg;
    int WIDTH;
    int HEIGHT;
};

int main()
{
    initgraph(640, 480);
    RECT r = { 0, 0, 640,480 };
    settextcolor(YELLOW);
    settextstyle(50, 0, _T("楷体"));
    drawtext(_T("鼠标左键选择图片"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    char szFile[MAX_PATH] = { 0 };
    AddPhoto(szFile);    // 获取图片路径后
    IMAGE img;        // 备份
    IMAGE img1;        // 操作

    int width;        // 图像宽度
    int height;        // 图像高度
    double tran = 0;
    double size = 0;
    double Size = 0;
    loadimage(&img, szFile);
    width = img.getwidth();
    height = img.getheight();

    // 这里可以写一个防止图片过大而显示不全
    /*double n = width * 1.0 / height;
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
    }*/
    closegraph();
    /*
    if (height < 480)
    {
        initgraph(width, 480);
    }
    else
    {
        initgraph(width, height);
    }*/
    int Width = W;
    int Height = H;
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
    initgraph(width, height);
    loadimage(&img1, szFile, width, height);
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
            myA.Smooth();
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
    saveimage(_T("test.jpg"));
    // 关闭图形窗口
    int a=_getch();
    return 0;
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

void Algorithm::Smooth()      // 平滑
{
    IMAGE* data;
    data = new IMAGE;
    DWORD* p_data = GetImageBuffer(pimg);    // 原图
    DWORD* Gray = GetImageBuffer(data);      // 容器
    int n, nminR, nminG, nminB, R[9], G[9], B[9];
    int r, g, b;
    double  bunsanR[9], bunsanG[9], bunsanB[9], myR[9], myG[9], myB[9], bmR, bmG, bmB;
    int wide = WIDTH;
    for (int j = 2; j <= HEIGHT - 3; j++)
        for (int i = 2; i <= WIDTH - 3; i++)
        {
            //第一近邻域红色
            R[0] = GetRValue(p_data[(j - 1) * wide + (i - 1)]);
            R[1] = GetRValue(p_data[(j - 1) * wide + i]);
            R[2] = GetRValue(p_data[(j - 1) * wide + (i + 1)]);
            R[3] = GetRValue(p_data[j * wide + (i - 1)]);
            R[4] = GetRValue(p_data[j * wide + i]);
            R[5] = GetRValue(p_data[j * wide + (i + 1)]);
            R[6] = GetRValue(p_data[(j + 1) * wide + (i - 1)]);
            R[7] = GetRValue(p_data[(j + 1) * wide + i]);
            R[8] = GetRValue(p_data[(j + 1) * wide + (i + 1)]);
            myR[0] = (float)
                (R[0] + R[1] + R[2] + R[3] + R[4] + R[5] + R[6] + R[7] + R[8]) / 9.0;
            bunsanR[0] = 0;
            for (n = 0; n <= 8; n++)
                bunsanR[0] += R[n] * R[n] - myR[0] * myR[0];

            //第一近邻域绿色
            G[0] = GetGValue(p_data[(j - 1) * wide + (i - 1)]);
            G[1] = GetGValue(p_data[(j - 1) * wide + i]);
            G[2] = GetGValue(p_data[(j - 1) * wide + (i + 1)]);
            G[3] = GetGValue(p_data[j * wide + (i - 1)]);
            G[4] = GetGValue(p_data[j * wide + i]);
            G[5] = GetGValue(p_data[j * wide + (i + 1)]);
            G[6] = GetGValue(p_data[(j + 1) * wide + (i - 1)]);
            G[7] = GetGValue(p_data[(j + 1) * wide + i]);
            G[8] = GetGValue(p_data[(j + 1) * wide + (i + 1)]);
            myG[0] = (float)
                (G[0] + G[1] + G[2] + G[3] + G[4] + G[5] + G[6] + G[7] + G[8]) / 9.0;
            bunsanG[0] = 0;
            for (n = 0; n <= 8; n++)
                bunsanG[0] += G[n] * G[n] - myG[0] * myG[0];

            //第一近邻域蓝色色
            B[0] = GetBValue(p_data[(j - 1) * wide + (i - 1)]);
            B[1] = GetBValue(p_data[(j - 1) * wide + i]);
            B[2] = GetBValue(p_data[(j - 1) * wide + (i + 1)]);
            B[3] = GetBValue(p_data[j * wide + (i - 1)]);
            B[4] = GetBValue(p_data[j * wide + i]);
            B[5] = GetBValue(p_data[j * wide + (i + 1)]);
            B[6] = GetBValue(p_data[(j + 1) * wide + (i - 1)]);
            B[7] = GetBValue(p_data[(j + 1) * wide + i]);
            B[8] = GetBValue(p_data[(j + 1) * wide + (i + 1)]);
            myB[0] = (float)
                (B[0] + B[1] + B[2] + B[3] + B[4] + B[5] + B[6] + B[7] + B[8]) / 9.0;
            bunsanB[0] = 0;
            for (n = 0; n <= 8; n++)
                bunsanB[0] += B[n] * B[n] - myB[0] * myB[0];


            //第二近邻域红色
            R[0] = GetRValue(p_data[(j - 2) * wide + (i - 1)]);
            R[1] = GetRValue(p_data[(j - 2) * wide + i]);
            R[2] = GetRValue(p_data[(j - 2) * wide + (i + 1)]);
            R[3] = GetRValue(p_data[(j - 1) * wide + (i - 1)]);
            R[4] = GetRValue(p_data[(j - 1) * wide + i]);
            R[5] = GetRValue(p_data[(j - 1) * wide + (i + 1)]);
            R[6] = GetRValue(p_data[j * wide + i]);
            myR[1] = (float)
                (R[0] + R[1] + R[2] + R[3] + R[4] + R[5] + R[6]) / 7;
            bunsanR[1] = 0;
            for (n = 0; n <= 6; n++)
                bunsanR[1] += R[n] * R[n] - myR[1] * myR[1];

            //第二近邻域红色
            G[0] = GetGValue(p_data[(j - 2) * wide + (i - 1)]);
            G[1] = GetGValue(p_data[(j - 2) * wide + i]);
            G[2] = GetGValue(p_data[(j - 2) * wide + (i + 1)]);
            G[3] = GetGValue(p_data[(j - 1) * wide + (i - 1)]);
            G[4] = GetGValue(p_data[(j - 1) * wide + i]);
            G[5] = GetGValue(p_data[(j - 1) * wide + (i + 1)]);
            G[6] = GetGValue(p_data[j * wide + i]);
            myG[1] = (float)
                (G[0] + G[1] + G[2] + G[3] + G[4] + G[5] + G[6]) / 7;
            bunsanG[1] = 0;
            for (n = 0; n <= 6; n++)
                bunsanG[1] += G[n] * G[n] - myG[1] * myG[1];

            //第二近邻域蓝色
            B[0] = GetBValue(p_data[(j - 2) * wide + (i - 1)]);
            B[1] = GetBValue(p_data[(j - 2) * wide + i]);
            B[2] = GetBValue(p_data[(j - 2) * wide + (i + 1)]);
            B[3] = GetBValue(p_data[(j - 1) * wide + (i - 1)]);
            B[4] = GetBValue(p_data[(j - 1) * wide + i]);
            B[5] = GetBValue(p_data[(j - 1) * wide + (i + 1)]);
            B[6] = GetBValue(p_data[j * wide + i]);
            myB[1] = (float)
                (B[0] + B[1] + B[2] + B[3] + B[4] + B[5] + B[6]) / 7;
            bunsanB[1] = 0;
            for (n = 0; n <= 6; n++)
                bunsanB[1] += B[n] * B[n] - myB[1] * myB[1];

            //第三近邻域红色
            R[0] = GetRValue(p_data[(j - 1) * wide + (i - 2)]);
            R[1] = GetRValue(p_data[(j - 1) * wide + (i - 1)]);
            R[2] = GetRValue(p_data[j * wide + (i - 2)]);
            R[3] = GetRValue(p_data[j * wide + (i - 1)]);
            R[4] = GetRValue(p_data[j * wide + i]);
            R[5] = GetRValue(p_data[(j + 1) * wide + (i - 2)]);
            R[6] = GetRValue(p_data[(j + 1) * wide + (i - 1)]);
            myR[2] = (float)
                (R[0] + R[1] + R[2] + R[3] + R[4] + R[5] + R[6]) / 7;
            bunsanR[2] = 0;
            for (n = 0; n <= 6; n++)
                bunsanR[2] += R[n] * R[n] - myR[2] * myR[2];

            //第三近邻域绿色
            G[0] = GetGValue(p_data[(j - 1) * wide + (i - 2)]);
            G[1] = GetGValue(p_data[(j - 1) * wide + (i - 1)]);
            G[2] = GetGValue(p_data[j * wide + (i - 2)]);
            G[3] = GetGValue(p_data[j * wide + (i - 1)]);
            G[4] = GetGValue(p_data[j * wide + i]);
            G[5] = GetGValue(p_data[(j + 1) * wide + (i - 2)]);
            G[6] = GetGValue(p_data[(j + 1) * wide + (i - 1)]);

            myG[2] = (float)
                (G[0] + G[1] + G[2] + G[3] + G[4] + G[5] + G[6]) / 7;
            bunsanG[2] = 0;
            for (n = 0; n <= 6; n++)
                bunsanG[2] += G[n] * G[n] - myG[2] * myG[2];

            //第三近邻域绿色
            B[0] = GetBValue(p_data[(j - 1) * wide + (i - 2)]);
            B[1] = GetBValue(p_data[(j - 1) * wide + (i - 1)]);
            B[2] = GetBValue(p_data[j * wide + (i - 2)]);
            B[3] = GetBValue(p_data[j * wide + (i - 1)]);
            B[4] = GetBValue(p_data[j * wide + i]);
            B[5] = GetBValue(p_data[(j + 1) * wide + (i - 2)]);
            B[6] = GetBValue(p_data[(j + 1) * wide + (i - 1)]);

            myB[2] = (float)
                (B[0] + B[1] + B[2] + B[3] + B[4] + B[5] + B[6]) / 7;
            bunsanB[2] = 0;
            for (n = 0; n <= 6; n++)
                bunsanB[2] += B[n] * B[n] - myB[2] * myB[2];


            //第四近邻域红色
            R[0] = GetRValue(p_data[j * wide + i]);
            R[1] = GetRValue(p_data[(j + 1) * wide + (i - 1)]);
            R[2] = GetRValue(p_data[(j + 1) * wide + i]);
            R[3] = GetRValue(p_data[(j + 1) * wide + (i + 1)]);
            R[4] = GetRValue(p_data[(j + 2) * wide + (i - 1)]);
            R[5] = GetRValue(p_data[(j + 2) * wide + i]);
            R[6] = GetRValue(p_data[(j + 2) * wide + (i + 1)]);

            myR[3] = (float)
                (R[0] + R[1] + R[2] + R[3] + R[4] + R[5] + R[6]) / 7;
            bunsanR[3] = 0;
            for (n = 0; n <= 6; n++)
                bunsanR[3] += R[n] * R[n] - myR[3] * myR[3];

            //第四近邻域绿色
            G[0] = GetGValue(p_data[j * wide + i]);
            G[1] = GetGValue(p_data[(j + 1) * wide + (i - 1)]);
            G[2] = GetGValue(p_data[(j + 1) * wide + i]);
            G[3] = GetGValue(p_data[(j + 1) * wide + (i + 1)]);
            G[4] = GetGValue(p_data[(j + 2) * wide + (i - 1)]);
            G[5] = GetGValue(p_data[(j + 2) * wide + i]);
            G[6] = GetGValue(p_data[(j + 2) * wide + (i + 1)]);

            myG[3] = (float)
                (G[0] + G[1] + G[2] + G[3] + G[4] + G[5] + G[6]) / 7;
            bunsanG[3] = 0;
            for (n = 0; n <= 6; n++)
                bunsanG[3] += G[n] * G[n] - myG[3] * myG[3];
            //第四近邻域绿色
            B[0] = GetBValue(p_data[j * wide + i]);
            B[1] = GetBValue(p_data[(j + 1) * wide + (i - 1)]);
            B[2] = GetBValue(p_data[(j + 1) * wide + i]);
            B[3] = GetBValue(p_data[(j + 1) * wide + (i + 1)]);
            B[4] = GetBValue(p_data[(j + 2) * wide + (i - 1)]);
            B[5] = GetBValue(p_data[(j + 2) * wide + i]);
            B[6] = GetBValue(p_data[(j + 2) * wide + (i + 1)]);

            myB[3] = (float)
                (B[0] + B[1] + B[2] + B[3] + B[4] + B[5] + B[6]) / 7;
            bunsanB[3] = 0;
            for (n = 0; n <= 6; n++)
                bunsanB[3] += B[n] * B[n] - myB[3] * myB[3];

            //第五邻域区域红
            R[0] = GetRValue(p_data[(j - 1) * wide + (i + 1)]);
            R[1] = GetRValue(p_data[(j - 1) * wide + (i + 2)]);
            R[2] = GetRValue(p_data[j * wide + i]);
            R[3] = GetRValue(p_data[j * wide + (i + 1)]);
            R[4] = GetRValue(p_data[j * wide + (i + 2)]);
            R[5] = GetRValue(p_data[(j + 1) * wide + (i + 1)]);
            R[6] = GetRValue(p_data[(j + 1) * wide + (i + 2)]);

            myR[4] = (float)
                (R[0] + R[1] + R[2] + R[3] + R[4] + R[5] + R[6]) / 7;
            bunsanR[4] = 0;
            for (n = 0; n <= 6; n++)
                bunsanR[4] += R[n] * R[n] - myR[4] * myR[4];

            //第五邻域区域红
            G[0] = GetGValue(p_data[(j - 1) * wide + (i + 1)]);
            G[1] = GetGValue(p_data[(j - 1) * wide + (i + 2)]);
            G[2] = GetGValue(p_data[j * wide + i]);
            G[3] = GetGValue(p_data[j * wide + (i + 1)]);
            G[4] = GetGValue(p_data[j * wide + (i + 2)]);
            G[5] = GetGValue(p_data[(j + 1) * wide + (i + 1)]);
            G[6] = GetGValue(p_data[(j + 1) * wide + (i + 2)]);

            myG[4] = (float)
                (G[0] + G[1] + G[2] + G[3] + G[4] + G[5] + G[6]) / 7;
            bunsanG[4] = 0;
            for (n = 0; n <= 6; n++)
                bunsanG[4] += G[n] * G[n] - myG[4] * myG[4];

            //第五邻域区域蓝
            B[0] = GetBValue(p_data[(j - 1) * wide + (i + 1)]);
            B[1] = GetBValue(p_data[(j - 1) * wide + (i + 2)]);
            B[2] = GetBValue(p_data[j * wide + i]);
            B[3] = GetBValue(p_data[j * wide + (i + 1)]);
            B[4] = GetBValue(p_data[j * wide + (i + 2)]);
            B[5] = GetBValue(p_data[(j + 1) * wide + (i + 1)]);
            B[6] = GetBValue(p_data[(j + 1) * wide + (i + 2)]);

            myB[4] = (float)
                (B[0] + B[1] + B[2] + B[3] + B[4] + B[5] + B[6]) / 7;
            bunsanB[4] = 0;
            for (n = 0; n <= 6; n++)
                bunsanB[4] += B[n] * B[n] - myB[4] * myB[4];

            //第六邻域区域红
            R[0] = GetRValue(p_data[(j - 2) * wide + (i + 1)]);
            R[1] = GetRValue(p_data[(j - 2) * wide + (i + 2)]);
            R[2] = GetRValue(p_data[(j - 1) * wide + i]);
            R[3] = GetRValue(p_data[(j - 1) * wide + (i + 1)]);
            R[4] = GetRValue(p_data[(j - 1) * wide + (i + 2)]);
            R[5] = GetRValue(p_data[j * wide + i]);
            R[6] = GetRValue(p_data[j * wide + (i + 1)]);

            myR[5] = (float)
                (R[0] + R[1] + R[2] + R[3] + R[4] + R[5] + R[6]) / 7;
            bunsanR[5] = 0;
            for (n = 0; n <= 6; n++)
                bunsanR[5] += R[n] * R[n] - myR[5] * myR[5];

            //第六邻域区域绿
            G[0] = GetGValue(p_data[(j - 2) * wide + (i + 1)]);
            G[1] = GetGValue(p_data[(j - 2) * wide + (i + 2)]);
            G[2] = GetGValue(p_data[(j - 1) * wide + i]);
            G[3] = GetGValue(p_data[(j - 1) * wide + (i + 1)]);
            G[4] = GetGValue(p_data[(j - 1) * wide + (i + 2)]);
            G[5] = GetGValue(p_data[j * wide + i]);
            G[6] = GetGValue(p_data[j * wide + (i + 1)]);

            myG[5] = (float)
                (G[0] + G[1] + G[2] + G[3] + G[4] + G[5] + G[6]) / 7;
            bunsanG[5] = 0;
            for (n = 0; n <= 6; n++)
                bunsanG[5] += G[n] * G[n] - myG[5] * myG[5];

            //第六邻域区域蓝
            B[0] = GetBValue(p_data[(j - 2) * wide + (i + 1)]);
            B[1] = GetBValue(p_data[(j - 2) * wide + (i + 2)]);
            B[2] = GetBValue(p_data[(j - 1) * wide + i]);
            B[3] = GetBValue(p_data[(j - 1) * wide + (i + 1)]);
            B[4] = GetBValue(p_data[(j - 1) * wide + (i + 2)]);
            B[5] = GetBValue(p_data[j * wide + i]);
            B[6] = GetBValue(p_data[j * wide + (i + 1)]);

            myB[5] = (float)
                (B[0] + B[1] + B[2] + B[3] + B[4] + B[5] + B[6]) / 7;
            bunsanB[5] = 0;
            for (n = 0; n <= 6; n++)
                bunsanB[5] += B[n] * B[n] - myB[5] * myB[5];


            //第七近邻域红
            R[0] = GetRValue(p_data[(j - 2) * wide + (i - 2)]);
            R[1] = GetRValue(p_data[(j - 2) * wide + (i - 1)]);
            R[2] = GetRValue(p_data[(j - 1) * wide + (i - 2)]);
            R[3] = GetRValue(p_data[(j - 1) * wide + (i - 1)]);
            R[4] = GetRValue(p_data[(j - 1) * wide + i]);
            R[5] = GetRValue(p_data[j * wide + (i - 1)]);
            R[6] = GetRValue(p_data[j * wide + i]);

            myR[6] = (float)
                (R[0] + R[1] + R[2] + R[3] + R[4] + R[5] + R[6]) / 7;
            bunsanR[6] = 0;
            for (n = 0; n <= 6; n++)
                bunsanR[6] += R[n] * R[n] - myR[6] * myR[6];

            //第七近邻域绿
            G[0] = GetGValue(p_data[(j - 2) * wide + (i - 2)]);
            G[1] = GetGValue(p_data[(j - 2) * wide + (i - 1)]);
            G[2] = GetGValue(p_data[(j - 1) * wide + (i - 2)]);
            G[3] = GetGValue(p_data[(j - 1) * wide + (i - 1)]);
            G[4] = GetGValue(p_data[(j - 1) * wide + i]);
            G[5] = GetGValue(p_data[j * wide + (i - 1)]);
            G[6] = GetGValue(p_data[j * wide + i]);
            myG[6] = (float)
                (G[0] + G[1] + G[2] + G[3] + G[4] + G[5] + G[6]) / 7;
            bunsanG[6] = 0;
            for (n = 0; n <= 6; n++)
                bunsanG[6] += G[n] * G[n] - myG[6] * myG[6];

            //第七近邻域蓝
            B[0] = GetBValue(p_data[(j - 2) * wide + (i - 2)]);
            B[1] = GetBValue(p_data[(j - 2) * wide + (i - 1)]);
            B[2] = GetBValue(p_data[(j - 1) * wide + (i - 2)]);
            B[3] = GetBValue(p_data[(j - 1) * wide + (i - 1)]);
            B[4] = GetBValue(p_data[(j - 1) * wide + i]);
            B[5] = GetBValue(p_data[j * wide + (i - 1)]);
            B[6] = GetBValue(p_data[j * wide + i]);
            myB[6] = (float)
                (B[0] + B[1] + B[2] + B[3] + B[4] + B[5] + B[6]) / 7;
            bunsanB[6] = 0;
            for (n = 0; n <= 6; n++)
                bunsanB[6] += B[n] * B[n] - myB[6] * myB[6];


            //第八近邻域区域红
            R[0] = GetRValue(p_data[j * wide + (i - 1)]);
            R[1] = GetRValue(p_data[j * wide + i]);
            R[2] = GetRValue(p_data[(j + 1) * wide + (i - 2)]);
            R[3] = GetRValue(p_data[(j + 1) * wide + (i - 1)]);
            R[4] = GetRValue(p_data[(j + 1) * wide + i]);
            R[5] = GetRValue(p_data[(j + 2) * wide + (i - 2)]);
            R[6] = GetRValue(p_data[(j + 2) * wide + (i - 1)]);
            myR[7] = (float)
                (R[0] + R[1] + R[2] + R[3] + R[4] + R[5] + R[6]) / 7;
            bunsanR[7] = 0;
            for (n = 0; n <= 6; n++)
                bunsanR[7] += R[n] * R[n] - myR[7] * myR[7];

            //第八近邻域区域绿
            G[0] = GetGValue(p_data[j * wide + (i - 1)]);
            G[1] = GetGValue(p_data[j * wide + i]);
            G[2] = GetGValue(p_data[(j + 1) * wide + (i - 2)]);
            G[3] = GetGValue(p_data[(j + 1) * wide + (i - 1)]);
            G[4] = GetGValue(p_data[(j + 1) * wide + i]);
            G[5] = GetGValue(p_data[(j + 2) * wide + (i - 2)]);
            G[6] = GetGValue(p_data[(j + 2) * wide + (i - 1)]);
            myG[7] = (float)
                (G[0] + G[1] + G[2] + G[3] + G[4] + G[5] + G[6]) / 7;
            bunsanG[7] = 0;
            for (n = 0; n <= 6; n++)
                bunsanG[7] += G[n] * G[n] - myG[7] * myG[7];

            //第八近邻域区域蓝
            B[0] = GetBValue(p_data[j * wide + (i - 1)]);
            B[1] = GetBValue(p_data[j * wide + i]);
            B[2] = GetBValue(p_data[(j + 1) * wide + (i - 2)]);
            B[3] = GetBValue(p_data[(j + 1) * wide + (i - 1)]);
            B[4] = GetBValue(p_data[(j + 1) * wide + i]);
            B[5] = GetBValue(p_data[(j + 2) * wide + (i - 2)]);
            B[6] = GetBValue(p_data[(j + 2) * wide + (i - 1)]);
            myB[7] = (float)
                (B[0] + B[1] + B[2] + B[3] + B[4] + B[5] + B[6]) / 7;
            bunsanB[7] = 0;
            for (n = 0; n <= 6; n++)
                bunsanB[7] += B[n] * B[n] - myB[7] * myB[7];

            //第九近邻域区域红
            R[0] = GetRValue(p_data[j * wide + i]);
            R[1] = GetRValue(p_data[j * wide + (i + 1)]);
            R[2] = GetRValue(p_data[(j + 1) * wide + i]);
            R[3] = GetRValue(p_data[(j + 1) * wide + (i + 1)]);
            R[4] = GetRValue(p_data[(j + 1) * wide + (i + 2)]);
            R[5] = GetRValue(p_data[(j + 2) * wide + (i + 1)]);
            R[6] = GetRValue(p_data[(j + 2) * wide + (i + 2)]);

            myR[8] = (float)
                (R[0] + R[1] + R[2] + R[3] + R[4] + R[5] + R[6]) / 7;
            bunsanR[8] = 0;
            for (n = 0; n <= 6; n++)
                bunsanR[8] += R[n] * R[n] - myR[8] * myR[8];

            //第九近邻域区域绿
            G[0] = GetGValue(p_data[j * wide + i]);
            G[1] = GetGValue(p_data[j * wide + (i + 1)]);
            G[2] = GetGValue(p_data[(j + 1) * wide + i]);
            G[3] = GetGValue(p_data[(j + 1) * wide + (i + 1)]);
            G[4] = GetGValue(p_data[(j + 1) * wide + (i + 2)]);
            G[5] = GetGValue(p_data[(j + 2) * wide + (i + 1)]);
            G[6] = GetGValue(p_data[(j + 2) * wide + (i + 2)]);

            myG[8] = (float)
                (G[0] + G[1] + G[2] + G[3] + G[4] + G[5] + G[6]) / 7;
            bunsanG[8] = 0;
            for (n = 0; n <= 6; n++)
                bunsanG[8] += G[n] * G[n] - myG[8] * myG[8];

            //第九近邻域区域蓝
            B[0] = GetBValue(p_data[j * wide + i]);
            B[1] = GetBValue(p_data[j * wide + (i + 1)]);
            B[2] = GetBValue(p_data[(j + 1) * wide + i]);
            B[3] = GetBValue(p_data[(j + 1) * wide + (i + 1)]);
            B[4] = GetBValue(p_data[(j + 1) * wide + (i + 2)]);
            B[5] = GetBValue(p_data[(j + 2) * wide + (i + 1)]);
            B[6] = GetBValue(p_data[(j + 2) * wide + (i + 2)]);

            myB[8] = (float)
                (B[0] + B[1] + B[2] + B[3] + B[4] + B[5] + B[6]) / 7;
            bunsanB[8] = 0;
            for (n = 0; n <= 6; n++)
                bunsanB[8] += B[n] * B[n] - myB[8] * myB[8];

            //求方差最小的近邻域区域nmin
            bmR = bunsanR[0];
            nminR = 0;
            for (n = 0; n <= 6; n++)
            {
                if (bmR > bunsanR[n])
                {
                    bmR = bunsanR[n];
                    nminR = n;
                }//四舍五入nmin作为图像像素值


                r = (int)(myR[nminR] + 0.5);
            }

            bmG = bunsanG[0];
            nminG = 0;
            for (n = 0; n <= 6; n++)
            {
                if (bmG > bunsanG[n])
                {
                    bmG = bunsanG[n];
                    nminG = n;
                }//四舍五入nmin作为图像像素值


                g = (int)(myG[nminG] + 0.5);
            }

            bmB = bunsanB[0];
            nminB = 0;
            for (n = 0; n <= 6; n++)
            {
                if (bmB > bunsanB[n])
                {
                    bmB = bunsanB[n];
                    nminB = n;
                }//四舍五入nmin作为图像像素值
                b = (int)(myB[nminB] + 0.5);
            }
            p_data[j * wide + i] = RGB(r, g, b);
    }
    *pimg = *p_data;
    delete(data);
}