#pragma once

#include "DllMain.h"
#include "Singleton.h"
#include <imgui.h>

namespace Draw
{
	class Renderer :
		public Singleton<Renderer>
	{
		friend class Singleton<Renderer>;
	protected:
		Renderer();
		~Renderer();
	public:
		void Initialize();
		void BeginScene();
		void EndScene();
		void InitBeforeDrawing();
		void DrawObjects(WObject* Entity, HealthColorVar Color);

	private:
		ImFont* m_pFont;
	};


}
#define g_sRenderer RangeMachine::Renderer::GetInstance()