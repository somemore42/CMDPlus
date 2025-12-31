#include<stdio.h>
#include<windows.h>
#include<tchar.h>
void c(char *c){
 HMODULE h=LoadLibrary(c);
if(!h){printf("This dll unable to laod!");}
else{printf("This dll Exist and Laodable!");}
FreeLibrary(h);
}
/*void b(char *cmd){
STARTUPINFO si = {sizeof(si)} ;
PROCESS_INFORMATION pi ;
TCHAR szCommandLine[] =TEXT(cmd);
CreateProcess(NULL,szCommandLine,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi) ;
}*/
/*void _tmainA( int argc, TCHAR *argv[] )
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    if( argc != 2 )
    {
        printf("Usage: %s [cmdline]\n", argv[0]);
        return;
    }

    // Start the child process. 
    if( !CreateProcess( NULL,   // No module name (use command line)
        argv[1],        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        return;
    }

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}*/
int main( int argc, TCHAR *argv[] ){
char dll[255]={0};
if(argc==1){
scanf("%s",dll);
c(dll);
}
else{
printf("%s: ",argv[1]);
c(argv[1]);
}
printf("\n");
//scanf("%s",dll);
//b(dll);
//_tmainA(2,argv[0]);
return 0;
}