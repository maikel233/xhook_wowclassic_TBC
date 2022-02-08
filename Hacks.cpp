#include "Hacks.h"

bool Settings::Hacks::Movement::JumpState = false;
bool Settings::Hacks::Movement::SuperSlowFall = false;
bool Settings::Hacks::Movement::JumpStatev2 = false;
bool Settings::Hacks::Movement::CTM = false;
int Settings::Hacks::Movement::SuperSlowSleepTime = 20;

namespace WoW
{
	void Hacks::FreezeJump(WObject* localplayer)
	{

		if (!Settings::Hacks::Movement::JumpState)
			return;

		__try
		{
			float ZAxis = Globals::LocalPlayer->GetUnitPosition().z;

			if (Settings::Hacks::Movement::SuperSlowFall) {
				Sleep(Settings::Hacks::Movement::SuperSlowSleepTime); // Some users will dc on 20ms try a higher number but this will decrease your in air time. I should probably check in jump state + max jump alt?
				localplayer->StopFall = 824;
				return;
			}

			if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
				Sleep(50);

				if (localplayer->GetUnitPosition().z == ZAxis)
					return;

				if (localplayer->GetUnitPosition().z != ZAxis) {
					Sleep(600);
					localplayer->StopFall = 824;
				}
			}
		}
		__except (Utils::filterException(GetExceptionCode(), GetExceptionInformation())) {
			printf("[!] Freeze jump caused a error!\n");

		}
	}

	void Hacks::ModifyJumpHeight(WObject* localplayer)
	{
		//Useless dc at jump...
		if (!Settings::Hacks::Movement::JumpStatev2)
			return;

		/*if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			localplayer->StartofJumpHeight = Settings::Hacks::Movement::jumpHeight;
		}*/

	}

	void Hacks::CTMLP(WObject* OBJDestination)
	{
/*		if (!Utils::ValidCoord(OBJDestination))
			return*/;

		if ((OBJDestination->GetUnitPosition().x == 0 && OBJDestination->GetUnitPosition().y == 0 && OBJDestination->GetUnitPosition().z == 0) || Utils::GetDistance(OBJDestination->GetUnitPosition()) >= 100000)
			return;

		WObject* LocalPlayer = Globals::LocalPlayer;
		GameMethods::ClickToMove(LocalPlayer->Ptr(), OBJDestination->GetUnitPosition());
		WoWObjectManager::SetHardwareEvent();
	}

	void Hacks::CTM(Vector3 destination)
	{
		if ((destination.x == 0 && destination.y == 0 && destination.z == 0) || Utils::GetDistance(destination) >= 100000)
			return;

		WObject* LocalPlayer = Globals::LocalPlayer;
		GameMethods::ClickToMove(LocalPlayer->Ptr(), destination);
		WoWObjectManager::SetHardwareEvent();
	}

	static bool once;
	void Hacks::GExecute_IGFunctions()
	{

		WObject* localplayer = (WObject*)Globals::LocalPlayer;
		if (!localplayer) {
			return;
		}

		Hacks::FreezeJump(localplayer);
		Hacks::ModifyJumpHeight(localplayer);

		if (!Settings::Hacks::Movement::TogglePlayerState)
			return;

		if (Settings::Hacks::Movement::TogglePlayerState) {
			once = true;

			if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::Ground)
				localplayer->MovementFlags = MovementFlags::MOVEMENTFLAG_NONE;
			else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::Swimming)
				localplayer->MovementFlags = MovementFlags::MOVEMENTFLAG_SWIMMING;
			else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::UnderWaterWalking)
				localplayer->MovementFlags = MovementFlags::MOVEMENTFLAG_WALKING;								//Yes
			else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::WaterWalking)
				localplayer->MovementFlags = MovementFlags::MOVEMENTFLAG_WATERWALKING; //Below this one are useless used for testing.	
			else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::FallingSlow)
				localplayer->MovementFlags = MovementFlags::MOVEMENTFLAG_FALLING_FAR;
			else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::CanFly)
				localplayer->MovementFlags = MovementFlags::MOVEMENTFLAG_FALLING_SLOW;
			else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::DisableCollision)
				localplayer->MovementFlags = MovementFlags::MOVEMENTFLAG_HOVER;
			else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::Root)
				localplayer->MovementFlags = MovementFlags::MOVEMENTFLAG_FLYING;
			else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::Loggedoff) // Antistun?
				localplayer->MovementFlags = MovementFlags::MOVEMENTFLAG_PITCH_UP;
			else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::DisableGravity)
				localplayer->MovementFlags = MovementFlags::MOVEMENTFLAG_ASCENDING;
		}
		else {
			if (once) {
				localplayer->MovementFlags = 0x3F8000003FEE38E4; // Walking state
				once = false; // After any movement wow should change the value to its original.
			}
		}
	}

	int Hacks::GoToCorpse(int64_t luaState) {
		//Kinda useless now because dc at tele...
		if (!Globals::LocalPlayer)
			return 1;
		int corpseMapID = *reinterpret_cast<int*>(Offsets::CorpseMapID);
		printf("Corpse located at: x %f y %f z %f MapID: %i \n", Globals::CorpsePos.x, Globals::CorpsePos.y, Globals::CorpsePos.z, corpseMapID);

		if (Globals::CorpsePos.x != 0 && Globals::CorpsePos.y != 0 && Globals::CorpsePos.z != 0) {
			Globals::LocalPlayer->GetUnitPositionModify.x = Globals::CorpsePos.x;
			Globals::LocalPlayer->GetUnitPositionModify.y = Globals::CorpsePos.y;
			Globals::LocalPlayer->GetUnitPositionModify.z = Globals::CorpsePos.z;
		}
		else {
			printf("Corpse not found!!!\n");
		}
		return 1;
	}

	int Hacks::fakeTeleport(int64_t luastate) {
		//Kinda useless now because dc at tele...
		if (!Globals::LocalPlayer)
			return 1;

		if (Settings::Hacks::Movement::TeleportBack) {
			Globals::LocalPlayer->GetUnitPosition() = Settings::Hacks::Movement::PrevPos; // For now 
			Settings::Hacks::Movement::TeleportBack = false;
			return 1;
		}
		else {
			Settings::Hacks::Movement::PrevPos = Globals::LocalPlayer->GetUnitPosition();
		}
		Globals::LocalPlayer->GetUnitPosition() = Settings::Hacks::Movement::NextPos;  // For now

		return 1;
	}
};
