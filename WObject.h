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
	uint32_t CooldownStartTim; //0x001C
	uint32_t CooldownSpellCooldownDuration; //0x0020
	uint32_t CooldownSpellCategoryId; //0x0024
	uint32_t CooldownCategoryCooldownStartTime; //0x0028
	uint32_t CooldownCategoryCooldownDuration; //0x002C
	char pad_0030[4]; //0x0030
	uint32_t CooldownGCDStartTime; //0x0034
	uint32_t CooldownGCDCategoryId; //0x0038
	uint32_t CooldownGCDDuration; //0x003C
	uint32_t CooldownEntrySize; //0x0040
	char pad_0044[68]; //0x0044
}; //Size: 0x0080
static_assert(sizeof(CoolDownStruct) == 0x88);
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


//#pragma pack(push, 1)
class WObject
{
public:

	virtual ~WObject() {}

	//Removed Player
	not my code cant include srry (:


 //Size: 0xEDDC
	Vector3 GetObjectNamePosition()
	{
		typedef int64_t(__fastcall* GetPosition)(int64_t, int64_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto getPosPtr = (uintptr_t)vTable[0x36];
		auto getPos = (GetPosition)getPosPtr;

		Vector3 v = Vector3(0, 0, 0);
		getPos((uintptr_t)this, (int64_t)&v);
		return v;
	}

	Vector3 GetUnitPosition() const
	{
		typedef int64_t(__fastcall* GetPosition)(int64_t, int64_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto getPosPtr = (uintptr_t)vTable[0x38];
		auto getPos = (GetPosition)getPosPtr;

		Vector3 v = Vector3(0.0, 0.0, 0.0);
		getPos((uintptr_t)this, (int64_t)&v);
		return v;
	}

	PowerTypeId Power_Type() { return *reinterpret_cast<PowerTypeId*>((uintptr_t)this + Offsets::UnitPowerType); }

	std::string getPowerString()
	{
		switch (this->Power_Type())
		{
		case PowerTypeId::mana:
			return "Mana";
			break;

		case PowerTypeId::rage:
			return "Rage";
			break;

		case PowerTypeId::energy:
			return "Energy";
			break;

		case PowerTypeId::runicpower:
			return "Runic Power";
			break;
		}

		return "Unknown Power Type";
	}

	//Unit stuff for Wrath
	uint32_t Health() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + Offsets::Health); }
	uint32_t MaxHealth() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + Offsets::MaxHealth); }

	uint32_t Mana() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + Offsets::Mana); }
	uint32_t MaxMana() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + Offsets::MaxMana); }

	uint32_t Energy() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + Offsets::Energy); }
	uint32_t MaxEnergy() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + Offsets::MaxEnergy); }

	uint8_t GetRaceID() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::Race); }
	uint8_t GetClassID() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::Class); }
	uint8_t GetSex() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::Sex); }

	uint32_t DynamicFlags() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + Offsets::DynamicFlag); }
	uint32_t UnitFlags() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + Offsets::UnitFlag3); }
	

	Vector3 Anchor_position() const { return *reinterpret_cast<Vector3*>((uintptr_t)this + Offsets::anchor_position); }
	float Anchor_facing() const { return *reinterpret_cast<float*>((uintptr_t)this + Offsets::anchor_facing); }
	float Anchor_pitch() const { return *reinterpret_cast<float*>((uintptr_t)this + Offsets::anchor_pitch); }
	Vector3 direction() const { return *reinterpret_cast<Vector3*>((uintptr_t)this + Offsets::direction); }
	Vector2 direction_2d() const { return *reinterpret_cast<Vector2*>((uintptr_t)this + Offsets::direction_2d); }


	CGGuid* GetOwner() { return reinterpret_cast<CGGuid*>((uintptr_t)this + Offsets::Owner); }
	CGGuid* GetGuid() { return reinterpret_cast<CGGuid*>((uintptr_t)this + Offsets::Guid); }
	CGGuid* TargetGuid() { return reinterpret_cast<CGGuid*>((uintptr_t)this + Offsets::Target); }
	TypeId GetType() { return *reinterpret_cast<TypeId*>((uintptr_t)this + Offsets::Type); }
	bool GetAnimStatus() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::AnimationStatus); }
	bool GetGatherStatus() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::GatherStatus); }
	bool isValid() { return (uintptr_t(this) != 0 && (uintptr_t(this) & 1) == 0) && (!this->GetGuid()->isEmpty()); } 	// Returns if this object is valid or not.
	uint8_t GetAnimStatusInt() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::AnimationStatus); }
	uint32_t GetSpellID() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + + 0x1A18); /*0x1A40*/ }
	uint32_t GetChannelID() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x1A70);  /*1C08*/ } 	//Script_ChannelInfo 
	uint32_t GetAuraCount() const { return *reinterpret_cast<int32_t*>((uintptr_t)this + Offsets::AuraCount); }
	uintptr_t Ptr() const { return uintptr_t(this); }

	WoWObjTypeId GetWoWObjType() { return *reinterpret_cast<WoWObjTypeId*>((uintptr_t)this + Offsets::WoWObjTypeID); }


	//Test values
	float GetNoFallVal() const { return *reinterpret_cast<float*>((uintptr_t)this + 0x01C4);  } 	
	float GetFallingAnim() const { return *reinterpret_cast<float*>((uintptr_t)this + 0x238); }


	//WUnit.h!TypeID == (int)TypeId::CGUnit
	bool owns(WObject* object, WObject* LocalPlayer) { return *object->GetOwner() == *LocalPlayer->GetGuid(); }
	bool IsItem() { return this->GetType() == TypeId::CGItem; }
	bool IsUnit() { return this->GetType() == TypeId::CGUnit; }
	bool IsPlayer() { return this->GetType() == TypeId::CGPlayer; }
	bool IsLocalPlayer() { return this->GetType() == TypeId::CGActivePlayer; }
	bool IsGameObject() { return this->GetType() == TypeId::CGGameObject; }
	bool IsCorpse() { return this->GetType() == TypeId::CGCorpse; }
	bool IsPlayerMoving() { return this->CurrentSpeed() != 0; }
	bool IsJumpingUp() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::MovementShared_IsJumpingUp); } //  result = (float)(v1 / -19.291103) > (float)((float)*((signed int *)this + 35) * 0.001);



	int Test() const { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x23C) = 255; }
	float CurrentSpeed() const { return *reinterpret_cast<float*>((uintptr_t)this + Offsets::CurrentSpeed); }


	bool IsGhost() { return Health() == 1; }
	bool IsDead() { return (Health() <= 0 || (DynamicFlags() & UnitDynFlags::UNIT_DYNFLAG_DEAD) == UnitDynFlags::UNIT_DYNFLAG_DEAD); }
	bool IsLootable() { return (DynamicFlags() & UnitDynFlags::UNIT_DYNFLAG_LOOTABLE) == UnitDynFlags::UNIT_DYNFLAG_LOOTABLE; }
	bool IsSkinnable() const { return (UnitFlags() & UnitFlags::UNIT_FLAG_SKINNABLE) == UnitFlags::UNIT_FLAG_SKINNABLE; }
	bool IsInCombat() const { return (UnitFlags() & UnitFlags::UNIT_FLAG_IN_COMBAT) == UnitFlags::UNIT_FLAG_IN_COMBAT; }
	bool IsTapped() const { return (DynamicFlags() & UnitDynFlags::UNIT_DYNFLAG_TAPPED) == UnitDynFlags::UNIT_DYNFLAG_TAPPED; }
	bool IsTappedByMe() const { return (DynamicFlags() & UnitDynFlags::UNIT_DYNFLAG_TAPPEDBYME) == UnitDynFlags::UNIT_DYNFLAG_TAPPEDBYME; }

	bool IsMounted() const { return (UnitFlags() & 0x08000000) > 0; }

	bool IsEating() { return this->pHasAura("Food"); }
	bool IsDrinking() { return this->pHasAura("Drink"); }

	float HealthPercent() { return (float)(Health() / (float)MaxHealth()) * 100.0; }
	float ManaPercent() { 	
		if (this->getPowerString() == "Mana") { return (float)(Mana() / (float)MaxMana()) * 100.0; }
		else { return (float)(Energy() / (float)MaxEnergy()) * 100.0; }
	}


	bool StopFall() const { return *reinterpret_cast<int64_t*>((uintptr_t)this + Offsets::NoFall); } //Tricky to achief stopfall nowadays most of the time DC
	float NoColl() const { return *reinterpret_cast<float*>((uintptr_t)this + Offsets::NoColl); }    // Set to 255 fly through mountains/Buildings     Default Value: 0.3984375298

	//Both vallues need to be adjusted.
	float Wallclimb1() const { return *reinterpret_cast<float*>((uintptr_t)this + Offsets::Wallllimb1); } //Set to 255 Wallclimb Default Value: 0.00f
	float Wallclimb2() const { return *reinterpret_cast<float*>((uintptr_t)this + Offsets::Wallllimb2); } //Set to 255 Wallclimb Default Value: 0.00f


	
	FactionID GetFactionID() {
		int RaceID = this->GetRaceID();
		if (RaceID == WoWRace::Undead || RaceID == WoWRace::Troll || RaceID == WoWRace::TrollFemale || RaceID == WoWRace::Tauren || RaceID == WoWRace::Orc) {
			return FactionID::Horde;
		}
		else if (RaceID == WoWRace::Human || RaceID == WoWRace::Dwarf || RaceID == WoWRace::Gnome || RaceID == WoWRace::NightElf || RaceID == WoWRace::Draenei || RaceID == WoWRace::Draeneis) {
			return FactionID::Alliance;
		}	
		return FactionID::INVALID;
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


	//Item stuff
	void UseItem(CGGuid* targetGuid) const {
		//WItem.h
		CGGuid* unk = reinterpret_cast<CGGuid*>(Offsets::CGItem_UseItemParm);
		reinterpret_cast<bool(__fastcall*)(uint64_t, CGGuid*, bool, CGGuid*)>(Offsets::CGItem_UseItem)((uintptr_t)this, targetGuid, 0, unk);
	}

	//Removed Sell/buy item not my code so cant include... (:

	//Vtable funcs
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
//static_assert(sizeof(WObject) == 0x4A0);
#pragma pack(pop)

//remove itemcache(*GetItemQuality, GetName
//Removed Witem getitem stuff
				 
