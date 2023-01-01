#pragma once
#include "DllMain.h"
#include "Singleton.h"
#include <imgui.h>
#include <set>

namespace Draw
{
	class Radar {
	public:
		void RenderWindow();
		void DrawObj(WObject* localplayer, WObject* entity, ImColor color, ImDrawList* draw_list, ImVec2 winpos, ImVec2 winsize);
	private:
		float RadianToDegree(float Rotation);
		enum EntityShape_t : int
		{
			SHAPE_CIRCLE,
			SHAPE_SQUARE,
			SHAPE_TRIANGLE,
			SHAPE_TRIANGLE_UPSIDEDOWN
		};
	};
}
