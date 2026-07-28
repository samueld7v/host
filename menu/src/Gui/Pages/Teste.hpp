#pragma once
#include <Includes/includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <vector>

#include <Core/Core.hpp>
#include <Core/Features/Exploits/Exploits.hpp>
#include <Core/Features/Exploits/GiveWeapon.hpp>
#include <Core/Features/Exploits/HandlingEditor.hpp>
#include <Core/Features/Exploits/ResourceList.hpp>
#include <Includes/CustomWidgets/Notify.hpp>

using namespace std;
using namespace Core;

namespace Teste {

	void Render()
	{
		// Move columns up specifically for this tab
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 25.f);

		ImGui::SetCursorPos(ImVec2(184, 60));
		ImGui::BeginGroup();
		{
			ImGui::BeginContent(xorstr("Exploits Tab"), ImVec2(g_MenuInfo.MenuSize.x - (188 + 24), 360), 0, ImGuiWindowFlags_NoScrollbar);
			{
				// Title
				ImGui::TextColored(g_Col.FeaturesText, xorstr("Weapon"));
				ImGui::SameLine();
				ImGui::TextColored(g_Col.SecundaryText, xorstr(" (Funciona apenas com o TAB liberado)"));

				// Weapon Selection Combo
				static const char* weaponHashes[] = {
					"Pistol", "Submetralhadora", "SpecialCarbine", "SpecialCarbine Mk2",
					"AssaultRifle", "CarbineRifle", "SniperRifle",
					"RPG", "Minigun",
					"RayMinigun", "RayCarbine"
				};
				static int selectedWeapon = 0;
				static unsigned int weaponHashValues[] = {
					0x1B06D571, 0x2BE6766B, 0xC0A3098D, 0x969C3D67,
					0xBFEFFF6D, 0x83BF0278, 0x5FC3C11,
					0xB1CA77B1, 0x42BF8A85,
					0xB4FD7B36, 0x476BF155
				};

				if (Custom::Combo(xorstr("Select Weapon"), &selectedWeapon, weaponHashes, IM_ARRAYSIZE(weaponHashes)))
				{
				}

				// Ammo Slider (Default 255)
				static int Ammo = 255;
				Custom::SliderInt(xorstr("Ammo"), &Ammo, 0, 250);

				// Button
				if (Custom::Button(xorstr("Spawn Weapon"), ImVec2(-1, 30), 0))
				{
					unsigned int hash = weaponHashValues[selectedWeapon];
					int ammo = Ammo;
					std::thread([hash, ammo]() {
						Core::Features::Exploits::g_WeaponSpawn.Spawn(hash, ammo);
						NotifyManager::Send(xorstr("Weapon spawned!"), 4000);
					}).detach();
				}

				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();

				ImGui::TextColored(g_Col.FeaturesText, xorstr("Mundo Solo"));
				ImGui::PushFont(g_Variables.m_FontSecundary);
				ImGui::TextColored(g_Col.SecundaryText, xorstr("Remova seu personagem do mundo solo/toxico"));
				ImGui::PopFont();

				if (Custom::Button(xorstr("Tirar Mundo Solo"), ImVec2(-1, 35), 0))
				{
					std::thread([]() {
						Core::Features::Exploits::TirarMundoSolo();
					}).detach();
				}
			}
			ImGui::EndContent();
		}
		ImGui::EndGroup();
	}
}
