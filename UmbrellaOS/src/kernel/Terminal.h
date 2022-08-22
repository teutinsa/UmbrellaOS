#pragma once
#include "Types.h"

#define VGA_MEM reinterpret_cast<volatile char*>(0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ELMSIZE 2
#define VGA_STRIDE (VGA_WIDTH * VGA_ELMSIZE)
#define VGA_SIZE (VGA_STRIDE * VGA_HEIGHT)

class Terminal
{
public:
	static void Clear(BYTE color = 0x0F);
	static void SetCursor(WORD x, WORD y);
	static void HideCursor();
	static void EnableCursor(WORD start, WORD end);
	static void PutString(WORD x, WORD y, const char* str, BYTE color);
	static WORD GetCursorPos();
	static void Print(const char* str, BYTE color);
	static void NewLine();
	static void Scroll(BYTE color);
};

