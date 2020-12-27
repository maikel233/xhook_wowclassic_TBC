#pragma once
#include <Windows.h>
#include <unordered_map>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <vector>
#include "json.h"

#include "Lua/LuaScript.h"

//ImGUI imports
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_internal.h"

#include "Constants.h"

#include "Utils.h"


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



class HealthColorVar : public ColorVar
{
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

enum class PlayerState : int
{
	Ground,
	Swimming,
	UnderWaterWalking,
	WaterWalking,
	FallingSlow,
	CanFly,
	DisableCollision,
	DisableGravity
};

enum class TeamColorType : int
{
	ABSOLUTE_,
	RELATIVE_,
};

enum class TeamID : int
{
	Horde,
	Alliance,
};

struct TeleporterInfo
{
	Vector3 pos;
	std::string name;
	int currmsg;

	TeleporterInfo(Vector3 pos, std::string name, int currmsg)
	{
		this->pos = pos;
		this->name = name;
		this->currmsg = currmsg;
	}
};

namespace Settings
{
	extern bool skip;

	namespace TeleportHelper
	{
		extern std::vector<TeleporterInfo> TeleporterInfos;
		extern bool enabled;
		extern std::string actMapName;
	}


	namespace EntityViewer
	{
		extern bool Enabled;
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
		extern bool Ally, Enemy;
		extern bool Player, LocalPlayer, Unit, Corpse, Object, GameObject, DynamicObject, Race, Horde, Alliance, DrawDeadEntity;
		extern bool Enabled, Lines, Names, Lvl, Health, Energy, Distance;
		extern int MaxLvl, MinLvl;
		extern float FOVX, FOVY, MultiPly;
		extern bool W2S_SKIP;
		extern ColorVar CorpseColor, GameObjectColor, ObjectColor, DynamicObjectColor;
		extern HealthColorVar PlayerColor, LocalPlayerColor, UnitColor, HordeColor, AllianceColor;
		
		namespace Radar
		{
			extern bool Enabled;
			extern bool name;
			extern bool Horde;
			extern bool Alliance;
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
			extern TeamID EntityTeamid;
		}
	}


	namespace UnitHelper
	{
		extern std::vector<UnitInfo> UnitInfos;
	}



	namespace Objectmanager
	{
		extern bool ObjMgrisdone, LoopObj;
	}

	namespace Hacks
	{
		namespace Lua {
			extern bool toggle;
		
		}
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
			extern bool TogglePlayerState;
			extern PlayerState CurrentPlayerState;
			extern bool CTM;
			
			extern bool TeleportBack;
			extern Vector3 NextPos;
			extern Vector3 PrevPos;

		

			extern float Current_Groundspeed; 
			extern float max_walkspeed; 
			extern float max_runspeed; 
			extern float max_walkingbackspeed; 
			extern float Current_Swimmingspeed;
			extern float max_walkspeed2; 
			extern float max_something2; 
			extern float player_rotationspeed;
			extern int max_jumpstate;
			extern bool JumpState, SuperSlowFall;
			extern bool JumpStatev2;
		
			extern int MovementType, NoClip; //BYTE
			extern float Cameraspeed, Jumpstartingheight, Swimmingspeed, Walkingspeed, Runningspeed, Turnspeed, Facing;
			extern float SomethingJump;
			extern float jumpHeight;
			extern float jumpHeightwaterspeed;
			extern float Movementspeed;
			extern float Fallingspeed;
			extern bool Toggleplayerstate;
			extern float WallClimb;
			extern bool Teleport;
			extern bool test, SuperFly, Infintejump, NoFallDamage, AntiJump, AntiMove, AntiRoot, Gravity, MovementFacing, TeleportBack, TeleporttoCorpse, TeleportMenu, SetCurrentXYZ, MovementNoClip, MovementJumpStartingHeight, MovementCameraspeed, MovementSwimmingspeed, MovementWalkingspeed, MovementRunningspeed, MovementTurnspeed, Lootpatch;
			extern float single;
			extern int MAPID;
		}

	}

	namespace Background
	{
		extern bool enable;
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
	
	void SaveTeleporterInfo(std::string path);
	void LoadTeleporterInfo(std::string path);
}

