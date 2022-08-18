#pragma once
#include "Types.h"

class Terminal
{
public:
	static void Clear();
	static void SetCursor(WORD x, WORD y);
	static void HideCursor();
	static void EnableCursor(WORD start, WORD end);
	static void PutString(WORD x, WORD y, const char* str, BYTE color);
};

