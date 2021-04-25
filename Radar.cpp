#include "Radar.h"

Vector2D WorldToRadar(const Vector3 location, const Vector3 origin, float Player_rotation, int width, float scale = 16.f)
{
	float x_diff = location.x - origin.x;
	float y_diff = location.y - origin.y;

	int iRadarRadius = width;

	float flOffset = atanf(y_diff / x_diff);
	flOffset *= 180;
	flOffset /= M_PI;

	if ((x_diff < 0) && (y_diff >= 0))
		flOffset = 180 + flOffset;
	else if ((x_diff < 0) && (y_diff < 0))
		flOffset = 180 + flOffset;
	else if ((x_diff >= 0) && (y_diff < 0))
		flOffset = 360 + flOffset;

	y_diff = -1 * (sqrtf((x_diff * x_diff) + (y_diff * y_diff)));
	x_diff = 0;

	flOffset = Player_rotation  - flOffset;

	flOffset *= M_PI;
	flOffset /= 180;

	float xnew_diff = x_diff * cosf(flOffset) - y_diff * sinf(flOffset);
	float ynew_diff = x_diff * sinf(flOffset) + y_diff * cosf(flOffset);

	xnew_diff /= scale;
	ynew_diff /= scale;

	xnew_diff = (iRadarRadius / 2) + (int)xnew_diff;
	ynew_diff = (iRadarRadius / 2) + (int)ynew_diff;

	// clamp x & y
	// FIXME: instead of using hardcoded "4" we should fix cliprect of the radar window
	if (xnew_diff > iRadarRadius)
		xnew_diff = iRadarRadius - 4;
	else if (xnew_diff < 4)
		xnew_diff = 4;

	if (ynew_diff > iRadarRadius)
		ynew_diff = iRadarRadius;
	else if (ynew_diff < 4)
		ynew_diff = 0;

	return Vector2D(xnew_diff, ynew_diff);
}

static void SquareConstraint(ImGuiSizeCallbackData* data)
{
	data->DesiredSize = ImVec2(max(data->DesiredSize.x, data->DesiredSize.y), max(data->DesiredSize.x, data->DesiredSize.y));
}

float RadianToDegree(float Rotation)
{
	return (float)(Rotation * (180 / PI));
}

void Radar::RenderWindow()
{
	if (!Settings::Drawing::Enabled)
		return;

	if (!Settings::Drawing::Radar::Enabled)
		return;

	if (Settings::UnitHelper::UnitInfos.empty())
		return;

	__try
	{

		ImGui::SetNextWindowSize(ImVec2(256, 256), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), SquareConstraint);

		if (ImGui::Begin("Radar", &Settings::Drawing::Radar::Enabled, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar))
		{
			ImDrawList* draw_list = ImGui::GetWindowDrawList();

			ImVec2 winpos = ImGui::GetWindowPos();
			ImVec2 winsize = ImGui::GetWindowSize();

			draw_list->AddLine(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y), ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y), ImColor(70, 70, 70, 255), 1.f);
			draw_list->AddLine(ImVec2(winpos.x, winpos.y + winsize.y * 0.5f), ImVec2(winpos.x + winsize.x, winpos.y + winsize.y * 0.5f), ImColor(70, 70, 70, 255), 1.f);

			draw_list->AddLine(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y * 0.5f), ImVec2(winpos.x, winpos.y), ImColor(90, 90, 90, 255), 1.f);
			draw_list->AddLine(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y * 0.5f), ImVec2(winpos.x + winsize.x, winpos.y), ImColor(90, 90, 90, 255), 1.f);


			WObject* localplayer = (WObject*)LuaScript::ActivePlayer;
			if (!localplayer)
			{
				ImGui::End();
				return;
			}

			float Player_rotation = RadianToDegree(localplayer->GetFacing());

			// draw localplayer
			draw_list->AddCircleFilled(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y * 0.5f), Settings::Drawing::Radar::iconsScale, ImColor(255, 255, 255, 255));

			float scale = Settings::Drawing::Radar::iconsScale;

			for (int i = 0; i < Settings::UnitHelper::UnitInfos.size(); i++)
			{

				if (!Settings::UnitHelper::UnitInfos.at(i).Entity)
					continue;

				WObject* entity = (WObject*)Settings::UnitHelper::UnitInfos.at(i).Entity;
				uintptr_t TypeID = *reinterpret_cast<TypeId*>(entity->Ptr() + Offsets::Type);

				if (!entity)
					continue;

				if (!entity->Ptr())
				{
				printf("[!] Radar class Invalid obj Ptr!\n");
				LuaScript::ReInitObjMgr(true);
				continue;
				}

				if (!TypeID)
					continue;

				if (!TypeID == CGUnit || !TypeID == CGPlayer || !TypeID == CGActivePlayer || !TypeID == CGGameObject)
					continue;

				if (!entity->GetUnitPosition().x < -10000000.000000 || !entity->GetUnitPosition().y < -10000000.000000 || !entity->GetUnitPosition().z < -10000000.000000)
				{
					printf("Invalid Player coordinates!\n");
					LuaScript::ReInitObjMgr(true);
					continue;
				}

				Vector2D screenpos = WorldToRadar(entity->GetUnitPosition(), localplayer->GetUnitPosition(), Player_rotation, winsize.x, Settings::Drawing::Radar::zoom);
				ImColor color;
				int shape = -1;

				if (Settings::Drawing::Radar::Unit && entity->GetType() == CGUnit)
				{

					if (!entity->GetType() == CGUnit)
						continue;

					WObject* Unit = (WObject*)entity;

					if ((!Unit->sUnitField->Health > 0) && !Settings::Drawing::Radar::DrawDeadEntity)
						continue;

					color = Settings::Drawing::Radar::UnitColor.Color(Unit);

					Vector3 localPos = localplayer->GetUnitPosition();
					Vector3 playerPos = Unit->GetUnitPosition();

					if (playerPos.z + 64.0f < localPos.z)
						shape = EntityShape_t::SHAPE_TRIANGLE_UPSIDEDOWN;
					else if (playerPos.z - 64.0f > localPos.z)
						shape = EntityShape_t::SHAPE_TRIANGLE;
					else
						shape = EntityShape_t::SHAPE_CIRCLE;

					//Fix arrow direction
					Vector3 forward = player->direction;

					Vector3 dirArrowVec = playerPos + (forward * 2 * Settings::Drawing::Radar::zoom * scale);
					Vector2D dirArrowPos = WorldToRadar(dirArrowVec, localplayer->GetUnitPosition(), Player_rotation, winsize.x, Settings::Drawing::Radar::zoom);
					Vector2D line = dirArrowPos - screenpos;

					float arrowWidth = scale;
					float arrowTheta = 45.f;
					float length = sqrtf(powf(line.x, 2.f) + powf(line.y, 2.f));

					Vector2D arrowBase = dirArrowPos - (arrowWidth / (2 * (tanf(arrowTheta) / 2) * length)) * line;
					Vector2D normal = Vector2D(-line.y, line.x);
					Vector2D left = arrowBase + arrowWidth / (2 * length) * normal;
					Vector2D right = arrowBase + -arrowWidth / (2 * length) * normal;

					draw_list->AddTriangleFilled(ImVec2(winpos.x + left.x, winpos.y + left.y),
						ImVec2(winpos.x + right.x, winpos.y + right.y),
						ImVec2(winpos.x + dirArrowPos.x, winpos.y + dirArrowPos.y),
						ImColor(230, 230, 230));

					if (Settings::Drawing::Radar::name)
					{
						draw_list->AddText(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y), color, Unit->GetObjectName());
					}
				}
				else if (entity->GetType() == CGPlayer)
				{
					if (!Settings::Drawing::Radar::Player)
						continue;

					if (!entity->GetType() == CGPlayer)
						continue;

					WObject* player = (WObject*)entity;

					if (player == localplayer)
						continue;

					if (!player->sUnitField->Health > 0 && !Settings::Drawing::Radar::DrawDeadEntity)
						continue;

					if (Utils::IsFriendlyOrEnemy(player) == Utils::IsFriendlyOrEnemy(localplayer) && !Settings::Drawing::Ally)
						continue;


					if (Utils::IsFriendlyOrEnemy(player) != Utils::IsFriendlyOrEnemy(localplayer) && !Settings::Drawing::Enemy)
						continue;

					color = Settings::Drawing::Radar::PlayerColor.Color(player);

					shape = EntityShape_t::SHAPE_TRIANGLE;
					if (Settings::Drawing::Radar::name)
					{
						draw_list->AddText(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y), color, player->GetObjectName());
					}
				}
				else if (entity->GetType() == CGGameObject)
				{
					if (!Settings::Drawing::Radar::GameObject)
						continue;

					if (!entity->GetType() == CGGameObject)
						continue;

					WObject* GameObj = (WObject*)entity;

					color = Settings::Drawing::Radar::GameObjectColor.Color();
					shape = EntityShape_t::SHAPE_SQUARE;
					if (Settings::Drawing::Radar::name)
					{
						draw_list->AddText(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y), color, GameObj->GetObjectName());
					}
				}
				switch (shape)
				{
				case EntityShape_t::SHAPE_CIRCLE:
					draw_list->AddCircleFilled(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y), scale, color);
					break;
				case EntityShape_t::SHAPE_SQUARE:
					draw_list->AddRectFilled(ImVec2(winpos.x + screenpos.x - scale, winpos.y + screenpos.y - scale),
						ImVec2(winpos.x + screenpos.x + scale, winpos.y + screenpos.y + scale),
						color, 0.0f, 0);
					break;
				case EntityShape_t::SHAPE_TRIANGLE:
					draw_list->AddTriangleFilled(ImVec2(winpos.x + screenpos.x + scale, winpos.y + screenpos.y + scale),
						ImVec2(winpos.x + screenpos.x - scale, winpos.y + screenpos.y + scale),
						ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y - scale),
						color);
					break;
				case EntityShape_t::SHAPE_TRIANGLE_UPSIDEDOWN:
					draw_list->AddTriangleFilled(ImVec2(winpos.x + screenpos.x - scale, winpos.y + screenpos.y - scale),
						ImVec2(winpos.x + screenpos.x + scale, winpos.y + screenpos.y - scale),
						ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y + scale),
						color);
					break;
				}
			}
			ImGui::End();
		}
	}
	__except (Utils::filterException(GetExceptionCode(), GetExceptionInformation())) {
		printf("[!] Radar Exception Caught!\n");
		LuaScript::ReInitObjMgr(true);
		ImGui::End();
	}
}

