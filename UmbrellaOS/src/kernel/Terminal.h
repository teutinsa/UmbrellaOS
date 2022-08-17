#pragma once
#include "Types.h"

class Terminal
{
public:
	static void Clear();
	static void SetCursor(WORD x, WORD y);
	static void HideCursor();
	static void EnableCursor();
};

