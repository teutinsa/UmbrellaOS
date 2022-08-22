#include "Terminal.h"
#include "IO.h"
#include "String.h"

void Terminal::Clear(BYTE color)
{
	WORD i = 0;
	while (i < VGA_SIZE)
	{
		VGA_MEM[i++] = 0;
		VGA_MEM[i++] = color;
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
	volatile char* vidmem = VGA_MEM + (y * VGA_STRIDE + x * VGA_ELMSIZE);
	while (*str != '\0')
	{
		*vidmem++ = *str++;
		*vidmem++ = color;
	}
}

WORD Terminal::GetCursorPos()
{
	WORD pos = 0;
	outb(0x3D4, 0x0F);
	pos |= inb(0x3D5);
	outb(0x3D4, 0x0E);
	pos |= ((WORD)inb(0x3D5)) << 8;
	return pos;
}

void Terminal::Print(const char* str, BYTE color)
{
	WORD curPos = GetCursorPos();
	WORD curX = curPos % VGA_WIDTH;
	WORD curY = curPos / VGA_WIDTH;
	UQWORD len = strlen(str);
	for (UQWORD i = 0; i < len + 1; i++)
	{
		if (curX >= VGA_WIDTH)
		{
			curY++;
			curX = 0;
		}

		if (curY >= VGA_HEIGHT)
		{
			curY = 24;
			Scroll(color);
		}

		WORD pos = curY * VGA_WIDTH + curX;

		switch (str[i])
		{
		case '\n':
			curY++;
			break;

		case '\r':
			curX = 0;
			break;

		case '\0':
			VGA_MEM[pos * VGA_ELMSIZE] = str[i];
			VGA_MEM[(pos * VGA_ELMSIZE) + 1] = color;
			break;

		default:
			VGA_MEM[pos * VGA_ELMSIZE] = str[i];
			VGA_MEM[(pos * VGA_ELMSIZE) + 1] = color;
			curX++;
			break;
		}
	}

	SetCursor(curX, curY);
}

void Terminal::NewLine()
{
	WORD curPos = GetCursorPos();
	WORD curX = curPos % VGA_WIDTH;
	WORD curY = curPos / VGA_WIDTH;


}

void Terminal::Scroll(BYTE color)
{
	for (BYTE i = 1; i < VGA_HEIGHT; i++)
	{
		memcpy(const_cast<const char*>(VGA_MEM + VGA_STRIDE * i), const_cast<char*>(VGA_MEM + VGA_STRIDE * (i - 1)), VGA_STRIDE);
		if (i == VGA_HEIGHT - 1)
			memset(const_cast<char*>(VGA_MEM + VGA_STRIDE * i), 0, VGA_STRIDE);
	}
}