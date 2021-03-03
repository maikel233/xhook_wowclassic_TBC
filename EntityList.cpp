#include "EntityList.h"

std::string Race, UnitHealth, ObjType, Faction;
const char* cRace;
const char* cUnitHealth;
const char* cObjType;
const char* cFaction;

void ShowEntityList::GetObjectInfo(WObject* entity)
{
	if (!entity || !entity->Ptr())
		return;

	Race = Utils::GetRace(entity);
	cRace = Race.c_str();

	UnitHealth = Utils::GetHealth(entity);
	cUnitHealth = UnitHealth.c_str();

	ObjType = Utils::GetObjType(entity->GetType());
	cObjType = ObjType.c_str();

	Faction = Utils::IsHordeOrAlliance(entity).c_str();
	cFaction = Faction.c_str();
}

void ShowEntityList::RenderWindow()
{
	if (!Settings::EntityViewer::Enabled)
		return;

	if (Settings::UnitHelper::UnitInfos.empty())
		return;

	__try
	{

		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

		if (ImGui::Begin(XorStr("EntityViewer"), &Settings::EntityViewer::Enabled, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
		{
			ImGui::Columns(7);
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

			ImGui::Text(XorStr("Race:"));
			ImGui::NextColumn();

			ImGui::Text(XorStr("Faction:"));
			ImGui::NextColumn();

			WObject* localplayer = (WObject*)LuaScript::ActivePlayer;
			if (!localplayer)
			{
				ImGui::End();
				return;
			}

			for (int i = 0; i < Settings::UnitHelper::UnitInfos.size(); i++)
			{

				if (!Settings::UnitHelper::UnitInfos.at(i).Entity)
					continue;

				WObject* Object = (WObject*)Settings::UnitHelper::UnitInfos.at(i).Entity;
				uintptr_t TypeID = *reinterpret_cast<TypeId*>(Object->Ptr() + Offsets::Type);

				if (!Object || !Object->Ptr())
					continue;

				if (!TypeID)
					continue;

				if (!TypeID == CGUnit || !TypeID == CGPlayer || !TypeID == CGActivePlayer || !TypeID == CGGameObject || !TypeID == CGCorpse)
					continue;

				if (!Object->GetUnitPosition().x < -10000000.000000 || !Object->GetUnitPosition().y < -10000000.000000 || !Object->GetUnitPosition().z < -10000000.000000)
				{
					printf("[!] Invalid player coordinates!\n");
					LuaScript::ReInitObjMgr(true);
					continue;
				}

				WObject* entity = Object;

				if (!entity)
					continue;

				if (entity == localplayer)
					continue;

				if (!TypeID == CGUnit || !TypeID == CGPlayer || !TypeID == CGActivePlayer || !TypeID == CGGameObject)
					continue;

				if (Utils::IsEntityAlive(entity))
					continue;

				if (Utils::IsFriendlyOrEnemy(entity) == Utils::IsFriendlyOrEnemy(localplayer) && !Settings::Drawing::Ally)
					continue;

				if (Utils::IsFriendlyOrEnemy(entity) != Utils::IsFriendlyOrEnemy(localplayer) && !Settings::Drawing::Enemy)
					continue;

				//A bypass for the Try/catch func
				GetObjectInfo(entity);

				ImGui::Separator();

				ImGui::Text("%s", cObjType);
				ImGui::NextColumn();

				ImGui::Text("%s", entity->GetObjectName());
				ImGui::NextColumn();

				ImGui::Text("%i", entity->GetUnitLevel(1));
				ImGui::NextColumn();

				ImGui::Text("%s", cUnitHealth);
				ImGui::NextColumn();

				ImGui::Text("X: %f Y: %f Z: %f R: %f", entity->GetUnitPosition().x, entity->GetUnitPosition().y, entity->GetUnitPosition().z, entity->GetFacing());
				ImGui::NextColumn();

				ImGui::Text("%s", cRace);
				ImGui::NextColumn();

				ImGui::Text("%s", cFaction);
				ImGui::NextColumn();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::End();
		}
	}
	__except (Utils::filterException(GetExceptionCode(), GetExceptionInformation())) {
		printf("[!] EntityList Exception Caught!\n");
		LuaScript::ReInitObjMgr(true);
		ImGui::End();
	}
}
