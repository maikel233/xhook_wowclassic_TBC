#pragma once
#include "stdafx.h"
#include "Constants.h"
#include "Location.hpp"
using namespace std;

class GameMethods
{
public:
	// typedefs
	typedef unsigned int(__fastcall* EnumVisibleObjectsCb)(int64_t, int64_t);
	typedef signed int(__fastcall* LuaCallback)(int64_t luaState);

	template <typename T, typename... Types>
	inline static T Invoke(uintptr_t offset, Types... args)
	{
		return reinterpret_cast<T(__fastcall*)(Types...)>(offset)(args...);
	}

	// framescript	
	static inline int64_t GameMethods::Execute(const char* command)
	{
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, int64_t, int64_t)>(Offsets::Base + Offsets::FrameScriptExecute)(int64_t(command), int64_t("compat"), 0);
	}

	static inline int64_t GameMethods::Execute(const std::string& command)
	{
		return Execute(command.c_str());
	}

	static inline string GameMethods::GetText(const char* varName)
	{
		return reinterpret_cast<char* (__fastcall*)(const char*, int64_t, int, uint8_t)>(Offsets::Base + Offsets::FrameScriptGetText)(varName, -1, 0, 0);
	}

	static inline void Register(const char* scriptName, GameMethods::LuaCallback callback)
	{
		return reinterpret_cast<void(__fastcall*)(const char*, GameMethods::LuaCallback)>(Offsets::Base + Offsets::FrameScriptRegister)(scriptName, callback);
	}

	//// lua

	//static inline int64_t LuaSetTop(int64_t l, const int32_t a2)
	//{
	//	return reinterpret_cast<int64_t(__fastcall*)(int64_t, int32_t)>(Offsets::Base + Offsets::lua_settop)(l, a2);
	//}

	//static inline int64_t LuaGetTop(int64_t l)
	//{
	//	return reinterpret_cast<int64_t(__fastcall*)(int64_t)>(Offsets::Base + Offsets::lua_gettop)(l);
	//}

	//static inline int64_t LuaError(int64_t l, const char* msg)
	//{
	//	return reinterpret_cast<int64_t(__cdecl*)(int64_t, const char*)>(Offsets::Base + Offsets::luaL_error)(l, msg);
	//}

	//static inline int64_t LoadFile(int64_t luaState, int64_t path)
	//{
	//	return reinterpret_cast<int64_t(__fastcall*)(int64_t, int)>(Offsets::Base + Offsets::lua_LoadFile)(luaState, path);
	//}

	//static inline int64_t PCall(int64_t luaState, int a, int b, int c)
	//{
	//	return reinterpret_cast<int64_t(__fastcall*)(int64_t, int, int, int)>(Offsets::Base + Offsets::lua_PCall)(luaState, a, b, c);
	//}
	//static int64_t PushClosure(int64_t luaState, int64_t fn, int n)
	//{
	//	return reinterpret_cast<int64_t(__fastcall*)(int64_t, int64_t, int)>(Offsets::Base + Offsets::lua_PushClosure)(luaState, fn, n);
	//}
	//static int8_t PushBoolean(int64_t luaState, int value)
	//{
	//	return reinterpret_cast<int8_t(__fastcall*)(int64_t, int)>(Offsets::Base + Offsets::lua_pushboolean)(luaState, value);
	//}
	//static int64_t PushGuid(int64_t luaState, WGuid* guidPtr)
	//{
	//	return reinterpret_cast<int64_t(__fastcall*)(int64_t, WGuid*)>(Offsets::Base + Offsets::lua_PushGuid)(luaState, guidPtr);
	//}
	//static inline int64_t PushNumber(int64_t luaState, double value)
	//{
	//	return reinterpret_cast<int64_t(__fastcall*)(int64_t, double)>(Offsets::Base + Offsets::lua_PushNumber)(luaState, value);
	//}
	//static int64_t PushString(int64_t luaState, int64_t value)
	//{
	//	return reinterpret_cast<int64_t(__fastcall*)(int64_t, int64_t)>(Offsets::Base + Offsets::lua_PushString)(luaState, value);
	//}
	//static int64_t ToInteger(int64_t luaState, int idx)
	//{
	//	return reinterpret_cast<int64_t(__fastcall*)(int64_t, int)>(Offsets::Base + Offsets::lua_ToInteger)(luaState, idx);
	//}
	//static string ToLString(int64_t luaState, int64_t index, uintptr_t* len)
	//{
	//	return reinterpret_cast<char* (__fastcall*)(int64_t, int64_t, uintptr_t*)>(Offsets::Base + Offsets::lua_ToLString)(luaState, index, len);
	//}

	//static bool LuaIsString(int64_t luastate, const int64_t len)
	//{
	//	return reinterpret_cast<bool(__fastcall*)(int64_t, int64_t)>(Offsets::Base + Offsets::lua_isstring)(luastate, len);
	//}

	//static double ToNumber(int64_t luaState, int idx)
	//{
	//	return reinterpret_cast<double(__fastcall*)(int64_t, int)>(Offsets::Base + Offsets::lua_ToNumber)(luaState, idx);
	//}

	// object manager
	static inline bool ObjMgrIsValid(uint8_t param)
	{
		return reinterpret_cast<bool(__fastcall*)(int8_t)>(Offsets::ClntObjMgrIsValid)(param);
	}

	//// object manager
	//static inline bool LootWindow()
	//{
	//	return reinterpret_cast<bool(__fastcall*)(int8_t)>(Offsets::Base + Offsets::LootWindow);
	//}

	static inline char EnumVisibleObjects(EnumVisibleObjectsCb callback, int64_t filter)
	{
		return reinterpret_cast<char(__fastcall*)(GameMethods::EnumVisibleObjectsCb, int64_t)>(Offsets::ClntObjMgrEnumVisibleObjectsPtr)(callback, filter);
	}


	// ctm
	static inline void ClickToMove(int64_t playerPtr, C3Vector& position)
	{
		return reinterpret_cast<void(__fastcall*)(int64_t, C3Vector&)>(Offsets::Base + Offsets::ClickToMove)(playerPtr, position);
	}

	// ctm
	static inline void FaceTo(int64_t playerPtr, float& angle)
	{
		return reinterpret_cast<void(__fastcall*)(int64_t, float&)>(Offsets::Base + Offsets::FaceTo)(playerPtr, angle);
	}


	// Spell Funcs
	static inline int64_t GetMinMaxSpellRange(int64_t playerPtr, uint64_t SpellId, float_t* MinRange, float_t* MaxRange, WGuid* TargetGuid)
	{
		return reinterpret_cast<int64_t(__fastcall*)(int64_t playerPtr, uint64_t, float_t*, float_t*, WGuid*)>(Offsets::Spell_C_GetMinMaxRange)(playerPtr, SpellId, MinRange, MaxRange, TargetGuid);
	}
	
	static inline bool IsSpellKnown(int32_t spellId) {
		return reinterpret_cast<bool(__fastcall*)(int32_t, int32_t)>(Offsets::isSpellKnown)(spellId, 0);
	}

	static inline int32_t FindSlotBySpellId(int32_t spellId) {
		return reinterpret_cast<int64_t(__fastcall*)(int32_t, int32_t)>(Offsets::findSlotBySpellId)(spellId, 0);
	}

	static inline int64_t StopCast() {
		return reinterpret_cast<int64_t(__fastcall*)()>(0x1089B40)();
	}

	static inline int64_t CastSpell(int32_t spellSlot, WGuid* targetGuid) {
		return reinterpret_cast<int64_t(__fastcall*)(int32_t, int32_t, WGuid*, uint8_t, uint8_t)>(Offsets::castSpell)(spellSlot, 0, targetGuid, 0, 0);
	}

	static bool Spell_C_GetSpellCooldown(uint32_t spellId, bool unk1, bool isPet, int64_t* duration, int64_t* startTime, bool* enabled, int64_t* unk2, int64_t* unk3, int64_t* modRate)
	{
		return reinterpret_cast<bool(__fastcall*)(uint32_t, bool, bool, int64_t*, int64_t*, bool*, int64_t*, int64_t*, int64_t*)>(Offsets::Spell_C_GetSpellCoolDown)(spellId, unk1, isPet, duration, startTime, enabled, unk2, unk3, modRate);
	}


	using ClntObjMgr__GetMapId_Fn = uint32_t(__stdcall*)();
	static inline uint32_t ClntObjMgr__GetMapId()
	{
		auto const getMapIdFn = reinterpret_cast<ClntObjMgr__GetMapId_Fn>(
			Offsets::ClntObjMgrGetMapId);

		return (getMapIdFn)();
	}


	// object manager
	static inline uint8_t test(uint8_t param)
	{
		return(param);
	}

};

