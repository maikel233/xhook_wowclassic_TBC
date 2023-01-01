#pragma once
#include <Windows.h>
#include <unordered_map>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <vector>
#include "json.h"

#include "Lua/ObjectManager.h"

//ImGUI imports
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_internal.h"

#include "Constants.h"
#include "Utils.h"
#include "Settings/Settings.h"

enum class PathTypes : int
{
	STRAIGHT = 0,
	RANDOM = 1,
};

enum class PathRequestFlag : int
{
	NONE = 0,
	CHAIKIN = 1,
	CATMULLROM = 2,
};


class ColorVar
{
public:
	ImColor color;
	bool rainbow;
	float rainbowSpeed;

	ColorVar() {}

	ColorVar(ImColor color)
	{
		this->color = color;
		this->rainbow = false;
		this->rainbowSpeed = 0.5f;
	}

	ImColor Color()
	{
		ImColor result = this->rainbow ? Utils::GetRainbowColor(this->rainbowSpeed) : this->color;
		result.Value.w = this->color.Value.w;
		return result;
	}
};

class HealthColorVar : public ColorVar {
public:
	bool hp;
	HealthColorVar(ImColor color)
	{
		this->color = color;
		this->rainbow = false;
		this->rainbowSpeed = 0.5f;
		this->hp = false;
	}

	ImColor Color(WObject* player)
	{
		ImColor result = this->rainbow ? Utils::GetRainbowColor(this->rainbowSpeed) : (this->hp ? Color::ToImColor(Utils::GetHealthColor(player)) : this->color);
		result.Value.w = this->color.Value.w;
		return result;
	}

};

enum class PlayerState : int {
	Ground,
	Swimming,
	UnderWaterWalking,
	WaterWalking,
	FallingSlow,
	CanFly,
	DisableCollision,
	Root,
	Loggedoff,
	DisableGravity
};

enum class TeamColorType : int {
	ABSOLUTE_,
	RELATIVE_,
};

//enum class TeamID : int {
//	Horde,
//	Alliance,
//	INVALID,
//};

//struct TeleporterInfo
//{
//	Vector3 pos;
//	std::string name;
//	int currmsg;
//
//	TeleporterInfo(Vector3 pos, std::string name, int currmsg)
//	{
//		this->pos = pos;
//		this->name = name;
//		this->currmsg = currmsg;
//	}
//};

namespace Settings
{

	//namespace TeleportHelper
	//{
	//	extern std::vector<TeleporterInfo> TeleporterInfos;
	//	extern bool enabled;
	//	extern std::string actMapName;
	//}

	namespace bot
	{
		extern bool NPCEXIST;
		extern int TotalUnits;
		extern int TotalPlayers;
		extern int TotalObjects;
		//extern int TotalUnits;

		extern bool Refresh;
		namespace Navigator
		{
			extern PathTypes pPathType;
			extern PathRequestFlag pPathRequestFlag;
		}

		namespace Grinding
		{
			extern bool Enabled;
			extern const char* FoodName;
			extern const char* DrinkName;
			extern float mRestManaPercent;
			extern float mRestHealthPercent;
			extern bool SkinMobs;
		}
		namespace fishing
		{
			extern bool Enabled;
			extern bool IsFishing;
			extern bool PoolDetection;
		}
	}


	namespace HWID
	{
		extern bool LoggedIn;
		extern bool Enabled;
		extern char Message[255];
		extern bool uninject;
	}

	namespace Drawing
	{
		extern bool TraceLine;
		extern bool Ally, Enemy, HostileUnits, HostilePlayers;
		extern bool Player, LocalPlayer, Unit, Corpse, Object, GameObject, DynamicObject, Race, Horde, Alliance, DrawDeadEntity;
		extern bool Enabled, Lines, Names, Lvl, Health, EnergyAndMana, Distance, WayPoints, GuidStr;
		extern int MaxLvl, MinLvl;
		extern ColorVar CorpseColor, GameObjectColor, UnlockedGameObjectColor, ObjectColor, DynamicObjectColor;
		extern HealthColorVar PlayerColor, LocalPlayerColor, UnitColor, HordeColor, AllianceColor;

		namespace EntityViewer
		{
			extern bool Enabled;
		}

		namespace Radar
		{
			extern bool Enabled;
			extern bool name;
			extern bool Ally, Enemy, HostileUnits, HostilePlayers;
			extern bool Player, LocalPlayer, Unit, Corpse, Object, GameObject, DrawDeadEntity;
			extern float zoom;
			extern float iconsScale;
			extern float multiply;
			extern TeamColorType teamColorType;
			extern HealthColorVar enemyColor;
			extern HealthColorVar enemyVisibleColor;
			extern HealthColorVar allyColor;
			extern HealthColorVar allyVisibleColor;
			extern HealthColorVar HordeColor;
			extern HealthColorVar HordeVisibleColor;
			extern HealthColorVar AllianceColor;
			extern HealthColorVar AllianceVisibleColor;
			extern HealthColorVar PlayerColor, UnitColor;
			extern ColorVar GameObjectColor;
			extern ColorVar UnlockedGameObjectColor;
		}
	}

	namespace Hacks
	{

		namespace Misc {
			extern float ScaleHeight;
		}
		namespace Camera
		{
			extern bool Enable;
			extern float Camera_zoomout, Camera_zoomin, Camera_fov;
		}
		namespace Movement
		{

			extern bool enabled;
			extern PlayerState CurrentPlayerState;
			extern bool CTM;
			extern bool TeleportBack;
			extern bool TogglePlayerState;
			extern bool JumpState, SuperSlowFall;
			extern bool JumpStatev2;
			extern bool Teleport;
			//	extern bool test, SuperFly, Infintejump, NoFallDamage, AntiJump, AntiMove, AntiRoot, Gravity, MovementFacing, TeleportBack, TeleporttoCorpse, TeleportMenu, SetCurrentXYZ, MovementNoClip, MovementJumpStartingHeight, MovementCameraspeed, MovementSwimmingspeed, MovementWalkingspeed, MovementRunningspeed, MovementTurnspeed, Lootpatch;
			extern int SuperSlowSleepTime;

			extern int max_jumpstate;
			extern int MovementType, NoClip; //BYTE

			extern float max_walkspeed, max_runspeed, max_walkingbackspeed, Current_Groundspeed, Current_Swimmingspeed;
			extern float max_walkspeed2;
			extern float max_something2;
			extern float player_rotationspeed;
			extern float Cameraspeed, Jumpstartingheight, Swimmingspeed, Walkingspeed, Runningspeed, Turnspeed, Facing;
			extern float SomethingJump;
			extern float jumpHeight;
			extern float jumpHeightwaterspeed;
			extern float Movementspeed;
			extern float Fallingspeed;
			extern float WallClimb;
			extern float single;

			extern Vector3 NextPos, PrevPos;

		}

	}


	namespace UI
	{
		extern bool is_renderer_active;
		extern ColorVar mainColor;
		extern ColorVar bodyColor;
		extern ColorVar fontColor;
		extern ColorVar accentColor;

		extern bool MainUI;

		namespace Windows {
			namespace Menu {
				extern bool GetInvItems;
				extern bool g_ShowMenu;
			}
			namespace Config {
				extern int posX;
				extern int posY;
				extern int sizeX;
				extern int sizeY;
				extern bool open;
				extern bool reload; // True on config load, used to change Window Position.
			}
		}

	}
	void LoadDefaultsOrSave(std::string path);
	void LoadConfig(std::string path);
	void LoadSettings();
}

