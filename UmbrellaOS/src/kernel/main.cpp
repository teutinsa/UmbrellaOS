#include "Types.h"
#include "Terminal.h"
#include "String.h"

extern "C" void kmain(void* memmap)
{
	Terminal::HideCursor();
	Terminal::Clear(0x0F);

	const char* str = "Umbrella OS (C) 2022 Florian Schumacher";
	char tmp[512];
	memset(tmp, 0, sizeof(tmp));
	memcpy(str, tmp, strlen(str));
	Terminal::PutString(0, 0, tmp);
}