#pragma once


// Standard imports
#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_set>
#include <mutex>

#include "detours.h"

#include <iostream>
#include <fstream>
#include "detours.h"

#include "IncludeHeaders.h"

//ImGUI imports
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_internal.h"

#include "Menu.h"

#include <stdio.h>
#include <vector>

#include <iostream>
#include <vector>
#include <TlHelp32.h>
#include <tchar.h>

#include "Lua/LuaBase.h"
#include "Lua/LuaScript.h"
#include "Renderer.h"
#include "Singleton.h"
#include "Offsets.h"




namespace WoW
{
	namespace Funcs
	{

		bool IsEntityAlive(WObject* entity);
		bool IsGhost(Vector3 Corpse);
		bool InRangeOf(WObject* Entity, const Vector3& v, float distance);
		static void ReleaseSpirit();
		static void ReviveAtCorpse();

	};
}
