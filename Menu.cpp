#include "Menu.h"

#define IM_ARRAYSIZE(_ARR)      ((int)(sizeof(_ARR)/sizeof(*_ARR)))

char ConfigNames[128] = "";
bool ColorPicker(float* col, bool alphabar)
{

    const int EDGE_SIZE = 200;
    const ImVec2 SV_PICKER_SIZE = ImVec2(EDGE_SIZE, EDGE_SIZE);
    const float SPACING = ImGui::GetStyle().ItemInnerSpacing.x;
    const float HUE_PICKER_WIDTH = 20.f;
    const float CROSSHAIR_SIZE = 7.0f;

    ImColor color(col[0], col[1], col[2]);
    bool value_changed = false;

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    ImVec2 picker_pos = ImGui::GetCursorScreenPos();

    float hue, saturation, value;
    ImGui::ColorConvertRGBtoHSV(color.Value.x, color.Value.y, color.Value.z, hue, saturation, value);

    ImColor colors[] = {
        ImColor(255, 0, 0),
        ImColor(255, 255, 0),
        ImColor(0, 255, 0),
        ImColor(0, 255, 255),
        ImColor(0, 0, 255),
        ImColor(255, 0, 255),
        ImColor(255, 0, 0)
    };

    for (int i = 0; i < 6; i++)
    {
        draw_list->AddRectFilledMultiColor(
            ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING, picker_pos.y + i * (SV_PICKER_SIZE.y / 6)),
            ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING + HUE_PICKER_WIDTH,
                picker_pos.y + (i + 1) * (SV_PICKER_SIZE.y / 6)),
            colors[i],
            colors[i],
            colors[i + 1],
            colors[i + 1]
        );
    }

    draw_list->AddLine(
        ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING - 2, picker_pos.y + hue * SV_PICKER_SIZE.y),
        ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING + 2 + HUE_PICKER_WIDTH, picker_pos.y + hue * SV_PICKER_SIZE.y),
        ImColor(255, 255, 255)
    );

    if (alphabar)
    {
        float alpha = col[3];

        draw_list->AddRectFilledMultiColor(
            ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * SPACING + HUE_PICKER_WIDTH, picker_pos.y),
            ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * SPACING + 2 * HUE_PICKER_WIDTH, picker_pos.y + SV_PICKER_SIZE.y),
            ImColor(0, 0, 0), ImColor(0, 0, 0), ImColor(255, 255, 255), ImColor(255, 255, 255)
        );

        draw_list->AddLine(
            ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * (SPACING - 2) + HUE_PICKER_WIDTH, picker_pos.y + alpha * SV_PICKER_SIZE.y),
            ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * (SPACING + 2) + 2 * HUE_PICKER_WIDTH, picker_pos.y + alpha * SV_PICKER_SIZE.y),
            ImColor(255.f - alpha, 255.f, 255.f)
        );
    }

    const ImU32 c_oColorBlack = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 1.f));
    const ImU32 c_oColorBlackTransparent = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 0.f));
    const ImU32 c_oColorWhite = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f));

    ImVec4 cHueValue(1, 1, 1, 1);
    ImGui::ColorConvertHSVtoRGB(hue, 1, 1, cHueValue.x, cHueValue.y, cHueValue.z);
    ImU32 oHueColor = ImGui::ColorConvertFloat4ToU32(cHueValue);

    draw_list->AddRectFilledMultiColor(
        ImVec2(picker_pos.x, picker_pos.y),
        ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
        c_oColorWhite,
        oHueColor,
        oHueColor,
        c_oColorWhite
    );

    draw_list->AddRectFilledMultiColor(
        ImVec2(picker_pos.x, picker_pos.y),
        ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
        c_oColorBlackTransparent,
        c_oColorBlackTransparent,
        c_oColorBlack,
        c_oColorBlack
    );

    float x = saturation * SV_PICKER_SIZE.x;
    float y = (1 - value) * SV_PICKER_SIZE.y;
    ImVec2 p(picker_pos.x + x, picker_pos.y + y);
    draw_list->AddLine(ImVec2(p.x - CROSSHAIR_SIZE, p.y), ImVec2(p.x - 2, p.y), ImColor(255, 255, 255));
    draw_list->AddLine(ImVec2(p.x + CROSSHAIR_SIZE, p.y), ImVec2(p.x + 2, p.y), ImColor(255, 255, 255));
    draw_list->AddLine(ImVec2(p.x, p.y + CROSSHAIR_SIZE), ImVec2(p.x, p.y + 2), ImColor(255, 255, 255));
    draw_list->AddLine(ImVec2(p.x, p.y - CROSSHAIR_SIZE), ImVec2(p.x, p.y - 2), ImColor(255, 255, 255));

    ImGui::InvisibleButton("saturation_value_selector", SV_PICKER_SIZE);

    if (ImGui::IsItemActive() && ImGui::GetIO().MouseDown[0])
    {
        ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

        if (mouse_pos_in_canvas.x < 0)
            mouse_pos_in_canvas.x = 0;
        else if (mouse_pos_in_canvas.x >= SV_PICKER_SIZE.x - 1)
            mouse_pos_in_canvas.x = SV_PICKER_SIZE.x - 1;

        if (mouse_pos_in_canvas.y < 0)
            mouse_pos_in_canvas.y = 0;
        else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
            mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

        value = 1 - (mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1));
        saturation = mouse_pos_in_canvas.x / (SV_PICKER_SIZE.x - 1);
        value_changed = true;
    }

    // hue bar logic
    ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SPACING + SV_PICKER_SIZE.x, picker_pos.y));
    ImGui::InvisibleButton("hue_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

    if (ImGui::GetIO().MouseDown[0] && (ImGui::IsItemHovered() || ImGui::IsItemActive()))
    {
        ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

        if (mouse_pos_in_canvas.y < 0)
            mouse_pos_in_canvas.y = 0;
        else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
            mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

        hue = mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1);
        value_changed = true;
    }

    if (alphabar)
    {
        ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SPACING * 2 + HUE_PICKER_WIDTH + SV_PICKER_SIZE.x, picker_pos.y));
        ImGui::InvisibleButton("alpha_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

        if (ImGui::GetIO().MouseDown[0] && (ImGui::IsItemHovered() || ImGui::IsItemActive()))
        {
            ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

            if (mouse_pos_in_canvas.y < 0)
                mouse_pos_in_canvas.y = 0;
            else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
                mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

            float alpha = mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1);
            col[3] = alpha;
            value_changed = true;
        }
    }

    color = ImColor::HSV(hue >= 1 ? hue - 10 * 1e-6 : hue, saturation > 0 ? saturation : 10 * 1e-6, value > 0 ? value : 1e-6);
    col[0] = color.Value.x;
    col[1] = color.Value.y;
    col[2] = color.Value.z;

    bool widget_used;
    ImGui::PushItemWidth((alphabar ? SPACING + HUE_PICKER_WIDTH : 0) + SV_PICKER_SIZE.x + SPACING + HUE_PICKER_WIDTH - 2 * ImGui::GetStyle().FramePadding.x);
    widget_used = alphabar ? ImGui::ColorEdit4("", col) : ImGui::ColorEdit3("", col);
    ImGui::PopItemWidth();

    float new_hue, new_sat, new_val;
    ImGui::ColorConvertRGBtoHSV(col[0], col[1], col[2], new_hue, new_sat, new_val);

    if (new_hue <= 0 && hue > 0)
    {
        if (new_val <= 0 && value != new_val)
        {
            color = ImColor::HSV(hue, saturation, new_val <= 0 ? value * 0.5f : new_val);
            col[0] = color.Value.x;
            col[1] = color.Value.y;
            col[2] = color.Value.z;
        }
        else if (new_sat <= 0)
        {
            color = ImColor::HSV(hue, new_sat <= 0 ? saturation * 0.5f : new_sat, new_val);
            col[0] = color.Value.x;
            col[1] = color.Value.y;
            col[2] = color.Value.z;
        }
    }

    return value_changed | widget_used;
}
bool ColorPicker4(float col[4])
{
    return ColorPicker(col, true);
}

struct ColorListVar
{
    const char* name;
    union
    {
        ColorVar* colorVarPtr;
        HealthColorVar* healthColorVarPtr;
    };
    enum
    {
        COLORVAR_TYPE,
        HEALTHCOLORVAR_TYPE
    } type;

    ColorListVar(const char* name, ColorVar* ptr)
    {
        this->name = name;
        this->colorVarPtr = ptr;
        this->type = COLORVAR_TYPE;
    }

    ColorListVar(const char* name, HealthColorVar* ptr)
    {
        this->name = name;
        this->healthColorVarPtr = ptr;
        this->type = HEALTHCOLORVAR_TYPE;
    }
};

ColorListVar colors[] = {
    { "UI Main", &Settings::UI::mainColor },
    { "UI Body", &Settings::UI::bodyColor },
    { "UI Font", &Settings::UI::fontColor },
    { "UI accent", &Settings::UI::accentColor },
    { "Player", &Settings::Drawing::PlayerColor},
    { "LocalPlayer", &Settings::Drawing::LocalPlayerColor},
    { "Unit", &Settings::Drawing::UnitColor},
    { "Corpse", &Settings::Drawing::CorpseColor},
    { "GameObject", &Settings::Drawing::GameObjectColor},
    { "Object", &Settings::Drawing::ObjectColor},
    { "DynamicObject", &Settings::Drawing::DynamicObjectColor},
    { "Horde", &Settings::Drawing::HordeColor},
    { "Alliance", &Settings::Drawing::AllianceColor},
};
const char* colorNames[IM_ARRAYSIZE(colors)];

const char* NavPathType[] = { "Straight", "Random" };
const char* NavPathFlag[] = { "None", "PathCatmullRom", "ChaikinCurve" };
const char* GMenu::MenuTabs[] = { "Misc", "Config" };
const char* PlayerState[] = { "Ground", "Swimming", "UnderWaterWalking", "WaterWalking", "NoFallDmg", "CanFly", "DisableCollision", "Rooted", "Loggedoff", "DisableGravity" };

bool is_selected = false;
bool isItemselected = false;
bool GetList = false;
static WObject* selected = 0;
static WObject* selectedItem = 0;
static CGGuid* selected_index;


bool IsSelectingFood = false;
bool IsSelectingDrink = false;

bool Settings::UI::Windows::Menu::GetInvItems = false;

void GMenu::GetInventoryItem() {

    if (!Settings::UI::Windows::Menu::GetInvItems || Globals::Objects.empty())
        return;


    ImGui::Begin("Select Inventory item", &Settings::UI::Windows::Menu::GetInvItems);
    if (ImGui::BeginPopupContextItem()) // <-- This is using IsItemHovered()
    {
        if (ImGui::MenuItem("Close")) { Settings::UI::Windows::Menu::GetInvItems = false; }
        ImGui::EndPopup();
    }
    ImGui::PushItemWidth(-1);
    if (ImGui::ListBoxHeader("##ItemList", Globals::Objects.size())) {
        for (auto& [guid, Item] : Globals::Objects)
        {
            if (!Item->isValid())
                continue;
            if (!Item->IsItem())
                continue;

            isItemselected = (selectedItem == Item);

            if (ImGui::Selectable(Item->GetObjectName(), isItemselected)) {
                selectedItem = Item;
            }
        }
        ImGui::ListBoxFooter();
    }
    ImGui::PopItemWidth();

    ImGui::Separator();

    ImGui::NewLine();

    if (ImGui::Button("Add food", ImVec2(200, 0))) {
        Settings::UI::Windows::Menu::GetInvItems = false;
        Settings::bot::Grinding::FoodName = selectedItem->GetObjectName();
    }
    ImGui::SameLine();
    if (ImGui::Button("Add Drink", ImVec2(200, 0))) {
        Settings::bot::Grinding::DrinkName = selectedItem->GetObjectName();
        Settings::UI::Windows::Menu::GetInvItems = false;
    }


    ImGui::End();

}

        


void GMenu::Menu(bool p_open)
{

    static int page = 0;

    // We specify a default position/size in case there's no data in the .ini file. Typically this isn't required! We only do it to make the Demo applications a little more welcoming.
    ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

    if (!ImGui::Begin("XHOOK for World of Warcraft 2.5.2.41510", &p_open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))  {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }

    for (int i = 0; i < IM_ARRAYSIZE(GMenu::MenuTabs); i++)
    {
        int distance = i == page ? 0 : i > page ? i - page : page - i;

        if (ImGui::Button(GMenu::MenuTabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(GMenu::MenuTabs) - 9, 0)))
            page = i;

        if (i < IM_ARRAYSIZE(GMenu::MenuTabs) - 1)
            ImGui::SameLine();
    }

    GetInventoryItem();

    switch (page)
    {
    case 0:
        ImGui::BeginChild("COL1", ImVec2(0, 0), true);
        {

            ImGui::Text("Misc");
            ImGui::BeginChild("MISC", ImVec2(0, 0), true);
            ImGui::Separator();

            ImGui::Columns(2, NULL, true);
            {
                ImGui::PushItemWidth(100);
                if (Globals::LocalPlayer)
                {
                    ImGui::Text("Hello Maikel233, LocalPlayer is located at: %p\n", Globals::LocalPlayer->Ptr());
                    //  ImGui::Text("Casting %i and %i", Globals::LocalPlayer->sUnitField->SpellID, Globals::LocalPlayer->GetSpellCastID());
                    ImGui::Text("Coordinates: X:%f Y:%f Z:%f R:%f MapID:%i", Globals::LocalPlayer->GetUnitPosition().x, Globals::LocalPlayer->GetUnitPosition().y, Globals::LocalPlayer->GetUnitPosition().z, Globals::LocalPlayer->GetFacing(), GameMethods::ClntObjMgr__GetMapId());
                    //   ImGui::Text("Current speed: %f", Globals::LocalPlayer->CurrentSpeed);
                    ImGui::Text("X:");
                    ImGui::SameLine();
                    ImGui::InputFloat(XorStr("##X"), &Settings::Hacks::Movement::NextPos.x, 10.01f, 0.0f, 2.0f);
                    ImGui::SameLine();
                    ImGui::Text("Y:");
                    ImGui::SameLine();
                    ImGui::InputFloat(XorStr("##Y"), &Settings::Hacks::Movement::NextPos.y, 10.01f, 3.0f, 2.0f);
                    ImGui::SameLine();
                    ImGui::Text("Z:");
                    ImGui::SameLine();
                    ImGui::InputFloat(XorStr("##Z"), &Settings::Hacks::Movement::NextPos.z, 10.01f, 1.0f, 2.0f);
                    ImGui::SameLine();
                    if (ImGui::Button("<="))
                    {
                        Settings::Hacks::Movement::TeleportBack = true;
                        WoW::Hacks::fakeTeleport(1);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Corpse"))
                    {
                        WoW::Hacks::GoToCorpse(1);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("=>"))
                    {
                        WoW::Hacks::fakeTeleport(1);
                    }

                    ImGui::PushItemWidth(478);

                    ImGui::Checkbox("NoFall & MultiJump", &Settings::Hacks::Movement::JumpState);
                    SetTooltip("Jump to a height altitude and use superslowfall to maintain altitude.\n Dont use this above water! Instant dc");
                    if (Settings::Hacks::Movement::JumpState) {
                        ImGui::Checkbox("Superslowfall", &Settings::Hacks::Movement::SuperSlowFall);
                        SetTooltip("Dont use this on ground level or above the water!");
                        ImGui::SliderInt("SlowFallValue", &Settings::Hacks::Movement::SuperSlowSleepTime, 0, 100, "SlowFall SleepTime %i");
                    }
                    else {
                        Settings::Hacks::Movement::SuperSlowFall = false;
                    }
                    ImGui::Combo("##PLAYERSTATETYPE", (int*)&Settings::Hacks::Movement::CurrentPlayerState, PlayerState, IM_ARRAYSIZE(PlayerState));
                    ImGui::SameLine();
                    ImGui::Checkbox("Playerstate", &Settings::Hacks::Movement::TogglePlayerState);
                    SetTooltip("This option freezes your current playerstate.\n Enable the option go in the water set playerstate to swimming. and now you're flying in air.\n");
                    //ImGui::NewLine();
                    //ImGui::SliderFloat("##WALKSPEED", &Settings::Hacks::Movement::max_walkspeed, 0, 9999, "Walk speed %0.3f");
                    //ImGui::SameLine();
                    //if (ImGui::Button("set##1")) {
                    //    Globals::LocalPlayer->WalkSpeed = Settings::Hacks::Movement::max_walkspeed;
                    //}
                    //SetTooltip("Warning!\nThis option will dc you if you go faster than normal!");
                    //ImGui::SliderFloat("##RUNSPEED", &Settings::Hacks::Movement::max_runspeed, -10, 10, "Run speed %0.3f");
                    //ImGui::SameLine();
                    //if (ImGui::Button("set##2")) {
                    //    Globals::LocalPlayer->RunForwardSpeed = Settings::Hacks::Movement::max_runspeed;
                    //};
                    //SetTooltip("Warning!\nThis option will dc you if you go faster than normal!\n Try increasing in small steps and test it out.");
                    ImGui::SliderFloat("##ROTATIONSPEED", &Settings::Hacks::Movement::player_rotationspeed, 0, 10, "Rotation speed %0.3f");
                    ImGui::SameLine();
                    if (ImGui::Button("set##3")) {
                        Globals::LocalPlayer->Player_rotationspeed = Settings::Hacks::Movement::player_rotationspeed;
                    }

                    ImGui::PopItemWidth();


                    ImGui::NextColumn();
                    {

                        ImGui::Checkbox("FishBot", &Settings::bot::fishing::Enabled);
                        ImGui::Checkbox("GrindBot", &Settings::bot::Grinding::Enabled);
                        SetTooltip("A simple grindbot\nSupported classes: Druid lvl 1-10!\nRequires mmaps and tiles else it the bot wont work!\n");
                        ImGui::SameLine();

                        ImGui::PushItemWidth(-1.0f);
                        if (Settings::bot::Grinding::Enabled) {
                            ImGui::NewLine();

                           // ImGui::InputText(XorStr("##FOOD"), Settings::bot::Grinding::FoodName, 30);
                            ImGui::Text("FoodName: %s", Settings::bot::Grinding::FoodName);
                            ImGui::SameLine();
                            if (ImGui::Button("Find##0")) {
                                Settings::UI::Windows::Menu::GetInvItems = true;
                            }
                            ImGui::Text("ManaName: %s", Settings::bot::Grinding::DrinkName);
                   

                            ImGui::SliderFloat("##RestHealthPercent", &Settings::bot::Grinding::mRestHealthPercent, 10, 100);
                            ImGui::SliderFloat("##RestManaPercent", &Settings::bot::Grinding::mRestManaPercent, 10, 100);

                            ImGui::Checkbox("SkinMobs", &Settings::bot::Grinding::SkinMobs);

                            if (!WoW::GrindBot::mobList.empty())
                            {
                                if (ImGui::ListBoxHeader("##TargettingList", WoW::GrindBot::mobList.size())) {
                                    ImGui::TextColored(ImColor(1.00f, 0.0f, 0.0f, 1.0f), "TargetList:");
                                    for (auto& npc : WoW::GrindBot::mobList) {
                                        ImGui::Text("%s", npc.c_str());
                                    }
                                    ImGui::ListBoxFooter();
                                }
                            }
              
                            if (!Globals::Objects.empty())
                            {
                                if (ImGui::ListBoxHeader("##MobList", Globals::Objects.size())) {
                                    for (auto& [guid, npc] : Globals::Objects)
                                    {
                                        if (!npc->isValid())
                                            continue;
                                        if (!npc->IsUnit())
                                            continue;                  
                                        if (npc->IsDead())
                                            continue;
                                        if (!Utils::ValidCoord(npc))
                                            continue;
                                        if (Utils::IsUnitEnemy(npc))
                                            continue;

                                        is_selected = (selected == npc);

                                        //TODO: 
                                        //Add color to the strings if they exist in moblist vector?
                                        if (ImGui::Selectable(npc->GetObjectName(), is_selected)) {
                                            selected = npc;
                                            selected_index = npc->GetGuid();
                                        }

                                        if (is_selected) {
                                            ImGui::SetItemDefaultFocus();
                                        }
                                    }
                                    ImGui::ListBoxFooter();
                                }
                            }
                                
                            ImGui::PopItemWidth();
                            ImGui::PushItemWidth(-1);
                            if (selected && !selected_index->isEmpty()) { /*Settings for each target->Name */
                                if (std::find(WoW::GrindBot::mobList.begin(), WoW::GrindBot::mobList.end(), selected->GetObjectName()) != WoW::GrindBot::mobList.end()) {
                                    if (ImGui::Button("Remove")) {
                                        WoW::GrindBot::mobList.erase(find(WoW::GrindBot::mobList.begin(), WoW::GrindBot::mobList.end(), selected->GetObjectName()));
                                    }
                                }
                                else {
                                    if (ImGui::Button("Add")) {
                                        WoW::GrindBot::mobList.push_back(selected->GetObjectName());
                                    }
                                }
                            }
                        }              
                            ImGui::PopItemWidth();
                    }

                    ImGui::Columns(1);
                    ImGui::Separator();
                    ImGui::Text("World");
                    ImGui::Separator();
                    ImGui::Columns(2, NULL, true);
                    {
                        ImGui::PushItemWidth(188);
                        ImGui::SliderFloat("##FOV", &Settings::Hacks::Camera::Camera_fov, 0, 10, "FOV: %0.3f");
                        ImGui::SameLine();
                        if (ImGui::Button("set##100"))
                        {
                            if (WoW::camera::GCamera == nullptr) WoW::camera::Init();
                            else
                                WoW::camera::GCamera->cameraptr->FOV = Settings::Hacks::Camera::Camera_fov;
                        }
                        ImGui::NewLine();
                        ImGui::SliderFloat("##ZOOMOUT", &Settings::Hacks::Camera::Camera_zoomout, 0, 100000, "Zoomout: %0.3f");
                        ImGui::SameLine();
                        if (ImGui::Button("set##101"))
                        {
                            if (WoW::camera::GCamera == nullptr) WoW::camera::Init();
                            else
                                WoW::camera::GCamera->cameraptr->Camera_zoomin = Settings::Hacks::Camera::Camera_zoomin;
                        }
                        ImGui::SliderFloat("##ZOOMIN", &Settings::Hacks::Camera::Camera_zoomin, 0, 100000, "Zoomin: %0.3f");
                        ImGui::SameLine();
                        if (ImGui::Button("set##103"))
                        {
                            if (WoW::camera::GCamera == nullptr) WoW::camera::Init();
                            else
                                WoW::camera::GCamera->cameraptr->Camera_zoomout = Settings::Hacks::Camera::Camera_zoomout;
                        }
                        ImGui::Checkbox("EntityViewer", &Settings::Drawing::EntityViewer::Enabled);
                        ImGui::PopItemWidth();
                    }

                    ImGui::NextColumn();
                    {
                        ImGui::Checkbox("Toggle ESP", &Settings::Drawing::Enabled);
                        ImGui::Checkbox("Lines", &Settings::Drawing::Lines);
                        ImGui::SameLine();
                        ImGui::Checkbox("Names", &Settings::Drawing::Names);
                        ImGui::SameLine();
                        ImGui::Checkbox("Lvl", &Settings::Drawing::Lvl);
                        ImGui::SameLine();
                        ImGui::Checkbox("Health", &Settings::Drawing::Health);
                        ImGui::SameLine();
                        ImGui::Checkbox("Energy & Mana", &Settings::Drawing::EnergyAndMana);
                        ImGui::SameLine();
                        ImGui::Checkbox("Race", &Settings::Drawing::Race);
                        ImGui::SameLine();
                        ImGui::Checkbox("Distance", &Settings::Drawing::Distance);
                        ImGui::SameLine();
                        ImGui::Checkbox("Waypoints", &Settings::Drawing::WayPoints);
                        ImGui::Text("Filter");
                        ImGui::Checkbox("LocalPlayer##1", &Settings::Drawing::LocalPlayer);
                        ImGui::SameLine();
                        ImGui::Checkbox("Players", &Settings::Drawing::Player);
                        ImGui::SameLine();
                        ImGui::Checkbox("Npc", &Settings::Drawing::Unit);
                        ImGui::SameLine();
                        ImGui::Checkbox("Corpse##2", &Settings::Drawing::Corpse);
                        ImGui::SameLine();
                        ImGui::Checkbox("GObjects", &Settings::Drawing::GameObject);
                        ImGui::SameLine();
                        ImGui::Checkbox("DeadEntitys", &Settings::Drawing::DrawDeadEntity);
                        ImGui::SameLine();
                        ImGui::Checkbox("Objects", &Settings::Drawing::Object);
                        ImGui::SameLine();
                        ImGui::Checkbox("DObjects", &Settings::Drawing::DynamicObject);
                        ImGui::Checkbox("TraceLine", &Settings::Drawing::TraceLine);
                        ImGui::Checkbox("GuidString", &Settings::Drawing::GuidStr);

                        ImGui::Text("Hostile filter");
                        SetTooltip("Hostile filter\nThis will only render attackable Units/Players");
                        ImGui::Checkbox("Units#2", &Settings::Drawing::HostileUnits);
                        ImGui::SameLine();
                        ImGui::Checkbox("Players#2", &Settings::Drawing::HostilePlayers);
                        //ImGui::Text("Player faction filter:");
                        //SetTooltip("Player faction filter\n Will only draw Ally or Horde obj.");
                        //ImGui::Checkbox("Enemy", &Settings::Drawing::Enemy);
                        //ImGui::SameLine();
                        //ImGui::Checkbox("Friendly", &Settings::Drawing::Ally);


                        ImGui::Text("Radar:");
                        ImGui::PushItemWidth(-1);
                        ImGui::Checkbox("Enable", &Settings::Drawing::Radar::Enabled);
                        ImGui::NewLine();
                        ImGui::Text("Draws only Attackable units");
                        ImGui::Checkbox("Units#3", &Settings::Drawing::Radar::HostileUnits);
                        ImGui::SameLine();
                        ImGui::Checkbox("Players#3", &Settings::Drawing::Radar::HostilePlayers);

                        //Remove 2 of the 4???
                        //ImGui::Text("Player faction filter:");
                        //SetTooltip("Player faction filter\n Will only draw Ally or Horde obj.");
                        //ImGui::Checkbox("Enemy#1", &Settings::Drawing::Radar::Enemy);
                        //ImGui::SameLine();
                        //ImGui::Checkbox("Friendly#1", &Settings::Drawing::Radar::Ally);

                        ImGui::Text("Filter");
                        ImGui::Checkbox("Name", &Settings::Drawing::Radar::name);
                        ImGui::SameLine();
                        ImGui::Checkbox("Players##1", &Settings::Drawing::Radar::Player);
                        ImGui::SameLine();
                        ImGui::Checkbox("Npc##1", &Settings::Drawing::Radar::Unit);
                        ImGui::SameLine();
                        ImGui::Checkbox("Corpse##3", &Settings::Drawing::Radar::Corpse);
                        ImGui::SameLine();
                        ImGui::Checkbox("GObjects##1", &Settings::Drawing::Radar::GameObject);
                        ImGui::SameLine();
                        ImGui::Checkbox("DeadEntitys##1", &Settings::Drawing::Radar::DrawDeadEntity);
                        ImGui::SliderFloat("##RADARZOOM", &Settings::Drawing::Radar::zoom, 0.f, 100.f, "Zoom: %0.f");
                        ImGui::SliderFloat("##RADARICONSSCALE", &Settings::Drawing::Radar::iconsScale, 2, 16, "Icons Scale: %0.1f");
                        ImGui::PopItemWidth();

                    }
                }
                else
                {
                    ImGui::Text("Log into your character.");
                    if (WoWObjectManager::InGame() || GameMethods::ObjMgrIsValid(1))
                    {
                            WoWObjectManager::CycleObjects(true);                    
                    }
                }
                ImGui::EndChild();
                ImGui::EndChild();
            }
            break;
    case 1:
        // for this
       // ImGui::Text("Config tab");
        static int colorSelected = 0;
        for (int i = 0; i < IM_ARRAYSIZE(colors); i++)
            colorNames[i] = colors[i].name;

        ImGui::SetNextWindowSize(ImVec2(540, 325), ImGuiSetCond_Always);
        ImGui::Columns(2, NULL, true);
        {
            ImGui::PushItemWidth(-1);
            ImGui::ListBox("##COLORSELECTION", &colorSelected, colorNames, IM_ARRAYSIZE(colorNames), 12);
            ImGui::PopItemWidth();

            ImGui::Checkbox("Config window", &Configs::showWindow);
        }
        ImGui::NextColumn();
        {
            if (colors[colorSelected].type == ColorListVar::HEALTHCOLORVAR_TYPE)
            {
                ColorPicker4((float*)colors[colorSelected].healthColorVarPtr);
                ImGui::Checkbox("Rainbow", &colors[colorSelected].healthColorVarPtr->rainbow);
                SetTooltip("Makes the color an animated rainbow.");
                ImGui::SameLine();
                ImGui::Checkbox("Health-Based", &colors[colorSelected].healthColorVarPtr->hp);
                SetTooltip("Takes color from entity health, i.e. 100 - green, 50 - yellow.");
                ImGui::PushItemWidth(-1);
                ImGui::SliderFloat("##RAINBOWSPEED", &colors[colorSelected].healthColorVarPtr->rainbowSpeed, 0.f, 1.f, "Rainbow Speed: %0.3f");
                ImGui::PopItemWidth();
            }
            else
            {
                ColorPicker4((float*)colors[colorSelected].colorVarPtr);
                ImGui::Checkbox("Rainbow", &colors[colorSelected].colorVarPtr->rainbow);
                SetTooltip("Makes the color an animated rainbow.");
                ImGui::PushItemWidth(-1);
                ImGui::SliderFloat("##RAINBOWSPEED", &colors[colorSelected].colorVarPtr->rainbowSpeed, 0.f, 1.f, "Rainbow Speed: %0.3f");
            }
        }
        break;
        }
    }
    ImGui::End();
}