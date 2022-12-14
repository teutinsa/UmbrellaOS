#include "Types.h"
#include "Terminal.h"
#include "String.h"
#include "Utils.h"
#include "MemMap.h"
#include "Memory.h"
#include "IDT.h"

void kmain()
{
	EnableCursor(14, 15);
	Clear(0x0F);

	Print("Umbrella OS (C) 2022 Florian Schumacher\r\n", 0x0F);

	Print("Loading IDT...\r\n", 0x0F);
	LoadIDT();

	DWORD memMapNum = *((DWORD*)0x8000);
	char buffer[12];
	itoa(memMapNum, buffer, sizeof(buffer));
	Print("Number of memory map entries: ", 0x0F);
	Print(buffer, 0x0F);
	Print("\r\n", 0x0F);

	const MemMapEntry* qualifiedEntry = NULL;
	for (DWORD i = 0; i < memMapNum; i++)
	{
		char tmp[22];
		MemMapEntry* entry = &((MemMapEntry*)(((BYTE*)0x8000) + sizeof(DWORD)))[i];

		Print(" - [", 0x0F);
		itoa(i + 1, tmp, sizeof(tmp));
		Print(tmp, 0x0F);
		
		Print("]\n\r    base: ", 0x0F);
		itoa(entry->baseAddr, tmp, 21);
		Print(tmp, 0x0F);

		Print(", length: ", 0x0F);
		itoa(entry->length, tmp, sizeof(tmp));
		Print(tmp, 0x0F);

		Print("\n\r    type: ", 0x0F);
		itoa((DWORD)entry->type, tmp, sizeof(tmp));
		Print(tmp, 0x0F);
		
		Print("\n\r    attributes {", 0x0F);
		Print(" ignored: ", 0x0F);
		if ((entry->exAttrib & (1<<0)) < 1)
			Print("yes", 0x0F);
		else
			Print("no", 0x0F);
		
		Print(", non volatile: ", 0x0F);
		if ((entry->exAttrib & (1 << 1)) >= 1)
			Print("yes", 0x0F);
		else
			Print("no", 0x0F);

		Print(" }\r\n", 0x0F);

		if (entry->type == MEMMAP_TYPE_USABLE && ((entry->exAttrib & (1 << 0)) >= 1) && ((entry->exAttrib & (1 << 1)) < 1))
			qualifiedEntry = entry;
	}

	if (!qualifiedEntry)
	{
		Print("No qualified entries found!\r\n", 0x0F);
		return;
	}

	InitPages(qualifiedEntry);
}