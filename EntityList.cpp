#include "EntityList.h"
#include <xutility>
std::string Race, Class, UnitHealth, ObjType, Faction;
const char* cRace;
const char* cClass;
const char* cUnitHealth;
const char* cObjType;
const char* cFaction;
ImColor ClassColor, FactionColor;
void ShowEntityList::GetObjectInfo(WObject* entity)
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
void ShowEntityList::RenderWindow()
{

	if (!Settings::Drawing::Enabled)
		return;

	if (!Settings::EntityViewer::Enabled)
		return;

	if (LuaScript::Objects.empty())
		return;

	//if (LuaScript::InGame())
	//	return;

	__try
	{

		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

		if (ImGui::Begin(XorStr("EntityViewer"), &Settings::EntityViewer::Enabled, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
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

			WObject* localplayer = (WObject*)LuaScript::ActivePlayer;
			if (!localplayer)
			{
				ImGui::End();
				return;
			}

			for (auto& Object : LuaScript::Objects)
			{
				if (!Object)
					continue;

		/*		if (Object == localplayer)
					continue;*/

				if (!Object->isValid())
					continue;


				int TypeID = (int)Object->GetType();
				if (!TypeID)
					continue;

				if (!TypeID == (int)TypeId::CGUnit || !TypeID == (int)TypeId::CGPlayer || !TypeID == (int)TypeId::CGActivePlayer || !TypeID == (int)TypeId::CGGameObject)
					continue;

				if (!Utils::ValidCoord(Object))
					continue;

				if (Utils::IsEntityAlive(Object))
					continue;

				if (Utils::IsFriendlyOrEnemy(Object) == Utils::IsFriendlyOrEnemy(localplayer) && !Settings::Drawing::Ally)
					continue;

				if (Utils::IsFriendlyOrEnemy(Object) != Utils::IsFriendlyOrEnemy(localplayer) && !Settings::Drawing::Enemy)
					continue;

				WObject* Obj = (WObject*)Object;

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
		Settings::bot::Refresh = true;
		ImGui::End();
	}
}
