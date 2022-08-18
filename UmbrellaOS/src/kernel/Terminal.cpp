#include "Terminal.h"
#include "IO.h"

#define VGA_MEM reinterpret_cast<volatile char*>(0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ELMSIZE 2
#define VGA_STRIDE (VGA_WIDTH * VGA_ELMSIZE)
#define VGA_SIZE (VGA_STRIDE * VGA_HEIGHT)

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
	WORD pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (WORD)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (WORD)((pos >> 8) & 0xFF));
}

void Terminal::HideCursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void Terminal::EnableCursor(WORD start, WORD end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3E0) & 0xE0) | end);
}

void Terminal::PutString(WORD x, WORD y, const char* str, BYTE color)
{
	volatile char* vidmem = VGA_MEM;
	WORD i = 0;
	while (str[i] != '\0')
	{

	}
}