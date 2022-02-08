#pragma once
#include "DllMain.h"
#include "Singleton.h"
#include <imgui.h>
#include <set>

namespace Draw
{
	class EntityList {
	public:
		void RenderWindow();
	private:
		void GetObjectInfo(WObject* entity);
	};
}