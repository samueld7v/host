#include "Gui.hpp"

#include <Includes/CustomWidgets/Custom.hpp>
#include <Includes/CustomWidgets/WaterMarks.hpp>
#include <Includes/CustomWidgets/Notify.hpp>

#include <Gui/Pages/Combat.hpp>
#include <Gui/Pages/Visuals.hpp>
#include <Gui/Pages/Local.hpp>
#include <Gui/Pages/Exploits.hpp>
#include <Gui/Pages/World.hpp>
#include <Gui/Pages/Settings.hpp>
#include <Gui/Pages/Resoucer.hpp>
#include <Gui/Pages/Login.hpp>
#include <Gui/Pages/Teste.hpp>
#include <Core/Features/Exploits/Exploits.hpp>
#include <Core/Features/Esp.hpp>

int PauseLoop;
inline std::mutex DrawMtx;

float accent_color[4] = {
	255 / 255.f, // r
	255 / 255.f, // g
	255 / 255.f, // b
	1.f          // a
};

static inline void SendNotify(const std::string& msg, time_t duration = 2000) {
	NotifyManager::Send(msg, duration);
}

static void ApplyNoClip(bool enable) {
	g_Config.Player.NoClipEnabled = enable;
	if (Core::SDK::Pointers::pLocalPlayer) {
		auto lp = Core::SDK::Pointers::pLocalPlayer;
		if (!enable) Features::Player::ResetNoClip();
		if (!lp->IsInVehicle()) {
			if (lp->pNetObject()) {
				if (g_Config.Player.NoClipMode == 0 || g_Config.Player.NoClipMode == 2)
					lp->pNetObject()->SetInvisible(enable);
				else
					lp->pNetObject()->SetInvisible(false);
			}
		}
		else if (!enable || g_Config.Player.NoClipMode == 1) {
			if (lp->pNetObject())
				lp->pNetObject()->SetInvisible(false);
		}
		Features::Exploits::SetInvisibleLocal(enable && g_Config.Player.NoClipMode == 2);
	}
}

static void ApplyAntiAimFlags(bool enable) {
	if (Core::SDK::Pointers::pLocalPlayer) {
		Core::SDK::Pointers::pLocalPlayer->SetConfigFlag(CPED_CONFIG_FLAG_DisablePlayerLockon, enable);
		Core::SDK::Pointers::pLocalPlayer->SetConfigFlag(CPED_CONFIG_FLAG_AllowPlayerLockOnIfFriendly, enable);
		Core::SDK::Pointers::pLocalPlayer->SetConfigFlag(CPED_CONFIG_FLAG_TreatAsFriendlyForTargetingAndDamage, enable);
	}
}

static void DrawSplashLogo() {
	if (!g_Variables.Logo) return;
	ImVec2 size = g_MenuInfo.LoginSize;
	float logoW = 200.f, logoH = 100.f;
	ImGui::SetCursorPos(ImVec2(size.x / 2.f - logoW / 2.f, size.y / 2.f - logoH / 2.f - 30.f));
	ImGui::Image((void*)g_Variables.Logo, ImVec2(logoW, logoH));
}

void Gui::Rendering()
{
	static bool wasLogged = false;
	ImVec2 currentSize = g_MenuInfo.IsLogged ? g_MenuInfo.MenuSize : g_MenuInfo.LoginSize;

	if (g_MenuInfo.IsLogged != wasLogged) {
		ImGui::SetNextWindowPos(g_Variables.g_vGameWindowSize / 2 - currentSize / 2);
		wasLogged = g_MenuInfo.IsLogged;
	}

	ImGui::SetNextWindowSize(currentSize);

	if (!PauseLoop) { ImGui::SetNextWindowPos(g_Variables.g_vGameWindowSize / 2 - currentSize / 2); PauseLoop++; }

	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, g_MenuInfo.MenuAlpha);
	ImGui::Begin(" ", nullptr, ImGuiWindowFlags);
	ImGui::PushFont(g_Variables.m_FontNormal);
	{
		Custom::DrawBackground(g_MenuInfo.IsLogged);
		if (g_MenuInfo.IsLogged)
		{


			// Header dimensions
			float headerHeight = 45.f; // Reduced header height
			float tabSpacing = 15.f;
			
			// Measure total width to align correctly
			ImFont* font = g_Variables.m_FontNormal; // Mesmo aumento da fonte
			float font_size = font->FontSize + 2.f;
			float totalTabsWidth = 0.f;
			
			const char* tabs[] = { "Combat", "Visual", "Misc", "World", "Exploits", "Config" };
			const char* tabIcons[] = { ICON_FA_CROSSHAIRS, ICON_FA_EYE, ICON_FA_USER, ICON_FA_GLOBE, ICON_FA_BOMB, ICON_FA_GEAR };
			ImGui::PushFont(font);
			for(int i = 0; i < 6; i++) {
				ImVec2 text_size = font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, tabs[i]);
				ImVec2 icon_size = g_Variables.FontAwesomeSolid->CalcTextSizeA(16.f, FLT_MAX, 0.0f, tabIcons[i]);
				totalTabsWidth += text_size.x + 16.f + icon_size.x + 6.f;
			}
			ImGui::PopFont();
			totalTabsWidth += tabSpacing * 5;

			// Align tabs to the RIGHT with 20px margin
			float tabsStartX = g_MenuInfo.MenuSize.x - totalTabsWidth - 20.f;
			ImGui::SetCursorPos(ImVec2(tabsStartX, (headerHeight - 36.f) / 2.f));

			ImGui::BeginGroup();
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(tabSpacing, 0)); // Horizontal spacing
			{
				if (Custom::Tab(tabs[0], g_MenuInfo.Combat == g_MenuInfo.iTabCount, tabIcons[0]))
				{
					g_MenuInfo.iTabCount = g_MenuInfo.Combat;
				}
				ImGui::SameLine();
				if (Custom::Tab(tabs[1], g_MenuInfo.Visuals == g_MenuInfo.iTabCount, tabIcons[1]))
				{
					g_MenuInfo.iTabCount = g_MenuInfo.Visuals;
				}
				ImGui::SameLine();
				if (Custom::Tab(tabs[2], g_MenuInfo.Local == g_MenuInfo.iTabCount, tabIcons[2]))
				{
					g_MenuInfo.iTabCount = g_MenuInfo.Local;
				}
				ImGui::SameLine();
				if (Custom::Tab(tabs[3], g_MenuInfo.World == g_MenuInfo.iTabCount, tabIcons[3]))
				{
					g_MenuInfo.iTabCount = g_MenuInfo.World;
				}
				ImGui::SameLine();
				if (Custom::Tab(tabs[4], g_MenuInfo.Exploits == g_MenuInfo.iTabCount, tabIcons[4]))
				{
					g_MenuInfo.iTabCount = g_MenuInfo.Exploits;
				}
				ImGui::SameLine();
				if (Custom::Tab(tabs[5], g_MenuInfo.Settings == g_MenuInfo.iTabCount, tabIcons[5]))
				{
					g_MenuInfo.iTabCount = g_MenuInfo.Settings;
				}

			}
			ImGui::PopStyleVar();
			ImGui::EndGroup();
		}

		g_MenuInfo.TabAlpha = ImClamp(g_MenuInfo.TabAlpha + (5.f * ImGui::GetIO().DeltaTime * (g_MenuInfo.iTabCount == g_MenuInfo.iCurrentPage ? 1.f : -1.f)), 0.f, 1.f);

		if (g_MenuInfo.TabAlpha == 0.f)
			g_MenuInfo.iCurrentPage = g_MenuInfo.iTabCount;

		ImGuiStyle* style = &ImGui::GetStyle();
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, g_MenuInfo.TabAlpha * style->Alpha);

		if (g_MenuInfo.IsLogged)
		{


			// Move content below header with padding
			ImGui::SetCursorPos(ImVec2(20, 75)); // Moved further down
			ImGui::BeginGroup();



			switch (g_MenuInfo.iCurrentPage)
			{

			case g_MenuInfo.Combat:
				Combat::Render();
				break;
			case g_MenuInfo.Visuals:
				Visuals::Render();
				break;
			case g_MenuInfo.Local:
				Local::Render();
				break;
			case g_MenuInfo.World:
				World::Render();
				break;
			case g_MenuInfo.Settings:
				Settings::Render();
				break;
			case g_MenuInfo.Resoucer:
				Resoucer::Render();
				break;
			case g_MenuInfo.Exploits:
				Teste::Render();
				break;

			}

			ImGui::EndGroup();
		}
		else
		{
			if (!g_MenuInfo.IsSplashFinished)
			{
				if (g_MenuInfo.SplashStartTime == 0)
					g_MenuInfo.SplashStartTime = GetTickCount();

				if (GetTickCount() - g_MenuInfo.SplashStartTime > 3000)
				{
					g_MenuInfo.IsSplashFinished = true;
				}

				DrawSplashLogo();

				ImVec2 size = g_MenuInfo.LoginSize;

				ImGui::PushFont(g_Variables.m_FontNormal);
				const char* text = "Connecting to Server";
				ImVec2 textSize = ImGui::CalcTextSize(text);

				float time = (float)ImGui::GetTime();
				float alpha = (sin(time * 4.f) + 1.f) * 0.5f; // Blinking effect
				
				ImGui::SetCursorPos(ImVec2(size.x / 2.f - textSize.x / 2.f, size.y / 2.f + 40.f));
				ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 0.3f + (alpha * 0.7f)), text);
				ImGui::PopFont();
			}
			else if (g_MenuInfo.is_injecting && !g_MenuInfo.IsSuccessSplashFinished)
			{
				if (g_MenuInfo.SuccessSplashStartTime == 0)
					g_MenuInfo.SuccessSplashStartTime = GetTickCount();

				if (GetTickCount() - g_MenuInfo.SuccessSplashStartTime > 4000)
				{
					g_MenuInfo.IsSuccessSplashFinished = true;
					g_MenuInfo.IsLogged = true;
				}

				DrawSplashLogo();

				ImVec2 size = g_MenuInfo.LoginSize;

				ImGui::PushFont(g_Variables.m_FontNormal);
				const char* text = "Preparing to inject";
				ImVec2 textSize = ImGui::CalcTextSize(text);

				ImGui::SetCursorPos(ImVec2(size.x / 2.f - textSize.x / 2.f, size.y / 2.f + 40.f));
				ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 0.8f), text);
				ImGui::PopFont();
			}
			else
			{
				Login::Render();
			}
		}

		ImGui::PopStyleVar();
		ImGui::PopFont();
	}
	ImGui::End();
	ImGui::PopStyleVar();


	HWND ActiveWindow = GetForegroundWindow();

	{
		std::lock_guard<std::mutex> Lock(DrawMtx);

		NotifyManager::Render();

		if (ActiveWindow == g_Variables.g_hGameWindow)
		{
			if (GetAsyncKeyState(g_Config.Player.GodModeKey) & 1)
			{
				g_Config.Player.EnableGodMode = !g_Config.Player.EnableGodMode;
				Core::SDK::Pointers::pLocalPlayer->SetGodMode(g_Config.Player.EnableGodMode);
				SendNotify(xorstr("GodMode has been ") + (std::string)(g_Config.Player.EnableGodMode ? xorstr("enabled!") : xorstr("disabled!")));
			}

			if (GetAsyncKeyState(g_Config.ESP.KeyBind) & 1)
			{
				g_Config.ESP.Enabled = !g_Config.ESP.Enabled;
				SendNotify(xorstr("ESP has been ") + (std::string)(g_Config.ESP.Enabled ? xorstr("enabled!") : xorstr("disabled!")));
			}

			if (GetAsyncKeyState(g_Config.Player.NoClipKey) & 1)
			{
				if (!g_Config.Player.NoClipHoldMode) {
					ApplyNoClip(!g_Config.Player.NoClipEnabled);
					SendNotify(xorstr("NoClip has been ") + (std::string)(g_Config.Player.NoClipEnabled ? xorstr("enabled!") : xorstr("disabled!")));
				}
			}

			if (g_Config.Player.NoClipHoldMode)
			{
				bool IsKeyDown = GetAsyncKeyState(g_Config.Player.NoClipKey) & 0x8000;
				if (IsKeyDown != g_Config.Player.NoClipEnabled) {
					ApplyNoClip(IsKeyDown);
					SendNotify(xorstr("NoClip has been ") + (std::string)(g_Config.Player.NoClipEnabled ? xorstr("enabled!") : xorstr("disabled!")));
				}
			}

			// Removed Freecam Toggle
			if (g_Config.Player.FreecamKey != 0 && (GetAsyncKeyState(g_Config.Player.FreecamKey) & 1))
			{
				g_Config.Player.FreecamEnabled = !g_Config.Player.FreecamEnabled;
				auto localPlayer = Core::SDK::Pointers::pLocalPlayer;
				if (localPlayer)
				{
					if (g_Config.Player.FreecamEnabled) {
						localPlayer->SetGodMode(true);
					}
					else {
						localPlayer->SetGodMode(g_Config.Player.EnableGodMode);
						if (localPlayer->IsInVehicle()) {
							CVehicle* veh = localPlayer->GetLastVehicle();
							if (veh) veh->FreezeVehicle(false);
						}
						else {
							localPlayer->FreezePed(false);
						}
					}
				}
				SendNotify(xorstr("Freecam has been ") + (std::string)(g_Config.Player.FreecamEnabled ? xorstr("enabled!") : xorstr("disabled!")));
			}

			if (GetAsyncKeyState(g_Config.Player.ParaDeVenderEssaMerdaKey) & 1)
			{
				g_Config.Player.ParaDeVenderEssaMerda = !g_Config.Player.ParaDeVenderEssaMerda;
				ApplyAntiAimFlags(g_Config.Player.ParaDeVenderEssaMerda);
				SendNotify(xorstr("Anti Aim has been ") + (std::string)(g_Config.Player.ParaDeVenderEssaMerda ? xorstr("enabled!") : xorstr("disabled!")));
			}

			if (g_Config.Player.NoClipEnabled && g_Config.Player.NoClipMode != 2)
				Features::Player::NoClip();

			if (g_Config.Player.SpinbotEnabled) {
				if (Core::SDK::Pointers::pLocalPlayer) {
					Features::Player::g_Spinbot.Apply((uintptr_t)Core::SDK::Pointers::pLocalPlayer);
				}
			}

			Features::Player::ApplyPlayerFlags();
			Features::Player::DoubleShot();
			Features::Player::NoReload();

			if (g_Config.Player.WeaponSizeEnabled)
				Features::Exploits::SetWeaponSize(g_Config.Player.WeaponSize);

			// Chuva de Vehicles Keybind Toggle
			if (g_Config.Player.RainVehiclesBind != 0 && (GetAsyncKeyState(g_Config.Player.RainVehiclesBind) & 1))
			{
				std::thread([]() {
					Core::Features::Exploits::RainVehiclesToPlayer();
				}).detach();

				SendNotify(xorstr("Raining Vehicles on Player!"));
			}

			// Update FakeLag
			if (g_Config.Player.FakeLagEnabled)
				Features::Exploits::g_FakeLag.Update();

			if (g_Config.Player.PsychicGun)
				Features::g_PsychicGun.Draw();

			Features::Exploits::free_cam();

			Features::Exploits::UpdateCamFov();

			ApplyAntiAimFlags(g_Config.Player.ParaDeVenderEssaMerda);

			if (GetAsyncKeyState(g_Config.Player.FixVehicleBind) & 1)
			{
				Features::Exploits::FixVehicle();
				SendNotify(xorstr("Vehicle Fixed!"));
			}

			// Peek Assist Keybinds
			if (g_Config.Player.SavePeekKey != 0 && (GetAsyncKeyState(g_Config.Player.SavePeekKey) & 1))
			{
				if (Core::SDK::Pointers::pLocalPlayer)
				{
					D3DXVECTOR3 currentPos = Core::SDK::Pointers::pLocalPlayer->GetPos();
					g_Config.Player.SavedPeekX = currentPos.x;
					g_Config.Player.SavedPeekY = currentPos.y;
					g_Config.Player.SavedPeekZ = currentPos.z;
					g_Config.Player.PeekPositionSaved = true;
					SendNotify(xorstr("Peek position saved!"));
				}
			}

			if (g_Config.Player.TeleportPeekKey != 0 && (GetAsyncKeyState(g_Config.Player.TeleportPeekKey) & 1))
			{
				if (!g_Config.Player.PeekPositionSaved)
				{
					SendNotify(xorstr("No peek position saved!"));
				}
				else if (Core::SDK::Pointers::pLocalPlayer)
				{
					D3DXVECTOR3 peekPos(g_Config.Player.SavedPeekX, g_Config.Player.SavedPeekY, g_Config.Player.SavedPeekZ);
					Core::SDK::Pointers::pLocalPlayer->SetPos(peekPos);
					SendNotify(xorstr("Teleported to peek position!"));
				}
			}

		}

		if (ActiveWindow == g_Variables.g_hGameWindow || ActiveWindow == g_Variables.g_hCheatWindow)
		{
			struct FovData_t {
				bool* Enabled; int* FovSize; ImColor* FovColor;
			};
			FovData_t fovData[] = {
				{&g_Config.Aimbot.ShowFov, &g_Config.Aimbot.FOV, &g_Config.Aimbot.FovColor},
				{&g_Config.SilentAim.ShowFov, &g_Config.SilentAim.FOV, &g_Config.SilentAim.FovColor},
				{&g_Config.TriggerBot.ShowFov, &g_Config.TriggerBot.FOV, &g_Config.TriggerBot.FovColor},
			};
			const int fovCount = 3;

			static float Alphas[3]{}, Sizes[3]{};

			for (int i = 0; i < fovCount; ++i)
			{
				Alphas[i] = ImClamp(ImLerp(Alphas[i], *fovData[i].Enabled ? 1.f : 0.f, ImGui::GetIO().DeltaTime * 10.f), 0.f, 1.f);
				Sizes[i] = ImLerp(Sizes[i], (float)*fovData[i].FovSize, ImGui::GetIO().DeltaTime * 12.f);

				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, Alphas[i]);
				ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(g_Variables.g_vGameWindowCenter.x, g_Variables.g_vGameWindowCenter.y), Sizes[i], ImGui::GetColorU32(fovData[i].FovColor->Value), 999);
				ImGui::PopStyleVar();
			}

			if (g_Config.General.WaterMark)
				Custom::WaterMark::Render();

			ImGui::PushFont(g_Variables.m_DrawFont);

			Features::g_Esp.Draw();
			Features::g_Esp.DrawVehicle();
			Features::g_Esp.InvisibleWarning();
			Features::g_Esp.AdminList();
			Features::g_Esp.FeatureList();
			Features::g_Esp.WeatherPersist();

			// Crosshair Logic
			if (g_Config.ESP.Crosshair)
			{
				ImVec2 center = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
				ImColor color = g_Config.ESP.CrosshairColor;
				
				float size = g_Config.ESP.CrosshairSize;
				float thickness = g_Config.ESP.CrosshairThickness;
				
				auto drawList = ImGui::GetBackgroundDrawList();
				
				if (g_Config.ESP.CrosshairType == 0) // Tipo: Static (Dot/Ponto)
				{
					drawList->AddCircleFilled(center, thickness + 1.f, color);
				}
				else if (g_Config.ESP.CrosshairType == 1) // Tipo: Plus (Cruz +)
				{
					drawList->AddLine(ImVec2(center.x - size, center.y), ImVec2(center.x + size, center.y), color, thickness);
					// Linha Vertical
					drawList->AddLine(ImVec2(center.x, center.y - size), ImVec2(center.x, center.y + size), color, thickness);
				}
				else if (g_Config.ESP.CrosshairType == 2) // Tipo: X
				{
					drawList->AddLine(ImVec2(center.x - size, center.y - size), ImVec2(center.x + size, center.y + size), color, thickness);
					drawList->AddLine(ImVec2(center.x + size, center.y - size), ImVec2(center.x - size, center.y + size), color, thickness);
				}
			}

			ImGui::PopFont();
		}
		else {
			// Não fechamos mais o menu automaticamente se a janela ativa for outra.
			// O menu só fechará ao apertar a bind.
			/*
			if (g_MenuInfo.MenuAlpha >= 0.9f)
			{
				g_MenuInfo.IsOpen = false;
				SetWindowLong(g_Variables.g_hCheatWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT);
			}
			*/
		}

	}
}
