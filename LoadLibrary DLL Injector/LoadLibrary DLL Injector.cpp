// LoadLibrary DLL Injector by morganlewiswall.

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

#include "proc.h"

std::string getexepath()
{
    char result[MAX_PATH];
    return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
}

int main()
{
    std::string exePath = getexepath(), userInput, dllNameStart = "/", dllName;
    DWORD processID = 0;

#ifdef _WIN32
    dllNameStart = "\\";
#endif

    std::string exePathNoFileName = exePath.substr(0, exePath.find_last_of("\\/")); // Credits: https://stackoverflow.com/questions/10364877/c-how-to-remove-filename-from-path-string Removes the exe name from the path string.

    std::cout << "LoadLibrary Injector by morganlewiswall\n\n";
    std::cout << "Please make sure that your DLL is in the same path as the EXE (" << exePathNoFileName << ").\n\n";

    std::cout << "DLL Name: ";
    std::cin >> dllName;

    std::string fullPath = exePathNoFileName + dllNameStart + dllName + ".dll"; // Adds all the strings together.

    const char* dllPath = fullPath.c_str(); // Converts the new full path string to a const char.

    std::cout << "Process Name: ";
    std::cin >> userInput;

    std::string fullProcessName = userInput + ".exe";

    const char* processName = fullProcessName.c_str(); // Same as before.

    while (!processID) // Loop while we don't have the process ID.
    {
        processID = GetProcessID(processName); // Search for the process ID using the given name, in the snapshot.
        Sleep(30);
    }

    HANDLE handleProc = OpenProcess(PROCESS_ALL_ACCESS, 0, processID); // Open a handle to the process with all access rights.

    if (handleProc && handleProc != INVALID_HANDLE_VALUE)
    {
        void* location = VirtualAllocEx(handleProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        if (location)
        {
            WriteProcessMemory(handleProc, location, dllPath, strlen(dllPath) + 1, 0);
        }

        HANDLE handleThread = CreateRemoteThread(handleProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, location, 0, 0); // Creates a thread and loads out dll into the game memory.

        if (handleThread) // Closing handles.
        {
            CloseHandle(handleThread);
        }

        if (handleProc)
        {
            CloseHandle(handleProc);
        }
    }

    return 0;
}