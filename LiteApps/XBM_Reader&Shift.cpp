#include <iostream>
#include<fstream>
#include<windows.h>
#include<graphics.h>

using namespace std;
void decode(int n) {
	int array[8] = { 0 };
	for (int i = 0; i < 8; i++) {
		array[i] = n % 2;
		n /= 2;
	}
	for (int i = 0; i < 8; i++) {
		if (array[i])cout << "□";
		else cout << "■";
	}
}
void decode2px(int n,int *p) {
	int array[8] = { 0 };
	for (int i = 0; i < 8; i++) {
		array[i] = n % 2;
		n /= 2;
	}
	for (int i = 0; i < 8; i++,p++) {
		if (array[i])*p = 0;
		else *p = 1;
	}
}
int C2N(char c) {
	if(c>='0'&&c<='9')
	return c - '0';
	if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 10;
}
int t16(char c[]) {
	int num = 0;
	num = C2N(c[2]) * 16 + C2N(c[3]);
	return num;
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
int getNum(char* c) {
	int i = 0; int space = 0; 
	int lastone = 0;//o is char while 1 is space
	char value[8] = "";
	while (c[i] != 0) {
		if (c[i] == ' ' && lastone == 0) { space++; }
		if (c[i] == ' ' && lastone == 1) {}
		if (c[i] == ' ')lastone = 1; else lastone = 0;
		i++;
		if (space == 2) break;
	}
	int j ;
	for (j=0; c[i] != 0; i++) {
		if (c[i] <= '9' && c[i] >= '0') {
			value[j] = c[i];
			j++;
		}
	}
	value[j + 1] = '\0';
	return Number(value);
}
int getSize(int l) {
	int px = l / 8;
	if (px * 8 < l) { px += 1; }
	else px = px;
	return px * 8;
}
int Size(char c[]) {
	return getSize(getNum(c));
}
void drawSqare(int xlu, int ylu, int xrd, int yrd) { solidrectangle(xlu, ylu, xrd, yrd); }
void drawout(int w, int h,int realw,int realh, int* data,int px=5) {
	int nowX = 0; int nowY = 0;
	int length = realw * realh;
	if (px <= 0 || px > 25)px = 5;
	initgraph(w*px, h*px, 0);
	for (int i = 1; i <=length; i++) {

		if (*data == 0) { setlinecolor(BLACK); setfillcolor(BLACK);		}
		else { setlinecolor(WHITE); setfillcolor(WHITE);		}
		drawSqare(nowX, nowY, nowX + px, nowY + px);
		nowX += px;
		data++;

		if (i % realw == 0) { nowY += px; nowX = 0; }//next line
	}

}
void saveToImg(int w,int h,LPCTSTR name,int px=5) {
	if (px <= 0||px>25)px = 5;
	IMAGE s; 
	getimage(&s, 0, 0, w*px, h*px); 
	saveimage(name, &s);

}
int main(int argc, char* argv[], char* envp[])
{
	
	char file[100] = "";
	char line[255] = "";
	char data = ' ';
	int*(xbmpx);
	int* head;
	int px = 0;
	int state = 0;//1 head 2 data 3 end;
	char x16[8] = "";
	int counter = 0;
	ifstream xbm;
	ifstream ini;
	int xbmW = 0;
	int xbmH = 0;
	int showW = 0;
	int showH = 0;
	int allpx = 0;
	int pxx = 10;
	char cppx[7] = "";
	int linew = 0;
	if (argc == 2) {
		strcpy_s(file, argv[1]);
	}
	if (argc == 1) {
		cout << "输入要打开的文件路径，或拖曳文件到本程序文件上（可以是这个窗口）";
		cin >> file;
	}
	try {
		ini.open(".//xbm.ini");
		ini.getline(cppx, 6);
		pxx = Number(cppx);
		ini.close();
		if (!pxx) {
			pxx = 10;
			throw "xbm.ini Not Found, use default value, continue...";
		}
	}
	catch (const char msg[]) { cout << msg << endl; }
	xbm.open(file);
	xbm.getline(line, 255); showW = getNum(line); xbmW = Size(line);
	xbm.getline(line, 255);  showH = getNum(line); xbmH = Size(line);
	if (argc == 1) {
		cout << "WIDTH:" << showW << ' ';
		cout << "HIGHT:" << showH << ' ';
		cout << endl;
	}
	allpx = xbmW * xbmH;
	xbmpx = new  int[allpx];//visual buffer
	head = xbmpx;//copy original start
	linew = xbmW / 8;
	while (xbm.eof() == 0) {
		xbm.get(data);
		if (data == '{'&&state==0)state = 1;
		if (state == 1) {
			break;
		}
	}
	int step = 0;

	while (xbm.eof() == 0) {
		xbm.get(data); 
		if (data == ',') {
			counter++;
			if (argc == 1) {
				decode(t16(x16));//output
			}
			decode2px(t16(x16), &xbmpx[0]); xbmpx += 8;
			step = 0;//end read
			if (counter % linew == 0) { if (argc == 1) { cout << endl; } }
			continue;
		}
		if (data == '}') { if (argc == 1) { decode(t16(x16)); cout << endl; }decode2px(t16(x16), &xbmpx[0]); xbmpx += 8;  break; }
	    if (data != ' '&&data!='\n') {
			x16[step] = data;
			step++;
		}
		
		//cout << data << endl;;
	}
	//for (int i = 0; i < allpx; i++) { cout << *(head + i) << " ";; }
	if (argc == 1) {
		cout << "\n即将生成图片...";
		Sleep(2000);
	}
	drawout(showW,showH,xbmW,xbmH,head,pxx);
	saveToImg(showW, showH, _T("xbm_jpg.jpg"),pxx);
	//delete [] head;
	xbm.close();
	if (argc == 1) {
		Sleep(5000);
		closegraph();
		cout << endl<<"操作完成！"<<endl;
	}
	else { while (1) { Sleep(1000); } }
/*TEST CODE
	static int s[] = {
	   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x07, 0x01, 0x00, 0x0c,
   0xe1, 0x03, 0x0c, 0x31, 0x06, 0x0c, 0x99, 0x0c, 0x0c, 0xc9, 0x09, 0x0c,
   0x09, 0x0a, 0x0c, 0x09, 0x08, 0x0c, 0x19, 0x0c, 0x0c, 0x31, 0x16, 0x0c,
   0xe1, 0x2f, 0x0c, 0x01, 0x5c, 0x0c, 0x01, 0xb8, 0x0c, 0x01, 0x70, 0x0d,
   0x01, 0xe0, 0x0d, 0x01, 0xe0, 0x0c, 0x01, 0x00, 0x0c, 0xff, 0xff, 0x0f,
   0xfe, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	for (int i = 0; i < 69; i++) {
		decode(s[i]);
		if ((i+1) % 3 == 0)cout << endl;
	}
	*/
	system("pause");
	return 0;
}
