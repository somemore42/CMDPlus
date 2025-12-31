#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include<stdio.h>
#include<conio.h>
#include<windows.h>
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
	int sign = 1;
	if (c[0] == '-') { sign = -1; i++; }
	while (c[i] != 0) {
		n *= 10;
		n += C2N(c[i]);
		i++;
	}
	return n*sign;
}
int strcopy(char* target, char* origin) {
	int i = 0;
	for (i = 0; origin[i] != 0; i++) {
		target[i] = origin[i];
	}
	//i++;
	target[i] = '\0';
	return i;
}
void strlink(char* p, char* str) {
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
void strlinkc(char* p, const char* str) {
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
void strmove(char* target, char* origin, int length) {
	int i = 0;
	for (i = 0; (origin[i] != 0) && (i < length); i++) {
		target[i] = origin[i];
	}
	//i++;
	target[i] = '\0';
}
char* String(int num, char* str, int radix = 10) {
	char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; unsigned unum; int i = 0, j, k;
	if (radix == 10 && num < 0) { unum = (unsigned)-num; str[i++] = '-'; }
	else unum = (unsigned)num; do { str[i++] = index[unum % (unsigned)radix]; unum /= radix; } while (unum);
	str[i] = '\0'; if (str[0] == '-') k = 1; else k = 0; char temp;
	for (j = k; j <= (i - 1) / 2; j++) { temp = str[j]; str[j] = str[i - 1 + k - j]; str[i - 1 + k - j] = temp; }return str;
}
struct operation {
	int v1;
	int v2;
	int v3;
	int v4;
	char name[30];
	char argv1[100];
	char argv2[100];
	char argv3[10];
	char argv4[10];
}obj;
struct xandy {
	int x;
	int y;
}location;
struct Area{
	int lx;
	int ly;
	int bx;
	int by;
}rect;
struct textline {
	char string[255];
	int height;
	int width;
	int length;
	char face[10];
	int angle;
	int eachAngle;
	int stroke;
}text;
struct globalcolor {
	int red;
	int green;
	int blue;
}color;
struct image {
	int w;
	int h;
	char url[100];
}img,foreimg,maskimg;
struct thiswindow {
	int w;
	int h;
	int x;
	int y;
}box;
/*int ll() {
	setcolor(RGB(0, 0, 0));
	setbkcolor(RGB(0,0, 0));
	setlinecolor(RGB(0, 0, 0));
	cleardevice();
	outtextxy(0,0,"");
	//settextstyle(22, 0, "微软雅黑", variable * 3600 / fors, variable * 3600 / fors, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	textwidth("");
}
*/
void toColor(int r,int g,int b) {
	color.red = r;
	color.green = g;
	color.blue = b;
}
int split(char* cmd, char* cpp) {
	int i = 0;
	int j = 0;
	int lastpace = 0;
	int now = 0;
	if (cmd[0] == ' ') { lastpace = 1; }
	while (cmd[i] != '\0') {
		if (cmd[i] == ' ') {
			if (lastpace) {
				i++;
				lastpace = 1;
			}
			else {
				cpp[j] = '\0';
				j++;
				lastpace = 1;
				i++;
				now++;
			}
		}
		else {
			cpp[j] = cmd[i];
			j++;
			lastpace = 0;
			i++;
		}
	}
	cpp[j] = '\0';
	if (!lastpace)now++;
	return now;
}
int length(char c[]) {
	int len = 0;
	for (int i = 0; i < 25585; i++) {
		if (c[i] == '\0')break;
		len++;
	}
	return len;
}
int lengthc(const char c[]) {
	int len = 0;
	for (int i = 0; i < 25585; i++) {
		if (c[i] == '\0')break;
		len++;
	}
	return len;
}
int strmac(char t[], const char o[]) {
	int hex = 'a' - 'A';
	int len = 0;
	if (length(t) != lengthc(o)) { return 0; }
	int sup = length(t);
	for (int i = 0; i < sup; i++) {
		if (t[i] == 0 || o[i] == 0)break;
		if (t[i] >= 'A' && t[i] <= 'Z') {
			if (t[i] == o[i] || (t[i] + hex) == o[i])continue;
			else return 0;
		}
		else if (t[i] >= 'a' && t[i] <= 'z') {
			if (t[i] == o[i] || (t[i] - hex) == o[i])continue;
			else return 0;
		}
		else {
			if (t[i] == o[i])continue;
			else return 0;
		}
	}
	return 1;
}
int streqa(char* a, char* b) {
	int i = 0, L = 0;
	if (length(a) != length(b)) { return 0; }
	else {
		L = length(a);
		for (; i < L; i++) {
			if (a[i] == b[i]) { continue; }
			else { return 0; }
		}
	}
	return 1;
}
void prase(char* clk, char* temp, int line) {
	int x = 0;
	x = split(clk, temp);
	int l = 0;
	char* poc = temp;
	for (int d = 0; d < x; d++) {
		if (d == 0) {
			strcopy(obj.name, poc + l);
		}
		if (d == 1) {
			strcopy(obj.argv1, poc + l);
		}
		if (d == 2) {
			strcopy(obj.argv2, poc + l);
		}
		if (d == 3) {
			strcopy(obj.argv3, poc + l);
		}
		if (d == 4) {
			strcopy(obj.argv4, poc + l);
		}
		if (d > 4) {
			printf("Fatal Error:Line %d has %d paramers.\n", line, x);
			break;
		}
		l += length(poc + l);
		l++;
		//poc++;
	}
}
int main(int argc, char* argv[]) {
	int x = 0;
	int y = 0;
	int type = 0;
	int cline = 0;//记录操作码读取到哪一行了
	char isShowCode = 0;//是否输出操作码
	char operate = 0;
	char commandline[255] = "";
	char temp[255] = "";
	HWND hwnd = 0;
	FILE* code;
	IMAGE im;
	IMAGE imfore;
	IMAGE immask;
	if (argc == 1) {
		printf("[COMMAND] CmdCanvas [Command_Canvas Operation-Code File path(*.coc)]\n");
		return 1;
	}
	if (argc >= 2) {
		hwnd = GetConsoleWindow();
		if (argc == 2) {
			if ((code = fopen(argv[1], "r")) == 0)
			{
				printf("打开操作码文件失败！\n"); return 1;
			}
			while (fgets(commandline, 255, code) != 0) {
				cline++;

				type = length(commandline);
				if (commandline[type - 1] == '\n') {//BUG：2024-6-25 13:45:22防止末行指令读取少字节
					commandline[type - 1] = '\0';
				}
				//BUG2024年6月24日18:21:26修复
				//Fuck!
				// fget获得的字符
				//串最后一个竟然是换行符，
				// 导致最后一个数字字符串参数转换为整数是总是出错！
				// 浪费我几个小时的生命！！！MD

				obj.name[0] = '\0';
				obj.argv1[0] = '\0'; obj.argv2[0] = '\0'; obj.argv3[0] = '\0'; obj.argv4[0] = '\0';
				obj.v1 = 0; obj.v2 = 0; obj.v3 = 0; obj.v4 = 0;
				temp[0] = 0;

				prase(commandline, temp, cline);
				//printf("Name:%s,argv1:%s,argv2:%s,argv3:%s,argv4:%s;",obj.name,obj.argv1,obj.argv2,obj.argv3,obj.argv4);
				//_getch();
				if (strmac(obj.name, "initial")) {
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					box.w = obj.v1;
					box.h = obj.v2;
					hwnd=initgraph(obj.v1,obj.v2);
					type=SetWindowText(hwnd,"CmdCanvas");
				}
				if (strmac(obj.name, "clearCanvas")) {
					cleardevice();
				}
				if (strmac(obj.name, "RequireAnimateFrame")) {
					BeginBatchDraw();
				}
				if (strmac(obj.name, "OutputFrame")) {
					FlushBatchDraw();
				}
				if (strmac(obj.name, "ExitAnimateFrame")) {
					EndBatchDraw();
				}
				if (strmac(obj.name, "RGB")) {
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					obj.v3 = Number(obj.argv3);
					toColor(obj.v1,obj.v2,obj.v3);
				}
				if (strmac(obj.name, "color")) {
					if (strmac(obj.argv1, "white")) { toColor(255,255,255); }
					if (strmac(obj.argv1, "black")) { toColor(0, 0, 0); }
					if (strmac(obj.argv1, "red")) { toColor(255, 0, 0); }
					if (strmac(obj.argv1, "blue")) { toColor(0, 0, 255); }
					if (strmac(obj.argv1, "green")) { toColor(0, 255, 0); }
					if (strmac(obj.argv1, "yellow")) { toColor(255, 255, 0); }
					if (strmac(obj.argv1, "orange")) { toColor(255, 125, 0); }
					if (strmac(obj.argv1, "skyblue")) { toColor(0x00, 0xe1, 0xff); }
					if (strmac(obj.argv1, "lightgreen")) { toColor(0x85, 0xee, 0x45); }
					if (strmac(obj.argv1, "purple")) { toColor(0x87, 0x45, 0xee); }
					if (strmac(obj.argv1, "pink")) { toColor(0xee, 0x45, 0xc0); }
					if (strmac(obj.argv1, "gray")) { toColor(0xa0, 0xaf, 0xce); }
				}
				if (strmac(obj.name, "SetColor")) {
					setcolor(RGB(color.red, color.green, color.blue));
				}
				if (strmac(obj.name, "SetBkColor")) {
					setbkcolor(RGB(color.red,color.green,color.blue));
				}
				if (strmac(obj.name, "SetTextColor")) {
					settextcolor(RGB(color.red, color.green, color.blue));
				}
				if (strmac(obj.name, "SetLineColor")) {
					setlinecolor(RGB(color.red, color.green, color.blue));
				}
				if (strmac(obj.name, "SetFillColor")) {
					setfillcolor(RGB(color.red, color.green, color.blue));
				}
				if (strmac(obj.name, "SetTextStyle")) {
					settextstyle(text.height,text.width, text.face, text.angle, text.eachAngle, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
				}
				if (strmac(obj.name, "SetTextSize")) {
					text.width = Number(obj.argv1);
					text.height = Number(obj.argv2);
				}
				if (strmac(obj.name, "SetTextFont")) {
					strcopy(text.face,obj.argv1);
				}
				if (strmac(obj.name, "SetTextAngle")) {
					text.angle = Number(obj.argv1);
					text.eachAngle = Number(obj.argv2);
				}
				if (strmac(obj.name, "Square")) {
					solidrectangle(rect.lx,rect.ly,rect.bx,rect.by);
				}
				if (strmac(obj.name, "Circle")) {
					circle(location.x, location.y, Number(obj.argv1));
				}
				if (strmac(obj.name, "rect")) {
					rect.lx = Number(obj.argv1);
					rect.ly = Number(obj.argv2);
					rect.bx= Number(obj.argv3);
					rect.by= Number(obj.argv4);
				}
				if (strmac(obj.name, "GoTo")) {
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					location.x = obj.v1;
					location.y = obj.v2;
				}
				if (strmac(obj.name, "MoveBy")) {
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					location.x += obj.v1;
					location.y += obj.v2;
				}
				if (strmac(obj.name, "LoadImage")) {
					strcopy(img.url,obj.argv1);
					img.w = Number(obj.argv2);
					img.h = Number(obj.argv3);
				}
				if (strmac(obj.name, "LoadOriginalImage")) {
					strcopy(img.url, obj.argv1);
					IMAGE *i=new IMAGE;
					loadimage(i,img.url);
					img.w = i->getwidth();
					img.h = i->getheight();
					delete i;
				}
				if (strmac(obj.name, "LoadTransImage")) {
					strcopy(foreimg.url, obj.argv1);
					strcopy(maskimg.url,obj.argv2);
					obj.v1 = Number(obj.argv3);
					obj.v2 = Number(obj.argv4);
					foreimg.w = obj.v1;
					maskimg.w = obj.v1;
					foreimg.h = obj.v2;
					maskimg.h = obj.v2;
				}
				if (strmac(obj.name, "LoadOriginalTransImage")) {
					strcopy(foreimg.url,obj.argv1);
					strcopy(maskimg.url, obj.argv2);
					IMAGE* i = new IMAGE;
					loadimage(i,foreimg.url);
					obj.v1 =i->getwidth();
					obj.v2 = i->getheight();
					foreimg.w = obj.v1;
					maskimg.w = obj.v1;
					foreimg.h = obj.v2;
					maskimg.h = obj.v2;
					delete i;
				}
				if (strmac(obj.name, "LoadText")) {
					temp[0] = '\0';
					if (obj.argv1[0] != '\0') { strlink(temp,obj.argv1); }
					if (obj.argv2[0] != '\0') { strlinkc(temp," "); strlink(temp, obj.argv2); }
					if (obj.argv3[0] != '\0') { strlinkc(temp, " "); strlink(temp, obj.argv3); }
					if (obj.argv4[0] != '\0') { strlinkc(temp, " "); strlink(temp, obj.argv4); }
					
					for (int i = 0; i < 254; i++) {
						if (temp[i] == '\0') { break; }
						if (temp[i] == '\\' && temp[i + 1] == 'b') {
							temp[i] = ' '; temp[i + 1] = ' ';
						}
					}
					strcopy(text.string, temp);
					x= textwidth(temp);
					text.length = x;
					text.width = 3; text.height = 15;//
				}
				if (strmac(obj.name, "Line")) {
					line(rect.lx,rect.ly,rect.bx,rect.by);
				}
				if (strmac(obj.name, "PX")) {
					putpixel(location.x,location.y, RGB(color.red, color.green, color.blue));
				}
				if (strmac(obj.name, "Image")) {
					IMAGE* i = new IMAGE;
					loadimage(i,img.url,img.w,img.h,1);
					putimage(location.x,location.y,i);
					delete i;
				}
				if (strmac(obj.name, "ImageTrans")) {
					IMAGE* i = new IMAGE;
					IMAGE* j = new IMAGE;
					loadimage(i, foreimg.url, foreimg.w, foreimg.h, 1);
					loadimage(j,maskimg.url,maskimg.w,maskimg.h,1);
					putimage(location.x, location.y, j, SRCAND); 
					putimage(location.x, location.y,i, SRCPAINT);
					delete i;
					delete j;
				}
				if (strmac(obj.name, "Text")) {
					outtextxy(location.x,location.y,text.string);
				}
				if (strmac(obj.name, "PutImage")) {
					IMAGE* i = new IMAGE;
					loadimage(i, img.url, img.w, img.h, 1);
					putimage(Number(obj.argv1), Number(obj.argv2), i);
					delete i;
				}
				if (strmac(obj.name, "PutImageByRect")) {
					IMAGE* i = new IMAGE;
					loadimage(i, img.url, rect.bx-rect.lx,rect.by-rect.ly, 1);
					putimage(rect.lx,rect.ly, i);
					delete i;
				}
				if (strmac(obj.name, "PutTransImage")) {
					IMAGE* i = new IMAGE;
					IMAGE* j = new IMAGE;
					obj.v1 = Number(obj.argv1);
					obj.v2 = Number(obj.argv2);
					loadimage(i, foreimg.url, foreimg.w, foreimg.h, 1);
					loadimage(j, maskimg.url, maskimg.w, maskimg.h, 1);
					putimage(obj.v1,obj.v2, j, SRCAND);
					putimage(obj.v1,obj.v2, i, SRCPAINT);
					delete i;
					delete j;
				}
				if (strmac(obj.name, "PutTransImageByRect")) {
					IMAGE* i = new IMAGE;
					IMAGE* j = new IMAGE;
					loadimage(i, foreimg.url, rect.bx-rect.lx, rect.by-rect.ly, 1);
					loadimage(j, maskimg.url, rect.bx - rect.lx, rect.by - rect.ly, 1);
					putimage(rect.lx, rect.ly, j, SRCAND);
					putimage(rect.lx, rect.ly, i, SRCPAINT);
					delete i;
					delete j;
				}
				if (strmac(obj.name, "PutText")) {
					outtextxy(Number(obj.argv1),Number(obj.argv2),text.string);
				}
				if (strmac(obj.name, "PutTextByRect")) {
					int i = 0;
					x = rect.bx - rect.lx;//container width
					temp[0] = '\0';
					if (text.length > x) {
						y = x / text.width;//allowed char nums of each line
						type = length(text.string) / y;//total number of lines
						for (i=0; i < type; i++) {
							strmove(temp, (text.string+i*y), y);
							outtextxy(rect.lx,rect.ly + i * text.height,temp);
						}
						if (length(text.string) % y) {
							strmove(temp, (text.string + i * y),length(text.string) % y);
							outtextxy(rect.lx, rect.ly + i* text.height, temp);
						}
					}
					else { outtextxy(rect.lx,rect.ly,text.string); }
					//for(int i=0;i<length)
				}
				if (strmac(obj.name, "SetLineColor")) {
					setlinecolor(RGB(color.red, color.green, color.blue));
				}
				if (strmac(obj.name, "SetLineWidth")) {
					setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, Number(obj.argv1));
				}
				if (strmac(obj.name, "SaveImage")) {
					time_t n;
					n = time(&n);
					temp[0] = '\0';
					strlinkc(String(n, temp), ".jpg");
					saveimage(temp);
				}
				if (strmac(obj.name, "SaveAs")) {
					temp[0] = '\0';
					if (obj.argv1[0] != '\0') { strlink(temp, obj.argv1); }
					if (obj.argv2[0] != '\0') { strlinkc(temp, " "); strlink(temp, obj.argv2); }
					if (obj.argv3[0] != '\0') { strlinkc(temp, " "); strlink(temp, obj.argv3); }
					if (obj.argv4[0] != '\0') { strlinkc(temp, " "); strlink(temp, obj.argv4); }
					saveimage(temp);
				}
				if (strmac(obj.name, "Title")) {
					//hwnd = GetHWnd();
					temp[0] = '\0';
					if (obj.argv1[0] != '\0') { strlink(temp, obj.argv1); }
					if (obj.argv2[0] != '\0') { strlinkc(temp, " "); strlink(temp, obj.argv2); }
					if (obj.argv3[0] != '\0') { strlinkc(temp, " "); strlink(temp, obj.argv3); }
					if (obj.argv4[0] != '\0') { strlinkc(temp, " "); strlink(temp, obj.argv4); }
					SetWindowText(hwnd,temp);
				}
				if (strmac(obj.name, "MoveWindow")) {
					box.x=Number(obj.argv1), box.y=Number(obj.argv2);
					MoveWindow(hwnd,box.x,box.y,box.w,box.h,0);
				}
				if (strmac(obj.name, "ResizeWindow")) {
					time_t n;
					n = time(&n);
					temp[0] = '\0';
					strlinkc(String(n, temp), ".png");
					saveimage(temp);
					closegraph();
					box.w = Number(obj.argv1), box.h=Number(obj.argv2);
					hwnd=initgraph(box.w, box.h);
					IMAGE* i = new IMAGE;
					loadimage(i,temp,box.w,box.h,1);
					putimage(0,0,i);
					delete i;
				}
				if (strmac(obj.name, "alert")) {
					temp[0] = '\0';
					if (obj.argv1[0] != '\0') { strlink(temp, obj.argv1); }
					if (obj.argv2[0] != '\0') { strlinkc(temp, " "); strlink(temp, obj.argv2); }
					if (obj.argv3[0] != '\0') { strlinkc(temp, " "); strlink(temp, obj.argv3); }
					if (obj.argv4[0] != '\0') { strlinkc(temp, " "); strlink(temp, obj.argv4); }
					for (int i = 0; i < 254; i++) {
						if (temp[i] == '\0') { break; }
						if (temp[i] == '\\' && temp[i + 1] == 'n') {
							temp[i] = ' '; temp[i + 1] = '\n';
						}
					}
					MessageBox(hwnd,temp,"CmdCanvas:", MB_OK | MB_ICONINFORMATION);
				}
				if (strmac(obj.name, "sleep")) {
					Sleep(Number(obj.argv1));
				}
				if (strmac(obj.name, "Keep")) {
					type=_getch();
				}
			};
		}
	}
	return 0;
}