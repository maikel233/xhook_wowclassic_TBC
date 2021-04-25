#pragma once
#include "stdafx.h"
#include "Constants.h"
#include "Offsets.h"

// Created with Reclass 1.3 by Maikel233

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

class UnitField
{
public:
	char pad_0000[92]; //0x0000
	uint8_t Summoner; //0x005C
	char pad_005D[63]; //0x005D
	uint32_t TargetGuid; //0x009C
	uint32_t SomethingGuid; //0x00A0
	uint32_t SomethingGuid2; //0x00A4 Player returns 0 Unit returns random GUID.
	char pad_00A8[28]; //0x00A8
	uint32_t SpellID; //0x00C4
	uint32_t SpellDuration; //0x00C8
	char pad_00CC[5]; //0x00CC
	uint8_t ClassID; //0x00D1
	char pad_00D2[10]; //0x00D2
	uint32_t Health; //0x00DC
	char pad_00E0[4]; //0x00E0
	uint32_t Energy; //0x00E4
	char pad_00E8[20]; //0x00E8
	uint32_t MaxHealth; //0x00FC
	char pad_0100[4]; //0x0100
	uint32_t MaxEnergy; //0x0104
	char pad_0108[44]; //0x0108
	uint32_t N000004A4; //0x0134
	char pad_0138[32]; //0x0138
	uint64_t RaceID; //0x0158
	char pad_0160[156]; //0x0160
	uint32_t Strength; //0x01FC                   
	uint32_t Agility; //0x0200
	uint32_t Stamina; //0x0204
	uint32_t Intelect; //0x0208
	uint32_t Spirit; //0x020C
	char pad_0210[40]; //0x0210
	uint32_t Armor; //0x0238
	uint32_t resistance_fire; //0x023C
	uint32_t resistance_arcane; //0x0240
	uint32_t resistance_nature; //0x0244
	uint32_t resistance_frost; //0x0248
	uint32_t resistance_shadow; //0x024C
	char pad_0250[328]; //0x0250
	uint32_t IsPlayerDead; //0x0398 Changes the skybox to blue
	char pad_039C[1476]; //0x039C
	float Drunk; //0x0960  Set to 0/255
	char pad_0964[209004]; //0x0964
	 //0x01BE // Stealth walking Animation
}; //Size: 0x339D0
static_assert(sizeof(UnitField) == 0x339D0);

class WObject
{
public:

	char pad_0008[8]; //0x0008
	class UnitField* sUnitField; //0x0010
	char pad_0018[8]; //0x0018
	TypeId Type; //0x0020
	char pad_0021[55]; //0x0021
	WGuid Guid; //0x0058
	char pad_0060[5536]; //0x0060  // 0x0066
	Vector3 GetUnitPositionModify; //0x1600
	char pad_160C[52]; //0x160C
	Vector3 anchor_position; //0x1640 *UnitPos2
	float anchor_facing; //0x164C
	float anchor_pitch; //0x1650
	uint32_t MoveTime; //0x1658
	Vector3 direction; //0x165C <== Wo
	Vector2 direction_2d; //0x1668 
	float Unk; //0x1654
	float cos_anchor_pitch;  // 0x70
	float sin_anchor_pitch;  // 0x74
	uint32_t StopFall; //0x1678
	float fall_start_elev_1; // 0x7C
	float fall_start_elev_2; // 0x80
	float CurrentSpeed; //0x1684
	float WalkSpeed; //0x1688
	float RunForwardSpeed; //0x168C
	float RunBackwardsSpeed; //0x1690
	float SwimmingSpeed; //0x1694
	float SwimBackwardsSpeed; //0x1698
	float FlyForwardSpeed; //0x169C 
	float FlyBackwardsSpeed2; //0x16A0 
	float Player_rotationspeed; //0x16A4
	char pad_16A8[8]; //0x16A8
	float JumpHeight; //0x16B0
	char pad_16B4[44]; //0x16B4
	uint32_t Collision_StateHack; //0x16E0
	char pad_16E4[316]; //0x16E4
	float Player_scale; //0x1820
	char pad_1824[2156]; //0x1824


	virtual ~WObject() = default;
	virtual void Function1();
	virtual float GetObjectFacing(float = 1.0f) = 0;  // returns radians of direction facing
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();						 // returns 0 not combat, stealth, or mounted
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();						 // returns 0 not combat, stealth, or mounted
	virtual void Function13();
	virtual float GetObjectDisplayHeight(float = 1.0f) = 0;  
	virtual const char* GetObjectName2() = 0;		 // object name
	virtual int64_t GetUnitLevel2(int64_t) = 0;		 // CGObject level
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
	virtual void CGObject__UpdateDisplayInfo();     //int					
	virtual void Function54();
	virtual void Function55();
	virtual Vector3 GetUnitPosition() = 0;			//CGObject::GetPosition
	virtual Vector3 GetRawUnitPosition() = 0;		//CGObject::GetRawPosition
	virtual float GetFacing2() = 0;    				//CGObject_C::GetFacing
	virtual float GetRawFacing() = 0;				///CGObject_C::GetRawFacing
	virtual void BuildMatrix59();					//CGObject::BuildMatrix(void)
	virtual void BuildMatrixFromFacing60();			//CGObject::BuildMatrixFromFacing(void)
	virtual void BuildMatrixFromRotation61();		//CGObject::BuildMatrixFromRotation(void)
	virtual float GetScale() = 0;					//CGObject::GetScale
	virtual float GetModelScale() = 0;				//CGObject::GetModelScale(void)
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
	virtual void GetModelFileName74(char const** modelFileName); // Should be GetModelFileName(char  const**)?
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
	virtual int64_t CGObject_C_OnLeftClick(int64_t) = 0;
	virtual void CGObject_C_OnRightClick();						
	virtual void Function90();
	virtual void Function91();
	virtual void Function92();
	virtual void Function93();
	virtual void Function94();
	virtual void Function95();
	virtual void Function96();
	virtual const char* GetObjectName97() = 0;  // 97
	virtual int64_t Function98(int64_t) = 0;
	virtual int64_t Function99(int64_t) = 0;
	virtual int64_t Function100(int64_t) = 0;
	virtual void Function101();
	virtual void Function102();
	virtual void Function103();
	virtual void Function104();
	virtual void Function105();
	virtual void Function106();
	virtual void Function107();
	virtual void Function108();
	virtual void Function109();
	virtual void Function110();
	virtual void Function111();
	virtual int64_t IsDeadOrGhost(int64_t) = 0;

	virtual void Function115(); // Makes the character sit
	virtual void Function123(); // Returns 10000
	virtual void Function129(); // Returns 220

	//WGuid GetOwner() const {
	//	return WGuid(Ptr() + Offsets::Owner);
	//}
	//	
	//WGuid* GetGuid() 
	//{
	//		return &Guid; 
	//}

	WGuid* GetOwner() const
	{
		if (const auto base_ptr = Ptr())
		{		
			return reinterpret_cast<WGuid*>(base_ptr + Offsets::Owner);		
		}

		return nullptr;
	}

	WGuid* GetGuid() const
	{
		if (const auto base_ptr = Ptr())
		{
			return reinterpret_cast<WGuid*>(base_ptr + Offsets::Guid);
		}

		return nullptr;
	}

	uintptr_t Ptr() const
	{
		 return uintptr_t(this); 
	}

	TypeId GetType() const
	{
		if (const auto base_ptr = Ptr())
		{
			return *reinterpret_cast<TypeId*>(base_ptr + Offsets::Type);
		}

		return TypeId::Invalid;
	}

	bool GetAnimStatus() const
	{
		return *reinterpret_cast<int8_t*>(Ptr() + Offsets::AnimationStatus);
	}

	uint8_t GetAnimStatusInt() const
	{
		return *reinterpret_cast<int8_t*>(Ptr() + Offsets::AnimationStatus);
	}

	/*WGuid* GetGuid() const
	{
		if (const auto base_ptr = Ptr())
		{
			WGuid* guid;
			auto _guid = *reinterpret_cast<WGuid*>(base_ptr + Offsets::Guid);
			guid = &_guid;
			return guid;
		}

		return nullptr;
	}

	WGuid* GetOwner() const
	{
		if (const auto base_ptr = Ptr())
		{
			WGuid* guid;
			auto _guid = *reinterpret_cast<WGuid*>(base_ptr + Offsets::Owner);
			guid = &_guid;
			return guid;
		}

		return nullptr;
	}*/

	void Interact()
	{
		typedef DWORD* (__fastcall* InteractWith)(uintptr_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto interactPtr = (uintptr_t)vTable[0x59];
		auto interact = (InteractWith)interactPtr;

		interact((uintptr_t)this);
	}

	const uint64_t GetUnitLevel(uint64_t)
	{

		typedef const uint64_t(__fastcall* GetUnitLvl)(uintptr_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto GetUnitLevelPtr = (uintptr_t)vTable[0x10];
		auto GetUnitLevel = (GetUnitLvl)GetUnitLevelPtr;

		return GetUnitLevel((uintptr_t)this);
	}

	const float GetFacing()
	{

		typedef const float (__fastcall* GetFacing)(uintptr_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto getFacingPtr = (uintptr_t)vTable[0x3A];
		auto getFacing = (GetFacing)getFacingPtr;

		return getFacing((uintptr_t)this);
	}


	const char* GetObjectName()
	{

		typedef const char* (__fastcall* GetName)(uintptr_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto getNamePtr = (uintptr_t)vTable[0x0F];
		auto getName = (GetName)getNamePtr;

		return getName((uintptr_t)this);
	}

	// Returns if this object is valid or not.
	bool isValid()
	{
		return (this->Ptr() != 0 && (this->Ptr() & 1) == 0) && (this->GetGuid() != 0);
	}

	bool isItem()
	{
		return this->GetType() == CGItem;
	}

	bool isUnit()
	{
		return this->GetType() == CGUnit;
	}

	bool isPlayer()
	{
		return this->GetType() == CGPlayer;
	}

	bool isGameObject()
	{
		return this->GetType() == CGGameObject;
	}


};
static_assert(sizeof(WObject) == 0x2098);
