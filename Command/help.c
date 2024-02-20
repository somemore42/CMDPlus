#include <stdio.h>
char help[255];
int main(){
FILE *fp=fopen("MENU.dat","r");
if(fp==0){printf("Failed to find message file!\n");return 0;}
while(!feof(fp)){
fscanf(fp,"%s",help);
printf("%s\n",help);
if(feof(fp)){break;}
}
printf("以上是列出的部分命令\n");
return 0;
}
