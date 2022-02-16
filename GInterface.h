#pragma once
#include "DllMain.h"
#include "Hacks.h"
#include "Lua/GameMethods.h"
#include "nav.h"


class GInterface
{

public:
	//Removed anti crash
  //Removed crash warning
	static void Init(HMODULE);
	static void WaitForReload();
	static void Monitor(HMODULE);
};
