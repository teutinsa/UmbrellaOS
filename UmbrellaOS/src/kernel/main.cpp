#include "Types.h"
#include "Terminal.h"

extern "C" void kmain(void* memmap)
{
	Terminal::HideCursor(); //TODO: Look into why this is not working!
	Terminal::Clear();
}