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
		: "memory"
	);
}

int strcmp(const char* str0, const char* str1, UQWORD size)
{
	//TODO: do this in assembly
	for (UQWORD i = 0; i < size; i++)
		if (str0[i] != str1[i])
			return 0;
	return 1;
}

void rmemcpy(const void* start, const void* end, void* dest)
{
	char* beg = (char*)((const char*)start);

	do
	{
		*((char*)dest) = *beg++;
	}
	while (beg <= ((char*)end));
}
