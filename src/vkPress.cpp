#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
char hex[255] = "";
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
int length(char c[]) {
    int len = 0;
    for (int i = 0; i < 25585; i++) {
        if (c[i] == '\0')break;
        len++;
    }
    return len;
}
int length(const char c[]) {
    int len = 0;
    for (int i = 0; i < 25585; i++) {
        if (c[i] == '\0')break;
        len++;
    }
    return len;
}
/*
    设置键盘大小写状态
    big:为TRUE则切换大写状态,否则切换小写状态
*/
VOID MySetKeyBig(BOOL big);

/*
    模拟键盘按键，支持大小写
    str:需要按出的字符串
*/
VOID MyAnalogKey(char *str);

int main(int argc, char* argv[], char* envp[])
{
    if (argc == 1) {
        MyAnalogKey(argv[0]);
        printf("[COMMAND]:\nVKPress [FilePath]\nVKPress [StringForShow] [DelaySeconds]\n");
    }
    if (argc==2) {
        FILE* fp = fopen(argv[1], "r");
        while (!feof(fp)) {
            fscanf(fp, "%s", hex);
            MyAnalogKey(hex);
        }
    }
    
    if (argc == 3) {
        Sleep(Number(argv[2]));
        MyAnalogKey(argv[1]);
    }
    //system("pause");
    return 0;
}

VOID MySetKeyBig(BOOL big)
{
    // 判断键盘CapsLock键是否开启状态,开启状态则为大写,否则为小写
    if (GetKeyState(VK_CAPITAL))
    {
        // 如果当前键盘状态为大写,要求改小写,则模拟按键CapsLock切换状态
        if (!big)
        {
            keybd_event(VK_CAPITAL, NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
            keybd_event(VK_CAPITAL, NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
        }
    }
    else
    {
        // 如果当前键盘状态为小写,要求改大写,则模拟按键CapsLock切换状态
        if (big)
        {
            keybd_event(VK_CAPITAL, NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
            keybd_event(VK_CAPITAL, NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
        }
    }
}

VOID MyAnalogKey(char *str)
{
    int iLen = 0;
    char *tmp = NULL;
    INPUT *keys = NULL;
    BOOL bOldState = FALSE;

    // 保存此操作前的键盘状态
    bOldState = (BOOL)GetKeyState(VK_CAPITAL);
    iLen = length(str);
    tmp = (char *)malloc(iLen);
    memmove(tmp, str, iLen);
    for (int i = 0; i < iLen; i++)
    {
        // 某些符号非直属键盘按键,这里只过滤转换两个,以后用到其它字符自行添加过滤
        if (tmp[i] == ' ')
        {
            // 产生一个击键消息步骤:按下->抬起
            keybd_event(VK_SPACE, NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
            keybd_event(VK_SPACE, NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
        }
        else if (tmp[i] == ',')
        {
            keybd_event(VK_OEM_COMMA, NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
            keybd_event(VK_OEM_COMMA, NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
        }
        else if (tmp[i] >= 'a' && tmp[i] <= 'z')
        { // 根据字符大小写切换键盘大小写状态
            MySetKeyBig(0);
            // keybd_event只识别大写
            keybd_event((BYTE)tmp[i]-32, NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
            keybd_event((BYTE)tmp[i]-32, NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
        }
        else if ((tmp[i] >= 'A' && tmp[i] <= 'Z') || (tmp[i] >= '0' && tmp[i] <= '9'))
        {
            MySetKeyBig(1);
            keybd_event((BYTE)tmp[i], NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
            keybd_event((BYTE)tmp[i], NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
        }
        else
        {
            keybd_event((BYTE)tmp[i]+64, NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
            keybd_event((BYTE)tmp[i]+64, NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
        }
    }
    // 恢复此操作之前的键盘状态
    MySetKeyBig(bOldState);
    free(tmp);
}