#pragma once
#include "stdafx.h"
#include "Constants.h"
#include "Offsets.h"

// Created with Reclass 1.3 by Maikel233




class CameraMgr
{
public:
    char pad_0000[13104]; //0x0000
    class CameraMgrPtr *cameraptr; //0x3330
    char pad_3338[328]; //0x3338
}; //Size: 0x3480
static_assert(sizeof(CameraMgr) == 0x3480);

class CameraMgrPtr
{
public:
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
                         //0x148 = Script_FlipCameraYaw 
}; //Size: 0x08A8
static_assert(sizeof(CameraMgrPtr) == 0x8A8);

class WCorpse
{  
public: //Dont use corpse has to been in los else it crashes!
    char pad_0000[432]; //0x0000
    float X; //0x01B0
    float Y; //0x01B4
    float Z; //0x01B8
    char pad_01BC[224]; //0x01BC
}; //Size: 0x029C
static_assert(sizeof(WCorpse) == 0x29C);

// Created with Steam 1.3 by Gabe

// Created with Steam 1.3 by Gabe
// Created with Steam 1.3 by Gabe

// Created with Steam 1.3 by Gabe

// Created with Steam 1.3 by Gabe

// Created with Steam 1.3 by Gabe

class WObject
{
public:
	//All text with ** is not confirmed havent tested these just checked old offsets.
	char pad_0000[16]; //0x0000
	class UnitField* sUnitField; //0x0010
	char pad_0018[8]; //0x0018
	TypeId Type; //0x0020
	char pad_0021[55]; //0x0021
	WGuid Guid; //0x0058
	WGuid Guid2; //0x0060
	char pad_0068[5528]; //0x0068
	Vector3 GetUnitPositionModify; //0x1600
	char pad_160C[52]; //0x160C
	Vector3 GetUnitPosition2Modify; //0x1640
	//** 163C
	char pad_164C[44]; //0x164C
	int64_t StopFall; //0x1678
	// ** 167C **FallTime
	uint64_t SomethinginAir; //0x1680 **Acording to old offsets this might be fall time or jump position.

	//** 0x1684 Current speed...
	float WalkSpeed; //0x1688
	float RunForwardSpeed; //0x168C
	float RunBackwardsSpeed; //0x1690
	float SwimmingSpeed; //0x1694
	float SwimBackwardsSpeed; //0x1698
	float SwimForwardSpeed; //0x169C (Flyspeed?)
	float SwimBackwardsSpeed2; //0x16A0 (Flyspeed backwards)
	float Player_rotationspeed; //0x16A4
	                            // ** 16B0 **Acording to old offsets this might be jump momentum? 
	char pad_16A8[8]; //0x16A8
	float JumpHeight; //0x16B0
	char pad_16B4[44]; //0x16B4
	uint64_t Collision_StateHack; //0x16E0
	char pad_16E8[312]; //0x16E8
	//**  Player_width // 0x1860?  (Set to (0)
	float Player_scale; //0x1820
	//**  climb offset // 0x1824? (Set to 200)
	char pad_1824[2164]; //0x1824

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual const char* GetObjectName() = 0;     // object name
	virtual int64_t GetUnitLevel(int64_t) = 0;   // CGObject level
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual void Function41();
	virtual void Function42();
	virtual void Function43();
	virtual void Function44();
	virtual void Function45();
	virtual void Function46();
	virtual void Function47();
	virtual void Function48();
	virtual void Function49();
	virtual void Function50();
	virtual void Function51();
	virtual void Function52();
	virtual void Function53(); // CGObject::UpdateDisplayInfo(int)
	virtual void Function54();
	virtual void Function55();
	virtual Vector3 GetUnitPosition() = 0;   //CGObject::GetPosition
	virtual Vector3 GetRawUnitPosition() = 0; //CGObject::GetRawPosition
	virtual float GetFacing() = 0;    		//CGObject_C::GetFacing
	virtual float GetRawFacing() = 0;       ///CGObject_C::GetRawFacing
	virtual void BuildMatrix59();	//CGObject::BuildMatrix(void)
	virtual void BuildMatrixFromFacing60();	//CGObject::BuildMatrixFromFacing(void)
	virtual void BuildMatrixFromRotation61();	//CGObject::BuildMatrixFromRotation(void)
	virtual float GetScale() = 0;  //   CGObject::GetScale
	virtual float GetModelScale() = 0;    //  CGObject::GetModelScale(void)
	virtual void Function64();
	virtual void Function65();
	virtual void Function66();
	virtual void Function67();
	virtual void Function68();
	virtual void Function69();
	virtual void Function70();
	virtual void Function71();
	virtual void Function72();
	virtual void Function73();
	virtual void Function74();
	virtual void Function75();
	virtual void Function76();
	virtual void Function77();
	virtual void Function78();
	virtual void Function79();
	virtual void Function80();
	virtual void Function81();
	virtual void Function82();
	virtual void Function83();
	virtual float MaybeAnimate() = 0;
	virtual void Function85();
	virtual void Function86();
	virtual void Function87();
	virtual void Function88(); //CGObject_C::__vmt::OnRightClick
	virtual void Function89(); //CGObject_C::OnLeftClick(void)
	virtual void Function90();
	virtual void Function91();
	virtual void Function92();
	virtual void Function93();
	virtual void Function94();
	virtual void Function95();
	virtual void Function96();
	virtual const char* GetObjectName97() = 0;  // 97
	virtual void Function98();
	virtual void Function99();
	virtual void Function100();

	[[nodiscard]] TypeId GetType() const { return Type; }
	[[nodiscard]] bool GetAnimStatus() const { return *reinterpret_cast<int8_t*>(Ptr() + Offsets::AnimationStatus); }
	[[nodiscard]] WGuid* GetGuid() { return &Guid; }
	[[nodiscard]] WGuid GetOwner() const { return WGuid(Ptr() + Offsets::Owner); }
	[[nodiscard]] uintptr_t Ptr() const { return uintptr_t(this); }

}; //Original Size: 0x2098
static_assert(sizeof(WObject) == 0x20B0);



class UnitField
{
public:
	char pad_0000[152]; //0x0000
	int32_t Unk; //0x0098
	int32_t TargetGuid; //0x009C
	char pad_00A0[56]; //0x00A0
	int32_t Unk2; //0x00D8
	int32_t Health; //0x00DC
	char pad_00E0[24]; //0x00E0
	int32_t Unk3; //0x00F8
	int32_t HealthMax; //0x00FC
	//ENERGY 0xE04
	char pad_0100[88]; //0x0100
	//ENERGY MAX 0x0104
	int64_t RaceId; //0x0158
	char pad_0160[104]; //0x0160
	
}; //Size: 0x01C8
//static_assert(sizeof(UnitField) == 0x1C8);

//class WObject
//{
//public:
//	char pad_0008[8]; //0x0008
//	class UnitField* sUnitField; //0x0010
//	char pad_0018[8]; //0x0018
//	TypeId Type; //0x0020
//	char pad_0021[55]; //0x0021
//	WGuid Guid; //0x0058
//	char pad_0060[2080]; //0x0060
//
//	virtual void Function0();
//	virtual void Function1();
//	virtual void Function2();
//	virtual void Function3();
//	virtual void Function4();
//	virtual void Function5();
//	virtual void Function6();
//	virtual void Function7();
//	virtual void Function8();
//	virtual void Function9();
//	virtual void Function10();
//	virtual void Function11();
//	virtual void Function12();
//	virtual void Function13();
//	virtual void Function14();
//	virtual const char* GetObjectName() = 0;     // object name
//	virtual int64_t GetUnitLevel(int64_t) = 0;   // CGObject level
//	virtual void Function17();
//	virtual void Function18();
//	virtual void Function19();
//	virtual void Function20();
//	virtual void Function21();
//	virtual void Function22();
//	virtual void Function23();
//	virtual void Function24();
//	virtual void Function25();
//	virtual void Function26();
//	virtual void Function27();
//	virtual void Function28();
//	virtual void Function29();
//	virtual void Function30();
//	virtual void Function31();
//	virtual void Function32();
//	virtual void Function33();
//	virtual void Function34();
//	virtual void Function35();
//	virtual void Function36();
//	virtual void Function37();
//	virtual void Function38();
//	virtual void Function39();
//	virtual void Function40();
//	virtual void Function41();
//	virtual void Function42();
//	virtual void Function43();
//	virtual void Function44();
//	virtual void Function45();
//	virtual void Function46();
//	virtual void Function47();
//	virtual void Function48();
//	virtual void Function49();
//	virtual void Function50();
//	virtual void Function51();
//	virtual void Function52();
//	virtual void Function53(); // CGObject::UpdateDisplayInfo(int)
//	virtual void Function54();				
//	virtual void Function55();				
//	virtual Vector3 GetUnitPosition() = 0;   //CGObject::GetPosition
//	virtual Vector3 GetRawUnitPosition() = 0; //CGObject::GetRawPosition
//	virtual float GetFacing() = 0;    		//CGObject_C::GetFacing
//	virtual float GetRawFacing() = 0;       ///CGObject_C::GetRawFacing
//	virtual void BuildMatrix59();	//CGObject::BuildMatrix(void)
//	virtual void BuildMatrixFromFacing60();	//CGObject::BuildMatrixFromFacing(void)
//	virtual void BuildMatrixFromRotation61();	//CGObject::BuildMatrixFromRotation(void)
//	virtual float GetScale() = 0;  //   CGObject::GetScale
//	virtual float GetModelScale() = 0;    //  CGObject::GetModelScale(void)
//	virtual void Function64();
//	virtual void Function65();
//	virtual void Function66();
//	virtual void Function67();
//	virtual void Function68();
//	virtual void Function69();
//	virtual void Function70();
//	virtual void Function71();
//	virtual void Function72();
//	virtual void Function73();
//	virtual void Function74();
//	virtual void Function75();
//	virtual void Function76();
//	virtual void Function77();
//	virtual void Function78();
//	virtual void Function79();
//	virtual void Function80();
//	virtual void Function81();
//	virtual void Function82();
//	virtual void Function83();
//	virtual float MaybeAnimate() = 0;  
//	virtual void Function85();
//	virtual void Function86();
//	virtual void Function87();
//	virtual void Function88(); //CGObject_C::__vmt::OnRightClick
//	virtual void Function89(); //CGObject_C::OnLeftClick(void)
//	virtual void Function90();
//	virtual void Function91();
//	virtual void Function92();
//	virtual void Function93();
//	virtual void Function94();
//	virtual void Function95();
//	virtual void Function96();
//	virtual const char* GetObjectName97() = 0;  // 97
//	virtual void Function98();
//	virtual void Function99();
//	virtual void Function100();
//
//	    [[nodiscard]] TypeId GetType() const { return Type; }
// //   [[nodiscard]] bool GetAnimStatus() const { return *reinterpret_cast<int8_t*>(Ptr() + Offsets::AnimationStatus); }
//    [[nodiscard]] WGuid* GetGuid() { return &Guid; }
// //   [[nodiscard]] WGuid GetOwner() const { return WGuid(Ptr() + Offsets::Owner); }
//    [[nodiscard]] uintptr_t Ptr() const { return uintptr_t(this); }
//}; //Size: 0x0880
//static_assert(sizeof(WObject) == 0x888);



