#include "stdafx.h"
#include "ObjectManager.h"
#include "Renderer.h"


void WoWObjectManager::CycleObjects(bool Refresh)
{
	if (Refresh) {
		printf("Clear!\n");
		Globals::Objects.clear();
	}

	GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, WoWObjectManager::EnumVisibleObjCb, (int)TypeId::CGItem);
	GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, WoWObjectManager::EnumVisibleObjCb, (int)TypeId::CGUnit);
	GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, WoWObjectManager::EnumVisibleObjCb, (int)TypeId::CGPlayer);
	GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, WoWObjectManager::EnumVisibleObjCb, (int)TypeId::CGActivePlayer);
	GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, WoWObjectManager::EnumVisibleObjCb, (int)TypeId::CGGameObject);
	GameMethods::Invoke<char>(Offsets::ClntObjMgrEnumVisibleObjectsPtr, WoWObjectManager::EnumVisibleObjCb, (int)TypeId::CGCorpse);
}

void WoWObjectManager::LoopObjectManager()
{
	CycleObjects(false);

	if (!Globals::LocalPlayer) {
		return;
	}

	nav::Move(); //Move our LocalPlayer
}

unsigned int WoWObjectManager::EnumVisibleObjCb(int64_t objectPtr, int64_t filter) {
	if (objectPtr)
	{
		auto object = reinterpret_cast<WObject*>(objectPtr);
		auto iType = (int)object->GetType();

		char guidStr[MAX_PATH];

		if (iType < (int)TypeId::Invalid && iType == filter)
		{
			if (iType == (int)TypeId::CGActivePlayer && !Globals::LocalPlayer) {
				Globals::LocalPlayer = object;
				std::cout << "[+] LocalPlayer address:" << std::hex << Globals::LocalPlayer << std::endl;
			}
			
			GameMethods::GuidToString(object->GetGuid(), guidStr);

			if (!Globals::Objects.contains(guidStr)) 
				Globals::Objects.emplace(guidStr, object);			
		}
		return 1;
	}
	return 0; // Break cycle point
}

bool WoWObjectManager::InGame() {
	return *reinterpret_cast<int8_t*>(Offsets::IsPlayerInWorld) != 0 ? true : false;
}

void WoWObjectManager::SetHardwareEvent() {
	static uintptr_t hardwareEventPtr = Offsets::HardwareEventPtr;

	LARGE_INTEGER frequency;
	LARGE_INTEGER perfCount;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&perfCount);

	const long currentTime = (perfCount.QuadPart * 1000) / frequency.QuadPart;
	*reinterpret_cast<uintptr_t*>(hardwareEventPtr) = currentTime;
}



