#include<stdio.h>
#include<time.h>
int C2N(char c) {
	int n = 0;
	if (c >= '0' && c <= '9') {
		n = c - '0';
	}
	else if (c == 'x' || c == 'X') {
		n = 10;
	}
	else {
		n = -1;
	}
	return n;
}

int power(int p) {
	//p %= 17;
	int array[17] = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
	return array[p];
}
char inflect(int p) {
	//p %= 11;
	char mod[11] = {'1','0','X','9','8','7','6','5','4','3','2'};
	return mod[p];
}
int length(char url[]) {
	int i = 0; int l = 0;
	while (url[i] != '\0' && i < 100) {
		l++; i++;
	}
	return l;
}
int nowYear() {
	time_t second;
	int year = 0;
	time(&second);
	year = second / 3600 / 24 / 365 + 1970;
	return year;
}
int isLeap(int yyyy) {
	if (yyyy % 4 == 0 && yyyy % 100 != 0 || yyyy % 4 == 0)
	{
		return 1;
	}
	else {
		return 0;
	}
}
int checkYear(char url[]) {
	int year = 0;
	int p = 6;
	for (int i = 0; i < 4; i++) {
		year *= 10; year += C2N(url[p++]);
	}
	if (year > nowYear()) { return 0; }
	else { return 1; }
}
int checkDate(char url[]) {
	int flag = 1;
	int p = 6;
	int year = 0;
	int month = 0;
	int day = 0;
	for (int i = 0; i < 4; i++) {
		year *= 10; year += C2N(url[p++]);
	}
	month = C2N(url[10]) * 10 + C2N(url[11]);
	day = C2N(url[12]) * 10 + C2N(url[13]);
	if (!(month <= 12 && month >= 1)) {
		return -2;
	}
	if (!(year > 1000)) { return -3; }
	if (!(day >= 1 && day <= 31)) { return -1; }
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30) { return 0; }
	}
	if (month == 2) {
		if (isLeap(year)) {
			if (day > 29) { return 0; }
		}
		else {
			if (day > 28) { return 0; }
		}
	}
	else {
		if (day > 30) { return 0; }
	}
	return flag;
}
int checkPost(char url[]) {
	int h2 = 0;
	h2 = C2N(url[0]) * 10 + C2N(url[1]);
	if (h2 > 0 && h2 < 100) { return 1; }
	else{return 0;}
}
int compare(char url[]) {
	int sum = 0;
	char X = (char)url[17];
	for (int j = 0; j < 17; j++) {
		sum += C2N(url[j]) * power(j);
	}
	sum %= 11;
	if (X== inflect(sum)) {
		return 1;
	}
	else { return 0; }
}
char rightX(char url[]) {
	int sum = 0;
	for (int j = 0; j < 17; j++) {
		sum += C2N(url[j]) * power(j);
	}
	sum %= 11;
	return inflect(sum);
}
int isValid(char url[]) {
	if (length(url) < 18) { return -1; }//too short!
	if (length(url) > 18) { return -7; }//too long!
	if (checkDate(url) == -1) { return -4; }//overflowed days
	if (checkDate(url) == -2) { return -5; }//overflowed months
	if (checkDate(url) == -3) { return -6; }//overflowed years
	if (checkDate(url) == 0) { return -3; }//wrong days!
	if (checkYear(url) == 0) { return -2; }//future year!
	if (compare(url) == 0) { return 0; }//Fake Code!
	else { return 1; }
}
void fill(char url[]) {
	int p = 0;
	for (int i = 0; i < 19; i++) {
		if (url[i] == '\0') { p = i; break; }
		else { p = 19; }
	}
	for (int j = p; j < 18; j++) {
		url[j] = '0';
	}
	url[18] = '\0';
}
void cut(char url[]) {
	url[18] = '\0';
}
void info(char url[]) {
	const char where[34][10] = { "内蒙古","山西","河北","北京","辽宁","吉林","黑龙江","上海","江苏","安徽","山东","天津","浙江","江西","福建","重庆","湖南","湖北","河南","广东","广西","贵州","海南","四川","云南","陕西","甘肃","宁夏","青海","新疆","西藏","香港","澳门","台湾" };
	int age = 0;
	int year = 0;
	int postnum = 0;
	int p = -1;
	for (int i = 0; i < 3; i++) {
		postnum *= 10;
		postnum += C2N(url[i]);
	}
	for (int j = 6; j < 10; j++) {
		year *= 10;
		year += C2N(url[j]);
	}
	age = nowYear() - year;
     if (postnum >= 10) { p++; }
	 if (postnum >= 30) { p++; }
	 if (postnum >= 50) { p++; }
	 if (postnum >= 100) { p++; }
	 if (postnum >= 110) { p++; }
	 if (postnum >= 130) { p++; }
	 if (postnum >= 150) { p++; }
	 if (postnum >= 200) { p++; }
	 if (postnum >= 210) { p++; }
	 if (postnum >= 230) { p++; }
	 if (postnum >= 250) { p++; }
	 if (postnum >= 300) { p++; }
	 if (postnum >= 310) { p++; }
	 if (postnum >= 330) { p++; }
	 if (postnum >= 350) { p++; }
	 if (postnum >= 400) { p++; }
	 if (postnum >= 410) { p++; }
	 if (postnum >= 430) { p++; }
	 if (postnum >= 450) { p++; }
	 if (postnum >= 510) { p++; }
	 if (postnum >= 530) { p++; }
	 if (postnum >= 550) { p++; }
	 if (postnum >= 570) { p++; }
	 if (postnum >= 610) { p++; }
	 if (postnum >= 650) { p++; }
	 if (postnum >= 710) { p++; }
	 if (postnum >= 730) { p++; }
	 if (postnum >= 750) { p++; }
	 if (postnum >= 810) { p++; }
	 if (postnum >= 830) { p++; }
	 if (postnum >= 850) { p++; }
	 if (postnum == 999) { p++; }
	 if(postnum==0) { p = 33; }
	 if (url[16] % 2 == 0) { printf("性别：女 "); }
	 else { printf("性别：男 "); }
	printf("年龄：%d周岁 ",age);
	printf("户籍：%s \n", where[p]);
	
}
int main() {
	char id[19] = "\0";
	char rX = '\0';
	int code = 0;
	printf("中华人民共和国身份证号码校验程序 Copyright 2020-%d MDS, All Rights Reserved.\n仅适用于第二代身份证，户籍结果仅供参考。\n\n", nowYear());
	while (1) {
		printf("输入待检验的身份证号码：>");
		scanf("%s", &id);
		if (id[0] == 'E'&&id[1]=='N'&&id[2]=='D') { break; }
		code = isValid(id);
		if (code==1)
		{
			printf("号码 ");
			printf("%s", id);
			printf("%s\n", " 校验通过");
			info(id);
		}
		
		else if (code == -1) {
			printf("%s", " 校验未通过，长度过短,应当为18位，而样本只有 ");
			printf("%d 位\n用0补全空位后，号码为 ",length(id));
			fill(id);
			printf("%s,", id);
			if (isValid(id) == 1) { printf("%s\n","检验通过"); info(id);}
			else if(isValid(id)==-2){ printf("%s\n", "检验仍不通过，因为年份不能为未来的年份"); }
			else if(isValid(id)==-5) { printf("%s", "检验仍不通过，因为一年中没有"); printf("%c%c月\n", id[10], id[11]);}
			else if (isValid(id) == -3) { printf("%s", "检验仍不通过，因为一个月没有第"); printf("%c%c天\n", id[12], id[13]); }
			else if (isValid(id) == -4) { printf("检验仍不通过，因为%c%c月没有第", id[10], id[11]);  printf("%c%c天\n", id[12], id[13]);}
			else if (isValid(id) == 0) { printf("%s", "检验仍不通过，最后一位应当为 "); rX = rightX(id); printf("%c\n",rX); }
			else { printf("%s\n", "检验仍不通过，"); printf("因为%c%c%c%c年太早了", id[6], id[7], id[8], id[9]); }
		}
		else if (code == -7) {
			printf("%s", "校验未通过，长度过长,应当为18位，而样本却有 ");
			printf("%d 位\n删除多余的数位后位后，号码为 ", length(id));
			cut(id);
			printf("%s,", id);
			if (isValid(id) == 1) { printf("%s\n", "检验通过"); info(id);}
			else if (isValid(id) == -2) { printf("%s\n", "检验仍不通过，因为年份不能为未来的年份"); }
			else if (isValid(id) == -5) { printf("%s", "检验仍不通过，因为一年中没有"); printf("%c%c月\n", id[10], id[11]); }
			else if (isValid(id) == -3) { printf("%s", "检验仍不通过，因为一个月没有第"); printf("%c%c天\n", id[12], id[13]); }
			else if (isValid(id) == -4) { printf("检验仍不通过，因为%c%c月没有第", id[10], id[11]);  printf("%c%c天\n", id[12], id[13]); }
			else if (isValid(id) == 0) { printf("%s", "检验仍不通过，最后一位应当为 "); rX = rightX(id); printf("%c\n", rX); }
			else { printf("%s\n", "检验仍不通过，"); printf("因为%c%c%c%c年太早了", id[6], id[7], id[8], id[9]);}
		}
		else if (code == -2) {
			printf("检验未通过，因为%c%c%c%c年没有到来", id[6], id[7], id[8], id[9]);
		}
		else if (code == -3) {
			printf("检验未通过，因为%c%c%c%c年%c%c月份没有第", id[6], id[7], id[8], id[9],id[10], id[11]); printf("%c%c天\n", id[12], id[13]);
		}
		else if (code == -4) {
			printf("%s", "检验未通过，因为一个月没有第"); printf("%c%c天\n", id[12], id[13]);
		}
		else if (code == -5) {
			printf("%s", "检验未通过，因为一年中没有"); printf("%c%c月\n", id[10], id[11]);
		}
		else if (code == -6) {
			printf("检验未通过，因为%c%c%c%c年太早了\n",id[6],id[7],id[8],id[9]);
		}
		else if (code == 0) {

			rX = rightX(id);
			printf("%s", id);
			printf("%s", "校验未通过，校验码错误，最后一位应当为 ");
			printf("%c\n", rX);
			id[17] = rX;
			id[18] = '\0';
			printf("正确的形式应当为 %s\n", id);
			info(id);
		}
		else { printf("Unknown code,Inner Error!"); break; }
		printf("\n");
	}
	return 0;
}