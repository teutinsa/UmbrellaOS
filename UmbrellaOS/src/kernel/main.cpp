#include "Types.h"
#include "Terminal.h"
#include "String.h"
#include "Utils.h"
#include "MemMap.h"

extern "C" void kmain()
{
	Terminal::EnableCursor(14, 15);
	Terminal::Clear(0x0F);

	Terminal::Print("Umbrella OS (C) 2022 Florian Schumacher\r\n", 0x0F);

	DWORD memMapNum = *reinterpret_cast<volatile DWORD*>(0x8000);
	char buffer[11];
	itoa(memMapNum, buffer, 11);
	Terminal::Print("Number of memory map entries: ", 0x0F);
	Terminal::Print(buffer, 0x0F);
	Terminal::Print("\r\n", 0x0F);

	for (DWORD i = 0; i < memMapNum; i++)
	{
		char tmp[21];
		volatile MemMapEntry* entry = &reinterpret_cast<volatile MemMapEntry*>(reinterpret_cast<volatile BYTE*>(0x8000) + sizeof(DWORD))[i];

		Terminal::Print(" - [", 0x0F);
		itoa(i + 1, tmp, 21);
		Terminal::Print(tmp, 0x0F);
		
		Terminal::Print("]\n\r    base: ", 0x0F);
		itoa(entry->baseAddr, tmp, 21);
		Terminal::Print(tmp, 0x0F);

		Terminal::Print(", length: ", 0x0F);
		itoa(entry->length, tmp, 21);
		Terminal::Print(tmp, 0x0F);

		Terminal::Print("\n\r    type: ", 0x0F);
		itoa((DWORD)entry->type, tmp, 21);
		Terminal::Print(tmp, 0x0F);
		
		Terminal::Print("\n\r    attributes {", 0x0F);
		Terminal::Print(" ignored: ", 0x0F);
		if (!entry->exAttrib.ignore)
			Terminal::Print("yes", 0x0F);
		else
			Terminal::Print("no", 0x0F);
		
		Terminal::Print(", non volatile: ", 0x0F);
		if (entry->exAttrib.nonVolatile)
			Terminal::Print("yes", 0x0F);
		else
			Terminal::Print("no", 0x0F);

		Terminal::Print(" }\r\n", 0x0F);
	}
}