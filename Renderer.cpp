#include "Renderer.h"
#include "Camera.h"
#include "Constants.h"
#include <imgui_internal.h>
#include <inttypes.h>
#include "Radar.h"

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
			printf("Drawing font: Arial.ttf\n");
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

	void Renderer::DrawObjects(WObject* Entity, HealthColorVar Color)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window)
		{
			Vector2 OPPos = wow::camera::WorldToScreenv2(Entity->GetUnitPosition());
			Vector2 LPPos = wow::camera::WorldToScreenv2(LuaScript::ActivePlayer->GetUnitPosition());

			if ((OPPos.x == NULL && OPPos.y == NULL) || LPPos.x == NULL && LPPos.y == NULL)
				return;

			int TypeID = Entity->GetType();

			if (Settings::Drawing::Lines)
			{
				window->DrawList->AddLine(ImVec2(LPPos.x, LPPos.y), ImVec2(OPPos.x, OPPos.y), Color.color, 1);
			}

			if (Settings::Drawing::Names)
			{
				if ((TypeID == CGUnit) || TypeID == CGPlayer || TypeID == CGGameObject)
				{
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 40.f), Color.color, Entity->GetObjectName());
				}
			}

			if ((TypeID == CGUnit) || TypeID == CGPlayer)
			{
				if (Settings::Drawing::Distance)
				{
					float Distance = LuaScript::ActivePlayer->GetUnitPosition().Distance(Entity->GetUnitPosition());
					string Distancestr = "Meters: " + std::to_string(Distance);
					const char* cDistancestr = Distancestr.c_str();
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 10.f), Color.color, cDistancestr);
				}

				if (Settings::Drawing::Race)
				{
					string Race = Utils::GetRace(Entity);
					const char* cRace = Race.c_str();
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y), Color.color, cRace);
				}

				if (Settings::Drawing::Health)
				{
					string UnitHealthstr2 = "HP:" + Utils::GetHealth(Entity);
					const char* cUnitHealthstr = UnitHealthstr2.c_str();
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 30.f), Color.color, cUnitHealthstr);
				}
				if (Settings::Drawing::Lvl)
				{
					string UnitLevelstr = "LVL: " + std::to_string(Entity->GetUnitLevel(1));
					const char* cUnitLevelstr = UnitLevelstr.c_str();
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 20.f), Color.color, cUnitLevelstr);
				}
			}

		}
	}


	void Renderer::InitBeforeDrawing()
	{
		__try
		{
			// Draw World through ImGui

			if (!Settings::Objectmanager::ObjMgrisdone)
				return;

			if (!Settings::Drawing::Enabled)
				return;

			if (Settings::UnitHelper::UnitInfos.empty())
				return;

			for (int i = 0; i < Settings::UnitHelper::UnitInfos.size(); i++)
			{
				if (!Settings::UnitHelper::UnitInfos.at(i).Entity)
				{
					printf("[!] Invalid obj Ptr!\n");
					LuaScript::ReInitObjMgr(true);
					continue;
				}

				WObject* Object = (WObject*)Settings::UnitHelper::UnitInfos.at(i).Entity;
				uintptr_t TypeID = *reinterpret_cast<TypeId*>(Object->Ptr() + Offsets::Type);

				if (!Object)
					continue;

				if (!Object->Ptr())
				{
					printf("[!] Invalid Player Ptr!\n");
					LuaScript::ReInitObjMgr(true);
					continue;
				}

				if (!TypeID)
					continue;

				if (!TypeID == CGUnit || !TypeID == CGPlayer || !TypeID == CGActivePlayer || !TypeID == CGGameObject || !TypeID == CGCorpse)
					continue;

				if (!Object->GetUnitPosition().x < -10000000.000000 || !Object->GetUnitPosition().y < -10000000.000000 || !Object->GetUnitPosition().z < -10000000.000000)
				{
					printf("[!] Invalid Player coordinates!\n");
					LuaScript::ReInitObjMgr(true);
					continue;
				}

				if (TypeID == CGUnit || TypeID == CGPlayer || TypeID == CGActivePlayer)
				{
					if (!Object->sUnitField->Health > 0 && !Settings::Drawing::DrawDeadEntity)
						continue;
					if (Utils::IsFriendlyOrEnemy(Object) == Utils::IsFriendlyOrEnemy(LuaScript::ActivePlayer) && !Settings::Drawing::Ally)
						continue;
					if (Utils::IsFriendlyOrEnemy(Object) != Utils::IsFriendlyOrEnemy(LuaScript::ActivePlayer) && !Settings::Drawing::Enemy)
						continue;
				}
				if (TypeID == CGCorpse && Settings::Drawing::Corpse)
				{
					Renderer::DrawObjects(Object, Settings::Drawing::CorpseColor.color);
				}
				else if (TypeID == CGActivePlayer && Settings::Drawing::LocalPlayer)
				{
					ImColor LocalplayerColor;
					LocalplayerColor = Settings::Drawing::LocalPlayerColor.Color(Object);
					Renderer::DrawObjects(Object, LocalplayerColor);
				}
				else if (TypeID == CGPlayer && Settings::Drawing::Player)
				{
					ImColor PlayerColor;
					PlayerColor = Settings::Drawing::PlayerColor.Color(Object);
					Renderer::DrawObjects(Object, PlayerColor);
				}
				else if (TypeID == CGUnit && Settings::Drawing::Unit)
				{
					ImColor UnitColor;
					if (!Object->sUnitField->Health > 0 && !Settings::Drawing::DrawDeadEntity)
					{
						UnitColor = Settings::Drawing::CorpseColor.Color();
					}
					else
					{
						UnitColor = Settings::Drawing::UnitColor.Color(Object);
					}

					Renderer::DrawObjects(Object, UnitColor);
				}
				else if (TypeID == CGGameObject && Settings::Drawing::GameObject)
				{
					Renderer::DrawObjects(Object, Settings::Drawing::GameObjectColor.color);
				}
			}
		}
		__except (Utils::filterException(GetExceptionCode(), GetExceptionInformation())) {
			printf("[!] Render class Exception Caught!\n");
			LuaScript::ReInitObjMgr(true);
		}
	}

	/*float GMISlandos[3]; float GMPoss[2];
	GMISlandos[0] = 16222.099609;
	GMISlandos[1] = 16252.099609;
	GMISlandos[2] = 12.581040;*/
	void Renderer::EndScene()
	{
		if (!Settings::Objectmanager::ObjMgrisdone)
		{
			GMenu::InitObjmgr();
		}

		InitBeforeDrawing();

		ImGuiWindow* windowGui = ImGui::GetCurrentWindow();
		windowGui->DrawList->PushClipRectFullScreen();

		windowGui->DrawList->AddText(ImVec2(5, 0), ImColor(0, 162, 232), "XHOOK for World of warcraft");

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);
	}
}