#pragma once
#include <Includes/Includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace Core;

namespace Settings {

	void Render( ) {

		// Move columns up specifically for this tab
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 25.f);

		// Calculate proportional column widths with symmetrical padding
		float spacing = ImGui::GetStyle().ItemSpacing.x;
		float right_padding = 20.0f;
		float available_width = ImGui::GetContentRegionAvail().x - right_padding;
		float col_width = (available_width - spacing * 2.0f) / 3.0f;

		ImGui::BeginGroup( );
		{
			ImGui::BeginGroup( );
			{
				float child_height = ImGui::GetContentRegionAvail().y - 10.f;
				ImGui::BeginChild( xorstr( "Misc ESP Settings" ), ImVec2(col_width, child_height), false, ImGuiWindowFlags_NoScrollbar );
				{
					if (Custom::CheckBox( xorstr( "Minecraft (ESP)" ), &g_Config.MiscESP.MinecraftFont )) {
						if (g_Config.MiscESP.MinecraftFont) g_Config.MiscESP.HyperXFont = false;
					}
					if (Custom::CheckBox( xorstr( "HyperX Esp" ), &g_Config.MiscESP.HyperXFont )) {
						if (g_Config.MiscESP.HyperXFont) g_Config.MiscESP.MinecraftFont = false;
					}
					Custom::CheckBox( xorstr( "Feature List" ), &g_Config.MiscESP.FeatureList );

					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();

					// Crosshair settings
					Custom::CheckBox(xorstr("Crosshair"), &g_Config.ESP.Crosshair);
					if (g_Config.ESP.Crosshair)
					{
						static const char* crosshairTypes[] = { "Dot", "Plus", "X" };
						Custom::Combo(xorstr("Type"), &g_Config.ESP.CrosshairType, crosshairTypes, IM_ARRAYSIZE(crosshairTypes));
						
						Custom::SliderFloat(xorstr("Size"), &g_Config.ESP.CrosshairSize, 1.0f, 50.0f, "%.1f");
						Custom::SliderFloat(xorstr("Thickness"), &g_Config.ESP.CrosshairThickness, 1.0f, 10.0f, "%.1f");
						
						float crosshairCol[4] = { 
							g_Config.ESP.CrosshairColor.Value.x, 
							g_Config.ESP.CrosshairColor.Value.y, 
							g_Config.ESP.CrosshairColor.Value.z, 
							g_Config.ESP.CrosshairColor.Value.w 
						};
						ImGui::SetCursorPosX(10);
						if (ImGui::ColorEdit4(xorstr("Crosshair Color"), crosshairCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
							g_Config.ESP.CrosshairColor = ImColor(crosshairCol[0], crosshairCol[1], crosshairCol[2], crosshairCol[3]);
						}
					}
				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );
			ImGui::SameLine( );
			ImGui::BeginGroup( );
			{
				float child_height = ImGui::GetContentRegionAvail().y - 10.f;
				ImGui::BeginChild( xorstr( "Menu Settings" ), ImVec2(col_width, child_height), false, ImGuiWindowFlags_NoScrollbar );
				{
					if ( Custom::CheckBox( xorstr( "Hide from Screenshot" ), &g_Config.General.StreamProof ) )
					{
						if ( g_Config.General.StreamProof )
						{
							SetWindowDisplayAffinity( g_Variables.g_hCheatWindow, WDA_EXCLUDEFROMCAPTURE );
						}
						else
						{
							SetWindowDisplayAffinity( g_Variables.g_hCheatWindow, WDA_NONE );
						}
					}
					Custom::CheckBox( xorstr( "Enable V-Sync" ), &g_Config.General.VSync );
					Custom::CheckBox( xorstr( "Second Monitor" ), &g_Config.General.SecondMonitor );
					Custom::CheckBox( xorstr( "Particulas" ), &g_MenuInfo.EnableParticles );
					Custom::CheckBox( xorstr( "Glassmorphism" ), &g_MenuInfo.Glassmorphism );

					ImGui::Spacing( );

					static int MenuKeyMode = 1;
					ImGui::Keybind( xorstr( "Menu Key" ), &g_Config.General.MenuKey, &MenuKeyMode );

					ImGui::Text( xorstr( "Menu Color" ) );
					ImGui::SameLine( );
					ImGui::SetCursorPosX( ImGui::GetWindowWidth( ) - 35 );
					ImGui::SetCursorPosY( ImGui::GetCursorPosY( ) - 2 );
					Custom::ColorPicker( xorstr( "##MenuColor" ), ( float * ) &g_Col.Base );

					ImGui::Spacing( );

					if ( Custom::Button( xorstr( "Unload" ), ImVec2( -1, 30 ), 0 ) ) 
					{
						exit( 0 );
					}
				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );
			ImGui::SameLine( );
			ImGui::BeginGroup( );
			{
				float child_height = ImGui::GetContentRegionAvail().y - 10.f;
				ImGui::BeginChild( xorstr( "Config System" ), ImVec2(col_width, child_height), false, ImGuiWindowFlags_NoScrollbar );
				{
					static char cfgName[64] = "";
					static int selectedCfg = -1;
					static std::vector<std::string> configs = g_Config.GetConfigs();

					ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 14, 8 ) );

					ImGui::PushItemWidth(-1);
					ImGui::InputTextWithHint(xorstr("##CfgName"), xorstr("Config Name..."), cfgName, IM_ARRAYSIZE(cfgName));
					ImGui::PopItemWidth();

					ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
					ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
					ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.25f, 0.25f, 0.25f, 1.0f));

					if (ImGui::BeginListBox(xorstr("##ConfigsList"), ImVec2(-1, 120))) {
						for (int i = 0; i < configs.size(); i++) {
							const bool isSelected = (selectedCfg == i);
							if (ImGui::Selectable(configs[i].c_str(), isSelected)) {
								selectedCfg = i;
								strcpy_s(cfgName, sizeof(cfgName), configs[i].c_str());
							}
							if (isSelected) {
								ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndListBox();
					}
					ImGui::PopStyleColor(3);

					if ( Custom::Button( xorstr( "Refresh" ), ImVec2( -1, 30 ), 0 ) ) 
					{
						configs = g_Config.GetConfigs();
					}

					if ( Custom::Button( xorstr( "Save / Create" ), ImVec2( -1, 30 ), 0 ) ) 
					{
						if (cfgName[0] != '\0') {
							std::string nameStr = cfgName;
							std::thread cfgExport( [nameStr] {
								std::string CfgMsg = g_Config.SaveCurrentConfig( nameStr );
								NotifyManager::Send( CfgMsg.c_str( ), 3000 );
								} );
							cfgExport.detach( );
							configs = g_Config.GetConfigs();
						}
					}
					if ( Custom::Button( xorstr( "Load Config" ), ImVec2( -1, 30 ), 0 ) ) 
					{
						if (cfgName[0] != '\0') {
							std::string nameStr = cfgName;
							std::thread cfgImport( [nameStr] {
								std::string CfgMsg = g_Config.LoadCurrentConfig( nameStr );
								NotifyManager::Send( CfgMsg.c_str( ), 3000 );
								} );
							cfgImport.detach( );
						}
					}
					if ( Custom::Button( xorstr( "Delete Config" ), ImVec2( -1, 30 ), 0 ) ) 
					{
						if (cfgName[0] != '\0') {
							std::string nameStr = cfgName;
							std::thread cfgDelete( [nameStr] {
								std::string CfgMsg = g_Config.DeleteConfig( nameStr );
								NotifyManager::Send( CfgMsg.c_str( ), 3000 );
								} );
							cfgDelete.detach( );
							configs = g_Config.GetConfigs();
							cfgName[0] = '\0';
							selectedCfg = -1;
						}
					}

					ImGui::PopStyleVar();
				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );
		}
		ImGui::EndGroup( );

	}
}