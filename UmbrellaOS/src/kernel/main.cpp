#include "Types.h"
#include "Terminal.h"
#include "String.h"

extern "C" void kmain(void* memmap)
{
	Terminal::EnableCursor(14, 15);
	Terminal::Clear(0x08);

	Terminal::Print("Umbrella OS (C) 2022\r\n", 0x0F);
}