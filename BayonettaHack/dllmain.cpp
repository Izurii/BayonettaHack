#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <string>
#include "Functions.h"

using namespace std;

DWORD FindPattern(DWORD dwInicio, DWORD dwFim, BYTE *arrayBytes, CHAR mascara[]) {
	UINT r = NULL;
	INT sizeMask = strlen(mascara) - 1;
	for (DWORD i = dwInicio; i < (dwInicio + dwFim); i++) {
		if (*(BYTE*)i == arrayBytes[r] || mascara[r] == '?') {
			if (mascara[r + 1] == '\0')
				return(i - sizeMask);
			r++;
		}
		else
			r = NULL;
	}
	return 0;
}

DWORD WINAPI inicializa(PVOID ini)
{

	//Actual h4ck3r codes
	BYTE jmpInstruction[] = { 0xE9 };
	BYTE nopInstruction[] = { 0x90 };
	BYTE haloCheat[] = { 0x90 };

	//Other things lol

	HWND hwnd = FindWindowA(0, "Bayonetta");
	DWORD processId;
	GetWindowThreadProcessId(hwnd, &processId);
	HANDLE p = GetCurrentProcess();
	unsigned int temp, buff;
	

	/*  Address || Pointers && Offsets (P.S: Variables for the final addresses) */

	DWORD gameBaseAddress = getBaseAddress(processId, L"Bayonetta.exe");

	//Halos
	DWORD haloAddress = gameBaseAddress + 0x000291B4;
	char haloOffset = { 0x14 };
	unsigned int haloFinalAddress;
	int haloMax = 9000000;

	
	//--------------------------------------------------------------------------------


	/* Picking (the pointers || Final addresses) */

	//Halos
	ReadProcessMemory(p, LPVOID(haloAddress), &temp, sizeof(temp), nullptr);
	haloFinalAddress = haloOffset + temp;


	//--------------------------------------------------------------------------------


	while (true)
	{

		Sleep(100);

		if (GetAsyncKeyState(VK_F1))
		{

			void* MemAddress = allocMem(p, haloCheat+0x5);
			void* MemAddressOff = static_cast<char*>(MemAddress) + 0x1;
			void* MemAddressOff2 = static_cast<char*>(MemAddress) + 0x2;
			DWORD scriptGold = FindPattern(0x00501000, 6000, (PBYTE)"\x29\x81\xE4\xF5\x00\x00", "xxxxxx");
			void* jmpToCheat = calJmp(MemAddress, scriptGold, 1, NULL);
			void* jmpOfReturn = calJmp(MemAddress, scriptGold, 0, sizeof(haloCheat));

			//"Max" Gold

			WriteProcessMemory(p, LPVOID(haloFinalAddress), &haloMax, sizeof(haloMax), nullptr);

			//Write in the allocated memory

			WriteProcessMemory(p, LPVOID(MemAddress), &haloCheat, sizeof(haloCheat), nullptr);
			WriteProcessMemory(p, LPVOID(MemAddressOff), &jmpInstruction, sizeof(jmpInstruction), nullptr);
			WriteProcessMemory(p, LPVOID(MemAddressOff2), &jmpOfReturn, sizeof(jmpOfReturn), nullptr);

			//Codecave in game

			WriteProcessMemory(p, LPVOID(scriptGold), &jmpInstruction, sizeof(jmpInstruction), nullptr);
			WriteProcessMemory(p, LPVOID(scriptGold + 0x1), &jmpToCheat, sizeof(jmpToCheat), nullptr);
			WriteProcessMemory(p, LPVOID(scriptGold + 0x5), &nopInstruction, sizeof(nopInstruction), nullptr);

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
		CreateThread(0, 0, &inicializa, 0, 0, 0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
