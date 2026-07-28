#pragma once
#include <Includes/includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <Includes/CustomWidgets/Preview.hpp>

#include <Core/Core.hpp>

using namespace std;
using namespace Core;

namespace Visuals {

	void Render( ) {

		// Move columns up specifically for this tab
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 25.f);

		// Calculate proportional column widths with symmetrical padding
		float spacing = ImGui::GetStyle().ItemSpacing.x;
		float right_padding = 20.0f;
		float available_width = ImGui::GetContentRegionAvail().x - right_padding;
		float col_width = (available_width - spacing * 2.0f) / 3.0f;
		float child_height = ImGui::GetContentRegionAvail().y - 10.f - 25.f; // Compensa o SetCursorPosY(-25)

		ImGui::BeginGroup( );
		{
			ImGui::BeginGroup( );
			{
				ImGui::BeginChild( xorstr( "Player ESP" ), ImVec2(col_width, child_height), false, ImGuiWindowFlags_NoScrollbar );
				{

					Custom::CheckBox( xorstr( "Enable ESP" ), &g_Config.ESP.Enabled );

					Custom::SliderInt( xorstr( "Render Distance" ), &g_Config.ESP.MaxDistance, 0, 1000, xorstr( "%dm" ) );


					Custom::CheckBox( xorstr( "Box" ), &g_Config.ESP.Box );
					Custom::CheckBox( xorstr( "Skeleton" ), &g_Config.ESP.Skeleton );
					Custom::CheckBox( xorstr( "Player Name" ), &g_Config.ESP.UserNames );
					Custom::CheckBox( xorstr( "Weapon Name" ), &g_Config.ESP.WeaponName );
					Custom::CheckBox( xorstr( "Head Circle" ), &g_Config.ESP.HeadCircle );
					Custom::CheckBox( xorstr( "China Hat" ), &g_Config.ESP.ChinaHat );
					Custom::CheckBox( xorstr( "Health Bar" ), &g_Config.ESP.HealthBar );
					Custom::CheckBox( xorstr( "Armor Bar" ), &g_Config.ESP.ArmorBar );
					Custom::CheckBox( xorstr( "SnapLines" ), &g_Config.ESP.SnapLines );
					Custom::CheckBox( xorstr( "Distance" ), &g_Config.ESP.DistanceFromMe );
					Custom::CheckBox( xorstr( "Admin List" ), &g_Config.ESP.AdminList );
					Custom::CheckBox( xorstr( "Admin Highlight" ), &g_Config.ESP.AdminHighlight );
					Custom::CheckBox( xorstr( "Invisible Warning" ), &g_Config.ESP.InvisiblePlayerWarning );
					Custom::CheckBox(xorstr("Ignore Dead"), &g_Config.ESP.IgnoreDead);
					Custom::CheckBox( xorstr( "Ignore NPCs" ), &g_Config.ESP.IgnoreNPCs );
					Custom::CheckBox( xorstr( "Show LocalPlayer" ), &g_Config.ESP.ShowLocalPlayer );

				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );
			ImGui::SameLine( );
			ImGui::BeginGroup( );
			{
				ImGui::BeginChild( xorstr( "Vehicle ESP" ), ImVec2(col_width, 185), false, ImGuiWindowFlags_NoScrollbar );
				{
					Custom::CheckBox( xorstr( "Enable" ), &g_Config.VehicleESP.Enabled );
					Custom::SliderInt( xorstr( "Render Distance" ), &g_Config.VehicleESP.MaxDistance, 0, 1000, xorstr( "%dm" ), 0 );
					Custom::CheckBox( xorstr( "Vehicle Name" ), &g_Config.VehicleESP.VehName );
					Custom::CheckBox( xorstr( "Locked/Unlocked" ), &g_Config.VehicleESP.ShowLockUnlock );
					Custom::CheckBox( xorstr( "Distance" ), &g_Config.VehicleESP.DistanceFromMe );
					Custom::CheckBox( xorstr( "SnapLines" ), &g_Config.VehicleESP.SnapLines );
				}
				ImGui::EndChild( );

				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4);

				float color_settings_height = (std::max)(child_height - 185 - 4, 0.0f);
				ImGui::BeginChild( xorstr( "Color Settings" ), ImVec2(col_width, color_settings_height), false, ImGuiWindowFlags_NoScrollbar );
				{
					Custom::SliderFloat(xorstr("Text Size"), &g_Config.ESP.TextSize, 0.5f, 2.0f, "%.1fx");
					Custom::SliderFloat(xorstr("Skeleton Thickness"), &g_Config.ESP.SkeletonSize, 0.5f, 5.0f, "%.1f");

					auto ColorOption = [](const char* label, ImColor* col) {
						ImGui::Text("%s", label);
						ImGui::SameLine();
						ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 35);
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 1);
						Custom::ColorPicker(("##" + std::string(label)).c_str(), (float*)col);
					};

					if (g_Config.ESP.Box) ColorOption(xorstr("Box Color"), &g_Config.ESP.BoxCol);
					if (g_Config.ESP.FilledBox) ColorOption(xorstr("Filled Box Color"), &g_Config.ESP.FilledBoxCol);
					if (g_Config.ESP.Skeleton) ColorOption(xorstr("Skeleton Color"), &g_Config.ESP.SkeletonCol);
					if (g_Config.ESP.ChinaHat) ColorOption(xorstr("China Hat Color"), &g_Config.ESP.ChinaHatCol);
					if (g_Config.ESP.UserNames) ColorOption(xorstr("Player Name Color"), &g_Config.ESP.UserNamesCol);
					if (g_Config.ESP.WeaponName) ColorOption(xorstr("Weapon Name Color"), &g_Config.ESP.WeaponNameCol);
					if (g_Config.ESP.DistanceFromMe) ColorOption(xorstr("Distance Color"), &g_Config.ESP.DistanceCol);
					if (g_Config.ESP.SnapLines || g_Config.VehicleESP.SnapLines) ColorOption(xorstr("Snaplines Color"), &g_Config.ESP.SnapLinesCol);
					
					// Essas cores podem aparecer sob condições específicas de amizade/admin
					if (g_Config.ESP.Skeleton) ColorOption(xorstr("Friend Color"), &g_Config.ESP.FriendCol);
					if (g_Config.ESP.AdminList) ColorOption(xorstr("Invisible Filter Color"), &g_Config.ESP.InvisibleFilterColor);
					if (g_Config.ESP.AdminHighlight) ColorOption(xorstr("Admin Highlight Color"), &g_Config.ESP.AdminHighlightCol);
				}
				ImGui::EndChild();
			}
			ImGui::EndGroup( );
			ImGui::SameLine( );
			ImGui::BeginGroup( );
			{
				ImGui::BeginChild( xorstr( "Player Preview" ), ImVec2(col_width, child_height), false, ImGuiWindowFlags_NoScrollbar );
				{
					Custom::g_EspPreview.DragDropHandler();
					Custom::g_EspPreview.Draw();
				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );
		}
		ImGui::EndGroup( );
	}
}