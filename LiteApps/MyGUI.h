#undef UNICODE
#undef _UNICODE
#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<graphics.h>
#include<stdlib.h>
//参数配置
#define MAXBTNS 3
#define MAXTAS 2
#define MAXIMGS 3
#define MAXTIPS 3
void alert(const char* c) { MessageBox(NULL,c,"来自此程序的提示", MB_OK); }
class GUI{
private:
const char *APPNAME;
POINT p;POINT lp;
HWND han = GetForegroundWindow();
HWND father=han;
int appWidth=0;int appHeight=0;
int btnCounter=-1;int delayTime=5;
int taCounter=-1;
int imgCounter=-1;
int tipCounter=-1;
int msX=0;int msY=0;int msLD=0;//内部鼠标数据缓冲区
int fakeint=0;
struct btn{
int x=0;
int y=0;
int w=0;
int h=0;
const char *text;
int isShow=0;//need enlive
int inHover=0;
int hoverDelay=0;
int isWaitHandle=0;
}btnlist[MAXBTNS];
struct textarea{
int x=0;
int y=0;
int w=0;
int h=0;
const char *text;
int isShow=0;
int whichline=0;
int isWaitHandle=0;
}talist[MAXTAS];
struct Image{
int x=0;
int y=0;
int w=0;
int h=0;
const char *url;
int isUse=0;
int isDouble=0;
const char *url2;
IMAGE i;
IMAGE f;
}imglist[MAXIMGS];
struct Tips{
int x=0;
int y=0;
int w=0;
int h=0;
const char *tip;
int isUse=0;
}tiplist[MAXTIPS];
//绘图函数
	void Text(int x, int y, const char c[]) { outtextxy(x, y, _T(c)); }
	void Line(int xs, int xe, int ys, int ye) { line(xs, xe, ys, ye); }
	void Circle(int x, int y, int r) { circle(x, y, r); }
	void Point(int x, int y, COLORREF c) { putpixel(x, y, c); }
	void Square(int xlu, int ylu, int xrd, int yrd) { solidrectangle(xlu, ylu, xrd, yrd); }
	void reset(){setlinestyle(PS_SOLID, 2);setlinecolor(RGB(0, 0, 0));setbkcolor(RGB(255, 255, 255));setcolor(RGB(0, 0, 0));}
	void cleanArea(int x, int y, int w, int h) { clearrectangle(x, y, x + w, y + h); }
	void setFont(int w, int h, COLORREF c, LPCTSTR font, int linesize,int isUnderLine = 0, int isSLine = 0, int isEmphaize = 0) { settextcolor(c); settextstyle(w,h,font,0,0,linesize,isEmphaize,isUnderLine,isSLine); }
	void putImage(IMAGE i,IMAGE f, int x, int y,int w ,int h,int isDoubleImg = 0) {if (isDoubleImg == 0) { putimage(x, y, &i); } else { putimage(x, y, &f, SRCAND); putimage(x, y, &i, SRCPAINT); } }
void pass(){}
protected:
void getWmHn(){
	//HWND han = GetForegroundWindow();
	//HWND han = AfxGetMainWnd();
	int isget = GetCursorPos(&p);
	ScreenToClient(han, &p);}
void setAppTitle(const char *t){APPNAME=t;}
int key(int k) { return( (GetAsyncKeyState(k) & 0x8000) ? 1 : 0); }
int getMsX(){getWmHn();return p.x;}
int getMsY(){getWmHn();return p.y;}
int isInBtn(int bid,int mx,int my){
if(mx>=btnlist[bid].x&&mx<=(btnlist[bid].x+btnlist[bid].w)&&my>=btnlist[bid].y&&my<=(btnlist[bid].y+btnlist[bid].h)){return 1;}
else{return 0;}
}
int isInTextArea(int bid,int mx,int my){
if(mx>=talist[bid].x&&mx<=(talist[bid].x+talist[bid].w)&&my>=talist[bid].y&&my<=(talist[bid].y+talist[bid].h)){return 1;}
else{return 0;}
}
public:
int isMsDn(){
 if(GetForegroundWindow()==father){
  if(key(0x01)){return 1;}else{return 0;}
 }
}
int isMouseMove(){
if(GetForegroundWindow()==father){
getWmHn();
if(p.x!=lp.x||p.y!=lp.y){
fakeint = GetCursorPos(&lp);
ScreenToClient(han, &lp);
return 1;
}
else{return 0;}
}
}
protected:
void regBtn(int x=0,int y=0,int w=75,int h=45,const char *ti=NULL){
btnCounter+=1;
btnlist[btnCounter].isShow=1;
btnlist[btnCounter].x=x;
btnlist[btnCounter].y=y;
btnlist[btnCounter].w=w;
btnlist[btnCounter].h=h;
btnlist[btnCounter].text=ti;
}
void regTextarea(int x=0,int y=0,int w=100,int h=90,const char *innerHTML=NULL){
taCounter+=1;
talist[taCounter].isShow=1;
talist[taCounter].x=x;
talist[taCounter].y=y;
talist[taCounter].w=w;
talist[taCounter].h=h;
talist[taCounter].text=innerHTML;
}
void regImg(int x=0,int y=0,int w=50,int h=50,const char *url=NULL,int isd=0,const char *url2=NULL){
imgCounter+=1;
imglist[imgCounter].isUse=1;
imglist[imgCounter].isDouble=isd;
imglist[imgCounter].x=x;
imglist[imgCounter].y=y;
imglist[imgCounter].w=w;
imglist[imgCounter].h=h;
imglist[imgCounter].url=url;
imglist[imgCounter].url2=url2;
loadimage(&(imglist[imgCounter].i), _T(url),w,h); 
if(isd==1){
loadimage(&(imglist[imgCounter].f), _T(url2),w,h); 
}
}
void regTip(int x=0,int y=0,const char *tip=NULL){
tipCounter+=1;
tiplist[tipCounter].isUse=1;
tiplist[tipCounter].x=x;
tiplist[tipCounter].y=y;
//tiplist[tipCounter].w=w;
//tiplist[tipCounter].h=h;
tiplist[tipCounter].tip=tip;
}
void drawNormalBtn(int bid){//单纯的绘画
		int x, y, w, h,lw=1; 
		x = btnlist[bid].x; y = btnlist[bid].y; w = btnlist[bid].w; h = btnlist[bid].h;
		const char *txt=btnlist[bid].text;
		setcolor(RGB(0, 0, 0));
		setfillcolor(RGB(248, 249, 250));
		setlinestyle(PS_SOLID, lw);
		Square(x, y, x + w, y + h);
		setlinecolor(RGB(245, 246, 244));
		Line(x-lw, y, x + w, y);
		Line(x, y-lw, x, y + h);
		setlinecolor(RGB(0, 0, 0));
		Line(x, y + h, x + w, y + h);
		Line(x + w, y, x + w, y + h);
		setbkcolor(RGB(248, 249, 250));
		setcolor(RGB(51,51,51));
		Text(x +5, y +2, txt);
}
void drawHoverBtn(int bid){//单纯的绘画
		int x, y, w, h,lw=1; 
		x = btnlist[bid].x; y = btnlist[bid].y; w = btnlist[bid].w; h = btnlist[bid].h;
		const char *txt=btnlist[bid].text;
		setcolor(RGB(255, 255, 255));
		setfillcolor(RGB(255, 255, 255));
		setlinestyle(PS_SOLID, 2);
		Square(x, y, x + w, y + h);
		setlinecolor(RGB(108, 117, 125));
		Line(x-lw, y, x + w, y);
		Line(x, y-lw, x, y + h);
		setlinecolor(RGB(246, 246, 244));
		Line(x, y + h, x + w, y + h);
		Line(x + w, y, x + w, y + h);
		setbkcolor(RGB(255, 255, 255));
		setcolor(RGB(0, 0, 0));
		Text(x + 5, y + 2, txt);
reset();
}
void drawTa(int tid){
	int x, y, w, h,lw=2; 
	x = talist[tid].x; y = talist[tid].y; w = talist[tid].w; h = talist[tid].h;
		const char *txt=talist[tid].text;
		setcolor(RGB(0, 0, 0));
		setbkcolor(RGB(255, 255, 255));
		setlinestyle(PS_SOLID, lw);
		Square(x, y, x + w, y + h);
		setlinecolor(RGB(0, 0, 0));
		setfillcolor(RGB(255, 255, 255));
		Line(x-lw, y, x + w, y);
		Line(x, y-lw, x, y + h);
		Line(x, y + h, x + w, y + h);
		Line(x + w, y, x + w, y + h);
		setcolor(RGB(0, 0, 0));
		Text(x +5, y +2, txt);
}
void drawImg(int mid){
	int x, y, w, h; 
	x = imglist[mid].x; y = imglist[mid].y; w = imglist[mid].w; h = imglist[mid].h;
	//const char *url=imglist[mid].url;const char *url2=imglist[mid].url2;
	putImage(imglist[mid].i,imglist[mid].f,x,y,w,h,imglist[mid].isDouble);
}
void drawTip(int mid){
	int x, y;
	x = tiplist[mid].x; y = tiplist[mid].y; //w = tiplist[mid].w; h = tiplist[mid].h;
	const char *tip=tiplist[mid].tip;
	Text(x,y,tip);
}
void delayClick(int bti=0){
int forma=btnlist[bti].hoverDelay;
if(forma<=delayTime&&(btnlist[bti].inHover==1)){forma+=1;btnlist[bti].hoverDelay=forma;}
else{btnlist[bti].hoverDelay=0;btnlist[bti].inHover=0;}//结束按钮变色
}
int inClick(int dti){
if(btnlist[dti].inHover){delayClick(dti);return 1;}else{return 0;}
}
void drawBtn(int bid=0){
if(inClick(bid)){drawHoverBtn(bid);}
else{drawNormalBtn(bid);}
}

void updateAllBtn(){//单纯的画，不处理事件
for(int i=0;i<MAXBTNS;i++){
if(btnlist[i].isShow){drawBtn(i);}else{pass();}
}}
void updateAllTextarea(){
for(int i=0;i<MAXTAS;i++){
if(talist[i].isShow){drawTa(i);}else{pass();}
}
}
void updateData(){
msX=getMsX();msY=getMsY();
if(isMsDn()){msLD=1;}
else{msLD=0;}//单纯的更新鼠标事件，其他函数只能只读，不许更改
}
void updateAllImg(){
for(int i=0;i<MAXIMGS;i++){
if(imglist[i].isUse){drawImg(i);}
}
}
void updateAllTip(){
for(int i=0;i<MAXTIPS;i++){
if(tiplist[i].isUse){drawTip(i);}
}
}
void checkAllBtn(){//仅在鼠标点点击时被调用
for(int i=0;i<MAXBTNS;i++){
if(isInBtn(i,msX,msY)){btnlist[i].isWaitHandle=1;btnlist[i].inHover=1;}
}
}
void checkAllTextarea(){
for(int i=0;i<MAXTAS;i++){
if(isInTextArea(i,msX,msY)){talist[i].isWaitHandle=1;}
}
}
void InStream(){//处理鼠标事件，写入相应结构体
if(msLD){checkAllBtn();checkAllTextarea();}
}
public:
GUI(int w=200,int h=250,const char* title=NULL){
APPNAME=title;appWidth=w;appHeight=h;
initgraph(w, h);setbkcolor(RGB(255, 255, 255));cleardevice();
HWND hd = GetForegroundWindow();han=hd;father=hd;
SetWindowTextA(hd,APPNAME);
BeginBatchDraw();
fakeint = GetCursorPos(&lp);//记录最初的鼠标数据
ScreenToClient(han, &lp);
}//GUI初始化专用
void addBtn(int x=0,int y=0,int w=75,int h=45,const char *btw=NULL){//GUI输入接口
regBtn(x,y,w,h,btw);
}
void addTextarea(int x=0,int y=0,int w=100,int h=90,const char *innerHTML=NULL){
regTextarea(x,y,w,h,innerHTML);
}
void addImg(int x=0,int y=0,int w=50,int h=50,const char *url=NULL,int isd=0,const char *url2=NULL){
regImg(x,y,w,h,url,isd,url2);
}
void addTip(int x=0,int y=0,const char *tip=NULL){
regTip(x,y,tip);
}
void flashTaText(int tid=0,const char*newtext=NULL){
talist[tid].text=newtext;
}
void flashTip(int id=0,const char*nT=NULL){
tiplist[id].tip=nT;
}
void flashBtnText(int id=0,const char*nT=NULL){
btnlist[id].text=nT;
}
void hideBtn(int id=0,int ishow=0){
btnlist[id].isShow=ishow;
}
void resizeBtn(int id=0,int neww=0,int newh=0){
btnlist[id].w=neww;
btnlist[id].h=newh;
}
void locateBtn(int id=0,int newx=0,int newy=0){
btnlist[id].x=newx;
btnlist[id].y=newy;
}
int isHoverBtn(int bid=0){
return isInBtn(bid,msX,msY);
}
void moveImg(int id=0,int xadd=0,int yadd=0){
imglist[id].x+=xadd;
imglist[id].y+=yadd;
}
void locateImg(int id=0,int newx=0,int newy=0){
imglist[id].x=newx;
imglist[id].y=newy;
}
void reloadImg(int id=0,const char*url=NULL,const char*url2=NULL){
loadimage(&(imglist[id].i), _T(url),imglist[id].w,imglist[id].h); 
if(imglist[id].isDouble){
loadimage(&(imglist[id].f), _T(url2),imglist[id].w,imglist[id].h); 
}
}
void resizeImg(int id=0,int neww=0,int newh=0){
imglist[id].w=neww;
imglist[id].h=newh;
loadimage(&(imglist[id].i), imglist[id].url,neww,newh); 
if(imglist[id].isDouble){
loadimage(&(imglist[id].f), imglist[id].url2,neww,newh); 
}
}
void update(){//一定要使用的函数

updateData();//与用户有关的输入
InStream();//与输入有关的判断
updateAllImg();//刷新画面
updateAllTip();
updateAllBtn();//刷新画面
updateAllTextarea();//刷新画面
FlushBatchDraw();
}
int queryBtn(int bid=0){//GUI输出接口
if(btnlist[bid].isWaitHandle==1){btnlist[bid].isWaitHandle=0;return 1;}else{return 0;}//bug 0099：不要先return！
}
int queryTextarea(int tid=0){
if(talist[tid].isWaitHandle==1){talist[tid].isWaitHandle=0;return 1;}else{return 0;}
}
};