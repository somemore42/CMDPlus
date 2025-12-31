#include <stdio.h>
int index=0;
float L0_N1;float L0_N2;float L0_R;char L0_OP;
float L1_N1;float L1_N2;float L1_R;char L1_OP;
char isShift;
char direction;//0 same level;1 shift; 2;reback;
char OPERATIONCODE;//0 null ;1 ADD ;2 CUT ;3 POW ;4 MOD
char numTemp[32];
float numValue;
char TEST[128]="0+1+1*7+1=";
char* FileDataForCal=0;
char ifUseFileData=0;int FileDataSize=0;
char getChar(){
char r;
if(!ifUseFileData){
	if(TEST[index]){r=TEST[index];index++;}
	else {index=0;r='=';}
}else{
	if(index<FileDataSize){r=FileDataForCal[index];index++;}
	else {index=0;r='=';}
}
return r;
}
int getBinSize(char* path)
{
	int  size = 0;
	FILE* file;
	errno_t err = fopen_s(&file, path, "rb");
	if (!err)
	{
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fclose(file);
	}
	return size;
}

int C2N(char c){
if (c >= '0' && c <= '9')
return c - '0';
if (c >= 'a' && c <= 'z')
return c - 'a' + 10;
if (c >= 'A' && c <= 'Z')
return c - 'A' + 10;
return 0;
}
float Number_Int(char c[]) {
	//printf("$%s\n",c);
	float n = 0;
	int i = 0;
	int sign=1;
	if(c[0]=='-'){sign=-1;}
	while (c[i] != 0) {
		n *= 10;
		n += C2N(c[i]);
		i++;
	}
	return n*sign;
}
float Number(char* st) {
    float result = 0.0f;
    float frac = 0.0f;
    float scale = 0.1f;
    int sign = 1;
    int i = 0;
    int hasDigit = 0;        // 是否遇到过有效数字
    int afterDecimal = 0;    // 是否已经开始处理小数部分（用于判断是否是第一个小数点）
    
    // 处理空指针
    if (st == 0) return 0.0f;

    // 跳过前导空白（可选，根据需要）
    while (st[i] == ' ' || st[i] == '\t') i++;

    // 处理符号
    if (st[i] == '-') {
        sign = -1;
        i++;
    } else if (st[i] == '+') {
        i++;
    }

    // 主循环
    while (st[i] != '\0') {
        char c = st[i];

        if (c!='.') {
           // int digit = c - '0';
	int digit=C2N(c);
            if (!afterDecimal) {
                // 整数部分
                result = result * 10.0f + (float)digit;
            } else {
                // 小数部分
                frac = frac + ((float)digit) * scale;
                scale *= 0.1f;
            }
            hasDigit = 1;
        }
        else{// if (c == '.') 
            // 遇到小数点：重置小数部分
            afterDecimal = 1;
            frac = 0.0f;      // 清零小数部分
            scale = 0.1f;     // 重置缩放因子
        }
//        else {
            // 遇到非数字、非小数点字符，停止解析（或可跳过）
//            break;
//        }
        i++;
    }

    // 没有有效数字则返回 0
    if (!hasDigit) return 0.0f;

    return sign * (result + frac);
}
void istrcopy(char* target, char* origin) {
	int i = 0;
	for (i = 0; origin[i] != 0; i++) {
		target[i] = origin[i];
	}
	target[i] = '\0';
	index=0;
}
void strlinkchar(char *p,char c){
	int e = 0;
	while (1) {
	if(p[e]=='\0'){break;}
		e++;
	}
	p[e] = c;
	p[e+1] = '\0';
}
void compute(){
	if(isShift){
		if(L0_OP=='*'){L0_R=(L0_N1*L0_N2);}
		if(L0_OP=='%'){L0_R=(L0_N1/L0_N2);}
	}
	else{
		if(L1_OP=='+'){L1_R=(L1_N1+L1_N2);}
		if(L1_OP=='-'){L1_R=(L1_N1-L1_N2);}
	}
//printf(">%c %.2f %.2f %.2f | %c %.2f %.2f %.2f\n",L0_OP,L0_N1,L0_N2,L0_R,L1_OP,L1_N1,L1_N2,L1_R);
}

void pushNum(){
	numValue=Number(numTemp);
	numTemp[0]='\0';
}


float Calculator(){
L0_N1=0,L0_N2=0,L0_R=0;L0_OP='*';
L1_N1=0,L1_N2=0,L1_R=0;L1_OP='+';
direction=0;isShift=0;OPERATIONCODE='+';
numTemp[0]='\0';
char input;
char keep=1;
	while(keep){
		input=getChar();//printf("%c",input);
	if(input=='+'||input=='-'){
		pushNum();//printf("[%c]",input);
		if(isShift){/*printf("@Y\n");*/L0_N2=numValue;compute();L1_N2=L0_R;isShift=0;L1_N1=L1_R;/*!!*/compute();L1_N1=L1_R;L1_OP=input;}
		else{/*printf("@N\n");*/L1_N2=numValue;compute();L1_N1=L1_R;L1_OP=input;}
	}
	else if(input=='*'||input=='%'){
		pushNum();//printf("[%c]",input);
		if(isShift){/*printf("@Y\n");*/L0_N2=numValue;compute();L0_N1=L0_R;L0_OP=input;}
		else{/*printf("@N\n");*/L0_N1=numValue;isShift=1;L0_OP=input;}
	}
	else if(input=='='){
		pushNum();//printf("[=]");
		if(isShift){L0_N2=numValue;compute();L1_N2=L0_R;isShift=0;compute();}
		else{L1_N1=L1_R;L1_N2=numValue;compute();}
		keep=0;
	}
	else{//printf("[?]");
		strlinkchar(numTemp,input); 
	}
	}
  return L1_R;
}
int main(int argc, char* argv[], char* envp[]){
/*printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"1+2=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"1*2=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"1-2=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"100%2=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"1*2+1+2+3=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"1+2+3+1*2=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"2=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"+2=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"%6=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"1*2*3*4=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"1+2+3+4=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"1-2-3-4=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"12%6+1-3+6*2=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"1-12%6+2*3-2*9=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"1-2+3*4%2-5+1=");printf("\n%s %d\n",TEST,Calculator());
istrcopy(TEST,"123+234*345%3*2*3%2-456%2-567=");printf("\n%s %d\n",TEST,Calculator());
*/
if(argc==1){
printf("#>");
scanf("%s",TEST);
printf("%.2f\n",Calculator());
}
if(argc==2){
istrcopy(TEST,argv[1]);
printf("%.2f\n",Calculator());
}
if(argc==3){
	FILE* script;int ScriptLength;
	if ((script=fopen(argv[2], "rb"))==0)
	{
		printf("Failed to open script file!\n");return 1;
	}
	ScriptLength=getBinSize(argv[2]);
	if(!ScriptLength){
	printf("Null file.\n");return 2;
	}
	FileDataForCal=(char *)malloc(ScriptLength);
	if(!FileDataForCal){
	printf("Run Memory Space is Not enough.\n");return 3;
	}
	fread(FileDataForCal, sizeof(unsigned char), sizeof(unsigned char)*ScriptLength, script);
	fclose(script);
ifUseFileData=1;FileDataSize=ScriptLength;
printf("Results=%.2f\n",Calculator());
}
return 0;
}