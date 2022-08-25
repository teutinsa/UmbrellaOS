#include "Utils.h"
#include "String.h"

#define min(x, y) ((x) < (y) ? (x) : (y))

char* itoa_internal(char* next, UQWORD n)
{
	UQWORD nTrunc = n;

	do
	{
		*--next = '0' + nTrunc % 10;
		nTrunc /= 10;
	}
	while (nTrunc != 0);

	return next;
}

void itoa(QWORD num, char* buffer, UQWORD len)
{
	char tmp[22];
	tmp[21] = '\0';

	char* end = tmp + 21;
	char* next = end;
	if (num < 0)
	{
		next = itoa_internal(next, num);
		*--next = '-';
	}
	else
		next = itoa_internal(next, num);

	memcpy(next, buffer, min(len, (end - next) + 1));
}