#pragma once
#include "Utils.h"

#include "stdafx.h"
#include "WObject.h"
#include "Lua/GameMethods.h"
#include "Lua/LuaBase.h"
#include "Lua/LuaScript.h"

#define M_DEG2RAD 0.017453292519943295769236907684886f
	namespace wow {
		class camera {
		public:
			static Vector2 WorldToScreenv2(Vector3 unitPosition);
		};
	}