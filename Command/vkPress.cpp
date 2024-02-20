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
    ���ü��̴�Сд״̬
    big:ΪTRUE���л���д״̬,�����л�Сд״̬
*/
VOID MySetKeyBig(BOOL big);

/*
    ģ����̰�����֧�ִ�Сд
    str:��Ҫ�������ַ���
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
    // �жϼ���CapsLock���Ƿ���״̬,����״̬��Ϊ��д,����ΪСд
    if (GetKeyState(VK_CAPITAL))
    {
        // �����ǰ����״̬Ϊ��д,Ҫ���Сд,��ģ�ⰴ��CapsLock�л�״̬
        if (!big)
        {
            keybd_event(VK_CAPITAL, NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
            keybd_event(VK_CAPITAL, NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
        }
    }
    else
    {
        // �����ǰ����״̬ΪСд,Ҫ��Ĵ�д,��ģ�ⰴ��CapsLock�л�״̬
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

    // ����˲���ǰ�ļ���״̬
    bOldState = (BOOL)GetKeyState(VK_CAPITAL);
    iLen = length(str);
    tmp = (char *)malloc(iLen);
    memmove(tmp, str, iLen);
    for (int i = 0; i < iLen; i++)
    {
        // ĳЩ���ŷ�ֱ�����̰���,����ֻ����ת������,�Ժ��õ������ַ�������ӹ���
        if (tmp[i] == ' ')
        {
            // ����һ��������Ϣ����:����->̧��
            keybd_event(VK_SPACE, NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
            keybd_event(VK_SPACE, NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
        }
        else if (tmp[i] == ',')
        {
            keybd_event(VK_OEM_COMMA, NULL, KEYEVENTF_EXTENDEDKEY | 0, NULL);
            keybd_event(VK_OEM_COMMA, NULL, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
        }
        else if (tmp[i] >= 'a' && tmp[i] <= 'z')
        { // �����ַ���Сд�л����̴�Сд״̬
            MySetKeyBig(0);
            // keybd_eventֻʶ���д
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
    // �ָ��˲���֮ǰ�ļ���״̬
    MySetKeyBig(bOldState);
    free(tmp);
}