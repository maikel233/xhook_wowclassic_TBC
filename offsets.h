#pragma once
#include "stdafx.h"
#include "Constants.h"
namespace Offsets
{
	////////////////////////
	//     1.13.7.38386  //
	////////////////////////

	// base address
	static inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));

	// framescript
	static inline uintptr_t FrameScriptExecute = 0x13FC5FE; // Unsure of this one  
	static inline uintptr_t FrameScriptGetText = 0x3A3750;	// 
	static inline uintptr_t FrameScriptRegister = 0x3AB350;	// 

	// lua
	static inline uintptr_t lua_PushNil = 0x198AF30;			
	static inline uintptr_t lua_PushGuid = 0x3AFEE0;			
	static inline uintptr_t lua_PushNumber = 0x198AF50;			
	static inline uintptr_t lua_PushInteger = 0x198AE60;
	static inline uintptr_t lua_PushBoolean = 0x198ABD0;
	static inline uintptr_t lua_PushClosure = 0x0;				
	static inline uintptr_t lua_PushString = 0x198AF70;			
	static inline uintptr_t lua_pushboolean = 0x1976C20;	

	static inline uintptr_t lua_ToLString = 0x198C0D0;			
	static inline uintptr_t lua_ToInteger = 0x195A7B0;
	static inline uintptr_t lua_ToNumber = 0x198C050;		
	static inline uintptr_t lua_gettop = 0x1974FD0;			
	static inline uintptr_t lua_settop = 0x198BDF0;			
	static inline uintptr_t lua_createtable = 0x0;			
	static inline uintptr_t lua_GetTable = 0x198A370;

	static inline uintptr_t lua_LoadFile = 0x0;		
	static inline uintptr_t lua_PCall = 0x0;
	static inline uintptr_t lua_State = 0x25C29E8;									
	static inline uintptr_t lua_type = 0x198C280;

	static inline uintptr_t lua_isNumber = 0x198A700;
	static inline uintptr_t lua_isstring = 0x198A730;		
	static inline uintptr_t luaL_error = 0x195B450;			// 
	
	// State
	static inline uintptr_t InGame = 0x28A26A4;
	static inline uintptr_t LoadingScreen = 0x2586630;

	// object manager
	static inline uintptr_t ClntObjMgrEnumVisibleObjectsPtr = 0xD5A590;
	static inline uintptr_t ClntObjMgrGetMapId = 0xA62820;
	static inline uintptr_t J_ClntObjMgrGetMapId = 0x5AD30;
	static inline uintptr_t ClntObjMgrIsValid = 0xD5B3F0;
	static inline uintptr_t ClntObjMgrLocalPlayerGUID = 0x299A8E0;
	static inline uintptr_t ClntObjMgrTargetGUID = 0x24F3900;
	static inline uintptr_t ClntObjMgrPetGUID = 0x28CA66C;
	 
	//CTM
	static inline uintptr_t ClickToMove = 0xACE6A0;

	// pointers
	static inline uintptr_t InvalidPtrCheckMin = 0x2600D78;
	static inline uintptr_t InvalidPtrCheckMax = 0x2600D80;
	static inline uintptr_t CanPerformAction = 0x00; 
	static inline uintptr_t HardwareEventPtr = 0x25D95C0;

	static inline uintptr_t Int3 = 0xFEADC;		// CC CC CC CC

	// Unit struct
	static inline uint16_t Guid = 0x58;
	static inline uint16_t AnimationStatus = 0x14C;
	static inline uint16_t Owner = 0x534;
	static inline uint8_t Type = 0x20;

	//cast  
	static inline uintptr_t castSpell = 0xFF0610;
	static inline uintptr_t isSpellKnown = 0xFFA800;
	static inline uintptr_t isSpellInRange = 0xFE02D0;
	static inline uintptr_t iscurrentspell = 0x990BE0;
	static inline uintptr_t findSlotBySpellId = 0xFF2920;

	//Globals
	static inline uintptr_t LootWindow = 0x28CB0A0;
	static inline uintptr_t GetPlayerName = 0x299A8F8;
	static inline uintptr_t GetRealmName = 0x2807650;

	//Corpse 
	static inline uintptr_t Corpsex = 0x24EB800;
	static inline uintptr_t Corpsey = 0x24EB804;
	static inline uintptr_t Corpsez = 0x24EB808;

	//Camera 
	static inline  uintptr_t CameraMgr = 0x28BC230;
	static inline  uintptr_t CameraPtr = 0x3330;		

};

