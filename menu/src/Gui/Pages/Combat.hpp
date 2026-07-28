#pragma once
#include <Includes/Includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace Core;

namespace Combat {

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
				float child_height = ImGui::GetContentRegionAvail().y - 10.f; // Max height minus small bottom padding
				ImGui::BeginChild( xorstr( "Aimbot" ), ImVec2(col_width, child_height), false, ImGuiWindowFlags_NoScrollbar );
				{
					Custom::CheckBox( xorstr( "Enable" ), &g_Config.Aimbot.Enabled );
					Custom::CheckBox( xorstr( "Show Fov" ), &g_Config.Aimbot.ShowFov );
					ImGui::Text( xorstr( "Fov Color" ) );
					ImGui::SameLine( );
					ImGui::SetCursorPosX( ImGui::GetWindowWidth( ) - 35 );
					ImGui::SetCursorPosY( ImGui::GetCursorPosY( ) + 1 );
					Custom::ColorPicker( xorstr( "##FovColorAimbot" ), (float*)&g_Config.Aimbot.FovColor );
					Custom::CheckBox( xorstr( "Visible Check" ), &g_Config.Aimbot.OnlyVisible );
					Custom::CheckBox( xorstr( "Ignore NPCs" ), &g_Config.Aimbot.IgnoreNPCs );
					static int KeyMode1 = 1;
					ImGui::Keybind( xorstr( "KeyBind" ), &g_Config.Aimbot.KeyBind, &KeyMode1 );
					Custom::SliderInt( xorstr( "Fov Size" ), &g_Config.Aimbot.FOV, 0, 400, xorstr( "%d" ), 0 );
					Custom::SliderInt( xorstr( "Max Distance" ), &g_Config.Aimbot.MaxDistance, 0, 1000, xorstr( "%dm" ), 0 );
					Custom::SliderInt( xorstr( "Smooth X" ), &g_Config.Aimbot.AimbotSpeed, 0, 100, xorstr( "%d" ), 0 );
					Custom::SliderInt( xorstr( "Smooth Y" ), &g_Config.Aimbot.SmoothVertical, 0, 100, xorstr( "%d" ), 0 );
				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );
			ImGui::SameLine( );
			ImGui::BeginGroup( );
			{
				float child_height = ImGui::GetContentRegionAvail().y - 10.f;
				ImGui::BeginChild( xorstr( "Trigger" ), ImVec2(col_width, child_height), false, ImGuiWindowFlags_NoScrollbar );
				{
					Custom::CheckBox( xorstr( "Enable" ), &g_Config.TriggerBot.Enabled );
					Custom::CheckBox( xorstr( "Show Fov" ), &g_Config.TriggerBot.ShowFov );
					
					ImGui::Text( xorstr( "Fov Color" ) );
					ImGui::SameLine( );
					ImGui::SetCursorPosX( ImGui::GetWindowWidth( ) - 35 );
					ImGui::SetCursorPosY( ImGui::GetCursorPosY( ) + 1 );
					Custom::ColorPicker( xorstr( "##FovColorTrigger" ), (float*)&g_Config.TriggerBot.FovColor );

					Custom::CheckBox( xorstr( "Smart Triggerbot" ), &g_Config.TriggerBot.SmartTrigger );
					Custom::CheckBox( xorstr( "Visible Check" ), &g_Config.TriggerBot.OnlyVisible );
					Custom::CheckBox( xorstr( "Ignore NPCs" ), &g_Config.TriggerBot.IgnoreNPCs );
					static int KeyMode2 = 1;
					ImGui::Keybind( xorstr( "KeyBind" ), &g_Config.TriggerBot.KeyBind, &KeyMode2 );
					Custom::SliderInt( xorstr( "Fov Size" ), &g_Config.TriggerBot.FOV, 0, 400, xorstr( "%d" ), 0 );
					Custom::SliderInt( xorstr( "Max Distance" ), &g_Config.TriggerBot.MaxDistance, 0, 1000, xorstr( "%dm" ), 0 );
					Custom::SliderInt( xorstr( "Reaction Time" ), &g_Config.TriggerBot.Delay, 0, 10, xorstr( "%d" ), 0 );
				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );
			ImGui::SameLine( );
			ImGui::BeginGroup( );
			{
				float child_height = ImGui::GetContentRegionAvail().y - 10.f;
				ImGui::BeginChild( xorstr( "Silent" ), ImVec2(col_width, child_height), false, ImGuiWindowFlags_NoScrollbar );
				{
					Custom::CheckBox( xorstr( "Enable" ), &g_Config.SilentAim.Enabled );
					Custom::CheckBox( xorstr( "Show Fov" ), &g_Config.SilentAim.ShowFov );

					ImGui::Text( xorstr( "Fov Color" ) );
					ImGui::SameLine( );
					ImGui::SetCursorPosX( ImGui::GetWindowWidth( ) - 35 );
					ImGui::SetCursorPosY( ImGui::GetCursorPosY( ) + 1 );
					Custom::ColorPicker( xorstr( "##FovColorSilent" ), (float*)&g_Config.SilentAim.FovColor );

					Custom::CheckBox( xorstr( "Magic Bullets" ), &g_Config.SilentAim.MagicBullets );
					Custom::CheckBox( xorstr( "Visible Check" ), &g_Config.SilentAim.OnlyVisible );
					Custom::CheckBox( xorstr( "Ignore NPCs" ), &g_Config.SilentAim.IgnoreNPCs );
					Custom::SliderInt( xorstr( "Fov Size" ), &g_Config.SilentAim.FOV, 0, 400, xorstr( "%d" ), 0 );
					Custom::SliderInt( xorstr( "Max Distance" ), &g_Config.SilentAim.MaxDistance, 0, 1000, xorstr( "%dm" ), 0 );
				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );

		}
		ImGui::EndGroup( );

	}
}
