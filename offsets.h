#pragma once
#include "stdafx.h"
#include "Constants.h"
namespace Offsets
{
	////////////////////////
	//     1.13.6.36935    //
	////////////////////////

	// base address
	static inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));

	// framescript
	static inline uintptr_t FrameScriptExecute = 0x337390; // nope
	static inline uintptr_t FrameScriptGetText = 0x3AE0E0;	// OK
	static inline uintptr_t FrameScriptRegister = 0x3381D0;	// nope

	// lua
	static inline uintptr_t PushGuid = 0x3BAD20;			// Verify
	static inline uintptr_t PushNumber = 0x19B6AB0;			// OK
	static inline uintptr_t ToLString = 0x19B7C30;			// OK
	static inline uintptr_t ToNumber = 0x19B7CD0;			// ToNumber/ToInteger?
	static inline uintptr_t lua_gettop = 0x1665740;			// Nope
	static inline uintptr_t lua_settop = 0x19B7950;			// Verify

	static inline uintptr_t LoadFile = 0x1D6B600;			// NO
	static inline uintptr_t LuaState = 0x2E11B38;			// NO
	static inline uintptr_t PCall = 0x2584D0;				// NO
	static inline uintptr_t ToInteger = 0x19B7BB0;			// ToNumber/ToInteger?

	static inline uintptr_t PushClosure = 0x1665DE0;		// OK
	static inline uintptr_t PushString = 0x19B6AD0;			// OK
	static inline uintptr_t LuaGetTable = 0x1665710;		// OK
	//Lua
	static inline uintptr_t lua_isstring = 0x19B6290;		// OK
	static inline uintptr_t luaL_error = 0x19B8850;			// OK
	static inline uintptr_t lua_pushboolean = 0x19B6730;	// Verify
	static inline uintptr_t lua_createtable = 0x1CFC90;		// NO

	// State
	static inline uintptr_t InGame = 0x25C7388; // Retail addr

	// object manager
	static inline uintptr_t ClntObjMgrEnumVisibleObjectsPtr = 0xD79D40; // <== EC0 // 36325 0xB72B00; 
	static inline uintptr_t ObjMgrIsValid = 0xCA5AA0; // 36325 0xB739C0;					

	//Fastcall CTM(__int64 a1, __int64 a2) 
	// (s_Cvar_autoClearAFK + 92)
	static inline uintptr_t ClickToMove = 0xAEEF00;

	// pointers
	static inline uintptr_t InvalidPtrCheckMin = 0x2659A28;
	static inline uintptr_t InvalidPtrCheckMax = 0x2659A30;
	static inline uintptr_t CanPerformAction = 0x2D95200; // <== Retail addr
	static inline uintptr_t HardwareEventPtr = 0x0CA29C0;

	static inline uintptr_t Int3 = 0xFEADC;		// CC CC CC CC

	// units
	static inline uint16_t AnimationStatus = 0x14C;
	static inline uint16_t Owner = 0x534;
	static inline uint8_t Type = 0x20;

	//Camera
	static inline  uintptr_t CameraMgr = 0x25C7ED0;						
	static inline  uintptr_t CameraPtr = 0x3330;						
};

