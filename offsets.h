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
	// base address
	static inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));

	// Pointers
	static inline uintptr_t IsPlayerInWorld = Base + 0x2CEBBDC;// Script_IsPlayerInWorld or Script_GameMovieFinished 

	// object manager
	static inline uintptr_t ClntObjMgrEnumVisibleObjectsPtr = Base + 0x14B9640; // 48 89 74 24 ? 57 48 83 EC 20 48 8B 05 ? ? ? ? 48 8B FA 48 8B F1 4C 8B 80 ? ? ? ? 41 F6 C0 01 75 09 4D 85 C0 74 04 33 D2 EB 05 BA ? ? ? ? 33 C9 48 89 5C 24 ? 85 D2 49 0F 44 C8 90 F6 C1 01 
	static inline uintptr_t ClntObjMgrGetMapId = Base + 0xD41750; //48 8B 05 ? ? ? ? 48 85 C0 74 07 8B 80 ? ? ? ? C3 C3  !!Second QWORD
	static inline uintptr_t ClntObjMgrIsValid = Base + 0x587D60; // 48 83 EC 28 44 0F B6 C1 48 8B 0D ? ? ? ? 48 85 C9 74 15 BA ? ? ? ? E8 ? ? ? ? 84 C0 74 07 B0 01 48 83 C4 28 C3 32 C0 48 83 C4 28 C3 


	//CTM    --Must   //Mhmmh??  v11 = sub_1B75050(*(_QWORD *)(PlayerPtr + 240), (__int64)&Position, (unsigned int *)&v13);  
	static inline uintptr_t ClickToMove = Base + 0x407B70;  //ClickToMove(v11, PlayerPtr, PlayerPtr, a3, v12);
	static inline uintptr_t FaceTo = Base + 0x4078F0;      // void __usercall FaceTo(__int64 PlayerPtr@<rcx>, int a2@<ebx>, int a3@<esi>)
	
	// pointers 40 55 48 83 EC 60 48 8B 15 ? ? ? ? 48 8B E9 48 8B 05 ? ? ? ? 48 85 D2 74 09 48 85 C0 0F 85 ? ? ? ? 48 89 5C 24 ? 48 8D 05 ? ? ? ? 
	static inline uintptr_t InvalidPtrCheckMin = Base + 0x306D998;
	static inline uintptr_t InvalidPtrCheckMax = Base + 0x306D9A0;
	static inline uintptr_t HardwareEventPtr = Base + 0x2E5CA38; //0F 85 ? ? ? ? 48 8B 07 48 8B CF 8B 1D ? ? ? ? FF 90 ? ? ? ? 85 C0 74 11 48 8B 07 45 33 C0 33 D2 48 8B CF FF 90 ? ? ? ? E8 ? ? ? ? 48 85 C0 74 0A 33

	static inline uintptr_t CGItem_UseItemParm = Base + 0x2C86680; // Close to second lea under loc 75 34 E8 ? ? ? ? 8B D0 48 8D 0D ? ? ? ? E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 48 8B CB E8 ? ? ? ? 8B C8 48 8B D7 E8 ? ? ? ? 48 8B CB 84 C0 75 27 48 89 75 B8 48 89 75 C0 E8 ? ? ? ? 4C 8D 4D B8 45 33 C0 48 8D 15 ? ? ? ? 
	static inline uintptr_t CGItem_UseItem = Base + 0x443950; // 3B 91 ? ? ? ? 73 11 8B C2 48 83 C0 28 48 69 C0 ? ? ? ? 48 03 C1 C3 33 C0 C3

	// Unit struct
	static inline uint8_t Type = 0x20;
	static inline uint16_t Guid = 0x58;
	static inline uint16_t AnimationStatus = 0x14C;
	inline static uint16_t	GatherStatus = 0x6B0;
	static inline uint16_t DisplayID = 0x003C;
	static inline uint16_t Owner = 0x534;
	static inline uintptr_t AuraCount = 0x6C0; // 3B 91 ? ? ? ? 73 14 8B C2 48 69 D0 ? ? ? ? 48 8D 81 ? ? ? ? 48 03 C2 C3 33 C0 C3
	static inline uintptr_t AuraTable = AuraCount + 0x8;
	static inline uintptr_t AuraSize = 0xB0;

	//cast  
	//static inline uintptr_t GetBagAndSlot = Base + 0x17C2630; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC 30 4C 8B 74 24 ? 49 8B D9 49 C7 00 ? ? ? ? 49 8B F0 41 C7 01 ? ? ? ? 8B EA 48 63 F9 41 C7 06 ? ? ? ? E8 ? ? ? ? 48 85 C0 74 3D 89 2B 85 FF 79 7D 48 05 ? ? ? ? 48 89 06 83 FF FB 74 63
	//static inline uintptr_t GetItemPointer = Base + 0x139B360; // script_C_NewItems_IsNewItem 40 57 48 83 EC 50 BA ? ? ? ? 48 8B F9 E8 ? ? ? ? 85 C0 0F 84 ? ? ? ? BA ? ? ? ? 48 8B CF E8 ? ? ? ? 85 C0 0F 84 ? ? ? ? BA ? ? ? ? 48 89 5C 24 ? 48 8B CF E8 ? ? ? ? BA ? ? ? ? 48 8B CF 8B D8 E8 ? ? ? ? 48 8D 4C 24 ? 48 89 4C 24 ? 4C 8D 4C 24 ? 4C 8D 44 24 ? 8D 48 FF 8D 53 FF E8 ? ? ? ? 48 8B 5C 24 ? 84 C0 
	static inline uintptr_t Spell_C_GetMinMaxRange = Base + 0x322CB0;// 0x1097010; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 49 8B D9 49 8B F8 8B F2 48 8B E9 E8 ? ? ? ? 89 44 24 28 4C 8B CB 48 8B 44 24 ? 4C 8B C7 8B D6 48 89 44 24 ? 48 8B CD E8 ? ? ? ? 48 8B 5C 24 ? 48 8B 6C 24 ? 48 8B 74 24 ? 48 83 C4 30 5F 
	static inline uintptr_t Spell_C_IsCurrentSpell = Base + 0x32D860; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 81 EC ? ? ? ? 8B D9 
	static inline uintptr_t Spell_C_GetSpellCoolDown = Base + 0x325660; // 48 83 EC 58 44 8B D1 C6 44 24 ? ? 41 F7 D8 48 8D 05 ? ? ? ? 44 8B C2 41 8B D2 48 1B C9 81 E1 ? ? ? ? 48 03 C8 0F B6 84 24 ? ? ? ? 88 44 24 40 48 8B 84 24 ? ? ? ? 48 89 44 24 ? 48 8B 84 24 ? ? ? ? 
	static inline uintptr_t Spell_C_CastSpell = Base + 0x62C050; // From Spell_C_CastSpell not the function itself. 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 41 56 48 83 EC 50 41 0F B6 F1 49 8B E8 44 0F B6 F2 48 63 D9 E8 ? ? ? ? 85 C0 0F 85 ? ? ? ? 39 05 ? ? ? ? 0F 85 ? ? ? ?
	static inline uintptr_t Spell_C_HaveSpellPower = Base + 0x3297B0; // 4C 89 4C 24 ? 4C 89 44 24 ? 89 54 24 10 53 55 56 57
	static inline uintptr_t isSpellKnown = Base + 0x6347A0; // 48 89 5C 24 ? 57 48 83 EC 20 0F B6 FA 8B D9 E8 ? ? ? ? 85 C0 79 43 40 84 FF 74 18 8B CB E8 ? ? ? ? 48 85 C0 0F 95 C0 48 8B 5C 24 ? 48 83 C4 20 5F C3 81 FB ? ? ? ?
	static inline uintptr_t findSlotBySpellId = Base + 0x62E230; //44 8B C1 85 C9 0F 84 ? ? ? ? 84 D2 74 51 44 8B 0D ? ? ? ? 33 D2 45 85 C9 74 74 4C 8B 15 ? ? ? ? 49 8B 0C D2 
	//static inline uintptr_t CancelChannelOffset = Base + 0x1106010;  //48 89 5C 24 ?? 48 89 74 24 ?? 57 48 83 EC 50 8B F2 8B D9 E8 ?? ?? ?? ?? BA ?? ?? ?? ?? 41 B8 ?? ?? (...) FF
	static inline uintptr_t UnitReaction = Base + 0x1311A90; //48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 E8 ? ? ? ? 83 F8 04 7D 37 48 8B D7 48 8B CB E8 ? ? ? ? 83 F8 04 7D 27 8B 87 ? ? ? ? C1 E8 14 A8 01 74 0D 8B 83 ? ? ? ? C1 E8 03 A8 01 75 0D 32 C0 48 8B 5C 24 ? 48 83 C4 20 5F C3 48 8B 5C 24 ? B0 01 48 83 C4 20 5F C3
	static inline uintptr_t Cooldown = Base + 0x2C866A0;

	static inline uintptr_t GuidToString = Base + 0x285A10; // 48 89 ?? ?? ?? 48 89 ?? ?? ?? 56 48 ?? ?? ?? 41 ?? ?? 48 ?? ?? 48 ?? ?? 45

	//Release ghost
	static inline uintptr_t CGPlayer_C_HandleRepopRequest = Base + 0x374A50; // 40 53 48 83 EC 50 48 8B 01 0F B6 DA FF 90 ? ? ? ? 84 C0 74 18 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 4C 24 ? 88 5C 24 40 E8 ? ? ? ? 48 83 C4 50 5B 
	static inline uintptr_t RetrieveCorpse = Base + 0x00;//0x1244984; // Should be right but not doing a thing. Maybe this is for accept ressurect? and not revive at corpse?
	//89 54 24 10 48 89 4C 24 ? 48 81 EC ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 0F B6 C0 85 C0 75 02 EB 73 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 0F 10 00 

	//40 53 48 83 EC 30 83 3D ? ? ? ? ? 48 8B D9 74 0C BA ? ? ? ? Second Call LeftClick, Third Call RightClick
	static inline uintptr_t SpriteLeftClick = Base + 0x5C61E0;
	static inline uintptr_t SpriteRightClick = Base + 0x5C6610;

	static inline uintptr_t CGUnit_C_OnAttackIconPressed = Base + 0x3F89F0; //Script::Attack 48 89 74 24 ? 41 54 41 56 41 57 48 83 EC 70 0F 10 02 48 8B F1 45 8B F9 48 8D 0D ? ? ? ? 45 8B E0 0F 11 44 24 ? E8 ? ? ? ? C6 44 24 ? ? 48 8D 54 24 ? 45 33 F6 C6 44 24 ? ? 45 8B C4 C6 44 24 ? ? 0F 10 00 
	static inline uintptr_t CGUnit_C_IsInMelee = Base + 0x3F2590; // 48 8B 81 ? ? ? ? 48 C1 E8 3A 84 C0 0F 95 C0 C3 

	//static inline uintptr_t spellDB = 0x00;//Script_GetProfessionInfo, First CS:Offset under WowClientDB2_Base__GetRecordDataUnsafe
	//static inline uintptr_t spellDBTotalRowsAddr = 0x00 ; , Second CS:Offset

	//Globals
	static inline uintptr_t isLootWindowOpen = Base + 0x2D2AAC0; // xmmword 4C 8D 05 ? ? ? ? BA ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 4C 8B 00 48 8B C8 41 FF 90 ? ? ? ? 4C 8B F0 4D 85 F6 0F 84 ? ? ? ? 85 DB 0F 88 ? ? ? ? 41 3B 1E 0F 8D ? ? ? ? 8B D3 49 8B CE EB 24 49 8D 9F ? ? ? ? E8 ? ? ? ? 8D 50 FF 48 85 DB 0F 84 ? ? ? ? 83 FA 12 0F 87 ? ? ? ? 48 8B CB E8 ? ? ? ? 48 8B C8 48 85 C0 0F 84 ? ? ? ? 0F 10 05 ? ? ? ?
	static inline uintptr_t CorpseMapID = Base + 0x2B415B0;  // First Dword 40 53 48 83 EC 20 48 8B D9 48 8B D1 48 8D 0D ? ? ? ? E8 ? ? ? ? F3 0F 10 43 ? F3 0F 10 13 F3 0F 10 4B ? F3 0F 59 D2 F3 0F 59 C0 F3 0F 59 C9 F3 0F 58 D0 F3 0F 58 D1 0F 54 15 ? ? ? ? 0F 2F 15 ? ? ? ? 0F 93 C0 48 83 C4 20 5B C3 
	static inline uintptr_t Corpsex = CorpseMapID + 0x40; //Bruteforced always ~close to the CorpseMapID
	static inline uintptr_t Bool_MustEnterInstanceToRecoverBodymsg = CorpseMapID + 0x04; 

	//Camera WorldFrame::GetActiveCamera
	static inline  uintptr_t CameraMgr = Base + 0x30BB1B8; // 48 89 74 24 ? 48 89 7C 24 ? 0F 29 74 24 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 89 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ?
	static inline  uintptr_t CameraPtr = 0x38E0; // Shifted 8 bytes since 38631

	//ESP
	static inline uintptr_t GetWorld = Base + 0x2C6827C; // Script_QuitGame, First Call, First DWORD. OR search String logs sub Above that!  (48 83 EC 28 45 33 C0 48 8D 0D ? ? ? ? 33 D2 E8 ? ? ? ? 4C 8D 05 ? ? ? ? 33 D2 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9 74 10 48 8D 15 ? ? ? ? 48 83 C4 28 E9 ? ? ? ? 48 83 C4 28 C3 )
	static inline uintptr_t WorldFrameIntersect = Base + 0x1CFAC60; // F12, Search: Preload Immediate End -> DATA XREF: sub -> Sub below that, First Call and select second sub.
	//48 83 EC 58 8B 42 08 F2 0F 10 02 48 8D 54 24 ? 89 44 24 28 41 8B 40 08 89 44 24 34 48 8B 84 24 ? ? ? ? 48 89 44 24 ? 48 8B 84 24 ? ? ? ? F2 0F 11 44 24 ? F2 41 0F 10 00 48 89 44 24 ? F2 0F 11 44 24 ? 4C 89 4C 24 ? E8 ? ? ? ? 48 83 C4 58 C3 
};

// Below offsets can be used for sig scan

//WorldFrameIntersect
//CGUnit_C_OnAttackIconPressed
// CGUnit_C_IsInMelee
//Spellc funcs
//CancelChannelOffset
