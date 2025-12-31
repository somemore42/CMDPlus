#include<stdio.h>
#include<windows.h>
#include"commonFunction.h"
#include"data.h"
#include"PrivateFunction.h"
#include"PrivateCmdFunction.h"
int loadSettings(){
 HANDLE iniFile;
 char defaultSettings[1024]="[SHOW]\nforeColor=15\nbackColor=0\n[VIEW]\nlastFile=";
 strlink(defaultSettings,DBstate.filePath);
 strlinkc(defaultSettings,"\n;\n");
  // printf("%s\n",defaultSettings);
 iniFile=CreateFile(
  (LPSTR)"PsdAccess.ini",
  GENERIC_READ,
  0,
  NULL,
  OPEN_EXISTING,
  FILE_ATTRIBUTE_NORMAL,
  NULL
 );
 if( iniFile==INVALID_HANDLE_VALUE){
  error=GetLastError();
  printf("Settings File Not Found,use default Settings...\n");
  CUIsettings.foreColor=15;// 0ºÚ 1°µÀ¶ 2°µÂÌ 3°µÌìÀ¶ 4°µºì 5°µ×Ï 6°µ»Æ 7°µ°× 8»Ò 9À¶ 10ÂÌ 11ÌìÀ¶ 12ºì 13×Ï 14»Æ 15°×
  CUIsettings.backColor=0;
  setCUI();
   iniFile=CreateFile(
  (LPSTR)"PsdAccess.ini",
  GENERIC_READ|GENERIC_WRITE,
  0,
  NULL,
  CREATE_ALWAYS,
  FILE_ATTRIBUTE_NORMAL,
  NULL
 );
   if( iniFile==INVALID_HANDLE_VALUE){
    error=GetLastError();
    printf("Settings File Failed to Build...\n");
   }
   else{
   DWORD bytesWritten;
   BOOL r;
   r=WriteFile(
    iniFile,
    defaultSettings,
    1024,
    &bytesWritten,
    NULL
    );
 
    if(!r){error=GetLastError();printf("Settings File Failed to Write...\n");}
    else{if(!CloseHandle(iniFile)){error=GetLastError();printf("Settings File Failed to Close...\n");};}
   }
 }
 else{
  char temp[1024];
  DWORD bytesRead;
  if(!ReadFile(iniFile,temp,sizeof(temp),&bytesRead,NULL)){error=GetLastError();printf("Settings File Failed to Read...\n");}
  else{
        praseIni(temp); 
        setCUI();
        if(!CloseHandle(iniFile)){error=GetLastError();printf("Settings File Failed to Close...\n");}
        }
  }
}
void prepare(){
if(length(CUIsettings.lastFilePath)<1){
printf("Select a DB for Open>");
scanf("%s",DBstate.filePath);
printf("%s\n",DBstate.filePath);
 char defaultSettings[1024]="[SHOW]\nforeColor=15\nbackColor=0\n[VIEW]\nlastFile=";
 strlink(defaultSettings,DBstate.filePath);
 strlinkc(defaultSettings,"\n;\n");
 //  printf("%s\n",defaultSettings);
HANDLE   iniFile=CreateFile(
  (LPSTR)"PsdAccess.ini",
  GENERIC_READ|GENERIC_WRITE,
  0,
  NULL,
  CREATE_ALWAYS,
  FILE_ATTRIBUTE_NORMAL,
  NULL
 );
   if( iniFile==INVALID_HANDLE_VALUE){
    error=GetLastError();
    printf("Settings File Failed to Build...\n");
   }
   else{
   DWORD bytesWritten;
   BOOL r;
   r=WriteFile(
    iniFile,
    defaultSettings,
    length(defaultSettings),
    &bytesWritten,
    NULL
    );
 
    if(!r){error=GetLastError();printf("Settings File Failed to Write...\n");}
    else{if(!CloseHandle(iniFile)){error=GetLastError();printf("Settings File Failed to Close...\n");};}
   }
}
else{strcopy(DBstate.filePath,CUIsettings.lastFilePath);}
}
void ShowData(){
/* HANDLE DBFile;
 char* path;
 path=DBstate.filePath;
 DBFile=CreateFileA(
 (LPSTR)path,
  GENERIC_READ,
  0,
  NULL,
  OPEN_EXISTING,
  FILE_ATTRIBUTE_NORMAL,
  NULL
 );
 if( DBFile==INVALID_HANDLE_VALUE){
  error=GetLastError();
  printf("DB File Not Found...\n");
 }  
 else{
  DWORD bytesRead;
  if(!ReadFile(DBFile,&DBheader,sizeof(DBheader),&bytesRead,NULL)){error=GetLastError();printf("DB File Failed to Read...\n");}
  else{
   //...
*/
   printf("DB name:%s Total Section:%d All Pages:%d\nSECTION:%s\t|%s\t|%s\t|%s\t|%s\t|%s\t|%s\t|%s\n",DBheader.DBTitle, DBstate.activedSections,DBstate.usedPages   ,DBheader.RowTitle_1,DBheader.RowTitle_2,DBheader.RowTitle_3,DBheader.RowTitle_4,DBheader.RowTitle_5,DBheader.RowTitle_6,DBheader.RowTitle_7,DBheader.RowTitle_8);
  
  for(int i=0;i<DBstate.usedPages;i++){
  printf("%d:",i);
  for(int j=0;j<DBstate.activedSections;j++){
        printf("%s\t",(DBsection[i].Section_1+MAXSECTIONLENGTH*j));
        }
  printf("\n");
 }
 /*  
   if(!CloseHandle(DBFile)){error=GetLastError();printf("DB File Failed to Close...\n");}
   }
 }
*/
}
void CreatDB(){
char hold=1;
char o[4];
DBheader.enabledSections=0;
printf("DB Name>");
scanf("%s",DBheader.DBTitle);
while(hold){
printf("Futher Action:a,d,r,f,s>");
scanf("%s",o);
switch(o[0]){
case 'a':
scanf("%s",(DBheader.RowTitle_1+MAXROWTITLELENGTH*DBheader.enabledSections));
DBheader.enabledSections++;
break;
case 'd':
DBheader.enabledSections--;
break;
case 'r':
scanf("%s",DBheader.RowTitle_1+MAXROWTITLELENGTH*(DBheader.enabledSections-1));
break;
case 'f':
scanf("%s",DBstate.filePath);
break;
case 's':
DBheader.magicNumber=MAGICMUNBER;
DBheader.usedPages=0;
writeNewDB();
hold=0;
break;
}
}

}
int main(int argc, char* argv[]){
//printf("%d\n",sizeof(DBheader)+sizeof(DBsection));
int KEEP=1;
char cmd[4];
handle=GetStdHandle(STD_OUTPUT_HANDLE);


if(argc>1){
if(argc>16){printf("Too many argvs!\n");return 1;}
Extern_argc=argc;
for(int p=0;p<argc;p++){
Extern_argv[p]=argv[p];
}
goto CMDMODE;
}


loadSettings();
prepare();
while(KEEP){

//SetConsoleCursorPosition(hsh,cusor);
DrawMenu();
scanf("%s",cmd);
switch(cmd[0]){
case  'C':case  'c':
 CreatDB();
 break;
case 'V':case  'v':
 verifyDBFile();
 ShowData();
break;
case  'O':case  'o':
 printf("Select the DB you want to Open>");
 scanf("%s",DBstate.filePath);
 verifyDBFile();
 ShowData();
 break;
case  'U':case  'u':
 verifyDBFile();
 UpdatePages();
 break;
case  'A':case  'a':
  verifyDBFile();
  addNewPages();
 break;
case  'D':case  'd':
  verifyDBFile();
 deletePages();
 break;
case  'Q':case  'q':
  verifyDBFile();
 queryPages();
 break;
case  'F':case  'f':
 verifyDBFile();
 findPartInDB();
 break;
case  'X':case  'x':
 verifyDBFile();
 FindPartAllInDB();
 break;
case  'B':case  'b':
 verifyDBFile();
 FindPartBySectionInDB();
 break;
case  'E':case  'e':
KEEP=0;
 break;
}
}
return 0;
CMDMODE:
if(argc>=3){
strcopy(DBstate.filePath,argv[1]);
}else{
printf("%d argvs,too less!\n",argc);
return 1;
}

if(strmac(argv[2],"UPDATE")){return cmd_UpdatePages();}
if(strmac(argv[2],"QUERY")){return cmd_QueryPages();}
if(strmac(argv[2],"ADD")){return cmd_AddNewPages();}
if(strmac(argv[2],"DELETE")){return cmd_DeletePages();}
if(strmac(argv[2],"BROWSE")){return cmd_BrowseDB();}
if(strmac(argv[2],"CREATE")){return cmd_CreateNewDB();}
if(strmac(argv[2],"FIND")){return cmd_FindPartInDB();}
if(strmac(argv[2],"FINDALL")){return cmd_FindPartAllInDB();}
if(strmac(argv[2],"FINDAT")){return cmd_FindPartBySectionInDB();}

return 0;
}