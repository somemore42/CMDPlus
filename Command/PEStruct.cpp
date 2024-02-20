//#include "stdafx.h"
#undef UNICODE
#undef _UNICODE
#include <stdio.h>  
#include <tchar.h>  
#include <Windows.h>
 
extern void DirectoryString(DWORD dwIndex);
 
int main(int argc, char* argv[], char* envp[])
{
	if(argc==1){
		printf("[COMMAND] PEstruct [ExeFilePath]");
	}
	if(argc==2){
	//��ȡ�ļ����
	HANDLE hFile = CreateFile(
		argv[1],
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//��ȡ�ļ���С
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	CHAR *pFileBuf = new CHAR[dwFileSize];
	//���ļ���ȡ���ڴ�
	DWORD ReadSize = 0;
	ReadFile(hFile, pFileBuf, dwFileSize, &ReadSize, NULL);
 
	//�ж��Ƿ�ΪPE�ļ�
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)pFileBuf;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		//����PE
		printf("����PE�ļ�\n");
		//system("pause");
		return 0;
	}
 
	PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)(pFileBuf + pDosHeader->e_lfanew);
	if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
	{
		//����PE�ļ�
		printf("����PE�ļ�\n");
		//system("pause");
		return 0;
	}
 
	//��ȡ����PEͷ��Ϣ
	//��ȡ��Ϣ���õ��������ṹ��ָ��	���������ṹ�嶼����NTͷ��
	PIMAGE_FILE_HEADER		pFileHeader		= &(pNtHeader->FileHeader);
	PIMAGE_OPTIONAL_HEADER	pOptionalHeader	= &(pNtHeader->OptionalHeader);
	//���PEͷ��Ϣ
	printf("================== �� �� P E ͷ �� Ϣ ==================\n\n");
	printf("�� �� ��:\t%08X\t", pOptionalHeader->AddressOfEntryPoint);
	printf("�� ϵ ͳ:\t%04X\n", pOptionalHeader->Subsystem);
	printf("�����ַ:\t%08X\t", pOptionalHeader->ImageBase);
	printf("������Ŀ:\t%04X\n", pFileHeader->NumberOfSections);
	printf("�����С:\t%08X\t", pOptionalHeader->SizeOfImage);
	printf("����ʱ���־:\t%08X\n", pFileHeader->TimeDateStamp);
	printf("�����ַ:\t%08X\t", pOptionalHeader->BaseOfCode);
	printf("���״�С:\t%08X\n", pOptionalHeader->SizeOfHeaders);
	printf("���ݻ�ַ:\t%08X\t", pOptionalHeader->BaseOfData);
	printf("�� �� ֵ:\t%04X\n", pFileHeader->Characteristics);
	printf("�� �� ��:\t%08X\t", pOptionalHeader->SectionAlignment);
	printf("У �� ��:\t%08X\n", pOptionalHeader->CheckSum);
	printf("�ļ������:\t%08X\t", pOptionalHeader->FileAlignment);
	printf("��ѡͷ����С:\t%04X\n", pFileHeader->SizeOfOptionalHeader);
	printf("�� ־ ��:\t%04X\t\t", pOptionalHeader->Magic);
	printf("RVA������С:\t%08X\n\n", pOptionalHeader->NumberOfRvaAndSizes);
 
	printf("======================= Ŀ ¼ �� =======================\n");
	//��ȡĿ¼��ͷָ��
	PIMAGE_DATA_DIRECTORY pDataDirectory = pOptionalHeader->DataDirectory;
	printf("\t\t  RAV\t\t  ��С\n");
	for (DWORD i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
	{
		DirectoryString(i);
		printf("%08X\t%08X\n",
			pDataDirectory[i].VirtualAddress, pDataDirectory[i].Size);
	}
 
	printf("======================= �� �� �� =======================\n");
	//��ȡ���α�ͷָ��
	PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNtHeader);
	printf("����      VOffset   VSize     ROffset   RSize     ��־\n");
	//��ȡ���θ���
	DWORD dwSectionNum = pFileHeader->NumberOfSections;
	//�������θ�������������Ϣ
	for (DWORD i = 0; i < dwSectionNum; i++, pSectionHeader++)
	{
		for (DWORD j = 0; j < IMAGE_SIZEOF_SHORT_NAME; j++)
		{
			printf("%c", pSectionHeader->Name[j]);
		}
		printf("  %08X  %08X  %08X  %08X  %08X\n",
			pSectionHeader->VirtualAddress,
			pSectionHeader->Misc.VirtualSize,
			pSectionHeader->PointerToRawData,
			pSectionHeader->SizeOfRawData,
			pSectionHeader->Characteristics);
	}
	printf("\n");
	}
	//system("pause");
	return 0;
}
 
void DirectoryString(DWORD dwIndex)
{
	switch (dwIndex)
	{
	case 0:printf("�����:\t\t");
		break;
	case 1:printf("�����:\t\t");
		break;
	case 2:printf("��Դ:\t\t");
		break;
	case 3:printf("�쳣:\t\t");
		break;
	case 4:printf("��ȫ:\t\t");
		break;
	case 5:printf("�ض�λ:\t\t");
		break;
	case 6:printf("����:\t\t");
		break;
	case 7:printf("��Ȩ:\t\t");
		break;
	case 8:printf("ȫ��ָ��:\t");
		break;
	case 9:printf("TLS��:\t\t");
		break;
	case 10:printf("��������:\t");
		break;
	case 11:printf("���뷶Χ:\t");
		break;
	case 12:printf("IAT:\t\t");
		break;
	case 13:printf("�ӳ�����:\t");
		break;
	case 14:printf("COM:\t\t");
		break;
	case 15:printf("����:\t\t");
		break;
	}
}
