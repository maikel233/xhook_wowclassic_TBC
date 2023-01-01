#include "Globals.h"

bool Globals::isLootWindowOpen()
{
	return (*reinterpret_cast<uintptr_t*>(Offsets::Base + Offsets::IsLootWindowOpen)) != 0L; // 0xB71B48
}
