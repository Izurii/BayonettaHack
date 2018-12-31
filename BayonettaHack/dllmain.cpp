#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <string>
#include "Functions.h"
#include <memory.h>

using namespace std;

DWORD WINAPI main(PVOID ini)
{

	//Actual h4ck3r codes
	BYTE jmpInstruction[] = { 0xE9 };
	BYTE nopInstruction[] = { 0x90 };
	BYTE haloCheat[] = { 0x90, 0xE9 }; 
	BYTE healthCheat[] = { 0x90, 0xE9 };
	BYTE witchTimeCheat[] = { 0xC7, 0x86, 0x5C, 0x5D, 0x09, 0x00, 0x00, 0x00, 0xC8, 0x42, 0xF3, 0x0F, 0x10, 0x96, 0x5C, 0x5D, 0x09, 0x00, 0xE9 };

	//Actual original/patterns codes
	BYTE goldBytes[] = { 0x29, 0x81, 0xE4, 0xF5, 0x00, 0x00 };
	BYTE healthBytes[] = { 0x89, 0x86, 0x08, 0x35, 0x09, 0x00 };
	BYTE witchTimeBytes[] = { 0xF3, 0x0F, 0x10, 0x96, 0x5C, 0x5D, 0x09, 0x00 };

	//Other things lol

	HWND hwnd = FindWindowA(0, "Bayonetta");
	DWORD processId;
	GetWindowThreadProcessId(hwnd, &processId);
	HANDLE p = GetCurrentProcess();
	unsigned int temp, buff;
	unsigned int status = 0;
	

	/*  Address || Pointers && Offsets (P.S: Variables for the final addresses) */

	DWORD gameBaseAddress = getBaseAddress(processId, L"Bayonetta.exe");

	//Halos
	DWORD haloAddress = gameBaseAddress + 0x000291B4;
	char haloOffset = { 0x14 };
	unsigned int haloFinalAddress;
	int haloMax = 9000000;
	void* haloMemAddressOri = 0;
	void* haloScriptAddressOri = 0;

	//Health
	DWORD healthFirstAddress = gameBaseAddress + 0x0567AB8C;
	DWORD healthSecondAddress = gameBaseAddress + 0x008235F8;
	char healthFirstOffset[] = { 0x0, 0x168, 0x8, 0x4, 0x0, 0x98 };
	char healthSecondOffset[] = { 0xC };
	unsigned int healthFirstFinalAddress, healthSecondFinalAddress;
	int healthMax = 8000;
	void* healthMemAddressOri = 0;
	void* healthScriptAddressOri = 0;

	//Witch Time
	void* witchTimeAddressOri = 0;
	void* witchTimeMemAddressOri = 0;

	
	//--------------------------------------------------------------------------------


	/* Picking (the pointers || Final addresses) */

	//Halos
	ReadProcessMemory(p, LPVOID(haloAddress), &temp, sizeof(temp), nullptr);
	haloFinalAddress = haloOffset + temp;

	//Health

						//Get the first pointer to health//

	ReadProcessMemory(p, LPVOID(healthFirstAddress), &temp, sizeof(temp), nullptr);
	ReadProcessMemory(p, LPVOID(temp + 0x0), &temp, sizeof(temp), nullptr);
	ReadProcessMemory(p, LPVOID(temp + 0x168), &temp, sizeof(temp), nullptr);
	ReadProcessMemory(p, LPVOID(temp + 0x8), &temp, sizeof(temp), nullptr);
	ReadProcessMemory(p, LPVOID(temp + 0x4), &temp, sizeof(temp), nullptr);
	ReadProcessMemory(p, LPVOID(temp + 0x0), &temp, sizeof(temp), nullptr);

	healthFirstFinalAddress = temp + 0x98;

						//Get the second pointer to health//

	ReadProcessMemory(p, LPVOID(healthSecondAddress), &temp, sizeof(temp), nullptr);

	healthSecondFinalAddress = temp + 0xC;

	//--------------------------------------------------------------------------------


	while (true)
	{

		Sleep(100);

		if (GetAsyncKeyState(VK_F1))
		{

			void* MemAddress = allocMem(p, haloCheat + 0x5);
			void* MemAddressOff = static_cast<char*>(MemAddress) + 0x2;
			
			DWORD scriptGold = FindPattern(0x00501000, 6000, goldBytes, "xxxxxx");

			void* jmpToCheat = calJmp(MemAddress, scriptGold, 1, NULL);
			void* jmpOfReturn = calJmp(MemAddress, scriptGold, 0, sizeof(haloCheat));

			if (status == 0)
			{

				//Define some variables

				status = 1;
				haloScriptAddressOri = reinterpret_cast<void*>(scriptGold);
				haloMemAddressOri = MemAddress;

				//"Max" Gold

				WriteProcessMemory(p, LPVOID(haloFinalAddress), &haloMax, sizeof(haloMax), nullptr);

				//Write in the allocated memory

				WriteProcessMemory(p, LPVOID(MemAddress), &haloCheat, sizeof(haloCheat), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff), &jmpOfReturn, sizeof(jmpOfReturn), nullptr);

				//Codecave in game

				WriteProcessMemory(p, LPVOID(scriptGold), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptGold + 0x1), &jmpToCheat, sizeof(jmpToCheat), nullptr);
				WriteProcessMemory(p, LPVOID(scriptGold + 0x5), &nopInstruction, sizeof(nopInstruction), nullptr);

			}
			else
			{

				status = 0;

				//Return original code in game memory and deallocate the memory allocated by allocMem

				WriteProcessMemory(p, LPVOID(haloScriptAddressOri), &goldBytes, sizeof(goldBytes), nullptr);
				VirtualFreeEx(p, haloMemAddressOri, sizeof(haloCheat + 0x5), MEM_DECOMMIT);

			}

		}

		if (GetAsyncKeyState(VK_F2))
		{
			
			void* MemAddress = allocMem(p, healthCheat+0x5);
			void* MemAddressOff = static_cast<char*>(MemAddress) + 0x2;

			DWORD scriptHealth = FindPattern(0x009D4000, 6000, healthBytes, "xxxxxx");

			void* jmpToCheat = calJmp(MemAddress, scriptHealth, 1, NULL);
			void* jmpOfReturn = calJmp(MemAddress, scriptHealth, 0, sizeof(healthCheat));

			if (status == 0)
			{

				//Define some variables

				status = 1;
				healthScriptAddressOri = reinterpret_cast<void*>(scriptHealth);
				healthMemAddressOri = MemAddress;

				//Write the max health

				WriteProcessMemory(p, LPVOID(healthFirstFinalAddress), &healthMax, sizeof(healthMax), nullptr);
				WriteProcessMemory(p, LPVOID(healthSecondFinalAddress), &healthMax, sizeof(healthMax), nullptr);

				//Write in the allocated mem

				WriteProcessMemory(p, LPVOID(MemAddress), &healthCheat, sizeof(healthCheat), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff), &jmpOfReturn, sizeof(jmpOfReturn), nullptr);

				//c0d3 c4v1ng

				WriteProcessMemory(p, LPVOID(scriptHealth), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptHealth + 0x1), &jmpToCheat, sizeof(jmpToCheat), nullptr);
				WriteProcessMemory(p, LPVOID(scriptHealth + 0x5), &nopInstruction, sizeof(nopInstruction), nullptr);

			}
			else {

				status = 0;

				//Return original code in game memory and deallocate the memory allocated by allocMem

				WriteProcessMemory(p, LPVOID(healthScriptAddressOri), &healthBytes, sizeof(healthBytes), nullptr);
				VirtualFreeEx(p, healthMemAddressOri, sizeof(healthCheat + 0x5), MEM_DECOMMIT);

			}
		
		}

		if (GetAsyncKeyState(VK_F3))
		{

			void* MemAddress = allocMem(p, witchTimeCheat + 0x5);
			void* MemAddressOff = static_cast<char*>(MemAddress) + sizeof(witchTimeCheat);

			DWORD scriptWitchTime = FindPattern(0x009E1000, 6000, witchTimeBytes, "xxxxxxxx");
			
			void* jmpToCheat = calJmp(MemAddress, scriptWitchTime, 1, NULL);
			void* jmpOfReturn = calJmp((static_cast<char*>(MemAddressOff)-0x1), scriptWitchTime, 0, 0x8);

			if (status == 0)
			{

				//Define some variables
				status = 1;
				witchTimeMemAddressOri = MemAddress;
				witchTimeAddressOri = reinterpret_cast<void*>(scriptWitchTime);

				//Write in the allocated memory

				WriteProcessMemory(p, LPVOID(MemAddress), &witchTimeCheat, sizeof(witchTimeCheat), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff), &jmpOfReturn, sizeof(jmpOfReturn), nullptr);

				//C0d35 c4v35

				WriteProcessMemory(p, LPVOID(scriptWitchTime), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptWitchTime + 0x1), &jmpToCheat, sizeof(jmpToCheat), nullptr);
				WriteProcessMemory(p, LPVOID(scriptWitchTime + 0x5), &nopInstruction, sizeof(nopInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptWitchTime + 0x6), &nopInstruction, sizeof(nopInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptWitchTime + 0x7), &nopInstruction, sizeof(nopInstruction), nullptr);


			}
			else {

				status = 0;

				//Return original code in game memory and deallocate the memory allocated by allocMem

				WriteProcessMemory(p, LPVOID(witchTimeAddressOri), &witchTimeBytes, sizeof(witchTimeBytes), nullptr);
				VirtualFreeEx(p, witchTimeMemAddressOri, sizeof(witchTimeCheat + 0x5), MEM_DECOMMIT);

			}

		}

	}

	return 0;

}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, &main, 0, 0, 0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
