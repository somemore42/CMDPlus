#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<graphics.h>
const int W = GetSystemMetrics(SM_CXSCREEN);
const int H = GetSystemMetrics(SM_CYSCREEN);

int FileDialog(char* path);      // 获取图片地址
char szFile[MAX_PATH] = { 0 };
void AddPhoto(char szFile[]);    // 添加照片

class Algorithm
{
public:
    Algorithm(IMAGE* img, int width, int heigth);
    void La();      // Laplacian算子        
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

    loadimage(&img, szFile);
    width = img.getwidth();
    height = img.getheight();

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
    ;
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
            myA.La();
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
    _getch();
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

void Algorithm::La()
{
    int YZ = 130;
    while (true)
    {
        char s[10];
        InputBox(s, 10, "请输入阈值,建议值为20");
        // 将用户输入转换为数字
        sscanf(s, "%d", &YZ);
        if (YZ > 0 && YZ < 255)
        {
            break;
        }
        else
        {
            MessageBox(NULL, "请输入0-255区间的值", "提示", MB_ICONQUESTION | MB_YESNO);
        }
    }
    DWORD* pMem = GetImageBuffer(pimg);
    int** Gray = (int**)malloc(sizeof(int*) * HEIGHT);
    int** result = (int**)malloc(sizeof(int*) * HEIGHT);
    for (int i = 0; i < HEIGHT; i++)
    {
        Gray[i] = (int*)malloc(sizeof(int) * WIDTH);
        result[i] = (int*)malloc(sizeof(int) * WIDTH);
    }
    //1.图像灰度化
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            *pMem = BGR(*pMem);
            Gray[i][j] = (GetRValue(*pMem) * 299 + GetGValue(*pMem) * 587 + GetBValue(*pMem) * 114 + 500) / 1000;
            *pMem = RGB(Gray[i][j], Gray[i][j], Gray[i][j]);
            pMem++;
        }
    }
    pMem -= HEIGHT * WIDTH;

    //2.对图像利用算子处理
    for (int i = 1; i < HEIGHT - 1; i++)
    {
        for (int j = 1; j < WIDTH - 1; j++)
        {
            //拉普拉斯算子
            int nSum = 4 * Gray[i][j] - Gray[i + 1][j] - Gray[i][j - 1] - Gray[i][j + 1] - Gray[i - 1][j];
            if (nSum > 20)
                result[i][j] = 255;
            else
                result[i][j] = 0;
        }
    }

    //3.将处理后的图像显示出来
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            *pMem = RGB(result[i][j], result[i][j], result[i][j]);
            pMem++;
        }
    }
    for (int i = 0; i < HEIGHT; i++)
    {
        free(Gray[i]);
        free(result[i]);
    }
    // 再释放每行
    free(Gray);
    free(result);
    Gray = NULL; // 赋空
    result = NULL;
}