#pragma once
#include "Types.h"

#pragma pack(push, 1)
typedef struct
{
	UQWORD baseAddr;
	UQWORD length;
	UDWORD type;
	UDWORD exAttrib;
} MemMapEntry;
#pragma pack(pop)