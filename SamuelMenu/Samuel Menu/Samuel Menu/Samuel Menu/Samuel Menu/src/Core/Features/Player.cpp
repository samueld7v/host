#include "Player.hpp"

namespace
{
	uintptr_t GetCurrentNoClipModelInfo()
	{
		auto localPed = Core::SDK::Pointers::pLocalPlayer;
		if (!localPed)
			return 0;

		if (localPed->IsInVehicle())
		{
			CVehicle* currentVehicle = localPed->GetLastVehicle();
			return currentVehicle ? currentVehicle->GetModelInfo() : 0;
		}

		return localPed->GetModelInfo();
	}

	float g_NoClipMagicValue = 0.0f;
	uintptr_t g_NoClipModelInfo = 0;
	bool g_NoClipModelPatched = false;

	void RestoreNoClipModelInfo()
	{
		uintptr_t restoreModelInfo = GetCurrentNoClipModelInfo();
		if (!restoreModelInfo)
			restoreModelInfo = g_NoClipModelInfo;

		if (g_NoClipModelPatched && restoreModelInfo)
		{
			Core::Mem.Write<float>(restoreModelInfo + 0x2C, g_NoClipMagicValue);
		}

		g_NoClipMagicValue = 0.0f;
		g_NoClipModelInfo = 0;
		g_NoClipModelPatched = false;
	}

	void PatchNoClipModelInfo(uintptr_t modelInfo)
	{
		if (!modelInfo)
		{
			RestoreNoClipModelInfo();
			return;
		}

		if (g_NoClipModelPatched && g_NoClipModelInfo == modelInfo)
			return;

		RestoreNoClipModelInfo();

		g_NoClipMagicValue = Core::Mem.Read<float>(modelInfo + 0x2C);
		Core::Mem.Write<float>(modelInfo + 0x2C, 0.0f);

		g_NoClipModelInfo = modelInfo;
		g_NoClipModelPatched = true;
	}
}

namespace Core
{
	namespace Features
	{
		namespace Player
		{
			float GetNoClipSpeedValue(float level)
			{
				if (level <= 1.5f)
					return 0.25f;
				if (level <= 2.5f)
					return 0.60f;
				if (level <= 3.5f)
					return 1.10f;
				if (level <= 4.5f)
					return 1.80f;
				if (level <= 5.5f)
					return 2.60f;
				return 4.00f;
			}

			void ResetNoClip()
			{
				RestoreNoClipModelInfo();
			}

			void NoClip()
			{
				auto localPed = Core::SDK::Pointers::pLocalPlayer;
				if (!localPed)
				{
					ResetNoClip();
					return;
				}

				const bool isInVehicle = localPed->IsInVehicle();
				CVehicle* currentVehicle = isInVehicle ? localPed->GetLastVehicle() : nullptr;

				uintptr_t targetAddr = currentVehicle
					? reinterpret_cast<uintptr_t>(currentVehicle)
					: reinterpret_cast<uintptr_t>(localPed);
				uintptr_t targetNav = currentVehicle
					? currentVehicle->GetNavigation()
					: localPed->GetNavigation();
				uintptr_t targetModel = currentVehicle
					? currentVehicle->GetModelInfo()
					: localPed->GetModelInfo();

				if (!targetAddr || !targetNav || !targetModel)
				{
					ResetNoClip();
					return;
				}

				PatchNoClipModelInfo(targetModel);

				D3DXVECTOR3 pos = Mem.Read<D3DXVECTOR3>(targetAddr + 0x90);
				if (pos == D3DXVECTOR3(0, 0, 0))
					return;

				uintptr_t cam = Mem.Read<uintptr_t>(Core::SDK::Pointers::pCamGamePlayDirector + 0x2C0);
				if (!cam)
					return;

				D3DXVECTOR3 view = Mem.Read<D3DXVECTOR3>(cam + 0x3D0);
				if (view == D3DXVECTOR3(0, 0, 0))
					view = Mem.Read<D3DXVECTOR3>(cam + 0x40);

				if (view == D3DXVECTOR3(0, 0, 0))
					return;

				D3DXVec3Normalize(&view, &view);

				D3DXVECTOR3 viewFlat(view.x, view.y, 0.f);
				if (D3DXVec3LengthSq(&viewFlat) > 0.0001f)
					D3DXVec3Normalize(&viewFlat, &viewFlat);
				else
					viewFlat = D3DXVECTOR3(0.f, 1.f, 0.f);

				D3DXVECTOR3 rightFull;
				D3DXVECTOR3 worldUp(0.f, 0.f, 1.f);
				D3DXVec3Cross(&rightFull, &view, &worldUp);
				if (D3DXVec3LengthSq(&rightFull) < 0.001f)
					rightFull = D3DXVECTOR3(1.f, 0.f, 0.f);
				else
					D3DXVec3Normalize(&rightFull, &rightFull);

				D3DXVECTOR3 upFull;
				D3DXVec3Cross(&upFull, &rightFull, &view);
				D3DXVec3Normalize(&upFull, &upFull);

				static const D3DXVECTOR3 zeroVector(0.0f, 0.0f, 0.0f);

				static auto lastTime = std::chrono::high_resolution_clock::now();
				auto currentTime = std::chrono::high_resolution_clock::now();
				float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
				lastTime = currentTime;

				if (deltaTime > 0.1f)
					deltaTime = 0.016f;

				float speed = GetNoClipSpeedValue(g_Config.Player.NoClipSpeed) * deltaTime * 60.0f;
				if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					speed *= 1.8f;

				D3DXVECTOR3 move(0.f, 0.f, 0.f);

				if (GetAsyncKeyState('W') & 0x8000) move += view * speed;
				if (GetAsyncKeyState('S') & 0x8000) move -= view * speed;
				if (GetAsyncKeyState('D') & 0x8000) move += rightFull * speed;
				if (GetAsyncKeyState('A') & 0x8000) move -= rightFull * speed;
				if (GetAsyncKeyState(VK_SPACE) & 0x8000) move += worldUp * (speed / 2.5f);
				if (GetAsyncKeyState(VK_CONTROL) & 0x8000) move -= worldUp * (speed / 2.5f);

				D3DXVECTOR3 newPos = pos + move;
				Mem.Write<D3DXVECTOR3>(targetAddr + 0x90, newPos);
				Mem.Write<D3DXVECTOR3>(targetNav + 0x50, newPos);

				if (!isInVehicle)
				{
					Mem.Write<D3DXVECTOR3>(targetAddr + 0x320, zeroVector);
					Mem.Write<D3DXVECTOR3>(targetAddr + 0x330, zeroVector);
					Mem.Write<D3DXVECTOR3>(targetAddr + 0x300, zeroVector);

					if (g_Config.Player.NoClipMode != 1)
						localPed->SetLocalAlpha(160);
					else
						localPed->SetLocalAlpha(255);
				}
				else
				{
					Mem.Write<D3DXVECTOR3>(targetAddr + 0x320, zeroVector);
				}

				Mem.Write<D3DXVECTOR3>(targetAddr + 0x60, rightFull);
				Mem.Write<D3DXVECTOR3>(targetAddr + 0x70, view);
				Mem.Write<D3DXVECTOR3>(targetAddr + 0x80, upFull);

				Mem.Write<D3DXVECTOR3>(targetNav + 0x20, rightFull);
				Mem.Write<D3DXVECTOR3>(targetNav + 0x30, view);
				Mem.Write<D3DXVECTOR3>(targetNav + 0x40, upFull);

				if (!isInVehicle)
				{
					uint8_t rotFlag = Mem.Read<uint8_t>(targetAddr + 0x83C);
					Mem.Write<uint8_t>(targetAddr + 0x83C, rotFlag & ~0x40u);

					uint8_t updFlag = Mem.Read<uint8_t>(targetAddr + 0x848);
					Mem.Write<uint8_t>(targetAddr + 0x848, updFlag | 1u);
				}
			}

			void ApplyPlayerFlags() {
				auto localPed = Core::SDK::Pointers::pLocalPlayer;
				if (!localPed) return;
				auto playerInfo = localPed->GetPlayerInfo();
				if (!playerInfo) return;

				uint32_t flags = Core::Mem.Read<uint32_t>((uintptr_t)playerInfo + 0x270);

				if (g_Config.Player.SuperJump && (GetAsyncKeyState(VK_SPACE) & 0x8000))
					flags |= (1 << 14);

				if (g_Config.Player.BeastJump)
					flags |= (1 << 28);

				if (g_Config.Player.ExplosiveFist)
					flags |= (1 << 13);
				else
					flags &= ~(1 << 13);

				if (g_Config.Player.FireAmmo)
					flags |= (1 << 12);
				else
					flags &= ~(1 << 12);

				Core::Mem.Write<uint32_t>((uintptr_t)playerInfo + 0x270, flags);
			}

			void DoubleShot() {
				auto localPed = Core::SDK::Pointers::pLocalPlayer;
				if (!localPed) return;
				auto weapon_manager = localPed->GetWeaponManager();
				if (!weapon_manager) return;
				auto weapon_info = weapon_manager->GetWeaponInfo();
				if (!weapon_info) return;
				Core::Mem.Write<uint32_t>((uintptr_t)weapon_info + 0x013C, g_Config.Player.DoubleShot ? 1 : 0);
			}

			void NoReload() {
				auto localPed = Core::SDK::Pointers::pLocalPlayer;
				if (!localPed) return;
				auto weapon_manager = localPed->GetWeaponManager();
				if (!weapon_manager) return;
				auto weapon_info = weapon_manager->GetWeaponInfo();
				if (!weapon_info) return;

				if (g_Config.Player.NoReloadEnabled) {
					Core::Mem.Write<float>((uintptr_t)weapon_info + 0x134, 1000.f);

					uint64_t currentWeapon = Core::Mem.Read<uint64_t>((uintptr_t)weapon_manager + 0x60);
					if (currentWeapon) {
						uint64_t ammoInfo = Core::Mem.Read<uint64_t>(currentWeapon + 0x8);
						if (ammoInfo)
							Core::Mem.Write<uint32_t>(ammoInfo + 0x18, 999);
					}
				}
				else {
					Core::Mem.Write<float>((uintptr_t)weapon_info + 0x134, 1.f);
				}
			}
		}
	}
}
