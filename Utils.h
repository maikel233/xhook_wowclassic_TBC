#pragma once
#include "Settings/Color.h"
#include "Lua/LuaBase.h"
#include "Lua/LuaScript.h"
#include "Lua/GameMethods.h"
using namespace std;

namespace Utils
{
	long GetEpochTime();
	ImColor GetRainbowColor(float speed);
	Color GetHealthColor(int hp);
	Color GetHealthColor(WObject* player);
	bool IsEntityAlive(WObject* entity);
	int IsFriendlyOrEnemy(WObject* player);
	std::string IsHordeOrAlliance(WObject* player);
	std::string GetRace(WObject* entity);
	std::string GetObjType(int TypeID);
	std::string GetHealth(WObject* entity);
	int filterException(int code, PEXCEPTION_POINTERS ex);

}