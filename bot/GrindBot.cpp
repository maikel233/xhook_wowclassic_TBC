#include "GrindBot.h"
#include "offsets.h"
//Still contains random crashes needs some love



//Now targeting correct guid
//[TargetIsDeadIsLootable]
//invalid guid




bool Settings::bot::NPCEXIST = false;


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

	map <string, vector<string> > Subjects;


	std::string GrindBot::GetMobName() {

		//Maybe loop entity[0] to totalunits?
		for (auto& npc : WoW::GrindBot::mobList) {
			printf("%s \n", npc.c_str());
			return npc.c_str();
		}
		

		//if (WoW::GrindBot::mobList.empty())
		//	return "";

		//for (std::vector<std::string>::iterator t = WoW::GrindBot::mobList.begin(); t != WoW::GrindBot::mobList.end(); t++) {;
		//	return *t;
		//}
	}

	WObject* GrindBot::GetClosestDeathMob()
	{
		WoWObjectManager::CycleObjects(true);

		//if (Settings::bot::TotalUnits == 0)
		//	return nullptr;

		float minDist = INFINITY;
		auto position = Globals::LocalPlayer->GetUnitPosition();
		WObject* closestObject = nullptr;
		printf("[++]closestobj is nullptr\n");
		for (auto& [guid, o] : Globals::Objects)
		{
			printf("[++]2222\n");

			if (o->isValid() && o->IsDead() && o->IsLootable() &&  o->GetType() == TypeId::CGUnit)
			{
				printf("[++]4444 \n");
				auto destQuery = o->GetUnitPosition();

				printf("[++]TargetDestination: X: %f Y:%f Z:%f \n", o->GetUnitPosition().x, o->GetUnitPosition().y, o->GetUnitPosition().z);
				float dist = sqrt(pow(destQuery.x - position.x, 2) + pow(destQuery.y - position.y, 2) + pow(destQuery.z - position.z, 2) * 1.0);
				if (dist < minDist) {
					minDist = dist;
					closestObject = o;
				}
			}
		}

		if (nav::GetPath(closestObject))
		{
			printf("[++] 11111111  \n");
			*Globals::LocalPlayer->TargetGuid() = *closestObject->GetGuid(); // Targets npc
			printf("[++] Closest mob After Guid \n");
			nav::StartNavigator = true;
			printf("[++] After navigator=true \n");
			return closestObject;
		}

		return nullptr;
	}

	WObject* GrindBot::GetClosestMob()
	{
		WoWObjectManager::CycleObjects(true);

		//if (Settings::bot::TotalUnits == 0)
		//	return nullptr;

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
			*Globals::LocalPlayer->TargetGuid() = *closestObject->GetGuid(); // Targets npc
			printf("[+] Closest mob After Guid \n");
			nav::StartNavigator = true;
			printf("[+] After navigator=true \n");
			return closestObject;
		}


		printf("[+]Returns NullPtr\n");
		return nullptr;
	}

	WObject* GrindBot::HostileUnit_TargetingUs(/*CGGuid* NPCGUID*/) {

		//WoWObjectManager::CycleObjects(true);

		for (auto& [guid, o] : Globals::Objects)
		{
			//if (o->isValid() && o->IsUnit() && !o->IsDead() && Utils::IsUnitEnemy(o)/* && o->GetGuid()*/) {
				/*if ( != NPCGUID)*/ 
	/*			printf("Komen wij hier wel???");*/
					if (o->TargetGuid() == Globals::LocalPlayer->GetGuid()) {
						printf("[TargetHostile] %s is targeting us!\n", o->GetObjectName());
						*Globals::LocalPlayer->TargetGuid() = *o->GetGuid(); // Targets npc
						Target = o;
						return o;
					}
			//	}		
		}
		return Target;
	}


	void GrindBot::CastSpell(WObject* Unit, int SpellID) {

		printf("[CASTSPELL] HaveSpellPower\n");
		if (!GameMethods::Spell_C_HaveSpellPower(SpellID))
			return;

		printf("[CASTSPELL] Before Spell_C_RangeCheckSelected\n");
		if (Unit && Unit->GetGuid() != Globals::LocalPlayer->GetGuid()) {
			printf("[CASTSPELL] Spell_C_RangeCheckSelected\n");
			/*float_t min = 0;
			float_t max = 0;
			GameMethods::Spell_C_GetMinMaxSpellRange(SpellID, &min, &max, Unit->GetGuid());
			printf("[CASTSPELL] MaxSpellRange is %f\n", max);
			if (Globals::LocalPlayer->GetUnitPosition().DistanceTo(Unit->GetUnitPosition()) >= max)
				return;*/

			bool IsUnitInRange = false;
			GameMethods::Spell_C_RangeCheckSelected(SpellID, Target->GetGuid(), &IsUnitInRange);

			if (!IsUnitInRange) {
				return;
			}
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

		if (Unit && Unit->GetGuid() != Globals::LocalPlayer->GetGuid()) {
			WoW::Hacks::SetFacing(Unit->GetUnitPosition());
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

		static int RaceID = LocalPlayer->GetClassID();
		if (RaceID == WoWClass::Druid) {
			static int MOTW = GameMethods::SpellBook_FindSpellByName("Mark of the Wild");
			static int Thorns = GameMethods::SpellBook_FindSpellByName("Thorns");
			if (MOTW == 0 || Thorns == 0) {
				return true; 
			}

			else if (!LocalPlayer->pHasAura("Mark of the Wild")) {
				CastSpell(LocalPlayer, MOTW);
				return false;
			}
		
			else if (!LocalPlayer->pHasAura("Thorns")) {
				CastSpell(LocalPlayer, Thorns);
				return false;
			}
		}
		return true;
	}

	int GrindBot::GetSpellID(WObject* LocalPlayer, WObject* Target) {
		//Spellbook? or enum with isknown?
		if (LocalPlayer->GetClassID() == WoWClass::Druid) {

			//Get Highest SpellID
			static int Spell_Wrath = GameMethods::SpellBook_FindSpellByName("Wrath");
			static int Spell_MoonFire = GameMethods::SpellBook_FindSpellByName("MoonFire");
			static int Spell_Rejuvenation = GameMethods::SpellBook_FindSpellByName("Rejuvenation");
			static int Spell_HealingTouch = GameMethods::SpellBook_FindSpellByName("HealingTouch");

			printf("GetSpellID\n");
			if (LocalPlayer->HealthPercent() < 40 && !LocalPlayer->pHasAura("Rejuvenation") && GameMethods::Spell_C_HaveSpellPower(Spell_Rejuvenation)) {
				printf("Casting: Rejuvenation\n");
				CastSpell(LocalPlayer, Spell_Rejuvenation);
				return 0;
			}
			else if (LocalPlayer->HealthPercent() < 20 && Target->HealthPercent() > 20 && GameMethods::Spell_C_HaveSpellPower(Spell_HealingTouch)) {
				printf("Casting: HealingTouch\n");
				CastSpell(LocalPlayer, Spell_HealingTouch);
				return 0;
			}
			////Entry Attack
			//else if (Target->HealthPercent() == 100) {
			//	printf("Spell=Wrath Target is FullHP\n");
			//	return Spell_WrathR1;
			//}
			else if (Target->HealthPercent() < 95 && !Target->pHasAura("Moonfire") && GameMethods::Spell_C_HaveSpellPower(Spell_MoonFire)) {
				printf("Spell=MoonFire\n");
				return Spell_MoonFire;
			}
			else if (GameMethods::Spell_C_HaveSpellPower(Spell_Wrath)) {
				printf("Spell=Wrath\n");
				return Spell_Wrath; // Return default casting spell
			}
			else
				printf("No mana? Trying melee attack or CGCooldown skill..\n");
			return 0;
		}
		return 0;
	}

	bool GrindBot::DistCheck(WObject* LocalPlayer, WObject* Target, int SpellID, float DistTo)
	{
		printf("[DISTCHECK] GetMinMaxSpellRange\n");
		float_t minstop = 0;
		float_t maxstop = 0;
		GameMethods::Spell_C_GetMinMaxSpellRange(SpellID, &minstop, &maxstop, Target->GetGuid());
		printf("[DISTCHECK] After GetMinMaxSpellRange %f %f\n", minstop, maxstop);


		if (!nav::StartNavigator && !LocalPlayer->IsPlayerMoving() && DistTo >= maxstop) {
			bool FindPath = nav::GetPath(Target);
			if (FindPath) {
				nav::StartNavigator = true;
				printf("[DISTCHECK] We are still to far away from the target. Moving to target....\n");
				return false;
			}
		}// /*nav::StartNavigator Checking if this value is true doesnt do anything because i set it to False at 10000 places....
		else if (/*nav::StartNavigator && */WoW::camera::TraceLine(LocalPlayer, Target->GetUnitPosition(), IntersectFlags::LineOfSight)
			&& LocalPlayer->IsPlayerMoving()
			&& DistTo < 30) {

			printf("DISTCHECK TraceLine !!!!!!!!!!!!!!!!!!!!!!!!!!\n");

			nav::Waypoints.clear();
			nav::StartNavigator = false; //Startnavigator=false doesnt clear the vector fast enough maybe because of the tick delay?
			if (nav::Waypoints.empty()) {
				printf("Clicking on localplayer ground!!!\n");
				//WoW::Hacks::CTM(LocalPlayer);
				WoW::Hacks::MoveToPoint(Globals::LocalPlayer->GetUnitPosition(), 0);
				return true;
			}
		}



		return true;
	}


	void GrindBot::WalkToTarget(WObject* LocalPlayer, WObject* Target) {
		float DistTo = LocalPlayer->GetUnitPosition().DistanceTo(Target->GetUnitPosition());
		printf("DisToBody: %f\n", DistTo);


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
			printf("We ded or ghost\n");
			Target = nullptr;
			return;
		}

		if (!Target->isValid() && LocalPlayer->IsInCombat() /*&& Globals::update*/) {
			printf("thostile\n");
			Target = (WObject*)HostileUnit_TargetingUs();
		}

		else if (!Target->isValid() && !LocalPlayer->IsInCombat() /*&& Globals::update*/) {

			if (!Buff(LocalPlayer))
				return;

			if (!Rest(LocalPlayer))
				return;

			if (Settings::bot::NPCEXIST) {
				Target = (WObject*)GetClosestMob(); }
		}
		else if (Target == nullptr) {
			printf("Nullptr hiero????\n");
		}


		if (!Target)
			return;



		if (!Target->isValid())
			return;

		if (!Utils::ValidCoord(Target) || !Utils::ValidCoord(LocalPlayer))
			return;

		//if (LocalPlayer->TargetGuid()->isEmpty() || *LocalPlayer->TargetGuid() != *Target->GetGuid()) {
		//	printf("invalid guid\n");

		//	//Loot Nearby corpses
		//	if (LocalPlayer->IsInCombat()) {
		//		// We are still in combat Fight!
		//		printf("We're still in combat!\n");
		//	}
		//	else {
		//		// Go loot nearby corpses
		//		//Enum dead targets
		//		printf("Enum GetClosestDeathMob!\n");
		//		Target = (WObject*)GetClosestDeathMob();


		//	}
		///*	if (LocalPlayer->TargetGuid() != Target->GetGuid()) {
		//		printf("Now targeting correct guid\n");
		//		LocalPlayer->TargetGuid() == Target->GetGuid();*/
		//	
		//}


		if (!Target->IsDead() && !Target->IsLootable())
		{

			printf("Entry Point\n");

			float DistTo = LocalPlayer->GetUnitPosition().DistanceTo(Target->GetUnitPosition());


			


			int spellID = GetSpellID(LocalPlayer, Target); // Get spellid

			//MeleeAttack
			if (spellID == 0 && DistTo <= 6) {
				printf("Spell ID %i Trying to attack?\n", spellID);
				if (!GameMethods::Spell_C_IsCurrentSpell(6603) && GameMethods::CGUnit_C_IsInCombat) {
					printf("CGUnit_C_OnAttackIconPressed\n");
					GameMethods::CGUnit_C_OnAttackIconPressed(Target->GetGuid());
				}
				else if (GameMethods::GetCoolDown()) {
					if (LocalPlayer->GetRaceID() == WoWRace::Tauren && DistTo <= 6 && !LocalPlayer->pHasCoolDown("War Stomp")) {
						//static int Warstomp = 20549;
						static int CD = GameMethods::SpellBook_FindSpellByName("War Stomp");
						CastSpell(LocalPlayer, CD);
						printf("No cooldown!!\n");
					}
				}
			}
			else {
				printf("DistCheck Before\n");
				if (DistCheck(LocalPlayer, Target, spellID, DistTo)) { //Distance check Findpath to target if we are far away or not in los.				
					if (!LocalPlayer->IsPlayerMoving()) {
						printf("CastingSpell332\n");
						CastSpell(Target, spellID);
					}					
				}
			}

		}
		else if (Target->IsDead()) {

			printf("[Target %s IsDead]\n", Target->GetObjectName());


			//Fix later.
		/*	if (LocalPlayer->IsInCombat() && HostileUnit_TargetingUs(Target->GetGuid()))
				return;*/

			//if (/*nav::StartNavigator || */LocalPlayer->IsPlayerMoving())
			//	return;

			if (Target->IsLootable()) {
				printf("[TargetIsDeadIsLootable]\n");
				WalkToTarget(LocalPlayer, Target);
				return;
			}
			else if (Settings::bot::Grinding::SkinMobs && Target->IsSkinnable())
			{
				printf("[TargetIsDeadIsSkinnable]\n");
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
