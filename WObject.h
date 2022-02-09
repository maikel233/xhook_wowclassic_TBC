#pragma once
#include "stdafx.h"
#include "Constants.h"
#include "WoWTypes.h"

enum class TeamID : int {
	Horde,
	Alliance,
	INVALID,
};

inline std::string FetchAuraName(int AuraID) {
	switch (AuraID)
	{
	case 26990: case 1126: case 9885: case 9884: case 8907: case 5232: case 5234: case 6756:
		return "Mark of the Wild";
		break;
	case 467: case 26992: case 782: case 1075: case 9756: case 9910: case 8914:
		return "Thorns";
		break;
	case 8936: case 8938: case 8939: case 8940: case 8941: case 9750: case 9856: case 9857: case 9858: case 26980:
		return "Regrowth";
		break;
	case 774: case 1058: case 1430: case 2090: case 2091: case 3627: case 8910: case 9839: case 9840: case 9841: case 25299: case 26981:
		return "Rejuvenation";
		break;
	case 33763:
		return "Lifebloom";
		break;
	case 8921: case 8924:  case 8925: case 8926: case 8927: case 8928: case 8929: case 9833: case 9834: case 9835: case 26987: case 26988:
		return "Moonfire";
		break;
		//Eating/Drinking state lvl 25~
	case 433: case 434: case 435:
		return "Food";
		break;
	case 430: case 431: case 432:
		return "Drink";
		break;
	case 20549: 
		return "Warstomp";
		break;
	default:
		return "";
		break;
	}
}

#pragma pack(push, 1)
class CoolDownStruct
{
public:
	char pad_0000[8]; //0x0000
	uintptr_t Next; //0x0008
	uint32_t SpellID; //0x0010
	uint32_t ItemID; //0x0014
	char pad_0018[4]; //0x0018
	uint32_t RecoveryStart; //0x001C
	uint32_t Recovery1; //0x0020
	char pad_0024[4]; //0x0024
	uint32_t CatRecoveryStart; //0x0028
	uint32_t Recovery2; //0x002C
	char pad_0030[4]; //0x0030
	uint32_t GcdRecoveryStart; //0x0034
	char pad_0038[72]; //0x0038
}; //Size: 0x0080
static_assert(sizeof(CoolDownStruct) == 0x80);
#pragma pack(pop)

inline static std::vector<CoolDownStruct>(Cooldowns);

// Created with Reclass 1.3 by Maikel233
#pragma pack(push, 1)
class Aura
{
public:
	char pad_0000[32]; //0x0000
	CGGuid OwnerGuid; //0x0020
	char pad_0028[16]; //0x0028
	uint32_t TimeLeft; //0x0040
	char pad_0044[68]; //0x0044
	int SpellID; //0x0088
	char pad_008C[4]; //0x008C
	uint16_t Flags; //0x0090
	BYTE Level; //0x0092
	//char pad_0094[240]; //0x0094
}; //Size: 0x0184
#pragma pack(pop)

#pragma pack(push, 1)
class UnitField
{
public:
	char pad_0000[20]; //0x0000
	uint32_t DynamicFlags; //0x0014
	char pad_0018[36]; //0x0018
	uint32_t GameObjectDisPlayID; //0x003C
	uint32_t GameObjectFlag; //0x0040
	char pad_0044[8]; //0x0044
	CGGuid CritterOrCharmerGuid; //0x004C
	CGGuid SummonedBy; //0x005C
	CGGuid CreatorGuid; //0x006C
	CGGuid MasterGuid; //0x007C
	char pad_0084[16]; //0x0084
	CGGuid TargetGuid; //0x009C
	char pad_00A4[24]; //0x00A4
	uint32_t UNK;//SpellID; //0x00C4
	uint32_t UNKK; //0x00C8
	char pad_00CC[4]; //0x00CC  5
	uint8_t Race; //0x00D0
	uint8_t ClassID; //0x00D1
	uint8_t PlayerClassID; //0x00D2
	uint8_t Sex; //0x00D3
	uint32_t DisplayPower; //0x00D4
	uint32_t OverrideDisplayPowerID; //0x00D8
	uint32_t Health; //0x00DC
	char pad_00E0[4]; //0x00E0
	uint32_t Energy; //0x00E4
	uint32_t Power2; //0x00E8
	uint32_t Power3; //0x00EC
	uint32_t Power4; //0x00F0
	char pad_00F4[12]; //0x00F4
	uint32_t MaxHealth; //0x0100
	char pad_0104[4]; //0x0104
	uint32_t MaxEnergy; //0x0108
	uint32_t MaxPower2; //0x010C
	uint32_t MaxPower3; //0x0110
	uint32_t MaxPower4; //0x0114
	char pad_0118[40]; //0x0118
	uint32_t Level; //0x0140
	char pad_0144[32]; //0x0144
	uint32_t RaceID; //0x0164
	uint32_t FactionTemplate;
	char pad_0168[20]; //0x0168
	uint32_t UnitFlag1; //0x0180
	uint32_t UnitFlag2; //0x0184
	uint32_t UnitFlag3; //0x0188
	char pad_018C[24]; //0x018C
	uint32_t DisplayID; //0x01A4
	char pad_01A8[12]; //0x01A8
	uint32_t MountID; //0x01B4
	char pad_01B8[64]; //0x01B8
	uint32_t NPCFLAG; //0x01F8
	char pad_01FC[652]; //0x01FC
}; //Size: 0x339D0
//static_assert(sizeof(UnitField) == 0x339D0);
#pragma pack(pop)


#pragma pack(push, 1)
class WObject
{
public:
	char pad_0008[8]; //0x0008
	class UnitField* sUnitField; //0x0010
	char pad_0018[8]; //0x0018
	TypeId Type; //0x0020
	char pad_0021[55]; //0x0021
	CGGuid Guid; //0x0058
	char pad_0060[5528]; //0x0060
	Vector3 GetUnitPositionModify; //0x1600  
	char pad_160C[56]; //0x160C
	Vector3 anchor_position; //
	float anchor_facing; //0x1650
	float anchor_pitch; //0x1654
	uint32_t MoveTime;
	Vector3 direction;
	Vector2 direction_2d;
	float unk01;
	float unk02;
	float unk03;
	uint32_t StopFall;
	float fall_start_elev_1; //DC
	float CurrentSpeed; //0x1684
	float WalkSpeed;    //0x1688
	float RunForwardSpeed; //0x168C
	float RunBackwardsSpeed; //0x1690
	float SwimmingSpeed; //0x1694
	float SwimBackwardsSpeed; //0x1698
	float FlyForwardSpeed; //0x169C
	float FlyBackwardsSpeed2; //0x16A0
	float Player_rotationspeed; //0x16A4 //Below this offset are invalid ones they need a update...
	char pad_165C[8]; 
	float StartofJumpHeight; //  Sets Starting jumpheight will dc you after a few ms... // 16B0
	char pad_16B4[60]; //0x16B4
	uint32_t MovementFlags; //0x16F0
	char pad_16F4[6548]; //0x16F4

	virtual ~WObject() {}

	CGGuid* GetOwner() { return reinterpret_cast<CGGuid*>((uintptr_t)this + Offsets::Owner); }
	CGGuid* GetGuid() { return reinterpret_cast<CGGuid*>((uintptr_t)this + Offsets::Guid); }
	TypeId GetType() { return *reinterpret_cast<TypeId*>((uintptr_t)this + Offsets::Type); }
	bool GetAnimStatus() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::AnimationStatus); }
	bool GetGatherStatus() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::GatherStatus); }
	bool isValid() { return (uintptr_t(this) != 0 && (uintptr_t(this) & 1) == 0) && (!this->GetGuid()->isEmpty()); } 	// Returns if this object is valid or not.
	uint8_t GetAnimStatusInt() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::AnimationStatus); }
	uint32_t GetSpellID() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + + 0x1A18); /*0x1A40*/ }
	uint32_t GetChannelID() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x1A70);  /*1C08*/ } 	//Script_ChannelInfo 
	uint32_t GetAuraCount() const { return *reinterpret_cast<int32_t*>((uintptr_t)this + Offsets::AuraCount); }
	uintptr_t Ptr() const { return uintptr_t(this); }
	

	//WUnit.h!TypeID == (int)TypeId::CGUnit
	bool owns(WObject* object, WObject* LocalPlayer) { return *object->GetOwner() == *LocalPlayer->GetGuid(); }
	bool IsItem() { return this->GetType() == TypeId::CGItem; }
	bool IsUnit() { return this->GetType() == TypeId::CGUnit; }
	bool IsPlayer() { return this->GetType() == TypeId::CGPlayer; }
	bool IsLocalPlayer() { return this->GetType() == TypeId::CGActivePlayer; }
	bool IsGameObject() { return this->GetType() == TypeId::CGGameObject; }
	bool IsCorpse() { return this->GetType() == TypeId::CGCorpse; }
	bool IsPlayerMoving() { return this->CurrentSpeed != 0; }

	bool IsGhost() { return sUnitField->Health == 1; }
	bool IsDead() { return (sUnitField->Health <= 0 || (sUnitField->DynamicFlags & UnitDynFlags::UNIT_DYNFLAG_DEAD) == UnitDynFlags::UNIT_DYNFLAG_DEAD); }
	bool IsLootable() { return (sUnitField->DynamicFlags & UnitDynFlags::UNIT_DYNFLAG_LOOTABLE) == UnitDynFlags::UNIT_DYNFLAG_LOOTABLE; }
	bool IsSkinnable() const { return (sUnitField->UnitFlag1 & UnitFlags::UNIT_FLAG_SKINNABLE) == UnitFlags::UNIT_FLAG_SKINNABLE; }
	bool IsInCombat() const { return (sUnitField->UnitFlag1 & UnitFlags::UNIT_FLAG_IN_COMBAT) == UnitFlags::UNIT_FLAG_IN_COMBAT; }
	bool IsTapped() const { return (sUnitField->DynamicFlags & UnitDynFlags::UNIT_DYNFLAG_TAPPED) == UnitDynFlags::UNIT_DYNFLAG_TAPPED; }
	bool IsTappedByMe() const { return (sUnitField->DynamicFlags & UnitDynFlags::UNIT_DYNFLAG_TAPPEDBYME) == UnitDynFlags::UNIT_DYNFLAG_TAPPEDBYME; }

	bool IsEating() { return this->pHasAura("Food"); }
	bool IsDrinking() { return this->pHasAura("Drink"); }

	float HealthPercent() { return (float)(sUnitField->Health / (float)sUnitField->MaxHealth) * 100.0; }
	float ManaPercent() const { return (float)(sUnitField->Energy / (float)sUnitField->MaxEnergy) * 100.0; }

	TeamID GetFactionID() {
		int RaceID = this->sUnitField->RaceID;
		if (RaceID == WoWRace::Undead || RaceID == WoWRace::Troll || RaceID == WoWRace::TrollFemale || RaceID == WoWRace::Tauren || RaceID == WoWRace::Orc) {
			return TeamID::Horde;
		}
		else if (RaceID == WoWRace::Human || RaceID == WoWRace::Dwarf || RaceID == WoWRace::Gnome || RaceID == WoWRace::NightElf || RaceID == WoWRace::Draenei || RaceID == WoWRace::Draeneis) {
			return TeamID::Alliance;
		}	
		return TeamID::INVALID;
	}

	void UseItem(CGGuid* targetGuid) const { 
		//WItem.h
		CGGuid* unk = reinterpret_cast<CGGuid*>(Offsets::CGItem_UseItemParm);
		reinterpret_cast<bool(__fastcall*)(uint64_t, CGGuid*, bool, CGGuid*)>(Offsets::CGItem_UseItem)((uintptr_t)this, targetGuid, 0, unk);
	}

	//LocalPlayer only
	bool pHasCoolDown(const std::string& aura) {	
		for (auto& CoolDown : Cooldowns) {
			if (CoolDown.SpellID != 0) {
				return FetchAuraName(CoolDown.SpellID) == aura;
			}
		}
		return false;
	}

	bool pHasAura(const std::string& aura) {
		std::vector<uint32_t> mBuffs = HasAura();
		return std::any_of(
			mBuffs.begin(),
			mBuffs.end(),
			[&aura](uint32_t buff) {
				return FetchAuraName(buff) == aura;
			});
	}

	std::vector<uint32_t> HasAura() {
		std::vector<uint32_t> mBuffs;
		uint32_t auraCount = GetAuraCount();
		if (auraCount == -1) 
		{  /* // Does this ever happen??? */ }
		for (int32 currentAuraCount = 0; currentAuraCount < auraCount; ++currentAuraCount) {
			Aura Table;
			auto offset = (Offsets::AuraTable + currentAuraCount * Offsets::AuraSize);
			ReadOffsetInto(AddOffset(this, offset), &Table);
			if (Table.SpellID && (Table.Flags & 20/*AuraFlags::Harmful*/)) {
				mBuffs.push_back(Table.SpellID);
			}
		}
		return mBuffs;
	}

	//Vtable funcs
	
	Vector3 GetObjectNamePosition() {
		typedef int64_t(__fastcall* GetPosition)(int64_t, int64_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto getPosPtr = (uintptr_t)vTable[0x36];
		auto getPos = (GetPosition)getPosPtr;

		Vector3 v = Vector3(0, 0, 0);
		getPos((uintptr_t)this, (int64_t)&v);
		return v;
	}

	Vector3 GetUnitPosition() const {
		typedef int64_t(__fastcall* GetPosition)(int64_t, int64_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto getPosPtr = (uintptr_t)vTable[0x38];
		auto getPos = (GetPosition)getPosPtr;

		Vector3 v = Vector3(0.0, 0.0, 0.0);
		getPos((uintptr_t)this, (int64_t)&v);
		return v;
	}
	
	void Interact() {
		typedef DWORD* (__fastcall* InteractWith)(uintptr_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto interactPtr = (uintptr_t)vTable[0x59];
		auto interact = (InteractWith)interactPtr;

		interact((uintptr_t)this);
	}

	const uint64_t GetUnitLevel(uint64_t) {
		typedef const uint64_t(__fastcall* GetUnitLvl)(uintptr_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto GetUnitLevelPtr = (uintptr_t)vTable[0x10];
		auto GetUnitLevel = (GetUnitLvl)GetUnitLevelPtr;

		return GetUnitLevel((uintptr_t)this);
	}

	const float GetObjectDisplayHeight() {
		typedef const float(__fastcall* GetObjectDisplayHeight)(uintptr_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto getObjectDisplayHeightPtr = (uintptr_t)vTable[0xE];
		auto getObjectDisplayHeight = (GetObjectDisplayHeight)getObjectDisplayHeightPtr;

		return getObjectDisplayHeight((uintptr_t)this);
	}

	const float GetFacing() {
		typedef const float(__fastcall* GetFacing)(uintptr_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto getFacingPtr = (uintptr_t)vTable[0x3A];
		auto getFacing = (GetFacing)getFacingPtr;

		return getFacing((uintptr_t)this);
	}

	const char* GetObjectName() {
		typedef const char* (__fastcall* GetName)(uintptr_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto getNamePtr = (uintptr_t)vTable[0x0F];
		auto getName = (GetName)getNamePtr;
		auto name = getName((uintptr_t)this);
		if (name)
			return name;
		return "None";
	}
}; 
//static_assert(sizeof(WObject) == 0x20A8);
#pragma pack(pop)



