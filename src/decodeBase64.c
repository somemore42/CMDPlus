#include <stdio.h>
#include <stdlib.h>
#include<string.h>
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
 unsigned char *base64_de(unsigned char *code,int codelen,unsigned char *res,int *reslen)  
{  
//根据base64表，以字符找到对应的十进制数据  
    int table[]={0,0,0,0,0,0,0,0,0,0,0,0,
    		 0,0,0,0,0,0,0,0,0,0,0,0,
    		 0,0,0,0,0,0,0,0,0,0,0,0,
    		 0,0,0,0,0,0,0,62,0,0,0,
    		 63,52,53,54,55,56,57,58,
    		 59,60,61,0,0,0,0,0,0,0,0,
    		 1,2,3,4,5,6,7,8,9,10,11,12,
    		 13,14,15,16,17,18,19,20,21,
    		 22,23,24,25,0,0,0,0,0,0,26,
    		 27,28,29,30,31,32,33,34,35,
    		 36,37,38,39,40,41,42,43,44,
    		 45,46,47,48,49,50,51
    	       };  
    long len;  
    long str_len;  
    int i,j;  
  
//计算解码后的字符串长度  
    len=codelen;
//判断编码后的字符串后是否有=  
    if(strstr(code,"=="))  
        str_len=len/4*3-2;  
    else if(strstr(code,"="))  
        str_len=len/4*3-1;  
    else  
        str_len=len/4*3;  
  *reslen=str_len;
    res=malloc(sizeof(unsigned char)*str_len+1);
  //  if(res==0){printf("申请大小为%d的内存空间失败！\n",*reslen);return -6;}
    res[str_len]='\0';
  
//以4个字符为一位进行解码  
    for(i=0,j=0;i < len-2;j+=3,i+=4)  
    {  
        res[j]=((unsigned char)table[code[i]])<<2 | (((unsigned char)table[code[i+1]])>>4); //取出第一个字符对应base64表的十进制数的前6位与第二个字符对应base64表的十进制数的后2位进行组合  
        res[j+1]=(((unsigned char)table[code[i+1]])<<4) | (((unsigned char)table[code[i+2]])>>2); //取出第二个字符对应base64表的十进制数的后4位与第三个字符对应bas464表的十进制数的后4位进行组合  
        res[j+2]=(((unsigned char)table[code[i+2]])<<6) | ((unsigned char)table[code[i+3]]); //取出第三个字符对应base64表的十进制数的后2位与第4个字符进行组合  
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
        printf("[COMMAND] decodeBase64 [sourceFilePath] [outputFilePath]\n");
	return 1;
    }
    else if(argc==2){
    strlink(inf,argv[1]);
    time_t n;
    n=time(&n);
    strlinkc(String(n, outf,10), ".bin");
   }else if(argc==3){
	strlink(inf,argv[1]);
	strlink(outf,argv[2]);
   }else{printf("No more than 2 parameters!\n");return 2;}
	if ((sourcefile=fopen(inf, "r"))==0)
	{
		printf("打开目标文件失败！\n");return -1;
	}
	if ((resultfile=fopen(outf, "wb+"))==0)
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
	fread(temp, sizeof(unsigned char), sizeof(unsigned char)*lenBin, sourcefile);
	s64=base64_de(temp,lenBin,s64,&x);
	fwrite(s64,sizeof(unsigned char),sizeof(unsigned char)*x,resultfile);
fclose(sourcefile);
fclose(resultfile);
free(temp);
free(s64);
return 0;
}