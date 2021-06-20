#pragma once
#include "stdafx.h"
#include "WObject.h"
#include "GameMethods.h"
#include "LuaBase.h"
#include "Constants.h"



class LuaScript
{
public:

    static WObject* ActivePlayer;
    inline static std::vector<WObject*> Objects{};

    static bool InGame();

    // helpers
    static unsigned int EnumVisibleObjCb(int64_t, int64_t);
    static void RegisterHandler(string, GameMethods::LuaCallback);
    static void SetHardwareEvent();
    static long getCurrentTime();
    static void SetPlayer();
    static GameMethods::LuaCallback WriteCallback(GameMethods::LuaCallback);

    static void GetObjectGuid(int64_t L);

    // scripts
    //static int ExecuteAfterMS(int64_t);
    //static int ExecuteEveryMS(int64_t);
    //static int Fish(int64_t);
    //static int GetPlayerGuid(int64_t);
    //static int GetPlayerPosition(int64_t);
    //static int IterateObjects(int64_t);
    //static int TestParam(int64_t);
    //static void chat(std::string message);

    static void ReInitObjMgr();
    static bool once;

 
   
};

struct Rect
{
    unsigned width;
    unsigned heigth;
};


