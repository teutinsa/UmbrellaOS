#include "Types.h"
#include "Terminal.h"

extern "C" void kmain(void* memmap)
{
	Terminal::HideCursor();
	Terminal::Clear();
}