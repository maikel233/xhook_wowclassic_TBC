#pragma once

#include "DllMain.h"
#include "Singleton.h"
#include <imgui.h>
#include <set>

namespace Draw
{
	/*namespace chrono = std::chrono;*/
	using clock = chrono::high_resolution_clock;
	using duration = chrono::duration<std::int64_t, std::milli>;
	using time_point = chrono::time_point<clock>;


	class InfoWindow {
	public:
		void RenderWindow();
	};
}