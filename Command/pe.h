#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <Windows.h>
#include <time.h>


HANDLE m_hFile = NULL;                    // �ļ����
HANDLE m_hMap = NULL;                    // �ļ�ӳ����
LPVOID m_lpBase = NULL;                    // ӳ���ַ
DWORD m_dwLen = 0;                        // �ļ����ݴ�С
IMAGE_DOS_HEADER* m_pDosHeader = NULL;    // Dosͷ
IMAGE_NT_HEADERS* m_pNtHeaders = NULL;    // NTͷ
IMAGE_SECTION_HEADER* m_pSecHeader = NULL;

/*
    ��ȡPE�����ļ�
    fileUrl:�ļ�·��
    lpSaveData:�������ݵ�ָ��
    �ɹ��������ݴ�С,ʧ�ܷ���0.
*/
DWORD ReadPeFile(char* fileUrl, LPVOID lpSaveData);

VOID DestroryFunc(void);