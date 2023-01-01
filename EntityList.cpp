#include "EntityList.h"

namespace Draw
{
	std::string Race, Class, UnitHealth, ObjType, Faction;
	const char* cRace;
	const char* cClass;
	const char* cUnitHealth;
	const char* cObjType;
	const char* cFaction;
	ImColor ClassColor, FactionColor;
	void EntityList::GetObjectInfo(WObject* entity)
	{
		if (!entity || !entity->Ptr())
			return;

		ClassColor = Utils::GetClassColor(entity);
		FactionColor = Utils::GetFactionColor(entity);

		Race = Utils::GetRace(entity);
		cRace = Race.c_str();

		Class = Utils::GetClass(entity);
		cClass = Class.c_str();

		UnitHealth = Utils::GetHealth(entity);
		cUnitHealth = UnitHealth.c_str();

		ObjType = Utils::GetObjType(entity);
		cObjType = ObjType.c_str();

		Faction = Utils::IsHordeOrAlliance(entity).c_str();
		cFaction = Faction.c_str();
	}
	static int currentPlayer = -1;
	void EntityList::RenderWindow()
	{

		if (!Settings::Drawing::Enabled)
			return;

		if (!Settings::Drawing::EntityViewer::Enabled)
			return;

		if (Globals::Objects.empty())
			return;

		if (!WoWObjectManager::InGame())
			return;

		__try
		{

			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

			if (ImGui::Begin(XorStr("EntityViewer"), &Settings::Drawing::EntityViewer::Enabled, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
			{
				ImGui::Columns(9);
				ImGui::Separator();

				ImGui::Text(XorStr("Type"));
				ImGui::NextColumn();

				ImGui::Text(XorStr("Name"));
				ImGui::NextColumn();

				ImGui::Text(XorStr("LVL"));
				ImGui::NextColumn();

				ImGui::Text(XorStr("HP"));
				ImGui::NextColumn();

				ImGui::Text(XorStr("Coords"));
				ImGui::NextColumn();

				ImGui::Text(XorStr("Class"));
				ImGui::NextColumn();

				ImGui::Text(XorStr("Race:"));
				ImGui::NextColumn();

				ImGui::Text(XorStr("Faction:"));
				ImGui::NextColumn();

				ImGui::Text(XorStr("Ptr"));
				ImGui::NextColumn();

				WObject* localplayer = (WObject*)Globals::LocalPlayer;
				if (!localplayer)
				{
					ImGui::End();
					return;
				}

				for (auto& [guid, Object] : Globals::Objects)
				{

					if (!Object)
						continue;

					if (!Object->isValid())
						continue;

					bool IsCorrectObj = false;

					if (Object->IsGameObject() || Object->IsUnit() || Object->IsPlayer() || Object->IsLocalPlayer()) {
						IsCorrectObj = true;
					}
					else {
						IsCorrectObj = false;
					}

					if (!IsCorrectObj)
						continue;


					if (!Utils::ValidCoord(Object))
						continue;

					WObject* Obj = (WObject*)Object;

					if (Utils::IsUnitEnemy(Obj) && Obj->IsUnit() && !Settings::Drawing::HostileUnits)
						continue;
					if (Utils::IsUnitEnemy(Obj) && Obj->IsPlayer() && !Settings::Drawing::HostileUnits)
						continue;

					GetObjectInfo(Obj);

					ImGui::Separator();

					ImGui::Text("%s", cObjType);
					ImGui::NextColumn();

					ImGui::Text("%s", Obj->GetObjectName());
					ImGui::NextColumn();

					ImGui::Text("%i", Obj->GetUnitLevel(1));
					ImGui::NextColumn();

					ImGui::Text("%s", cUnitHealth);
					ImGui::NextColumn();

					ImGui::Text("X:%fY:%fZ:%fR:%f", Obj->GetUnitPosition().x, Obj->GetUnitPosition().y, Obj->GetUnitPosition().z, Obj->GetFacing());
					ImGui::NextColumn();

					ImGui::TextColored(ClassColor, "%s", cClass);
					ImGui::NextColumn();

					ImGui::TextColored(FactionColor, "%s", cRace);
					ImGui::NextColumn();

					ImGui::TextColored(FactionColor, "%s", cFaction);
					ImGui::NextColumn();

					ImGui::Text("%p\n", Obj->Ptr());

					ImGui::NextColumn();

				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::End();
			}
		}
		__except (Utils::filterException(GetExceptionCode(), GetExceptionInformation())) {
			printf("[!] EntityList Exception Caught!\n");
			WoWObjectManager::CycleObjects(true);
			ImGui::End();
		}
	}
}
