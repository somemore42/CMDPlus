#undef UNICODE
#undef _UNICODE
#include"MyGUI.h"
#include<time.h>
const int width = 330;
const int height = 200;
const int bw = 70;
const int bh = 25;
time_t t;

void escape(int &x,int &y) {
	int nx, ny;
	while (1) {
	nx = rand() % width - bw; //x = nx;
		if (nx != x&&nx>0) { x = nx; break; }
		else { continue; }
	}
	while (1) {
	ny = rand() % height - bh;// y = ny;
		if (ny != x && ny > 0) { y = ny; break; }
		else { continue; }
	}
}
int main() {
	int code = 0;
	int flag =1;
	int newx = 210;
	int newy = 150;
	GUI app(width, height, "辞职信");
	t=time(&t);
	srand(t);
	code = rand();
	app.addImg(0, 0, width, height, "blank.bmp");
	app.addImg(10, 30, 100, 100, "gaoci.jpg");
	app.addTip(120, 70, "老板，我走了。");
	app.addTip(120,90,"这一走就是一辈子！");
	app.addBtn(30, 150, bw, bh, "    同意");
	app.addBtn(newx, newy,bw, bh, "    拒绝");
	app.update();
	app.update();
	while (flag) {
		while (app.isMsDn()||app.isMouseMove()|| app.isHoverBtn(1)) {
			if (app.queryBtn(0)) {
				alert("谢谢老板，再见！");
				flag = 0;
			}
			if (app.isHoverBtn(1)) {
				escape(newx, newy);
				app.locateBtn(1, newx, newy);
			}
			app.update();
		}
		Sleep(50);
			
		//app.update();
		
		
		//else{Sleep(50);}
	}
	return code;
}