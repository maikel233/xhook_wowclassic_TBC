#pragma once
#include "stdafx.h"
#include "Constants.h"
namespace Offsets
{
	////////////////////////
	//     2.5.2.41446   //
	////////////////////////

	// base address
	static inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));


	//Lua
	inline static uintptr_t lua_pushnumber = Base + 0x511E00;
	inline static uintptr_t lua_pushboolean = Base + 0x511E00;

	// framescript
	static inline uintptr_t FrameScriptExecute = 0x00;
	static inline uintptr_t FrameScriptGetText = 0x00;	// 
	static inline uintptr_t FrameScriptRegister = 0x08C7A70;	// 
	static inline uintptr_t FrameScript_RegisterFunctionNamespaceWithCount = 0x8C79C0;

	// Pointers
	static inline uintptr_t IsPlayerInWorld = Base + 0x30C2F24;// Script_IsPlayerInWorld or Script_GameMovieFinished 
	static inline uintptr_t LoadingScreen = Base + 0x00; // good //Reversed From Script_CanLogIn to CGlueMgr__CanLogIn
	static inline uintptr_t InWorld = Base + 0x00;
	static inline uintptr_t CGGameUI_s_inWorld = Base + 0x30C2F24; //   NotInitialized = 0, LoadingScreen1 = 3, LoadingScreen2 = 2, InGame = 4

	// object manager
	static inline uintptr_t ClntObjMgrEnumVisibleObjectsPtr = Base + 0x13E3EB0;
	static inline uintptr_t ClntObjMgrGetMapId = Base + 0x13E8680;
	static inline uintptr_t ClntObjMgrIsValid = Base + 0x13E8DF0;

	//CTM
	static inline uintptr_t ClickToMove = 0x161F1D0; // ~s_Cvar_deselectOnClick  xref one of those sub_loc is CGGameUI::OnTerrainClick.

	static inline uintptr_t FaceTo = 0x000;
	// pointers
	static inline uintptr_t InvalidPtrCheckMin = Base + 0x2E416C0;
	static inline uintptr_t InvalidPtrCheckMax = Base + 0x2E416C8;
	static inline uintptr_t HardwareEventPtr = Base + 0x2E1AE78;
	static inline uintptr_t CanPerformAction = 0x00;


	// Unit struct
	static inline uint8_t Type = 0x20;
	static inline uint16_t Guid = 0x58;
	static inline uint16_t AnimationStatus = 0x14C;
	inline static uint16_t	GatherStatus = 0x6B0;
	static inline uint16_t DisplayID = 0x003C;
	static inline uint16_t Owner = 0x534;

	//cast  
	static inline uintptr_t Spell_C_GetMinMaxRange = Base + 0x103F080;
	static inline uintptr_t Spell_C_GetSpellCoolDown = Base + 0x1041B60;
	static inline uintptr_t castSpell = Base + 0x16851F0; // From Spell_C_CastSpell not the function itself.
	static inline uintptr_t isSpellKnown = Base + 0x168EE60; // 
	static inline uintptr_t findSlotBySpellId = Base + 0x16874F0;

	//Globals
	static inline uintptr_t GetPlayerName = Base + 0x264270;
		
	static inline uintptr_t CorpseMapID = Base + 0x00;
	static inline uintptr_t Corpsex = Base + 0x2CAEAB0;  // Script_RetrieveCorpse -> First xmmword xref -> sub -> Under cintobjmgr first dword.  
	static inline uintptr_t Corpsey = Corpsex + 0x4;
	static inline uintptr_t Corpsez = Corpsex + 0x8;

	//Camera WorldFrame::GetActiveCamera
	static inline  uintptr_t CameraMgr = Base + 0x31A4CA8;
	static inline  uintptr_t CameraPtr = 0x38E0; // Shifted 8 bytes since 38631

	//ESP
	static inline uintptr_t GetWorld = Base + 0x214DE0; // Script_QuitGame, First Call, First DWORD.
	static inline uintptr_t WorldFrameIntersect = Base + 0x1A9F9D0; // F12, Search: Preload Immediate End -> DATA XREF: sub -> Sub below that, First Call and select second sub.

};

