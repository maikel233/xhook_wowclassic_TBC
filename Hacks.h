#pragma once
#include "DllMain.h"
#include "Singleton.h"
#include <imgui.h>
#include <set>

namespace WoW
{
	class Hacks {
	public:
		static void FreezeJump();
		static void ModifyJumpHeight();
		static void CTM(C3Vector destination);
		static void StartQualityOfLife();
		static void GExecute_IGFunctions();

		static int ClickToMove(int64_t);
		static int GoToCorpse(int64_t);
		static int fakeTeleport(int64_t);
	};

	class Funcs {
	public:
	/*	static bool IsEntityAlive(WObject* entity);
		static bool IsGhost(Vector3 Corpse);
		static bool InRangeOf(WObject* Entity, const Vector3& v, float distance);
		static void ReleaseSpirit();
		static void ReviveAtCorpse();*/
	};
}