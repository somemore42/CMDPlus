#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<graphics.h>
//#define WIDTH 500
//#define HEIGHT 400
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
int main(int argc, char* argv[])
{
    int WIDTH = 500;
    int HEIGHT = 400;
    int fps = 24;
    int total = 24;
    char floder[128] = "";
    int sleepTime = 42;

    int argcp = 0;
    char argcc = '\0';

    if (argc == 1) {
        printf("[COMMAND] VideoFrameStream  i [image_floder-path] t [total_frames] /s [Width] [Height] / f [fps]\n");
        return -1;
    }
    else {
        //printf("else ok!");
        for (; argcp < argc;) {
            argcp++;
            if (!(argcp < argc)) { break; }
            argcc = *(argv[argcp]);
            if (argcc == 's') {
                argcp++;
                WIDTH = Number(argv[argcp]);
                argcp++;
                HEIGHT = Number(argv[argcp]);
                continue;
            }
            else
                if (argcc == 't') {
                    argcp++;
                    total = Number(argv[argcp]);
                    continue;
                }else 
                    if (argcc == 'i') {
                        argcp++;
                        floder[0] = '\0';
                        strlink(floder, argv[argcp]);// printf("i ok!");
                        continue;
                    }
                    else
                        if (argcc == 'f') {
                            argcp++;
                            fps = Number(argv[argcp]);
                            continue;
                        }
                        else { printf("Wrong parama at %d: %s,which ought to be one of i,t,s or f.\n", argcp, argv[argcp]); return -2; }
        }
    }
    sleepTime =(int)( (double)1 / (double)fps*1000);
    initgraph(WIDTH, HEIGHT);
    IMAGE background;
    BeginBatchDraw();
    char buf[255]="";
    while (1) {
        for (int i = 1; i < total; i++)
        {
            buf[0] = '\0';
            //strlink(buf,floder);
            sprintf_s(buf, "%s//%d.jpg",floder, i);

            loadimage(&background, buf, WIDTH, HEIGHT);
            putimage(0, 0, &background);
            FlushBatchDraw();
            Sleep(sleepTime);
        }
    }
    EndBatchDraw();
    return 0;
}