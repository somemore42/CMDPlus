#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<time.h>
void strlink(char *p,char *str) {
	int i = 0; int e = 0;
	while (1) {
	if(p[e]=='\0'){break;}
		e++;
	}
	while (1) {
	if(str[i]=='\0'){break;}
		p[e + i] = str[i];
		i++;
	}
	p[e + i ] = '\0';
}
void strlinkc(char *p,const char *str) {
	int i = 0; int e = 0;
	while (1) {
	if(p[e]=='\0'){break;}
		e++;
	}
	while (1) {
	if(str[i]=='\0'){break;}
		p[e + i] = str[i];
		i++;
	}
	p[e + i ] = '\0';
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
char* String(int num, char* str, int radix) {
    char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; unsigned unum; int i = 0, j, k;
    if (radix == 10 && num < 0) { unum = (unsigned)-num; str[i++] = '-'; }
    else unum = (unsigned)num; do { str[i++] = index[unum % (unsigned)radix]; unum /= radix; } while (unum);
    str[i] = '\0'; if (str[0] == '-') k = 1; else k = 0; char temp;
    for (j = k; j <= (i - 1) / 2; j++) { temp = str[j]; str[j] = str[i - 1 + k - j]; str[i - 1 + k - j] = temp; }return str;
}
unsigned char *base64_en(unsigned char *str,int strlen,unsigned char *res,int *reslen)  
{  
    long len;  
    long str_len;  
    int i,j;  
//定义base64编码表  
    unsigned char *base64_table="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  
//计算经过base64编码后的字符串长度  
    str_len=strlen;
    if(str_len % 3 == 0)  
        len=str_len/3*4;  
    else  
        len=(str_len/3+1)*4;  
  *reslen=len;
   // res=malloc(sizeof(unsigned char)*len+1);  
    res[len]='\0';  
  
//以3个8位字符为一组进行编码  
    for(i=0,j=0;i<len-2;j+=3,i+=4)  
    {  
        res[i]=base64_table[str[j]>>2]; //取出第一个字符的前6位并找出对应的结果字符  
        res[i+1]=base64_table[(str[j]&0x3)<<4 | (str[j+1]>>4)]; //将第一个字符的后位与第二个字符的前4位进行组合并找到对应的结果字符  
        res[i+2]=base64_table[(str[j+1]&0xf)<<2 | (str[j+2]>>6)]; //将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符  
        res[i+3]=base64_table[str[j+2]&0x3f]; //取出第三个字符的后6位并找出结果字符  
    }  
  
    switch(str_len % 3)  
    {  
        case 1:  
            res[i-2]='=';  
            res[i-1]='=';  
            break;  
        case 2:  
            res[i-1]='=';  
            break;  
    }
    return res;
}
int main(int argc, char* argv[]){
	FILE* sourcefile;
	FILE* resultfile;
	char byte[2]="";
	char *s64=0;
	char outf[255] = "";
	char inf[255]="";
	char inherit[2048]="";
	unsigned char *temp=0;
	int lenBin=0;
	int x=0;//accept return value of system()
    if (argc == 1) {
        printf("[COMMAND] toBase64 [sourceFilePath] [outputFilePath]\n");
	return 1;
    }
    else if(argc==2){
    strlink(inf,argv[1]);
    time_t n;
    n=time(&n);
    strlinkc(String(n, outf,10), ".base64");
}else if(argc==3){
	strlink(inf,argv[1]);
	strlink(outf,argv[2]);
}else{printf("No more than 2 parameters!\n");return 2;}
	if ((sourcefile=fopen(inf, "rb"))==0)
	{
		printf("打开目标文件失败！\n");return -1;
	}
	if ((resultfile=fopen(outf, "w+"))==0)
	{
		printf("写入目标文件失败！\n");return -2;
	}
	lenBin=getBinSize(inf);
	if(!lenBin){
	printf("目标文件为空！\n");return -3;
	}
	if((temp=malloc(lenBin+1))==0){
	printf("申请大小为%d的内存空间失败！\n",lenBin);return -4;
	}
	//int baseLen=(int)((double)lenBin*((double)4/(double)3))+44;
	int baseLen=0;
	if(lenBin % 3 == 0){ baseLen=lenBin/3*4;  } else {baseLen=(lenBin/3+1)*4; }
	if((s64=malloc(baseLen+1))==0){
	printf("申请大小为%d的内存空间失败！\n",baseLen);return -5;
	}
	fread(temp, sizeof(unsigned char), sizeof(unsigned char)*lenBin, sourcefile);
	s64=base64_en(temp,lenBin,s64,&x);
	fwrite(s64,sizeof(unsigned char),sizeof(unsigned char)*x,resultfile);
fclose(sourcefile);
fclose(resultfile);
free(temp);
free(s64);
return 0;
}