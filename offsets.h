#pragma once
#include "stdafx.h"
#include "Constants.h"
namespace Offsets
{
	////////////////////////
	//     2.5.1.39640 //
	////////////////////////

	// base address
	static inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));

	// framescript
	static inline uintptr_t FrameScriptExecute = 0x00;
	static inline uintptr_t FrameScriptGetText = 0x00;	// 
	static inline uintptr_t FrameScriptRegister = 0x806460;	// 
	static inline uintptr_t FrameScript_RegisterFunctionNamespaceWithCount = 0x00;

	// Pointers
	static inline uintptr_t InGame = Base + 0x2EA55B0;// Script_IsPlayerInWorld
	static inline uintptr_t LoadingScreen = Base + 0x00; // good //Reversed From Script_CanLogIn to CGlueMgr__CanLogIn
	static inline uintptr_t InWorld = Base + 0x00;
	static inline uintptr_t CGGameUI_s_inWorld = Base + 0x2EA55B0; //   NotInitialized = 0, LoadingScreen1 = 3, LoadingScreen2 = 2, InGame = 4

	// object manager
	static inline uintptr_t ClntObjMgrEnumVisibleObjectsPtr = Base + 0x129D9C0;
	static inline uintptr_t ClntObjMgrGetMapId = Base + 0x12A1760;
	static inline uintptr_t ClntObjMgrIsValid = Base + 0x12A1ED0;

	//CTM
	static inline uintptr_t ClickToMove = 0x00; //CGGameUI::HandleTerrainClick

	static inline uintptr_t FaceTo = 0x000;
	// pointers
	static inline uintptr_t InvalidPtrCheckMin = Base + 0x2C2CF30;
	static inline uintptr_t InvalidPtrCheckMax = Base + 0x2C2CF38;
	static inline uintptr_t HardwareEventPtr = Base + 0x2B9B750;
	static inline uintptr_t CanPerformAction = 0x00;


	// Unit struct
	static inline uint8_t Type = 0x20;
	static inline uint16_t Guid = 0x58;
	static inline uint16_t AnimationStatus = 0x14C;
	inline static uint16_t	GatherStatus = 0x6B0;
	static inline uint16_t DisplayID = 0x003C;
	static inline uint16_t Owner = 0x534;

	//cast  
	static inline uintptr_t Spell_C_GetMinMaxRange = Base + 0xEFD590;
	static inline uintptr_t Spell_C_GetSpellCoolDown = Base + 0xF00060;
	static inline uintptr_t castSpell = Base + 0xEF7790; // From Spell_C_CastSpell not the function itself.
	static inline uintptr_t isSpellKnown = Base + 0x14FE6E0;
	static inline uintptr_t findSlotBySpellId = Base + 0x1509BB0;

	//Globals
	static inline uintptr_t GetPlayerName = Base + 0x264270;
		
	static inline uintptr_t CorpseMapID = Base + 0x00;/
	static inline uintptr_t Corpsex = Base + 0x00;  // float x,y,z is gone Decompile -> 0x14FA330
	static inline uintptr_t Corpsey = Corpsex + 0x4;
	static inline uintptr_t Corpsez = Corpsex + 0x8;

	//Camera WorldFrame::GetActiveCamera
	static inline  uintptr_t CameraMgr = Base + 0x2F89740;
	static inline  uintptr_t CameraPtr = 0x38D8; // wowclassic 0x3330;

};

