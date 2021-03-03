#include "stdafx.h"
#include "LuaScript.h"
#include <inttypes.h>
#include <stdio.h>
#include <iostream>
#include <type_traits>

#include "Renderer.h"

#include "Settings/Settings.h"

#define ADDON_PATH R"(C:\Program Files (x86)\World of Warcraft\_classic_\Interface\AddOns\)"
constexpr auto ADDON_FILE = "Ding.lua";


//objmgr inits
WObject* LuaScript::Object = nullptr;
WObject* LuaScript::Unit = nullptr;
WObject* LuaScript::Player = nullptr;
WObject* LuaScript::ActivePlayer = nullptr;
//WActivePlayer* LuaScript::ActivePlayer = nullptr;
WObject* LuaScript::GameObject = nullptr;
WObject* LuaScript::DynamicObject = nullptr;
WCorpse* LuaScript::Corpseob = nullptr;
WObject* LuaScript::Corpse = nullptr;
//Camera init
CameraMgr* LuaScript::GCamera = nullptr;

std::vector<UnitInfo> Settings::UnitHelper::UnitInfos; 



WObject* LuaScript::WMain;

bool InitCamera = false;

std::vector<uintptr_t> LuaScript::players;

bool Initobj;

void LuaScript::ReInitObjMgr(bool Yes)
{
	if (!Yes)
		return;

	Settings::UnitHelper::UnitInfos.clear();
	LuaBase::Input("iterObjects(1)", 0);
	LuaBase::PushLua();
	LuaBase::Execute();

	Yes = false;
}

bool LuaScript::InGame()
{
	return *reinterpret_cast<int8_t*>(Offsets::Base + Offsets::InGame) != 0 ? true : false;
}

unsigned int LuaScript::EnumVisibleObjCb(int64_t objectPtr, int64_t filter)
{

	if (!InitCamera)
	{
		//Camera
		uintptr_t Camera = *reinterpret_cast<uintptr_t*>(Offsets::Base + Offsets::CameraMgr);
		auto* Camerasec = reinterpret_cast<CameraMgr*>(Camera);
		GCamera = Camerasec;

		std::cout << "[+] Camera addr:" << std::hex << Camerasec << std::endl;
		InitCamera = true;
	}

	if (objectPtr)
	{
		WObject* object = reinterpret_cast<WObject*>(objectPtr);
		uintptr_t EntityList = *reinterpret_cast<TypeId*>(object->Ptr() + Offsets::Type);



		UnitInfo CObject = UnitInfo(object);
		Settings::UnitHelper::UnitInfos.push_back(CObject);

		switch (EntityList)
		{
		case CGObject:
			if (!Object)
				Object = object;
			std::cout << "[+] Object addr:" << std::hex << Object << std::endl;
			break;
		case CGUnit:
			std::cout << "[+] Unit addr:" << std::hex << object << std::endl;
			if (!Unit)
				Unit = object;
			break;
		case CGPlayer:
			std::cout << "[+] Player addr:" << std::hex << object << std::endl;
			if (!Player)
				Player = object;	
			break;
		case CGActivePlayer:
			if (!ActivePlayer)
				ActivePlayer = object;
			//	ActivePlayer = reinterpret_cast<WActivePlayer*>(object->Ptr());
			std::cout << "[+] ActivePlayer addr:" << std::hex << ActivePlayer << std::endl;		
			break;
		case CGGameObject:		
			if (!GameObject)
			GameObject = object;
			std::cout << "[+] GameObject addr:" << std::hex << GameObject << std::endl;
			break;
		case CGDynamicObject:
			if (!DynamicObject)
				DynamicObject = object;
			std::cout << "[+] CGDynamicObject addr:" << std::hex << DynamicObject << std::endl;
			break;
		case CGCorpse:
			if (!Corpse)
				Corpse = object;
	//			Corpseob = reinterpret_cast<WCorpse*>(object->Ptr());
			std::cout << "[+] Corpse addr:" << std::hex << Corpse << std::endl;		
			break;
		default:
			return 1;
		}
		return 1;
	}
	return 0;
}


void LuaScript::RegisterHandler(string commandName, GameMethods::LuaCallback callback)
{
	GameMethods::Register(commandName.c_str(), LuaScript::WriteCallback(callback));
}

void LuaScript::SetHardwareEvent()
{
	static uintptr_t hardwareEventPtr = Offsets::Base + Offsets::HardwareEventPtr;

	LARGE_INTEGER frequency;
	LARGE_INTEGER perfCount;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&perfCount);

	const long currentTime = (perfCount.QuadPart * 1000) / frequency.QuadPart;
	*reinterpret_cast<uintptr_t*>(hardwareEventPtr) = currentTime;
}

void LuaScript::SetPlayer()
{
	if (Player)
		return;

	LuaBase::Input("iterObjects(0)", 0);
}

GameMethods::LuaCallback LuaScript::WriteCallback(GameMethods::LuaCallback callback)
{
	static auto runOnce = true;

	if (!runOnce)
		return callback;

	runOnce = false;

	uintptr_t invalidPtrCheckMax = Offsets::Base + Offsets::InvalidPtrCheckMax;
	uintptr_t invalidPtrCheckMin = Offsets::Base + Offsets::InvalidPtrCheckMin;
	*reinterpret_cast<uintptr_t*>(invalidPtrCheckMax) = uintptr_t(callback) + 0x1000;
	*reinterpret_cast<uintptr_t*>(invalidPtrCheckMin) = 2;

	return callback;
}
//
//void LuaScript::WriteCanPerformAction()
//{
//	*reinterpret_cast<uint64_t*>(Offsets::Base + Offsets::CanPerformAction) = 0;
//}
//
//
//void LuaScript::Load(const char* script)
//{
//	WriteCanPerformAction();
//
//	char szPath[1024];
//	strcpy_s(szPath, ADDON_PATH);
//	strcat_s(szPath, script);
//
//	auto luaState = *reinterpret_cast <uint64_t*>(Offsets::Base + Offsets::LuaState);
//	GameMethods::LoadFile(luaState, (int64_t)szPath);
//	GameMethods::PCall(luaState, 0, 0, 0);
//}
//
//void LuaScript::Register()
//{
//	GameMethods::Register("Cpp", LuaCall);
//
//	Load(ADDON_FILE);
//}
//
//enum CALL_NUM
//{
//	GGetPosition = 1,
//	GClickToMove = 2,
//	GLoadScript = 3,
//	GClose = 4,
//	GReload = 5,
//};
//
//bool SafeToExit = false;
//int LuaScript::LuaCall(int64_t L)
//{
//	Vector3 position = Vector3(0, 0, 0);;
//	Vector3 destination = Vector3(0, 0, 0);
//
//	uintptr_t* szStr = nullptr;
//
//	switch (GameMethods::ToInteger(L, 1))
//	{
//	case GGetPosition:
//		position = LuaScript::ActivePlayerOb->GetUnitPosition();
//		GameMethods::PushNumber(L, position.x);
//		GameMethods::PushNumber(L, position.y);
//		GameMethods::PushNumber(L, position.z);
//		return 3;
//		break;
//	case GClickToMove:
//		destination = Vector3(GameMethods::ToNumber(L, 2), GameMethods::ToNumber(L, 3), GameMethods::ToNumber(L, 4));
//		GameMethods::ClickToMove(LuaScript::ActivePlayerOb->Ptr(), destination);
//		SetHardwareEvent();
//		return 1;
//		break;
//	case GLoadScript:
//		Load(GameMethods::ToLString(L, 2, szStr).c_str());
//		break;
//	case GClose:
//		SafeToExit = true;
//		break;
//	case GReload:
//		std::thread t([]()
//			{
//				while (!InGame())
//				{
//					std::this_thread::yield();
//				}
//				Sleep(1000);
//				Register();
//			});
//		t.detach();
//		break;
//	}
//}
//


int LuaScript::ClickToMove(int64_t luaState)
{
	if (!Player)
		return 1;

	int x = GameMethods::ToNumber(luaState, 1);
	int y = GameMethods::ToNumber(luaState, 2);
	int z = GameMethods::ToNumber(luaState, 3);

	Vector3 position = Vector3(x, y, z);

	GameMethods::ClickToMove(Player->Ptr(), position);

	SetHardwareEvent();

	return 1;
}

int LuaScript::ExecuteAfterMS(int64_t luaState)
{
	auto delay = GameMethods::ToNumber(luaState, 1);
	auto function = GameMethods::ToLString(luaState, 2, nullptr) + "()";

	if (delay <= 0)
		return 1;

	LuaBase::Input(function, delay);

	return 1;
}

int LuaScript::ExecuteEveryMS(int64_t luaState)
{
	auto sleepTime = GameMethods::ToNumber(luaState, 1);
	auto function = GameMethods::ToLString(luaState, 2, nullptr);

	string functionRepeater = "function " + function + "Repeater() " + function + "() after(" + to_string(sleepTime) + ", '" + function + "Repeater') end " + function + "Repeater()";

	LuaBase::Input(functionRepeater, 0);

	return 1;
}

int LuaScript::Fish(int64_t luaState)
{
	LuaBase::Input("iterObjects(1)", 0);

	return 1;
}

int LuaScript::IterateObjects(int64_t luaState)
{
	if (!GameMethods::ObjMgrIsValid(0))
		return 1;

	auto param = GameMethods::ToNumber(luaState, 1);

	GameMethods::EnumVisibleObjects(EnumVisibleObjCb, param);

	return 1;
}

int LuaScript::GetPlayerGuid(int64_t luaState)
{
	SetPlayer();

	GameMethods::PushGuid(luaState, reinterpret_cast<uintptr_t>(Player->GetGuid()));

	return 1;
}

int LuaScript::GetPlayerPosition(int64_t luaState)
{
	SetPlayer();

	int x = GameMethods::PushNumber(luaState, ActivePlayer->GetUnitPosition().x);
	int y = GameMethods::PushNumber(luaState, ActivePlayer->GetUnitPosition().y);
	int z = GameMethods::PushNumber(luaState, ActivePlayer->GetUnitPosition().z);

	return 3;
}

int LuaScript::TestParam(int64_t luaState)
{
	auto param = GameMethods::ToNumber(luaState, 1);
	GameMethods::PushNumber(luaState, param);

	return 1;
}

int LuaScript::GoToCorpse(int64_t luaState)
{
	if (!LuaScript::ActivePlayer)
		return 1;

	float corpseXPos = *reinterpret_cast<float*>(Offsets::Base + 0x21F67B0);
	float corpseYPos = *reinterpret_cast<float*>(Offsets::Base + 0x21F67B4);
	float corpseZPos = *reinterpret_cast<float*>(Offsets::Base + 0x21F67B8);

	printf("x %f y %f z %f", corpseXPos, corpseYPos, corpseZPos);

	if (corpseXPos != 0 && corpseYPos != 0 && corpseZPos != 0)
	{
		LuaScript::ActivePlayer->GetUnitPositionModify.y = corpseXPos;
		LuaScript::ActivePlayer->GetUnitPositionModify.y = corpseYPos;
		LuaScript::ActivePlayer->GetUnitPositionModify.z = corpseZPos;
	}
	else
	{
		LuaScript::chat("Corpse not found!");
	}
	return 1;
}


int LuaScript::fakeTeleport(int64_t luastate)
{
	if (!Player)
		return 1;

	if (Settings::Hacks::Movement::TeleportBack)
	{
		LuaScript::ActivePlayer->GetUnitPositionModify = Settings::Hacks::Movement::PrevPos; // For now 
		Settings::Hacks::Movement::TeleportBack = false;
		return 1;
	}
	else
	{
		Settings::Hacks::Movement::PrevPos = LuaScript::ActivePlayer->GetUnitPositionModify;
	}

	LuaScript::ActivePlayer->GetUnitPositionModify = Settings::Hacks::Movement::NextPos;  // For now
	
	return 1;
}


void LuaScript::chat(std::string message)
{
	if (!ActivePlayer)
		return;

	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(buffer, 80, "[%H:%M:%S] ", &timeinfo);
	std::string CName = "[XHOOK] ";
	std::string taggedMessage = buffer + CName + message;
	std::replace(taggedMessage.begin(), taggedMessage.end(), '\'', '_');
	std::string to_print = "DEFAULT_CHAT_FRAME:AddMessage('" + taggedMessage + "')";
	GameMethods::Execute(to_print.c_str());
}

//the first param will be sent by wow when u call this function and its the lua_state pointer aka stack basically
int64_t LuaScript::Unlock(int64_t l) //ok so ur return value here is how many returns ur lua function will return we aernt returning anything so will be 0
{
	//so to run protected function from addon we need to call execute in our dll so the first thing we need to do is get the number of arguments on the lua stack when this is called

	//num args sent to this command we expect 1 and we expect it to be a string 
	auto numArgs = GameMethods::LuaGetTop(l);

	//if we have 1 arg passed to function like we expect
	if (numArgs == 1)
	{
		//check if that arg is a string like we expect
		//if we have 1 arg then its pos on stack is 1
		if (GameMethods::LuaIsString(l, 1))
		{
			const auto currentState = *reinterpret_cast<unsigned __int16*>(Offsets::Base + Offsets::InGame);
			if ((currentState >> 4) & 1)
			{
				//if we are here the 1 arg on the stack is a string now we need to convert it to a string type for lua > c++
				auto s = GameMethods::ToLString(l, 1, nullptr);
				GameMethods::Execute(s);
			}
			return 0;
		}
		GameMethods::LuaError(l, "Invalid Argument: string expected.");
	}
	GameMethods::LuaError(l, "Invalid # of Arguments: 1 expected.");
	return 0;
}
