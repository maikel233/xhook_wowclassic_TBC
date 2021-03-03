#pragma once
#include "DllMain.h"
#include "Singleton.h"
#include <imgui.h>
#include <set>

namespace ShowEntityList
{
	void GetObjectInfo(WObject* entity);
	void RenderWindow();
}
