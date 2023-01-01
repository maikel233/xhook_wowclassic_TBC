#pragma once
#include "NAV/AmeisonNavigation.h"
#include "WObject.h"

constexpr int MAX_NAV = 10002;
constexpr int MAX_NODES = 2560;

//filter swapchain


class Globals
{
public:

	inline static WObject* LocalPlayer;
	inline static std::map<std::string, WObject*> Objects;
	inline static std::map<std::string, WObject*> AttackList;
	inline static Vector3 CorpsePos;

	inline static AmeisenNavigation* Nav = new AmeisenNavigation(("C:\\xhook\\wow\\mmaps\\"), MAX_NAV, MAX_NODES);
	static bool isLootWindowOpen();

	inline static uint64_t timeSinceEpochMillisec() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	//Delay
	inline static uint64_t last_update = 0;
	inline static uint64_t next_update_delta = 0;
	inline static bool update = false;

	// Mutex
	inline static bool SafeToExit = false;
	inline static bool Registered = false;

	inline static int swapchaincount = 0;
	inline static IDXGISwapChain* Swapchains[20];
	inline static IDXGISwapChain* g_pSwapChain;
};

extern Globals G;
