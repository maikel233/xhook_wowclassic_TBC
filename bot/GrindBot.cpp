#include "GrindBot.h"
#include "offsets.h"
//Still contains random crashes needs some love

bool Settings::bot::Grinding::Enabled = false;
bool Settings::bot::Grinding::SkinMobs = false;

const char* Settings::bot::Grinding::FoodName;
const char* Settings::bot::Grinding::DrinkName;

float Settings::bot::Grinding::mRestManaPercent = 40;
float Settings::bot::Grinding::mRestHealthPercent = 40;

vector<string> WoW::GrindBot::mobList;
WObject* Target;

namespace WoW {


	void GrindBot::CleanUp() {
		WoWObjectManager::CycleObjects(true);
		Target = nullptr;
	}

	void SetFacing(Vector3 targetPos) {
		if (!targetPos.zero()) {
			const float PI = acos(-1);
			Vector3 basePos = Globals::LocalPlayer->GetUnitPosition();
			float toFace = atan2(targetPos.y - basePos.y, targetPos.x - basePos.x);
			if (toFace < 0.0f)
				toFace += PI * 2.0f;
			else {
				if (toFace > PI * 2)
					toFace -= (PI * 2.0f);
			}
			GameMethods::FaceTo(Globals::LocalPlayer->Ptr(), toFace);
		}
	}

	std::string GetMobName() {
		for (std::vector<std::string>::iterator t = WoW::GrindBot::mobList.begin(); t != WoW::GrindBot::mobList.end(); t++) {
			return *t;
		}
	}

	WObject* GrindBot::GetClosestMob()
	{
		WoWObjectManager::CycleObjects(true);

		float minDist = INFINITY;
		auto position = Globals::LocalPlayer->GetUnitPosition();
		WObject* closestObject = nullptr;
		printf("[+]closestobj is nullptr\n");
		for (auto& [guid, o] : Globals::Objects)
		{
			printf("[+]2222\n");

			if (o->isValid() && !o->IsDead() && !o->IsTapped() && string(o->GetObjectName()) == GetMobName() && o->GetType() == TypeId::CGUnit)
			{
				printf("[+]4444 \n");
				auto destQuery = o->GetUnitPosition();
				printf("[+]TargetDestination: X: %f Y:%f Z:%f \n", o->GetUnitPosition().x, o->GetUnitPosition().y, o->GetUnitPosition().z);
				float dist = sqrt(pow(destQuery.x - position.x, 2) + pow(destQuery.y - position.y, 2) + pow(destQuery.z - position.z, 2) * 1.0);
				if (dist < minDist) {
					minDist = dist;
					closestObject = o;
				}
			}
		}

		if (nav::GetPath(closestObject))
		{
			printf("[+] 11111111  \n");
			Globals::LocalPlayer->sUnitField->TargetGuid = *closestObject->GetGuid(); // Targets npc
			printf("[+] Closest mob After Guid \n");
			nav::StartNavigator = true;
			printf("[+] After navigator=true \n");
			return closestObject;
		}

		return nullptr;
	}

	WObject* GrindBot::HostileUnit_TargetingUs(CGGuid* NPCGUID) {
		for (auto& [guid, o] : Globals::Objects)
		{
			if (o->isValid() && o->GetType() == TypeId::CGUnit) {
				if (!Utils::IsUnitEnemy(o) && !o->IsDead() && o->GetGuid() != NPCGUID) {
					if (o->sUnitField->TargetGuid == *Globals::LocalPlayer->GetGuid()) {
						printf("[TargetHostile] %s is targeting us!\n", o->GetObjectName());
						Globals::LocalPlayer->sUnitField->TargetGuid = *o->GetGuid(); // Targets npc
						Target = o;
						return o;
					}
				}
			}
		}
		return Target;
	}


	void GrindBot::CastSpell(WObject* Unit, int SpellID) {

		printf("[CASTSPELL] HaveSpellPower\n");
		if (!GameMethods::Spell_C_HaveSpellPower(SpellID))
			return;

		printf("[CASTSPELL] Before GetMinMaxSpellRange\n");
		if (Unit->GetGuid() != Globals::LocalPlayer->GetGuid()) {
			printf("[CASTSPELL] GetMinMaxSpellRange\n");
			float_t min = 0;
			float_t max = 0;
			GameMethods::Spell_C_GetMinMaxSpellRange(SpellID, &min, &max, Unit->GetGuid());
			printf("[CASTSPELL] MaxSpellRange is %f\n", max);
			if (Globals::LocalPlayer->GetUnitPosition().DistanceTo(Unit->GetUnitPosition()) >= max)
				return;
		}

		printf("[CASTSPELL] GetSpellDuration\n");
		int64_t duration = 0, startTime = 0, modRate = 1;
		GameMethods::Spell_C_GetSpellCooldown(SpellID, &duration, &startTime, &modRate);
		int CastDuration = startTime + duration - (int)GameMethods::getCurrentTime();
		//
		//		auto count = (int)WoWObjectManager::getCurrentTime();
		//auto result = start + duration - count;

		if (CastDuration > 0)
			return;

		printf("[CASTSPELL] IsSpellKnown\n");
		if (!GameMethods::IsSpellKnown(SpellID))
			return;

		printf("[CASTSPELL] FindSlotBySpellId\n");
		int32_t spellSlot = GameMethods::FindSlotBySpellId(SpellID);
		if (!spellSlot)
			return;

		if (Unit->GetGuid() != Globals::LocalPlayer->GetGuid()) {
			SetFacing(Unit->GetUnitPosition());
		}

		printf("[CASTSPELL] Casting at %s spell %i\n", Unit->GetObjectName(), SpellID);
		GameMethods::Spell_C_CastSpell(spellSlot, Unit->GetGuid());
		printf("[+] Casting spell %i \n", SpellID);
		WoWObjectManager::SetHardwareEvent();
		printf("[+] SetHardware After casted %i \n", SpellID);
	}

	bool GrindBot::Rest(WObject* LocalPlayer) {

		if ((LocalPlayer->IsDrinking() && LocalPlayer->ManaPercent() < 100) ||
			(LocalPlayer->IsEating() && LocalPlayer->HealthPercent() < 100)) {
			return false;
		}
		else if (LocalPlayer->ManaPercent() < Settings::bot::Grinding::mRestManaPercent)
		{
			if (Settings::bot::Grinding::DrinkName == NULL)
				return false;

			if (LocalPlayer->IsDrinking())
				return false;

			printf("ManaState\n");
			//	DrinkingState
			for (auto& [guid, ItemList] : Globals::Objects) {

				if (!ItemList->isValid())
					continue;

				if (!ItemList->IsItem())
					continue;

				printf("ManaState Entry !\n");
				if (strcmp(ItemList->GetObjectName(), Settings::bot::Grinding::DrinkName) == 0) {
					WObject* Drink = ItemList;
					printf("Drinking: %s", Drink->GetObjectName());
					Drink->UseItem(LocalPlayer->GetGuid());
					return false;
				}
			}
		}
		else if (LocalPlayer->HealthPercent() < Settings::bot::Grinding::mRestHealthPercent)
		{
			if (Settings::bot::Grinding::FoodName == NULL)
				return false;

			if (LocalPlayer->IsEating())
				return false;

			for (auto& [guid, ItemList] : Globals::Objects) {

				if (!ItemList->isValid())
					continue;

				if (!ItemList->IsItem())
					continue;
				printf("Healthstate\n");
				if (strcmp(ItemList->GetObjectName(), Settings::bot::Grinding::FoodName) == 0) {
					WObject* Food = ItemList;
					printf("Eating: %s", Food->GetObjectName());
					Food->UseItem(LocalPlayer->GetGuid());
					return false;
				}
			}
		}
		return true;
	}

	bool GrindBot::Buff(WObject* LocalPlayer) {

		static int RaceID = LocalPlayer->sUnitField->ClassID;
		if (RaceID == WoWClass::Druid) {
			if (!LocalPlayer->pHasAura("Mark of the Wild")) {
				CastSpell(LocalPlayer, 1126);
				return false;
			}
			else if (!LocalPlayer->pHasAura("Thorns")) {
				CastSpell(LocalPlayer, 467);
				return false;
			}
		}
		//else if (RaceID == WoWClass::Paladin) {
		//}
		//else if (RaceID == WoWClass::Priest) {
		//}
		//else if (RaceID == WoWClass::Shaman) {
		//}
		return true;
	}

	int GrindBot::GetSpellID(WObject* LocalPlayer, WObject* Target) {
		//Spellbook? or enum with isknown?
		static int Spell_WrathR1 = 5176;
		static int Spell_MoonFireR1 = 8921;
		static int Spell_RejuvenationR1 = 774;
		static int Spell_HealingTouchR1 = 5185;

		printf("GetSpellID\n");
		if (LocalPlayer->HealthPercent() < 40 && !LocalPlayer->pHasAura("Rejuvenation") && GameMethods::Spell_C_HaveSpellPower(Spell_RejuvenationR1)) {
			printf("Casting: Rejuvenation\n");
			CastSpell(LocalPlayer, Spell_RejuvenationR1);
			return 0;
		}
		else if (LocalPlayer->HealthPercent() < 20 && Target->HealthPercent() > 20 && GameMethods::Spell_C_HaveSpellPower(Spell_HealingTouchR1)) {
			printf("Casting: HealingTouch\n");
			CastSpell(LocalPlayer, Spell_HealingTouchR1);
			return 0;
		}
		else if (Target->HealthPercent() == 100) {
			printf("Spell=Wrath Target is FullHP\n");
			return Spell_WrathR1;
		}
		else if (Target->HealthPercent() < 5 && GameMethods::Spell_C_HaveSpellPower(Spell_MoonFireR1) || !Target->pHasAura("Moonfire") && GameMethods::Spell_C_HaveSpellPower(Spell_MoonFireR1)) {
			printf("Spell=MoonFire\n");
			return Spell_MoonFireR1;
		}
		else if (GameMethods::Spell_C_HaveSpellPower(Spell_WrathR1)) {
			printf("Spell=Wrath\n");
			return Spell_WrathR1; // Return default casting spell
		}
		else
			printf("zero!!!\n");
			return 0;
	}

	void GrindBot::DistCheck(WObject* LocalPlayer, WObject* Target, int SpellID, float DistTo) 
	{
		printf("[CASTSPELL] GetMinMaxSpellRange\n");
		float_t minstop = 0;
		float_t maxstop = 0;
		GameMethods::Spell_C_GetMinMaxSpellRange(SpellID, &minstop, &maxstop, Target->GetGuid());
		printf("[CASTSPELL] After GetMinMaxSpellRange %f %f\n", minstop, maxstop);

		if (!nav::StartNavigator && !LocalPlayer->IsPlayerMoving() && DistTo >= maxstop) {
			bool FindPath = nav::GetPath(Target);
			if (FindPath) {
				nav::StartNavigator = true;
				printf("[DISTCHECK] We are still to far away from the target. Moving to target....\n");
			}
		}
		else if (nav::StartNavigator && WoW::camera::TraceLine(LocalPlayer, Target->GetUnitPosition(), IntersectFlags::LineOfSight)
			&& LocalPlayer->IsPlayerMoving()
			&& DistTo < 30) {

			printf("Distcheck TraceLine\n");
			nav::StartNavigator = false;
			nav::Waypoints.clear(); //Startnavigator=false doesnt clear the vector fast enough maybe because of the tick delay?
			if (nav::Waypoints.empty()) {
				Hacks::CTMLP(LocalPlayer);
			}
		}
	}



	void GrindBot::WalkToTarget(WObject* LocalPlayer, WObject* Target) {
		float DistTo = LocalPlayer->GetUnitPosition().DistanceTo(Target->GetUnitPosition());
		printf("DistoToBody: %f\n", DistTo);
		if (!LocalPlayer->IsPlayerMoving() && DistTo > 6) {
			bool isReachable = nav::GetPath(Target);
			if (isReachable) {
				printf("Walking to Target. DistTo: %f\n", DistTo);
				nav::StartNavigator = true;
			}
			else {
				printf("Cant reach it. DistTo: %f\n", DistTo);
				GrindBot::CleanUp();

			}
		}
		else if (!LocalPlayer->IsPlayerMoving() && DistTo <= 6) {
			nav::StartNavigator = false;
			printf("[+] Target is dead DistTo: %f\n", DistTo);
			if (Target->IsLootable()) {
				Target->Interact();
				return;
			}
			else if (Settings::bot::Grinding::SkinMobs && !Target->IsLootable() && Target->IsSkinnable()) {
				GameMethods::SpriteRightClick(Target->GetGuid());
				return;
			}
			else {
				GrindBot::CleanUp();
			}
		}
	}

	//Crashes at some funcs 
	void GrindBot::Fight() {

		if (mobList.empty())
			return;

		WObject* LocalPlayer = (WObject*)Globals::LocalPlayer;
		if (!LocalPlayer) {
			return;
		}

		if (LocalPlayer->IsDead() || LocalPlayer->IsGhost()) {
			Target = nullptr;
			return;
		}

		if (!Target->isValid() && LocalPlayer->IsInCombat() /*&& Globals::update*/) {
			printf("thostile\n");
			Target = (WObject*)HostileUnit_TargetingUs(0);
		}
		else if (!Target->isValid() && !LocalPlayer->IsInCombat() /*&& Globals::update*/) {

			if (!Buff(LocalPlayer))
				return;

			if (!Rest(LocalPlayer))
				return;

			Target = (WObject*)GetClosestMob();
		}


		if (!Target)
			return;

		if (!Target->isValid())
			return;

		if (!Utils::ValidCoord(Target) || !Utils::ValidCoord(LocalPlayer))
			return;

		if (LocalPlayer->sUnitField->TargetGuid.isEmpty() || LocalPlayer->sUnitField->TargetGuid != *Target->GetGuid()) {
			printf("invalid guid\n");
			if (LocalPlayer->sUnitField->TargetGuid != *Target->GetGuid()) {
				printf("Now targeting correct guid\n");
				LocalPlayer->sUnitField->TargetGuid == *Target->GetGuid();
			}
		}

		if (!Target->IsDead() && !Target->IsLootable())
		{
			printf("Entry Point\n");

			float DistTo = LocalPlayer->GetUnitPosition().DistanceTo(Target->GetUnitPosition());
			int spellID = GetSpellID(LocalPlayer, Target); // Get spellid

			// if (0) we cant cast so meleeattack or stun target.
			if (spellID == 0) {
				bool pGetCoolDown = GameMethods::GetCoolDown();
				if (pGetCoolDown) {
					if (LocalPlayer->sUnitField->RaceID == WoWRace::Tauren && DistTo <= 6 && !LocalPlayer->pHasCoolDown("Warstomp")) {
						static int Warstomp = 20549;
						CastSpell(LocalPlayer, Warstomp);
						printf("No cooldown!!\n");
					}
				}
				else if (!GameMethods::Spell_C_IsCurrentSpell(6603) && GameMethods::CGUnit_C_IsInCombat && DistTo <= 6) {
					printf("CGUnit_C_OnAttackIconPressed\n");
					GameMethods::CGUnit_C_OnAttackIconPressed(Target->GetGuid());
					return;
				}
			}


			printf("DistCheck Before\n");
			DistCheck(LocalPlayer, Target, spellID, DistTo); //Distance check Findpath to target if we are far away or not in los.					
			printf("After DistCheck\n");

			if (nav::StartNavigator
				|| LocalPlayer->IsPlayerMoving()
				|| LocalPlayer->GetChannelID() != 0) {
				printf("Not going to cast!\n");
				return;
			}


			printf("After Mana\n");
			CastSpell(Target, spellID);
			printf("[+] After castSpell? \n");

		}
		else if (Target->IsDead()) {

			printf("[TargetIsDeadIsLootable]\n");
			if (LocalPlayer->IsInCombat() && HostileUnit_TargetingUs(Target->GetGuid()))
				return;

			if (nav::StartNavigator || LocalPlayer->IsPlayerMoving())
				return;

			if (Target->IsLootable()) {
				WalkToTarget(LocalPlayer, Target);
				return;
			}
			else if (Settings::bot::Grinding::SkinMobs && Target->IsSkinnable())
			{
				WalkToTarget(LocalPlayer, Target);
				return;
			}
			else {
				printf("Cleanup\n");
				GrindBot::CleanUp();
			}
		}
	}
}
