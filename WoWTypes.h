#pragma once
//#include "SharedDefines.h"
#include "stdafx.h"
typedef unsigned char byte;

const float MaxRange = 43.72f;
const float MeleeRange = 6;



//
//#define MAX_TYPE_ID        8
//
//enum TypeMask
//{
//	TYPEMASK_OBJECT = 0x0001,
//	TYPEMASK_ITEM = 0x0002,
//	TYPEMASK_CONTAINER = 0x0004,
//	TYPEMASK_UNIT = 0x0008,                       // players also have it
//	TYPEMASK_PLAYER = 0x0010,
//	TYPEMASK_GAMEOBJECT = 0x0020,
//	TYPEMASK_DYNAMICOBJECT = 0x0040,
//	TYPEMASK_CORPSE = 0x0080,
//
//	// used combinations in Player::GetObjectByTypeMask (TYPEMASK_UNIT case ignore players in call)
//	TYPEMASK_CREATURE_OR_GAMEOBJECT = TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT,
//	TYPEMASK_CREATURE_GAMEOBJECT_OR_ITEM = TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT | TYPEMASK_ITEM,
//	TYPEMASK_CREATURE_GAMEOBJECT_PLAYER_OR_ITEM = TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT | TYPEMASK_ITEM | TYPEMASK_PLAYER,
//
//	TYPEMASK_WORLDOBJECT = TYPEMASK_UNIT | TYPEMASK_PLAYER | TYPEMASK_GAMEOBJECT | TYPEMASK_DYNAMICOBJECT | TYPEMASK_CORPSE,
//};
//
//enum HighGuid
//{
//	HIGHGUID_ITEM = 0x4000,                       // blizz 4000
//	HIGHGUID_CONTAINER = 0x4000,                       // blizz 4000
//	HIGHGUID_PLAYER = 0x0000,                       // blizz 0000
//	HIGHGUID_GAMEOBJECT = 0xF110,                       // blizz F110
//	HIGHGUID_TRANSPORT = 0xF120,                       // blizz F120 (for GAMEOBJECT_TYPE_TRANSPORT)
//	HIGHGUID_UNIT = 0xF130,                       // blizz F130
//	HIGHGUID_PET = 0xF140,                       // blizz F140
//	HIGHGUID_DYNAMICOBJECT = 0xF100,                       // blizz F100
//	HIGHGUID_CORPSE = 0xF101,                       // blizz F100
//	HIGHGUID_MO_TRANSPORT = 0x1FC0,                       // blizz 1FC0 (for GAMEOBJECT_TYPE_MO_TRANSPORT)
//};
//
//enum EObjectFields
//{
//	OBJECT_FIELD_GUID = 0x00, // Size:2
//	OBJECT_FIELD_TYPE = 0x02, // Size:1
//	OBJECT_FIELD_ENTRY = 0x03, // Size:1
//	OBJECT_FIELD_SCALE_X = 0x04, // Size:1
//	OBJECT_FIELD_PADDING = 0x05, // Size:1
//	OBJECT_END = 0x06,
//};
//
//enum EItemFields
//{
//	ITEM_FIELD_OWNER = OBJECT_END + 0x00, // Size:2
//	ITEM_FIELD_CONTAINED = OBJECT_END + 0x02, // Size:2
//	ITEM_FIELD_CREATOR = OBJECT_END + 0x04, // Size:2
//	ITEM_FIELD_GIFTCREATOR = OBJECT_END + 0x06, // Size:2
//	ITEM_FIELD_STACK_COUNT = OBJECT_END + 0x08, // Size:1
//	ITEM_FIELD_DURATION = OBJECT_END + 0x09, // Size:1
//	ITEM_FIELD_SPELL_CHARGES = OBJECT_END + 0x0A, // Size:5
//	ITEM_FIELD_SPELL_CHARGES_01 = OBJECT_END + 0x0B,
//	ITEM_FIELD_SPELL_CHARGES_02 = OBJECT_END + 0x0C,
//	ITEM_FIELD_SPELL_CHARGES_03 = OBJECT_END + 0x0D,
//	ITEM_FIELD_SPELL_CHARGES_04 = OBJECT_END + 0x0E,
//	ITEM_FIELD_FLAGS = OBJECT_END + 0x0F, // Size:1
//	ITEM_FIELD_ENCHANTMENT = OBJECT_END + 0x10, // count=21
//	ITEM_FIELD_PROPERTY_SEED = OBJECT_END + 0x25, // Size:1
//	ITEM_FIELD_RANDOM_PROPERTIES_ID = OBJECT_END + 0x26, // Size:1
//	ITEM_FIELD_ITEM_TEXT_ID = OBJECT_END + 0x27, // Size:1
//	ITEM_FIELD_DURABILITY = OBJECT_END + 0x28, // Size:1
//	ITEM_FIELD_MAXDURABILITY = OBJECT_END + 0x29, // Size:1
//	ITEM_END = OBJECT_END + 0x2A,
//};
//
//enum EContainerFields
//{
//	CONTAINER_FIELD_NUM_SLOTS = ITEM_END + 0x00, // Size:1
//	CONTAINER_ALIGN_PAD = ITEM_END + 0x01, // Size:1
//	CONTAINER_FIELD_SLOT_1 = ITEM_END + 0x02, // count=56
//	CONTAINER_FIELD_SLOT_LAST = ITEM_END + 0x38,
//	CONTAINER_END = ITEM_END + 0x3A,
//};
//
///**
//* Fields that are available for a \ref Unit ?
//* \see Object::HasFlag
//* \todo Document this properly!
//*/
//enum EUnitFields
//{
//	UNIT_FIELD_CHARM = 0x00 + OBJECT_END, // Size:2
//	UNIT_FIELD_SUMMON = 0x02 + OBJECT_END, // Size:2
//	UNIT_FIELD_CHARMEDBY = 0x04 + OBJECT_END, // Size:2
//	UNIT_FIELD_SUMMONEDBY = 0x06 + OBJECT_END, // Size:2
//	UNIT_FIELD_CREATEDBY = 0x08 + OBJECT_END, // Size:2
//	UNIT_FIELD_TARGET = 0x0A + OBJECT_END, // Size:2
//	UNIT_FIELD_PERSUADED = 0x0C + OBJECT_END, // Size:2
//	UNIT_FIELD_CHANNEL_OBJECT = 0x0E + OBJECT_END, // Size:2
//	UNIT_FIELD_HEALTH = 0x10 + OBJECT_END, // Size:1
//	UNIT_FIELD_POWER1 = 0x11 + OBJECT_END, // Size:1
//	UNIT_FIELD_POWER2 = 0x12 + OBJECT_END, // Size:1
//	UNIT_FIELD_POWER3 = 0x13 + OBJECT_END, // Size:1
//	UNIT_FIELD_POWER4 = 0x14 + OBJECT_END, // Size:1
//	UNIT_FIELD_POWER5 = 0x15 + OBJECT_END, // Size:1
//	UNIT_FIELD_MAXHEALTH = 0x16 + OBJECT_END, // Size:1
//	UNIT_FIELD_MAXPOWER1 = 0x17 + OBJECT_END, // Size:1
//	UNIT_FIELD_MAXPOWER2 = 0x18 + OBJECT_END, // Size:1
//	UNIT_FIELD_MAXPOWER3 = 0x19 + OBJECT_END, // Size:1
//	UNIT_FIELD_MAXPOWER4 = 0x1A + OBJECT_END, // Size:1
//	UNIT_FIELD_MAXPOWER5 = 0x1B + OBJECT_END, // Size:1
//	UNIT_FIELD_LEVEL = 0x1C + OBJECT_END, // Size:1
//	UNIT_FIELD_FACTIONTEMPLATE = 0x1D + OBJECT_END, // Size:1
//	UNIT_FIELD_BYTES_0 = 0x1E + OBJECT_END, // Size:1
//	UNIT_VIRTUAL_ITEM_SLOT_DISPLAY = 0x1F + OBJECT_END, // Size:3
//	UNIT_VIRTUAL_ITEM_SLOT_DISPLAY_01 = 0x20 + OBJECT_END,
//	UNIT_VIRTUAL_ITEM_SLOT_DISPLAY_02 = 0x21 + OBJECT_END,
//	UNIT_VIRTUAL_ITEM_INFO = 0x22 + OBJECT_END, // Size:6
//	UNIT_VIRTUAL_ITEM_INFO_01 = 0x23 + OBJECT_END,
//	UNIT_VIRTUAL_ITEM_INFO_02 = 0x24 + OBJECT_END,
//	UNIT_VIRTUAL_ITEM_INFO_03 = 0x25 + OBJECT_END,
//	UNIT_VIRTUAL_ITEM_INFO_04 = 0x26 + OBJECT_END,
//	UNIT_VIRTUAL_ITEM_INFO_05 = 0x27 + OBJECT_END,
//	UNIT_FIELD_FLAGS = 0x28 + OBJECT_END, // Size:1
//	UNIT_FIELD_AURA = 0x29 + OBJECT_END, // Size:48
//	UNIT_FIELD_AURA_LAST = 0x58 + OBJECT_END,
//	UNIT_FIELD_AURAFLAGS = 0x59 + OBJECT_END, // Size:6
//	UNIT_FIELD_AURAFLAGS_01 = 0x5a + OBJECT_END,
//	UNIT_FIELD_AURAFLAGS_02 = 0x5b + OBJECT_END,
//	UNIT_FIELD_AURAFLAGS_03 = 0x5c + OBJECT_END,
//	UNIT_FIELD_AURAFLAGS_04 = 0x5d + OBJECT_END,
//	UNIT_FIELD_AURAFLAGS_05 = 0x5e + OBJECT_END,
//	UNIT_FIELD_AURALEVELS = 0x5f + OBJECT_END, // Size:12
//	UNIT_FIELD_AURALEVELS_LAST = 0x6a + OBJECT_END,
//	UNIT_FIELD_AURAAPPLICATIONS = 0x6b + OBJECT_END, // Size:12
//	UNIT_FIELD_AURAAPPLICATIONS_LAST = 0x76 + OBJECT_END,
//	UNIT_FIELD_AURASTATE = 0x77 + OBJECT_END, // Size:1
//	UNIT_FIELD_BASEATTACKTIME = 0x78 + OBJECT_END, // Size:2
//	UNIT_FIELD_OFFHANDATTACKTIME = 0x79 + OBJECT_END, // Size:2
//	UNIT_FIELD_RANGEDATTACKTIME = 0x7a + OBJECT_END, // Size:1
//	UNIT_FIELD_BOUNDINGRADIUS = 0x7b + OBJECT_END, // Size:1
//	UNIT_FIELD_COMBATREACH = 0x7c + OBJECT_END, // Size:1
//	UNIT_FIELD_DISPLAYID = 0x7d + OBJECT_END, // Size:1
//	UNIT_FIELD_NATIVEDISPLAYID = 0x7e + OBJECT_END, // Size:1
//	UNIT_FIELD_MOUNTDISPLAYID = 0x7f + OBJECT_END, // Size:1
//	UNIT_FIELD_MINDAMAGE = 0x80 + OBJECT_END, // Size:1
//	UNIT_FIELD_MAXDAMAGE = 0x81 + OBJECT_END, // Size:1
//	UNIT_FIELD_MINOFFHANDDAMAGE = 0x82 + OBJECT_END, // Size:1
//	UNIT_FIELD_MAXOFFHANDDAMAGE = 0x83 + OBJECT_END, // Size:1
//	UNIT_FIELD_BYTES_1 = 0x84 + OBJECT_END, // Size:1
//	UNIT_FIELD_PETNUMBER = 0x85 + OBJECT_END, // Size:1
//	UNIT_FIELD_PET_NAME_TIMESTAMP = 0x86 + OBJECT_END, // Size:1
//	UNIT_FIELD_PETEXPERIENCE = 0x87 + OBJECT_END, // Size:1
//	UNIT_FIELD_PETNEXTLEVELEXP = 0x88 + OBJECT_END, // Size:1
//	UNIT_DYNAMIC_FLAGS = 0x89 + OBJECT_END, // Size:1
//	UNIT_CHANNEL_SPELL = 0x8a + OBJECT_END, // Size:1
//	UNIT_MOD_CAST_SPEED = 0x8b + OBJECT_END, // Size:1
//	UNIT_CREATED_BY_SPELL = 0x8c + OBJECT_END, // Size:1
//	UNIT_NPC_FLAGS = 0x8d + OBJECT_END, // Size:1
//	UNIT_NPC_EMOTESTATE = 0x8e + OBJECT_END, // Size:1
//	UNIT_TRAINING_POINTS = 0x8f + OBJECT_END, // Size:1
//	UNIT_FIELD_STAT0 = 0x90 + OBJECT_END, // Size:1
//	UNIT_FIELD_STAT1 = 0x91 + OBJECT_END, // Size:1
//	UNIT_FIELD_STAT2 = 0x92 + OBJECT_END, // Size:1
//	UNIT_FIELD_STAT3 = 0x93 + OBJECT_END, // Size:1
//	UNIT_FIELD_STAT4 = 0x94 + OBJECT_END, // Size:1
//	UNIT_FIELD_RESISTANCES = 0x95 + OBJECT_END, // Size:7
//	UNIT_FIELD_RESISTANCES_01 = 0x96 + OBJECT_END,
//	UNIT_FIELD_RESISTANCES_02 = 0x97 + OBJECT_END,
//	UNIT_FIELD_RESISTANCES_03 = 0x98 + OBJECT_END,
//	UNIT_FIELD_RESISTANCES_04 = 0x99 + OBJECT_END,
//	UNIT_FIELD_RESISTANCES_05 = 0x9a + OBJECT_END,
//	UNIT_FIELD_RESISTANCES_06 = 0x9b + OBJECT_END,
//	UNIT_FIELD_BASE_MANA = 0x9c + OBJECT_END, // Size:1
//	UNIT_FIELD_BASE_HEALTH = 0x9d + OBJECT_END, // Size:1
//	UNIT_FIELD_BYTES_2 = 0x9e + OBJECT_END, // Size:1
//	UNIT_FIELD_ATTACK_POWER = 0x9f + OBJECT_END, // Size:1
//	UNIT_FIELD_ATTACK_POWER_MODS = 0xa0 + OBJECT_END, // Size:1
//	UNIT_FIELD_ATTACK_POWER_MULTIPLIER = 0xa1 + OBJECT_END, // Size:1
//	UNIT_FIELD_RANGED_ATTACK_POWER = 0xa2 + OBJECT_END, // Size:1
//	UNIT_FIELD_RANGED_ATTACK_POWER_MODS = 0xa3 + OBJECT_END, // Size:1
//	UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER = 0xa4 + OBJECT_END, // Size:1
//	UNIT_FIELD_MINRANGEDDAMAGE = 0xa5 + OBJECT_END, // Size:1
//	UNIT_FIELD_MAXRANGEDDAMAGE = 0xa6 + OBJECT_END, // Size:1
//	UNIT_FIELD_POWER_COST_MODIFIER = 0xa7 + OBJECT_END, // Size:7
//	UNIT_FIELD_POWER_COST_MODIFIER_01 = 0xa8 + OBJECT_END,
//	UNIT_FIELD_POWER_COST_MODIFIER_02 = 0xa9 + OBJECT_END,
//	UNIT_FIELD_POWER_COST_MODIFIER_03 = 0xaa + OBJECT_END,
//	UNIT_FIELD_POWER_COST_MODIFIER_04 = 0xab + OBJECT_END,
//	UNIT_FIELD_POWER_COST_MODIFIER_05 = 0xac + OBJECT_END,
//	UNIT_FIELD_POWER_COST_MODIFIER_06 = 0xad + OBJECT_END,
//	UNIT_FIELD_POWER_COST_MULTIPLIER = 0xae + OBJECT_END, // Size:7
//	UNIT_FIELD_POWER_COST_MULTIPLIER_01 = 0xaf + OBJECT_END,
//	UNIT_FIELD_POWER_COST_MULTIPLIER_02 = 0xb0 + OBJECT_END,
//	UNIT_FIELD_POWER_COST_MULTIPLIER_03 = 0xb1 + OBJECT_END,
//	UNIT_FIELD_POWER_COST_MULTIPLIER_04 = 0xb2 + OBJECT_END,
//	UNIT_FIELD_POWER_COST_MULTIPLIER_05 = 0xb3 + OBJECT_END,
//	UNIT_FIELD_POWER_COST_MULTIPLIER_06 = 0xb4 + OBJECT_END,
//	UNIT_FIELD_PADDING = 0xb5 + OBJECT_END,
//	UNIT_END = 0xb6 + OBJECT_END,
//
//	PLAYER_DUEL_ARBITER = 0x00 + UNIT_END, // Size:2
//	PLAYER_FLAGS = 0x02 + UNIT_END, // Size:1
//	PLAYER_GUILDID = 0x03 + UNIT_END, // Size:1
//	PLAYER_GUILDRANK = 0x04 + UNIT_END, // Size:1
//	PLAYER_BYTES = 0x05 + UNIT_END, // Size:1
//	PLAYER_BYTES_2 = 0x06 + UNIT_END, // Size:1
//	PLAYER_BYTES_3 = 0x07 + UNIT_END, // Size:1
//	PLAYER_DUEL_TEAM = 0x08 + UNIT_END, // Size:1
//	PLAYER_GUILD_TIMESTAMP = 0x09 + UNIT_END, // Size:1
//	PLAYER_QUEST_LOG_1_1 = 0x0A + UNIT_END, // count = 20
//	PLAYER_QUEST_LOG_1_2 = 0x0B + UNIT_END,
//	PLAYER_QUEST_LOG_1_3 = 0x0C + UNIT_END,
//	PLAYER_QUEST_LOG_LAST_1 = 0x43 + UNIT_END,
//	PLAYER_QUEST_LOG_LAST_2 = 0x44 + UNIT_END,
//	PLAYER_QUEST_LOG_LAST_3 = 0x45 + UNIT_END,
//	PLAYER_VISIBLE_ITEM_1_CREATOR = 0x46 + UNIT_END, // Size:2, count = 19
//	PLAYER_VISIBLE_ITEM_1_0 = 0x48 + UNIT_END, // Size:8
//	PLAYER_VISIBLE_ITEM_1_PROPERTIES = 0x50 + UNIT_END, // Size:1
//	PLAYER_VISIBLE_ITEM_1_PAD = 0x51 + UNIT_END, // Size:1
//	PLAYER_VISIBLE_ITEM_LAST_CREATOR = 0x11e + UNIT_END,
//	PLAYER_VISIBLE_ITEM_LAST_0 = 0x120 + UNIT_END,
//	PLAYER_VISIBLE_ITEM_LAST_PROPERTIES = 0x128 + UNIT_END,
//	PLAYER_VISIBLE_ITEM_LAST_PAD = 0x129 + UNIT_END,
//	PLAYER_FIELD_INV_SLOT_HEAD = 0x12a + UNIT_END, // Size:46
//	PLAYER_FIELD_PACK_SLOT_1 = 0x158 + UNIT_END, // Size:32
//	PLAYER_FIELD_PACK_SLOT_LAST = 0x176 + UNIT_END,
//	PLAYER_FIELD_BANK_SLOT_1 = 0x178 + UNIT_END, // Size:48
//	PLAYER_FIELD_BANK_SLOT_LAST = 0x1a6 + UNIT_END,
//	PLAYER_FIELD_BANKBAG_SLOT_1 = 0x1a8 + UNIT_END, // Size:12
//	PLAYER_FIELD_BANKBAG_SLOT_LAST = 0xab2 + UNIT_END,
//	PLAYER_FIELD_VENDORBUYBACK_SLOT_1 = 0x1b4 + UNIT_END, // Size:24
//	PLAYER_FIELD_VENDORBUYBACK_SLOT_LAST = 0x1ca + UNIT_END,
//	PLAYER_FIELD_KEYRING_SLOT_1 = 0x1cc + UNIT_END, // Size:64
//	PLAYER_FIELD_KEYRING_SLOT_LAST = 0x20a + UNIT_END,
//	PLAYER_FARSIGHT = 0x20c + UNIT_END, // Size:2
//	PLAYER_FIELD_COMBO_TARGET = 0x20e + UNIT_END, // Size:2
//	PLAYER_XP = 0x210 + UNIT_END, // Size:1
//	PLAYER_NEXT_LEVEL_XP = 0x211 + UNIT_END, // Size:1
//	PLAYER_SKILL_INFO_1_1 = 0x212 + UNIT_END, // Size:384
//	PLAYER_CHARACTER_POINTS1 = 0x392 + UNIT_END, // Size:1
//	PLAYER_CHARACTER_POINTS2 = 0x393 + UNIT_END, // Size:1
//	PLAYER_TRACK_CREATURES = 0x394 + UNIT_END, // Size:1
//	PLAYER_TRACK_RESOURCES = 0x395 + UNIT_END, // Size:1
//	PLAYER_BLOCK_PERCENTAGE = 0x396 + UNIT_END, // Size:1
//	PLAYER_DODGE_PERCENTAGE = 0x397 + UNIT_END, // Size:1
//	PLAYER_PARRY_PERCENTAGE = 0x398 + UNIT_END, // Size:1
//	PLAYER_CRIT_PERCENTAGE = 0x399 + UNIT_END, // Size:1
//	PLAYER_RANGED_CRIT_PERCENTAGE = 0x39a + UNIT_END, // Size:1
//	PLAYER_EXPLORED_ZONES_1 = 0x39b + UNIT_END, // Size:64
//	PLAYER_REST_STATE_EXPERIENCE = 0x3db + UNIT_END, // Size:1
//	PLAYER_FIELD_COINAGE = 0x3dc + UNIT_END, // Size:1
//	PLAYER_FIELD_POSSTAT0 = 0x3DD + UNIT_END, // Size:1
//	PLAYER_FIELD_POSSTAT1 = 0x3DE + UNIT_END, // Size:1
//	PLAYER_FIELD_POSSTAT2 = 0x3DF + UNIT_END, // Size:1
//	PLAYER_FIELD_POSSTAT3 = 0x3E0 + UNIT_END, // Size:1
//	PLAYER_FIELD_POSSTAT4 = 0x3E1 + UNIT_END, // Size:1
//	PLAYER_FIELD_NEGSTAT0 = 0x3E2 + UNIT_END, // Size:1
//	PLAYER_FIELD_NEGSTAT1 = 0x3E3 + UNIT_END, // Size:1
//	PLAYER_FIELD_NEGSTAT2 = 0x3E4 + UNIT_END, // Size:1
//	PLAYER_FIELD_NEGSTAT3 = 0x3E5 + UNIT_END, // Size:1,
//	PLAYER_FIELD_NEGSTAT4 = 0x3E6 + UNIT_END, // Size:1
//	PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE = 0x3E7 + UNIT_END, // Size:7
//	PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE = 0x3EE + UNIT_END, // Size:7
//	PLAYER_FIELD_MOD_DAMAGE_DONE_POS = 0x3F5 + UNIT_END, // Size:7
//	PLAYER_FIELD_MOD_DAMAGE_DONE_NEG = 0x3FC + UNIT_END, // Size:7
//	PLAYER_FIELD_MOD_DAMAGE_DONE_PCT = 0x403 + UNIT_END, // Size:7
//	PLAYER_FIELD_BYTES = 0x40A + UNIT_END, // Size:1
//	PLAYER_AMMO_ID = 0x40B + UNIT_END, // Size:1
//	PLAYER_SELF_RES_SPELL = 0x40C + UNIT_END, // Size:1
//	PLAYER_FIELD_PVP_MEDALS = 0x40D + UNIT_END, // Size:1
//	PLAYER_FIELD_BUYBACK_PRICE_1 = 0x40E + UNIT_END, // count=12
//	PLAYER_FIELD_BUYBACK_PRICE_LAST = 0x419 + UNIT_END,
//	PLAYER_FIELD_BUYBACK_TIMESTAMP_1 = 0x41A + UNIT_END, // count=12
//	PLAYER_FIELD_BUYBACK_TIMESTAMP_LAST = 0x425 + UNIT_END,
//	PLAYER_FIELD_SESSION_KILLS = 0x426 + UNIT_END, // Size:1
//	PLAYER_FIELD_YESTERDAY_KILLS = 0x427 + UNIT_END, // Size:1
//	PLAYER_FIELD_LAST_WEEK_KILLS = 0x428 + UNIT_END, // Size:1
//	PLAYER_FIELD_THIS_WEEK_KILLS = 0x429 + UNIT_END, // Size:1
//	PLAYER_FIELD_THIS_WEEK_CONTRIBUTION = 0x42a + UNIT_END, // Size:1
//	PLAYER_FIELD_LIFETIME_HONORABLE_KILLS = 0x42b + UNIT_END, // Size:1
//	PLAYER_FIELD_LIFETIME_DISHONORABLE_KILLS = 0x42c + UNIT_END, // Size:1
//	PLAYER_FIELD_YESTERDAY_CONTRIBUTION = 0x42d + UNIT_END, // Size:1
//	PLAYER_FIELD_LAST_WEEK_CONTRIBUTION = 0x42e + UNIT_END, // Size:1
//	PLAYER_FIELD_LAST_WEEK_RANK = 0x42f + UNIT_END, // Size:1
//	PLAYER_FIELD_BYTES2 = 0x430 + UNIT_END, // Size:1
//	PLAYER_FIELD_WATCHED_FACTION_INDEX = 0x431 + UNIT_END, // Size:1
//	PLAYER_FIELD_COMBAT_RATING_1 = 0x432 + UNIT_END, // Size:20
//
//	PLAYER_END = 0x446 + UNIT_END
//};
//
//enum EGameObjectFields
//{
//	OBJECT_FIELD_CREATED_BY = OBJECT_END + 0x00,
//	GAMEOBJECT_DISPLAYID = OBJECT_END + 0x02,
//	GAMEOBJECT_FLAGS = OBJECT_END + 0x03,
//	GAMEOBJECT_ROTATION = OBJECT_END + 0x04,
//	GAMEOBJECT_STATE = OBJECT_END + 0x08,
//	GAMEOBJECT_POS_X = OBJECT_END + 0x09,
//	GAMEOBJECT_POS_Y = OBJECT_END + 0x0A,
//	GAMEOBJECT_POS_Z = OBJECT_END + 0x0B,
//	GAMEOBJECT_FACING = OBJECT_END + 0x0C,
//	GAMEOBJECT_DYN_FLAGS = OBJECT_END + 0x0D,
//	GAMEOBJECT_FACTION = OBJECT_END + 0x0E,
//	GAMEOBJECT_TYPE_ID = OBJECT_END + 0x0F,
//	GAMEOBJECT_LEVEL = OBJECT_END + 0x10,
//	GAMEOBJECT_ARTKIT = OBJECT_END + 0x11,
//	GAMEOBJECT_ANIMPROGRESS = OBJECT_END + 0x12,
//	GAMEOBJECT_PADDING = OBJECT_END + 0x13,
//	GAMEOBJECT_END = OBJECT_END + 0x14,
//};
//
//enum EDynamicObjectFields
//{
//	DYNAMICOBJECT_CASTER = OBJECT_END + 0x00,
//	DYNAMICOBJECT_BYTES = OBJECT_END + 0x02,
//	DYNAMICOBJECT_SPELLID = OBJECT_END + 0x03,
//	DYNAMICOBJECT_RADIUS = OBJECT_END + 0x04,
//	DYNAMICOBJECT_POS_X = OBJECT_END + 0x05,
//	DYNAMICOBJECT_POS_Y = OBJECT_END + 0x06,
//	DYNAMICOBJECT_POS_Z = OBJECT_END + 0x07,
//	DYNAMICOBJECT_FACING = OBJECT_END + 0x08,
//	DYNAMICOBJECT_PAD = OBJECT_END + 0x09,
//	DYNAMICOBJECT_END = OBJECT_END + 0x0A,
//};
//
//enum ECorpseFields
//{
//	CORPSE_FIELD_OWNER = OBJECT_END + 0x00,
//	CORPSE_FIELD_FACING = OBJECT_END + 0x02,
//	CORPSE_FIELD_POS_X = OBJECT_END + 0x03,
//	CORPSE_FIELD_POS_Y = OBJECT_END + 0x04,
//	CORPSE_FIELD_POS_Z = OBJECT_END + 0x05,
//	CORPSE_FIELD_DISPLAY_ID = OBJECT_END + 0x06,
//	CORPSE_FIELD_ITEM = OBJECT_END + 0x07, // 19
//	CORPSE_FIELD_BYTES_1 = OBJECT_END + 0x1A,
//	CORPSE_FIELD_BYTES_2 = OBJECT_END + 0x1B,
//	CORPSE_FIELD_GUILD = OBJECT_END + 0x1C,
//	CORPSE_FIELD_FLAGS = OBJECT_END + 0x1D,
//	CORPSE_FIELD_DYNAMIC_FLAGS = OBJECT_END + 0x1E,
//	CORPSE_FIELD_PAD = OBJECT_END + 0x1F,
//	CORPSE_END = OBJECT_END + 0x20,
//};
//
///**
//* [-ZERO] Need recheck values
//* Value masks for UNIT_FIELD_FLAGS (Taken from source)
//* \todo Document all the flags, not just the ones already commented

enum UnitFlags
{
	UNIT_FLAG_NONE = 0x00000000,
	UNIT_FLAG_UNK_0 = 0x00000001,
	UNIT_FLAG_NON_ATTACKABLE = 0x00000002,           ///< not attackable
	UNIT_FLAG_DISABLE_MOVE = 0x00000004,
	UNIT_FLAG_PVP_ATTACKABLE = 0x00000008,           ///< allow apply pvp rules to attackable state in addition to faction dependent state, UNIT_FLAG_UNKNOWN1 in pre-bc mangos
	UNIT_FLAG_RENAME = 0x00000010,           ///< rename creature
	UNIT_FLAG_RESTING = 0x00000020,
	UNIT_FLAG_UNK_6 = 0x00000040,
	UNIT_FLAG_OOC_NOT_ATTACKABLE = 0x00000100,           ///< (OOC Out Of Combat) Can not be attacked when not in combat. Removed if unit for some reason enter combat (flag probably removed for the attacked and it's party/group only) \todo Needs more documentation
	UNIT_FLAG_PASSIVE = 0x00000200,           ///< makes you unable to attack everything. Almost identical to our "civilian"-term. Will ignore it's surroundings and not engage in combat unless "called upon" or engaged by another unit.
	UNIT_FLAG_PVP = 0x00001000,
	UNIT_FLAG_SILENCED = 0x00002000,           ///< silenced, 2.1.1
	UNIT_FLAG_UNK_14 = 0x00004000,           ///< 2.0.8
	UNIT_FLAG_UNK_15 = 0x00008000,           ///< related to jerky movement in water?
	UNIT_FLAG_UNK_16 = 0x00010000,           ///< removes attackable icon
	UNIT_FLAG_PACIFIED = 0x00020000,
	UNIT_FLAG_DISABLE_ROTATE = 0x00040000,
	UNIT_FLAG_IN_COMBAT = 0x00080000,
	UNIT_FLAG_NOT_SELECTABLE = 0x02000000,
	UNIT_FLAG_SKINNABLE = 0x04000000,
	UNIT_FLAG_AURAS_VISIBLE = 0x08000000,           ///< magic detect
	UNIT_FLAG_SHEATHE = 0x40000000,
	// UNIT_FLAG_UNK_31              = 0x80000000           // no affect in 1.12.1

	// [-ZERO] TBC enumerations [?]
	UNIT_FLAG_NOT_ATTACKABLE_1 = 0x00000080,           ///< ?? (UNIT_FLAG_PVP_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1) is NON_PVP_ATTACKABLE
	UNIT_FLAG_LOOTING = 0x00000400,           ///< loot animation
	UNIT_FLAG_PET_IN_COMBAT = 0x00000800,           ///< in combat?, 2.0.8
	UNIT_FLAG_STUNNED = 0x00040000,           ///< stunned, 2.1.1
	UNIT_FLAG_TAXI_FLIGHT = 0x00100000,           ///< disable casting at client side spell not allowed by taxi flight (mounted?), probably used with 0x4 flag
	UNIT_FLAG_DISARMED = 0x00200000,           ///< disable melee spells casting..., "Required melee weapon" added to melee spells tooltip.
	UNIT_FLAG_CONFUSED = 0x00400000,
	UNIT_FLAG_FLEEING = 0x00800000,
	UNIT_FLAG_PLAYER_CONTROLLED = 0x01000000,           ///< used in spell Eyes of the Beast for pet... let attack by controlled creature
														// [-ZERO] UNIT_FLAG_MOUNT                 = 0x08000000,
	UNIT_FLAG_UNK_28 = 0x10000000,
	UNIT_FLAG_UNK_29 = 0x20000000            ///< used in Feign Death spell
};
//
///**
//* Non Player Character flags
//* \todo Properly document this
//*/
//enum NPCFlags
//{
//	UNIT_NPC_FLAG_NONE = 0x00000000,
//	UNIT_NPC_FLAG_GOSSIP = 0x00000001,       ///< 100%
//	UNIT_NPC_FLAG_QUESTGIVER = 0x00000002,       ///< guessed, probably ok
//	UNIT_NPC_FLAG_VENDOR = 0x00000004,       ///< 100%
//	UNIT_NPC_FLAG_FLIGHTMASTER = 0x00000008,       ///< 100%
//	UNIT_NPC_FLAG_TRAINER = 0x00000010,       ///< 100%
//	UNIT_NPC_FLAG_SPIRITHEALER = 0x00000020,       ///< guessed
//	UNIT_NPC_FLAG_SPIRITGUIDE = 0x00000040,       ///< guessed
//	UNIT_NPC_FLAG_INNKEEPER = 0x00000080,       ///< 100%
//	UNIT_NPC_FLAG_BANKER = 0x00000100,       ///< 100%
//	UNIT_NPC_FLAG_PETITIONER = 0x00000200,       ///< 100% 0xC0000 = guild petitions
//	UNIT_NPC_FLAG_TABARDDESIGNER = 0x00000400,       ///< 100%
//	UNIT_NPC_FLAG_BATTLEMASTER = 0x00000800,       ///< 100%
//	UNIT_NPC_FLAG_AUCTIONEER = 0x00001000,       ///< 100%
//	UNIT_NPC_FLAG_STABLEMASTER = 0x00002000,       ///< 100%
//	UNIT_NPC_FLAG_REPAIR = 0x00004000,       ///< 100%
//	UNIT_NPC_FLAG_OUTDOORPVP = 0x20000000        ///< custom flag for outdoor pvp creatures || Custom flag
//};
//
///**
//* These flags denote the different kinds of movement you can do. You can have many at the
//* same time as this is used as a bitmask.
//* \todo [-ZERO] Need check and update used in most movement packets (send and received)
//* \see MovementInfo
//*/


enum MovementFlags : uint32_t
{
	MOVEMENTFLAG_NONE = 0x00000000,
	MOVEMENTFLAG_FORWARD = 0x00000001,
	MOVEMENTFLAG_BACKWARD = 0x00000002,
	MOVEMENTFLAG_STRAFE_LEFT = 0x00000004,
	MOVEMENTFLAG_STRAFE_RIGHT = 0x00000008,
	MOVEMENTFLAG_LEFT = 0x00000010,
	MOVEMENTFLAG_RIGHT = 0x00000020,
	MOVEMENTFLAG_PITCH_UP = 0x00000040,
	MOVEMENTFLAG_PITCH_DOWN = 0x00000080,
	MOVEMENTFLAG_WALKING = 0x00000100,               // Walking
	MOVEMENTFLAG_DISABLE_GRAVITY = 0x00000200,               // Former MOVEMENTFLAG_LEVITATING. This is used when walking is not possible.
	MOVEMENTFLAG_ROOT = 0x00000400,               // Must not be set along with MOVEMENTFLAG_MASK_MOVING
	MOVEMENTFLAG_FALLING = 0x00000800,               // damage dealt on that type of falling
	MOVEMENTFLAG_FALLING_FAR = 0x00001000,
	MOVEMENTFLAG_PENDING_STOP = 0x00002000,
	MOVEMENTFLAG_PENDING_STRAFE_STOP = 0x00004000,
	MOVEMENTFLAG_PENDING_FORWARD = 0x00008000,
	MOVEMENTFLAG_PENDING_BACKWARD = 0x00010000,
	MOVEMENTFLAG_PENDING_STRAFE_LEFT = 0x00020000,
	MOVEMENTFLAG_PENDING_STRAFE_RIGHT = 0x00040000,
	MOVEMENTFLAG_PENDING_ROOT = 0x00080000,
	MOVEMENTFLAG_SWIMMING = 0x00100000,               // appears with fly flag also
	MOVEMENTFLAG_ASCENDING = 0x00200000,               // press "space" when flying
	MOVEMENTFLAG_DESCENDING = 0x00400000,
	MOVEMENTFLAG_CAN_FLY = 0x00800000,               // Appears when unit can fly AND also walk
	MOVEMENTFLAG_FLYING = 0x01000000,               // unit is actually flying. pretty sure this is only used for players. creatures use disable_gravity
	MOVEMENTFLAG_SPLINE_ELEVATION = 0x02000000,               // used for flight paths
	MOVEMENTFLAG_WATERWALKING = 0x04000000,               // prevent unit from falling through water
	MOVEMENTFLAG_FALLING_SLOW = 0x08000000,               // active rogue safe fall spell (passive)
	MOVEMENTFLAG_HOVER = 0x10000000,               // hover, cannot jump
	MOVEMENTFLAG_DISABLE_COLLISION = 0x20000000,

	MOVEMENTFLAG_MASK_MOVING =
	MOVEMENTFLAG_FORWARD | MOVEMENTFLAG_BACKWARD | MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT |
	MOVEMENTFLAG_FALLING | MOVEMENTFLAG_ASCENDING | MOVEMENTFLAG_DESCENDING,

	MOVEMENTFLAG_MASK_TURNING =
	MOVEMENTFLAG_LEFT | MOVEMENTFLAG_RIGHT | MOVEMENTFLAG_PITCH_UP | MOVEMENTFLAG_PITCH_DOWN,

	MOVEMENTFLAG_MASK_MOVING_FLY =
	MOVEMENTFLAG_FLYING | MOVEMENTFLAG_ASCENDING | MOVEMENTFLAG_DESCENDING,

	// Movement flags allowed for creature in CreateObject - we need to keep all other enabled serverside
	// to properly calculate all movement
	MOVEMENTFLAG_MASK_CREATURE_ALLOWED =
	MOVEMENTFLAG_FORWARD | MOVEMENTFLAG_DISABLE_GRAVITY | MOVEMENTFLAG_ROOT | MOVEMENTFLAG_SWIMMING |
	MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_WATERWALKING | MOVEMENTFLAG_FALLING_SLOW | MOVEMENTFLAG_HOVER | MOVEMENTFLAG_DISABLE_COLLISION,

	// @todo if needed: add more flags to this masks that are exclusive to players
	MOVEMENTFLAG_MASK_PLAYER_ONLY =
	MOVEMENTFLAG_FLYING,

	// Movement flags that have change status opcodes associated for players
	MOVEMENTFLAG_MASK_HAS_PLAYER_STATUS_OPCODE = MOVEMENTFLAG_DISABLE_GRAVITY | MOVEMENTFLAG_ROOT |
	MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_WATERWALKING | MOVEMENTFLAG_FALLING_SLOW | MOVEMENTFLAG_HOVER | MOVEMENTFLAG_DISABLE_COLLISION
};

//// flags that use in movement check for example at spell casting
//MovementFlags const movementFlagsMask = MovementFlags(
//	MOVEFLAG_FORWARD | MOVEFLAG_BACKWARD | MOVEFLAG_STRAFE_LEFT | MOVEFLAG_STRAFE_RIGHT |
//	MOVEFLAG_PITCH_UP | MOVEFLAG_PITCH_DOWN | MOVEFLAG_ROOT |
//	MOVEFLAG_FALLING | MOVEFLAG_FALLINGFAR | MOVEFLAG_SPLINE_ELEVATION
//);
//
//MovementFlags const movementOrTurningFlagsMask = MovementFlags(
//	movementFlagsMask | MOVEFLAG_TURN_LEFT | MOVEFLAG_TURN_RIGHT
//);

//// used in CallForAllControlledUnits/CheckAllControlledUnits
//enum ControlledUnitMask
//{
//	CONTROLLED_PET = 0x01,
//	CONTROLLED_MINIPET = 0x02,
//	CONTROLLED_GUARDIANS = 0x04,                            // including PROTECTOR_PET
//	CONTROLLED_CHARM = 0x08,
//	CONTROLLED_TOTEMS = 0x10,
//};
//
//// for clearing special attacks
//#define REACTIVE_TIMER_START 4000
//
//enum ReactiveType
//{
//	REACTIVE_DEFENSE = 1,
//	REACTIVE_HUNTER_PARRY = 2,
//	// REACTIVE_CRIT         = 3,
//	// REACTIVE_HUNTER_CRIT  = 4,
//	REACTIVE_OVERPOWER = 5
//};
//
//typedef struct
//{
//	int Id;
//	int School;
//	int Category;
//	int CastUI;
//	int Dispel;
//	int Mechanic;
//	int Attributes;
//	int AttributesEx;
//	int AttributesEx2;
//	int AttributesEx3;
//	int AttributesEx4;
//	int Stances;
//	int StancesNot;
//	int Targets;
//	int TargetCreatureType;
//	int RequiresSpellFocus;
//	int CasterAuraState;
//	int TargetAuraState;
//	int CastingTimeIndex;
//	int RecoveryTime;
//	int CategoryRecoveryTime;
//	int InterruptFlags;
//	int AuraInterruptFlags;
//	int ChannelInterruptFlags;
//	int procFlags;
//	int procChance;
//	int procCharges;
//	int maxLevel;
//	int baseLevel;
//	int spellLevel;
//	int DurationIndex;
//	int powerType;
//	int manaCost;
//	int manaCostPerlevel;
//	int manaPerSecond;
//	int manaPerSecondPerLevel;
//	int rangeIndex;
//	float speed;
//	int modalNextSpell;
//	int StackAmount;
//	int Totem[2];
//	int Reagent[8];
//	int ReagentCount[8];
//	int EquippedItemClass;
//	int EquippedItemSubClassMask;
//	int EquippedItemInventoryTypeMask;
//	int Effect[3];
//	int EffectDieSides[3];
//	int EffectBaceDice[3];
//	float EffectDicePerLevel[3];
//	float EffectRealPointsPerLevel[3];
//	int EffectBasePoints[3];
//	int EffectMechanic[3];
//	int EffectImplicitTargetA[3];
//	int EffectImplicitTargetB[3];
//	int EffectRadiusIndex[3];
//	int EffectApplyAuraName[3];
//	int EffectAmplitude[3];
//	float EffectMultipleValue[3];
//	int EffectChainTarget[3];
//	int EffectItemType[3];
//	int EffectMiscValue[3];
//	int EffectTriggerSpell[3];
//	float EffectPointsPerComboPoint[3];
//	int SpellVisual;
//	int SpellVisual2;
//	int SpellIconID;
//	int activeIconID;
//	int spellPriority;
//	char* SpellName[8];
//	int SpellNameFlag;
//	char* Rank[8];
//	int RankFlags;
//	char* Description[8];
//	int DescriptionFlags;
//	char* ToolTip[8];
//	int ToolTipFlags;
//	int ManaCostPercentage;
//	int StartRecoveryCategory;
//	int StartRecoveryTime;
//	int MaxTargetLevel;
//	int SpellFamilyName;
//	__int64 SpellFamilyFlags;
//	int MaxAffectedTargets;
//	int DmgClass;
//	int PreventionType;
//	int StanceBarOrder;
//	float DmgMultiplier[3];
//	int MinFactionId;
//	int MinReputation;
//	int RequiredAuraVision;
//}SpellRec;
//
//struct _Damage
//{
//	float   DamageMin;
//	float   DamageMax;
//	uint32  DamageType;                                     // id from Resistances.dbc
//};
//
//struct _ItemStat
//{
//	uint32  ItemStatType;
//	int32   ItemStatValue;
//};
//struct _Spell
//{
//	uint32 SpellId;                                         // id from Spell.dbc
//	uint32 SpellTrigger;
//	int32  SpellCharges;
//	float  SpellPPMRate;
//	int32  SpellCooldown;
//	uint32 SpellCategory;                                   // id from SpellCategory.dbc
//	int32  SpellCategoryCooldown;
//};
//
//typedef struct
//{
//	uint32 ItemId;
//	uint32 Class;                                           // id from ItemClass.dbc
//	uint32 SubClass;                                        // id from ItemSubClass.dbc
//	char* Name1;
//	uint32 DisplayInfoID;                                   // id from ItemDisplayInfo.dbc
//	uint32 Quality;
//	uint32 Flags;
//	uint32 BuyCount;
//	uint32 BuyPrice;
//	uint32 SellPrice;
//	uint32 InventoryType;
//	uint32 AllowableClass;
//	uint32 AllowableRace;
//	uint32 ItemLevel;
//	uint32 RequiredLevel;
//	uint32 RequiredSkill;                                   // id from SkillLine.dbc
//	uint32 RequiredSkillRank;
//	uint32 RequiredSpell;                                   // id from Spell.dbc
//	uint32 RequiredHonorRank;
//	uint32 RequiredCityRank;
//	uint32 RequiredReputationFaction;                       // id from Faction.dbc
//	uint32 RequiredReputationRank;
//	uint32 MaxCount;
//	uint32 Stackable;
//	uint32 ContainerSlots;
//	_ItemStat ItemStat[10];
//	_Damage Damage[5];
//	uint32 Armor;
//	uint32 HolyRes;
//	uint32 FireRes;
//	uint32 NatureRes;
//	uint32 FrostRes;
//	uint32 ShadowRes;
//	uint32 ArcaneRes;
//	uint32 Delay;
//	uint32 AmmoType;
//	float  RangedModRange;
//	_Spell Spells[5];
//	uint32 Bonding;                              ///< See \ref ItemBondingType
//	char* Description;
//	uint32 PageText;
//	uint32 LanguageID;
//	uint32 PageMaterial;
//	uint32 StartQuest;                                      // id from QuestCache.wdb
//	uint32 LockID;
//	uint32 Material;                                        // id from Material.dbc
//	uint32 Sheath;
//	uint32 RandomProperty;                                  // id from ItemRandomProperties.dbc
//	uint32 Block;
//	uint32 ItemSet;                                         // id from ItemSet.dbc
//	uint32 MaxDurability;
//	uint32 Area;                                            // id from AreaTable.dbc
//	uint32 Map;                                             // id from Map.dbc
//	uint32 BagFamily;                                       // bit mask (1 << id from ItemBagFamily.dbc)
//	uint32 DisenchantID;
//	uint32 FoodType;
//	uint32 MinMoneyLoot;
//	uint32 MaxMoneyLoot;
//	uint32 Duration;
//	uint32 ExtraFlags;                                      // see ItemExtraFlags
//}ItemPrototype;
//
