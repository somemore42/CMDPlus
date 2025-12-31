#include <stdio.h>
FILE*file1_out_b;
void writeInFile(char c){
FILE*_file1_out_b;
if((_file1_out_b=fopen("file1.bin","ab+"))==NULL){
printf("Failed to open object file!\n");
}
int i;
if(fwrite(&c,sizeof(c),1,_file1_out_b)!=1){printf("Error!501...\n");}
fclose(_file1_out_b);
}
void __writeInFile(char c,char f[]){
FILE*_file1_out_b;
if((_file1_out_b=fopen(f,"ab+"))==NULL){
printf("Failed to open object file!\n");
}
int i;
if(fwrite(&c,sizeof(c),1,_file1_out_b)!=1){printf("Error!501...\n");}
fclose(_file1_out_b);
}
void _writeInFile(char c){
int i;
if(fwrite(&c,sizeof(c),1,file1_out_b)!=1){printf("Failed to write in the object file!\n");}
}
char x16(char c[]){
char v=0;
if(c[0]<='9'&&c[0]>='0')
{v=(c[0]-'0')*16;}
else if(c[0]<='F'&&c[0]>='A'){v=((c[0]-'A')+10)*16;}
else{v=((c[0]-'a')+10)*16;}
if(c[1]<='9'&&c[1]>='0')
{v+=c[1]-'0';}
else if(c[1]<='F'&&c[1]>='A'){v+=(c[1]-'A')+10;}
else{v+=(c[1]-'a')+10;}
return v;
}

int main(int argc, char* argv[], char* envp[]){
int i=1;
char hex[3];
char asfilename[100];
char x;
if(argc==1){
printf("\nCOMMAND: HEXWRITE [HEX type text Filename]\nHEXWRITE [Original from Text Filename] [Save as Binary Filename]\n");
return -1;
}
if(argc==2){
FILE *fp=fopen(argv[1],"r");
if(fp==NULL){
printf("Failed to open source file!\n\n");
}
if((file1_out_b=fopen("BinaryFile.bin","ab+"))==NULL){
printf("Failed to open object file!\n\n");
}
while(!feof(fp)){
fscanf(fp,"%s",hex);
if(hex[0]=='\\'){i=0;continue;}
x=x16(hex);
_writeInFile(x);
}
fclose(fp);
fclose(file1_out_b);

}
if(argc==3){
FILE *fp=fopen(argv[1],"r");
if((file1_out_b=fopen(argv[2],"ab+"))==NULL){
printf("Failed to open object file!\n\n");
}
while(!feof(fp)){
fscanf(fp,"%s",hex);
if(hex[0]=='\\'){i=0;continue;}
x=x16(hex);
_writeInFile(x);
}
fclose(fp);
fclose(file1_out_b);
}
if(argc>3){printf("\nCOMMAND: HEXWRITE [HEX type text Filename]\nHEXWRITE [Original from Text Filename] [Save as Binary Filename]\n");return -2;}
//int frame=0;
//char *frames[]={"[      ]","[-     ]","[--    ]","[---   ]","[ ---  ]","[  --- ]","[   ---]","[    --]","[     -]"};
//while(1==1){
//printf("%s%s","\r",frames[frame]);
//frame+=1;
//if(frame==9){frame=0;}
//Sleep(300);
//}
printf("Finished!\n");
return 0;
}