#pragma once
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

DWORD GetProcessID(const char* processName);

uintptr_t GetModuleBaseAddress(DWORD processID, const char* moduleName);

uintptr_t FindDMAAddy(HANDLE handleProcess, uintptr_t pointer, std::vector<unsigned int> offsets);