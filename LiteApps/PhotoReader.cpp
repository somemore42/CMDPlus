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
int main() {
    int  width = 0;
    int  height = 0;
    IMAGE imgpolt, imgpol;
    char o[255] = "";
    printf("请选择图片\n");
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
    loadimage(&imgpolt, o, width, height);
    initgraph(width, height);
    putimage(0, 0, &imgpolt);
    while (1) {
    x = _getch();
    }

    return 0;
}