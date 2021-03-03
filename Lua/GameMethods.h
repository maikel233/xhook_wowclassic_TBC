#pragma once
#include "stdafx.h"
#include "Constants.h"
using namespace std;

class GameMethods
{
public:
	// typedefs
	typedef unsigned int(__fastcall* EnumVisibleObjectsCb)(int64_t, int64_t);
	typedef signed int(__fastcall* LuaCallback)(int64_t luaState);

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

	// lua

	static inline int64_t LuaSetTop(int64_t l, const int32_t a2)
	{
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, int32_t)>(Offsets::Base + Offsets::lua_settop)(l, a2);
	}

	static inline int64_t LuaGetTop(int64_t l)
	{
		return reinterpret_cast<int64_t(__fastcall*)(int64_t)>(Offsets::Base + Offsets::lua_gettop)(l);
	}

	static inline int64_t LuaError(int64_t l, const char* msg)
	{
		return reinterpret_cast<int64_t(__cdecl*)(int64_t, const char*)>(Offsets::Base + Offsets::luaL_error)(l, msg);
	}

	static inline int64_t LoadFile(int64_t luaState, int64_t path)
	{
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, int)>(Offsets::Base + Offsets::LoadFile)(luaState, path);
	}
	static inline int64_t PCall(int64_t luaState, int a, int b, int c)
	{
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, int, int, int)>(Offsets::Base + Offsets::PCall)(luaState, a, b, c);
	}
	static int64_t PushClosure(int64_t luaState, int64_t fn, int n)
	{
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, int64_t, int)>(Offsets::Base + Offsets::PushClosure)(luaState, fn, n);
	}
	static void PushGuid(int64_t luaState, uintptr_t guidPtr)
	{
		return reinterpret_cast<void(__fastcall*)(int64_t, uintptr_t)>(Offsets::Base + Offsets::PushGuid)(luaState, guidPtr);
	}
	static inline int64_t PushNumber(int64_t luaState, double value)
	{
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, double)>(Offsets::Base + Offsets::PushNumber)(luaState, value);
	}
	static int64_t PushString(int64_t luaState, int64_t value)
	{
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, int64_t)>(Offsets::Base + Offsets::PushString)(luaState, value);
	}
	static int64_t ToInteger(int64_t luaState, int idx)
	{
		return reinterpret_cast<int64_t(__fastcall*)(int64_t, int)>(Offsets::Base + Offsets::ToInteger)(luaState, idx);
	}
	static string ToLString(int64_t luaState, int64_t index, uintptr_t* len)
	{
		return reinterpret_cast<char* (__fastcall*)(int64_t, int64_t, uintptr_t*)>(Offsets::Base + Offsets::ToLString)(luaState, index, len);
	}

	static bool LuaIsString(int64_t luastate, const int64_t len)
	{
		return reinterpret_cast<bool(__fastcall*)(int64_t, int64_t)>(Offsets::Base + Offsets::lua_isstring)(luastate, len);
	}

	static double ToNumber(int64_t luaState, int idx)
	{
		return reinterpret_cast<double(__fastcall*)(int64_t, int)>(Offsets::Base + Offsets::ToNumber)(luaState, idx);
	}

	// object manager
	static inline bool ObjMgrIsValid(uint8_t param)
	{
		return reinterpret_cast<bool(__fastcall*)(int8_t)>(Offsets::Base + Offsets::ObjMgrIsValid)(param);
	}
	static inline char EnumVisibleObjects(EnumVisibleObjectsCb callback, int64_t filter)
	{
		return reinterpret_cast<char(__fastcall*)(GameMethods::EnumVisibleObjectsCb, int64_t)>(Offsets::Base + Offsets::ClntObjMgrEnumVisibleObjectsPtr)(callback, filter);
	}

	// ctm
	static inline void ClickToMove(int64_t playerPtr, Vector3& position)
	{
		return reinterpret_cast<void(__fastcall*)(int64_t, Vector3&)>(Offsets::Base + Offsets::ClickToMove)(playerPtr, position);
	}
};



//class GameMethods
//{
//public:
//    // typedefs
//    typedef signed int(__fastcall* LuaCallback)(int64_t luaState);
//    typedef unsigned int(__fastcall* EnumVisibleObjectsCb)(int64_t, int64_t);
//
//    // framescript
//    static int64_t Execute(const char*);
//    static int64_t Execute(const std::string&);
//    static string GetText(const char*);
//    static void Register(const char*, LuaCallback);
//
// // lua
// //   static int64_t PCall(int64_t luaState, int a, int b, int c);
// //   static int64_t LoadFile(int64_t luaState, int64_t path);
//    static void PushGuid(int64_t, uintptr_t);
//    static int64_t PushNumber(int64_t, double);
//    static string ToLString(int64_t, int64_t, uintptr_t*);
//    static bool LuaIsString(uintptr_t*, const int64_t);
//    static int64_t ToNumber(int64_t, int64_t);
//    static int64_t LuaError(int64_t, const char*);
//
//    static int64_t LuaSetTop(int64_t, const int32_t);
//    static int64_t LuaGetTop(int64_t);
//
//
////  static int64_t ToInteger(int64_t luaState, int idx);
//    // object manager
//    static int64_t EnumVisibleObjects(EnumVisibleObjectsCb, int64_t);
//    static bool ObjMgrIsValid(uint8_t);
//
//    // ctm
//    static void ClickToMove(int64_t, Vector3&);
//};