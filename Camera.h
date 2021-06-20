#pragma once
#include "Utils.h"

#include "stdafx.h"
#include "WObject.h"
#include "Lua/GameMethods.h"
#include "Lua/LuaBase.h"
#include "Lua/LuaScript.h"

#define M_DEG2RAD 0.017453292519943295769236907684886f

class CameraMgr
{
public:
    char pad_0000[14552]; //0x0000          // classic char pad_0000[13104]; //0x0000
    class CameraMgrPtr* cameraptr; //0x38D8
    char pad_38E0[1952]; //0x38E0           // classic char pad_3338[328]; //0x3338
}; //Size: 0x4080
static_assert(sizeof(CameraMgr) == 0x4080); // classic 0x3480);


class CameraMgrPtr
{
public:
    char pad_0000[16]; //0x0000
    C3Vector Camera_pos; //0x0010
    Matrix3x3 mat; //0x001C

    float FOV; //0x0040
    char pad_0044[500]; //0x0044
    float unk_Something1; //0x0238
    float Camera_zoomout; //0x023C
    float Camera_zoomin; //0x0240
    bool unk_wecallit_iszooming; //0x0244
    char pad_0245[3]; //0x0245
    float camera_max30; //0x0248
    char pad_024C[1628]; //0x024C                     
    //0x0278 Camera goes UP and than down 
}; //Size: 0x08A8
static_assert(sizeof(CameraMgrPtr) == 0x8A8);

	namespace WoW {
		class camera {
		public:
			static CameraMgr* GCamera;
			static void Init();
			static Vector2 WorldToScreenv2(C3Vector unitPosition);
		};
	}