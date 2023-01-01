#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string>
#include <iostream>

//using namespace std;

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

#pragma pack(push, 1)


struct CGGuid
{
    uint64_t high;
    uint64_t low;

    bool isEmpty() { return high == 0 && low == 0; }

    bool operator!=(const CGGuid& rhs) const {
        return (this->high != rhs.high && this->low != rhs.low);
    }
    bool operator==(const CGGuid& rhs) const {
        return (this->high == rhs.high && this->low == rhs.low);
    }

    std::string toString() const { return std::string("Guid (" + std::to_string(high) + " " + std::to_string(low) + ")"); }
};
#pragma pack(pop)

enum AuraFlags : BYTE {
    Active = 0x80,
    Passive = 0x10, 
    Harmful = 0x20
};

enum CGGameUI_isinworldID : uint8_t
{
    NotInitialized = 0x0000000,
    LoadingScreen1 = 0x1000003,
    LoadingScreen2 = 0x1000002,
    Loaded = 0x1010004
};

enum class TypeIdTBC : uint8_t
{
    CGObject = 0,
    CGItem = 1,
    CGContainer = 2,
    CGUnit = 3,
    CGPlayer = 4,
    CGActivePlayer = 5,
    CGGameObject = 6,
    CGDynamicObject = 7,
    CGCorpse = 8,
    CGAreaTrigger = 9,
    CGSceneObject = 10,
    CGConversation = 11,
    AIGroup = 12,
    Scenario = 13,
    Loot = 14,
    Invalid = 15
};

//Wrath
enum class TypeId : uint8_t
{
	CGObject = 0,
	CGItem = 1,
	CGContainer = 2,
	CGAzeriteEmpoweredItem_C,
	CGAzeriteItem_C,
	CGUnit = 5,
	CGPlayer = 6,
	CGActivePlayer = 7,
	CGGameObject = 8,
	CGDynamicObject = 9,
	CGCorpse = 10,
	CGAreaTrigger = 11,
	CGSceneObject = 12,
	CGConversation = 13,
	//AIGroup = 14,
	//Scenario = 15,
	//Loot = 16,
	Invalid = 17
};

enum class WoWObjTypeId : uint8_t
{
	Door = 0,
	Button = 1,
	Questgiver = 2,
	ChestHerbsMinerals = 3,// # Herbs, Minerals, Chests
	Binder = 4,
	Generic = 5,
	Trap = 6,
	Chair = 7,
	SpellFocus = 8,
	Text = 9,
	Goober = 10,
	TransportElevator = 11,
	AreaDamage = 12,
	Camera = 13,
	Mapobject = 14,
	MoTransportShip = 15,
	DuelFlag = 16,
	FishingNode = 17,
	Ritual = 18,
	Mailbox = 19,
	DONOTUSE1 = 20,
	GuardPost = 21,
	SpellCaster = 22,
	MeetingStone = 23,
	FlagStand = 24,
	FishingHole = 25,
	FlagDrop = 26,
	DONOTUSE2 = 27,
	DONOTUSE3 = 28,
	ControlZone = 29,
	AuraGenerator = 30,
	DungeonDifficulty = 31,
	BarberChair = 32,
	DestructibleBuilding = 33,
	GuildBank = 34,
	Trapdoor = 35,
	Newflag = 36,
	Newflagdrop = 37,
	GarrisonBuilding = 38,
	GarrisonPlot = 39,
	ClientCreature = 40,
	ClientItem = 41,
	CapturePoint = 42,
	PhaseableMO = 43,
	GarrisonMonument = 44,
	GarrisonShipment = 45,
	GarrisonMonumentPlaque = 46,
	NUM_GAMEOBJECT_TYPE = 47
};


enum class PowerTypeId : uint8_t
{
	mana = 0,
	rage = 1,
	focus = 2,
	energy = 3,
	happiness = 4,
	runes = 5,
	runicpower = 6,
	SoulShards,
	HolyPower,
	Maelstrom,
	Chi,
	Insanity,
	ComboPoints,
	Obsolete2,
	ArcaneCharges,
	Fury,
	Pain,
	Essence,
	RuneBlood,
	RuneFrost,
	RuneUnholy
};

enum WoWClass : uint8_t
{
    None = 0,
    Warrior = 1,
    Paladin = 2,
    Hunter = 3,
    Rogue = 4,
    Priest = 5,
    DeathKnight = 6,
    Shaman = 7,
    Mage = 8,
    Warlock = 9,
    Druid = 11,
};

enum WoWRace : uint8_t
{
    Human = 1,
    Orc,
    Dwarf,
    NightElf,
    Undead,
    Tauren,
    Gnome = 115,
    TrollFemale = 116,
    Troll = 158,
    Goblin = 8,
    BloodElf,
    Draenei,
    FelOrc,
    Naga,
    Broken,
    Skeleton = 15,
    Draeneis = 1629,
    BloodElfs = 1610,
};

enum class IntersectFlags {
    None,
    DoodadCollision = 0x00000001,
    DoodadRender = 0x00000002,
    WmoCollision = 0x00000010,
    WmoRender = 0x00000020,
    WmoNoCamCollision = 0x00000040,
    Terrain = 0x00000100,
    IgnoreWmoDoodad = 0x00002000,
    LiquidWaterWalkable = 0x00010000,
    LiquidAll = 0x00020000,
    Cull = 0x00080000,
    EntityCollision = 0x00100000,
    EntityRender = 0x00200000,
    Collision = DoodadCollision | WmoCollision | Terrain | EntityCollision,
    LineOfSight = WmoCollision | EntityCollision | DoodadCollision
};

enum UnitDynFlags {
    UNIT_DYNFLAG_NONE = 0x0000,
    UNIT_DYNFLAG_HIDE_MODEL = 0x0001, // Object model is not shown with this flag
    UNIT_DYNFLAG_LOOTABLE = 0x0004,
    UNIT_DYNFLAG_TRACK_UNIT = 0x0008,
    UNIT_DYNFLAG_TAPPED = 0x0010, // Lua_UnitIsTapped - Indicates the target as grey for the client.
	UNIT_DYNFLAG_TAPPEDBYME = 0x0020, // 
    UNIT_DYNFLAG_DEAD = 0x0040,
    UNIT_DYNFLAG_REFER_A_FRIEND = 0x0080,
	UNIT_DYNFLAG_ISTAPPEDBYALL_THREATLIST = 0x100
};

enum SPELL_FAILED_REASON : BYTE
{
	Success = 0,
	AffectingCombat = 1,
	AlreadyAtFullHealth = 2,
	AlreadyAtFullMana = 3,
	AlreadyAtFullPower = 4,
	AlreadyBeingTamed = 5,
	AlreadyHaveCharm = 6,
	AlreadyHaveSummon = 7,
	AlreadyOpen = 8,
	AuraBounced = 9,
	AutotrackInterrupted = 10,
	BadImplicitTargets = 11,
	BadTargets = 12,
	CantBeCharmed = 13,
	CantBeDisenchanted = 14,
	CantBeDisenchantedSkill = 15,
	CantBeMilled = 16,
	CantBeProspected = 17,
	CantCastOnTapped = 18,
	CantDuelWhileInvisible = 19,
	CantDuelWhileStealthed = 20,
	CantStealth = 21,
	CasterAurastate = 22,
	CasterDead = 23,
	Charmed = 24,
	ChestInUse = 25,
	Confused = 26,
	DontReport = 27,
	EquippedItem = 28,
	EquippedItemClass = 29,
	EquippedItemClassMainhand = 30,
	EquippedItemClassOffhand = 31,
	Error = 32,
	Fizzle = 33,
	Fleeing = 34,
	FoodLowlevel = 35,
	Highlevel = 36,
	HungerSatiated = 37,
	Immune = 38,
	IncorrectArea = 39,
	Interrupted = 40,
	InterruptedCombat = 41,
	ItemAlreadyEnchanted = 42,
	ItemGone = 43,
	ItemNotFound = 44,
	ItemNotReady = 45,
	LevelRequirement = 46,
	LineOfSight = 47,
	TargetLowlevel = 48,
	LowCastlevel = 49,
	MainhandEmpty = 50,
	Moving = 51,
	NeedAmmo = 52,
	NeedAmmoPouch = 53,
	NeedExoticAmmo = 54,
	NeedMoreItems = 55,
	Nopath = 56,
	NotBehind = 57,
	NotFishable = 58,
	NotFlying = 59,
	NotHere = 60,
	NotInfront = 61,
	NotInControl = 62,
	NotKnown = 63,
	NotMounted = 64,
	NotOnTaxi = 65,
	NotOnTransport = 66,
	NotReady = 67,
	NotShapeshift = 68,
	NotStanding = 69,
	NotTradeable = 70,
	NotTrading = 71,
	NotUnsheathed = 72,
	NotWhileGhost = 73,
	NotWhileLooting = 74,
	NoAmmo = 75,
	NoChargesRemain = 76,
	NoChampion = 77,
	NoComboPoints = 78,
	NoDueling = 79,
	NoEndurance = 80,
	NoFish = 81,
	NoItemsWhileShapeshifted = 82,
	NoMountsAllowed = 83,
	NoPet = 84,
	NoPower = 85,
	NothingToDispel = 86,
	NothingToSteal = 87,
	OnlyAbovewater = 88,
	OnlyDaytime = 89,
	OnlyIndoors = 90,
	OnlyMounted = 91,
	OnlyNighttime = 92,
	OnlyOutdoors = 93,
	OnlyShapeshift = 94,
	OnlyStealthed = 95,
	OnlyUnderwater = 96,
	OutOfRange = 97,
	Pacified = 98,
	Possessed = 99,
	Reagents = 100,
	RequiresArea = 101,
	RequiresSpellFocus = 102,
	Rooted = 103,
	Silenced = 104,
	SpellInProgress = 105,
	SpellLearned = 106,
	SpellUnavailable = 107,
	Stunned = 108,
	TargetsDead = 109,
	TargetAffectingCombat = 110,
	TargetAurastate = 111,
	TargetDueling = 112,
	TargetEnemy = 113,
	TargetEnraged = 114,
	TargetFriendly = 115,
	TargetInCombat = 116,
	TargetIsPlayer = 117,
	TargetIsPlayerControlled = 118,
	TargetNotDead = 119,
	TargetNotInParty = 120,
	TargetNotLooted = 121,
	TargetNotPlayer = 122,
	TargetNoPockets = 123,
	TargetNoWeapons = 124,
	TargetNoRangedWeapons = 125,
	TargetUnskinnable = 126,
	ThirstSatiated = 127,
	TooClose = 128,
	TooManyOfItem = 129,
	TotemCategory = 130,
	Totems = 131,
	TryAgain = 132,
	UnitNotBehind = 133,
	UnitNotInfront = 134,
	WrongPetFood = 135,
	NotWhileFatigued = 136,
	TargetNotInInstance = 137,
	NotWhileTrading = 138,
	TargetNotInRaid = 139,
	TargetFreeforall = 140,
	NoEdibleCorpses = 141,
	OnlyBattlegrounds = 142,
	TargetNotGhost = 143,
	TransformUnusable = 144,
	WrongWeather = 145,
	DamageImmune = 146,
	PreventedByMechanic = 147,
	PlayTime = 148,
	Reputation = 149,
	MinSkill = 150,
	NotInArena = 151,
	NotOnShapeshift = 152,
	NotOnStealthed = 153,
	NotOnDamageImmune = 154,
	NotOnMounted = 155,
	TooShallow = 156,
	TargetNotInSanctuary = 157,
	TargetIsTrivial = 158,
	BmOrInvisgod = 159,
	ExpertRidingRequirement = 160,
	ArtisanRidingRequirement = 161,
	NotIdle = 162,
	NotInactive = 163,
	PartialPlaytime = 164,
	NoPlaytime = 165,
	NotInBattleground = 166,
	NotInRaidInstance = 167,
	OnlyInArena = 168,
	TargetLockedToRaidInstance = 169,
	OnUseEnchant = 170,
	NotOnGround = 171,
	CustomError = 172,
	TooManySockets = 173,
	CantDoThatRightNow = 173,
	InvalidGlyph = 175,
	UniqueGlyph = 176,
	GlyphSocketLocked = 177,
	NoValidTargets = 178,
	ItemAtMaxCharges = 179,
	NotInBarbershop = 180,
	FishingTooLow = 181,
	ItemEnchantTradeWindow = 182,
	SummonPending = 183,
	MaxSockets = 184,
	PetCanRename = 185,
	TargetCannotBeResurrected = 186,
	Unknownn = 187,
	Ok = 0xFF
};
enum class ControlBits {
	Nothing = 0x00000000,
	CtmWalk = 0x00001000,
	Front = 0x00000010,
	Back = 0x00000020,
	Jump = 0x00002000,
	Left = 0x00000100,
	Right = 0x00000200,
	MovingFrontOrBack = 0x00010000,
	StrafeLeft = 0x00000040,
	StrafeRight = 0x00000080,
	Strafing = 0x00020000,
	Turning = 0x00040000
};
