#pragma once
#include "DllMain.h"
#include "Hacks.h"
#include "Lua/GameMethods.h"
#include "nav.h"


class GInterface
{

public:
  //Removed anticrash handler
	static LONG VectoredHandler(EXCEPTION_POINTERS* ExceptionInfo);
	static void Init(HMODULE);
	static void WaitForReload();
	static void Monitor(HMODULE);
};
