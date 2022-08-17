#include "Terminal.h"

#define VGA_MEM reinterpret_cast<volatile char*>(0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_STRIDE (VGA_WIDTH * 2)
#define VGA_SIZE (VGA_STRIDE * VGA_HEIGHT)

inline void outb(BYTE value, WORD port)
{
	__asm volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}

inline BYTE inb(WORD port)
{
	BYTE value;
	__asm volatile ("inb %1, %0" : "=a" (value) : "Nd" (port));
	return value;
}

void Terminal::Clear()
{
	WORD i = 0;
	while (i < VGA_SIZE)
	{
		VGA_MEM[i++] = 0;
		VGA_MEM[i++] = 0x0F;
	}
	SetCursor(0, 0);
}

void Terminal::SetCursor(WORD x, WORD y)
{
}

void Terminal::HideCursor()
{
	outb(0x03D4, 0x0A);
	outb(0x03D5, 0x20);
}

void Terminal::EnableCursor()
{
}