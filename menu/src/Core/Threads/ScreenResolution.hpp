#pragma once 
#include <Includes/Includes.hpp> 
#include <Includes/Utils.hpp> 
 
#include <iostream> 
#include <fstream> 
#include <string> 
#include <regex> 
#include <Includes/CustomWidgets/Notify.hpp> 
 
namespace Core 
{ 
	namespace Threads 
	{ 
		class cScreenResolution 
		{ 
		public: 
			void MoveAndSetResolution() 
			{ 
				g_Variables.g_hGameWindow = FindWindowA(xorstr("grcWindow"), nullptr); 
				if (!g_Variables.g_hGameWindow) 
					exit(0); 

				POINT monitorPos; 
				POINT monitorSize; 

				GetTargetMonitorInfo(g_Config.General.SecondMonitor, monitorPos, monitorSize); 

				g_Variables.g_vGameWindowPos = { 
					static_cast<float>(monitorPos.x), 
					static_cast<float>(monitorPos.y) 
				}; 
				g_Variables.g_vGameWindowSize = { 
					static_cast<float>(monitorSize.x), 
					static_cast<float>(monitorSize.y) 
				}; 
				g_Variables.g_vGameWindowCenter = { 
					static_cast<float>(monitorSize.x) / 2.0f, 
					static_cast<float>(monitorSize.y) / 2.0f 
				}; 

				MoveWindow( 
					g_Variables.g_hCheatWindow, 
					monitorPos.x, 
					monitorPos.y, 
					monitorSize.x, 
					monitorSize.y, 
					true 
				); 
			} 

			void Update() 
			{ 
				static int monitor_check_counter = 0; 
				static int failed_checks = 0; 

				while (true) 
				{ 
					try 
					{ 
						if (monitor_check_counter % 34 == 0) { 
							auto monitors = GetAllMonitors(); 
							bool has_second_monitor = monitors.size() >= 2; 

							if (!has_second_monitor && g_Config.General.SecondMonitor) { 
								failed_checks++; 
								if (failed_checks >= 1) { 
									g_Config.General.SecondMonitor = false; 
									NotifyManager::Send(xorstr("Second monitor option disabled - monitor not detected"), 2000); 
									failed_checks = 0; 
								} 
							} 
							else { 
								failed_checks = 0; 
							} 
						} 

						monitor_check_counter++; 
						MoveAndSetResolution(); 
					} 
					catch (const std::exception&) 
					{ 
						// Silently handle - don't show MessageBox every cycle
					} 

					std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
				} 
			}
 
			 
			static std::vector<HMONITOR> GetAllMonitors() { 
				std::vector<HMONITOR> monitors; 
				EnumDisplayMonitors(NULL, NULL, [](HMONITOR hMonitor, HDC, LPRECT, LPARAM lParam) -> BOOL { 
					auto* pMonitors = reinterpret_cast<std::vector<HMONITOR>*>(lParam); 
					pMonitors->push_back(hMonitor); 
					return TRUE; 
					}, reinterpret_cast<LPARAM>(&monitors)); 
				return monitors; 
			} 
 
			 
			static std::pair<POINT, POINT> GetMonitorDimensions(HMONITOR hMonitor) { 
				MONITORINFO mi = { sizeof(MONITORINFO) }; 
				if (!GetMonitorInfo(hMonitor, &mi)) { 
					return { {0, 0}, {1920, 1080} }; // fallback padrão 
				} 
				return { 
					{ mi.rcMonitor.left, mi.rcMonitor.top }, 
					{ mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top } 
				}; 
			} 
 
			 
			static HMONITOR GetSecondaryMonitor() { 
				auto monitors = GetAllMonitors(); 
				for (auto hMonitor : monitors) {
					MONITORINFO mi = { sizeof(MONITORINFO) };
					if (GetMonitorInfo(hMonitor, &mi) && !(mi.dwFlags & MONITORINFOF_PRIMARY)) {
						return hMonitor;
					}
				}
				if (monitors.size() > 1) 
					return monitors[1]; 
				return NULL; 
			} 
 
			 
			static HMONITOR GetPrimaryMonitor() { 
				auto monitors = GetAllMonitors(); 
				for (auto hMonitor : monitors) {
					MONITORINFO mi = { sizeof(MONITORINFO) };
					if (GetMonitorInfo(hMonitor, &mi) && (mi.dwFlags & MONITORINFOF_PRIMARY)) {
						return hMonitor;
					}
				}
				return monitors.empty() ? NULL : monitors[0]; 
			} 
 
			 
			static void GetTargetMonitorInfo(bool useSecondMonitor, POINT& pos, POINT& size) { 
				HMONITOR targetMonitor = useSecondMonitor ? GetSecondaryMonitor() : GetPrimaryMonitor(); 
 
				if (targetMonitor) { 
					auto [monitorPos, monitorSize] = GetMonitorDimensions(targetMonitor); 
					pos = monitorPos; 
					size = monitorSize; 
				} 
				else { 
					 
					pos = { static_cast<LONG>(g_Variables.g_vGameWindowPos.x), static_cast<LONG>(g_Variables.g_vGameWindowPos.y) }; 
					size = { static_cast<LONG>(g_Variables.g_vGameWindowSize.x), static_cast<LONG>(g_Variables.g_vGameWindowSize.y) }; 
				} 
			} 
 
			 
			static void MapPrimaryToSecondary(ImVec2& primaryPos, ImVec2& mappedPos) { 
				HMONITOR primary = GetPrimaryMonitor(); 
				HMONITOR secondary = GetSecondaryMonitor(); 
 
				if (!primary || !secondary || primary == secondary) { 
					mappedPos = primaryPos; 
					return; 
				} 
 
				auto [primaryPosInfo, primarySize] = GetMonitorDimensions(primary); 
				auto [secondaryPosInfo, secondarySize] = GetMonitorDimensions(secondary); 
 
				float xRatio = static_cast<float>(secondarySize.x) / primarySize.x; 
				float yRatio = static_cast<float>(secondarySize.y) / primarySize.y; 
 
				mappedPos.x = primaryPos.x * xRatio + secondaryPosInfo.x; 
				mappedPos.y = primaryPos.y * yRatio + secondaryPosInfo.y; 
			} 
		}; 
 
		inline cScreenResolution g_ScreenResolution; 
	} 
}