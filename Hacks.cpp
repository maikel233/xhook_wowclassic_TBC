#include "Hacks.h"
#include "WowTypes.h"
bool Settings::Hacks::Movement::JumpState = false;
bool Settings::Hacks::Movement::SuperSlowFall = false;
bool Settings::Hacks::Movement::JumpStatev2 = false;
bool Settings::Hacks::Movement::CTM = false;

int Settings::Hacks::Movement::SuperSlowSleepTime = 20;

namespace WoW
{
	//bool Funcs::IsGhost(Vector3 Corpse)
	//{
	//	if (Corpse.x != 0 || Corpse.y != 0 || Corpse.z != 0)
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}

	//bool Funcs::IsEntityAlive(WObject* entity)
	//{
	//	int TypeID = entity->GetType();

	//	if (TypeID == CGPlayer || TypeID == CGUnit || TypeID == CGActivePlayer)
	//	{
	//		if (entity->sUnitField->Health > 0)
	//			return false;
	//	}
	//	return true;
	//}

	////bool Funcs::InRangeOf(WObject* Entity, const C3Vector& v, float distance)
	////{
	////	return Entity->GetUnitPosition().Distance(v) <= distance;
	////}

	//void Funcs::ReleaseSpirit()
	//{
	//	//GameMethods::Execute("RepopMe()");

	//}

	//void Funcs::ReviveAtCorpse()
	//{
	//	//GameMethods::Execute("RetrieveCorpse()");
	//}

	void Hacks::StartQualityOfLife()
	{

		if (!Settings::Hacks::Movement::CTM)
			return;

		__try
		{
			WObject* LocalPlayer = (WObject*)LuaScript::ActivePlayer;


			//if (WoW::Funcs::IsEntityAlive(LocalPlayer))
			//{
			//	Sleep(1250);
			//	printf("[+] Releasing Spirit!\n");
			//	WoW::Funcs::ReleaseSpirit(); //Spamming this will crash your game.
			//}


			Vector3 Corpse;
			Corpse.x = *reinterpret_cast<float*>(Offsets::Corpsex);
			Corpse.y = *reinterpret_cast<float*>(Offsets::Corpsey);
			Corpse.z = *reinterpret_cast<float*>(Offsets::Corpsez);
			if (Corpse.x != 0 && Corpse.y != 0 && Corpse.z != 0)
			{
				/*if (Funcs::IsGhost(Corpse))
				{
					if (Funcs::InRangeOf(LocalPlayer, Corpse, 20.0))
					{
						Sleep(1250);
						printf("[+] Reviving!\n");
						WoW::Funcs::ReviveAtCorpse();
						C2M_Test(false, Corpse);
					}
					else
					{
						printf("[+] Walking to Corpse\n");
						C2M_Test(true, Corpse);
					}
				}*/
			}
			else
			{
				//Continue...
			}
		}
		__except (Utils::filterException(GetExceptionCode(), GetExceptionInformation())) {
			printf("[!] Auto Mode Exception Caught!\n");
			LuaScript::ReInitObjMgr();
		}
	}

	void Hacks::FreezeJump()
	{

		if (!Settings::Hacks::Movement::JumpState)
			return;

		if (!LuaScript::ActivePlayer)
			return;

		__try
		{
			float ZAxis = LuaScript::ActivePlayer->GetUnitPosition().z;

			if (Settings::Hacks::Movement::SuperSlowFall)
			{
				Sleep(Settings::Hacks::Movement::SuperSlowSleepTime); // Some users will dc on 20ms try a higher number but this will decrease your in air time. I should probably check in jump state + max jump alt?
				LuaScript::ActivePlayer->StopFall = 824;
				return;
			}

			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				Sleep(50);

				if (LuaScript::ActivePlayer->GetUnitPosition().z == ZAxis)
					return;

				if (LuaScript::ActivePlayer->GetUnitPosition().z != ZAxis)
				{
					Sleep(600);
					LuaScript::ActivePlayer->StopFall = 824;
					printf("test\n");
				}
			}
		}
		__except (Utils::filterException(GetExceptionCode(), GetExceptionInformation())) {
			printf("[!] WoW Error!\n");

		}
	}

	float test;
	void Hacks::ModifyJumpHeight()
	{
		//Useless dc at jump...
		if (!Settings::Hacks::Movement::JumpStatev2)
			return;


		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			LuaScript::ActivePlayer->JumpHeight = Settings::Hacks::Movement::jumpHeight;			
		}
		
	}

	void Hacks::CTM(C3Vector destination)
	{
		WObject* LocalPlayer = LuaScript::ActivePlayer;

		if (LocalPlayer->CurrentSpeed != 0)
			return;

		//Vector destination = Unit->GetUnitPosition();
		GameMethods::ClickToMove(LocalPlayer->Ptr(), destination);

		LuaScript::SetHardwareEvent();
	}

	static bool once;
	bool Init = false;
	void Hacks::GExecute_IGFunctions()
	{
		//if (!LuaScript::InGame())
		//{
		//	printf("Not Ingame\n");
		//	
		
	

		if (!GameMethods::ObjMgrIsValid(0))
			return;

		//LuaScript::ReInitObjMgr(); // Loop ObjMgr
	
		Hacks::FreezeJump();
		Hacks::ModifyJumpHeight();
		Hacks::StartQualityOfLife();

			if (!Settings::Hacks::Movement::TogglePlayerState)
				return;

			if (Settings::Hacks::Movement::TogglePlayerState) {
				once = true;


				if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::Ground)
					LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_SWIMMING;								//Yes
				else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::Swimming)
					LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_FALLING;			//Yes
				else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::UnderWaterWalking)
					LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_SPLINE_ELEVATION;								//Yes
				else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::WaterWalking)
					LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_PITCH_DOWN;		//Disconnect
				else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::FallingSlow)
					LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_FALLING_FAR;		//Nope
				else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::CanFly)
					LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_FALLING_SLOW;				//Nope
				else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::DisableCollision)
					LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_HOVER; // Nope
				else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::Root)
					LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_FLYING;
				else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::Loggedoff)
					LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_PITCH_UP;
				else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::DisableGravity)
					LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_ASCENDING;
			} 
			else {
				if (once)
					LuaScript::ActivePlayer->Collision_StateHack = 0x3F8000003FEE38E4; // Walking state
					once = false; // After any movement wow should change the value to its original.
			}
	}



	int Hacks::GoToCorpse(int64_t luaState)
	{
		if (!LuaScript::ActivePlayer)
			return 1;

		float corpseXPos = *reinterpret_cast<float*>(Offsets::Corpsex);
		float corpseYPos = *reinterpret_cast<float*>(Offsets::Corpsey);
		float corpseZPos = *reinterpret_cast<float*>(Offsets::Corpsez);

		int corpseMapID = *reinterpret_cast<int*>(Offsets::CorpseMapID);

		printf("Corpse located at: x %f y %f z %f MapID: %i \n", corpseXPos, corpseYPos, corpseZPos, corpseMapID);

		if (corpseXPos != 0 && corpseYPos != 0 && corpseZPos != 0)
		{
			LuaScript::ActivePlayer->GetUnitPositionModify.x = corpseXPos;
			LuaScript::ActivePlayer->GetUnitPositionModify.y = corpseYPos;
			LuaScript::ActivePlayer->GetUnitPositionModify.z = corpseZPos;
		}
		else
		{
			printf("Corpse not found!\n");
		}
		return 1;
	}

	int Hacks::fakeTeleport(int64_t luastate)
	{
		if (!LuaScript::ActivePlayer)
			return 1;

		if (Settings::Hacks::Movement::TeleportBack)
		{
			LuaScript::ActivePlayer->GetUnitPosition() = Settings::Hacks::Movement::PrevPos; // For now 
			Settings::Hacks::Movement::TeleportBack = false;
			return 1;
		}
		else
		{
			Settings::Hacks::Movement::PrevPos = LuaScript::ActivePlayer->GetUnitPosition();
		}

		LuaScript::ActivePlayer->GetUnitPosition() = Settings::Hacks::Movement::NextPos;  // For now

		return 1;
	}

	//int Hacks::ClickToMove(int64_t luaState)
	//{
	//	if (!LuaScript::ActivePlayer)
	//		return 1;

	//	int x = GameMethods::ToNumber(luaState, 1);
	//	int y = GameMethods::ToNumber(luaState, 2);
	//	int z = GameMethods::ToNumber(luaState, 3);

	//	Vector3 position = Vector3(x, y, z);

	//	GameMethods::ClickToMove(LuaScript::ActivePlayer->Ptr(), position);

	//	LuaScript::SetHardwareEvent();

	//	return 1;
	//}



};