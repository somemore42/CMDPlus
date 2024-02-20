#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <Windows.h>
#include <time.h>


HANDLE m_hFile = NULL;                    // 文件句柄
HANDLE m_hMap = NULL;                    // 文件映射句柄
LPVOID m_lpBase = NULL;                    // 映射基址
DWORD m_dwLen = 0;                        // 文件数据大小
IMAGE_DOS_HEADER* m_pDosHeader = NULL;    // Dos头
IMAGE_NT_HEADERS* m_pNtHeaders = NULL;    // NT头
IMAGE_SECTION_HEADER* m_pSecHeader = NULL;

/*
    读取PE磁盘文件
    fileUrl:文件路径
    lpSaveData:保存数据的指针
    成功返回数据大小,失败返回0.
*/
DWORD ReadPeFile(char* fileUrl, LPVOID lpSaveData);

VOID DestroryFunc(void);