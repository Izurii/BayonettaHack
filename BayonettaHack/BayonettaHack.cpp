#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <string>

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

	HANDLE p = GetCurrentProcess();
	BYTE cheat[13] = { 0xC7, 0x46, 0x2C, 0x00, 0x00, 0xC8, 0x42, 0xF3, 0x0F, 0x58, 0x46, 0x2C, 0xE9 };
	BYTE ori[] = { 0xE9 };
	DWORD hp = FindPattern(0x004A8000, 6000, (PBYTE)"\xF3\x0F\x58\x46\x2C\x50", "xxxxxx");
	void* alloc = VirtualAllocEx(p, NULL, sizeof(cheat) + 1, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	void * pa = alloc;
	pa = static_cast<char*>(pa) + 0xD;
	char t[1024];
	sprintf_s(t, "%0x", alloc); 

	while (true)
	{

		Sleep(100);

		if (GetAsyncKeyState(VK_F3))
		{

			
			MessageBoxA(NULL, t, "Address of AllocMem", NULL);


			DWORD x1 = (DWORD)alloc + 0xC;
			DWORD x2 = (hp + 0x5) - x1 - 0x5;
			void *x3 = (void*)x2;
			DWORD x4 = (DWORD)alloc;
			DWORD x5 = x4 - hp - 0x5;
			void *x6 = (void*)x5;


			WriteProcessMemory(p, LPVOID(alloc), &cheat, sizeof(cheat), nullptr);
			WriteProcessMemory(p, LPVOID(pa), &x3, sizeof(x3), nullptr);
			WriteProcessMemory(p, LPVOID(hp), &ori, sizeof(ori), nullptr);
			WriteProcessMemory(p, LPVOID(hp+0x1), &x6, sizeof(x6), nullptr);


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
