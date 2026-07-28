#pragma once
#include <Includes/includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <Includes/CustomWidgets/Notify.hpp>

using namespace std;

namespace World {

	inline int PlayerSeletedIndex = -1;

	void Render( )
	{
		bool PlayerIsSelected;
		static int VehicleSeletedIndex = -1;
		bool VehicleIsSelected;
		static bool IsSpectating = false;

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
				ImGui::BeginChild( xorstr( "Player List" ), ImVec2( col_width, child_height ), false, ImGuiWindowFlags_NoScrollbar );
				{
					ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 14, 8 ) );
					for ( int i = 0; i < Core::SDK::Game::EntityList.size( ); i++ )
					{
						if ( Core::SDK::Game::EntityList[ i ].Ped == Core::SDK::Pointers::pLocalPlayer )
							continue;

						if ( Core::SDK::Game::EntityList[ i ].PedType != 2 )
							continue;

						PlayerIsSelected = PlayerSeletedIndex == i;
						std::string displayName = Core::SDK::Game::EntityList[ i ].NetworkInfo.UserName + " [" + std::to_string( ( int )Core::SDK::Game::EntityList[ i ].Distance ) + "m]";
						if ( ImGui::ListSelectable( displayName.c_str( ), &PlayerIsSelected ) ) PlayerSeletedIndex = i;
					}
					ImGui::PopStyleVar( );
				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );
			ImGui::SameLine( );
			ImGui::BeginGroup( );
			{
				float child_height_top = ImGui::GetContentRegionAvail().y * 0.55f;
				ImGui::BeginChild( xorstr( "Actions for Players" ), ImVec2( col_width, child_height_top ), false, ImGuiWindowFlags_NoScrollbar );
				{
					if ( PlayerSeletedIndex == -1 ) {
						ImGui::TextColored( ImColor( g_Col.SecundaryText ), xorstr( "Select Player" ) );
					}
					else
					{
						auto SelectedPed = Core::SDK::Game::EntityList[ PlayerSeletedIndex ];
						ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 14, 4 ) );

						ImGui::TextColored( ImColor( g_Col.FeaturesText ), xorstr( "Name:" ) ); ImGui::SameLine( );
						ImGui::TextColored( ImColor( g_Col.SecundaryText ), SelectedPed.NetworkInfo.UserName.c_str());
						ImGui::TextColored( ImColor( g_Col.FeaturesText ), xorstr( "Id:" ) ); ImGui::SameLine( );
						ImGui::TextColored( ImColor( g_Col.SecundaryText ), std::to_string( SelectedPed.Id ).c_str( ) );
						ImGui::TextColored( ImColor( g_Col.FeaturesText ), xorstr( "Distance:" ) ); ImGui::SameLine( );
						ImGui::TextColored( ImColor( g_Col.SecundaryText ), std::to_string( SelectedPed.Distance ).c_str( ) );
						ImGui::TextColored( ImColor( g_Col.FeaturesText ), xorstr( "Weapon:" ) ); ImGui::SameLine( );
						ImGui::TextColored( ImColor( g_Col.SecundaryText ), SelectedPed.WeaponName.c_str( ) );
						
						if ( Custom::CheckBox( xorstr( "Friend" ), &Core::SDK::Game::FriendMap[ SelectedPed.Ped ] ) )
						{
							bool IsFriend = Core::SDK::Game::FriendMap[ SelectedPed.Ped ];
							std::string Msg = SelectedPed.NetworkInfo.UserName + ( IsFriend ? xorstr( " added to friends!" ) : xorstr( " removed from friends!" ) );
							std::thread( [ Msg ] ( ) {
								NotifyManager::Send( Msg, 4000 );
							} ).detach( );
						}

						ImGui::Spacing( );

						if (Custom::Button(IsSpectating ? xorstr("Stop Spectating") : xorstr("Spectate Player"), ImVec2(-1, 30), 0))
						{
							if (SelectedPed.Ped) {
								IsSpectating = !IsSpectating;
								bool currentSpectating = IsSpectating;
								std::thread spectateThread([SelectedPed, currentSpectating]() {
									Core::SDK::Pointers::pLocalPlayer->SpectatePlayer(currentSpectating, (uintptr_t)SelectedPed.Ped);
									});
								spectateThread.detach();
							}
						}

						if ( Custom::Button( xorstr( "Copy Outfit" ), ImVec2( -1, 30 ), 0 ) )
						{
							if (SelectedPed.Ped) {
								std::thread copyCharacter([SelectedPed]() {
									Core::SDK::Pointers::pWorld->CopyVariation(SelectedPed.Ped, Core::SDK::Pointers::pLocalPlayer, true);
									});
								copyCharacter.detach();
							}
						}

						if (Custom::Button(xorstr("Pull Player"), ImVec2(-1, 30), 0))
						{
							if (SelectedPed.Ped && Core::SDK::Pointers::pLocalPlayer) {
								D3DXVECTOR3 myPos = Core::SDK::Pointers::pLocalPlayer->GetPos();
								SelectedPed.Ped->SetPos(myPos);
								std::thread([]() {
									NotifyManager::Send(xorstr("Player Pulled!"), 4000);
								}).detach();
							}
						}

						if (Custom::Button(xorstr("Kill Player"), ImVec2(-1, 30), 0))
						{
							if (SelectedPed.Ped) {
								// Mata o player selecionado externamente alterando a vida para o valor de morte
								SelectedPed.Ped->SetHealth(101.0f);
								std::thread([]() {
									NotifyManager::Send(xorstr("Player Killed!"), 4000);
								}).detach();
							}
						}

						ImGui::PopStyleVar( );
					}
				}
				ImGui::EndChild( );
				
				float child_height_bottom = ImGui::GetContentRegionAvail().y - 10.f;
				ImGui::BeginChild( xorstr( "Actions for Vehicles" ), ImVec2( col_width, child_height_bottom ), false, ImGuiWindowFlags_NoScrollbar );
				{
					if ( VehicleSeletedIndex == -1 ) {
						ImGui::TextColored( ImColor( g_Col.SecundaryText ), xorstr( "Select Vehicle" ) );
					}
					else
					{
						auto SelectedVeh = Core::SDK::Game::VehicleList[ VehicleSeletedIndex ];
						ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 14, 4 ) );

						ImGui::TextColored( ImColor( g_Col.FeaturesText ), xorstr( "Name:" ) ); ImGui::SameLine( );
						ImGui::TextColored( ImColor( g_Col.SecundaryText ), SelectedVeh.Name.c_str( ) );

						ImGui::Spacing( );

						if ( Custom::Button( xorstr( "Teleport to Vehicle" ), ImVec2( -1, 30 ), 0 ) )
						{
							Core::SDK::Pointers::pLocalPlayer->SetPos( SelectedVeh.Pos );
						}

						if ( Custom::Button( xorstr( "Pull Vehicle" ), ImVec2( -1, 30 ), 0 ) )
						{
							Features::Exploits::PullVehicle( SelectedVeh.Pointer );
						}

						// Assinatura atualizada dinamicamente caso não exista
						if (!Core::g_Offsets.m_BreakOffWheel) {
							Core::g_Offsets.m_BreakOffWheel = Core::Mem.FindSignatureStr("48 8b c4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 56 41 57 48 83 ec ? 80 3d ? ? ? ? ? 0f 29 78");
						}

						if ( Custom::Button( xorstr( "Break Wheels" ), ImVec2( -1, 30 ), 0 ) )
						{
							std::thread([SelectedVeh]() {
								auto vehicle = SelectedVeh.Pointer;
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

						bool IsLocked = SelectedVeh.Pointer->IsLocked( );
						if ( Custom::Button( IsLocked ? xorstr( "Unlock" ) : xorstr( "Lock" ), ImVec2( -1, 30 ), 0 ) )
						{
							SelectedVeh.Pointer->DoorState( IsLocked );
						}

						ImGui::PopStyleVar( );
					}
				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );
			ImGui::SameLine( );
			ImGui::BeginGroup( );
			{
				float child_height = ImGui::GetContentRegionAvail().y - 10.f;
				ImGui::BeginChild( xorstr( "Vehicle List" ), ImVec2( col_width, child_height), false, ImGuiWindowFlags_NoScrollbar );
				{
					ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 14, 8 ) );
					for ( int i = 0; i < Core::SDK::Game::VehicleList.size( ); i++ )
					{
						VehicleIsSelected = VehicleSeletedIndex == i;
						std::string displayName = Core::SDK::Game::VehicleList[ i ].Name + " [" + std::to_string( ( int )Core::SDK::Game::VehicleList[ i ].Dist ) + "m]";
						if ( ImGui::ListSelectable( displayName.c_str( ), &VehicleIsSelected ) ) VehicleSeletedIndex = i;
					}
					ImGui::PopStyleVar( );
				}
				ImGui::EndChild( );
			}
			ImGui::EndGroup( );

		}
		ImGui::EndGroup( );
	}
}