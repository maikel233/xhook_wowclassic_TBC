#pragma once
#include "stdafx.h"
#include "Constants.h"
#include "Globals.h"
#include <mutex>
#include <minmax.h>
#include "WObject.h"

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
		uint64_t* s_curMgr = reinterpret_cast<uint64_t*>(Offsets::Base + Offsets::ClntObjMgrIsValid);
		return reinterpret_cast<bool(__fastcall*)(uint64_t*, int8_t)>(Offsets::Base + Offsets::ClntObjMgrIsValid)(s_curMgr, param); /*sub_1E27A0(qword_2F99010, 376i64, param);*/
	}

	static int64_t CGUnit_C_OnJumpLocal() {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t PlayerPtr, int8_t)>(Offsets::Base + Offsets::CGUnit_C_OnJumpLocal)(Globals::LocalPlayer->Ptr(), 0);
	}

	static int64_t CGUnit_C_OnSwimStartLocal() {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t PlayerPtr, int8_t)>(Offsets::Base + Offsets::CGUnit_C_OnSwimStartLocal)(Globals::LocalPlayer->Ptr(), 0);
	}
	static int64_t CGUnit_C_OnFlightLocal() {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t PlayerPtr, int8_t)>(Offsets::Base + Offsets::CGUnit_C_OnFlightLocal)(Globals::LocalPlayer->Ptr(), 0);
	}

	static int64_t IsPlayerMoving() {
		return reinterpret_cast<bool(__fastcall*)(int64_t PlayerPtr, int8_t)>(Offsets::Base + Offsets::CGUnit_C_OnJumpLocal)(Globals::LocalPlayer->Ptr(), 0);
	}

	static inline float WorldGetFrameRate(float_t* param)
	{	
		return reinterpret_cast<float(__fastcall*)(float_t*)>(Offsets::Base + Offsets::World_GetFrameRatems)(param); /*sub_1E27A0(qword_2F99010, 376i64, param);*/ //0xEC5D20 alt tapped max fps?
	}

	//CGUnit_C::SetTrackingPosition
	static inline void ClickToMove(int64_t playerPtr, Vector3 position)
	{
		return reinterpret_cast<void(__fastcall*)(int64_t, Vector3&, int16_t)>(Offsets::Base + Offsets::CGUnit_C_SetTrackingPosition)(playerPtr, position, 5);
	}


	static int64_t FaceTo(int64_t playerPtr, float_t angle)
	{
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, float_t angle)>(Offsets::Base + Offsets::FaceTo)(playerPtr, angle);
	}

	static int64_t SpriteLeftClick(CGGuid* TargetGuid) {
		return reinterpret_cast<int64_t(__fastcall*)(CGGuid*)>(Offsets::Base + Offsets::SpriteLeftClick)(TargetGuid);
	}
	static int64_t SpriteRightClick(CGGuid* TargetGuid) {
		return reinterpret_cast<int64_t(__fastcall*)(CGGuid*)>(Offsets::Base + Offsets::SpriteRightClick)(TargetGuid);
	}

	//CGlueMgr::QuitGame(char quit, char forceLogout, char forceQuit)
	static int64_t Player_ForceLogout() {

		return reinterpret_cast<int64_t(__fastcall*)(int64_t, int64_t, int64_t)>(Offsets::Base + Offsets::ClientConnection_CharacterLogout)(1, 1, 0);
	}
	static int64_t Player_Quit() {

		return reinterpret_cast<int64_t(__fastcall*)()>(Offsets::Base + Offsets::CGlueMgr_QuitGame)();
	}

	static int64_t Player_Dismount() {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t)>(Offsets::Base + Offsets::CGUnit_C_Dismount)(Globals::LocalPlayer->Ptr());
	}


	//const uint64_t GameObjectIsLocked = 0x1499A40; // bool (CGGameObject* go, int64/*=0*/, int64/*=0*/, int64/*=0*/, int64/*=0*/, int64/*=0*/)

	//char __fastcall sub_140BBD0(__int64 a1, unsigned int *a2, _DWORD *a3, int *a4, __int64 *a5, unsigned int *a6)
	static inline bool CGGameObject_C_IsLocked(WObject* CGObj) {
		return reinterpret_cast<bool(__fastcall*)(int64_t, int64_t, int64_t, int64_t, int64_t, int64_t)>(Offsets::Base + Offsets::CGGameObject_C_IsLocked)(CGObj->Ptr(), 0, 0, 0, 0, 0);
	}

	static int64_t CGGameObject_C_CanUse(WObject* CGObj) {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t)>(Offsets::Base + Offsets::CGUnit_C_Dismount)(CGObj->Ptr());
	}
	static int64_t CGGameObject_C_CanUseNow(WObject* CGObj) {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t)>(Offsets::Base + Offsets::CGUnit_C_Dismount)(CGObj->Ptr());
	}

	//__int64 __fastcall CGPlayer_C::HandleRepopRequest(__int64 a1, char a2)
	static int64_t RepopMe() {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, int32_t)>(Offsets::Base + Offsets::CGPlayer_C_HandleRepopRequest)(Globals::LocalPlayer->Ptr(), 1);
	}
	//CGPlayer_C::AcceptResurrectRequest(RESURRECT_CLIENT_RESPONSE)
	//static int64_t RetrieveCorpse(int64_t activePlayerPtr, int32_t ClientResponse) {
	//	return reinterpret_cast<int64_t(__fastcall*)(int64_t, int32_t)>(Offsets::RetrieveCorpse)(activePlayerPtr, ClientResponse);
	//}
	//__int64 __usercall CGPlayer_C::CombatModeLeave@<rax>(CGPlayer_C *this@<rcx>, unsigned int a2@<edx>, float a3@<xmm0>)

	//GameMethods::Invoke<uintptr_t>(Offsets::Movement_ToggleControlBit, Offsets::Movement_InputControl, 0x20, (int32_t)1, (uint32_t)GetTickCount(), (uint8_t)0);

	static inline void ToggleControlBit(ControlBits ControlBit, int32_t Enable) {
		Invoke<uintptr_t>(Offsets::Base + Offsets::Movement_ToggleControlBit, Offsets::Base + Offsets::Movement_InputControl, ControlBit, Enable, (uint32_t)GetTickCount(), (uint8_t)0);
	}


	// SpellBookFindSpellByName(v48, &v53);


	//__int64 __fastcall SpellBookFindSpellByName(char *a1, _BYTE *a2)
	//Maybe bool or uint CGSpellBook::FindSpellByName(v8, (const char *)&v64);
	static inline int64_t SpellBook_FindSpellByName(const char* SpellName) {
		uint64_t Spell = 0;
		return reinterpret_cast<int64_t(__fastcall*)(const char*, uint64_t*)>(Offsets::Base + Offsets::SpellBook_FindSpellByName)(SpellName, &Spell);
	}
	// SPELL_C_
	static inline bool Spell_C_IsCurrentSpell(int SpellId) {
		typedef bool(__cdecl* tIsCurrentSpellBySpellId)(int);
		tIsCurrentSpellBySpellId IsCurrentSpellBySpellId = (tIsCurrentSpellBySpellId)(Offsets::Base + Offsets::Spell_C_IsCurrentSpell);
		return IsCurrentSpellBySpellId(SpellId);
	}
	static inline bool Spell_C_RangeCheckSelected(int32_t SpellId, CGGuid* TargetGuid, bool* Range) {
		return reinterpret_cast<bool(__fastcall*)(int64_t playerPtr, int32_t spellid, CGGuid*, bool*, int64_t*, int64_t)>(Offsets::Base + Offsets::Spell_C_RangeCheckSelected)(Globals::LocalPlayer->Ptr(), SpellId, TargetGuid, Range, 0, 0);
	}
	static inline int64_t Spell_C_GetMinMaxSpellRange(int32_t SpellId, float_t* MinRange, float_t* MaxRange, CGGuid* TargetGuid) {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t playerPtr, int32_t spellid, float_t*, float_t*, CGGuid*, int64_t)>(Offsets::Base + Offsets::Spell_C_GetMinMaxRange)(Globals::LocalPlayer->Ptr(), SpellId, MinRange, MaxRange, TargetGuid, 0);
	}

	static inline bool Spell_C_HaveSpellPower(int32_t spellId) {
		uint32_t unk0 = 0;
		uint32_t unk1 = 0;
		return reinterpret_cast<bool(__fastcall*)(int64_t, int32_t, uint32_t * flag1, uint32_t * flag2)>(Offsets::Base + Offsets::Spell_C_HaveSpellPower)(Globals::LocalPlayer->Ptr(), spellId, &unk0, &unk1);
	}

	static inline int64_t Spell_C_CastSpell(int32_t spellSlot, CGGuid* targetGuid) {
		return reinterpret_cast<int64_t(__fastcall*)(int32_t, int32_t, CGGuid*, uint8_t, uint8_t)>(Offsets::Base + Offsets::Spell_C_CastSpell)(spellSlot, 0, targetGuid, 0, 0);
	}



	//static void HandleTerrainClick(Vector3 pos) {
	//	uint64_t dummy = 0;
	//	struct  TerainClick
	//	{
	//		CGGuid Guid;
	//		Vector3 Pos;
	//		int clickType;
	//	};

	//	TerainClick t;
	//	t.Pos = pos;
	//	GameMethods::Invoke<bool>(Offsets::Base + Offsets::Spell_HandleTerrainClick, &t, dummy);
	//}


	
	static inline bool Spell_C_GetSpellCooldown(uint32_t spellId, int64_t* duration, int64_t* startTime, int64_t* modRate) {
		return reinterpret_cast<bool(__fastcall*)(uint32_t /* SpellId*/, int32_t /* Unk*/, int32_t/* isPet*/, int64_t* /* Duration*/, int64_t* /* StartTime*/, int64_t* /* IsEnabled??*/, int64_t* /* UNK3*/, int64_t*, int64_t*)>(Offsets::Base + Offsets::Spell_C_GetSpellCoolDown)(spellId, 0, 0, duration, startTime, 0, 0, 0, modRate);
	}
	
	// Spell_C_CancelSpell(v19, 1, 1, 30u);
	//__int64 __fastcall StopCasting(__int64 a1, char a2, char a3, unsigned int a4)
	static inline int64_t StopCastingSpell(int64_t a1) {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, int32_t, int32_t, int32_t)>(Offsets::Base + Offsets::Spell_C_CastSpell)(a1, 1, 1 , 30);
	}


	//const uint64_t SpellCancelChannel = 0x1351D80; // bool (int32 spellId, int32 reason/*=40*/) 

	static inline int64_t StopChannelingSpell(int64_t spellid) {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, int32_t)>(Offsets::Base + Offsets::Spell_C_CancelChannel)(spellid, 40);
	}


	//
	static inline bool IsSpellKnown(int32_t spellId) {
		return reinterpret_cast<bool(__fastcall*)(int32_t, int32_t)>(Offsets::Base + Offsets::Spell_isSpellKnown)(spellId, 0);
	}

	static inline int64_t FindSlotBySpellId(int32_t spellId) {
		return reinterpret_cast<int64_t(__fastcall*)(int32_t, int32_t)>(Offsets::Base + Offsets::SpellBook_FindSlotBySpellId)(spellId, 0);
	}

	static inline int64_t CGUnit_C_OnAttackIconPressed(CGGuid* targetGuid) {
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, CGGuid*, uint32_t, int32_t, int32_t, int32_t)>(Offsets::Base + Offsets::CGUnit_C_OnAttackIconPressed)(Globals::LocalPlayer->Ptr(), targetGuid, 0, 0, 0, 0);
	}

	static inline bool CGUnit_C_IsInCombat(int64_t playerPtr) {
		return reinterpret_cast<bool(__fastcall*)(int64_t)>(Offsets::Base + Offsets::CGUnit_C_IsInMelee)(playerPtr);
	}

	static inline void GuidToString(CGGuid* guid, char guidStr[])
	{
		// todo: no longer needed revert to guids
		Invoke<int64_t>(Offsets::Base + Offsets::GuidToString, (int64_t)guid, guidStr, 128);	// not sure why 128 ??? todo investigate
	}

	static inline uint32_t GetUnitReaction(WObject* unit) {
		typedef uint32_t(__thiscall* Unit_GetUnitReaction)(void*, void*);
		auto thisaddr = Globals::LocalPlayer;
		auto addr = unit;
		return ((Unit_GetUnitReaction)(Offsets::Base + Offsets::Unit_IsFriendly))(thisaddr, addr);
	}


	using ClntObjMgr__GetMapId_Fn = uint32_t(__stdcall*)();
	static inline uint32_t ClntObjMgr__GetMapId() {
		auto const getMapIdFn = reinterpret_cast<ClntObjMgr__GetMapId_Fn>(
			Offsets::Base + Offsets::ClntObjMgrGetMapId);
		return (getMapIdFn)();
	}
	
	//Removed GetSkillLvls 
	//Removed Skillstuff
	//Removed More
	//More more
	// more more more
	//Gamebreaking stuff cant release this yet...
	
	//Removed Item stuff
	//More item stuff

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
			uintptr_t Current = *reinterpret_cast<uintptr_t*>(Offsets::Base + Offsets::CoolDown + 0x10);
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
