#pragma once
#include "Types.h"

#pragma pack(push, 1)
typedef struct
{
	UWORD isrLow;
	UWORD kernelCs;
	BYTE ist;
	BYTE attributes;
	UWORD isrMid;
	UDWORD isrHeight;
	UDWORD reserved;
} IDTEntry;

typedef struct
{
	UWORD limit;
	UQWORD base;
} IDTR;
#pragma pack(pop)

void ExceptionHandler();

void LoadIDT();
