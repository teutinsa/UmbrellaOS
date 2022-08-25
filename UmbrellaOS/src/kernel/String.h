#pragma once
#include "Types.h"

void memcpy(const void* src, void* dest, UQWORD size);

UQWORD strlen(const char* str);

void memset(void* dest, BYTE value, UQWORD size);

int strcmp(const char* str0, const char* str1, UQWORD size);

void rmemcpy(const void* start, const void* end, void* dest);