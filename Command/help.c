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
printf("�������г��Ĳ�������\n");
return 0;
}
