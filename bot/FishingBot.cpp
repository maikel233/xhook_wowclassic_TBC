#include "FishingBot.h"

bool Settings::bot::Refresh = false;

bool Settings::bot::fishing::Enabled = false;
bool Settings::bot::fishing::IsFishing = false;
bool Settings::bot::fishing::PoolDetection = false;
bool Confirm = false;

float speed = 1;

namespace WoW {


	C3Vector GetMinNodeVec(string nodeName)
	{
		auto minDist = INT_MAX;
		auto position = LuaScript::ActivePlayer->GetUnitPosition();

		WObject* closestObject = nullptr;

		for (auto o : LuaScript::Objects)
		{
			if (string(o->GetObjectName()) == nodeName && o->GetType() == TypeId::CGGameObject) //&& o->GetGatherStatus() == 1)
			{
				printf(o->GetObjectName());
				auto destQuery = o->GetUnitPosition();
				float dist = sqrt(pow(destQuery.x - position.x, 2) + pow(destQuery.y - position.y, 2) + pow(destQuery.z - position.z, 2) * 1.0);
				if (dist < minDist)
				{
					minDist = dist;
					closestObject = o;
				}
			}
		}

		if (closestObject)// && //closestObject->GetGatherStatus() == 1)
			return closestObject->GetObjectNamePosition();
		else
			return C3Vector(0.0, 0.0, 0.0);
	}

	C3Vector GetClosestPool()
	{
		auto destination = GetMinNodeVec("Oily Blackmouth School");

		if (destination.x != 0 && destination.y != 0)
		{
			printf("X:%f Y:%f Z:%f\n", destination.x, destination.y, destination.z);
			return destination;
		}

		return C3Vector(0,0,0);
	}

	int FishBot::GetFishingLevel()
	{
		if (GameMethods::IsSpellKnown(FishBot::FishingLevels::master))
			return FishBot::FishingLevels::master;
		else if (GameMethods::IsSpellKnown(FishBot::FishingLevels::artisan))
			return FishBot::FishingLevels::artisan;
		else if (GameMethods::IsSpellKnown(FishBot::FishingLevels::expert))
			return FishBot::FishingLevels::expert;
		else if (GameMethods::IsSpellKnown(FishBot::FishingLevels::journeyman))
			return FishBot::FishingLevels::journeyman;
		else if (GameMethods::IsSpellKnown(FishBot::FishingLevels::apprentice))
			return FishBot::FishingLevels::apprentice;
	}

	int FishSpellID;
	void FishBot::Fish()
	{
	/*	__try
		{*/
		if (LuaScript::Objects.empty())
			return;

		if (!LuaScript::ActivePlayer)
			return;

		//if (!LuaScript::InGame())
		//	return;

		if (Utils::IsEntityAlive(LuaScript::ActivePlayer))
			return;
		

		if (LuaScript::ActivePlayer->CurrentSpeed != 0)
		{
			printf("[+] Player is moving\n");
			Settings::bot::fishing::IsFishing = false;
			std::this_thread::sleep_for(std::chrono::seconds(3)); 
		}

		if (!Settings::bot::fishing::IsFishing)
		{		
			if (LuaScript::ActivePlayer->CurrentSpeed != 0)
				return;

			FishSpellID = GetFishingLevel();

			int32_t spellSlot = GameMethods::FindSlotBySpellId(FishSpellID);
			if (!spellSlot)
				return;
		
			Confirm = true; // This is required else castspell will spam every tick. (Try calling Fishbot in the DXHook and not in DllMain probably wont need this bypass..)
			Settings::bot::fishing::IsFishing = true;
			GameMethods::CastSpell(spellSlot, LuaScript::ActivePlayer->GetGuid());		
			printf("[+] Casting Spell %i\n", FishSpellID);
			LuaScript::SetHardwareEvent();	
		}


		if (LuaScript::ActivePlayer->sUnitField->SpellID == FishSpellID)
		{
			if (Confirm)
			{ //EnumObj
				Settings::bot::Refresh = true;
				Confirm = false;
			}
		}

			
		for (auto o : LuaScript::Objects)
		{
			if (!Settings::bot::fishing::IsFishing)
				continue;

			if (!o->isValid())
				continue;

			if (!Utils::ValidCoord(o))
				continue;

			if (!o->isGameObject())
				continue;

			if (strcmp(o->GetObjectName(), "Fishing Bobber") == 0 && *o->GetOwner() == *LuaScript::ActivePlayer->GetGuid() && o->GetAnimStatus())
			{
			
				//Catch them all
				printf("[+] %s\n", o->GetObjectName());
				std::cout << "[+] Fishing Bobber ptr:" << std::hex << o << std::endl;
				Vector2 FishPos = WoW::camera::WorldToScreenv2(o->GetUnitPosition());
				printf("[+] Fish Found, Clickat@ [%f,%f]\n", FishPos.x, FishPos.y);
				o->Interact();
				LuaScript::SetHardwareEvent();
				std::this_thread::sleep_for(std::chrono::seconds(3)); //Replace this with if(LootWindow is open) { loot } !lootwindow -> continue...	
				Settings::bot::fishing::IsFishing = false;
			
			}
		}

	//	}
		/*__except (Utils::filterException(GetExceptionCode(), GetExceptionInformation())) {
			printf("[!] Fishingbot Exception Caught!\n");
			
			if (LuaScript::ActivePlayer->sUnitField->SpellID == FishSpellID)
			{
				Settings::bot::fishing::IsFishing = true;
			}
			else
			{
				Settings::bot::fishing::IsFishing = false;
				Settings::bot::fishing::Refresh = true;
			}
		}*/
	}
}
