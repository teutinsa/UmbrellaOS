<<<<<<< HEAD
#include "Memory.h"
#include "Utils.h"
#include "Terminal.h"

//PageInfo pageInfos[1024];
//UQWORD pageCount = 0;

void InitPages(const MemMapEntry* entry)
{
	//pageCount = entry->length / 4096;
	
}

const PageInfo* RequestPage()
{
	return (const PageInfo*)NULL;
}

void FreePage(const PageInfo* page)
{
}

void* VirtualAlloc(UQWORD size)
{
	return NULL;
}

void VirtualFree(void* block)
{
}
=======
#include "Memory.h"
>>>>>>> 94924cee4ba14e69d60fddb5621d28f6620e6514
