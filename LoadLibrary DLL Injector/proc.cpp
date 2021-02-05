// LoadLibrary DLL Injector by morganlewiswall.

#include "proc.h"

DWORD GetProcessID(const char* processName)
{
	DWORD processID = 0; // Using DWORD as process IDs are DWORDS. Setting it to 0 to avoid errors.
	HANDLE handleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // Takes a snapshot of the current processes.
	if (handleSnap != INVALID_HANDLE_VALUE) // CreateToolhelp32Snapshot returns INVALID_HANDLE_VALUE if it fails.
	{
		PROCESSENTRY32 processEntry;
		processEntry.dwSize = sizeof(processEntry); // MSDN says that we need to set the size for it to work correctly.

		if (Process32First(handleSnap, &processEntry)) // Takes the first process and stores it in processEntry.
		{
			do
			{
				if (!_stricmp(processEntry.szExeFile, processName)) // Compares the file name against the file name that we give it in processName. _stricmp compares strings.
				{
					processID = processEntry.th32ProcessID; // Gets the process ID of our process.
					break; // Breaks the loop once we find our process.
				}

			} while (Process32Next(handleSnap, &processEntry)); // Loops through the process list and stores it each time in processEntry.
		}
	}
	CloseHandle(handleSnap); // Closes the handle to the process snapshot, helps to prevent memory leaks.
	return processID; // Returns the process ID.
}

uintptr_t GetModuleBaseAddress(DWORD processID, const char* moduleName) // uintptr_t will compile to both x64 and x86. Same as the previous function but for modules.
{
	uintptr_t moduleBaseAddress = 0;
	HANDLE handleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID); // We use the or so we can get both 64 and 32 bit modules.
	if (handleSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32First(handleSnap, &moduleEntry))
		{
			do
			{
				if (!_stricmp(moduleEntry.szModule, moduleName))
				{
					moduleBaseAddress = (uintptr_t)moduleEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(handleSnap, &moduleEntry));
		}
	}
	CloseHandle(handleSnap);
	return moduleBaseAddress;
}