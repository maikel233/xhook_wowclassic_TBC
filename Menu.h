#pragma once

#include "stdafx.h"
#include "DllMain.h"
#include "Settings/Settings.h"

namespace GMenu
{
	void Menu(bool open);
	const char* MenuTabs[];
	void InitObjmgr();
}

inline void SetTooltip(const char* text) {
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("%s", text);
}
