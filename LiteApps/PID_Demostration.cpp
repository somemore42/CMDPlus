#include<stdio.h>
#include<graphics.h>
int objvalue = 0;
int targetvalue = 25000;
int dt = 1;
int KP = 2;//决定稳态建立的快慢，KP越大，稳态建立的越早
int KI = 30;//决定稳态的波动大小，KI越大，波动越小:7
int KD = 30;//决定建立稳态时峰值的大小，KD越大，峰值小:30
int delta = 0;
int lastdelta = 0;
int integral = 0;
int derivative = 0;
int output = 0;
int input = 0;
int t = 0;
int test[40] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-18,-19,0};
int set[10] = { 15000,40000,15000,5000,45000,10000,45000,15000,40000,35000 };
int i = 0;
int main() {
	initgraph(800, 650);
	while (1) {
		//let the real world add affection to the objvalue;
		//input = (-targetvalue) / t;
		input = test[t%40]*10;
		objvalue += input;
		//if (objvalue >= 50000) { objvalue = 0; }
		//draw
		putpixel(t%800,500-( (objvalue/100)),GREEN);
		putpixel(t%800,500-targetvalue/100,YELLOW);
		if (t % 800 == 0) { cleardevice(); }
		//let the controller do its job
		delta = (objvalue - targetvalue)/100;
		//integral = integral + (delta * dt);
		integral += (delta * dt);
		derivative = (((delta)-(lastdelta))) / dt;
		output = (KP * delta) + (KI * integral) + (KD * derivative);
		lastdelta = delta;
		Sleep(dt);
		//let the obj sum the input and output
		//objvalue += output;
		objvalue -=output;
		t++;
		if (t > 800) { t = 0; i++; if (i == 10) { i = 0; }; targetvalue = set[i]; }
	}
	return 0;
}