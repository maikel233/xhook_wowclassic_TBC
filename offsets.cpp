#include "offsets.h"

void* AddOffset(void* p, int offset)
{
	return (void*)((uintptr_t)p + offset);
}
