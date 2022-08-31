#include "Memory.h"
#include "Utils.h"
#include "Terminal.h"

static UQWORD pageCount = 0;

void InitPages(const MemMapEntry* entry)
{
	pageCount = entry->length / 0x1000;
	char buffer[22];
	itoa(pageCount, buffer, sizeof(buffer));
	Print("Estimated Page count: ", 0x0F);
	Print(buffer, 0x0F);
	Print("\r\n", 0x0F);
}

const PageInfo* RequestPage()
{
	return NULL;
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
