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
	BYTE magicCheat1[] = { 0x90, 0xE9 };
	BYTE magicCheat2[] = { 0x90, 0xE9 };
	BYTE oneHitCheat[] = { 0xC7, 0x86, 0xB4, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE9 };
	BYTE maxTonCheat1[] = { 0xC7, 0x46, 0x2C, 0x00, 0x00, 0xC8, 0x42, 0xF3, 0x0F, 0x58, 0x46, 0x2C, 0xE9 };
	BYTE maxTonCheat2[] = { 0xC7, 0x46, 0x74, 0x00, 0x00, 0xC8, 0x42, 0xF3, 0x0F, 0x10, 0x46, 0x74, 0xE9 };
	BYTE infJumpCheat[] = { 0x90, 0xE9 };
	BYTE alfLifeCheat[] = { 0x90, 0xE9 };
	BYTE alfTimeCheat[] = { 0x90, 0xE9 };

	//Actual original/patterns codes
	BYTE goldBytes[] = { 0x29, 0x81, 0xE4, 0xF5, 0x00, 0x00 };
	BYTE healthBytes[] = { 0x89, 0x86, 0x08, 0x35, 0x09, 0x00 };
	BYTE witchTimeBytes[] = { 0xF3, 0x0F, 0x10, 0x96, 0x5C, 0x5D, 0x09, 0x00 };
	BYTE magicBytes1[] = { 0xF3, 0x0F, 0x5C, 0x05, 0xDC, 0x0D, 0xDA, 0x00 };
	BYTE magicBytes2[] = { 0xF3, 0x0F, 0x5C, 0x05, 0x58, 0x4B, 0xDA, 0x00, 0x0F, 0x57, 0xC9, 0x0F, 0x2F, 0xC8, 0xF3, 0x0F, 0x11, 0x05 };
	BYTE oneHitBytes[] = { 0x89, 0x86, 0xB4, 0x06, 0x00, 0x00, 0x85, 0xC0, 0x7F, 0x26 };
	BYTE maxTonBytes1[] = { 0xF3, 0x0F, 0x58, 0x46, 0x2C, 0x50 };
	BYTE maxTonBytes2[] = { 0xF3, 0x0F, 0x10, 0x46, 0x74, 0x50 };
	BYTE infJumpBytes[] = { 0x01, 0xAE, 0x78, 0x35, 0x09, 0x00 };
	BYTE alfLifeBytes[] = { 0xFF, 0x8E, 0x54, 0x6B, 0x09, 0x00 };
	BYTE alfTimeBytes[] = { 0xF3, 0x0F, 0x11, 0x46, 0x0C, 0x76 };

	//Other things lol

	HWND hwnd = FindWindowA(0, "Bayonetta");
	DWORD processId;
	GetWindowThreadProcessId(hwnd, &processId);
	HANDLE p = GetCurrentProcess();
	unsigned int temp;
	

	/*  Address || Pointers && Offsets (P.S: Variables for the final addresses) status too */

	DWORD gameBaseAddress = getBaseAddress(processId, L"Bayonetta.exe");

	//Halos
	DWORD haloAddress = gameBaseAddress + 0x000291B4;
	char haloOffset = { 0x14 };
	unsigned int haloFinalAddress;
	int haloMax = 9000000;
	void* haloMemAddressOri = 0;
	void* haloScriptAddressOri = 0;
	int statusHaloCheat = 0;

	//Health
	DWORD healthFirstAddress = gameBaseAddress + 0x0567AB8C;
	DWORD healthSecondAddress = gameBaseAddress + 0x008235F8;
	unsigned int healthFirstFinalAddress, healthSecondFinalAddress;
	int healthMax = 8000;
	void* healthMemAddressOri = 0;
	void* healthScriptAddressOri = 0;
	int statusHealthCheat = 0;

	//Witch Time
	void* witchTimeAddressOri = 0;
	void* witchTimeMemAddressOri = 0;
	int statusWitchTimeCheat = 0;

	//Magic
	DWORD magicAddress = gameBaseAddress + 0x004BC82C;
	BYTE magicOffset[] = { 0x14 };
	unsigned int magicFinalAddress;
	float magicMax = 1200;
	void* magicMemAddressOri1 = 0;
	void* magicMemAddressOri2 = 0;
	void* magicScriptAddressOri1 = 0;
	void* magicScriptAddressOri2 = 0;
	int statusMagicCheat = 0;

	//One Hit Kill
	void* oneHitMemAddressOri = 0;
	void* oneHitScriptAddressOri = 0;
	int statusOneHitCheat = 0;

	//Max Giga/Mega Ton
	void* maxTonMemAddressOri1 = 0;
	void* maxTonMemAddressOri2 = 0;
	void* maxTonScriptAddressOri1 = 0;
	void* maxTonScriptAddressOri2 = 0;
	int statusMaxTonCheat = 0;

	//Infinite Jump
	void* infJumpMemAddressOri = 0;
	void* infJumpScriptAddressOri = 0;
	int statusInfJumpCheat = 0;

	//Max All Items

	int maxValueItem = 99;
	int maxValueBullet = 20;

		/* Lollipops */

	int bigGreen = gameBaseAddress + 0x000970C8; int bigRose = gameBaseAddress + 0x000970C8;
	int bigYellow = gameBaseAddress + 0x000970C8; int bigPurple = gameBaseAddress + 0x000970C8;
	int smallGreen = gameBaseAddress + 0x00747810; int smallRose = gameBaseAddress + 0x00747810;
	int smallYellow = gameBaseAddress + 0x00747810; int smallPurple = gameBaseAddress + 0x00747810;
	int bigGreenAddress, bigRoseAddress, bigYellowAddress, bigPurpleAddress;
	int smallGreenAddress, smallRoseAddress, smallYellowAddress, smallPurpleAddress;

		/* Compounds */

	int compGreen = gameBaseAddress + 0x000970C8;
	int compRose = gameBaseAddress + 0x000970C8;
	int compYellow = gameBaseAddress + 0x000970C8;
	int compGreenAddress, compRoseAddress, compYellowAddress;

		/* Other items */

	int magicFlute = gameBaseAddress + 0x000970C8;
	int redHot = gameBaseAddress + 0x000970C8;
	int bullet = gameBaseAddress + 0x000970C8;
	int magicFluteAddress, redHotAddress, bulletAddress;

	/*	NOTHING  */

	//Alfheim

		/* Alfheim cheat life */

	void* alfLifeMemAddressOri = 0;
	void* alfLifeScriptAddressOri = 0;
	int statusAlfLifeCheat = 0;

		/* Alfheim cheat time */

	void* alfTimeMemAddressOri = 0;
	void* alfTimeScriptAddressOri = 0;
	int statusAlfTimeCheat = 0;

	//The end

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

	//Magic

	ReadProcessMemory(p, LPVOID(magicAddress), &temp, sizeof(temp), nullptr);
	magicFinalAddress = temp + magicOffset[0];

	//Items

		/* Lollipops */

	bigGreenAddress = read(p, bigGreen) + 0x1C;		smallGreenAddress = read(p, smallGreen) + 0xC;
	bigRoseAddress = read(p, bigRose) + 0x2C;		smallRoseAddress = read(p, smallRose) + 0x1C;
	bigYellowAddress = read(p, bigYellow) + 0x34;	smallYellowAddress = read(p, smallYellow) + 0x24;
	bigPurpleAddress = read(p, bigPurple) + 0x24;	smallPurpleAddress = read(p, smallPurple) + 0x14;

		/* Compounds */

	compGreenAddress = read(p, compGreen) + 0x10;
	compRoseAddress = read(p, compRose) + 0x14;
	compYellowAddress = read(p, compYellow) + 0xC;

		/* Other items */

	magicFluteAddress = read(p, magicFlute) + 0x38;
	redHotAddress = read(p, redHot) + 0x40;
	bulletAddress = read(p, bullet) + 0x3C;

	/*  Again  */

	//--------------------------------------------------------------------------------


	while (true)
	{

		Sleep(100);

		if (GetAsyncKeyState(VK_F1))
		{

			//Allocate Memory

			void* MemAddress = allocMem(p, haloCheat + 0x5);
			void* MemAddressOff = static_cast<char*>(MemAddress) + sizeof(haloCheat);

			//Find the address of original code

			DWORD scriptGold = FindPattern(0x00501000, 6000, goldBytes, "xxxxxx");

			//Calculate the jmp bytes

			void* jmpToCheat = calJmp(MemAddress, scriptGold, 1, NULL);
			void* jmpOfReturn = calJmp(static_cast<char*>(MemAddress) - 0x3, scriptGold, 0, sizeof(haloCheat));

			if (statusHaloCheat == 0)
			{

				//Define some variables

				Beep(2000, 200);
				statusHaloCheat = 1;
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
				putNopes(p, scriptGold, 1);

			}
			else
			{

				Beep(1000, 200);
				statusHaloCheat = 0;

				//Return original code in game memory and deallocate the memory allocated by allocMem

				WriteProcessMemory(p, LPVOID(haloScriptAddressOri), &goldBytes, sizeof(goldBytes), nullptr);
				freeMemory(p, haloMemAddressOri, sizeof(haloCheat));

			}

		}

		if (GetAsyncKeyState(VK_F2))
		{

			//Allocate Memory

			void* MemAddress = allocMem(p, healthCheat + 0x5);
			void* MemAddressOff = static_cast<char*>(MemAddress) + sizeof(healthCheat);

			//Find the address of original code

			DWORD scriptHealth = FindPattern(0x009D4000, 6000, healthBytes, "xxxxxx");

			//Calculate the jmp bytes

			void* jmpToCheat = calJmp(MemAddress, scriptHealth, 1, NULL);
			void* jmpOfReturn = calJmp(MemAddress, scriptHealth, 0, sizeof(healthCheat));

			if (statusHealthCheat == 0)
			{

				//Define some variables

				Beep(2000, 200);
				statusHealthCheat = 1;
				healthScriptAddressOri = reinterpret_cast<void*>(scriptHealth);
				healthMemAddressOri = MemAddress;

				//Write the max health

				//WriteProcessMemory(p, LPVOID(healthFirstFinalAddress), &healthMax, sizeof(healthMax), nullptr);
				//WriteProcessMemory(p, LPVOID(healthSecondFinalAddress), &healthMax, sizeof(healthMax), nullptr);

				//Write in the allocated mem

				WriteProcessMemory(p, LPVOID(MemAddress), &healthCheat, sizeof(healthCheat), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff), &jmpOfReturn, sizeof(jmpOfReturn), nullptr);

				//c0d3 c4v1ng

				WriteProcessMemory(p, LPVOID(scriptHealth), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptHealth + 0x1), &jmpToCheat, sizeof(jmpToCheat), nullptr);
				putNopes(p, scriptHealth, 1);

			}
			else {

				Beep(1000, 200);
				statusHealthCheat = 0;

				//Return original code in game memory and deallocate the memory allocated by allocMem

				WriteProcessMemory(p, LPVOID(healthScriptAddressOri), &healthBytes, sizeof(healthBytes), nullptr);
				freeMemory(p, healthMemAddressOri, sizeof(healthCheat));

			}

		}

		if (GetAsyncKeyState(VK_F3))
		{

			//Allocate Memory

			void* MemAddress = allocMem(p, witchTimeCheat + 0x5);
			void* MemAddressOff = static_cast<char*>(MemAddress) + sizeof(witchTimeCheat);

			//Find the address of original code

			DWORD scriptWitchTime = FindPattern(0x009E1000, 6000, witchTimeBytes, "xxxxxxxx");

			//Calculate the jmp bytes

			void* jmpToCheat = calJmp(MemAddress, scriptWitchTime, 1, NULL);
			void* jmpOfReturn = calJmp((static_cast<char*>(MemAddressOff) - 0x1), scriptWitchTime, 0, 0x8);

			if (statusWitchTimeCheat == 0)
			{

				//Define some variables

				Beep(2000, 200);
				statusWitchTimeCheat = 1;
				witchTimeMemAddressOri = MemAddress;
				witchTimeAddressOri = reinterpret_cast<void*>(scriptWitchTime);

				//Write in the allocated memory

				WriteProcessMemory(p, LPVOID(MemAddress), &witchTimeCheat, sizeof(witchTimeCheat), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff), &jmpOfReturn, sizeof(jmpOfReturn), nullptr);

				//C0d35 c4v35

				WriteProcessMemory(p, LPVOID(scriptWitchTime), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptWitchTime + 0x1), &jmpToCheat, sizeof(jmpToCheat), nullptr);
				putNopes(p, scriptWitchTime, 3);


			}
			else {

				Beep(1000, 200);
				statusWitchTimeCheat = 0;

				//Return original code in game memory and deallocate the memory allocated by allocMem

				WriteProcessMemory(p, LPVOID(witchTimeAddressOri), &witchTimeBytes, sizeof(witchTimeBytes), nullptr);
				freeMemory(p, witchTimeMemAddressOri, sizeof(witchTimeCheat));

			}

		}

		if (GetAsyncKeyState(VK_F4))
		{

			//Allocate Memory

			void* MemAddress1 = allocMem(p, (magicCheat1 + 0x5));
			void* MemAddress2 = allocMem(p, (magicCheat2 + 0x5));
			void* MemAddressOff1 = static_cast<char*>(MemAddress1) + sizeof(magicCheat1);
			void* MemAddressOff2 = static_cast<char*>(MemAddress2) + sizeof(magicCheat2);

			//Find the address of original code

			DWORD scriptMagic1 = FindPattern(0x00501000, 6000, magicBytes1, "xxxxxxxx");
			DWORD scriptMagic2 = FindPattern(0x00502000, 6000, magicBytes2, "xxxxxxxxxxxxxxxxxx");

			//Calculate the jmp bytes

			void* jmpToCheat1 = calJmp(MemAddress1, scriptMagic1, 1, NULL);
			void* jmpToCheat2 = calJmp(MemAddress2, scriptMagic2, 1, NULL);
			void* jmpOfReturn1 = calJmp((static_cast<char*>(MemAddressOff1) - 0x1), scriptMagic1, 0, sizeof(magicBytes1));
			void* jmpOfReturn2 = calJmp((static_cast<char*>(MemAddressOff2) + 0x9), scriptMagic2, 0, sizeof(magicBytes2));

			if (statusMagicCheat == 0)
			{

				//As you see...

				Beep(2000, 200);
				statusMagicCheat = 1;
				magicScriptAddressOri1 = reinterpret_cast<void*>(scriptMagic1);
				magicScriptAddressOri2 = reinterpret_cast<void*>(scriptMagic2);
				magicMemAddressOri1 = MemAddress1;
				magicMemAddressOri2 = MemAddress2;

				//Max the magic

				WriteProcessMemory(p, LPVOID(magicFinalAddress), &magicMax, sizeof(magicMax), nullptr);

				//Write in allocated memory

				WriteProcessMemory(p, LPVOID(MemAddress1), &magicCheat1, sizeof(magicCheat1), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff1), &jmpOfReturn1, sizeof(jmpOfReturn1), nullptr);

				WriteProcessMemory(p, LPVOID(MemAddress2), &magicCheat2, sizeof(magicCheat2), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff2), &jmpOfReturn2, sizeof(jmpOfReturn2), nullptr);

				//c0d1ng caverna

				WriteProcessMemory(p, LPVOID(scriptMagic1), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptMagic1 + 0x1), &jmpToCheat1, sizeof(jmpToCheat1), nullptr);
				putNopes(p, scriptMagic1, 3);

				WriteProcessMemory(p, LPVOID(scriptMagic2), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptMagic2 + 0x1), &jmpToCheat2, sizeof(jmpToCheat2), nullptr);
				putNopes(p, scriptMagic2, 3);

			}
			else {

				Beep(1000, 200);
				statusMagicCheat = 0;

				//Return original code in game memory and deallocate the memory allocated by allocMem

				WriteProcessMemory(p, LPVOID(magicScriptAddressOri1), &magicBytes1, sizeof(magicBytes1), nullptr);
				WriteProcessMemory(p, LPVOID(magicScriptAddressOri2), &magicBytes2, sizeof(magicBytes2), nullptr);
				freeMemory(p, magicMemAddressOri1, sizeof(magicCheat1));
				freeMemory(p, magicMemAddressOri2, sizeof(magicCheat1));

			}

		}

		if (GetAsyncKeyState(VK_F5))
		{

			//Allocate Memory

			void* MemAddress = allocMem(p, oneHitCheat);
			void* MemAddressOff = static_cast<char*>(MemAddress) + sizeof(oneHitCheat);

			//Find the orignal code

			DWORD scriptoneHit = FindPattern(0x00457000, 6000, oneHitBytes, "xxxxxxxxxx");

			//Calculate jmp

			void* jmpToCheat = calJmp(MemAddress, scriptoneHit, 1, NULL);
			void* jmpOfReturn = calJmp((static_cast<char*>(MemAddressOff) + 0x4), scriptoneHit, 0, sizeof(oneHitBytes));

			if (statusOneHitCheat == 0)
			{

				//F.H.R.I.T.P

				Beep(2000, 200);
				statusOneHitCheat = 1;
				oneHitMemAddressOri = MemAddress;
				oneHitScriptAddressOri = reinterpret_cast<void*>(scriptoneHit);

				//Write in allocated memory

				WriteProcessMemory(p, LPVOID(MemAddress), &oneHitCheat, sizeof(oneHitCheat), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff), &jmpOfReturn, sizeof(jmpOfReturn), nullptr);

				//ca ving c0 d 3 (115*2-225)

				WriteProcessMemory(p, LPVOID(scriptoneHit), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptoneHit + 0x1), &jmpToCheat, sizeof(jmpToCheat), nullptr);
				putNopes(p, scriptoneHit, 1);

			}
			else {

				Beep(1000, 200);
				statusOneHitCheat = 0;

				WriteProcessMemory(p, LPVOID(oneHitScriptAddressOri), &oneHitBytes, sizeof(oneHitBytes), nullptr);
				freeMemory(p, oneHitMemAddressOri, sizeof(oneHitCheat));

			}


		}

		if (GetAsyncKeyState(VK_F6))
		{

			//Allocate Memory

			void* MemAddress1 = allocMem(p, maxTonCheat1);
			void* MemAddress2 = allocMem(p, maxTonCheat1);
			void* MemAddressOff1 = static_cast<char*>(MemAddress1) + sizeof(maxTonCheat1);
			void* MemAddressOff2 = static_cast<char*>(MemAddress2) + sizeof(maxTonCheat2);

			//Original code

			DWORD scriptmaxTon1 = FindPattern(0x004A8000, 6000, maxTonBytes1, "xxxxxx");
			DWORD scriptmaxTon2 = FindPattern(0x00C1D000, 6000, maxTonBytes2, "xxxxxx");

			//Calculate jmp

			void* jmpToCheat1 = calJmp(MemAddress1, scriptmaxTon1, 1, NULL);
			void* jmpToCheat2 = calJmp(MemAddress2, scriptmaxTon2, 1, NULL);
			void* jmpOfReturn1 = calJmp(static_cast<char*>(MemAddress1)+0x14, scriptmaxTon1, 0, sizeof(maxTonCheat1));
			void* jmpOfReturn2 = calJmp(static_cast<char*>(MemAddress2)+0x14, scriptmaxTon2, 0, sizeof(maxTonCheat2));


			if (statusMaxTonCheat == 0)
			{

				//Define

				Beep(2000, 200);
				statusMaxTonCheat = 1;
				maxTonMemAddressOri1 = MemAddress1;
				maxTonMemAddressOri2 = MemAddress2;
				maxTonScriptAddressOri1 = reinterpret_cast<void*>(scriptmaxTon1);
				maxTonScriptAddressOri2 = reinterpret_cast<void*>(scriptmaxTon2);

				//Write allocated memory

				WriteProcessMemory(p, LPVOID(MemAddress1), &maxTonCheat1, sizeof(maxTonCheat1), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff1), &jmpOfReturn1, sizeof(jmpOfReturn1), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddress2), &maxTonCheat2, sizeof(maxTonCheat2), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff2), &jmpOfReturn2, sizeof(jmpOfReturn2), nullptr);

				//Fucking h4ck3r5

				WriteProcessMemory(p, LPVOID(scriptmaxTon1), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptmaxTon1 + 0x1), &jmpToCheat1, sizeof(jmpToCheat1), nullptr);
				WriteProcessMemory(p, LPVOID(scriptmaxTon2), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptmaxTon2 + 0x1), &jmpToCheat2, sizeof(jmpToCheat2), nullptr);

			}
			else {

				Beep(1000, 200);
				statusMaxTonCheat = 0;

				WriteProcessMemory(p, LPVOID(maxTonScriptAddressOri1), &maxTonBytes1, sizeof(maxTonBytes1), nullptr);
				WriteProcessMemory(p, LPVOID(maxTonScriptAddressOri2), &maxTonBytes2, sizeof(maxTonBytes2), nullptr);
				freeMemory(p, maxTonMemAddressOri1, sizeof(maxTonCheat1));
				freeMemory(p, maxTonMemAddressOri2, sizeof(maxTonCheat2));


			}

		}

		if (GetAsyncKeyState(VK_F7))
		{

			//Allocate memory

			void* MemAddress = allocMem(p, infJumpCheat);
			void* MemAddressOff = static_cast<char*>(MemAddress) + sizeof(infJumpCheat);

			//Find original

			DWORD scriptInfJump = FindPattern(0x009E8000, 6000, infJumpBytes, "xxxxxx");

			//Calculate jmp

			void* jmpToCheat = calJmp(MemAddress, scriptInfJump, 1, NULL);
			void* jmpOfReturn = calJmp(static_cast<char*>(MemAddress) - 0x3, scriptInfJump, 0, sizeof(infJumpCheat));

			if (statusInfJumpCheat == 0)
			{

				//Define

				Beep(2000, 200);
				statusInfJumpCheat = 1;
				infJumpMemAddressOri = MemAddress;
				infJumpScriptAddressOri = reinterpret_cast<void*>(scriptInfJump);

				//Write in allocated memory

				WriteProcessMemory(p, LPVOID(MemAddress), &infJumpCheat, sizeof(infJumpCheat), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff), &jmpOfReturn, sizeof(jmpOfReturn), nullptr);

				//huhh c4v3s

				WriteProcessMemory(p, LPVOID(scriptInfJump), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptInfJump + 0x1), &jmpToCheat, sizeof(jmpToCheat), nullptr);
				putNopes(p, scriptInfJump, 1);

			}
			else {

				Beep(1000, 200);
				statusInfJumpCheat = 0;

				WriteProcessMemory(p, LPVOID(infJumpScriptAddressOri), &infJumpBytes, sizeof(infJumpBytes), nullptr);
				freeMemory(p, infJumpMemAddressOri, sizeof(infJumpCheat));

			}

		}

		if (GetAsyncKeyState(VK_F8))
		{

			Beep(2000, 200);

			//Write the values in memory

				/* Write lollipops */

			chkWItem(p, bigGreenAddress, maxValueItem);
			chkWItem(p, bigRose, maxValueItem);
			chkWItem(p, bigYellow, maxValueItem);
			chkWItem(p, bigPurple, maxValueItem);
			chkWItem(p, smallGreen, maxValueItem);
			chkWItem(p, smallRose, maxValueItem);
			chkWItem(p, smallYellow, maxValueItem);
			chkWItem(p, smallPurple, maxValueItem);

				/* Write Compounds */

			chkWItem(p, compGreen, maxValueItem);
			chkWItem(p, compRose, maxValueItem);
			chkWItem(p, compYellow, maxValueItem);

				/* Other items */

			chkWItem(p, redHot, maxValueItem);
			chkWItem(p, magicFlute, maxValueItem);
			chkWItem(p, bullet, maxValueBullet);

		}

		if (GetAsyncKeyState(VK_F9))
		{

			//Allocate Memory

			void* MemAddress = allocMem(p, alfLifeCheat);
			void* MemAddressOff = static_cast<char*>(MemAddress) + sizeof(alfLifeCheat);

			//Find original code

			DWORD scriptalfLife = FindPattern(0x009D4000, 6000, alfLifeBytes, "xxxxxx");

			//Calculate jmp

			void* jmpToCheat = calJmp(MemAddress, scriptalfLife, 1, NULL);
			void* jmpOfReturn = calJmp(static_cast<char*>(MemAddress) + 0x2, scriptalfLife, 0, sizeof(alfLifeBytes));

			if (statusAlfLifeCheat == 0)
			{

				//Sucks

				Beep(2000, 200);
				statusAlfLifeCheat = 1;
				alfLifeMemAddressOri = MemAddress;
				alfLifeScriptAddressOri = reinterpret_cast<void*>(scriptalfLife);

				//Write in allocated memory

				WriteProcessMemory(p, LPVOID(MemAddress), &alfLifeCheat, sizeof(alfLifeCheat), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff), &jmpOfReturn, sizeof(jmpOfReturn), nullptr);

				//Again caves

				WriteProcessMemory(p, LPVOID(scriptalfLife), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptalfLife+0x1), &jmpToCheat, sizeof(jmpToCheat), nullptr);
				putNopes(p, scriptalfLife, 1);


			}
			else {
				
				Beep(1000, 200);
				statusAlfLifeCheat = 0;
				WriteProcessMemory(p, LPVOID(alfLifeScriptAddressOri), &alfLifeBytes, sizeof(alfLifeBytes), nullptr);
				freeMemory(p, alfLifeMemAddressOri, sizeof(alfLifeCheat));

			}

		}

		if (GetAsyncKeyState(VK_F10))
		{

			//Allocate Memory

			void* MemAddress = allocMem(p, alfTimeCheat);
			void* MemAddressOff = static_cast<char*>(MemAddress) + sizeof(alfTimeCheat);

			//Find original code

			DWORD scriptalfTime = FindPattern(0x00620000, 6000, alfTimeBytes, "xxxxxx");

			//Calculate jmp

			void* jmpToCheat = calJmp(MemAddress, scriptalfTime, 1, NULL);
			void* jmpOfReturn = calJmp(static_cast<char*>(MemAddress) + 0x2, scriptalfTime, 0, sizeof(alfTimeBytes));

			if (statusAlfTimeCheat == 0)
			{

				//Sucks

				Beep(2000, 200);
				statusAlfTimeCheat = 1;
				alfTimeMemAddressOri = MemAddress;
				alfTimeScriptAddressOri = reinterpret_cast<void*>(scriptalfTime);

				//Write in allocated memory

				WriteProcessMemory(p, LPVOID(MemAddress), &alfTimeCheat, sizeof(alfTimeCheat), nullptr);
				WriteProcessMemory(p, LPVOID(MemAddressOff), &jmpOfReturn, sizeof(jmpOfReturn), nullptr);

				//Again caves 2

				WriteProcessMemory(p, LPVOID(scriptalfTime), &jmpInstruction, sizeof(jmpInstruction), nullptr);
				WriteProcessMemory(p, LPVOID(scriptalfTime + 0x1), &jmpToCheat, sizeof(jmpToCheat), nullptr);


			}
			else {

				Beep(1000, 200);
				statusAlfTimeCheat = 0;
				WriteProcessMemory(p, LPVOID(alfTimeScriptAddressOri), &alfTimeBytes, sizeof(alfTimeBytes), nullptr);
				freeMemory(p, alfTimeMemAddressOri, sizeof(alfTimeCheat));

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
