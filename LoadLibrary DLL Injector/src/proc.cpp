// LoadLibrary DLL Injector by morganlewiswall.

#include "proc.h"

DWORD GetProcessID(std::string processName)
{
	std::string strBuffer = processName + ".exe"; // Adding .exe to the end of the string.
	const char* nameBuffer = strBuffer.c_str(); // Convering the string to a const char* for _stricmp later.

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // Taking a snapshot of the current processes.

	if (hSnap == INVALID_HANDLE_VALUE)
		return int(INVALID_HANDLE_VALUE);

	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(procEntry);

	DWORD procID = 0;
	if (Process32First(hSnap, &procEntry)) // Takes the first process and stores it in processEntry.
	{
		do
		{
			if (!_stricmp(procEntry.szExeFile, nameBuffer)) // Compares the file name against the file name that we give it in processName. _stricmp compares strings.
			{
				procID = procEntry.th32ProcessID; // Gets the process ID of our process.
				break; // Breaks the loop once we find our process.
			}

		} while (Process32Next(hSnap, &procEntry)); // Loops through the process list and stores it each time in processEntry.
	}

	CloseHandle(hSnap); // Closes the handle to the process snapshot, helps to prevent memory leaks.
	return procID; // Returns the process ID.
}