#include "TeleportMenu.h"

int throwMessage = 0;
static int throwMessageCurrent = -1;
static char inputName[40];

static void SquareConstraint(ImGuiSizeCallbackData* data)
{
	data->DesiredSize = ImVec2(max(data->DesiredSize.x, data->DesiredSize.y), max(data->DesiredSize.x, data->DesiredSize.y));
}

void TeleportMenu::RenderWindow()
{

	if (!Settings::Hacks::Movement::TeleportMenu)
		return;

	if (!LuaScript::ActivePlayer)
		return;

		ImGui::SetNextWindowSize(ImVec2(256, 256), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), SquareConstraint);

		if (ImGui::Begin(XorStr("Teleport Menu - testphase"), &Configs::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar)) {

			ImGui::Columns(1);
			ImGui::PushItemWidth(500);
			ImGui::InputText("", inputName, sizeof(inputName));
			ImGui::PopItemWidth();
			ImGui::SameLine();
			if (ImGui::Button("Add"))
			{

				if (strlen(inputName) > 0)
				{		
					TeleporterInfo SET = TeleporterInfo(LuaScript::ActivePlayer->GetUnitPosition(), inputName, throwMessage);
					Settings::TeleportHelper::TeleporterInfos.push_back(SET);
					throwMessage++;


					const char* GetGhConfigDirectory = "C://Xhook//wow//Configs//TeleportHelper//";

					std::ostringstream path;

					path << GetGhConfigDirectory << Settings::Hacks::Movement::MAPID << "//";

					const char* GetPathInconst = path.str().c_str();


					CreateDirectoryA(GetPathInconst, nullptr);

					path << XorStr("teleconfig.json");
					Settings::SaveTeleporterInfo(path.str());

				}
				strcpy(inputName, "");
			}

			ImGui::PushItemWidth(550);

			auto lambda = [](void* data, int idx, const char** out_text)
			{
				*out_text = Settings::TeleportHelper::TeleporterInfos.at(idx).name.c_str();

				return *out_text != NULL;
			};
			ImGui::ListBox("", &throwMessageCurrent, lambda, NULL, Settings::TeleportHelper::TeleporterInfos.size(), 7);
			ImGui::PopItemWidth();

			ImGui::Columns(1);

			if (ImGui::Button("Teleport", ImVec2(ImGui::GetWindowWidth(), 30)))
			{

				if (Settings::TeleportHelper::TeleporterInfos.empty())
				{
					printf("Teleporter list is empty.\n");
				}

				for (auto TeleportInfo = Settings::TeleportHelper::TeleporterInfos.begin(); TeleportInfo != Settings::TeleportHelper::TeleporterInfos.end(); TeleportInfo++)
				{
					//	printf("Current message is :%i  Saved message is: %i", throwMessageCurrent, grenadeInfo->currmsg);
					if (throwMessageCurrent == TeleportInfo->currmsg)
					{
						LuaScript::ActivePlayer->GetUnitPositionModify = TeleportInfo->pos;
					}
				}
			}
			if (ImGui::Button("Replace", ImVec2(ImGui::GetWindowWidth(), 20)))
				if (throwMessageCurrent > -1 && (int)Settings::TeleportHelper::TeleporterInfos.size() > throwMessageCurrent)
				{

					int SavedthrowMessageCurrent = throwMessageCurrent;
					Settings::TeleportHelper::TeleporterInfos.erase(Settings::TeleportHelper::TeleporterInfos.begin() + throwMessageCurrent);

					std::string NoInput = "NO_INPUT_WAS_GIVEN"; // ZoneName
					if (strlen(inputName) <= 0)
					{
						TeleporterInfo SET = TeleporterInfo(LuaScript::ActivePlayer->GetUnitPosition(), NoInput, SavedthrowMessageCurrent);
						Settings::TeleportHelper::TeleporterInfos.push_back(SET);
					}
					else
					{
						TeleporterInfo SET = TeleporterInfo(LuaScript::ActivePlayer->GetUnitPosition(), inputName, throwMessage);
						Settings::TeleportHelper::TeleporterInfos.push_back(SET);
					}

					const char* GetGhConfigDirectory = "C://Xhook//wow//Configs//TeleportHelper//";

					std::ostringstream path;

					path << GetGhConfigDirectory << Settings::Hacks::Movement::MAPID << "//"; // <== Find...

					const char* GetPathInconst = path.str().c_str();

					CreateDirectoryA(GetPathInconst, nullptr);

					path << XorStr("teleconfig.json");
					Settings::SaveTeleporterInfo(path.str());

				}

			if (ImGui::Button("Manual Reload the maplist", ImVec2(ImGui::GetWindowWidth(), 20)))
			{
			//	ReloadTeleportListonmapchange(true);
			}

		}
		ImGui::End();
}