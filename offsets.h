#pragma once
#include "stdafx.h"
#include <hadesmem/read.hpp>

void* AddOffset(void* p, int offset);

static hadesmem::Process& GetThisProcess()
{
	static hadesmem::Process process{ GetCurrentProcessId() };
	return process;
}

template <typename T>
void ReadOffsetInto(uintptr_t addr, T* out)
{
	*out = hadesmem::Read<T>(GetThisProcess(), (void*)addr);
}

template <typename T>
void ReadOffsetInto(void* addr, T* out)
{
	*out = hadesmem::Read<T>(GetThisProcess(), addr);
}

template <typename T>
void ReadOffsetInto(void* base, uintptr_t offset, T* out)
{
	ReadOffsetInto(AddOffset(base, offset), out);
}

template <typename T>
T ReadOffset(uintptr_t base)
{
	T t;
	ReadOffsetInto(base, &t);
	return t;
}

template <typename T>
T ReadOffset(void* base)
{
	T t;
	ReadOffsetInto(base, &t);
	return t;
}

template <typename T>
T ReadOffset(void* base, uintptr_t offset)
{
	T t;
	ReadOffsetInto(base, offset, &t);
	return t;
}

namespace Offsets
{
	////////////////////////
	//     2.5.3 44833   //
	////////////////////////


	//How to find...

	//Aura sizes See .text:00000000012ADB56	Script_GetSpellConfirmationPromptsInfo	mov     eax, [rdi+6A0h]
	//

	
	// base address
	static inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));


	static inline uintptr_t CGGameObject_C_CanUse = 0x5C7DCB,
		CGGameObject_C_CanUseNow = 0x14032F0,
		CGGameObject_C_IsLocked = 0x140BBD0,
		CGItem_GetSpellIdById = 0x0,
		CGItem_UseItem = 0x13E6040,
		CGItem_UseItemParm = 0x10F9587,
		CGPlayer_AcceptResurrect = 0x1308EE0,
		CGPlayer_C_HandleRepopRequest = 0x1319E20,
		CGPlayer_C_SwapItems = 0x133C850,
		CGUnit_C_CanAttack = 0x1374600,
		CGUnit_C_Dismount = 0x1384740,
		CGUnit_C_HandleTrackingFacing = 0x13A8E20,
		CGUnit_C_IsInMelee = 0x13939D0,
		CGUnit_C_OnAttackIconPressed = 0x1399E10,
		CGUnit_C_OnFlightLocal = 0x139D4B0,
		CGUnit_C_OnJumpLocal = 0x139D510,
		CGUnit_C_OnSwimStartLocal = 0x13A1150,
		CGUnit_C_SetTrackingMoveTo = 0x13A90B0,
		CGUnit_C_SetTrackingObjectInteract = 0x13A8EF0,
		CGUnit_C_SetTrackingPosition = 0x13A90B0,
		CGUnit_C_SetTrackingTarget = 0x13A9190,
		CGUnit_IsOutdoors = 0x1393DC0,
		CameraMgr = 0x2EA7158,
		ClntObjMgrEnumVisibleObjectsPtr = 0x1521C10,
		ClntObjMgrGetMapId = 0x15261E0,
		ClntObjMgrIsValid = 0x1526900,
		CorpseMapID = 0x2BF6F30,
		GameBuild = 0x2531124,
		GameReleaseDate = 0x257FE10,
		GameVersion = 0x257FE1C,
		HardwareEventPtr = 0x2C57368,
		InvalidPtrCheckMax = 0x2E5FBD8,
		InvalidPtrCheckMin = 0x2E5FBD0,
		IsLootWindowOpen = 0x2FB01F0,
		IsPlayerInWorld = 0x2F7C134,
		IsPlayerMoving = 0x1536F90,
		NameCacheBase = 0x2AF7418,
		RedMessage = 0x2F7AF60,
		RuneReady = 0x0,
		SpellBook = 0x2FAF768,
		CGlueMgr_QuitGame = 0x1F1640,
		ClientConnection_CharacterLogout = 0x1135F10,
		CoolDown = 0x2F16040,
		EquippedBagGUID = 0x2FCB550,
		FaceTo = 0x13A8E20,
		FrameScript_GetText = 0x588630,
		GetDefaultLanguage = 0x1334E40,
		GetItemCachEntry = 0x4B1C90,
		GuidToString = 0x1123190,
		ItemCachEntryBase = 0x2C2A020,
		Merchant = 0x2FC00F8,
		MerchantBuyItems = 0x13271C0,
		MerchantCount = 0x2EC9DE0,
		MerchantItems = 0x0,
		MerchantSellItems = 0x1319E60,
		Movement_InputControl = 0x2AF73E0,
		Movement_ToggleControlBit = 0x10E8750,
		PartyInfo_GetActiveParty = 0x15F7F80,
		Party_FindMember = 0x15F7CD0,
		PetInfo_FindSpellById = 0x1609B20,
		PetInfo_SendPetAction = 0x160BB60,
		Player_LeaveCombatMode = 0x12DAE20,
		SendChatMessage = 0x0,
		Specialization_IsTalentSelectedById = 0x171C620,
		SpellBook_FindSlotBySpellId = 0x15C6410,
		SpellBook_FindSpellByName = 0x15C6620,
		SpellBook_FindSpellOverrideById = 0x15C7A10,
		SpellBook_GetOverridenSpell = 0x15C6CE0,
		SpellDB_GetRow = 0x2182FC0,
		SpellDB_HasAttribute = 0x2182F60,
		Spell_C_CancelActiveSpell = 0x12C2450,
		Spell_C_CancelChannel = 0x12C2DB0,
		Spell_C_CancelSpell = 0x12C31D0,
		Spell_C_CastSpell = 0x15C4380,
		Spell_C_GetMinMaxRange = 0x12CB170,
		Spell_C_GetSpellCoolDown = 0x12CD820,
		Spell_C_HaveSpellPower = 0x12D1A90,
		Spell_C_IsCurrentSpell = 0x12D6090,
		Spell_C_IsUsableAction = 0x12D66C0,
		Spell_C_RangeCheckSelected = 0x12D8C60,
		Spell_CancelAutoRepeat = 0x12C2B50,
		Spell_ClickSpell = 0x12C6E60,
		Spell_GetSomeSpellInfo = 0x21817C0,
		Spell_GetSpellCharges = 0x15BED30,
		Spell_GetSpellType = 0x3AE1C0,
		Spell_HandleTerrainClick = 0x12D10F0,
		Spell_IsPlayerSpell = 0x15CD090,
		Spell_IsStealable = 0x15C40D0,
		Spell_SomeInfo = 0x12FA9E0,
		Spell_isSpellKnown = 0x15CD120,
		SpriteLeftClick = 0x1564B30,
		SpriteRightClick = 0x1564F60,
		Unit_CanAttack = 0x1374600,
		Unit_GetAuraByIndex = 0x25C0C484,
		Unit_GetFacing = 0x113A2A0,
		Unit_GetPosition = 0x13178D0,
		Unit_GetPower = 0x191B1E0,
		Unit_GetPowerMax = 0x191B340,
		Unit_IsFriendly = 0x13AF210,
		WorldFrame_GetWorld = 0x1F1530,
		WorldFrame_HitTest = 0x1019CE0,
		WorldFrame_HitTestPoint = 0x101A2B0,
		WorldFrame_Intersect = 0xED16F0,
		WorldFrame_OnLayerUpdate = 0x101C360,
		World_GetFrameRateResult = 0x2495DE0, //2495DD0 of die   
		World_GetFrameRatems = 0xED2480,  // ED2480
		World_GetFramerateOffset = 0x2E99330,
		World_GetNetLatency = 0xDB6B50,
		World_GetNetLatency_GetIdx = 0x1DCDB0,
		World_GetNetLatency_RealmNamePointer = 0x2ECA7AF,
		pSubZoneID = 0x2F7BB1C,
		pSubZoneText = 0x2F7AEB8,
		pZoneID = 0x2F7BB18,
		pZoneText = 0x2F7AEB8;
		
		//TODO
		//static inline uintptr_t CGUnit_C_SetTrackingPosition = 0x13A01C0; // ClickToMove
		//static inline uintptr_t  FaceTo = 0x139FF30;

	static inline  uintptr_t CameraPtr = 0x38E8; // Shifted 8 Bytes in Wotlk and Shifted 8 bytes since 38631

		//// Unit struct for wrath
	static inline uint8_t Type = 0x10; // 0x20 TBC
	static inline uint16_t Guid = 0x18;
	static inline uint16_t AnimationStatus = 0x14C;
	inline static uint16_t	GatherStatus = 0x6B0;
	static inline uint16_t DisplayID = 0x003C;
	static inline uint16_t Owner = 0x534;
	static inline uintptr_t AuraCount = 0x6A0; // 3B 91 ? ? ? ? 73 14 8B C2 48 69 D0 ? ? ? ? 48 8D 81 ? ? ? ? 48 03 C2 C3 33 C0 C3
	static inline uintptr_t AuraTable = AuraCount + 0x8;
	static inline uintptr_t AuraSize = 0xB0;


	static inline uintptr_t WoWObjTypeID = 0x24D;


	static inline uintptr_t CurrentSpeed = 0x1CC;
	static inline uintptr_t StopFall = CurrentSpeed - 0x8;
	static inline uintptr_t WalkSpeed = CurrentSpeed + 0x4;    
	static inline uintptr_t RunForwardSpeed = CurrentSpeed + 0x8;
	static inline uintptr_t RunBackwardsSpeed = CurrentSpeed + 0xC;
	static inline uintptr_t SwimmingSpeed = CurrentSpeed + 0x10;
	static inline uintptr_t SwimBackwardsSpeed = CurrentSpeed + 0x14;
	static inline uintptr_t FlyForwardSpeed = CurrentSpeed + 0x18;
	static inline uintptr_t FlyBackwardsSpeed2 = CurrentSpeed + 0x1C;
	static inline uintptr_t Player_rotationspeed = CurrentSpeed + 0x20; //OK


	static inline uintptr_t UnitPos = 0x148; // Fake teleport exploration...
	static inline uintptr_t anchor_position = 0x18C;
	static inline uintptr_t anchor_facing = anchor_position + 0xC;  // 198
	static inline uintptr_t anchor_pitch = anchor_position + 0x10;  // 19C
	static inline uintptr_t direction = anchor_position + 0x18; // 0x1A4
	static inline uintptr_t direction_2d = anchor_position + 0x1C; // 0x1A8


	static inline uintptr_t UnitId = 0x0; // ?
	static inline uintptr_t Master = 0x0; // ?
	static inline uintptr_t Charmer = 0x0; // ?

	static inline uintptr_t DisplayId = 0x388; // Updated

	static inline uintptr_t CastID = 0x540; // Updated
	static inline uintptr_t ChanID = 0x598; // Updated

	static inline uintptr_t CastEnd = 0x594; // Updated
	static inline uintptr_t ChanEnd = 0x5A4; // Updated

	static inline uintptr_t CastStart = 0x590; // Updated
	static inline uintptr_t ChanStart = 0x5A0; // Updated

	static inline uintptr_t Info = 0x380; // Updated
	static inline uintptr_t Type2 = 0x30; // Updated
	static inline uintptr_t Family = 0x34; // Updated
	static inline uintptr_t Rank = 0x38; // Updated
	static inline uintptr_t GatherType = 0xE8; // Updated
	static inline uintptr_t Name = 0xF8; // Updated

	static inline uintptr_t UnitFlag1 = 0xD5F0; // Updated
	static inline uintptr_t UnitFlag2 = 0xD5F4; // Updated
	static inline uintptr_t UnitFlag3 = 0xD5F8; // Updated
	static inline uintptr_t DynamicFlag = 0xDC; // Updated

	static inline uintptr_t Summoner = 0xD540; // Updated => ?
	static inline uintptr_t Creator = 0xD560; // Updated => ?
	static inline uintptr_t NpcFlag = 0xD500; // Updated => ?
	static inline uintptr_t Faction = 0xD5EC; // Updated => ?

	static inline uintptr_t Level = 0xD5C8; // Updated
	static inline uintptr_t Health = 0xD3A8; // Updated
	static inline uintptr_t MaxHealth = 0xD4D0; // Updated

	static inline uintptr_t Mana = 0xD7E0;
	static inline uintptr_t MaxMana = 0xD7FC; // 0xD7FC;

	static inline uintptr_t Energy = 0xD3AC;
	static inline uintptr_t MaxEnergy = Energy + 0x4;

	static inline uintptr_t Sex = 0xD5BF; // Updated => ?
	static inline uintptr_t Race = 0xD5BC; // Updated => ?
	static inline uintptr_t Class = 0xD5BD; // Updated => ?

	static inline uintptr_t Target = 0x710; //0xD588; // Updated
	static inline uintptr_t MountID = 0xD618; // Updated

	static inline uintptr_t Movement = 0xF0; // Updated
	static inline uintptr_t Location = 0x20; // Updated
	static inline uintptr_t RotationD = 0x2C; // Updated
	static inline uintptr_t RotationF = 0x30; // Updated
	static inline uintptr_t Pitch = 0x34; // Updated
	static inline uintptr_t MoveFlag = 0x58; // Updated

	static inline uintptr_t MaxPower1 = 0xD7FC; // Updated
	static inline uintptr_t MaxPower2 = 0xD800; // Updated
	static inline uintptr_t MaxPower3 = 0xD804; // Updated
	static inline uintptr_t MaxPower4 = 0xD808; // Updated
	static inline uintptr_t MaxPower5 = 0xD80C; // Updated
	static inline uintptr_t MaxPower6 = 0xD810; // Updated
	static inline uintptr_t MaxPower7 = 0xD814; // Updated

	static inline uintptr_t Power1 = 0xD7E0; // Updated
	static inline uintptr_t Power2 = 0xD7E4; // Updated
	static inline uintptr_t Power3 = 0xD7E8; // Updated
	static inline uintptr_t Power4 = 0xD7EC; // Updated
	static inline uintptr_t Power5 = 0xD7F0; // Updated 
	static inline uintptr_t Power6 = 0xD7F4; // Updated
	static inline uintptr_t Power7 = 0xD7F8; // Updated

	static inline uintptr_t UnitPowerType = 0xD5C0;
	static inline uintptr_t UnitMaxPower = 0xD7FC;

	static inline uintptr_t MovementShared_IsJumpingUp = 0x1C0;
	static inline uintptr_t NoFall = 0x1C4; //Tricky to achief stopfall nowadays most of the time DC //01C4 StopFall ->0x40670C38 Falling state?


	static inline uintptr_t NoColl = 0x234;    // Set to 255 fly through mountains/Buildings     Default Value: 0.3984375298
	static inline uintptr_t Wallllimb1 = NoColl + 0x4;
	static inline uintptr_t Wallllimb2 = NoColl + 0x8;  //Set to 255 Wallclimb Default Value: 0.00f

	static inline uintptr_t GameObjectLocation = 0x108;
	static inline uintptr_t GameObjectFishingBobberFlag = 0xA0;
	static inline uintptr_t GameObjectNamePointer = 0x148;
	static inline uintptr_t GameObjectName = 0xE0;
	static inline uintptr_t GameObjectState = 0x1A8;
	static inline uintptr_t GameObjectFlags = 0x230;
	static inline uintptr_t GameObjectCreator = 0x210;





//OLD

	//// Pointers
	//static inline uintptr_t IsPlayerInWorld = Base + 0x2CEBBDC;// Script_IsPlayerInWorld or Script_GameMovieFinished 

	//// object manager
	//static inline uintptr_t ClntObjMgrEnumVisibleObjectsPtr = Base + 0x583F10; // Good
	//static inline uintptr_t ClntObjMgrGetMapId = Base + 0xD41750; //GOOD
	//static inline uintptr_t ClntObjMgrIsValid = Base + 0x587D60; //GOOD



	//static inline uintptr_t ClickToMove = Base + 0x407B70;  //TODO
	//static inline uintptr_t FaceTo = Base + 0x4078F0;      // TODO
	//
	//// pointers 40 55 48 83 EC 60 48 8B 15 ? ? ? ? 48 8B E9 48 8B 05 ? ? ? ? 48 85 D2 74 09 48 85 C0 0F 85 ? ? ? ? 48 89 5C 24 ? 48 8D 05 ? ? ? ? 
	//static inline uintptr_t InvalidPtrCheckMin = Base + 0x306D998; // GOOD
	//static inline uintptr_t InvalidPtrCheckMax = Base + 0x306D9A0; // GOOD
	//static inline uintptr_t HardwareEventPtr = Base + 0x2E5CA38; 

	//static inline uintptr_t CGItem_UseItemParm = Base + 0x2C86680; // GOOD
	//static inline uintptr_t CGItem_UseItem = Base + 0x443950; // GOOD

	//// Unit struct
	//static inline uint8_t Type = 0x20;
	//static inline uint16_t Guid = 0x58;
	//static inline uint16_t AnimationStatus = 0x14C;
	//inline static uint16_t	GatherStatus = 0x6B0;
	//static inline uint16_t DisplayID = 0x003C;
	//static inline uint16_t Owner = 0x534;
	//static inline uintptr_t AuraCount = 0x6C0; // 3B 91 ? ? ? ? 73 14 8B C2 48 69 D0 ? ? ? ? 48 8D 81 ? ? ? ? 48 03 C2 C3 33 C0 C3
	//static inline uintptr_t AuraTable = AuraCount + 0x8;
	//static inline uintptr_t AuraSize = 0xB0;

	////cast  
	////static inline uintptr_t GetBagAndSlot = Base + 0x17C2630; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC 30 4C 8B 74 24 ? 49 8B D9 49 C7 00 ? ? ? ? 49 8B F0 41 C7 01 ? ? ? ? 8B EA 48 63 F9 41 C7 06 ? ? ? ? E8 ? ? ? ? 48 85 C0 74 3D 89 2B 85 FF 79 7D 48 05 ? ? ? ? 48 89 06 83 FF FB 74 63
	////static inline uintptr_t GetItemPointer = Base + 0x139B360; // script_C_NewItems_IsNewItem 40 57 48 83 EC 50 BA ? ? ? ? 48 8B F9 E8 ? ? ? ? 85 C0 0F 84 ? ? ? ? BA ? ? ? ? 48 8B CF E8 ? ? ? ? 85 C0 0F 84 ? ? ? ? BA ? ? ? ? 48 89 5C 24 ? 48 8B CF E8 ? ? ? ? BA ? ? ? ? 48 8B CF 8B D8 E8 ? ? ? ? 48 8D 4C 24 ? 48 89 4C 24 ? 4C 8D 4C 24 ? 4C 8D 44 24 ? 8D 48 FF 8D 53 FF E8 ? ? ? ? 48 8B 5C 24 ? 84 C0 
	//static inline uintptr_t Spell_C_GetMinMaxRange = Base + 0x322CB0;
	//static inline uintptr_t Spell_C_IsCurrentSpell = Base + 0x32D860; 
	//static inline uintptr_t Spell_C_GetSpellCoolDown = Base + 0x325660; 
	//static inline uintptr_t Spell_C_HaveSpellPower = Base + 0x3297B0; 
	//static inline uintptr_t Spell_C_CastSpell = Base + 0x62C050;
	//static inline uintptr_t isSpellKnown = Base + 0x6347A0; 
	//static inline uintptr_t findSlotBySpellId = Base + 0x62E230; 
	//
	//static inline uintptr_t UnitReaction = Base + 0x3F2420; //Good
	//static inline uintptr_t Cooldown = Base + 0x2C866A0; 


	////Cooldown not good


	//static inline uintptr_t GuidToString = Base + 0x285A10; // 48 89 ?? ?? ?? 48 89 ?? ?? ?? 56 48 ?? ?? ?? 41 ?? ?? 48 ?? ?? 48 ?? ?? 45


	////Release ghost
	//static inline uintptr_t CGPlayer_C_HandleRepopRequest = Base + 0x374A50; 
	//static inline uintptr_t CGPlayer_AcceptResurrect = Base + 0x362730;//0x1244984; // S__int64 __fastcall CGPlayer_AcceptResurrect_5RESURRECT_CLIENT_RESPONSE(__int64 PlayerPtr, int Accept 0) 
	////89 54 24 10 48 89 4C 24 ? 48 81 EC ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 0F B6 C0 85 C0 75 02 EB 73 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 0F 10 00 

	////40 53 48 83 EC 30 83 3D ? ? ? ? ? 48 8B D9 74 0C BA ? ? ? ? Second Call LeftClick, Third Call RightClick
	//static inline uintptr_t SpriteLeftClick = Base + 0x5C61E0;
	//static inline uintptr_t SpriteRightClick = Base + 0x5C6610;

	//static inline uintptr_t CGUnit_C_OnAttackIconPressed = Base + 0x3F89F0; //Script::Attack 48 89 74 24 ? 41 54 41 56 41 57 48 83 EC 70 0F 10 02 48 8B F1 45 8B F9 48 8D 0D ? ? ? ? 45 8B E0 0F 11 44 24 ? E8 ? ? ? ? C6 44 24 ? ? 48 8D 54 24 ? 45 33 F6 C6 44 24 ? ? 45 8B C4 C6 44 24 ? ? 0F 10 00 
	//static inline uintptr_t CGUnit_C_IsInMelee = Base + 0x3F2590; 

	////static inline uintptr_t spellDB = 0x00;//Script_GetProfessionInfo, First CS:Offset under WowClientDB2_Base__GetRecordDataUnsafe
	////static inline uintptr_t spellDBTotalRowsAddr = 0x00 ; , Second CS:Offset

	////Globals
	//static inline uintptr_t isLootWindowOpen = Base + 0x2D2AAC0; // xmmword 4C 8D 05 ? ? ? ? BA ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 4C 8B 00 48 8B C8 41 FF 90 ? ? ? ? 4C 8B F0 4D 85 F6 0F 84 ? ? ? ? 85 DB 0F 88 ? ? ? ? 41 3B 1E 0F 8D ? ? ? ? 8B D3 49 8B CE EB 24 49 8D 9F ? ? ? ? E8 ? ? ? ? 8D 50 FF 48 85 DB 0F 84 ? ? ? ? 83 FA 12 0F 87 ? ? ? ? 48 8B CB E8 ? ? ? ? 48 8B C8 48 85 C0 0F 84 ? ? ? ? 0F 10 05 ? ? ? ?
	//static inline uintptr_t CorpseMapID = Base + 0x2B415B0;  // First Dword 40 53 48 83 EC 20 48 8B D9 48 8B D1 48 8D 0D ? ? ? ? E8 ? ? ? ? F3 0F 10 43 ? F3 0F 10 13 F3 0F 10 4B ? F3 0F 59 D2 F3 0F 59 C0 F3 0F 59 C9 F3 0F 58 D0 F3 0F 58 D1 0F 54 15 ? ? ? ? 0F 2F 15 ? ? ? ? 0F 93 C0 48 83 C4 20 5B C3 
	static inline uintptr_t CorpsePosition = CorpseMapID + 0x40; //Bruteforced always ~close to the CorpseMapID
	static inline uintptr_t Bool_MustEnterInstanceToRecoverBodymsg = CorpseMapID + 0x04; 

	////Camera WorldFrame::GetActiveCamera
	//static inline  uintptr_t CameraMgr = Base + 0x30BB1B8; // 48 89 74 24 ? 48 89 7C 24 ? 0F 29 74 24 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 89 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ?
	//static inline  uintptr_t CameraPtr = 0x38E0; // Shifted 8 bytes since 38631

	////ESP
	//static inline uintptr_t GetWorld = Base + 0x2C6827C; // Script_QuitGame, First Call, First DWORD. OR search String logs sub Above that!  (48 83 EC 28 45 33 C0 48 8D 0D ? ? ? ? 33 D2 E8 ? ? ? ? 4C 8D 05 ? ? ? ? 33 D2 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9 74 10 48 8D 15 ? ? ? ? 48 83 C4 28 E9 ? ? ? ? 48 83 C4 28 C3 )
	//static inline uintptr_t WorldFrameIntersect = Base + 0x1CFAC60; // F12, Search: Preload Immediate End -> DATA XREF: sub -> Sub below that, First Call and select second sub.
	////48 83 EC 58 8B 42 08 F2 0F 10 02 48 8D 54 24 ? 89 44 24 28 41 8B 40 08 89 44 24 34 48 8B 84 24 ? ? ? ? 48 89 44 24 ? 48 8B 84 24 ? ? ? ? F2 0F 11 44 24 ? F2 41 0F 10 00 48 89 44 24 ? F2 0F 11 44 24 ? 4C 89 4C 24 ? E8 ? ? ? ? 48 83 C4 58 C3 
};

// Below offsets can be used for sig scan

//WorldFrameIntersect
//CGUnit_C_OnAttackIconPressed
// CGUnit_C_IsInMelee
//Spellc funcs
//CancelChannelOffset
