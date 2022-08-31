#include "Types.h"
#include "MemMap.h"

#define OWNER_ID_KERNEL = 0x4B524E4C//KRNL

#define MEMMAP_TYPE_USABLE 1
#define MEMMAP_TYPE_RESERVED 2
#define MEMMAP_TYPE_ACPI_RECLAIMABLE 3
#define MEMMAP_TYPE_ACPI_NVS 4

typedef enum
{
	PageState_Free = 0x46524545,	//FREE
	PageState_Used = 0x55534544,	//USED
	PageState_Reserved = 0x52535644	//RSVD
}  PageState;

#pragma pack(push, 1)
typedef struct
{
	PageState state;
	UDWORD ownerId;
} PageHeader;
#pragma push(pop)

typedef struct
{
	PageHeader* header;
	UQWORD base;
	UQWORD start;
	UQWORD length;
} PageInfo;

void InitPages(const MemMapEntry* entry);
const PageInfo* RequestPage();
void FreePage(const PageInfo* page);

void* VirtualAlloc(UQWORD size);
void VirtualFree(void* block);