#pragma once
#include "stdafx.h"
#include "WObject.h"
#include "GameMethods.h"
#include "Constants.h"

class WoWObjectManager
{
public:
    static bool InGame();
    // helpers
    static unsigned int EnumVisibleObjCb(int64_t, int64_t);
    static void SetHardwareEvent();
    static void LoopObjectManager();
    static void CycleObjects(bool Refresh);
};

