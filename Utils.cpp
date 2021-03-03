#include "Utils.h"
#include "Settings/settings.h"
#include <algorithm>
#include <cctype>
#include <fcntl.h>
#include "Xorstr.h"

long Utils::GetEpochTime()
{
	using namespace std::chrono;
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);

	return ms.count();
}

ImColor Utils::GetRainbowColor(float speed)
{
	speed = 0.002f * speed;
	long now = Utils::GetEpochTime();
	float hue = (now % (int)(1.0f / speed)) * speed;

	return ImColor::HSV(hue, 1.0f, 1.0f);
}

Color Utils::GetHealthColor(int hp)
{
	return Color(
		min(510 * (100 - hp) / 100, 255),
		min(510 * hp / 100, 255),
		25
	);
}

Color Utils::GetHealthColor(WObject* player)
{
	return Color(
		min(510 * (player->sUnitField->HealthMax - player->sUnitField->Health) / player->sUnitField->HealthMax, 255),
		min(510 * player->sUnitField->Health / player->sUnitField->HealthMax, 255),
		25
	);
}

std::string Utils::GetHealth(WObject* entity)
{
	int TypeID = entity->GetType();
	std::string HealthStr;
	if (TypeID == CGPlayer || TypeID == CGUnit || TypeID == CGActivePlayer)
	{
		HealthStr = std::to_string(entity->sUnitField->Health) + "/" + std::to_string(entity->sUnitField->HealthMax);
	}
	return HealthStr;
}


bool Utils::IsEntityAlive(WObject* entity)
{
	int TypeID = entity->GetType();

	if (TypeID == CGPlayer || TypeID == CGUnit || TypeID == CGActivePlayer)
	{
		if (entity->sUnitField->Health > 0)
			return false;
	}
	return true;
}


int Utils::IsFriendlyOrEnemy(WObject* player)
{
	int RaceId = player->sUnitField->RaceId;
	int TypeID = player->GetType();

	if (TypeID == CGPlayer)
	{
		if (RaceId == WoWRace::Undead || RaceId == WoWRace::Troll || RaceId == WoWRace::Tauren || RaceId == WoWRace::Orc)
			return (int)TeamID::Horde;
		else if (RaceId == WoWRace::Human || RaceId == WoWRace::Dwarf || RaceId == WoWRace::Gnome || RaceId == WoWRace::NightElf)
			return (int)TeamID::Alliance;
	}
	return RaceId;
}


std::string Utils::IsHordeOrAlliance(WObject* player)
{
	int RaceId = player->sUnitField->RaceId;
	int TypeID = player->GetType();
	std::string Result;


	if (TypeID == CGPlayer || TypeID == CGActivePlayer)
	{
		if (RaceId == WoWRace::Undead || RaceId == WoWRace::Troll || RaceId == WoWRace::Tauren || RaceId == WoWRace::Orc)
			Result = "Horde";
		else if (RaceId == WoWRace::Human || RaceId == WoWRace::Dwarf || RaceId == WoWRace::Gnome || RaceId == WoWRace::NightElf)
			Result = "Alliance";
	}
	else { Result = ""; }
	
	return Result;
}

std::string Utils::GetRace(WObject* entity)
{
	int RaceId = entity->sUnitField->RaceId;
	int TypeID = entity->GetType();
	std::string Race;
	if (TypeID == CGPlayer)
	{		
		if (RaceId == WoWRace::Undead) { Race = "Undead"; }
		else if (RaceId == WoWRace::Troll) { Race = "Troll"; }
		else if (RaceId == WoWRace::Tauren) { Race = "Tauren"; }
		else if (RaceId == WoWRace::Skeleton) { Race = "Skeleton"; }
		else if (RaceId == WoWRace::Orc) { Race = "Orc"; }
		else if (RaceId == WoWRace::NightElf) { Race = "Nightelf"; }
		else if (RaceId == WoWRace::Naga) { Race = "Naga"; }
		else if (RaceId == WoWRace::Human) { Race = "Human"; }
		else if (RaceId == WoWRace::Goblin) { Race = "Goblin"; }
		else if (RaceId == WoWRace::Gnome) { Race = "Gnome"; }
		else if (RaceId == WoWRace::FelOrc) { Race = "FelOrc"; }
		else if (RaceId == WoWRace::Dwarf) { Race = "Dwarf"; }
		else if (RaceId == WoWRace::Draenei) { Race = "Draenei"; }
		else if (RaceId == WoWRace::Broken) { Race = "Broken"; }
		else if (RaceId == WoWRace::BloodElf) { Race = "BloodElf"; }
	}
		return Race;
}

std::string Utils::GetObjType(int TypeID)
{
	std::string Object;
	if (TypeID == CGActivePlayer) { Object = "CGActivePlayer"; }
	else if (TypeID == CGPlayer) { Object = "CGPlayer"; }
	else if (TypeID == CGUnit) { Object = "CGUnit"; }
	else if (TypeID == CGGameObject) { Object = "CGGameObj"; }
	else if (TypeID == CGCorpse) { Object = "CGCorpse"; }
	else if (TypeID == CGDynamicObject) { Object = "CGDynamicObj"; }
	else if (TypeID == CGObject) { Object = "CGObj"; }
	return Object;
}

int Utils::filterException(int code, PEXCEPTION_POINTERS ex) {
	std::cout << "[!] Filtering " << std::hex << code << std::endl;
	return EXCEPTION_EXECUTE_HANDLER;
}
