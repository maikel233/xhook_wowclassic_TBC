#include "stdafx.h"
#include "LuaScript.h"
#include <inttypes.h>
#include <stdio.h>
#include <iostream>
#include <type_traits>

#include "Renderer.h"

#include "Settings/Settings.h"

#include <algorithm>

#include "Hacks.h"
#include "bot/GrindBot.h"
//#define ADDON_PATH R"(C:\Program Files (x86)\World of Warcraft\_classic_\Interface\AddOns\)"
//constexpr auto ADDON_FILE = "Ding.lua";

WObject* object;

WObject* LuaScript::ActivePlayer = nullptr;



bool testf = false;
int i;
//
//bool hasWorld()
//{
//	std::byte buffer;
//
//	uintptr_t CGWorldFrame__RenderWorld = Offsets::Base + 0x101CA00;
//
//	if (CGWorldFrame__RenderWorld);
//		return true;
//
//	if (CGWorldFrame__RenderWorld == 0xC3)
//		return true;
//
//	return false;
//}

long LuaScript::getCurrentTime() {
	LARGE_INTEGER frequency, counter;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&counter);
	long currentTime = (counter.QuadPart * 1000) / frequency.QuadPart;
	return currentTime;
}


void LuaScript::ReInitObjMgr()
{
	__try
	{	
		if (Settings::bot::Refresh)
		{
			Objects.clear();
			if (Objects.empty())
			{
				GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, LuaScript::EnumVisibleObjCb, (int)TypeId::CGUnit);
				GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, LuaScript::EnumVisibleObjCb, (int)TypeId::CGGameObject);
				Settings::bot::Refresh = false;
				printf("[+] Vector is now empty\n");
			}
		}

		if (Settings::bot::Grinding::Enabled)//Settings::bot::Leveling::Enabled)
		{
			WoW::GrindBot::Fight();
		}

		if (Settings::bot::fishing::Enabled)
		{		
			WoW::FishBot::Fish();
			return;
		}


		GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, LuaScript::EnumVisibleObjCb, (int)TypeId::CGUnit);
		GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, LuaScript::EnumVisibleObjCb, (int)TypeId::CGCorpse);
		//GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, LuaScript::EnumVisibleObjCb, (int)TypeId::CGDynamicObject);
		GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, LuaScript::EnumVisibleObjCb, (int)TypeId::CGGameObject);
		//GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, LuaScript::EnumVisibleObjCb, (int)TypeId::CGItem);
		GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, LuaScript::EnumVisibleObjCb, (int)TypeId::CGPlayer);
		GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, LuaScript::EnumVisibleObjCb, (int)TypeId::CGActivePlayer);

		
	//	Probably smart to clear the Vector once in a time.
	//	i++;
	//	if (i > 10000)
	//	{	
	//		i = 0;
	//		Objects.clear();	
	//	}
	}
	__except (Utils::filterException(GetExceptionCode(), GetExceptionInformation())) {
		printf("[!] OBJMGR EXCEPTION!\n");
		Objects.clear();
	}
}

bool LuaScript::InGame()
{
	return *reinterpret_cast<int8_t*>(Offsets::InGame) != 0 ? true : false;
}

unsigned int LuaScript::EnumVisibleObjCb(int64_t objectPtr, int64_t filter)
{
	auto typeFilter = (TypeId)filter;

	if (objectPtr)
	{
		auto object = reinterpret_cast<WObject*>(objectPtr);

		switch (object->GetType())
		{
		case TypeId::CGObject:
			if (typeFilter != TypeId::CGObject)
				break;
			if (!(count(Objects.begin(), Objects.end(), object)))
				Objects.push_back(object);
			//	std::cout << "[+] Object addr:" << std::hex << Object << std::endl;
			break;
		case TypeId::CGUnit:
			if (typeFilter != TypeId::CGUnit)
				break;
			if (!(count(Objects.begin(), Objects.end(), object)))
				Objects.push_back(object);
			break;
		case TypeId::CGPlayer:
			if (typeFilter != TypeId::CGPlayer)
				break;
			if (!(count(Objects.begin(), Objects.end(), object)))
				Objects.push_back(object);
			//	std::cout << "[+] Player addr:" << std::hex << object << std::endl;
			break;
		case TypeId::CGActivePlayer:
			if (typeFilter != TypeId::CGActivePlayer)
				break;
			if (!ActivePlayer)
			{
				ActivePlayer = object;
				std::cout << "[+] ActivePlayer addr:" << std::hex << ActivePlayer << std::endl;
			}
			break;
		case TypeId::CGGameObject:
			if (typeFilter != TypeId::CGGameObject)
				break;
			if (!(count(Objects.begin(), Objects.end(), object)))
				Objects.push_back(object);
			//std::cout << "[+] GameObject addr:" << std::hex << GameObject << std::endl;
			break;
		case TypeId::CGDynamicObject:
			if (typeFilter != TypeId::CGDynamicObject)
				break;

			if (!(count(Objects.begin(), Objects.end(), object)))
				Objects.push_back(object);
			//std::cout << "[+] CGDynamicObject addr:" << std::hex << DynamicObject << std::endl;
			break;
		case TypeId::CGCorpse:
			if (typeFilter != TypeId::CGCorpse)
				break;
			if (!(count(Objects.begin(), Objects.end(), object)))
				Objects.push_back(object);
			//std::cout << "[+] Corpse addr:" << std::hex << Corpse << std::endl;		
			break;
		case TypeId::CGContainer:
			break;
			//	printf("%s", object->GetObjectName());
		default:
			return 1;

		}
		return 1;
	}
	return 0; // Failure point
}

//void LuaScript::GetObjectGuid(int64_t L)
//{
//	auto objectName = GameMethods::Invoke<char*>(Offsets::lua_tolstring, L, 2, nullptr);
//
//	Objects.clear();
//	GameMethods::Invoke<char>(Offsets::EnumVisibleObjectsPtr, GameInterface::EnumVisibleObjectsCb, (int)TypeId::Creature);
//	GameMethods::Invoke<char>(Offsets::EnumVisibleObjectsPtr, GameInterface::EnumVisibleObjectsCb, (int)TypeId::Corpse);
//	GameMethods::Invoke<char>(Offsets::EnumVisibleObjectsPtr, GameInterface::EnumVisibleObjectsCb, (int)TypeId::DynamicObject);
//	GameMethods::Invoke<char>(Offsets::EnumVisibleObjectsPtr, GameInterface::EnumVisibleObjectsCb, (int)TypeId::GameObject);
//	GameMethods::Invoke<char>(Offsets::EnumVisibleObjectsPtr, GameInterface::EnumVisibleObjectsCb, (int)TypeId::Item);
//	GameMethods::Invoke<char>(Offsets::EnumVisibleObjectsPtr, GameInterface::EnumVisibleObjectsCb, (int)TypeId::Player);
//
//	for (auto o : Globals::Objects)
//	{
//		if (string(o->GetObjectName()) == objectName)
//		{
//			GameMethods::Invoke<int64_t>(Offsets::lua_pushguid, L, o->GetGuid());
//			return;
//		}
//		else
//			continue;
//	}
//
//	GameMethods::Invoke<int64_t>(Offsets::lua_pushnil, L);
//}

void LuaScript::RegisterHandler(std::string commandName, GameMethods::LuaCallback callback)
{
	GameMethods::Register(commandName.c_str(), LuaScript::WriteCallback(callback));
}

void LuaScript::SetHardwareEvent()
{

	printf("[+] SetHardWareEvent\n");
	static uintptr_t hardwareEventPtr = Offsets::HardwareEventPtr;

	LARGE_INTEGER frequency;
	LARGE_INTEGER perfCount;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&perfCount);

	const long currentTime = (perfCount.QuadPart * 1000) / frequency.QuadPart;
	*reinterpret_cast<uintptr_t*>(hardwareEventPtr) = currentTime;
}

void LuaScript::SetPlayer()
{
	//if (Player)
	//	return;

	//LuaBase::Input("iterObjects(0)", 0);
}

GameMethods::LuaCallback LuaScript::WriteCallback(GameMethods::LuaCallback callback)
{
	static auto runOnce = true;

	if (!runOnce)
		return callback;

	runOnce = false;

	uintptr_t invalidPtrCheckMax = Offsets::InvalidPtrCheckMax;
	uintptr_t invalidPtrCheckMin = Offsets::InvalidPtrCheckMin;
	*reinterpret_cast<uintptr_t*>(invalidPtrCheckMax) = uintptr_t(callback) + 0x1000;
	*reinterpret_cast<uintptr_t*>(invalidPtrCheckMin) = 2;

	return callback;
}



//int LuaScript::ExecuteAfterMS(int64_t luaState)
//{
//	auto delay = GameMethods::ToNumber(luaState, 1);
//	auto function = GameMethods::ToLString(luaState, 2, nullptr) + "()";
//
//	if (delay <= 0)
//		return 1;
//
//	LuaBase::Input(function, delay);
//
//	return 1;
//}
//
//int LuaScript::ExecuteEveryMS(int64_t luaState)
//{
//	auto sleepTime = GameMethods::ToNumber(luaState, 1);
//	auto function = GameMethods::ToLString(luaState, 2, nullptr);
//
//	string functionRepeater = "function " + function + "Repeater() " + function + "() after(" + to_string(sleepTime) + ", '" + function + "Repeater') end " + function + "Repeater()";
//
//	LuaBase::Input(functionRepeater, 0);
//
//	return 1;
//}
//
////int LuaScript::Fish(int64_t luaState)
////{
////	LuaBase::Input("iterObjects(1)", 0);
////
////	return 1;
//}
//
//int LuaScript::IterateObjects(int64_t luaState)
//{
//	if (!GameMethods::ObjMgrIsValid(0))
//		return 1;
//
//	auto param = GameMethods::ToNumber(luaState, 1);
//
//	GameMethods::EnumVisibleObjects(EnumVisibleObjCb, param);
//
//	return 1;
//}
//
//int LuaScript::GetPlayerGuid(int64_t luaState)
//{
//	SetPlayer();
//
////	GameMethods::PushGuid(luaState, reinterpret_cast<uintptr_t>(Player->GetGuid()));
//
//	return 1;
//}
//
//int LuaScript::GetPlayerPosition(int64_t luaState)
//{
//
//	//int x = GameMethods::PushNumber(luaState, ActivePlayer->GetUnitPosition().x);
//	//int y = GameMethods::PushNumber(luaState, ActivePlayer->GetUnitPosition().y);
//	//int z = GameMethods::PushNumber(luaState, ActivePlayer->GetUnitPosition().z);
//
//	return 3;
//}
//
//
//
//int LuaScript::TestParam(int64_t luaState)
//{
//	auto param = GameMethods::ToNumber(luaState, 1);
//	GameMethods::PushNumber(luaState, param);
//
//	return 1;
//}
//
//
//
//void LuaScript::chat(std::string message)
//{
//	if (!ActivePlayer)
//		return;
//
//	time_t rawtime;
//	struct tm timeinfo;
//	char buffer[80];
//
//	time(&rawtime);
//	localtime_s(&timeinfo, &rawtime);
//
//	strftime(buffer, 80, "[%H:%M:%S] ", &timeinfo);
//	std::string CName = "[XHOOK] ";
//	std::string taggedMessage = buffer + CName + message;
//	std::replace(taggedMessage.begin(), taggedMessage.end(), '\'', '_');
//	std::string to_print = "DEFAULT_CHAT_FRAME:AddMessage('" + taggedMessage + "')";
//	//GameMethods::Execute(to_print.c_str());
//}
//
