#pragma once
#include "stdafx.h"
#include "Constants.h"
namespace Offsets
{
	////////////////////////
	//     2.5.1.39475 //
	////////////////////////

	// base address
	static inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));

	// framescript
	static inline uintptr_t FrameScriptExecute = 0x00;
	static inline uintptr_t FrameScriptGetText = 0x00;	// 
	static inline uintptr_t FrameScriptRegister = 0x00;	// 
	static inline uintptr_t FrameScript_RegisterFunctionNamespaceWithCount = 0x7F9CC0;

	// Pointers
	static inline uintptr_t InGame = Base + 0x2F525A8;// Script_IsPlayerInWorld
	static inline uintptr_t LoadingScreen = Base + 0x2C2BE00; // good //Reversed From Script_CanLogIn to CGlueMgr__CanLogIn
	static inline uintptr_t InWorld = Base + 0x00;
	static inline uintptr_t CGGameUI_s_inWorld = Base + 0x2F525A8; //   NotInitialized = 0, LoadingScreen1 = 3, LoadingScreen2 = 2, InGame = 4

	// object manager
	static inline uintptr_t ClntObjMgrEnumVisibleObjectsPtr = Base + 0x1303890;
	static inline uintptr_t ClntObjMgrGetMapId = Base + 0x13055E0;
	static inline uintptr_t ClntObjMgrIsValid = Base + 0x1305D50;

	//CTM
	static inline uintptr_t ClickToMove = 0x113F5C0; //CGGameUI::HandleTerrainClick

	static inline uintptr_t FaceTo = 0x11640B0;
	// pointers
	static inline uintptr_t InvalidPtrCheckMin = Base + 0x2CD9F20;
	static inline uintptr_t InvalidPtrCheckMax = Base + 0x2CD9F28;
	static inline uintptr_t HardwareEventPtr = Base + 0x2CB1D88;
	static inline uintptr_t CanPerformAction = 0x00;


	// Unit struct
	static inline uint8_t Type = 0x20;
	static inline uint16_t Guid = 0x58;
	static inline uint16_t AnimationStatus = 0x14C;
	inline static uint16_t	GatherStatus = 0x6B0;
	static inline uint16_t DisplayID = 0x003C;
	static inline uint16_t Owner = 0x534;

	//cast  
	static inline uintptr_t Spell_C_GetMinMaxRange = Base + 0xF7E8F0;
	static inline uintptr_t Spell_C_GetSpellCoolDown = Base + 0xF813C0;
	static inline uintptr_t castSpell = Base + 0xF78AF0; // From Spell_C_CastSpell not the function itself.
	static inline uintptr_t isSpellKnown = Base + 0x15840E0;
	static inline uintptr_t findSlotBySpellId = Base + 0x157CB30;

	//Globals
	static inline uintptr_t GetPlayerName = Base + 0x2C3FB58;
		
	static inline uintptr_t CorpseMapID = Base + 0x00;//0x2B0C070;
	static inline uintptr_t Corpsex = Base + 0x00;  // float x,y,z is gone Decompile -> 0x14FA330
	static inline uintptr_t Corpsey = Corpsex + 0x4;
	static inline uintptr_t Corpsez = Corpsex + 0x8;

	//Camera WorldFrame::GetActiveCamera
	static inline  uintptr_t CameraMgr = Base + 0x3036730;
	static inline  uintptr_t CameraPtr = 0x38D8; // wowclassic 0x3330;

};

