#include "Camera.h"

namespace WoW
{
	//Camera init
	CameraMgr* camera::GCamera = nullptr;

	void camera::Init() {
		uintptr_t Camera = *reinterpret_cast<uintptr_t*>(Offsets::Base + Offsets::CameraMgr);
		auto* Camerasec = reinterpret_cast<CameraMgr*>(Camera);
		GCamera = Camerasec;

		std::cout << "[+] Camera addr:" << std::hex << Camerasec << std::endl;

		Settings::Hacks::Camera::Camera_fov = WoW::camera::GCamera->cameraptr->FOV;
		Settings::Hacks::Camera::Camera_zoomin = WoW::camera::GCamera->cameraptr->Camera_zoomin;
		Settings::Hacks::Camera::Camera_zoomout = WoW::camera::GCamera->cameraptr->Camera_zoomout;
	}

	Vector2 camera::WorldToScreenv2(Vector3 pos) {
		if (camera::GCamera == nullptr) camera::Init();
		CameraMgr* pCameraBase = *reinterpret_cast<CameraMgr**>(Offsets::Base + Offsets::CameraMgr);
		if (pCameraBase == nullptr || pCameraBase->cameraptr == nullptr) return Vector2{ 0,0 };
		auto pCamera = pCameraBase->cameraptr;

		ImGuiIO& io = ImGui::GetIO();
		RECT rc = { 0,0,io.DisplaySize.x,io.DisplaySize.y };
		Vector3 difference{ pos.x - pCamera->Camera_pos.x, pos.y - pCamera->Camera_pos.y, pos.z - pCamera->Camera_pos.z };

		float product =
			difference.x * pCamera->mat.M11 +
			difference.y * pCamera->mat.M12 +
			difference.z * pCamera->mat.M13;

		if (product < 0)
			return Vector2{ 0,0 };

		Matrix3x3 inverse = pCamera->mat.Inverse();
		Vector3 view{
			inverse.M11 * difference.x + inverse.M21 * difference.y + inverse.M31 * difference.z ,
			inverse.M12 * difference.x + inverse.M22 * difference.y + inverse.M32 * difference.z,
			inverse.M13 * difference.x + inverse.M23 * difference.y + inverse.M33 * difference.z
		};
		Vector3 camera{ -view.y, -view.z, view.x };
		Vector2 gameScreen{ (rc.right - rc.left) / 2.0f , (rc.bottom - rc.top) / 2.0f };
		Vector2 aspect{ gameScreen.x / tan(((pCamera->FOV * 55.0f) / 2.0f) * M_DEG2RAD) ,gameScreen.y / tan(((pCamera->FOV * 35.0f) / 2.0f) * M_DEG2RAD) };
		Vector2 screenPos{ gameScreen.x + camera.x * aspect.x / camera.z,gameScreen.y + camera.y * aspect.y / camera.z };

		if (screenPos.x < 0 || screenPos.y < 0 || screenPos.x > rc.right || screenPos.y > rc.bottom)
			return Vector2{ 0,0 };

		return screenPos;
	}

	bool camera::TraceLine(WObject* Object, Vector3 Target, IntersectFlags intersectFlags) {
		float distance = 1.0f;
		Vector3 start = Object->GetUnitPosition();
		Vector3 end = Target;
		Vector3 hit = Vector3(0.0, 0.0, 0.0);

		bool collision = GameMethods::Invoke<bool>(Offsets::Base + Offsets::WorldFrame_Intersect, GameMethods::Invoke<int64_t>(Offsets::Base + Offsets::WorldFrame_GetWorld), &end, &start, &hit, &distance, intersectFlags);

		if (hit.x != 0 && hit.y != 0) {
		}
		else {}
		return !collision;
	}
}
