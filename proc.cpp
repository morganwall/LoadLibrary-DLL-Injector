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