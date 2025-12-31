#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<graphics.h>
#include <math.h>
#include <time.h>
int Eval(double, double, double*, double*);
#define PIC_WIDTH  width                // 照片的宽度
#define PIC_HEIGHT height                // 照片的高度
#define PI acos(-1.0)
const int Width = GetSystemMetrics(SM_CXSCREEN);
const int Height = GetSystemMetrics(SM_CYSCREEN);

DWORD* img_ptr1;                  // 原图片片内存指针
DWORD* img_ptr2;                  // 处理后显示的位图内存指针
int sign(int x);

int antialias = 2;
int mapping = 13;                  // 调整该参数获取不同的效果
double scale = 1;
int debug = FALSE;
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
int main()
{

    char o[255] = "";
    int i, j, i2, j2, ai, aj;
    int found, index;
    int outofrange = FALSE;
    double x, y;
    double xnew, ynew;
    double rsum, gsum, bsum;
    FileDialog(o);
    IMAGE* ter=NULL;
    ter = new IMAGE;
    loadimage(ter,o);
    int width;        // 图像宽度
    int height;        // 图像高度
    double tran = 0;
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
    IMAGE src_img;                    // 原位图    
    IMAGE dest_img(PIC_WIDTH, PIC_HEIGHT);        // 处理后显示的位图
    //loadimage()
    char mode[12] = "";
    InputBox(mode,11,"Select one mode from 1-13 and input it.","模式选择","0",300,80,1);
    mapping = Number(mode);
    initgraph(PIC_WIDTH, PIC_HEIGHT);
    setbkcolor(WHITE);
    cleardevice();
    loadimage(&src_img, o, PIC_WIDTH, PIC_HEIGHT);    // 加载原图

    img_ptr1 = GetImageBuffer(&src_img);
    img_ptr2 = GetImageBuffer(&dest_img);

    for (j = 0; j < PIC_HEIGHT; j++)
    {
        for (i = 0; i < PIC_WIDTH; i++)
        {
            found = 0;
            rsum = 0;
            gsum = 0;
            bsum = 0;
            /* Default colour */
            img_ptr2[j * PIC_WIDTH + i] = BLACK;
            /* Antialias loop */
            for (ai = 0; ai < antialias; ai++)
            {
                x = 2 * (i + ai / (double)antialias) / PIC_WIDTH - 1;
                x /= scale;

                for (aj = 0; aj < antialias; aj++)
                {
                    y = 2 * (j + aj / (double)antialias) / PIC_HEIGHT - 1;
                    y /= scale;

                    /* Apply Distortion */
                    if (!Eval(x, y, &xnew, &ynew))
                        continue;

                    /*
                       Determine the point to sample from
                       Convert normlaised coordinate to input image coordinates
                    */
                    i2 = 0.5 * PIC_WIDTH * (xnew + 1);
                    j2 = 0.5 * PIC_HEIGHT * (ynew + 1);
                    if (i2 < 0 || i2 >= PIC_WIDTH || j2 < 0 || j2 >= PIC_HEIGHT)
                    {
                        outofrange = TRUE;
                        continue;
                    }

                    /* Sum over the antialias group */
                    index = j2 * PIC_WIDTH + i2;
                    rsum += GetRValue(img_ptr1[index]);
                    gsum += GetGValue(img_ptr1[index]);
                    bsum += GetBValue(img_ptr1[index]);
                    //asum += inimage[index].a;
                    found++;
                }
            }
            /* Finally assign the colour */
            if (found > 0)
            {
                index = j * PIC_WIDTH + i;
                int Mr = rsum / (antialias * antialias);
                int Mg = gsum / (antialias * antialias);
                int Mb = bsum / (antialias * antialias);
                /*  int Ma = asum / (antialias * antialias);*/
                img_ptr2[index] = RGB(Mr, Mg, Mb);
            }
        }
    }
    putimage(0, 0, &dest_img);
    time_t n;
    n=time(&n);
    //String(n, o);
    strlink(String(n, o), ".jpg");
    saveimage(o);
    return _getch();
}

/*
   Calculate coordinates in input image from points in output image
   x and y are normalised coordinates, -1 ..1
   xnew and ynew are also normalised coordinates
*/
int Eval(double x, double y, double* xnew, double* ynew)
{
    double phi, radius, radius2;
    double xtmp, ytmp;
    double denom;
    /* Some things that may be needed */
    radius2 = x * x + y * y;
    radius = sqrt(radius2);
    phi = atan2(y, x);

    switch (mapping)
    {
    case 1:
        /*
           Square root radial function
           Normally clamped to radius <= 1
        */
        radius = sqrt(radius);
        *xnew = radius * cos(phi);
        *ynew = radius * sin(phi);
        break;
    case 2:
        /*
           arcsin radial function
        */
        if (radius > 1)
            return(FALSE);
        radius = 2 * asin(radius) / PI;
        *xnew = radius * cos(phi);
        *ynew = radius * sin(phi);
        break;
    case 3:
        /*
           sin radial function
           Normally clamped to radius <= 1
        if (radius > 1)
           return(FALSE);
        */
        radius = sin(PI * radius / 2);
        *xnew = radius * cos(phi);
        *ynew = radius * sin(phi);
        break;
    case 4:
        /*
           radius to a power, radial function
           Normally clamped to radius <= 1
        if (radius > 1)
           return(FALSE);
        */
        radius = pow(radius, 1.5);
        *xnew = radius * cos(phi);
        *ynew = radius * sin(phi);
        break;
    case 5:
        /*
           sin function cartesian function
        */
        *xnew = sin(PI * x / 2);
        *ynew = sin(PI * y / 2);
        break;
    case 6:
        /*
           square cartesian function
           Includes quadrant preserving
        */
        *xnew = x * x * sign(x);
        *ynew = y * y * sign(y);    //不对
        break;
    case 7:
        /*
           arc sine cartesian function
        */
        *xnew = asin(x) / PI * 2;
        *ynew = asin(y) / PI * 2;
        break;
    case 8:
        /*
           (1-ar^2) cartesian function
        */
        *xnew = x * (1 - 0.1 * radius2) / (1 - 0.1);
        *ynew = y * (1 - 0.1 * radius2) / (1 - 0.1);
        break;
    case 9:
        /*
           Method by H. Farid and A.C. Popescu
           Used for modest lens with good fit
        */
        denom = 1 - 0.6 * radius2;
        xtmp = x / denom;
        ytmp = y / denom;
        if (xtmp <= -1 || xtmp >= 1 || ytmp <= -1 || ytmp >= 1)
            return(FALSE);
        denom = 1 - 0.6 * (xtmp * xtmp + ytmp * ytmp);
        if (fabs(denom) < 0.000001)
            return(FALSE);
        *xnew = x / denom;
        *ynew = y / denom;
        break;
    case 10:
        /*
           Logarithmic relationship
           eg: fitted to test pattern with 2 parameters
        */
        radius = 0.049 * pow(10.0, 1.280 * radius) - 0.049;
        *xnew = radius * cos(phi);
        *ynew = radius * sin(phi);
        break;
    case 11:
        /*
           General third order polynomial
           eg: fitted to test pattern with 3 parameters
        */
        radius = 0.819 * radius2 * radius + 0.046 * radius2 + 0.152 * radius;
        *xnew = radius * cos(phi);
        *ynew = radius * sin(phi);
        break;
    case 12:
        /*
           Janez Pers, Stanislav Kovacic
           Alternative Model o Radial Distortion in Wide-Angle Lenses
           Single parameter model
        */
        radius = -0.5 * 0.3 * (exp(-2 * radius / 0.3) - 1) / (exp(-radius / 0.3));
        *xnew = radius * cos(phi);
        *ynew = radius * sin(phi);
        break;
    case 13:
        /*
           Image rotate by parameter1 in radians
        */
        *xnew = radius * cos(phi + 0.5);
        *ynew = radius * sin(phi + 0.5);
        break;
    case 0:
    default:
        /*
           Unity mapping
        */
        *xnew = x;
        *ynew = y;
        break;
    }
    return(TRUE);
}
int sign(int x)
{
    return (x > 0) - (x < 0);
}