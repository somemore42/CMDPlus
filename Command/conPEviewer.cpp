#undef UNICODE
#undef _UNICODE
#include "PE.h"

DWORD ReadPeFile(char* fileUrl, LPVOID lpSaveData)
{
    m_hFile = CreateFile(fileUrl, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (m_hFile == INVALID_HANDLE_VALUE)
    {
        printf("[ReadPeFile]:Can't open file!\n");
        return 0;
    }
    m_hMap = CreateFileMapping(m_hFile, NULL, PAGE_READWRITE | SEC_IMAGE, 0, 0, 0);
    if (!m_hMap)
    {
        printf("[ReadPeFile]:Can't create filemap!\n");
        return 0;
    }
    m_lpBase = MapViewOfFile(m_hMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    if (!m_lpBase)
    {
        printf("[ReadPeFile]:MapViewOfFile bad!\n");
        return 0;
    }
    m_dwLen = GetFileSize(m_hFile, &m_dwLen);
    m_pDosHeader = (PIMAGE_DOS_HEADER)m_lpBase;
    if (m_pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        printf("[ReadPeFile]:Not is pe file!\n");
        return 0;
    }
    m_pNtHeaders = (PIMAGE_NT_HEADERS)((DWORD)m_lpBase + m_pDosHeader->e_lfanew);
    if (m_pNtHeaders->Signature != IMAGE_NT_SIGNATURE)
    {
        printf("[ReadPeFile]:Not is execut programmer!\n");
        return 0;
    }
    m_pSecHeader = (PIMAGE_SECTION_HEADER)((DWORD) & (m_pNtHeaders->OptionalHeader) + m_pNtHeaders->FileHeader.SizeOfOptionalHeader);
    return m_dwLen;
}

VOID DestroryFunc(void)
{
    CloseHandle(m_hMap);
    CloseHandle(m_hFile);
    UnmapViewOfFile(m_lpBase);
}

LPCSTR _getMachineName(WORD wMachine)
{
    char* name = (char*)malloc(125);

    switch (wMachine)
    {
    case 0:
        lstrcpy(name, "Unknown");
        break;
    case 0x14c:
        lstrcpy(name, "Intel 386");
        break;
    case 0x0162:
        lstrcpy(name, "MIPS little-endian, 0x160 big-endian");
        break;
    case 0x0166:
        lstrcpy(name, "MIPS little-endian");
        break;
    case 0x0168:
        lstrcpy(name, "MIPS little-endian");
        break;
    case 0x0169:
        lstrcpy(name, "MIPS little-endian WCE v2");
        break;
    case 0x0184:
        lstrcpy(name, "Alpha_AXP");
        break;
    case 0x01a2:
        lstrcpy(name, "SH3 little-endian");
        break;
    case 0x01a4:
        lstrcpy(name, "SH3E little-endian");
        break;
    case 0x01a6:
        lstrcpy(name, "SH4 little-endian");
        break;
    case 0x01a8:
        lstrcpy(name, "SH5");
        break;
    case 0x01c0:
        lstrcpy(name, "ARM Little-Endian");
        break;
    case 0x01c2:
        lstrcpy(name, "ARM Thumb/Thumb-2 Little-Endian");
        break;
    case 0x01c4:
        lstrcpy(name, "ARM Thumb-2 Little-Endian");
        break;
    case 0x01F0:
        lstrcpy(name, "IBM PowerPC Little-Endian");
        break;
    case 0x0200:
        lstrcpy(name, "Intel 64");
        break;
    case 0x0266:
        lstrcpy(name, "MIPS");
        break;
    case 0x0284:
        lstrcpy(name, "ALPHA64");
        break;
    case 0x0366:
        lstrcpy(name, "MIPS");
        break;
    case 0x0466:
        lstrcpy(name, "MIPS");
        break;
    case 0x0520:
        lstrcpy(name, "Infineon");
        break;
    case 0x0EBC:
        lstrcpy(name, "EFI Byte Code");
        break;
    case 0x8664:
        lstrcpy(name, "AMD64 (K8)");
        break;
    case 0x9041:
        lstrcpy(name, "M32R little-endian");
        break;
    default:
        free(name);
        return NULL;
        break;
    }
    return name;
}

VOID _printFormat(char* dataName, WORD* dataAddr, int nSize)
{
    printf("\t%s:", dataName);
    for (int i = 0; i < (int)(13 - strlen(dataName)); i++)
    {
        printf(" ");
    }
    printf("0x");
    for (int i = 0; i < nSize; i++)
    {
        printf("%04X", dataAddr[i]);
    }
    printf("\n");
}
VOID _printFormat(const char* dataName, WORD* dataAddr, int nSize)
{
    printf("\t%s:", dataName);
    for (int i = 0; i < (int)(13 - strlen(dataName)); i++)
    {
        printf(" ");
    }
    printf("0x");
    for (int i = 0; i < nSize; i++)
    {
        printf("%04X", dataAddr[i]);
    }
    printf("\n");
}
VOID test_PrintPeInfo(void)
{
    char infoTmp[50] = { 0 };

    printf("->DOS Header\n");
    _printFormat("e_magic", &m_pDosHeader->e_magic, 1);
    _printFormat("e_cblp", &m_pDosHeader->e_cblp, 1);
    _printFormat("e_cp", &m_pDosHeader->e_cp, 1);
    _printFormat("e_crlc", &m_pDosHeader->e_crlc, 1);
    _printFormat("e_cparhdr", &m_pDosHeader->e_cparhdr, 1);
    _printFormat("e_minalloc", &m_pDosHeader->e_minalloc, 1);
    _printFormat("e_maxalloc", &m_pDosHeader->e_maxalloc, 1);
    _printFormat("e_ss", &m_pDosHeader->e_ss, 1);
    _printFormat("e_sp", &m_pDosHeader->e_sp, 1);
    _printFormat("e_csum", &m_pDosHeader->e_csum, 1);
    _printFormat("e_ip", &m_pDosHeader->e_ip, 1);
    _printFormat("e_cs", &m_pDosHeader->e_cs, 1);
    _printFormat("e_lfarlc", &m_pDosHeader->e_lfarlc, 1);
    _printFormat("e_ovno", &m_pDosHeader->e_ovno, 1);
    _printFormat("e_res", m_pDosHeader->e_res, 4);
    _printFormat("e_oeminfo", &m_pDosHeader->e_oemid, 1);
    _printFormat("e_oeminfo", &m_pDosHeader->e_oeminfo, 1);
    _printFormat("e_res2", m_pDosHeader->e_res2, 10);
    printf("\te_lfanew:     0x%08X\n\n", m_pDosHeader->e_lfanew);

    printf("->File Header\n");
    printf("\tMachine:              0x%04X  (%s)\n", m_pNtHeaders->FileHeader.Machine, _getMachineName(m_pNtHeaders->FileHeader.Machine));
    printf("\tNumberOfSections:     0x%04X\n", m_pNtHeaders->FileHeader.NumberOfSections);
    struct tm Tm = { 0 };
    gmtime_s(&Tm, (time_t*)&(m_pNtHeaders->FileHeader.TimeDateStamp));
   printf("\tTimeDateStamp:        0x%04X  (%d/%d/%d %d:%d:%d)\n", m_pNtHeaders->FileHeader.TimeDateStamp, Tm.tm_year + 1900, Tm.tm_mon + 1, Tm.tm_mday, Tm.tm_hour, Tm.tm_min, Tm.tm_sec);
    printf("\tPointerToSymbolTable: 0x%04X\n", m_pNtHeaders->FileHeader.PointerToSymbolTable);
    printf("\tNumberOfSymbols:      0x%04X\n", m_pNtHeaders->FileHeader.NumberOfSymbols);
    printf("\tSizeOfOptionalHeader: 0x%04X\n", m_pNtHeaders->FileHeader.SizeOfOptionalHeader);
    printf("\tCharacteristics:      0x%04X\n\n", m_pNtHeaders->FileHeader.Characteristics);

    printf("->Optional Header\n");
    printf("\tMagic:                       0x%04X", m_pNtHeaders->OptionalHeader.Magic);
    switch (m_pNtHeaders->OptionalHeader.Magic)
    {
    case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
        printf("  (HDR32_MAGIC)\n");
        break;
    case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
        printf("  (HDR64_MAGIC)\n");
        break;
    case IMAGE_ROM_OPTIONAL_HDR_MAGIC:
        printf("  (ROM_MAGIC)\n");
        break;
    default:
        printf("  (Unknown)\n");
        break;
    }
    printf("\tMajorLinkerVersion:          0x%02X\n", m_pNtHeaders->OptionalHeader.MajorLinkerVersion);
    printf("\tMinorLinkerVersion:          0x%02X  -> %d.%02d\n", m_pNtHeaders->OptionalHeader.MinorLinkerVersion, m_pNtHeaders->OptionalHeader.MajorLinkerVersion, m_pNtHeaders->OptionalHeader.MinorLinkerVersion);
    printf("\tSizeOfCode:                  0x%08X\n", m_pNtHeaders->OptionalHeader.SizeOfCode);
    printf("\tSizeOfInitializedData:       0x%08X\n", m_pNtHeaders->OptionalHeader.SizeOfInitializedData);
    printf("\tSizeOfUninitializedData:     0x%08X\n", m_pNtHeaders->OptionalHeader.SizeOfUninitializedData);
    printf("\tAddressOfEntryPoint:         0x%08X\n", m_pNtHeaders->OptionalHeader.AddressOfEntryPoint);
    printf("\tBaseOfCode:                  0x%08X\n", m_pNtHeaders->OptionalHeader.BaseOfCode);
    printf("\tBaseOfData:                  0x%08X\n", m_pNtHeaders->OptionalHeader.BaseOfData);
    printf("\tImageBase:                   0x%08X\n", m_pNtHeaders->OptionalHeader.ImageBase);
    printf("\tSectionAlignment:            0x%08X\n", m_pNtHeaders->OptionalHeader.SectionAlignment);
    printf("\tFileAlignment:               0x%08X\n", m_pNtHeaders->OptionalHeader.FileAlignment);
    printf("\tMajorOperatingSystemVersion: 0x%08X\n", m_pNtHeaders->OptionalHeader.MajorOperatingSystemVersion);
    printf("\tMinorOperatingSystemVersion: 0x%08X  -> %d.%02d\n", m_pNtHeaders->OptionalHeader.MinorOperatingSystemVersion, m_pNtHeaders->OptionalHeader.MajorOperatingSystemVersion, m_pNtHeaders->OptionalHeader.MinorOperatingSystemVersion);
    printf("\tMajorImageVersion:           0x%08X\n", m_pNtHeaders->OptionalHeader.MajorImageVersion);
    printf("\tMinorImageVersion:           0x%08X  -> %d.%02d\n", m_pNtHeaders->OptionalHeader.MinorImageVersion, m_pNtHeaders->OptionalHeader.MajorImageVersion, m_pNtHeaders->OptionalHeader.MinorImageVersion);
    printf("\tMajorSubsystemVersion:       0x%08X\n", m_pNtHeaders->OptionalHeader.MajorSubsystemVersion);
    printf("\tMinorSubsystemVersion:       0x%08X  -> %d.%02d\n", m_pNtHeaders->OptionalHeader.MinorSubsystemVersion, m_pNtHeaders->OptionalHeader.MajorSubsystemVersion, m_pNtHeaders->OptionalHeader.MinorSubsystemVersion);
    printf("\tWin32VersionValue:           0x%08X\n", m_pNtHeaders->OptionalHeader.Win32VersionValue);
    printf("\tSizeOfImage:                 0x%08X\n", m_pNtHeaders->OptionalHeader.SizeOfImage);
    printf("\tSizeOfHeaders:               0x%08X\n", m_pNtHeaders->OptionalHeader.SizeOfHeaders);
    printf("\tCheckSum:                    0x%08X\n", m_pNtHeaders->OptionalHeader.CheckSum);
    printf("\tSubsystem:                   0x%04X", m_pNtHeaders->OptionalHeader.Subsystem);
    
    switch (m_pNtHeaders->OptionalHeader.Subsystem)
    {
    case IMAGE_SUBSYSTEM_UNKNOWN:
        printf("  (Unknown)\n");
        break;
    case IMAGE_SUBSYSTEM_NATIVE:
        printf("  (Driver And SysPro)\n");
        break;
    case IMAGE_SUBSYSTEM_WINDOWS_GUI:
        printf("  (Windows_GUI)\n");
        break;
    case IMAGE_SUBSYSTEM_WINDOWS_CUI:
        printf("  (Windows_CUI)\n");
        break;
    case IMAGE_SUBSYSTEM_OS2_CUI:
        printf("  (OS/2_CUI)\n");
        break;
    case IMAGE_SUBSYSTEM_POSIX_CUI:
        printf("  (POSIX_CUI)\n");
        break;
    case IMAGE_SUBSYSTEM_WINDOWS_CE_GUI:
        printf("  (WinCE_GUI)\n");
        break;
    case IMAGE_SUBSYSTEM_EFI_APPLICATION:
        printf("  (EFI)\n");
        break;
    case IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER:
        printf("  (EFI_Driver)\n");
        break;
    case IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER:
        printf("  (EFI_Dirver Run-Time)\n");
        break;
    case IMAGE_SUBSYSTEM_EFI_ROM:
        printf("  (EFI_ROM)\n");
        break;
    case IMAGE_SUBSYSTEM_XBOX:
        printf("  (XBox)\n");
        break;
    case IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION:
        printf("  (Boot Application)\n");
        break;
    default:
        printf("  (Unknown!)");
        break;
    }
    printf("\tDllCharacteristics:          0x%04X\n", m_pNtHeaders->OptionalHeader.DllCharacteristics);
    printf("\tSizeOfStackReserve:          0x%08X\n", m_pNtHeaders->OptionalHeader.SizeOfStackReserve);
    printf("\tSizeOfStackCommit:           0x%08X\n", m_pNtHeaders->OptionalHeader.SizeOfStackCommit);
    printf("\tSizeOfHeapReserve:           0x%08X\n", m_pNtHeaders->OptionalHeader.SizeOfHeapReserve);
    printf("\tLoaderFlags:                 0x%08X\n", m_pNtHeaders->OptionalHeader.LoaderFlags);
    printf("\tNumberOfRvaAndSizes:         0x%08X\n\n", m_pNtHeaders->OptionalHeader.NumberOfRvaAndSizes);
    
    printf("\tDataDirectory(16)            RVA        Size\n");
    printf("\t-----------------            ---------- ----------\n");
    for (DWORD dwI = 0; dwI < m_pNtHeaders->OptionalHeader.NumberOfRvaAndSizes; dwI++)
    {
        switch (dwI)
        {
        case 0:
            printf("\t%-29s", "ExportTable");
            break;
        case 1:
            printf("\t%-29s", "ImportTable");
            break;
        case 2:
            printf("\t%-29s", "Resource");
            break;
        case 3:
            printf("\t%-29s", "Exception");
            break;
        case 4:
            printf("\t%-29s", "Security");
            break;
        case 5:
            printf("\t%-29s", "Relocation");
            break;
        case 6:
            printf("\t%-29s", "Debug");
            break;
        case 7:
            printf("\t%-29s", "Copyright");
            break;
        case 8:
            printf("\t%-29s", "GlobalPtr");
            break;
        case 9:
            printf("\t%-29s", "TLSTable");
            break;
        case 10:
            printf("\t%-29s", "LoadConfig");
            break;
        case 11:
            printf("\t%-29s", "BoundImport");
            break;
        case 12:
            printf("\t%-29s", "IAT");
            break;
        case 13:
            printf("\t%-29s", "DelayImport");
            break;
        case 14:
            printf("\t%-29s", "COM");
            break;
        case 15:
            printf("\t%-29s", "Reserved");
            break;
        default:
            printf("\t%-29s", "Unknown");
            break;
        }
        printf("0x%08X 0x%08X", m_pNtHeaders->OptionalHeader.DataDirectory[dwI].VirtualAddress, m_pNtHeaders->OptionalHeader.DataDirectory[dwI].Size);
        for (WORD wI = 0; wI < m_pNtHeaders->FileHeader.NumberOfSections; wI++)
        {
            // 如果该数据目录的起始地址>某节起始地址 && 该数据目录的结束地址<某节结束地址,那么就说明该数据目录存在此节中.
            if ((m_pSecHeader[wI].VirtualAddress <= m_pNtHeaders->OptionalHeader.DataDirectory[dwI].VirtualAddress) && ((m_pSecHeader[wI].VirtualAddress + m_pSecHeader[wI].Misc.VirtualSize) >= (m_pNtHeaders->OptionalHeader.DataDirectory[dwI].VirtualAddress + m_pNtHeaders->OptionalHeader.DataDirectory[dwI].Size)))
            {
                printf("  (\"%s\")", m_pSecHeader[wI].Name);
                break;
            }
        }
        printf("\n");
    }
    
    return;
}
LPVOID lpData = NULL;
int main(int argc, char* argv[], char* envp[])
{
    if (argc == 1) {
        //char url[255] = "C:\\Program Files\\Intel\\WiFi\\bin\\cpappletexe.exe";
        //printf("0");
		printf("[COMMAND] PEstruct [ExeFilePath]");
        //ReadPeFile(argv[0], lpData);
        //printf("1");
       // test_PrintPeInfo();
        //printf("2");
        //DestroryFunc();
        //scanf("");
    }
    if (argc == 2) {

        //printf("Hello Pe!\n");
        ReadPeFile(argv[1], lpData);
        test_PrintPeInfo();
        DestroryFunc();
    }
    system("pause");
    return 0;
}