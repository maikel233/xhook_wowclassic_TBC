#include "discord.hpp"

#include <discord_register.h>
#include <discord_rpc.h>

#include <cstring>
#include <chrono>
#include <unordered_map>


#include "Utils.h"
#include "Lua/ObjectManager.h"

// format string at runtime
template<typename... Args_t>
_NODISCARD inline constexpr std::string FORMAT(const std::string_view fmt, Args_t&&... args)
{
	return std::vformat(std::locale(), fmt, std::make_format_args(args...));
}


DiscordPresence::DiscordPresence()
{
	Discord_Initialize("1014961595354447882", NULL, 0, "730"); 
}

static std::pair<std::string, std::string> getImage(const std::string& map)
{
		return std::make_pair(("unknown"), ("unknown"));
}

void DiscordPresence::run()
{

	DiscordRichPresence pres;
	std::memset(&pres, 0, sizeof(pres));

	static std::string state;
	static std::pair<std::string, std::string> image;

	static std::string details;

	state = ("Maikel233#0063 is the best");
	if (WoWObjectManager::InGame() && GameMethods::ObjMgrIsValid(0))
	{
	//	state = ("Class: %s Level: %i ", Utils::GetClass(Globals::LocalPlayer), Globals::LocalPlayer->GetUnitLevel(1)/*, GameMethods::ClntObjMgr__GetMapId()*/);
		image = getImage("Woopdiedooooo");

		WObject* localplayer = (WObject*)Globals::LocalPlayer;
		if (!localplayer) {
			details = "LocalPlayer not initialized.";
		}
		else {
			details = FORMAT(("Race: {} Class: {} Level: {} MapId: {}"), Utils::GetRace(Globals::LocalPlayer), Utils::GetClass(Globals::LocalPlayer), Globals::LocalPlayer->GetUnitLevel(1), GameMethods::ClntObjMgr__GetMapId());
	
		}		
	}
	else 
	{
		state = ("X-HOOK: Login screen");
		image = getImage("Woopdiedoo");
	}

	pres.state = state.c_str();


	//if (WoWObjectManager::InGame() || GameMethods::ObjMgrIsValid(1))
	//{ //std::string Utils::GetClass(WObject* Entity)
	//	details = ("Class: %s Level: %i  MAPID: %i", Utils::GetClass(Globals::LocalPlayer), Globals::LocalPlayer->GetUnitLevel(1), GameMethods::ClntObjMgr__GetMapId());
	//}
	

	pres.details = details.c_str();
	const static auto epoch = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	pres.startTimestamp = epoch;

	pres.largeImageKey = image.second.c_str();
	pres.largeImageText = image.first.c_str();

	Discord_UpdatePresence(&pres);
}

void DiscordPresence::shutdown()
{
	Discord_ClearPresence();
	Discord_Shutdown();
}