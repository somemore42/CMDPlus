#undef UNICODE
#undef _UNICODE
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<graphics.h>
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
int strcopy(char* target, char* origin) {
	int i = 0;
	for (i = 0; origin[i] != 0;i++) {
		target[i] = origin[i];
	}
	i++;
	target[i] = 0;
	return i;
} 
void location(int w,int h,int &x,int &y,int length) {
	int cx = w / 2;
	int cy = h / 2;
	x = cx - length / 2;
	cy -= 5;
	y = cy;
}
void moveWindow(int x,int y,int w,int h) {
	RECT rect;
	//HWND hwnd = GetHWnd();
	HWND d = GetConsoleWindow();
	GetWindowRect(d, &rect);
	MoveWindow(d, x, y, w, h, TRUE);
}
void Draw(int w,int h,int x,int y,char *c,int r=255,int g=255,int b=255) {
	//HWND hd = GetHWnd();
	//SetWindowTextA(hd, "-   ");
	//Sleep(200);
	//initgraph(w, h, 0);
	setcolor(RGB(0,0,0));
	setbkcolor(RGB(r,g,b));
	setlinecolor(RGB(0,0,0));
	cleardevice();
	outtextxy(x, y, _T(c));
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
int main(int argc, char* argv[], char* envp[]) {
	int w, h, x, y;
	int length = 0,c_width=7,second=0;
	int r, g, b;
	int cx=0, cy=0;
	char c[255] = "";
	time_t t;
	t = time(&t); srand(t); r = rand() % 255 + 1;
	for (int k = 0; k < (rand()%255+1); k++) {
		r = rand() % 255 + 1;
		g = rand() % 255 + 1;
		b = rand() % 255 + 1;
	}
	if (argc == 1) { printf("%s\n", "ÃüÁî£ºLabelBox [width] [height] [position:x] [position:y] [sentence] \\[keep-seconds] \\[WindowTitle]");
	//char str[1024] = "";
	//strlink(str, GetCommandLineA());
	//printf("%s\n",str);
	return 1; }
	if (argc == 6) {
		w = Number(argv[1]);
		h = Number(argv[2]);
		x = Number(argv[3]);
		y = Number(argv[4]);
		if (w < 100) { w = 100; }
		if (h < 90) { h = 90; }
		if (x <= 0 || x > 1000) { x = 0; }
		if (y <= 0 || y > 800) { y = 0; }
		length = strcopy(c,argv[5])*c_width;
		location(w, h, cx, cy, length);
		moveWindow(x, y, w, h);
		initgraph(w, h, 0);
		SetWindowText(GetHWnd(), "LabelBox");
		
		Draw(w,h,cx,cy,c,r,g,b);
		
		for (;;) { Sleep(1000); }
	}
	if (argc > 6) {
		w = Number(argv[1]);
		h = Number(argv[2]);
		x = Number(argv[3]);
		y = Number(argv[4]);
		second = Number(argv[6]);
		if (w < 100) { w = 100; }
		if (h < 90) { h = 90; }
		if (x <= 0 || x > 1000) { x = 0; }
		if (y <= 0 || y > 800) { y = 0; }
		length = strcopy(c, argv[5]) * c_width;
		location(w, h, cx, cy, length);
		moveWindow(x, y, w, h);
		initgraph(w, h, 0);
		HWND hw = GetHWnd();
		if (argc >= 8) { SetWindowText(hw,argv[7]); }
		else { SetWindowText(hw, "LabelBox"); }
		
		
		Draw(w, h, cx, cy, c, r, g, b);
		Sleep(second);
	}

	return 0;
}