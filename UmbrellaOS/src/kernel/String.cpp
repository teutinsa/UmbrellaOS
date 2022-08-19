#include "String.h"

void memcpy(const void* src, void* dest, UQWORD size)
{
	__asm volatile (
		"cld\n"
		"rep movsb\n"
		:
		: "S"(src), "D"(dest), "c"(size)
		: "memory"
	);
}

UQWORD strlen(const char* str)
{
	UQWORD len = 0UL;
	while (str[len] != '\0') len++;
	return len;
}

void memset(void* dest, BYTE value, UQWORD size)
{
	__asm volatile (
		"cld\n"
		"rep stosb\n"
		:
		: "D"(dest), "a"(value), "c"(size)
	);
}