#pragma once
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <tchar.h>
#include <TlHelp32.h>
using namespace std;

void* allocMem(HANDLE p, BYTE cheat[]) //Allocate memory for codecave
{

	void* AllocMem = VirtualAllocEx(p, NULL, sizeof(cheat) + 1, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	return AllocMem;
}

void* calJmp(void* d, DWORD d2, int x, size_t cheatSize) //Calculate the address for jmp instruction
{
	
	if (x == 0)
	{

		DWORD x1 = (DWORD)d;
		DWORD x2 = (d2 + sizeof(cheatSize)) - x1 - 0x5;
		void *x3 = (void*)x2;
		return x3;

	}
	
	if (x == 1)
	{

		DWORD x1 = (DWORD)d;
		DWORD x2 = x1 - d2 - 0x5;
		void *x3 = (void*)x2;
		return x3;

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

void getPointer(HANDLE p, DWORD address, char* point, size_t size) //Future
{

	unsigned long temp, buff;
	ReadProcessMemory(p, LPVOID(address), &temp, sizeof(temp), nullptr);
	//cout << size;

	if (size < 2)
	{

		buff = temp + point[0];
		void* pointer = (void*)buff;
		//return buff;
		cout << hex << buff;

	}
	else if (size >= 2 && size < 3)
	{

		for (int i = 0; i < size; i++)
		{

			buff = temp + point[i];
			ReadProcessMemory(p, LPVOID(buff), &temp, sizeof(temp), nullptr);

		}

		void* pointer = (void*)buff;
		cout << hex << buff;
		//return pointer;

	}

	if (size >= 3)
	{

		for (int i = 0; i < size; i++)
		{

			buff = temp + point[i];
			ReadProcessMemory(p, LPVOID(buff), &temp, sizeof(temp), nullptr);

		}

		void* pointer = (void*)buff;
		cout << hex << buff;

	}

}
