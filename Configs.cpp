#include "Settings/Settings.h"
#include "Configs.h"
#include "XorStr.h"

int Settings::UI::Windows::Config::sizeX = 185;
int Settings::UI::Windows::Config::sizeY = 250;
int Settings::UI::Windows::Config::posX = 185;
int Settings::UI::Windows::Config::posY = 250;
bool Settings::UI::Windows::Config::open = false;
bool Settings::UI::Windows::Config::reload = false;

namespace ImGui
{

	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	inline bool Combo(const char* label, int* currIndex, std::vector<std::string>& values) {
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

	inline bool
		ListBox(const char* label, int* currIndex, std::vector<std::string>& values, int height_in_items = -1) {
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size(), height_in_items);
	}
}

std::string folder, file;
CHAR path[MAX_PATH];
char buf[128] = "";
class ConfigFile
{
public:

	ConfigFile(const char* path, const char* name)
	{
		this->path = path;
		this->name = name;
	}

public:

	std::string path, name;
};

std::vector<ConfigFile> getAllConfInFolder(std::string path);
std::vector<std::string> getAllConf();

//static std::vector<std::string> configItems = getAllConf();
//static int configItemCurrent = -1;

std::vector<ConfigFile> getAllConfInFolder(std::string path)
{
	std::vector<ConfigFile> configs;
	std::string search_path = path + "*.ini";
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				std::string fPath = path + fd.cFileName;

				std::string tmp_f_name(fd.cFileName);
				size_t pos = tmp_f_name.find(".");
				std::string fName = (std::string::npos == pos) ? tmp_f_name : tmp_f_name.substr(0, pos);

				ConfigFile newConf(fPath.c_str(), fName.c_str());
				configs.push_back(newConf);
			}
		} while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}
	return configs;
}

std::vector<std::string> getAllConf()
{
	folder = std::string(path) + "C:\\XHOOK\\wow\\Configs\\";

	std::vector<ConfigFile> confFiles = getAllConfInFolder(folder);
	std::vector<std::string> confs;

	for (auto config = confFiles.begin(); config != confFiles.end(); config++)
		confs.push_back(config->name);

	std::sort(confs.begin(), confs.end());

	return confs;
}

bool Configs::showWindow = false;
#define IM_ARRAYSIZE(_ARR)      ((int)(sizeof(_ARR)/sizeof(*_ARR)))
void Configs::RenderWindow() {
	if (Settings::UI::Windows::Config::reload) {
		ImGui::SetNextWindowPos(ImVec2(Settings::UI::Windows::Config::posX, Settings::UI::Windows::Config::posY),
			ImGuiSetCond_Always);
		ImGui::SetNextWindowSize(ImVec2(Settings::UI::Windows::Config::sizeX, Settings::UI::Windows::Config::sizeY),
			ImGuiSetCond_Always);
		Settings::UI::Windows::Config::reload = false;
		Configs::showWindow = Settings::UI::Windows::Config::open;
	}
	else {
		ImGui::SetNextWindowPos(ImVec2(Settings::UI::Windows::Config::posX, Settings::UI::Windows::Config::posY),
			ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(Settings::UI::Windows::Config::sizeX, Settings::UI::Windows::Config::sizeY),
			ImGuiSetCond_FirstUseEver);
	}
	if (!Configs::showWindow) {
		Settings::UI::Windows::Config::open = false;
		return;
	}



	if (ImGui::Begin(XorStr("Configs"), &Configs::showWindow,
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar)) {
		Settings::UI::Windows::Config::open = true;
		ImVec2 temp = ImGui::GetWindowSize();
		Settings::UI::Windows::Config::sizeX = (int)temp.x;
		Settings::UI::Windows::Config::sizeY = (int)temp.y;
		temp = ImGui::GetWindowPos();
		Settings::UI::Windows::Config::posX = (int)temp.x;
		Settings::UI::Windows::Config::posY = (int)temp.y;

		static std::vector<std::string> configItems = getAllConf();
		static int configItemCurrent = -1;

		if (ImGui::Button("Refresh"))
		{
			configItems = getAllConf();
		}

		ImGui::SameLine();
		if (ImGui::Button(XorStr("Save"))) {
			if (configItems.size() > 0 &&
				(configItemCurrent >= 0 && configItemCurrent < (int)configItems.size())) {


				folder = std::string(path) + "C:\\XHOOK\\wow\\Configs\\";
				file = std::string(folder) + configItems[configItemCurrent] + ".ini";
				//	remove(file.c_str());
				Settings::LoadDefaultsOrSave(file);
			}
		}

		ImGui::SameLine();
		if (ImGui::Button(XorStr("Remove"))) {
			if (configItems.size() > 0 &&
				(configItemCurrent >= 0 && configItemCurrent < (int)configItems.size())) {

				folder = std::string(path) + "C:\\XHOOK\\wow\\Configs\\";
				file = std::string(folder) + configItems[configItemCurrent] + ".ini";
				remove(file.c_str());

				configItems = getAllConf();
				configItemCurrent = -1;
			}
		}

		static char buf[128] = "";
		ImGui::PushItemWidth(138);
		ImGui::InputText("", buf, IM_ARRAYSIZE(buf));
		ImGui::PopItemWidth();

		ImGui::SameLine();
		if (ImGui::Button(XorStr("Add")) && strlen(buf) > 0) {
			folder = std::string(path) + "C:\\XHOOK\\wow\\Configs\\";
			file = std::string(folder) + std::string(buf) + ".ini";
			Settings::LoadDefaultsOrSave(file);
		}

		ImGui::PushItemWidth(178);
		if (ImGui::ListBox("", &configItemCurrent, configItems, 10)) {
			folder = std::string(path) + "C:\\XHOOK\\wow\\Configs\\";
			file = std::string(folder) + configItems[configItemCurrent] + ".ini";

			Settings::LoadConfig(file);

		}
		ImGui::PopItemWidth();

		ImGui::End();
	}
}