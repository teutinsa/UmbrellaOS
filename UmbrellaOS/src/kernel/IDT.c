#include "IDT.h"
#include "Terminal.h"

static IDTR idtr;
[[gnu::aligned(16)]] static IDTEntry idt[256];

extern void* isr_stub_table[];

void LoadIDT()
{
	idtr.base = (UQWORD)&idt[0];
	idtr.limit = (UWORD)sizeof(IDTEntry) * 255;

	for (BYTE i = 0; i < 32; i++)
		IdtSetDescriptor(i, isr_stub_table[i], 0x8E);

	__asm volatile (
		"lidt %0\n"
		"sti"
		:
		: "m"(idtr)
	);
}

void ExceptionHandler()
{
	Print("An unsolvable Exception occurred!", 0x0C);
	__asm volatile (
		"cli\n"
		"hlt"
	);
}

void IdtSetDescriptor(BYTE vector, void* isr, BYTE flags)
{
	IDTEntry* entry = &idt[vector];
	entry->isrLow = (UQWORD)isr & 0xFFFF;
	entry->kernelCs = 0x8;
	entry->ist = 0;
	entry->attributes = flags;
	entry->isrMid = ((UQWORD)isr >> 16) & 0xFFFF;
	entry->isrMid = ((UQWORD)isr >> 32) & 0xFFFFFFFF;
	entry->reserved = 0;
}