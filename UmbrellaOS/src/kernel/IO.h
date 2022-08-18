#pragma once
#include "Types.h"

static inline void outb(WORD port, BYTE value)
{
	__asm volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}

static inline BYTE inb(WORD port)
{
	BYTE value;
	__asm volatile ("inb %1, %0" : "=a" (value) : "Nd" (port));
	return value;
}