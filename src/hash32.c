#include <stdio.h>  
#include <windows.h>
#define MAX_PATH_LENGTH 1024
int length(char c[]) {
	int len = 0;
	for (int i = 0;i<25585; i++) {
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
void hash32(uint8_t *data, int length, uint32_t *hash_output) { 
uint32_t hash = 0x00000000; 
uint32_t b = 378551;
uint32_t a = 63689;
for (int i = 0; i < length; ++i) { hash =hash*a+ data[i]; a*=b;}
//hash *= 0x85ebca6b; // 乘以一个质数常量 
hash&=0x7FFFFFFF;
*hash_output = hash; 
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
int HashFile32(char* file,uint32_t *hashp) {
	FILE* sourcefile;
	int binsize=0;
	int fi=0;
	char *temp=0;
	
	if ((sourcefile=fopen(file, "rb"))==0)
	{
		printf("打开目标文件失败！\n");return 1;
	}
	binsize=getBinSize(file);
	if(!binsize){
	printf("Null file.\n");return 2;
	}
	temp=(char *)malloc(binsize);
	if(!temp){
	printf("ROM Space is Not enough.\n");return 3;
	}
	fread(temp, sizeof(unsigned char), sizeof(unsigned char)*binsize, sourcefile);
	fclose(sourcefile);
	hash32((uint8_t*)temp, binsize, hashp);
	free(temp);
	return 0;
}
char fullpath[1024]="";
char realfullpath[1024]="";
int result=0;
uint32_t hash=0x00000000;
void listFiles(char * dir)
{
char fullpath[1024]="";
char realfullpath[1024]="";
char dirNew[1024]="";
int result=0;
strlink(fullpath,dir);
strcopy(dirNew,dir);
strlinkc(dirNew,"*.*");
	
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    LARGE_INTEGER size;
	
    hFind = FindFirstFile(dirNew, &findData);
    do
    {
   
 	// 是否是文件夹，并且名称不为"."或".." 
        if ((findData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)&&(!streqa(findData.cFileName, "."))&&(!streqa(findData.cFileName, "..")))
        {
            // 将dirNew设置为搜索到的目录，并进行下一轮搜索 
            strcopy(dirNew, dir);
            //strlinkc(dirNew, "\\");
            strlink(dirNew, findData.cFileName);
            strlinkc(dirNew,"\\");
            listFiles(dirNew);
        }
        else if(streqa(findData.cFileName, ".")||streqa(findData.cFileName, "..")){     }
	else
        {
            size.LowPart = findData.nFileSizeLow;
            size.HighPart = findData.nFileSizeHigh;
           //printf("%s\t%d bytes\n",findData.cFileName,size.QuadPart);
	realfullpath[0]='\0';
	strlink(realfullpath,fullpath);
	strlink(realfullpath,findData.cFileName);
	printf(">%s\n",realfullpath);
	//result=CryptQ(realfullpath);
	HashFile32(realfullpath,&hash);// 打印哈希值（十六进制） 
	printf("Hash:0x%08X\n", hash);
        }
    } while (FindNextFile(hFind, &findData));
	FindClose(hFind);
}

int main(int argc, char* argv[]) { 
	uint32_t hash; // 计算哈希值 
	char rootPath[MAX_PATH_LENGTH] = "";
	int i=0;
	if(argc==1){
	strlink(rootPath,argv[0]);
	i=length(rootPath);
			for(;i>=0;i--){
				if(rootPath[i]=='\\'){
				rootPath[i+1]='\0';rootPath[i]='\\';
				break;
				}
			}
	printf("Default Work Floder: %s\n",rootPath);
	listFiles(rootPath); 
	}
	if(argc==2){
	strlink(rootPath,argv[1]);
	if(rootPath[length(rootPath)-1]!='\\'){strlinkc(rootPath,"\\");}
	printf("Target WorkFloder: %s\n",rootPath);
	listFiles(rootPath);
	}
return 0;
 }