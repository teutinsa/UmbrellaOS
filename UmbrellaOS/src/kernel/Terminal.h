#pragma once
#include "Types.h"

#define VGA_MEM ((volatile char*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ELMSIZE 2
#define VGA_STRIDE (VGA_WIDTH * VGA_ELMSIZE)
#define VGA_SIZE (VGA_STRIDE * VGA_HEIGHT)

void Clear(BYTE color);
void SetCursor(WORD x, WORD y);
void HideCursor();
void EnableCursor(WORD start, WORD end);
void PutString(WORD x, WORD y, const char* str, BYTE color);
WORD GetCursorPos();
void Print(const char* str, BYTE color);
void Scroll(BYTE color);
