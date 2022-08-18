#include "Types.h"
#include "Terminal.h"

extern "C" void kmain(void* memmap)
{
	Terminal::HideCursor();
	Terminal::Clear();
	Terminal::PutString(0, 0, "Umbrella OS (C) 2022 Florian Schumacher", 0x0F);
}