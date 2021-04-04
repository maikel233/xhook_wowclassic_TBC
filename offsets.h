#pragma once
#include "stdafx.h"
#include "Constants.h"
namespace Offsets
{
	////////////////////////
	//    1.13.6.37497    //
	////////////////////////
	
	//All offsets with ** are probably wrong or outdated.

	// base address
	static inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));

	// framescript
	static inline uintptr_t FrameScriptExecute = 0x3A2DA0; 		//  Verify
	static inline uintptr_t FrameScriptGetText = 0x39D160;		// 
	static inline uintptr_t FrameScriptRegister = 0x3A4CE0;		// 

	// lua
	static inline uintptr_t PushGuid = 0x3BAD20;			// **
	static inline uintptr_t PushNumber = 0x19B6AB0;			// **
	static inline uintptr_t ToLString = 0x19B7C30;			// **
	static inline uintptr_t ToNumber = 0x19B7CD0;			// **
	static inline uintptr_t lua_gettop = 0x1665740;			// **
	static inline uintptr_t lua_settop = 0x19B7950;			// **

	static inline uintptr_t LoadFile = 0x1D6B600;			// **
	static inline uintptr_t LuaState = 0x2E11B38;			// **
	static inline uintptr_t PCall = 0x2584D0;			// **
	static inline uintptr_t ToInteger = 0x19B7BB0;			// ToNumber/ToInteger**

	static inline uintptr_t PushClosure = 0x1665DE0;		// **
	static inline uintptr_t PushString = 0x19B6AD0;			// **
	static inline uintptr_t LuaGetTable = 0x1665710;		// **
	//Lua
	static inline uintptr_t lua_isstring = 0x19B6290;		// **
	static inline uintptr_t luaL_error = 0x19B8850;			// **
	static inline uintptr_t lua_pushboolean = 0x19B6730;		// **
	static inline uintptr_t lua_createtable = 0x1CFC90;		// **

	// State
	static inline uintptr_t InGame = 0x28B6368; 			//

	// object manager
	static inline uintptr_t ClntObjMgrEnumVisibleObjectsPtr = 0xD39130; 
	static inline uintptr_t ObjMgrIsValid = 0xD3A010; 					

	//Fastcall CTM(__int64 a1, __int64 a2) nearby -> (s_Cvar_autoClearAFK + 92)
	static inline uintptr_t ClickToMove = 0xA9E590; 		//

	// pointers
	static inline uintptr_t InvalidPtrCheckMin = 0x25FBA38; 	//
	static inline uintptr_t InvalidPtrCheckMax = 0x25FBA40;  	//
	static inline uintptr_t CanPerformAction = 0x2D95200; 		// **
	static inline uintptr_t HardwareEventPtr = 0x0CA29C0; 		// **

	static inline uintptr_t Int3 = 0xFEADC;				// CC CC CC CC  **

	// units
	static inline uint16_t AnimationStatus = 0x14C;			//
	static inline uint16_t Owner = 0x534;				//
	static inline uint8_t Type = 0x20;				//

	//Camera 
	static inline  uintptr_t CameraMgr = 0x28B6EC0;			//	
	static inline  uintptr_t CameraPtr = 0x3330;			//						
};

