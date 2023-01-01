#include "FishingBot.h"

bool Settings::bot::Refresh = false;
bool Settings::bot::fishing::Enabled = false;
bool Settings::bot::fishing::IsFishing = false;
bool Settings::bot::fishing::PoolDetection = false;

namespace WoW {


	//Vector3 GetMinNodeVec(string nodeName)
	//{
	//	auto minDist = INT_MAX;
	//	auto position = Vector3(0, 0, 0);

	//	WObject* closestObject = nullptr;


	//	for (auto& [guid, o] : )
	//	{
	//		if (o->GetType() == ActivePlayer)
	//			position = o->GetObjectPosition();

	//		if (string(o->GetObjectName()) == nodeName && o->GetType() == TypeId::GameObject && o->GetGatherStatus() == 1)
	//		{
	//			auto destQuery = o->GetObjectPosition();
	//			float dist = sqrt(pow(destQuery.x - position.x, 2) + pow(destQuery.y - position.y, 2) + pow(destQuery.z - position.z, 2) * 1.0);
	//			if (dist < minDist)
	//			{
	//				minDist = dist;
	//				closestObject = o;
	//			}
	//		}
	//	}

	//	if (closestObject && closestObject->GetGatherStatus() == 1)
	//		return closestObject->GetObjectDisplayHeight();
	//	else
	//		return Vector3(0.0, 0.0, 0.0);
	//}
	//

	int FishBot::GetFishingLevel() {
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

		WObject* LocalPlayer = (WObject*)Globals::LocalPlayer;
		if (!LocalPlayer) {
			return;
		}

		int FishSpellID = GetFishingLevel();
		
		if (Settings::bot::fishing::IsFishing && LocalPlayer->GetChannelID() != FishSpellID) {
			Settings::bot::fishing::IsFishing = false;
		}

		if (LocalPlayer->IsPlayerMoving()) {
			printf("[+] Player is moving\n");
			Settings::bot::fishing::IsFishing = false;
			return;
		}

		if (!Settings::bot::fishing::IsFishing) {
			int32_t spellSlot = GameMethods::FindSlotBySpellId(FishSpellID);
			if (!spellSlot)
				return;

			GameMethods::Spell_C_CastSpell(spellSlot, LocalPlayer->GetGuid());
			printf("[+] Casting Spell %i\n", FishSpellID);
			WoWObjectManager::SetHardwareEvent();
			Settings::bot::fishing::IsFishing = true;
		}

		for (auto& [guid,o] : Globals::Objects)
		{
			if (!Settings::bot::fishing::IsFishing)
				continue;

			if (!o->isValid())
				continue;

			if (!Utils::ValidCoord(o))
				continue;

			if (!o->IsGameObject())
				continue;

			if (strcmp(o->GetObjectName(), "Fishing Bobber") == 0 && *o->GetOwner() == *LocalPlayer->GetGuid() && o->GetAnimStatus())
			{
				//Catch them all
				printf("[+] %s\n", o->GetObjectName());
				std::cout << "[+] Fishing Bobber ptr:" << std::hex << o << std::endl;
				o->Interact();
				WoWObjectManager::SetHardwareEvent();

				if (Globals::isLootWindowOpen()) {
					printf("[+] Loot Window is open!\n");
					Settings::bot::fishing::IsFishing = false;
					WoWObjectManager::CycleObjects(true); // Refresh Vector
					return;
				}
			}
		}
	}
}
