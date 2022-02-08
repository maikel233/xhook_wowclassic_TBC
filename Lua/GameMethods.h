#pragma once
#include "stdafx.h"
#include "Constants.h"
#include "Globals.h"
#include <mutex>
#include <minmax.h>

using namespace std;


//Reference https://wowwiki-archive.fandom.com/wiki/
class GameMethods
{
public:
	// typedefs
	typedef unsigned int(__fastcall* EnumVisibleObjectsCb)(int64_t, int64_t);
	typedef signed int(__fastcall* LuaCallback)(int64_t luaState);

//	inline static std::vector<CoolDownStruct>(Cooldowns);

	template <typename T, typename... Types>
	inline static T Invoke(uintptr_t offset, Types... args)
	{
		return reinterpret_cast<T(__fastcall*)(Types...)>(offset)(args...);
	}
	// object manager
	static inline bool ObjMgrIsValid(uint8_t param)
	{
		return reinterpret_cast<bool(__fastcall*)(int8_t)>(Offsets::ClntObjMgrIsValid)(param);
	}

	static inline char EnumVisibleObjects(EnumVisibleObjectsCb callback, int64_t filter)
	{
		return reinterpret_cast<char(__fastcall*)(GameMethods::EnumVisibleObjectsCb, int64_t)>(Offsets::ClntObjMgrEnumVisibleObjectsPtr)(callback, filter);
	}

	// ctm
	static inline void ClickToMove(int64_t playerPtr, Vector3 position)
	{
		return reinterpret_cast<void(__fastcall*)(int64_t, Vector3&)>(Offsets::ClickToMove)(playerPtr, position);
	}

	static int64_t FaceTo(int64_t playerPtr, float_t angle)
	{
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, float_t angle)>(Offsets::FaceTo)(playerPtr, angle);
	}

	static int64_t SpriteLeftClick(CGGuid* TargetGuid) {
		return reinterpret_cast<int64_t(__fastcall*)(CGGuid*)>(Offsets::SpriteLeftClick)(TargetGuid);
	}
	static int64_t SpriteRightClick(CGGuid* TargetGuid) {
		return reinterpret_cast<int64_t(__fastcall*)(CGGuid*)>(Offsets::SpriteRightClick)(TargetGuid);
	}

	//__int64 __fastcall CGPlayer_C::HandleRepopRequest(__int64 a1, char a2)
	static int64_t RepopMe() {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, int32_t)>(Offsets::RepopMe)(Globals::LocalPlayer->Ptr(), 1);
	}
	//CGPlayer_C::AcceptResurrectRequest(RESURRECT_CLIENT_RESPONSE)
	//static int64_t RetrieveCorpse(int64_t activePlayerPtr, int32_t ClientResponse) {
	//	return reinterpret_cast<int64_t(__fastcall*)(int64_t, int32_t)>(Offsets::RetrieveCorpse)(activePlayerPtr, ClientResponse);
	//}
	//__int64 __usercall CGPlayer_C::CombatModeLeave@<rax>(CGPlayer_C *this@<rcx>, unsigned int a2@<edx>, float a3@<xmm0>)


	// SPELL_C_
	static inline bool Spell_C_IsCurrentSpell(int SpellId) {
		typedef bool(__cdecl* tIsCurrentSpellBySpellId)(int);
		tIsCurrentSpellBySpellId IsCurrentSpellBySpellId = (tIsCurrentSpellBySpellId)Offsets::Spell_C_IsCurrentSpell;
		return IsCurrentSpellBySpellId(SpellId);
	}

	static inline int64_t Spell_C_GetMinMaxSpellRange(int32_t SpellId, float_t* MinRange, float_t* MaxRange, CGGuid* TargetGuid) {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t playerPtr, int32_t, float_t*, float_t*, CGGuid*, int64_t)>(Offsets::Spell_C_GetMinMaxRange)(Globals::LocalPlayer->Ptr(), SpellId, MinRange, MaxRange, TargetGuid, 0);
	}

	static inline bool Spell_C_HaveSpellPower(int32_t spellId) {
		uint32_t unk0 = 0;
		uint32_t unk1 = 0;
		return reinterpret_cast<bool(__fastcall*)(int64_t, int32_t, uint32_t * flag1, uint32_t * flag2)>(Offsets::Spell_C_HaveSpellPower)(Globals::LocalPlayer->Ptr(), spellId, &unk0, &unk1);
	}

	static inline int64_t Spell_C_CastSpell(int32_t spellSlot, CGGuid* targetGuid) {
		return reinterpret_cast<int64_t(__fastcall*)(int32_t, int32_t, CGGuid*, uint8_t, uint8_t)>(Offsets::Spell_C_CastSpell)(spellSlot, 0, targetGuid, 0, 0);
	}

	static inline bool Spell_C_GetSpellCooldown(uint32_t spellId, int64_t* duration, int64_t* startTime, int64_t* modRate) {
		return reinterpret_cast<bool(__fastcall*)(uint32_t /* SpellId*/, int32_t /* Unk*/, int32_t/* isPet*/, int64_t* /* Duration*/, int64_t* /* StartTime*/, int64_t* /* IsEnabled??*/, int64_t* /* UNK3*/, int64_t*, int64_t*)>(Offsets::Spell_C_GetSpellCoolDown)(spellId, 0, 0, duration, startTime, 0, 0, 0, modRate);
	}

	static inline bool Spell_CancelSpell(int spell_id) {
		return reinterpret_cast<bool(__fastcall*)(int id, int flags)>(Offsets::CancelChannelOffset)(spell_id, 40);
	}

	//
	static inline bool IsSpellKnown(int32_t spellId) {
		return reinterpret_cast<bool(__fastcall*)(int32_t, int32_t)>(Offsets::isSpellKnown)(spellId, 0);
	}

	static inline int64_t FindSlotBySpellId(int32_t spellId) {
		return reinterpret_cast<int64_t(__fastcall*)(int32_t, int32_t)>(Offsets::findSlotBySpellId)(spellId, 0);
	}

	static inline int64_t CGUnit_C_OnAttackIconPressed(CGGuid* targetGuid) {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, CGGuid*, uint32_t, int32_t, int32_t, int32_t)>(Offsets::CGUnit_C_OnAttackIconPressed)(Globals::LocalPlayer->Ptr(), targetGuid, 0, 0, 0, 0);
	}

	static inline bool CGUnit_C_IsInCombat(int64_t playerPtr) {
		return reinterpret_cast<bool(__fastcall*)(int64_t)>(Offsets::CGUnit_C_IsInMelee)(playerPtr);
	}

	static inline void GuidToString(CGGuid* guid, char guidStr[])
	{
		// todo: no longer needed revert to guids
		Invoke<int64_t>(Offsets::GuidToString, (int64_t)guid, guidStr, 128);	// not sure why 128 ??? todo investigate
	}

	static inline uint32_t GetUnitReaction(WObject* unit) {
		typedef uint32_t(__thiscall* Unit_GetUnitReaction)(void*, void*);
		auto thisaddr = Globals::LocalPlayer;
		auto addr = unit;
		return ((Unit_GetUnitReaction)Offsets::UnitReaction)(thisaddr, addr);
	}

	using ClntObjMgr__GetMapId_Fn = uint32_t(__stdcall*)();
	static inline uint32_t ClntObjMgr__GetMapId() {
		auto const getMapIdFn = reinterpret_cast<ClntObjMgr__GetMapId_Fn>(
			Offsets::ClntObjMgrGetMapId);
		return (getMapIdFn)();
	}

	inline static long getCurrentTime() {
		LARGE_INTEGER frequency, counter;
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&counter);
		long currentTime = (counter.QuadPart * 1000) / frequency.QuadPart;
		return currentTime;
	}

	inline static bool GetCoolDown() {
		static std::mutex CooldownLock;
		static std::lock_guard<std::mutex> lock(CooldownLock);
		{
			uintptr_t Current = *reinterpret_cast<uintptr_t*>(Offsets::Cooldown + 0x10);
			if (!Current) return false;
			Cooldowns.clear(); /// Not sure if this works tho
			while ((int64_t)Current != 0 && ((int64_t)Current & 1) == 0)
			{
				auto cdObj = reinterpret_cast<CoolDownStruct*>(Current);
				if (cdObj->SpellID != 0 || cdObj->ItemID != 0) {
					/*	int CD1 = cdObj->CatRecoveryStart + cdObj->Recovery1 - (int)getCurrentTime();
						int CD2 = cdObj->GcdRecoveryStart + cdObj->Recovery1 - (int)getCurrentTime();
						int CD3 = cdObj->RecoveryStart + cdObj->Recovery1 - (int)getCurrentTime();		*/
					Cooldowns.push_back(*cdObj);
					Current = cdObj->Next;
				}
			}
		}
	}
};


//// framescript	
// 
// 
//static inline int64_t GameMethods::Execute(const std::string& command)
//{
//	return Execute(command.c_str());
//}
// 
//static inline int64_t GameMethods::Execute(const char* command)
//{
//	return reinterpret_cast<int64_t(__fastcall*)(int64_t, int64_t, int64_t)>(Offsets::Base + Offsets::FrameScriptExecute)(int64_t(command), int64_t("compat"), 0);
//}
/*static inline string GameMethods::GetText(const char* varName)
	{
		return reinterpret_cast<char* (__fastcall*)(const char*, int64_t, int, uint8_t)>(Offsets::Base + Offsets::FrameScriptGetText)(varName, -1, 0, 0);
	}

	static inline void Register(const char* scriptName, GameMethods::LuaCallback callback)
	{
		return reinterpret_cast<void(__fastcall*)(const char*, GameMethods::LuaCallback)>(Offsets::Base + Offsets::FrameScriptRegister)(scriptName, callback);
	}*/
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
