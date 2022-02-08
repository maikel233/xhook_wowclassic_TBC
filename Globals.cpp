#include "Globals.h"

bool Globals::isLootWindowOpen()
{
	return (*reinterpret_cast<uintptr_t*>(Offsets::Base + 0x3124670)) != 0L; // 0xB71B48
}

