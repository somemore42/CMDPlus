#include<iostream>
#include<iomanip>
#include<conio.h>
#include<fstream>
#include <graphics.h>
#include<stdlib.h>
#include<cstring>
using namespace std;


HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
void warning(const char* c) { SetConsoleTextAttribute(hand, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);  printf("%s", "[Warning]:"); printf("%s\n", c);  }
void log(const char* c) { SetConsoleTextAttribute(hand, FOREGROUND_INTENSITY | FOREGROUND_BLUE); printf("%s", "[Info]:"); printf("%s\n", c); };
void init(int su[]);//从文件in.txt中将数独值表格读入数独数组su
void fill(int n, int su[]);//递归函数，填写格子n-格子80，即su[n]-su[90]
int place(int n, int su[]);//剪枝函数，判断第n个格子中的数字su[n]是否与数组su中已有数字冲突
void printg(int su[]);//根据当前的数独数组su显示数独表，图形界面
void import(int su[], const char* file);
int main(int argc, char* argv[], char* envp[])
{
	int su[81];//9*9数组的值矩阵数组
	char file[255] = {0};
if (argc == 1) {
	log("数独数据文件格式：将宫格里的数字逐行自上而下写入，数与数以空格或换行隔开，待填宫格用0表示\n");
	cout << "输入数独数据文本文件路径，或拖曳文件到本程序上（可以是这个窗口）";
	cin >> file;
	import(su,file);
	printg(su);	//显示数独
	fill(0, su);	//求解数独，填写su[0]~su[80]，
	}
if (argc == 2) {
	strcpy_s(file,argv[1]);
	import(su,file);//从文件in.txt中将数独值矩阵读入数组su
	printg(su);	//显示数独
	fill(0, su);	//求解数独，填写su[0]~su[80]，
	}
if(argc>=3) { warning("一次只能打开一个文件！\n"); }
	while (1) { Sleep(1000); }
	return 0;
}
void init(int su[])
{
	ifstream cin;
	cin.open("NumAlone_Data.txt", ios_base::binary);
	for (int n = 0; n < 81; n++)
		cin >> su[n];
	cin.close();
}
void import(int su[],const char *file)
{
	ifstream cin;
	cin.open(file, ios_base::binary);
	for (int n = 0; n < 81; n++)
		cin >> su[n];
	cin.close();
}
void fill(int n, int su[])
{
	int r = n / 9, c = n % 9;
	if (n == 81) printg(su); //或printg(su);
	else
		if (su[n] != 0) fill(n + 1, su);
		else
			for (su[n] = 9; su[n] > 0; su[n]--)
				if (place(n, su))
					fill(n + 1, su);//填写su[n+1]~su[80]

}
int place(int n, int su[])
{
	int r = n / 9, c = n % 9;
	int i, j;
	//检查行方向冲突（同列不同行的数字）
	for (i = 0; i < 9; i++)
	{
		if (i == r) continue;
		if (su[i * 9 + c] == su[n]) return 0;
	}
	//检查列方向冲突（同行不同列的数字）
	for (i = 0; i < 9; i++)
	{
		if (i == c) continue;
		if (su[r * 9 + i] == su[n]) return 0;
	}
	//检查小矩阵冲突
	int rr = r / 3 * 3, cc = c / 3 * 3;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			if (i + rr == r && j + cc == c) continue;
			if (su[(i + rr) * 9 + j + cc] == su[n]) return 0;
		}
	return 1;
}
void print(int su[])
{
	int static t = -1;
	t++;
	char head[2][30] = { "-------原始数据------","-------数独结果------" };
	cout << setw(4) << " " << head[t] << endl;
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)	cout << setw(3) << su[r * 9 + c];
		cout << endl;
	}
}
void printg(int su[])
{
	int static t = -1;
	t++;
	if (t == 0)
	{
		initgraph(1028, 500);	// 创建绘图窗口	
		setbkcolor(RGB(59, 154, 241));// 设置背景色，蓝色
		cleardevice();// 用背景色清空屏幕
	}

	//1.设置本次数组表格的原点
	int ox = 60 + t * 514, oy = 20;
	//2.显示标题
	char head[2][30] = { "-------原始数据------","-------数独结果------" };
	RECT rh[2];
	//设置文本参数：白色文字，32像素，微软雅黑，透明背景
	settextcolor(WHITE);
	settextstyle(32, 0, _T("微软雅黑"));
	setbkmode(TRANSPARENT);
	rh[t].left = ox, rh[t].top = oy, rh[t].right = 9 * 40 + ox, rh[t].bottom = 40 + oy;
	//drawtext(head[t], rh[t], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//outtextxy(head[t],  DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	outtextxy(100,20,_T("------ - 原始数据------"));
	outtextxy(650,20,_T("-------数独结果------"));
	//3.绘制表格后的阴影
	setfillcolor(RGB(197, 217, 241)); //阴影颜色为灰色
	solidrectangle(ox - 2, 40 + oy - 2, 9 * 40 + ox + 2, 10 * 40 + oy + 2); //阴影面积比数独表宽2像素
	//4.绘制数独表：数独表由9*9个正方形构成，每个正方形中有一个数字字符
	RECT rt[2][9][9];//正方形数组。第一次调用print，显示rt[0]。第二次调用print，显示rt[1]
	int static label[81];//标记数组，用于记录提示数格，区分数字的颜色
	//设置正方形参数：填充白色，红色框线
	setlinecolor(RGB(114, 162, 220));
	//设置数字字符参数：高32像素，字体Candara，透明背景
	settextstyle(32, 0, _T("Candara"));
	setbkmode(TRANSPARENT);
	//绘制9*9个正方形，正方形rt[t][r][c]显示数字su[r*9+c]
	int r, c, fc = 0;
	for (r = 0; r < 9; r++)
		for (c = 0; c < 9; c++)
		{
			//设置宫的颜色
			if ((r / 3 + c / 3) % 2 == 0)
				setfillcolor(RGB(255, 255, 255));
			else
				setfillcolor(RGB(255, 204, 204));
			//设置数字颜色
			if (su[r * 9 + c] && t == 0 || label[r * 9 + c]) label[r * 9 + c]++, settextcolor(RGB(255, 0, 0));//提示数颜色为红色
			else settextcolor(RGB(0, 102, 255)); //空格数字为蓝色
			//绘制正方形和其中的数字
			rt[t][r][c].left = c * 40 + ox, rt[t][r][c].top = (r + 1) * 40 + oy, rt[t][r][c].right = (c + 1) * 40 + ox, rt[t][r][c].bottom = (r + 2) * 40 + oy;
			fillrectangle(rt[t][r][c].left, rt[t][r][c].top, rt[t][r][c].right, rt[t][r][c].bottom);
			drawtext(su[r * 9 + c] + '0', &rt[t][r][c], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}

	//_getch();
	//if (t)	closegraph();			// 关闭绘图窗口
}