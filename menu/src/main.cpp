#pragma once
#include <Gui/Overlay/Overlay.hpp>
#include <Includes/Includes.hpp>
#include <Core/SDK/Memory.hpp>
#include <Includes/Utils.hpp>
#include <Core/SDK/SDK.hpp>
#include <Core/Core.hpp>
#include <Gui/gui.hpp>
#include <winternl.h>
#include <windows.h>
#include <dwmapi.h>
#include <tchar.h>
#include <vector>
#include <regex>

#include <Security/AntiCrack.hpp>
#include <Auth/KeyAuthApp.hpp>
#include <Includes/CustomWidgets/Custom.hpp>
#include <Core/Features/Exploits/ResourceList.hpp>

using namespace Core;


int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	// --- ADICIONE ESTAS 3 LINHAS ---
	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	// -------------------------------

	if (!Mem.GetMaxPrivileges(GetCurrentProcess()))
	{
		// Agora você verá este erro no console:
		std::cout << xorstr("[Error]: Failed GetMaxPrivileges\n");
		std::cin.get(); // O programa vai esperar você apertar Enter antes de fechar
		return 0;
	}

	while (!g_Variables.g_hGameWindow)
	{

		g_Variables.g_hGameWindow = FindWindowA(xorstr("grcWindow"), nullptr);
		if (g_Variables.g_hGameWindow)
		{
			auto WindowInfo = Utils::GetWindowPosAndSize(g_Variables.g_hGameWindow);
			g_Variables.g_vGameWindowSize = WindowInfo.second;
			g_Variables.g_vGameWindowPos = WindowInfo.first;
			g_Variables.g_vGameWindowCenter = { g_Variables.g_vGameWindowSize.x / 2, g_Variables.g_vGameWindowSize.y / 2 };
			break;
		}

		Sleep(250);

	}

	GetWindowThreadProcessId(g_Variables.g_hGameWindow, &g_Variables.ProcIdFiveM);
	//std::thread(&AntiCrack::DoProtect).detach();
	Core::SetupOffsets();
	Auth::InitializeKeyAuth();
	std::thread(&Auth::SessionKeepAlive).detach();

	Gui::cOverlay.Render();

	return 0;
}

std::string hwid;
