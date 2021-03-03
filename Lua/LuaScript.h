#pragma once
#include "stdafx.h"
#include "WObject.h"
#include "GameMethods.h"
#include "LuaBase.h"


using namespace std;

class Memory
{
public:
    static inline uintptr_t AddToBase(uintptr_t offset) { return reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)) + offset; }
};


struct UnitInfo
{
    WObject* Entity;
 //   int TypeID;
    
    UnitInfo(WObject* Entity)/*, int TypeID)*/
    {
        this->Entity = Entity;
        //this->TypeID = TypeID;
    }
};

class LuaScript
{
    inline static PVOID VehHandler = nullptr;
    static std::vector<uintptr_t> players;
public:
    static WObject* WMain;
    static WObject* Player;
    static uintptr_t EntityList; 
    static WObject* Object;
    static WObject* Unit;
//    static WActivePlayer* ActivePlayer;
    static WObject* ActivePlayer;
    static WObject* GameObject;
    static WObject* DynamicObject;
    static WObject* Corpse;
    static WCorpse* Corpseob;
    static CameraMgr* GCamera;
  
    static bool InGame();

    // helpers
    static unsigned int EnumVisibleObjCb(int64_t, int64_t);
    static void RegisterHandler(string, GameMethods::LuaCallback);
    static void SetHardwareEvent();
    static void SetPlayer();
    static GameMethods::LuaCallback WriteCallback(GameMethods::LuaCallback);

    // scripts
    static int ClickToMove(int64_t);
    static int ExecuteAfterMS(int64_t);
    static int ExecuteEveryMS(int64_t);
    static int Fish(int64_t);
    static int GetPlayerGuid(int64_t);
    static int GetPlayerPosition(int64_t);
    static int IterateObjects(int64_t);
    static int TestParam(int64_t);
    static int GoToCorpse(int64_t);
    static int fakeTeleport(int64_t);
    static void chat(std::string message);
    //static void WriteCanPerformAction();
    //static void Load(const char* script);
    //static void Register();
    //static int LuaCall(int64_t L);
    static void ReInitObjMgr(bool Yes);

    static int64_t Unlock(int64_t l);


    static void Register();
    static void Init();
    static LONG NTAPI VectoredHandler(EXCEPTION_POINTERS* ExceptionInfo);

};

struct Rect
{
    unsigned width;
    unsigned heigth;
};
