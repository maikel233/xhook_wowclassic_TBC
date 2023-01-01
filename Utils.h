#pragma once
#include "Settings/Color.h"
#include "Lua/GameMethods.h"
#include <mutex>
#include <psapi.h>
#pragma comment( lib, "psapi.lib" )


namespace Utils
{
	bool approxEqual(float v1, float v2);
	long GetEpochTime();
	ImColor GetRainbowColor(float speed);
	ImColor GetClassColor(WObject* entity);
	ImColor GetFactionColor(WObject* entity);
	Color GetHealthColor(int hp);
	Color GetHealthColor(WObject* player);
	
	//bool IsEntityAlive(WObject* entity);
	//int IsSameFaction(WObject* player);
	std::string IsHordeOrAlliance(WObject* player);
	std::string GetRace(WObject* entity);
	std::string GetSex(WObject* entity);
	std::string GetClass(WObject* entity);
	std::string GetObjType(WObject* entity);
	std::string GetHealth(WObject* entity);
	std::string GetPower(WObject* entity);

	bool IsUnitFriendly(WObject* unit);
	bool IsUnitEnemy(WObject* unit);

	int filterException(int code, PEXCEPTION_POINTERS ex);
	bool ValidCoord(WObject* entity);
	float GetDistance(Vector3 Pos);
	float GetDistance2D(float fLocation2X, float fLocation1X, float fLocation2Y, float fLocation1Y);

	bool InRangeOf(WObject* Entity, const Vector3& v, float distance);
	//std::string FetchAuraNamew(int nAuraID);

}
