#pragma once
#include "DllMain.h"

namespace WoW
{
	class Hacks {
	public:
		static void FreezeJump(WObject* localplayer);
		static void ModifyJumpHeight(WObject* localplayer);
		static void CTM(Vector3 destination);
		static void CTMLP(WObject* OBJDestination);
		static void GExecute_IGFunctions();
		static int GoToCorpse(int64_t);
		static int fakeTeleport(int64_t);
	};
}