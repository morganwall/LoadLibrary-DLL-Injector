// LoadLibrary DLL Injector by morganlewiswall.

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

#include "proc.h"

int main()
{
    // Get Local Path.
    char pathBuffer[MAX_PATH];
    GetModuleFileName(NULL, pathBuffer, sizeof(pathBuffer)); // GetModuleFileName returns the length of the path as a DWORD, and the path string to the buffer provided.
    std::string localPath = pathBuffer; // Swapping to using std::string.
    localPath = localPath.substr(0, localPath.find_last_of("\\/")); // Removing the exe name from the path by finding the last / and removing it and everything after it.

    // Get DLL name and the target's name from the user.
    std::cout << "LoadLibrary Injector by morganlewiswall\n";
    std::cout << "Please ensure your DLL and the injector are in the same folder.\n\n";

    std::cout << "DLL Name: ";
    std::string dllName;
    std::cin >> dllName;

    std::cout << "Target Process: ";
    std::string targetName;
    std::cin >> targetName;

    // Get Process ID.
    DWORD procID = GetProcessID(targetName);
    std::cout << "\nProcess Found! (ID: " << procID << ")\n";

    // Get Process Handle.
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procID);
    if (!hProc)
    {
        std::cout << "Failed to get a handle to the process!\n";
        return 1;
    }

    void* baseAddressBuffer = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!baseAddressBuffer)
    {
        std::cout << "Failed VirtualAlloc!\n";
        return 2;
    }

    std::string seperatorBuffer = "/";
#ifdef _WIN32
    seperatorBuffer = "\\";
#endif

    std::string dllPath = localPath + seperatorBuffer + dllName + ".dll";

    // Inject DLL.
    WriteProcessMemory(hProc, baseAddressBuffer, dllPath.c_str(), dllPath.length() + 1, 0);
    HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, baseAddressBuffer, 0, 0); // Creates a thread and loads our dll into the game memory.

    // Clean up.
    if (hThread)
        CloseHandle(hThread);
    if (hProc)
        CloseHandle(hProc);

    return 0;
}