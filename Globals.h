#pragma once
//#include "DllMain.h"
#include "NAV/AmeisonNavigation.h"
#include "WObject.h"



constexpr int MAX_NAV = 10002;
constexpr int MAX_NODES = 2560;

class Globals
{
	struct HandleData {
		unsigned long pid;
		HWND wHandle;
	};

	static BOOL CALLBACK EnumWindowsCB(HWND handle, LPARAM lparam) {
		auto& data = *reinterpret_cast<HandleData*>(lparam);

		unsigned long process_id = 0;
		GetWindowThreadProcessId(handle, &process_id);

		if (data.pid != process_id)
			return TRUE;

		data.wHandle = handle;
		return FALSE;
	}

	static HWND FindMainWindow() {
		HandleData data{};

		data.pid = GetCurrentProcessId();
		data.wHandle = nullptr;
		EnumWindows(EnumWindowsCB, reinterpret_cast<LPARAM>(&data));

		return data.wHandle;
	}
public:

	inline static WObject* LocalPlayer;
	inline static std::map<std::string, WObject*> Objects;
	inline static Vector3 CorpsePos;

	inline static AmeisenNavigation* Nav = new AmeisenNavigation(("C:\\xhook\\wow\\mmaps\\"), MAX_NAV, MAX_NODES);
	static bool isLootWindowOpen();


	inline static uint64_t timeSinceEpochMillisec() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	// hWnd
	inline static HWND HWND = FindMainWindow();
	inline static WNDPROC OgWndProc;

	//Delay
	inline static uint64_t last_update = 0;
	inline static uint64_t next_update_delta = 0;
	inline static bool update = false;

	// Mutex
	inline static bool SafeToExit = false;
	inline static bool Registered = false;
};
