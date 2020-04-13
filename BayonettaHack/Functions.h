#pragma once
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <tchar.h>
#include <TlHelp32.h>
using namespace std;

//Test webhook

void* allocMem(HANDLE p, BYTE cheat[]) //Allocate memory for codecave
{

	void* AllocMem = VirtualAllocEx(p, NULL, sizeof(cheat)+0x5 + 1, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	return AllocMem;
}

void* calJmp(void* d, DWORD d2, int x, size_t cheatSize) //Calculate the address for jmp instruction
{
	
	if (x == 0) // Jmp address for return
	{

		DWORD voidToDword = reinterpret_cast<DWORD>(d);

		DWORD calc = (d2 + cheatSize) - voidToDword - 0x5;


		void *returnToVoid = reinterpret_cast<void*>(calc);
		return returnToVoid;

	}
	
	if (x == 1) // Jmp address for allocated memory
	{

		DWORD voidToDword = reinterpret_cast<DWORD>(d);

		DWORD calc = voidToDword - d2 - 0x5;

		void *returnToVoid = reinterpret_cast<void*>(calc);
		return returnToVoid;

	}
	
}

uintptr_t getBaseAddress(DWORD procId, const wchar_t* modName) //Get baseaddres of something
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

DWORD FindPattern(DWORD dwBegin, DWORD dwEnd, BYTE *arrayBytes, CHAR mask[]) {
	UINT r = NULL;
	INT sizeMask = strlen(mask) - 1;
	for (DWORD i = dwBegin; i < (dwBegin + dwEnd); i++) {
		if (*(BYTE*)i == arrayBytes[r] || mask[r] == '?') {
			if (mask[r + 1] == '\0')
				return(i - sizeMask);
			r++;
		}
		else
			r = NULL;
	}
	return 0;
}

void putNopes(HANDLE p, DWORD address, int x)
{

	BYTE nope[] = { 0x90 };
	for (int i = 0; i < x; i++)
	{

		WriteProcessMemory(p, LPVOID(address + 0x5), &nope, sizeof(nope), nullptr);
		address += 0x1;

	}

}

void freeMemory(HANDLE p, void* address, size_t cheatSize)
{

	VirtualFreeEx(p, address, (cheatSize + 0x5), MEM_DECOMMIT);

}

unsigned int read(HANDLE p, int address)
{

	unsigned int finalAddress;
	ReadProcessMemory(p, LPVOID(address), &finalAddress, sizeof(finalAddress), nullptr);

	return finalAddress;
	
}

void chkWItem(HANDLE p, int address, int value)// Check and Write Items - > chk W Item
{

	int temp;

	ReadProcessMemory(p, LPVOID(address), &temp, sizeof(temp), nullptr);

	if (!temp == 0)
	{

		WriteProcessMemory(p, LPVOID(address), &value, sizeof(value), nullptr);

	}

}
