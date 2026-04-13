#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <tlhelp32.h>

#include "resource.h"

// CALL
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        MessageBoxA(NULL, "Noellum Client Injected!", "Success", MB_OK | MB_ICONINFORMATION);
        break;
    }
    return TRUE;
}





// DLL Injection
DWORD GetProcId(const char* procName) {
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry)) {
            do {
                if (!_stricmp(procEntry.szExeFile, procName)) {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

// PROCESS PATH
int main() {
    const char* targetProcess = "PixelWorlds.exe"; // Sesuaikan nama proses game-nya
    char tempPath[MAX_PATH];
    GetTempPathA(MAX_PATH, tempPath);
    std::string dllPath = std::string(tempPath) + "NoellumClient.dll";

    // --- STEP 1: Ekstrak DLL dari Resource ke Folder Temp ---
    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_DLL1), "DLL");
    HGLOBAL hData = LoadResource(NULL, hRes);
    void* pDllData = LockResource(hData);
    DWORD dllSize = SizeofResource(NULL, hRes);

    std::ofstream outFile(dllPath, std::ios::binary);
    outFile.write((char*)pDllData, dllSize);
    outFile.close();

    std::cout << "Targeting: " << targetProcess << std::endl;

    // PROCESS + INJECT
    DWORD procId = 0;
    while (!procId) {
        procId = GetProcId(targetProcess);
        Sleep(1000); // Tunggu game dibuka
    }

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);
    if (hProc && hProc != INVALID_HANDLE_VALUE) {
        void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        WriteProcessMemory(hProc, loc, dllPath.c_str(), dllPath.size() + 1, 0);
        HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

        if (hThread) {
            std::cout << "Noellum Client Injected Successfully!" << std::endl;
            CloseHandle(hThread);
        }
    }

    if (hProc) CloseHandle(hProc);
    return 0;
}