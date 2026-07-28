#include "SilentAim.hpp"

bool Core::Features::cSilentAim::SilentAimInitialized;
std::uintptr_t Core::Features::cSilentAim::StartAddy;

void Core::Features::cSilentAim::InitializeSilentAim()
{
	StartAddy = g_Offsets.m_SilentAim;
	SilentAimHook = Mem.CreateCodeCave(500);

	if (!SilentAimHook)return;

	Mem.WriteBytes(SilentAimHook, SilentAimShell);

	OriginalFuncTable = Mem.ReadBytes(StartAddy, 38);

	Mem.HookJMP(StartAddy, SilentAimHook);
}

void Core::Features::cSilentAim::RestoreSilent()
{
	Mem.WriteBytes(StartAddy, OriginalFuncTable);
	Mem.FreeCave(SilentAimHook);
}

void Core::Features::cSilentAim::HookSilent()
{
	while (true)
	{
		if (g_Config.SilentAim.Enabled && GetForegroundWindow() != g_Variables.g_hCheatWindow)
		{
			if (!SilentAimInitialized) {
				InitializeSilentAim();
				if (!SilentAimHook) {
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					continue;
				}
				SilentAimInitialized = true;
			}

			CPed* Ped = Core::SDK::Game::GetClosestPed(g_Config.SilentAim.MaxDistance, g_Config.SilentAim.IgnoreNPCs, g_Config.SilentAim.OnlyVisible);

			D3DXVECTOR3 FinalPos = D3DXVECTOR3(0, 0, -1000);
			if (Ped) {
				D3DXVECTOR3 HeadPos = Ped->GetBonePosDefault(0);
				D3DXVECTOR2 HeadToScreen = Core::SDK::Game::WorldToScreen(HeadPos);

				if (Core::SDK::Game::IsOnScreen(HeadToScreen)) {
					float sdx = HeadToScreen.x - g_Variables.g_vGameWindowCenter.x;
					float sdy = HeadToScreen.y - g_Variables.g_vGameWindowCenter.y;
					int Fov = (int)sqrtf(sdx * sdx + sdy * sdy);
					if (Fov < g_Config.SilentAim.FOV) {
						bool Miss = g_Config.SilentAim.MissChance >= Utils::GenRandomInt(0, 100);
						FinalPos = Miss ? HeadPos + D3DXVECTOR3(0.0, 0.4, 0) : HeadPos + D3DXVECTOR3(0, 0, 0.08);
					}
				}
			}

			memcpy(SilentAimShell.data() + 3, &FinalPos.x, sizeof(float));
			memcpy(SilentAimShell.data() + 10, &FinalPos.y, sizeof(float));
			memcpy(SilentAimShell.data() + 17, &FinalPos.z, sizeof(float));

			uintptr_t BackAddress = (uintptr_t)(StartAddy + 0x26);
			memcpy(SilentAimShell.data() + 27, &BackAddress, sizeof(BackAddress));

			Mem.WriteBytes(SilentAimHook, SilentAimShell);

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		else {
			if (SilentAimInitialized) {
				RestoreSilent();
				SilentAimInitialized = false;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
}
