#pragma once
#include "Types.h"

enum class RegionType : UDWORD
{
	Usable = 1,
	Reserved = 2,
	ACPI_Reclaimable = 3,
	ACPI_NVS = 4,
	BadMemory = 5
};

#pragma pack(push, 1)
union ExtendedAttributes
{
	struct
	{
		UDWORD ignore : 1;
		UDWORD nonVolatile : 1;
		UDWORD unused : 30;
	};
	UDWORD value;
};

struct MemMapEntry
{
	UQWORD baseAddr;
	UQWORD length;
	RegionType type;
	ExtendedAttributes exAttrib;
};
#pragma pack(pop)