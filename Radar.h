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