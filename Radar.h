#pragma once
#include "DllMain.h"
#include "Singleton.h"
#include <imgui.h>
#include <set>
namespace Radar
{
	enum EntityShape_t : int
	{
		SHAPE_CIRCLE,
		SHAPE_SQUARE,
		SHAPE_TRIANGLE,
		SHAPE_TRIANGLE_UPSIDEDOWN
	};
	//ImColor GetRadarPlayerColor(WObject* player, bool visible);
	void RenderWindow();
};