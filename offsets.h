#pragma once
#include "stdafx.h"
#include "Constants.h"
namespace Offsets
{
	////////////////////////
	//     2.5.1.39170 //
	////////////////////////

	// base address
	static inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));

	// framescript
	static inline uintptr_t FrameScriptExecute = 0x7F7A80;
	static inline uintptr_t FrameScriptGetText = 0x7FD2C0;	// 
	static inline uintptr_t FrameScriptRegister = 0x7F94F0;	// 
	static inline uintptr_t FrameScript_RegisterFunctionNamespaceWithCount = 0x7F9CC0;

	//// Lua Outdated
	//inline static uintptr_t lua_createtable = Base; /*+ 0x19E5CC0;*/
	//inline static uintptr_t luaL_error = Base + 0x462450;
	//inline static uintptr_t lua_getfield = Base + 0x460000;
	//inline static uintptr_t lua_gettable = Base + 0x4600F0;
	//inline static uintptr_t lua_gettop = Base + 0x460120;
	//inline static uintptr_t lua_insert = Base + 0x4602A0;
	//inline static uintptr_t lua_isguid = Base + 0x80DAE0;
	//inline static uintptr_t lua_isnumber = Base + 0x460420;
	//inline static uintptr_t lua_isstring = Base + 0x460450;
	//inline static uintptr_t lua_isuserdata = Base + 0x460490;
	//inline static uintptr_t lua_newthread = Base; /*+ 0x19E69E0;*/
	//inline static uintptr_t lua_pcall = Base + 0x460790;
	//inline static uintptr_t lua_pushboolean = Base + 0x19E6C80;
	//inline static uintptr_t lua_pushcclosure = Base + 0x19E6CB0;
	//inline static uintptr_t lua_pushguid = Base + 0x80DC40;
	//inline static uintptr_t lua_pushinteger = Base + 0x460A20;
	//inline static uintptr_t lua_pushlightuserdata = Base + 0x19E6F40;
	//inline static uintptr_t lua_pushnil = Base + 0x456020;    39170
	//inline static uintptr_t lua_pushnumber = Base + 0x456040; 39170
	//inline static uintptr_t lua_pushstring = Base + 0x456060; 39170
	//inline static uintptr_t lua_rawget = Base + 0x460D60; // _lua_rawgeti 0x460E10
	//inline static uintptr_t lua_rawset = Base + 0x460ED0;
	//inline static uintptr_t lua_remove = Base + 0x4610B0;
	//inline static uintptr_t lua_setfield = Base + 0x4613D0;
	//inline static uintptr_t lua_settable = Base + 0x461520;
	//inline static uintptr_t lua_settop = Base + 0x461570;
	//inline static uintptr_t lua_toboolean = Base + 0x461770;
	//inline static uintptr_t lua_toguid = Base + 0x80DD00;
	//inline static uintptr_t lua_tointeger = Base + 0x4617D0;
	//inline static uintptr_t lua_tolstring = Base + 0x456D80; 39170
	//inline static uintptr_t lua_tonumber = Base + 0x456E20; 
	//inline static uintptr_t lua_type = Base + 0x461A00;
	//inline static uintptr_t luaL_loadfile = Base + 0x19E94F0;
	//inline static uintptr_t luaL_ref = Base; /*0x19E9CB0*/
	//// DUMP: _lua_getstack 0x0464C30; 

	// Pointers
	static inline uintptr_t InGame = Base + 0x2F165B0;// Script_IsPlayerInWorld
	static inline uintptr_t LoadingScreen = Base + 0x2BEFE00; // good //Reversed From Script_CanLogIn to CGlueMgr__CanLogIn
	static inline uintptr_t InWorld = Base + 0x00;
	static inline uintptr_t CGGameUI_s_inWorld = Base + 0x2F165B0; //   NotInitialized = 0, LoadingScreen1 = 3, LoadingScreen2 = 2, InGame = 4

	// object manager
	static inline uintptr_t ClntObjMgrEnumVisibleObjectsPtr = Base + 0x12DECA0;
	static inline uintptr_t ClntObjMgrGetMapId = Base + 0x12E3A40;
	static inline uintptr_t ClntObjMgrIsValid = Base + 0x12E41B0;

	//CTM
	static inline uintptr_t ClickToMove = 0x00; //

	static inline uintptr_t FaceTo = 0x113FAF0;
	// pointers
	static inline uintptr_t InvalidPtrCheckMin = Base + 0x2C9DF30;
	static inline uintptr_t InvalidPtrCheckMax = Base + 0x2C9DF38;
	static inline uintptr_t HardwareEventPtr = Base + 0x2C75D98;
	static inline uintptr_t CanPerformAction = 0x00;

	// Register
	inline static uintptr_t Int3 = Base + 0x00;//0x2BCC3C;

	// Unit struct
	static inline uint8_t Type = 0x20;
	static inline uint16_t Guid = 0x58;
	static inline uint16_t AnimationStatus = 0x14C;
	inline static uint16_t	GatherStatus = 0x6B0;
	static inline uint16_t DisplayID = 0x003C;
	static inline uint16_t Owner = 0x534;

	//cast  
	static inline uintptr_t Spell_C_GetMinMaxRange = Base + 0xF33EA0;//0xF5E440;/*0xF043C0;*/ // Unsure about this one...
	static inline uintptr_t Spell_C_GetSpellCoolDown = Base + 0xF36970;//0xF60F10;
	static inline uintptr_t castSpell = Base + 0xF2E0A0;
	static inline uintptr_t isSpellKnown = Base + 0x155AC90;
	static inline uintptr_t findSlotBySpellId = Base + 0x15536E0;

	//static inline uintptr_t s_spellHistory = Base + 0x2CCFB80;

	//Globals
	static inline uintptr_t GetPlayerName = Base + 0x2C03B58; //0x29F8918;
		
	static inline uintptr_t CorpseMapID = Base + 0x2B0C070;
	static inline uintptr_t Corpsex = Base + 0x00;  // float x,y,z is gone Decompile -> 0x14FA330
	static inline uintptr_t Corpsey = Corpsex + 0x4;
	static inline uintptr_t Corpsez = Corpsex + 0x8;

	//Camera WorldFrame::GetActiveCamera
	static inline  uintptr_t CameraMgr = Base + 0x2FFA740; // //wowclassic 0x291A250;
	static inline  uintptr_t CameraPtr = 0x38D8; // wowclassic 0x3330;

};

