#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string>
#include <iostream>

using namespace std;

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

    /// @todo if needed: add more flags to this masks that are exclusive to players
    MOVEMENTFLAG_MASK_PLAYER_ONLY =
    MOVEMENTFLAG_FLYING,

    /// Movement flags that have change status opcodes associated for players
    MOVEMENTFLAG_MASK_HAS_PLAYER_STATUS_OPCODE = MOVEMENTFLAG_DISABLE_GRAVITY | MOVEMENTFLAG_ROOT |
    MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_WATERWALKING | MOVEMENTFLAG_FALLING_SLOW | MOVEMENTFLAG_HOVER | MOVEMENTFLAG_DISABLE_COLLISION
};

enum CGGameUI_isinworldID : uint32_t
{
    CGGameUI_isinworld_NotInitialized = 0x0000000,
    CGGameUI_isinworld_LoadingScreen1 = 0x1000003,
    CGGameUI_isinworld_LoadingScreen2 = 0x1000002,
    CGGameUI_isinworld_Yes = 0x1010004
};

enum TypeId : uint8_t
{
    CGObject = 0,
    CGItem = 1,
    CGContainer = 2,
    CGAzeriteEmpoweredItem = 3,
    CGAzeriteItem = 4,
    CGUnit = 5,
    CGPlayer = 6,
    CGActivePlayer = 7,
    CGGameObject = 8,
    CGDynamicObject = 9,
    CGCorpse = 10,
    CGAreaTrigger = 11,
    CGSceneObject = 12,
    CGConversation = 13
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
    Gnome,
    Troll,
    Goblin,
    BloodElf,
    Draenei,
    FelOrc,
    Naga,
    Broken,
    Skeleton = 15,
};

struct WGuid
{
    uint64_t High;
    uint64_t Low;

    WGuid() { High = 0; Low = 0; }

    WGuid(const uintptr_t base)
    {
        High = *reinterpret_cast<uint64_t*>(base);
        Low = *reinterpret_cast<uint64_t*>(base + 0x8);
    }
};

const float PI = 3.14159265358979323846f;
template<class T>
struct Point2D
{
    T X;
    T Y;
    Point2D() :X(0), Y(0) {}
    Point2D(T x, T y) :X(x), Y(y) {}
    bool operator==(const Point2D& right)
    {
        return (this->X == right.X && this->Y == right.Y);
    }
    bool operator!=(const Point2D& right)
    {
        return (this->X != right.X || this->Y != right.Y);
    }
    Point2D operator -(const Point2D& right)
    {
        return Point2D(this->X - right.X, this->Y - right.Y);
    }
    Point2D operator +(const Point2D& right)
    {
        return Point2D(this->X + right.X, this->Y + right.Y);
    }
    Point2D operator -=(const Point2D& right)
    {
        return Point2D(this->X - right.X, this->Y - right.Y);
    }
    Point2D operator +=(const Point2D& right)
    {
        return Point2D(this->X + right.X, this->Y + right.Y);
    }

};
