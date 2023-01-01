#pragma once
#include "Utils.h"
#include "Settings/Settings.h"

#define M_DEG2RAD 0.017453292519943295769236907684886f
#pragma pack(push, 1)
class CameraMgr
{
public:
    char pad_0000[14568]; //0x0000
    class CameraMgrPtr* cameraptr; //0x38E8
    char pad_38F0[185552]; //0x38F0

}; //Size: 0x4080
static_assert(sizeof(CameraMgr) == 0x30DC0);
#pragma pack(pop)

#pragma pack(push, 1)
class CameraMgrPtr
{
public:
    //From script_camera
    char pad_0000[16]; //0x0000
    Vector3 Camera_pos; //0x0010
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
  // 0x0278 Camera goes UP and than down 
}; //Size: 0x08A8
static_assert(sizeof(CameraMgrPtr) == 0x8A8);
#pragma pack(pop)

namespace WoW {
    class camera {
    public:
        static CameraMgr* GCamera;
        static void Init();
        static Vector2 WorldToScreenv2(Vector3 unitPosition);
        static bool TraceLine(WObject* Object, Vector3 Target, IntersectFlags intersectFlags);
    };
}
