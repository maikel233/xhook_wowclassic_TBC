//#include <Psapi.h>

#include "Utils.h"
#include "Settings/settings.h"
#include "Globals.h"


bool Utils::IsUnitEnemy(WObject* unit) { return GameMethods::GetUnitReaction(unit) <= 3; }
bool Utils::IsUnitFriendly(WObject* unit) { return !IsUnitEnemy(unit); }

bool Utils::approxEqual(float v1, float v2) { return abs(v1 - v2) < pow(10, -7); }
bool Utils::InRangeOf(WObject* Entity, const Vector3& v, float distance) { return Entity->GetUnitPosition().Distance(v) <= distance; }
float Utils::GetDistance2D(float fLocation2X, float fLocation1X, float fLocation2Y, float fLocation1Y) { return sqrt(((fLocation2X - fLocation1X) * (fLocation2X - fLocation1X)) + ((fLocation2Y - fLocation1Y) * (fLocation2Y - fLocation1Y))); }
float Utils::GetDistance(Vector3 Pos) { return GetDistance2D(Pos.x, Globals::LocalPlayer->GetUnitPosition().x, Pos.y, Globals::LocalPlayer->GetUnitPosition().y); }

bool Utils::ValidCoord(WObject* entity) {
	if ((entity->GetUnitPosition().x == 0 && entity->GetUnitPosition().y == 0 && entity->GetUnitPosition().z == 0) || GetDistance(entity->GetUnitPosition()) >= 100000) return FALSE;
	return TRUE;
}

long Utils::GetEpochTime() {
	using namespace std::chrono;
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	return ms.count();
}

ImColor Utils::GetFactionColor(WObject* Player) {
	ImColor FactionColor;
	if (Player->IsPlayer() || Player->IsLocalPlayer())
	{
		if (Player->GetFactionID() == FactionID::Horde)
			FactionColor = ImColor(1.00f, 0.0f, 0.0f, 1.0f);
		else
			FactionColor = ImColor(0.00f, 0.0f, 1.0f, 1.0f);
	}
	else { FactionColor; }
	return FactionColor;
}

ImColor Utils::GetClassColor(WObject* entity) {
	int RaceID = entity->GetClassID();
	ImColor Class;

	if (RaceID == WoWClass::None) { Class = ImColor(0.0f, 0.0f, 0.0f, 1.0f); }
	else if (RaceID == WoWClass::Warrior) { Class = ImColor(0.78f, 0.61f, 0.43f, 1.0f); }
	else if (RaceID == WoWClass::Paladin) { Class = ImColor(0.96f, 0.55f, 0.73f, 1.0f); }
	else if (RaceID == WoWClass::Hunter) { Class = ImColor(0.67f, 0.83f, 0.45f, 1.0f); }
	else if (RaceID == WoWClass::Rogue) { Class = ImColor(1.0f, 0.96f, 0.41f, 1.0f); }
	else if (RaceID == WoWClass::Priest) { Class = ImColor(1.0f, 1.0f, 1.0f, 1.0f); }
	else if (RaceID == WoWClass::DeathKnight) { Class = ImColor(0.77f, 0.12f, 0.23f, 1.0f); }
	else if (RaceID == WoWClass::Shaman) { Class = ImColor(0.00f, 0.44f, 0.87f, 1.0f); }
	else if (RaceID == WoWClass::Mage) { Class = ImColor(0.25f, 0.78f, 0.92f, 1.0f); }
	else if (RaceID == WoWClass::Warlock) { Class = ImColor(0.53f, 0.53f, 0.93f, 1.0f); }
	else if (RaceID == WoWClass::Druid) { Class = ImColor(1.0f, 0.49f, 0.04f, 1.0f); }
	else { Class = ImColor(1.0f, 0.49f, 1.04f, 1.0f); }

	return Class;
}

ImColor Utils::GetRainbowColor(float speed) {
	speed = 0.002f * speed;
	long now = Utils::GetEpochTime();
	float hue = (now % (int)(1.0f / speed)) * speed;

	return ImColor::HSV(hue, 1.0f, 1.0f);
}

Color Utils::GetHealthColor(int hp) {
	return Color(
		min(510 * (100 - hp) / 100, 255),
		min(510 * hp / 100, 255),
		25
	);
}

Color Utils::GetHealthColor(WObject* player) {
	return Color(
		min(510 * (player->MaxHealth() - player->Health()) / player->MaxHealth(), 255),
		min(510 * player->Health() / player->MaxHealth(), 255),
		25
	);
}

std::string Utils::GetHealth(WObject* Entity) {
	std::string HealthStr;
	if (Entity->IsUnit() || Entity->IsPlayer() || Entity->IsLocalPlayer()) {
		HealthStr = std::to_string(Entity->Health()) + "/" + std::to_string(Entity->MaxHealth());
	}
	return HealthStr;
}

std::string Utils::GetPower(WObject* Entity) {
	std::string EnergyOrManaStr;
	if (Entity->IsUnit() || Entity->IsPlayer() || Entity->IsLocalPlayer()) {

		if (Entity->getPowerString() == "Mana") {
			EnergyOrManaStr = std::to_string(Entity->Mana()) + "/" + std::to_string(Entity->MaxMana());
		}
		else {
			EnergyOrManaStr = std::to_string(Entity->Energy()) + "/" + std::to_string(Entity->MaxEnergy());
		}
	}
	return EnergyOrManaStr;
}

std::string Utils::IsHordeOrAlliance(WObject* Player) {
	std::string Result;
	if (Player->IsPlayer() || Player->IsLocalPlayer()) {

		if (Player->GetFactionID() == FactionID::Horde)
			Result = "Horde";
		else
			Result = "Alliance";
	}
	else { Result = ""; }
	return Result;
}

std::string Utils::GetRace(WObject* Entity) {
	std::string Race;
	if (Entity->IsPlayer() || Entity->IsLocalPlayer()) {
		int RaceID = Entity->GetRaceID();
		if (RaceID == WoWRace::Undead) { Race = "Undead"; }
		else if (RaceID == WoWRace::Troll) { Race = "Troll"; }
		else if (RaceID == WoWRace::TrollFemale) { Race = "Troll"; }
		else if (RaceID == WoWRace::Tauren) { Race = "Tauren"; }
		else if (RaceID == WoWRace::Skeleton) { Race = "Skeleton"; }
		else if (RaceID == WoWRace::Orc) { Race = "Orc"; }
		else if (RaceID == WoWRace::NightElf) { Race = "Nightelf"; }
		else if (RaceID == WoWRace::Naga) { Race = "Naga"; }
		else if (RaceID == WoWRace::Human) { Race = "Human"; }
		else if (RaceID == WoWRace::Goblin) { Race = "Goblin"; }
		else if (RaceID == WoWRace::Gnome) { Race = "Gnome"; }
		else if (RaceID == WoWRace::FelOrc) { Race = "FelOrc"; }
		else if (RaceID == WoWRace::Dwarf) { Race = "Dwarf"; }
		else if (RaceID == WoWRace::Draenei) { Race = "Draenei"; }
		else if (RaceID == WoWRace::Broken) { Race = "Broken"; }
		else if (RaceID == WoWRace::BloodElf) { Race = "BloodElf"; }
	}
	else { Race = ""; }
	return Race;
}

std::string Utils::GetSex(WObject* Entity) {
	if (Entity->IsPlayer() || Entity->IsLocalPlayer()) {
		switch (Entity->GetSex()) {
		case 0: return "Male";
		case 1: return "Female";
		case 2: return "Unknown";
		default: return "";
		}
	}
	return "";
}

std::string Utils::GetClass(WObject* Entity) {
	std::string Class;
	if (Entity->IsPlayer() || Entity->IsLocalPlayer()) {
		int ClassID = Entity->GetClassID();
		if (ClassID == WoWClass::None) { Class = "None"; }
		else if (ClassID == WoWClass::Warrior) { Class = "Warrior"; }
		else if (ClassID == WoWClass::Paladin) { Class = "Paladin"; }
		else if (ClassID == WoWClass::Hunter) { Class = "Hunter"; }
		else if (ClassID == WoWClass::Rogue) { Class = "Rogue"; }
		else if (ClassID == WoWClass::Priest) { Class = "Priest"; }
		else if (ClassID == WoWClass::DeathKnight) { Class = "Deathknight"; }
		else if (ClassID == WoWClass::Shaman) { Class = "Shaman"; }
		else if (ClassID == WoWClass::Mage) { Class = "Mage"; }
		else if (ClassID == WoWClass::Warlock) { Class = "Warlock"; }
		else if (ClassID == WoWClass::Druid) { Class = "Druid"; }
	}
	else { Class = ""; }
	return Class;
}


std::string Utils::GetObjType(WObject* entity) {
	int TypeID = (int)entity->GetType();
	std::string Object;
	if (TypeID == (int)TypeId::CGActivePlayer) { Object = "CGActivePlayer"; }
	else if (TypeID == (int)TypeId::CGPlayer) { Object = "CGPlayer"; }
	else if (TypeID == (int)TypeId::CGUnit) { Object = "CGUnit"; }
	else if (TypeID == (int)TypeId::CGGameObject) { Object = "CGGameObj"; }
	else if (TypeID == (int)TypeId::CGCorpse) { Object = "CGCorpse"; }
	else if (TypeID == (int)TypeId::CGDynamicObject) { Object = "CGDynamicObj"; }
	else if (TypeID == (int)TypeId::CGObject) { Object = "CGObj"; }
	else { Object = ""; }
	return Object;
}

int Utils::filterException(int code, PEXCEPTION_POINTERS ex) {
	std::cout << "[!] Filtering " << std::hex << code << std::endl;
	return EXCEPTION_EXECUTE_HANDLER;
}
