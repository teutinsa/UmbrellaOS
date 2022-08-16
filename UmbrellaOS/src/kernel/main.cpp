#include "types.h"

extern "C" void kmain(void* memmap)
{
	volatile char* vidMem = reinterpret_cast<volatile char*>(0xB8000);
	vidMem[0] = 'K';
	vidMem[1] = 15;
}