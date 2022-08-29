<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 62176deb1b692053e1f2980e3030a9d759864af6
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
<<<<<<< HEAD
}
=======
}
=======
#include "Memory.h"
>>>>>>> 94924cee4ba14e69d60fddb5621d28f6620e6514
>>>>>>> 62176deb1b692053e1f2980e3030a9d759864af6
