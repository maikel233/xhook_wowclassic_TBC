#include "Renderer.h"
#include "Camera.h"
#include "Constants.h"
#include <imgui_internal.h>
#include <inttypes.h>
#include "Radar.h"
#include "Hacks.h"

namespace Draw
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}
	bool InitFont = false;
	void Renderer::Initialize()
	{
		if (!InitFont)
		{ 
			ImGuiIO& io = ImGui::GetIO();
			m_pFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13);
			InitFont = true;
		}
	}

	void Renderer::BeginScene()
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
		ImGui::Begin("##Backbuffer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
	}


	void Renderer::DrawObjects(WObject* entity, HealthColorVar Colors)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window)
		{
			Vector2 OPPos = WoW::camera::WorldToScreenv2(entity->GetUnitPosition());
			Vector2 LPPos = WoW::camera::WorldToScreenv2(LuaScript::ActivePlayer->GetUnitPosition());

			if ((OPPos.x == NULL && OPPos.y == NULL) || LPPos.x == NULL && LPPos.y == NULL)
				return;

			int TypeID = (int)entity->GetType();

			//Give Players made objects a color.
			if (*entity->GetOwner() == *LuaScript::ActivePlayer->GetGuid())
			{
				Colors = ImColor(1.4f, 0.1f, 0.0f, 1.0f);
				window->DrawList->AddCircle(ImVec2(OPPos.x, OPPos.y), 10, Colors.color, 12, 1.0);
			}

			if (LuaScript::ActivePlayer->sUnitField->Target == *entity->GetGuid())
			{
				Colors = ImColor(1.4f, 0.1f, 0.0f, 1.0f);
				window->DrawList->AddCircle(ImVec2(OPPos.x, OPPos.y), 10, Colors.color, 12, 1.0);
			}
		
			if (Settings::Drawing::Lines)
			{
				window->DrawList->AddLine(ImVec2(LPPos.x, LPPos.y), ImVec2(OPPos.x, OPPos.y), Colors.color, 1);
			}

			if (Settings::Drawing::Distance)
			{
				float Distance = LuaScript::ActivePlayer->GetUnitPosition().DistanceTo(entity->GetUnitPosition());
				string Distancestr = "Meters: " + std::to_string(Distance);
				const char* cDistancestr = Distancestr.c_str();
				window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 10.f), Colors.color, cDistancestr);
			}

			if (Settings::Drawing::Names)
			{		
				if (entity->GetType() == TypeId::CGPlayer || TypeID == (int)TypeId::CGActivePlayer)
				{
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 40.f), Utils::GetClassColor(entity), entity->GetObjectName());				
				}
				else if (TypeID == (int)TypeId::CGUnit || TypeID == (int)TypeId::CGGameObject)
				{ 
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 40.f), Colors.color, entity->GetObjectName());
				}
			}

			if ((TypeID == (int)TypeId::CGUnit) || TypeID == (int)TypeId::CGPlayer)
			{
	
				if (Settings::Drawing::Race)
				{
					string Race = Utils::GetRace(entity);
					const char* cRace = Race.c_str();
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y), Colors.color, cRace);
				}

				if (Settings::Drawing::Health)
				{
					string UnitHealthstr2 = "HP:" + Utils::GetHealth(entity);
					const char* cUnitHealthstr = UnitHealthstr2.c_str();
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 30.f), Colors.color, cUnitHealthstr);
				}
				if (Settings::Drawing::EnergyAndMana)
				{
					if (TypeID == (int)TypeId::CGPlayer)
					{
						std::string UnitClass;
						int RACEID = entity->sUnitField->RaceID;
						if (RACEID == WoWClass::Rogue)	{ UnitClass = "Energy:"; }
						else if (RACEID == WoWClass::Warrior) { UnitClass = "Rage:"; }
						else { "Mana:"; }
						string UnitEnergyAndManaStr = UnitClass + Utils::GetEnergyOrMana(entity);
						const char* cUnitEnergyAndManaStr = UnitEnergyAndManaStr.c_str();
						window->DrawList->AddText(ImVec2(OPPos.x + 100, OPPos.y - 30.f), Colors.color, cUnitEnergyAndManaStr);
					}
				}

				if (Settings::Drawing::Lvl)
				{
					string UnitLevelstr = "LVL:" + std::to_string(entity->GetUnitLevel(1));
					const char* cUnitLevelstr = UnitLevelstr.c_str();
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 20.f), Colors.color, cUnitLevelstr);
				}
			}
		}
	}

	void Renderer::InitBeforeDrawing()
	{
			// Draw World through ImGui
		__try
		{
		
			if (!Settings::Drawing::Enabled)
				return;

			if (!LuaScript::ActivePlayer)
				return;

			for (auto& Object : LuaScript::Objects)
			{

				if (!Object->isValid())
					continue;

				int TypeID = (int)Object->GetType();
				if (!TypeID)
					continue;

				if (!TypeID == (int)TypeId::CGUnit || !TypeID == (int)TypeId::CGPlayer || !TypeID == (int)TypeId::CGActivePlayer || !TypeID == (int)TypeId::CGGameObject || !TypeID == (int)TypeId::CGCorpse)
					continue;

				if (!Utils::ValidCoord(Object))
					continue;

				if (TypeID == (int)TypeId::CGUnit || TypeID == (int)TypeId::CGPlayer || TypeID == (int)TypeId::CGActivePlayer)
				{
					if (!Object->sUnitField->Health > 0 && !Settings::Drawing::DrawDeadEntity)
						continue;
					if (Utils::IsFriendlyOrEnemy(Object) == Utils::IsFriendlyOrEnemy(LuaScript::ActivePlayer) && !Settings::Drawing::Ally)
						continue;
					if (Utils::IsFriendlyOrEnemy(Object) != Utils::IsFriendlyOrEnemy(LuaScript::ActivePlayer) && !Settings::Drawing::Enemy)
						continue;
				}
				if (TypeID == (int)TypeId::CGUnit && Settings::Drawing::Unit)
				{
					ImColor UnitColor;
					if (!Object->sUnitField->Health > 0 && !Settings::Drawing::DrawDeadEntity) {
						UnitColor = Settings::Drawing::CorpseColor.Color();
					}
					else {
						UnitColor = Settings::Drawing::UnitColor.Color(Object);
					}
					Renderer::DrawObjects(Object, UnitColor);
				}
				else if (TypeID == (int)TypeId::CGPlayer && Settings::Drawing::Player)
				{
					ImColor PlayerColor;
					PlayerColor = Settings::Drawing::PlayerColor.Color(Object);
					Renderer::DrawObjects(Object, PlayerColor);
				}
				else if (TypeID == (int)TypeId::CGActivePlayer && Settings::Drawing::LocalPlayer)
				{
					ImColor LocalplayerColor;
					LocalplayerColor = Settings::Drawing::LocalPlayerColor.Color(Object);
					Renderer::DrawObjects(Object, LocalplayerColor);
				}
				else if (TypeID == (int)TypeId::CGGameObject && Settings::Drawing::GameObject)
				{
					Renderer::DrawObjects(Object, Settings::Drawing::GameObjectColor.color);
				}
				else if (TypeID == (int)TypeId::CGCorpse && Settings::Drawing::Corpse)
				{
					ImColor UnitColor;
					if (!Object->sUnitField->Health > 0 && !Settings::Drawing::DrawDeadEntity) {
						UnitColor = Settings::Drawing::CorpseColor.Color();
					}
					else {
						UnitColor = Settings::Drawing::UnitColor.Color(Object);
					}
					Renderer::DrawObjects(Object, UnitColor);
				}
			}
		}
		__except (Utils::filterException(GetExceptionCode(), GetExceptionInformation())) {
			printf("[!] RenderClass Exception Caught!\n");
			Settings::bot::Refresh = true;
		}
	}


	void Renderer::EndScene()
	{
		InitBeforeDrawing();

		ImGuiWindow* windowGui = ImGui::GetCurrentWindow();
		windowGui->DrawList->PushClipRectFullScreen();

		windowGui->DrawList->AddText(ImVec2(5, 0), ImColor(0, 162, 232), "X-HOOK for World of warcraft");

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);

		

		if ((Globals::timeSinceEpochMillisec() - Globals::last_update) >= Globals::next_update_delta)
		{
		//	printf("Last Update: %i Next_update_delta %i \n", Globals::last_update, Globals::next_update_delta);
			Globals::next_update_delta = Globals::timeSinceEpochMillisec() + 1000;
			Globals::last_update = Globals::timeSinceEpochMillisec();
		//	printf("After Last Update: %i Next_update_delta %i \n", Globals::last_update, Globals::next_update_delta);

			if (!GameMethods::ObjMgrIsValid(0))
			{ }
			else
			{
				LuaScript::ReInitObjMgr(); // Loop ObjMgr
			}
			Globals::last_update = 0;
		}
	}
}
