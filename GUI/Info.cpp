#include "info.h"
#include <math.h>

int Settings::bot::TotalUnits, Settings::bot::TotalPlayers, Settings::bot::TotalObjects;
std::string Status = "Off";
std::string Status2 = "Off";
namespace Draw
{

	void InfoWindow::RenderWindow()
	{

        float ms = 1.0f;
        float result = 1.0f;;

        float_t* Offset = reinterpret_cast<float*>(Offsets::Base + Offsets::World_GetFramerateOffset);
        ms = GameMethods::WorldGetFrameRate(Offset);
        result = *reinterpret_cast<float*>(Offsets::Base + Offsets::World_GetFrameRateResult);

        if (ms >= 0.001) {
            result = 1000.0 / ms;
        }

        //TIME
        time_t t = std::time(nullptr);
        std::ostringstream time;
        time << std::put_time(std::localtime(&t), ("%H:%M:%S"));

        std::ostringstream format;
        format << "XHOOK.XYZ"
            << " | " << ("Units: ") << Settings::bot::TotalUnits
            << " | " << ("Players: ") << Settings::bot::TotalPlayers
            << " | " << ("Objects: ") << Settings::bot::TotalObjects
            << " | " << (result != 0.0f ? static_cast<int>(result) : 0) << " ms"
            << " | " << (ms != 0.0f ? static_cast<int>(ms) : 0) << " fps"
            << " | " << (time.str().data());


        float windowWidth = ImGui::CalcTextSize(format.str().c_str()).x + 16.f;
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - windowWidth, 0), ImGuiSetCond_Always);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.0f);
        if (ImGui::Begin("Watermark", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar /*| ImGuiWindowFlags_ShowBorders*/ | ImGuiWindowFlags_NoTitleBar))
        {
            ImGui::Text("%s", format.str().c_str());
            ImGui::End();
        }


        ImGui::PopStyleVar();
    }
}
