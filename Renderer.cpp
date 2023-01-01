#include "Renderer.h"

namespace Draw
{
	Renderer::Renderer() {
	}
	Renderer::~Renderer(){
	}
	bool InitFont = false;
	void Renderer::Initialize() {
		if (!InitFont) { 
			ImGuiIO& io = ImGui::GetIO();
			m_pFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13);
			InitFont = true;
		}
	}

	void Renderer::BeginScene() {
		ImGuiIO& io = ImGui::GetIO();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
		ImGui::Begin("##Backbuffer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
	}

	void Renderer::DrawObjects(WObject* entity, HealthColorVar Colors) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window) {
			Vector2 OPPos = WoW::camera::WorldToScreenv2(entity->GetUnitPosition());
			Vector2 LPPos = WoW::camera::WorldToScreenv2(Globals::LocalPlayer->GetUnitPosition());

			if ((OPPos.x == NULL && OPPos.y == NULL) || LPPos.x == NULL && LPPos.y == NULL)
				return;

			if (Settings::Drawing::TraceLine && !WoW::camera::TraceLine(Globals::LocalPlayer, entity->GetUnitPosition(), IntersectFlags::LineOfSight))
				return;

			int TypeID = (int)entity->GetType();

			//Give Players made objects a color.
			if (*entity->GetOwner() == *Globals::LocalPlayer->GetGuid()) {
				Colors = ImColor(1.4f, 0.1f, 0.0f, 1.0f);
				window->DrawList->AddCircle(ImVec2(OPPos.x, OPPos.y), 10, Colors.color, 12, 1.0);
			}

			if (Settings::Drawing::Lines) {
				window->DrawList->AddLine(ImVec2(LPPos.x, LPPos.y), ImVec2(OPPos.x, OPPos.y), Colors.color, 1);
			}

			if (entity->IsUnit()) {

				if (Settings::Drawing::GuidStr) {
					string Guid = entity->GetGuid()->toString().c_str();
					const char* cstr = Guid.c_str();
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 30.f), Colors.color, cstr);
				}

				if (Settings::Drawing::Distance) {
					float Distance = Globals::LocalPlayer->GetUnitPosition().DistanceTo(entity->GetUnitPosition());
						string Distancestr = "Dist:" + std::to_string(Distance);
						const char* cDistancestr = Distancestr.c_str();
						window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 10.f), Colors.color, cDistancestr);
				}
			}

			if (Settings::Drawing::Names)
			{		
				if (entity->GetType() == TypeId::CGPlayer || TypeID == (int)TypeId::CGActivePlayer) {
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 40.f), Utils::GetClassColor(entity), entity->GetObjectName());				
				}
				else if (entity->IsUnit()) {
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 40.f), Colors.color, entity->GetObjectName());
				}
				else if (entity->IsGameObject()) {
					//if (!GameMethods::CGGameObject_C_IsLocked(entity)) {
				//	window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 40.f), Settings::Drawing::UnlockedGameObjectColor.Color(), entity->GetObjectName());
				//	}
				//	else {
						window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 40.f), Colors.color, entity->GetObjectName());
				//	}
				}			
			}	

			if ((TypeID == (int)TypeId::CGUnit) || TypeID == (int)TypeId::CGPlayer)
			{


				if (Globals::LocalPlayer->TargetGuid() == entity->GetGuid()) {
					Colors = ImColor(1.4f, 0.1f, 0.0f, 1.0f);
					window->DrawList->AddCircle(ImVec2(OPPos.x, OPPos.y), 10, Colors.color, 12, 1.0);
				}

				if (Settings::Drawing::Race) {
					string Race = Utils::GetRace(entity);
					const char* cRace = Race.c_str();
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y), Colors.color, cRace);
				}

				if (Settings::Drawing::Health) {
					string UnitHealthstr2 = "HP:" + Utils::GetHealth(entity);
					const char* cUnitHealthstr = UnitHealthstr2.c_str();
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 30.f), Colors.color, cUnitHealthstr);
				}

				if (Settings::Drawing::Lvl) {
					string UnitLevelstr = "LVL:" + std::to_string(entity->GetUnitLevel(1));
					const char* cUnitLevelstr = UnitLevelstr.c_str();
					window->DrawList->AddText(ImVec2(OPPos.x, OPPos.y - 20.f), Colors.color, cUnitLevelstr);
				}
				if (entity->IsPlayer()) {
					if (Settings::Drawing::EnergyAndMana)
					{

						string UnitEnergyAndManaStr = entity->getPowerString() + Utils::GetPower(entity);
						const char* cUnitEnergyAndManaStr = UnitEnergyAndManaStr.c_str();
						window->DrawList->AddText(ImVec2(OPPos.x + 100, OPPos.y - 30.f), Colors.color, cUnitEnergyAndManaStr);
					}
				}
			}

			if (Settings::Drawing::WayPoints) {
				for (int i = 0; i < nav::Waypoints.size(); i++) {
					Vector2 Waypoint_pos = WoW::camera::WorldToScreenv2(Vector3(nav::Waypoints[i].x, nav::Waypoints[i].y, nav::Waypoints[i].z));
					string UnitIdxstr = "Waypoint: " + std::to_string(i);
					const char* cUnitIdxstr = UnitIdxstr.c_str();
					window->DrawList->AddText(ImVec2(Waypoint_pos.x, Waypoint_pos.y), Colors.color, cUnitIdxstr);
				}
			}
		}
	}
	

	void Renderer::PreDraw()
	{
		// Draw World through ImGui
		__try
		{		
			if (!Settings::Drawing::Enabled)
				return;

			if (!Globals::LocalPlayer)
				return;

			for (auto& [guid, Object] : Globals::Objects)
			{

				if (!Object)
					continue;

				if (!Object->isValid())
					continue;

				int TypeID = (int)Object->GetType();
				if (!TypeID)
					continue;

				if (!TypeID == (int)TypeId::CGUnit || !TypeID == (int)TypeId::CGPlayer || !TypeID == (int)TypeId::CGGameObject || !TypeID == (int)TypeId::CGCorpse)
					continue;

				if (!Utils::ValidCoord(Object))
					continue;

				if (TypeID == (int)TypeId::CGUnit || TypeID == (int)TypeId::CGPlayer || TypeID == (int)TypeId::CGActivePlayer) {
					if (Object->IsDead() && !Settings::Drawing::DrawDeadEntity)
						continue;
					if (Utils::IsUnitEnemy(Object) && TypeID == (int)TypeId::CGUnit && !Settings::Drawing::HostileUnits)
						continue;
					if (Utils::IsUnitEnemy(Object) && TypeID == (int)TypeId::CGPlayer && !Settings::Drawing::HostileUnits)
						continue;	
				}

				if (Object->IsUnit() && Settings::Drawing::Unit) {
					ImColor UnitColor;
					if (Object->IsDead() && Settings::Drawing::DrawDeadEntity) {
						UnitColor = Settings::Drawing::CorpseColor.Color();
					}
					else {
						UnitColor = Settings::Drawing::UnitColor.Color(Object);
					}
					Renderer::DrawObjects(Object, UnitColor);
				}
				else if (Object->IsLocalPlayer() && Settings::Drawing::LocalPlayer) {
					ImColor LocalplayerColor;
					LocalplayerColor = Settings::Drawing::LocalPlayerColor.Color(Object);
					Renderer::DrawObjects(Globals::LocalPlayer, LocalplayerColor);
				}
				else if (Object->IsPlayer() && Settings::Drawing::Player) {
					ImColor PlayerColor;
					PlayerColor = Settings::Drawing::PlayerColor.Color(Object);
					Renderer::DrawObjects(Object, PlayerColor);
				}
				else if (Object->IsGameObject() && Settings::Drawing::GameObject) {
					Renderer::DrawObjects(Object, Settings::Drawing::GameObjectColor.color);
				}
				else if (Object->IsCorpse() && Settings::Drawing::Corpse) {
					ImColor UnitColor;
					if (Object->IsDead() && Settings::Drawing::DrawDeadEntity) {
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
			WoWObjectManager::CycleObjects(true);
		}
	}

	void Renderer::EndScene()
	{
		PreDraw();

		ImGuiWindow* windowGui = ImGui::GetCurrentWindow();
		windowGui->DrawList->PushClipRectFullScreen();

		pDll::LoopFuncs(); // Execute spell_c_ Must be executed from here e.se it will crash often!!!

		windowGui->DrawList->AddText(ImVec2(5, 0), ImColor(0, 162, 232), "X-HOOK for World of warcraft");

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);
	}
}
