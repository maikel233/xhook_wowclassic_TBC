#include "settings.h"
#include <string>
#include <sstream>
#include "Xorstr.h"

#include "Constants.h"

std::vector<TeleporterInfo> Settings::TeleportHelper::TeleporterInfos = {};
bool Settings::TeleportHelper::enabled = false;
std::string Settings::TeleportHelper::actMapName;

bool Settings::Drawing::Enabled = false;
bool Settings::Drawing::Lines = false;
bool Settings::Drawing::Names = false;
bool Settings::Drawing::Lvl = false;
bool Settings::Drawing::Health = false;
bool Settings::Drawing::EnergyAndMana = false;
bool Settings::Drawing::Ally = false;
bool Settings::Drawing::Enemy = false;
int Settings::Drawing::MaxLvl = 61;
int Settings::Drawing::MinLvl = 1;

bool Settings::EntityViewer::Enabled = false;

bool Settings::Drawing::Corpse;
bool Settings::Drawing::Player, Settings::Drawing::LocalPlayer, Settings::Drawing::Unit, Settings::Drawing::DrawDeadEntity;
bool Settings::Drawing::Object, Settings::Drawing::GameObject, Settings::Drawing::DynamicObject, Settings::Drawing::Race, Settings::Drawing::Horde, Settings::Drawing::Alliance = false;
bool Settings::Drawing::Distance;

bool Settings::Drawing::Radar::Enabled = false;
bool Settings::Drawing::Radar::Horde = false;
bool Settings::Drawing::Radar::Alliance = false;
bool Settings::Drawing::Radar::Player, Settings::Drawing::Radar::LocalPlayer, Settings::Drawing::Radar::Unit, Settings::Drawing::Radar::Corpse, Settings::Drawing::Radar::GameObject, Settings::Drawing::Radar::DrawDeadEntity;
bool Settings::Drawing::Radar::name = false;
float Settings::Drawing::Radar::zoom = 1.f;
float Settings::Drawing::Radar::iconsScale = 4.5f;
float Settings::Drawing::Radar::multiply = 4.5f;
TeamColorType Settings::Drawing::Radar::teamColorType = TeamColorType::RELATIVE_;
HealthColorVar Settings::Drawing::Radar::enemyColor = ImColor(255, 0, 0, 255);
HealthColorVar Settings::Drawing::Radar::enemyVisibleColor = ImColor(255, 255, 0, 255);
HealthColorVar Settings::Drawing::Radar::allyColor = ImColor(0, 0, 255, 255);
HealthColorVar Settings::Drawing::Radar::allyVisibleColor = ImColor(0, 255, 0, 255);
HealthColorVar Settings::Drawing::Radar::HordeColor = ImColor(255, 0, 0, 255);
HealthColorVar Settings::Drawing::Radar::HordeVisibleColor = ImColor(255, 255, 0, 255);
HealthColorVar Settings::Drawing::Radar::AllianceColor = ImColor(0, 0, 255, 255);
HealthColorVar Settings::Drawing::Radar::AllianceVisibleColor = ImColor(0, 255, 0, 255);



HealthColorVar Settings::Drawing::Radar::PlayerColor = ImColor(240, 248, 255);
HealthColorVar Settings::Drawing::Radar::UnitColor = ImColor(255, 127, 80);
ColorVar Settings::Drawing::Radar::GameObjectColor = ImColor(0, 157, 20);

HealthColorVar Settings::Drawing::PlayerColor = ImColor(240, 248, 255);
HealthColorVar Settings::Drawing::LocalPlayerColor = ImColor(15, 248, 255);
HealthColorVar Settings::Drawing::UnitColor = ImColor(255, 127, 80);
ColorVar Settings::Drawing::CorpseColor = ImColor(255, 0, 0);
ColorVar Settings::Drawing::GameObjectColor = ImColor(0, 157, 20);
HealthColorVar Settings::Drawing::HordeColor = ImColor(255, 0, 0);
HealthColorVar Settings::Drawing::AllianceColor = ImColor(0, 0, 255);
ColorVar Settings::Drawing::DynamicObjectColor = ImColor(0, 80, 60);
ColorVar Settings::Drawing::ObjectColor = ImColor(0, 157, 20);

float Settings::Drawing::FOVX = 44.0f;
float Settings::Drawing::FOVY = 35.0f;

float Settings::Drawing::MultiPly = 2.0f;
bool Settings::Drawing::W2S_SKIP = false;
bool Settings::Drawing::ClassColor = false;

bool Settings::Hacks::Movement::TogglePlayerState = false;
PlayerState Settings::Hacks::Movement::CurrentPlayerState = PlayerState::Ground;

TeamID Settings::Drawing::Radar::EntityTeamid = TeamID::Horde;


//Camera
bool Settings::Hacks::Camera::Enable = false;
float Settings::Hacks::Camera::Camera_zoomout = 0, Settings::Hacks::Camera::Camera_zoomin = 0, Settings::Hacks::Camera::Camera_fov;


//
float Settings::Hacks::Movement::Current_Groundspeed = 0;
float Settings::Hacks::Movement::max_walkspeed = 0;
float Settings::Hacks::Movement::max_runspeed = 0;
float Settings::Hacks::Movement::max_walkingbackspeed = 0;
float Settings::Hacks::Movement::Current_Swimmingspeed = 0;
float Settings::Hacks::Movement::max_walkspeed2 = 0;
float Settings::Hacks::Movement::max_something2 = 0;
float Settings::Hacks::Movement::player_rotationspeed = 0;

int Settings::Hacks::Movement::max_jumpstate = 824;

bool Settings::Objectmanager::LoopObj = false;
bool Settings::Objectmanager::ObjMgrisdone = false;


bool Settings::skip = false;

bool Settings::Hacks::Movement::TeleportBack = false;
C3Vector Settings::Hacks::Movement::NextPos = { 0,0,0 };
C3Vector Settings::Hacks::Movement::PrevPos = { 0,0,0 };

//
float Settings::Hacks::Movement::SomethingJump = -7.955547;
float Settings::Hacks::Movement::jumpHeight = -7.955547;
float Settings::Hacks::Movement::jumpHeightwaterspeed = 7.0f;
float Settings::Hacks::Movement::WallClimb = 5.6427876353;
float Settings::Hacks::Movement::Movementspeed = 9.0f;
float Settings::Hacks::Movement::Fallingspeed = 60.0f;
bool Settings::Hacks::Movement::Toggleplayerstate = false;
//int Settings::Hacks::Movement::Playerstate = 0;
bool Settings::Hacks::Movement::Teleport;
bool Settings::Hacks::Movement::SuperFly;
bool Settings::Hacks::Movement::AntiJump;
bool Settings::Hacks::Movement::AntiMove;
bool Settings::Hacks::Movement::AntiRoot;
bool Settings::Hacks::Movement::Infintejump;
bool Settings::Hacks::Movement::NoFallDamage;
float Settings::Hacks::Movement::single;
//float Settings::Hacks::Movement::CX, CY, CZ = 0.001f; // Current XYZ
//float Settings::Hacks::Movement::X, Y, Z = 0.001f; // Destination XYZ
int Settings::Hacks::Movement::MAPID = 0;


bool Settings::Background::enable = true;
bool Settings::Hacks::Movement::Gravity = false;
bool Settings::Hacks::Movement::MovementRunningspeed = false;
bool Settings::Hacks::Movement::MovementWalkingspeed = false;
bool Settings::Hacks::Movement::MovementSwimmingspeed = false;
bool Settings::Hacks::Movement::MovementCameraspeed = false;
bool Settings::Hacks::Movement::MovementFacing = false;
bool Settings::Hacks::Movement::test = false;
bool Settings::Hacks::Movement::MovementJumpStartingHeight = false;
bool Settings::Hacks::Movement::MovementNoClip = false;
//
bool WeTeleportedOnce = false;
//
bool Settings::Hacks::Movement::TeleportMenu = false;
bool Settings::Hacks::Movement::TeleporttoCorpse = false;
bool Settings::Hacks::Movement::SetCurrentXYZ = false;
bool Settings::Hacks::Movement::MovementTurnspeed = false;
bool Settings::Hacks::Lua::toggle = false;
bool Settings::Hacks::Movement::Lootpatch = false;

float  Settings::Hacks::Movement::Turnspeed = 3.7f;
float  Settings::Hacks::Movement::Cameraspeed = 10.0f;
float  Settings::Hacks::Movement::Jumpstartingheight;
float  Settings::Hacks::Movement::Swimmingspeed = 7.5f;
float  Settings::Hacks::Movement::Walkingspeed = 2.5f;
float  Settings::Hacks::Movement::Runningspeed = 7.5f;
float  Settings::Hacks::Movement::Facing = 1.0f;
int Settings::Hacks::Movement::MovementType = 60;
int Settings::Hacks::Movement::NoClip = 0;

float Settings::Hacks::Misc::ScaleHeight;



void GetVal(Json::Value& config, int* setting)
{
	if (config.isNull())
		return;

	*setting = config.asInt();
}

void GetVal(Json::Value& config, bool* setting)
{
	if (config.isNull())
		return;

	*setting = config.asBool();
}

void GetVal(Json::Value& config, float* setting)
{
	if (config.isNull())
		return;

	*setting = config.asFloat();
}

void GetVal(Json::Value& config, ImColor* setting)
{
	if (config.isNull())
		return;

	GetVal(config["r"], &setting->Value.x);
	GetVal(config["g"], &setting->Value.y);
	GetVal(config["b"], &setting->Value.z);
	GetVal(config["a"], &setting->Value.w);
}

void GetVal(Json::Value& config, char** setting)
{
	if (config.isNull())
		return;

	*setting = _strdup(config.asCString());
}

void GetVal(Json::Value& config, char* setting)
{
	if (config.isNull())
		return;

	strcpy(setting, config.asCString());
}

void GetVal(Json::Value& config, ColorVar* setting)
{
	if (config.isNull())
		return;

	GetVal(config["r"], &setting->color.Value.x);
	GetVal(config["g"], &setting->color.Value.y);
	GetVal(config["b"], &setting->color.Value.z);
	GetVal(config["a"], &setting->color.Value.w);
	GetVal(config["rainbow"], &setting->rainbow);
	GetVal(config["rainbowSpeed"], &setting->rainbowSpeed);
}

void GetVal(Json::Value& config, HealthColorVar* setting)
{
	if (config.isNull())
		return;

	GetVal(config["r"], &setting->color.Value.x);
	GetVal(config["g"], &setting->color.Value.y);
	GetVal(config["b"], &setting->color.Value.z);
	GetVal(config["a"], &setting->color.Value.w);
	GetVal(config["rainbow"], &setting->rainbow);
	GetVal(config["rainbowSpeed"], &setting->rainbowSpeed);
	GetVal(config["hp"], &setting->hp);
}

template <typename Ord, Ord(*lookupFunction)(std::string)>
void GetOrdinal(Json::Value& config, Ord* setting)
{
	if (config.isNull())
		return;

	Ord value;
	if (config.isString())
		value = lookupFunction(config.asString());
	else
		value = (Ord)config.asInt();

	*setting = value;
}

void LoadColor(Json::Value& config, ImColor color)
{
	config["r"] = color.Value.x;
	config["g"] = color.Value.y;
	config["b"] = color.Value.z;
	config["a"] = color.Value.w;
}

void LoadColor(Json::Value& config, ColorVar color)
{
	config["r"] = color.color.Value.x;
	config["g"] = color.color.Value.y;
	config["b"] = color.color.Value.z;
	config["a"] = color.color.Value.w;
	config["rainbow"] = color.rainbow;
	config["rainbowSpeed"] = color.rainbowSpeed;
}

void LoadColor(Json::Value& config, HealthColorVar color)
{
	config["r"] = color.color.Value.x;
	config["g"] = color.color.Value.y;
	config["b"] = color.color.Value.z;
	config["a"] = color.color.Value.w;
	config["rainbow"] = color.rainbow;
	config["rainbowSpeed"] = color.rainbowSpeed;
	config["hp"] = color.hp;
}

void Settings::LoadDefaultsOrSave(std::string path)
{
	Json::Value settings;
	Json::StyledWriter styledWriter;

	LoadColor(settings[XorStr("UI")][XorStr("mainColor")], Settings::UI::mainColor);
	LoadColor(settings[XorStr("UI")][XorStr("bodyColor")], Settings::UI::bodyColor);
	LoadColor(settings[XorStr("UI")][XorStr("fontColor")], Settings::UI::fontColor);
	LoadColor(settings[XorStr("UI")][XorStr("accentColor")], Settings::UI::accentColor);


	settings[XorStr("ESP")][XorStr("World")][XorStr("enabled")], Settings::Drawing::Enabled;
	settings[XorStr("ESP")][XorStr("World")][XorStr("Lines")], Settings::Drawing::Lines;
	settings[XorStr("ESP")][XorStr("World")][XorStr("Names")], Settings::Drawing::Names;
	settings[XorStr("ESP")][XorStr("World")][XorStr("lvl")], Settings::Drawing::Lvl;
	settings[XorStr("ESP")][XorStr("World")][XorStr("distance")], Settings::Drawing::Distance;
	settings[XorStr("ESP")][XorStr("World")][XorStr("race")], Settings::Drawing::Race;
	settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("LocalPlayer")], Settings::Drawing::LocalPlayer;
	settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("Unit")], Settings::Drawing::Unit;
	settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("Corpse")], Settings::Drawing::Corpse;
	settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("GameObject")], Settings::Drawing::GameObject;
	settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("DeadEntity")], Settings::Drawing::DrawDeadEntity;
	settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("Enemy")], Settings::Drawing::Enemy;
	settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("Friendly")], Settings::Drawing::Alliance;

	LoadColor(settings[XorStr("ESP")][XorStr("World")][XorStr("PlayerColor")], Settings::Drawing::PlayerColor);
	LoadColor(settings[XorStr("ESP")][XorStr("World")][XorStr("UnitColor")], Settings::Drawing::UnitColor);
	LoadColor(settings[XorStr("ESP")][XorStr("World")][XorStr("GameObjColor")], Settings::Drawing::GameObjectColor);
	LoadColor(settings[XorStr("ESP")][XorStr("World")][XorStr("CorpseColor")], Settings::Drawing::CorpseColor);
	LoadColor(settings[XorStr("ESP")][XorStr("World")][XorStr("HordeColor")], Settings::Drawing::HordeColor);
	LoadColor(settings[XorStr("ESP")][XorStr("World")][XorStr("AllianceColor")], Settings::Drawing::AllianceColor);


	settings[XorStr("ESP")][XorStr("Radar")][XorStr("enabled")], Settings::Drawing::Radar::Enabled;
	settings[XorStr("ESP")][XorStr("Radar")][XorStr("names")], Settings::Drawing::Radar::name;
	settings[XorStr("ESP")][XorStr("Radar")][XorStr("Zoom")], Settings::Drawing::Radar::zoom;
	settings[XorStr("ESP")][XorStr("Radar")][XorStr("icons_scale")], Settings::Drawing::Radar::iconsScale;

	settings[XorStr("ESP")][XorStr("Radar")][XorStr("Filter")][XorStr("LocalPlayer")], Settings::Drawing::Radar::LocalPlayer;
	settings[XorStr("ESP")][XorStr("Radar")][XorStr("Filter")][XorStr("Unit")], Settings::Drawing::Radar::Unit;
	settings[XorStr("ESP")][XorStr("Radar")][XorStr("Filter")][XorStr("GameObject")], Settings::Drawing::Radar::GameObject;
	settings[XorStr("ESP")][XorStr("Radar")][XorStr("Filter")][XorStr("DeadEntity")], Settings::Drawing::Radar::DrawDeadEntity;
	settings[XorStr("ESP")][XorStr("Radar")][XorStr("Filter")][XorStr("Enemy")], Settings::Drawing::Radar::Horde;
	settings[XorStr("ESP")][XorStr("Radar")][XorStr("Filter")][XorStr("Friendly")], Settings::Drawing::Radar::Alliance;

	LoadColor(settings[XorStr("ESP")][XorStr("Radar")][XorStr("PlayerColor")], Settings::Drawing::Radar::PlayerColor);
	LoadColor(settings[XorStr("ESP")][XorStr("Radar")][XorStr("UnitColor")], Settings::Drawing::Radar::UnitColor);
	LoadColor(settings[XorStr("ESP")][XorStr("Radar")][XorStr("HordeColor")], Settings::Drawing::Radar::HordeColor);
	LoadColor(settings[XorStr("ESP")][XorStr("Radar")][XorStr("AllianceColor")], Settings::Drawing::Radar::GameObjectColor);

	std::ofstream(path) << styledWriter.write(settings);
}

inline bool exists_test3(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
void Settings::LoadConfig(std::string path)
{
	if (!exists_test3(path))
	{
		//Settings::LoadDefaultsOrSave(path);
		return;
	}

	Json::Value settings;
	std::ifstream configDoc(path, std::ifstream::binary);
	configDoc >> settings;

	GetVal(settings[XorStr("UI")][XorStr("mainColor")], &Settings::UI::mainColor);
	GetVal(settings[XorStr("UI")][XorStr("bodyColor")], &Settings::UI::bodyColor);
	GetVal(settings[XorStr("UI")][XorStr("fontColor")], &Settings::UI::fontColor);
	GetVal(settings[XorStr("UI")][XorStr("accentColor")], &Settings::UI::accentColor);


	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("enabled")], &Settings::Drawing::Enabled);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("Lines")], &Settings::Drawing::Lines);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("Names")], &Settings::Drawing::Names);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("lvl")], &Settings::Drawing::Lvl);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("distance")], &Settings::Drawing::Distance);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("race")], &Settings::Drawing::Race);

	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("PlayerColor")], &Settings::Drawing::PlayerColor);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("UnitColor")], &Settings::Drawing::UnitColor);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("GameObjColor")], &Settings::Drawing::GameObjectColor);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("CorpseColor")], &Settings::Drawing::CorpseColor);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("HordeColor")], &Settings::Drawing::HordeColor);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("AllianceColor")], &Settings::Drawing::AllianceColor);

	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("LocalPlayer")], &Settings::Drawing::LocalPlayer);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("Unit")], &Settings::Drawing::Unit);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("Corpse")], &Settings::Drawing::Corpse);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("GameObject")], &Settings::Drawing::GameObject);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("DeadEntity")], &Settings::Drawing::DrawDeadEntity);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("Enemy")], &Settings::Drawing::Enemy);
	GetVal(settings[XorStr("ESP")][XorStr("World")][XorStr("Filter")][XorStr("Friendly")], &Settings::Drawing::Alliance);

	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("enabled")], &Settings::Drawing::Radar::Enabled);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("names")], &Settings::Drawing::Radar::name);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("Zoom")], &Settings::Drawing::Radar::zoom);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("icons_scale")], &Settings::Drawing::Radar::iconsScale);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("PlayerColor")], &Settings::Drawing::Radar::PlayerColor);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("UnitColor")], &Settings::Drawing::Radar::UnitColor);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("HordeColor")], &Settings::Drawing::Radar::HordeColor);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("AllianceColor")], &Settings::Drawing::Radar::GameObjectColor);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("Filter")][XorStr("LocalPlayer")], &Settings::Drawing::Radar::LocalPlayer);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("Filter")][XorStr("Unit")], &Settings::Drawing::Radar::Unit);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("Filter")][XorStr("GameObject")], &Settings::Drawing::Radar::GameObject);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("Filter")][XorStr("DeadEntity")], &Settings::Drawing::Radar::DrawDeadEntity);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("Filter")][XorStr("Enemy")], &Settings::Drawing::Radar::Horde);
	GetVal(settings[XorStr("ESP")][XorStr("Radar")][XorStr("Filter")][XorStr("Friendly")], &Settings::Drawing::Radar::Alliance);
}


char paths[255];
void Settings::LoadSettings()
{
	//static CHAR path[MAX_PATH];
	strcat(paths, "C:\\Xhook\\wow");
	std::string folder, file;

	folder = std::string(paths) + "\\Configs\\";

	CreateDirectoryA(folder.c_str(), NULL);
}

void Settings::SaveTeleporterInfo(std::string path) {
	Json::Value grenadeInfos;
	for (auto TeleporterInfo = TeleportHelper::TeleporterInfos.begin();
		TeleporterInfo != TeleportHelper::TeleporterInfos.end(); TeleporterInfo++) {
		Json::Value act;

		act[XorStr("pos")][XorStr("x")] = TeleporterInfo->pos.x;
		act[XorStr("pos")][XorStr("y")] = TeleporterInfo->pos.y;
		act[XorStr("pos")][XorStr("z")] = TeleporterInfo->pos.z;

		act[XorStr("name")] = TeleporterInfo->name.c_str();

		act[XorStr("currmsg")] = TeleporterInfo->currmsg;

		grenadeInfos.append(act);
	}

	Json::Value data;
	Json::StyledWriter styledWriter;

	data[XorStr("teleportinfo")] = grenadeInfos;

	std::ofstream(path) << styledWriter.write(data);
}

void Settings::LoadTeleporterInfo(std::string path) {
	/*if (!std::ifstream(path).good() || !DoesFileExist(path.c_str()))
		return;*/
	Json::Value data;
	std::ifstream configDoc(path, std::ifstream::binary);
	try {
		configDoc >> data;
	}
	catch (...) {
		printf("Error parsing the config file.\n");
		return;
	}

	Json::Value array = data[XorStr("teleportinfo")];
	Settings::TeleportHelper::TeleporterInfos = {};

	for (Json::Value::iterator it = array.begin(); it != array.end(); ++it) {

		Json::Value act = *it;

		Json::Value pos = act[XorStr("pos")];
		Vector3 currpos = Vector3(pos[XorStr("x")].asFloat(), pos[XorStr("y")].asFloat(),
			pos[XorStr("z")].asFloat());

		const char* name = act[XorStr("name")].asCString();

		Json::Value angle = act[XorStr("angle")];
		Vector vAngle = Vector(angle[XorStr("x")].asFloat(), angle[XorStr("y")].asFloat(), 0);

		int currmsg = act[XorStr("currmsg")].asInt();

		Settings::TeleportHelper::TeleporterInfos.push_back(TeleporterInfo(currpos, name, currmsg));
	}
}