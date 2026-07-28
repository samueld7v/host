#pragma once
#include <Includes/includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <vector>

#include <Core/Core.hpp>
#include <Core/Features/Exploits/Exploits.hpp>
#include <Core/Features/Exploits/HandlingEditor.hpp>
#include <Gui/Pages/Resoucer.hpp>

using namespace std;
using namespace Core;

namespace Local {

	inline int iSubTab = 0;

	void Render( )
	{
		// Move columns up specifically for this tab
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 25.f);

		float child_height = ImGui::GetContentRegionAvail().y - 35.f;

		// Calculate proportional column widths with symmetrical padding
		float spacing = ImGui::GetStyle().ItemSpacing.x;
		float right_padding = 20.0f;
		float available_width = ImGui::GetContentRegionAvail().x - right_padding;
		float col_width = (available_width - spacing * 2.0f) / 3.0f;

		ImGui::BeginGroup( );
		{
			if (iSubTab == 0)
			{
				
				ImGui::BeginGroup( );
				{
					ImGui::BeginChild( xorstr( "Player" ), ImVec2(col_width, child_height), false, ImGuiWindowFlags_NoScrollbar );
					{
					if ( Custom::CheckBox( xorstr( "God Mode" ), &g_Config.Player.EnableGodMode ) )
					{
						Core::SDK::Pointers::pLocalPlayer->SetGodMode( g_Config.Player.EnableGodMode );
					}
					if ( g_Config.Player.EnableGodMode )
					{
						static int GodModeKeyMode = 1;
						ImGui::Keybind( xorstr( "God Mode Key" ), &g_Config.Player.GodModeKey, &GodModeKeyMode );
					}

					if ( Custom::CheckBox( xorstr( "Anti HeadShot" ), &g_Config.Player.AntiHSEnabled ) )
					{
						Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( CPED_CONFIG_FLAG_NoCriticalHits, g_Config.Player.AntiHSEnabled );
					}
					
					if ( Custom::CheckBox( xorstr( "Anti Aim" ), &g_Config.Player.ParaDeVenderEssaMerda ) )
					{
						if ( g_Config.Player.ParaDeVenderEssaMerda ) {
							Core::SDK::Pointers::pLocalPlayer->SetConfigFlag(CPED_CONFIG_FLAG_DisablePlayerLockon, true); 
							Core::SDK::Pointers::pLocalPlayer->SetConfigFlag(CPED_CONFIG_FLAG_AllowPlayerLockOnIfFriendly, true); 
							Core::SDK::Pointers::pLocalPlayer->SetConfigFlag(CPED_CONFIG_FLAG_TreatAsFriendlyForTargetingAndDamage, true); 
						} else { 
							Core::SDK::Pointers::pLocalPlayer->SetConfigFlag(CPED_CONFIG_FLAG_DisablePlayerLockon, false); 
							Core::SDK::Pointers::pLocalPlayer->SetConfigFlag(CPED_CONFIG_FLAG_AllowPlayerLockOnIfFriendly, false); 
							Core::SDK::Pointers::pLocalPlayer->SetConfigFlag(CPED_CONFIG_FLAG_TreatAsFriendlyForTargetingAndDamage, false); 
						}
					}

					if (g_Config.Player.ParaDeVenderEssaMerda)
					{
						static int ParaDeVenderKeyMode = 1;
						ImGui::Keybind(xorstr("Bind Anti Aim"), &g_Config.Player.ParaDeVenderEssaMerdaKey, &ParaDeVenderKeyMode);
					}

					if (Custom::CheckBox(xorstr("Anti Attack"), &g_Config.Player.AntiEntityAttach))
					{
						if (g_Config.Player.AntiEntityAttach) {
							std::thread([]() {
								while (g_Config.Player.AntiEntityAttach) {
									if (Core::SDK::Pointers::pLocalPlayer) {
										if (Core::SDK::Pointers::pLocalPlayer->IsEntityAttached() ||
											Core::SDK::Pointers::pLocalPlayer->HasFlag(CPED_CONFIG_FLAG_IsHandCuffed) ||
											Core::SDK::Pointers::pLocalPlayer->HasFlag(CPED_CONFIG_FLAG_IsAnkleCuffed))
										{
											Core::SDK::Pointers::pLocalPlayer->DetachEntity(3, 1);
											Core::SDK::Pointers::pLocalPlayer->SetConfigFlag(CPED_CONFIG_FLAG_IsHandCuffed, false);
											Core::SDK::Pointers::pLocalPlayer->SetConfigFlag(CPED_CONFIG_FLAG_IsAnkleCuffed, false);
											Core::SDK::Pointers::pLocalPlayer->UnfreezePed();
										}
									}
									std::this_thread::sleep_for(std::chrono::milliseconds(250));
								}
								}).detach();
						}
					}

					if ( Custom::CheckBox( xorstr( "NoClip" ), &g_Config.Player.NoClipEnabled ) )
					{
						auto localPlayer = Core::SDK::Pointers::pLocalPlayer;
						if ( localPlayer )
						{
							if ( !g_Config.Player.NoClipEnabled ) {
								Features::Player::ResetNoClip();
							}

							if ( !localPlayer->IsInVehicle() ) {
								if ( auto netObj = localPlayer->pNetObject() ) {
									if (g_Config.Player.NoClipMode == 0 || g_Config.Player.NoClipMode == 2)
										netObj->SetInvisible( g_Config.Player.NoClipEnabled );
									else
										netObj->SetInvisible( false );
								}
							}
							else if ( !g_Config.Player.NoClipEnabled || g_Config.Player.NoClipMode == 1 ) {
								if ( auto netObj = localPlayer->pNetObject() ) {
									netObj->SetInvisible( false );
								}
							}
							Features::Exploits::SetInvisibleLocal(g_Config.Player.NoClipEnabled && g_Config.Player.NoClipMode == 2);
						}
					}
					if ( g_Config.Player.NoClipEnabled )
					{
						static const char* NoClipModes[] = { "Server Side", "Client Side", "Invisible Only" };
						if (ImGui::Combo(xorstr("NoClip Mode"), &g_Config.Player.NoClipMode, NoClipModes, IM_ARRAYSIZE(NoClipModes)))
						{
							auto localPlayer = Core::SDK::Pointers::pLocalPlayer;
							if (localPlayer) {
								if ( !localPlayer->IsInVehicle() ) {
									if ( auto netObj = localPlayer->pNetObject() ) {
										if (g_Config.Player.NoClipMode == 0 || g_Config.Player.NoClipMode == 2)
											netObj->SetInvisible( g_Config.Player.NoClipEnabled );
										else
											netObj->SetInvisible( false );
									}
								}
								if (g_Config.Player.NoClipMode == 2) {
									Features::Player::ResetNoClip();
								}
								Features::Exploits::SetInvisibleLocal( g_Config.Player.NoClipMode == 2 );
							}
						}

						static int NoClipKeyMode = 1;
						ImGui::Keybind( xorstr( "NoClip Key" ), &g_Config.Player.NoClipKey, &NoClipKeyMode );
						Custom::CheckBox( xorstr( "Hold Mode" ), &g_Config.Player.NoClipHoldMode );
						if (g_Config.Player.NoClipSpeed < 1.0f) g_Config.Player.NoClipSpeed = 1.0f;
						if (g_Config.Player.NoClipSpeed > 6.0f) g_Config.Player.NoClipSpeed = 6.0f;
						if (g_Config.Player.NoClipMode != 2) {
							Custom::SliderFloat( xorstr( "NoClip Speed" ), &g_Config.Player.NoClipSpeed, 1.0f, 6.0f, xorstr( "%.0f" ) );
						}
					}
					
					if ( Custom::CheckBox( xorstr( "Freecam" ), &g_Config.Player.FreecamEnabled ) )
					{
						auto localPlayer = Core::SDK::Pointers::pLocalPlayer;
						if ( localPlayer )
						{
							if (g_Config.Player.FreecamEnabled) {
								localPlayer->SetGodMode(true);
							}
							else {
								localPlayer->SetGodMode(g_Config.Player.EnableGodMode); // Restaura o status antigo do GodMode
								if ( localPlayer->IsInVehicle() ) {
									CVehicle* veh = localPlayer->GetLastVehicle();
									if ( veh ) {
										veh->FreezeVehicle(false);
									}
								}
								else {
									localPlayer->FreezePed(false);
								}
							}
						}
					}
					if ( g_Config.Player.FreecamEnabled )
					{
						static int FreecamKeyMode = 1;
						ImGui::Keybind( xorstr( "Freecam Key" ), &g_Config.Player.FreecamKey, &FreecamKeyMode );
						
						if (g_Config.Player.FreecamSpeed < 1.0f) g_Config.Player.FreecamSpeed = 1.0f;
						if (g_Config.Player.FreecamSpeed > 6.0f) g_Config.Player.FreecamSpeed = 6.0f;
						Custom::SliderFloat( xorstr( "Freecam Speed" ), &g_Config.Player.FreecamSpeed, 1.0f, 6.0f, xorstr( "%.0f" ) );
					}

					if ( Custom::CheckBox( xorstr( "Run Faster" ), &g_Config.Player.FastRun ) )
					{
						if ( !g_Config.Player.FastRun ) {
							Core::SDK::Pointers::pLocalPlayer->SetSpeed( 1.f );
						}
					}
					if ( g_Config.Player.FastRun )
					{
						if ( Custom::SliderFloat( xorstr( "Run Speed" ), &g_Config.Player.RunSpeed, 1.0f, 100.0f, xorstr( "%.1f" ) ) )
						{
							Core::SDK::Pointers::pLocalPlayer->SetSpeed( g_Config.Player.RunSpeed );
						}
					}

					if ( Custom::CheckBox( xorstr( "Shrink" ), &g_Config.Player.ShrinkEnabled, true, xorstr( "That function can be detected by server AntiCheat" ), ICON_FA_TRIANGLE_EXCLAMATION ) )
					{
						Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( ePedConfigFlag::Shrink, g_Config.Player.ShrinkEnabled );
					}

					Custom::CheckBox( xorstr( "Super Jump" ), &g_Config.Player.SuperJump );
					Custom::CheckBox( xorstr( "Pulo Da Besta" ), &g_Config.Player.BeastJump );

					if ( Custom::CheckBox( xorstr( "No RagDoll" ), &g_Config.Player.NoRagDollEnabled ) )
					{
						Core::SDK::Pointers::pLocalPlayer->NoRagDoll( g_Config.Player.NoRagDollEnabled );
					}

					if ( Custom::CheckBox( xorstr( "Solo Session" ), &g_Config.Player.SoloSessionEnabled ) )
					{
						std::thread( [ ] ( ) {
							Features::Exploits::SoloSession( g_Config.Player.SoloSessionEnabled );
						} ).detach( );
					}

					if ( Custom::CheckBox( xorstr( "Rolas infinito" ), &g_Config.Player.InfiniteCombatRoll ) )
					{
						Core::SDK::Pointers::pLocalPlayer->SetInfCombatRoll( g_Config.Player.InfiniteCombatRoll );
					}
					
					if ( Custom::CheckBox( xorstr( "Combat Glitch" ), &g_Config.Player.CombatGlitch ) )
					{
						g_Config.Player.SpinbotEnabled = g_Config.Player.CombatGlitch;
						if ( g_Config.Player.CombatGlitch )
						{
							g_Config.Player.SpinbotSpeed = 1000.0f;
						}
					}
					if ( Custom::CheckBox( xorstr( "Infinite Stamina" ), &g_Config.Player.InfiniteStamina ) )
					{
						Core::SDK::Pointers::pLocalPlayer->SetInfStamina( g_Config.Player.InfiniteStamina );
					}
					if ( Custom::CheckBox( xorstr( "Liberar CORONHADA / TAB" ), &g_Config.Player.UnlockAllActions ) )
					{
						Features::Exploits::UnlockAllActions( g_Config.Player.UnlockAllActions );
					}
					Custom::CheckBox( xorstr( "Camera FOV" ), &g_Config.Player.CamFov );
					if ( g_Config.Player.CamFov )
					{
						Custom::SliderFloat( xorstr( "FOV Amount" ), &g_Config.Player.CamFovAmount, 0.0f, 100.0f, xorstr( "%.1f" ) );
					}

					if ( Custom::CheckBox( xorstr( "Fake Lag" ), &g_Config.Player.FakeLagEnabled ) )
					{
						if ( !g_Config.Player.FakeLagEnabled )
						{
							Core::Features::Exploits::g_FakeLag.Reset();
						}
					}
					if ( g_Config.Player.FakeLagEnabled )
					{
						Custom::SliderInt( xorstr( "Lag Delay (ms)" ), &g_Config.Player.FakeLagDelay, 50, 500, xorstr( "%d ms" ) );
					}

					g_Config.Player.CurrentHealthValue = Core::SDK::Pointers::pLocalPlayer->GetHealth() - 100.f > Core::SDK::Pointers::pLocalPlayer->GetMaxHealth() - 100.f ? Core::SDK::Pointers::pLocalPlayer->GetHealth() - 100.f : Core::SDK::Pointers::pLocalPlayer->GetHealth() - 99.f;
					g_Config.Player.CurrentArmorValue = Core::SDK::Pointers::pLocalPlayer->GetArmor();
					if (Custom::SliderFloat(xorstr("Health"), &g_Config.Player.CurrentHealthValue, -1, Core::SDK::Pointers::pLocalPlayer->GetMaxHealth(), xorstr("%1.f")))
					{
						Core::SDK::Pointers::pLocalPlayer->SetHealth(g_Config.Player.CurrentHealthValue + 100.f);
					}
					if (Custom::SliderFloat(xorstr("Armor"), &g_Config.Player.CurrentArmorValue, 0, 100/*MaxArmor*/, xorstr("%1.f")))
					{
						Core::SDK::Pointers::pLocalPlayer->SetArmor(g_Config.Player.CurrentArmorValue);
					}

					if ( Custom::Button( xorstr( "Set Vida Maxima" ), ImVec2( -1, 30 ), 0 ) )
					{
						if ( Core::SDK::Pointers::pLocalPlayer ) {
							float maxHealth = Core::SDK::Pointers::pLocalPlayer->GetMaxHealth();
							g_Config.Player.CurrentHealthValue = maxHealth;
							g_Config.Player.CurrentArmorValue = 100.f;
							
							Core::SDK::Pointers::pLocalPlayer->SetHealth(maxHealth + 100.f);
							Core::SDK::Pointers::pLocalPlayer->SetArmor(100.f);
						}
					}
				}
				ImGui::EndChild();
			}
			ImGui::EndGroup( );
			ImGui::SameLine( );
			ImGui::BeginGroup( );
			{
				ImGui::BeginChild( xorstr( "Vehicles Mods" ), ImVec2(col_width, child_height), false, ImGuiWindowFlags_NoScrollbar );
				{
					Custom::CheckBox( xorstr( "Vehicle GodMode" ), &g_Config.Player.VehicleGodMode );
					if ( Custom::CheckBox( xorstr( "Car Jack" ), &g_Config.Player.StealCarEnabled ) )
					{
						if ( Core::SDK::Pointers::pLocalPlayer )
						{
							if ( g_Config.Player.StealCarEnabled )
							{
								Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( CPED_CONFIG_FLAG_NotAllowedToJackAnyPlayers, false );
								Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( CPED_CONFIG_FLAG_PlayerCanJackFriendlyPlayers, true );
								Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( CPED_CONFIG_FLAG_WillJackAnyPlayer, true );
							}
							else
							{
								Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( CPED_CONFIG_FLAG_NotAllowedToJackAnyPlayers, true );
								Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( CPED_CONFIG_FLAG_PlayerCanJackFriendlyPlayers, false );
								Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( CPED_CONFIG_FLAG_WillJackAnyPlayer, false );
							}
						}
					}
					Custom::CheckBox( xorstr( "Seat Belt" ), &g_Config.Player.SeatBelt );
					Custom::CheckBox( xorstr( "Jumping Car" ), &g_Config.Player.JumpingCar );
					Custom::CheckBox( xorstr( "Carr Planing" ), &g_Config.Player.CarPlaning );

					if ( Custom::CheckBox( xorstr( "Psychic Gun" ), &g_Config.Player.PsychicGun ) )
					{
						// Pode adicionar notificação aqui
					}
					if ( g_Config.Player.PsychicGun )
					{
						Custom::SliderFloat( xorstr( "Arremesso Force" ), &g_Config.Player.HornBoostPower, 10.0f, 300.0f, xorstr( "%.1f" ) );
					}

					if ( Custom::CheckBox( xorstr( "Rocket Boost (E)" ), &g_Config.Player.RocketBoost ) )
					{
						Features::Exploits::SetRocketMode( g_Config.Player.RocketBoost );
					}

					if (Custom::CheckBox(xorstr("Buzina Boost"), &g_Config.Player.BuzinaBoost))
					{
						// Opcional: Alguma lógica ao ativar/desativar
					}
					if (g_Config.Player.BuzinaBoost)
					{
						static int BuzinaBoostKeyMode = 1;
						ImGui::Keybind(xorstr("Boost Key"), &g_Config.Player.BuzinaBoostKey, &BuzinaBoostKeyMode);
						Custom::SliderFloat(xorstr("Boost Speed"), &g_Config.Player.BuzinaBoostSpeed, 1.0f, 300.0f, xorstr("%.1f"));
					}

					if ( Custom::Button( xorstr( "Fix Vehicle" ), ImVec2( -1, 30 ), 0 ) )
					{
						Features::Exploits::FixVehicle( );
					}

					// Assinatura atualizada dinamicamente caso não exista (conforme seu código)
					if (!Core::g_Offsets.m_BreakOffWheel) {
						Core::g_Offsets.m_BreakOffWheel = Core::Mem.FindSignatureStr("48 8b c4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 56 41 57 48 83 ec ? 80 3d ? ? ? ? ? 0f 29 78");
					}

					if ( Custom::Button( xorstr( "Break Wheels" ), ImVec2( -1, 30 ), 0 ) )
					{
						std::thread([] {
							auto localPlayer = Core::SDK::Pointers::pLocalPlayer;
							if (!localPlayer) return;

							auto vehicle = localPlayer->GetLastVehicle();
							if (!vehicle) return;

							// Offsets estáticas baseadas no seu código
							uintptr_t damageStruct = reinterpret_cast<uintptr_t>(vehicle) + 0x420;
							int NumberofWheels = Core::Mem.Read<int>(reinterpret_cast<uintptr_t>(vehicle) + 0xC28) - 1;

							if (NumberofWheels < 0 || NumberofWheels > 10) return; // sanity check

							for (int i = 0; i <= NumberofWheels; i++) {
								// ShellCode de injeção externa para CallBreakOffWheel
								std::vector<uint8_t> ShellCode = {
									0x48, 0x83, 0xEC, 0x48,                                     
									0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x48, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0x0F, 0x57, 0xD2,                                           
									0x0F, 0x57, 0xDB,                                           
									0x31, 0xC0,                                                 
									0x89, 0x44, 0x24, 0x20,                                     
									0x88, 0x44, 0x24, 0x28,                                     
									0x88, 0x44, 0x24, 0x30,                                     
									0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
									0xFF, 0xD0,                                                 
									0x48, 0x83, 0xC4, 0x48,                                     
									0xC3                                                        
								};

								uintptr_t Cave = Core::Mem.CreateCodeCave(ShellCode.size());
								uintptr_t Func = Core::g_Offsets.m_BreakOffWheel;
								int64_t wheelIdx = (int64_t)i;

								memcpy(ShellCode.data() + 6, &damageStruct, 8);
								memcpy(ShellCode.data() + 16, &wheelIdx, 8);
								memcpy(ShellCode.data() + 46, &Func, 8);

								Core::Mem.WriteBytes(Cave, ShellCode);

								HANDLE RemoteThread = CreateRemoteThread(Core::Mem.ProcHandle, NULL, 0, (LPTHREAD_START_ROUTINE)Cave, NULL, 0, NULL);
								if (RemoteThread) {
									WaitForSingleObject(RemoteThread, 1000);
									CloseHandle(RemoteThread);
								}
								
								Core::Mem.FreeCave(Cave);
								std::this_thread::sleep_for(std::chrono::milliseconds(50));
							}
						}).detach();
					}

					static int FixBindMode = 1;
					ImGui::Keybind( xorstr( "Fix Bind" ), &g_Config.Player.FixVehicleBind, &FixBindMode );

					if (Custom::CheckBox(xorstr("Change Vehicle Color"), &g_Config.Player.ChangeVehicleColor)) {
						if (!g_Config.Player.ChangeVehicleColor) {
							Features::g_VehicleColor.ResetMyVehicle();
						}
						else {
							g_Config.Player.RainbowCar = false; // Desativa rainbow se ativar cor manual
							Features::g_VehicleColor.ForceUpdate();
						}
					}
					if (g_Config.Player.ChangeVehicleColor) {
						float vehicleColor[4] = {
							g_Config.Player.VehicleColor.Value.x,
							g_Config.Player.VehicleColor.Value.y,
							g_Config.Player.VehicleColor.Value.z,
							g_Config.Player.VehicleColor.Value.w
						};
						if (ImGui::ColorEdit4(xorstr("Vehicle Color"), vehicleColor, ImGuiColorEditFlags_AlphaBar)) {
							g_Config.Player.VehicleColor.Value.x = vehicleColor[0];
							g_Config.Player.VehicleColor.Value.y = vehicleColor[1];
							g_Config.Player.VehicleColor.Value.z = vehicleColor[2];
							g_Config.Player.VehicleColor.Value.w = vehicleColor[3];

							Features::g_VehicleColor.ForceUpdate();
						}
					}

					if (Custom::CheckBox(xorstr("RGB Car (Rainbow)"), &g_Config.Player.RainbowCar)) {
						if (!g_Config.Player.RainbowCar) {
							Features::g_VehicleColor.ResetMyVehicle();
						} else {
							g_Config.Player.ChangeVehicleColor = false; // Desativa cor manual se ativar rainbow
						}
					}
					
					if (g_Config.Player.RainbowCar) {
						Custom::SliderFloat(xorstr("Rainbow Speed"), &g_Config.Player.RainbowCarSpeed, 0.1f, 10.0f, xorstr("%.1f"));
					}

					Custom::CheckBox( xorstr( "Modify Handling" ), &g_Config.Player.ModifyHandling );
					Custom::SliderFloat( xorstr( "Acceleration" ), &g_Config.Player.Acceleration, 0.f, 10.f, xorstr( "%.1f" ), 0 );
					Custom::SliderFloat( xorstr( "Break Force" ), &g_Config.Player.BreakForce, 0.f, 10.f, xorstr( "%.1f" ), 0 );
					Custom::SliderFloat( xorstr( "Traction Curve Min" ), &g_Config.Player.TractionCurveMin, 0.f, 10.f, xorstr( "%.1f" ), 0 );
				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );
			ImGui::SameLine( );
			ImGui::BeginGroup( );
			{
				ImGui::BeginChild( xorstr( "Weapons Options" ), ImVec2(col_width, child_height), false, ImGuiWindowFlags_NoScrollbar );
				{
					Custom::CheckBox( xorstr( "Remove Recoil" ), &g_Config.Player.NoRecoilEnabled );
					Custom::CheckBox( xorstr( "Remove Spread" ), &g_Config.Player.NoSpreadEnabled );
					if (Custom::CheckBox(xorstr("Infinite Ammo"), &g_Config.Player.InfiniteAmmoEnabled)) {
						if (g_Config.Player.InfiniteAmmoEnabled) {
							Mem.PatchFunc(g_Offsets.m_InfiniteAmmo0, 3);
							Mem.PatchFunc(g_Offsets.m_InfiniteAmmo1, 3);
						}
						else {
							if (!g_Config.Player.NoReloadEnabled) {
								Mem.WriteBytes(g_Offsets.m_InfiniteAmmo0, { 0x41, 0x2B, 0xC9, 0x3B, 0xC8, 0x0F, 0x4D, 0xC8 });
							}
							Mem.WriteBytes(g_Offsets.m_InfiniteAmmo1, { 0x41, 0x2B, 0xD1, 0xE8 });
						}
					}
					Custom::CheckBox( xorstr( "No Reload" ), &g_Config.Player.NoReloadEnabled );

					Custom::CheckBox( xorstr( "Explosive Fist" ), &g_Config.Player.ExplosiveFist );
					Custom::CheckBox( xorstr( "Double Shot" ), &g_Config.Player.DoubleShot );
					Custom::CheckBox( xorstr( "Fire Ammo" ), &g_Config.Player.FireAmmo );

					if ( Custom::CheckBox( xorstr( "Weapon Size" ), &g_Config.Player.WeaponSizeEnabled ) )
					{
						if ( !g_Config.Player.WeaponSizeEnabled ) {
							Features::Exploits::SetWeaponSize( 1.0f );
						}
					}

					if ( g_Config.Player.WeaponSizeEnabled )
					{
						if ( Custom::SliderFloat( xorstr( "Weapon Size" ), &g_Config.Player.WeaponSize, 1.0f, 10.0f, xorstr( "%.1f" ) ) )
						{
							Features::Exploits::SetWeaponSize( g_Config.Player.WeaponSize );
						}
					}

					Custom::CheckBox( xorstr( "Spinbot" ), &g_Config.Player.SpinbotEnabled );

					if ( g_Config.Player.SpinbotEnabled )
					{
						Custom::SliderFloat( xorstr( "Spin Speed" ), &g_Config.Player.SpinbotSpeed, 10.0f, 1000.0f, xorstr( "%.1f" ) );
					}

					// Weather Control
					Custom::CheckBox( xorstr( "Clima Temp" ), &g_Config.Player.WeatherControlEnabled );
					if ( g_Config.Player.WeatherControlEnabled )
					{
						static const char* weatherNames[] = {
							"Extra Sunny", "Clear", "Clouds", "Smog", "Cloudy",
							"Overcast", "Rain", "Thunder", "Clearing", "Neutral",
							"Snow Light", "Snow", "Blizzard", "Xmas", "Halloween"
						};
						
						if ( Custom::Combo( xorstr( "Weather" ), &g_Config.Player.SelectedWeather, weatherNames, IM_ARRAYSIZE( weatherNames ) ) )
						{
							Features::Exploits::SetWeather( g_Config.Player.SelectedWeather );
						}
					}
				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );
			}
			else if (iSubTab == 1)
			{
				ImGui::BeginGroup();
				{
					ImGui::BeginChild( xorstr( "Locations" ), ImVec2( 460, child_height ), false, ImGuiWindowFlags_NoScrollbar );
					{
						struct Locations_t {
							std::string Name;
							D3DXVECTOR3 Coords;
							Locations_t( std::string name, D3DXVECTOR3 coords ) : Name( name ), Coords( coords ) { }
						};

						static std::vector<Locations_t> Locations = {
							Locations_t( xorstr( "Waypoint" ), D3DXVECTOR3( 0, 0, 0 ) ),
							Locations_t( xorstr( "Square" ), D3DXVECTOR3( 156.184, -1043.17, 29.3236 ) ),
							Locations_t( xorstr( "Pier" ), D3DXVECTOR3( -1847.72, -1223.36, 13.8745 ) ),
							Locations_t( xorstr( "Paleto Bay" ), D3DXVECTOR3( -397.605, 6047.57, 32.1797 ) ),
							Locations_t( xorstr( "Central Bank" ), D3DXVECTOR3( 221.781, 217.278, 106.705 ) ),
							Locations_t( xorstr( "Cassino" ), D3DXVECTOR3( 885.322, 16.8489, 80.65 ) ),
							Locations_t( xorstr( "Los Santos Airport" ), D3DXVECTOR3( -975.532, -2880.89, 16.2665 ) ),
							Locations_t( xorstr( "Sandy Shores" ), D3DXVECTOR3( 1681.48, 3251.91, 40.809 ) ),
						};

						static int SeletedIndex = 0;
						bool IsSelected;

						ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 14, 8 ) );
						for ( int i = 0; i < Locations.size( ); i++ )
						{
							IsSelected = SeletedIndex == i;
							if ( ImGui::ListSelectable( Locations[ i ].Name.c_str( ), &IsSelected ) ) SeletedIndex = i;
						}
						ImGui::PopStyleVar( );

						ImGui::Spacing( );

						auto Location = Locations[ SeletedIndex ];
						std::string Loc = xorstr( "Teleport to " ) + Location.Name;
						if ( Custom::Button( Loc.c_str( ), ImVec2( -1, 32 ), 0 ) ) {
							if ( SeletedIndex == 0 )
							{
								Core::Features::Exploits::TpToWaypoint( );
							}
							else {
								Core::SDK::Pointers::pLocalPlayer->SetPos( Location.Coords );
							}
						}
					}
					ImGui::EndChild( );
				}
				ImGui::EndGroup();
				
				ImGui::SameLine();
				
				// Peek Assist Section
				ImGui::BeginGroup();
				{
					ImGui::BeginChild( xorstr( "Peek Assist" ), ImVec2( 460, child_height ), false, ImGuiWindowFlags_NoScrollbar );
					{
						// Save Peek Position Button
						if ( Custom::Button( xorstr( "Save Peek Position" ), ImVec2( -1, 32 ), 0 ) )
						{
							if ( Core::SDK::Pointers::pLocalPlayer )
							{
								D3DXVECTOR3 currentPos = Core::SDK::Pointers::pLocalPlayer->GetPos();
								g_Config.Player.SavedPeekX = currentPos.x;
								g_Config.Player.SavedPeekY = currentPos.y;
								g_Config.Player.SavedPeekZ = currentPos.z;
								g_Config.Player.PeekPositionSaved = true;
								
								std::thread([]()
								{
									NotifyManager::Send(xorstr("Peek position saved!"), 2000);
								}).detach();
							}
						}
						
						static int SavePeekKeyMode = 1;
						ImGui::Keybind( xorstr( "Save Peek Key" ), &g_Config.Player.SavePeekKey, &SavePeekKeyMode );
						
						ImGui::Spacing();
						ImGui::Spacing();
						
						// Teleport to Peek Position Button
						if ( Custom::Button( xorstr( "Teleport to Peek" ), ImVec2( -1, 32 ), 0 ) )
						{
							if ( !g_Config.Player.PeekPositionSaved )
							{
								std::thread([]()
								{
									NotifyManager::Send(xorstr("No peek position saved!"), 2000);
								}).detach();
							}
							else if ( Core::SDK::Pointers::pLocalPlayer )
							{
								D3DXVECTOR3 peekPos(g_Config.Player.SavedPeekX, g_Config.Player.SavedPeekY, g_Config.Player.SavedPeekZ);
								Core::SDK::Pointers::pLocalPlayer->SetPos( peekPos );
								
								std::thread([]()
								{
									NotifyManager::Send(xorstr("Teleported to peek position!"), 2000);
								}).detach();
							}
						}
						
						static int TeleportPeekKeyMode = 1;
						ImGui::Keybind( xorstr( "Teleport Peek Key" ), &g_Config.Player.TeleportPeekKey, &TeleportPeekKeyMode );
						
						ImGui::Spacing();
						ImGui::Spacing();
						
						// Display saved position info
						if ( g_Config.Player.PeekPositionSaved )
						{
							ImGui::TextColored( ImColor( g_Col.FeaturesText ), xorstr( "Saved Position:" ) );
							ImGui::TextColored( ImColor( g_Col.SecundaryFeaturesText ), xorstr( "X: %.2f" ), g_Config.Player.SavedPeekX );
							ImGui::TextColored( ImColor( g_Col.SecundaryFeaturesText ), xorstr( "Y: %.2f" ), g_Config.Player.SavedPeekY );
							ImGui::TextColored( ImColor( g_Col.SecundaryFeaturesText ), xorstr( "Z: %.2f" ), g_Config.Player.SavedPeekZ );
						}
						else
						{
							ImGui::TextColored( ImColor( g_Col.SecundaryFeaturesText ), xorstr( "No position saved" ) );
						}
					}
					ImGui::EndChild();
				}
				ImGui::EndGroup();
			}
			else if (iSubTab == 2)
			{
				Resoucer::Render();
			}
			
			// Subtabs at the bottom
			ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 35.f);
			
			// Measure subtabs width to center them
			ImFont* font = g_Variables.m_FontSecundary;
			float font_size = font->FontSize;
			float totalSubTabsWidth = 0.f;
			
			ImGui::PushFont(font);
			const char* subtabs[] = { "Main", "Teleporte", "Resources" };
			for(int i = 0; i < 3; i++) {
				ImVec2 text_size = ImGui::CalcTextSize(subtabs[i]);
				totalSubTabsWidth += text_size.x + 16.f; // text_size + subtab padding
			}
			ImGui::PopFont();
			totalSubTabsWidth += 10.f * 2; // spacing
			
			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - totalSubTabsWidth) / 2.f);

			ImGui::BeginGroup();
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 0));
				if (Custom::SubTab(xorstr("Main"), iSubTab == 0)) iSubTab = 0;
				ImGui::SameLine();
				if (Custom::SubTab(xorstr("Teleporte"), iSubTab == 1)) iSubTab = 1;
				ImGui::SameLine();
				if (Custom::SubTab(xorstr("Resources"), iSubTab == 2)) iSubTab = 2;
				ImGui::PopStyleVar();
			}
			::ImGui::EndGroup();
		}
		::ImGui::EndGroup( );
	}
}
