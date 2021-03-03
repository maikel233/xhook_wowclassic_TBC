#include "Camera.h"
#include "Vector.h"
#include "Settings/Settings.h"
//#include <D3DX11.h>
//#include <DirectXMath.h>

namespace wow
{

	/*
	void camera::GetMatrix(float* out)
	{
		uintptr_t CameraPtr = Offsets::Base + Offsets::CameraMgr;
		uintptr_t ptr = *reinterpret_cast<uintptr_t*>(CameraPtr);
		uintptr_t CameraBase = *reinterpret_cast<uintptr_t*>(ptr + Offsets::CameraPtr);
		float* CameraMatrix = reinterpret_cast<float*>(CameraBase + 0x1C);
		memcpy(out, CameraMatrix, 36);
	}

	void camera::GetPosition(float* out)
	{
		uintptr_t CameraPtr = Offsets::Base + Offsets::CameraMgr;
		uintptr_t ptr = *reinterpret_cast<uintptr_t*>(CameraPtr);
		uintptr_t CameraBase = *reinterpret_cast<uintptr_t*>(ptr + Offsets::CameraPtr);
		float* CameraOrigin = reinterpret_cast<float*>(CameraBase + 0x10);
		memcpy(out, CameraOrigin, 3 * sizeof(float));
	}

	float camera::GetFieldOfView(void)
	{
		uintptr_t CameraPtr = Offsets::Base + Offsets::CameraMgr;
		uintptr_t ptr = *reinterpret_cast<uintptr_t*>(CameraPtr);
		uintptr_t CameraBase = *reinterpret_cast<uintptr_t*>(ptr + Offsets::CameraPtr);
		return *reinterpret_cast<float*>(CameraBase + 0x40);
	}
	*/

	Vector2 camera::WorldToScreenv2(Vector3 pos)
	{
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
		Vector2 aspect{ gameScreen.x / tan(((pCamera->FOV * 55.0f) / 2.0f) * M_DEG2RAD) ,gameScreen.y / tan(((pCamera->FOV * 35.0f) / 2.0f) * M_DEG2RAD) }; // 2.0f <- pCamera->FOV.
		Vector2 screenPos{ gameScreen.x + camera.x * aspect.x / camera.z,gameScreen.y + camera.y * aspect.y / camera.z };

		if (screenPos.x < 0 || screenPos.y < 0 || screenPos.x > rc.right || screenPos.y > rc.bottom)
			return Vector2{ 0,0 };

		return screenPos;
	}
}
