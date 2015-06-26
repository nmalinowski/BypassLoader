#include "stdafx.h"
#include

int _tmain(int argc, _TCHAR* argv[])
{

    #define ADDRESS (LPVOID)0x447E2A

    unsigned char buffer[1024] = { 0 };
    SIZE_T nSize;
    int fooo = 0;

    PROCESS_INFORMATION procInfo = { 0 };

    STARTUPINFO startupInfo = { 0 };
    startupInfo.cb = sizeof(startupInfo);

    fooo = CreateProcess(L"FILENAME.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &procInfo);

    printf("%d\n", fooo);

    while (1)
    {
        //00A89010 E4 A6 42 00
        ReadProcessMemory(procInfo.hProcess, (LPVOID)0x00A89010, buffer, 12, &nSize);
        if ((buffer[0] == 0xE4) && (buffer[1] == 0xA6))
        {
            printf("Unpacked.\n");
            ReadProcessMemory(procInfo.hProcess, ADDRESS, buffer, 12, &nSize);
            if ((buffer[0] == 0xE8) && (buffer[1] == 0x79))
            {
                buffer[0] = 0x90;
                buffer[1] = 0x90;
                buffer[2] = 0x90;
                buffer[3] = 0x90;
                buffer[4] = 0x90;
                printf("Address FOUND!\n");
                WriteProcessMemory(procInfo.hProcess, ADDRESS, buffer, 12, &nSize);
                exit(1);
            }
        }
    }


    return 0;
}
