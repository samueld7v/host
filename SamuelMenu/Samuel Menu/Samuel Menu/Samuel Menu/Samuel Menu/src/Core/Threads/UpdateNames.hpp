#include <Includes/Includes.hpp>
#include <Includes/Utils.hpp>
#include <Core/Offsets.hpp>
#include <Core/Core.hpp>


#include <fstream>
#include <string>
#include <regex>
#include <iostream>

#define CURL_STATIC_LIB
#include <Security/Api/curl/curl.h>

using json = nlohmann::json;

namespace Core
{
	namespace Threads
	{
		class cUpdateNames
		{
		private:
			std::string ServerIp;
			std::string ServerToken;
			std::string DirFiveM;
			std::string RedirectUrl;
			std::string logFile = xorstr("D:\\mjqb8hv\\Samuel Menu\\esp_debug.log");
		public:
			std::unordered_map<int, Core::SDK::Game::NetworkInfo> NetworkMap;
		private:
			void Log(const std::string& msg) {
				std::ofstream log(logFile, std::ios::app);
				if (log) log << msg << std::endl;
			}

			static size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp)
			{
				((std::string*)userp)->append((char*)contents, size * nmemb);
				return size * nmemb;
			}

			bool TryGetServerIpFromRegistry() {
			HKEY hKey;
			if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\CitizenFX\\FiveM", 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
				Log(xorstr("[API] RegOpenKey CitizenFX failed"));
				return false;
			}
			wchar_t lastServer[512] = {};
			DWORD size = sizeof(lastServer);
			if (RegQueryValueExW(hKey, L"Last Joined Server", NULL, NULL, (LPBYTE)lastServer, &size) != ERROR_SUCCESS) {
				Log(xorstr("[API] RegQuery Last Joined Server failed"));
				RegCloseKey(hKey);
				return false;
			}
			RegCloseKey(hKey);
			int len = WideCharToMultiByte(CP_UTF8, 0, lastServer, -1, NULL, 0, NULL, NULL);
			if (len <= 0) return false;
			std::string ip(len, 0);
			WideCharToMultiByte(CP_UTF8, 0, lastServer, -1, &ip[0], len, NULL, NULL);
			ServerIp = ip;
			Log(xorstr("[API] Raw registry value: ") + ServerIp);
			std::regex ipPattern(R"((\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}:\d{2,5}))");
			std::smatch match;
			if (std::regex_search(ServerIp, match, ipPattern)) {
				ServerIp = match[1].str();
				return true;
			}
			ServerIp.clear();
			Log(xorstr("[API] No IP:port pattern in registry value"));
			return false;
		}

		bool TryGetServerIpFromFile(const std::string& path) {
			std::ifstream File(path, std::ios::binary);
			if (!File) {
				Log(xorstr("[API] File not found: ") + path);
				return false;
			}
			std::string content((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
			Log(xorstr("[API] File read: ") + path + xorstr(" (") + std::to_string(content.size()) + xorstr(" bytes)"));
			if (content.empty()) return false;
			std::regex ipPattern(R"((\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}:\d{2,5}))");
			std::smatch match;
			if (std::regex_search(content, match, ipPattern)) {
				ServerIp = match[1].str();
				Log(xorstr("[API] Found IP from file: ") + ServerIp);
				return true;
			}
			return false;
		}

		bool TryGetServerIpFromMemory() {
			if (!Mem.ModBase || !Mem.ModBaseSize) return false;
			uintptr_t scanEnd = Mem.ModBase + min(Mem.ModBaseSize, (uintptr_t)0x2000000);
			const size_t blockSize = 4096 * 4;
			std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(blockSize);
			std::regex ipPattern(R"((\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}:\d{2,5}))");
			for (uintptr_t addr = Mem.ModBase; addr < scanEnd; addr += blockSize) {
				SIZE_T bytesRead = 0;
				if (!ReadProcessMemory(Mem.ProcHandle, (LPCVOID)addr, data.get(), blockSize, &bytesRead))
					continue;
				std::string sdata((const char*)data.get(), bytesRead);
				std::smatch match;
				if (std::regex_search(sdata, match, ipPattern)) {
					ServerIp = match[1].str();
					Log(xorstr("[API] Found IP from memory scan: ") + ServerIp);
					return true;
				}
			}
			Log(xorstr("[API] Memory scan found no IP"));
			return false;
		}

		bool TryGetServerIpFromWindowTitle() {
			HWND hwnd = FindWindowA(NULL, xorstr("Grand Theft Auto V"));
			if (!hwnd) {
				Log(xorstr("[API] GTA V window not found"));
				return false;
			}
			wchar_t title[256] = {};
			GetWindowTextW(hwnd, title, 256);
			int len = WideCharToMultiByte(CP_UTF8, 0, title, -1, NULL, 0, NULL, NULL);
			if (len <= 0) return false;
			std::string titleA(len, 0);
			WideCharToMultiByte(CP_UTF8, 0, title, -1, &titleA[0], len, NULL, NULL);
			Log(xorstr("[API] Window title: ") + titleA);
			if (titleA.find(xorstr("FiveM")) == std::string::npos) return false;
			std::regex ipPattern(R"((\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}:\d{2,5}))");
			std::smatch match;
			if (std::regex_search(titleA, match, ipPattern)) {
				ServerIp = match[1].str();
				Log(xorstr("[API] Found IP from window title: ") + ServerIp);
				return true;
			}
			Log(xorstr("[API] No IP in window title"));
			return false;
		}

		std::string GetServerToken() {

			if (DirFiveM.empty())
			{
				char value[255];
				DWORD BufferSize = 8192;

				auto GetDirFiveM = RegGetValue(HKEY_CURRENT_USER, xorstr("Software\\CitizenFX\\FiveM"), xorstr("Last Run Location"), RRF_RT_REG_SZ, NULL, (PVOID)&value, &BufferSize);

				if (GetDirFiveM != ERROR_SUCCESS) {
					Log(xorstr("[API] Failed to get FiveM dir from registry"));
					return xorstr("");
				}

				DirFiveM = (std::string)value;
				Log(xorstr("[API] FiveM dir: ") + DirFiveM);
				if (!DirFiveM.empty() && DirFiveM.back() != '\\')
					DirFiveM += '\\';
			}

			ServerIp.clear();
			Log(xorstr("[API] === Server IP discovery ==="));

			if (!DirFiveM.empty()) {
				std::vector<std::string> paths = {
					DirFiveM + xorstr("data\\cache\\crashometry"),
					DirFiveM + xorstr("data\\cache\\crashometry-new"),
					DirFiveM + xorstr("data\\cache\\launcher_report"),
					DirFiveM + xorstr("data\\cache\\error_report"),
					DirFiveM + xorstr("data\\cache\\crashometry\\"),
					DirFiveM + xorstr("data\\cache\\crashometry-new\\"),
					DirFiveM + xorstr("..\\CitizenFX\\cache\\crashometry"),
					DirFiveM + xorstr("..\\..\\Roaming\\CitizenFX\\cache\\crashometry"),
				};
				for (const auto& p : paths) {
					if (TryGetServerIpFromFile(p)) break;
				}
			}

			if (ServerIp.empty())
				TryGetServerIpFromRegistry();

			if (ServerIp.empty())
				TryGetServerIpFromMemory();

			if (ServerIp.empty())
				TryGetServerIpFromWindowTitle();

			if (ServerIp.empty()) {
				Log(xorstr("[API] ALL IP discovery methods failed!"));
				return xorstr("");
			}

			g_Variables.ServerIp = ServerIp;
			Log(xorstr("[API] Connecting to server: http://") + ServerIp);

			std::string ResponseStr;
			std::string ReqUrl = xorstr("http://") + ServerIp;

			CURL* hnd;
			CURLcode res;
			hnd = curl_easy_init();
			if (!hnd) {
				Log(xorstr("[API] curl_easy_init failed"));
				return xorstr("");
			}
			curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, xorstr("GET"));
			curl_easy_setopt(hnd, CURLOPT_URL, ReqUrl.c_str());
			curl_easy_setopt(hnd, CURLOPT_TIMEOUT, 5L);
			curl_easy_setopt(hnd, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 10L);
			curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallBack);
			curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &ResponseStr);
			curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0L);
			curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYHOST, 0L);

			res = curl_easy_perform(hnd);

			if (res == CURLE_OK) {
				char* FinalUrl = NULL;
				curl_easy_getinfo(hnd, CURLINFO_EFFECTIVE_URL, &FinalUrl);
				if (FinalUrl) {
					RedirectUrl = std::string(FinalUrl);
					Log(xorstr("[API] Effective URL: ") + RedirectUrl);
				}
			} else {
				Log(xorstr("[API] Redirect request failed: ") + std::to_string(res) + xorstr(" (") + curl_easy_strerror(res) + xorstr(")"));
			}
			curl_easy_cleanup(hnd);

			if (RedirectUrl.empty()) {
				Log(xorstr("[API] No redirect URL obtained"));
				return xorstr("");
			}

			auto pos = RedirectUrl.find_last_of('/');
			if (pos == std::string::npos || pos + 1 >= RedirectUrl.size()) {
				Log(xorstr("[API] No token in redirect URL"));
				return xorstr("");
			}

			std::string Token = RedirectUrl.substr(pos + 1);
			Log(xorstr("[API] Server token: ") + Token);
			return Token;
		}
		public:

			nlohmann::json GetPlayerData() {
				ServerToken = GetServerToken();

				if (ServerToken.empty()) {
					Log(xorstr("[API] Empty server token, aborting"));
					return NULL;
				}
				Log(xorstr("[API] Server token: ") + ServerToken);

				std::string ApiUrl = xorstr("https://frontend.cfx-services.net/api/servers/single/") + ServerToken;
				Log(xorstr("[API] Fetching players from: ") + ApiUrl);

				std::string ResponseStr;
				CURL* hnd;
				CURLcode res;
				hnd = curl_easy_init();
				if (!hnd) {
					Log(xorstr("[API] curl_easy_init failed!"));
					return NULL;
				}
				curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, xorstr("GET"));
				curl_easy_setopt(hnd, CURLOPT_URL, ApiUrl.c_str());
				curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0L);
				curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYHOST, 0L);

				struct curl_slist* headers = NULL;
				headers = curl_slist_append(headers, xorstr("User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"));
				headers = curl_slist_append(headers, xorstr("Accept: application/json"));
				curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

				curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallBack);
				curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &ResponseStr);

				curl_easy_setopt(hnd, CURLOPT_TIMEOUT, 10L);
				curl_easy_setopt(hnd, CURLOPT_FOLLOWLOCATION, 1L);

				res = curl_easy_perform(hnd);

				curl_slist_free_all(headers);
				curl_easy_cleanup(hnd);

				if (res != CURLE_OK) {
					Log(xorstr("[API] curl error: ") + std::to_string(res) + xorstr(" (") + curl_easy_strerror(res) + xorstr(")"));
					return NULL;
				}

				if (ResponseStr.empty()) {
					Log(xorstr("[API] Empty response from API"));
					return NULL;
				}

				Log(xorstr("[API] Response size: ") + std::to_string(ResponseStr.size()) + xorstr(" bytes"));

				try {
					nlohmann::json ResponseJson = json::parse(ResponseStr);
					if (ResponseJson.contains(xorstr("Data")) && ResponseJson[xorstr("Data")].contains(xorstr("players"))) {
						auto& players = ResponseJson[xorstr("Data")][xorstr("players")];
						Log(xorstr("[API] Found ") + std::to_string(players.size()) + xorstr(" players in API response"));
						return players;
					} else {
						Log(xorstr("[API] Response JSON missing Data.players"));
						return NULL;
					}
				} catch (const std::exception& e) {
					Log(xorstr("[API] JSON parse error: ") + std::string(e.what()));
					return NULL;
				}

				return NULL;
			}

			void GetPlayerNames()
			{
				nlohmann::json PlayersArr = GetPlayerData();

				if (PlayersArr == NULL || !PlayersArr.is_array())
					return;

				for (const auto& Player : PlayersArr)
				{
					if (Player.is_null() || !Player.is_object() || !Player.contains(xorstr("id")) || !Player.contains(xorstr("name")))
						continue;

					int PlayerId = -1;
					if (Player[xorstr("id")].is_number()) {
						PlayerId = Player[xorstr("id")].get<int>();
					} else if (Player[xorstr("id")].is_string()) {
						try { PlayerId = std::stoi(Player[xorstr("id")].get<std::string>()); } catch (...) { continue; }
					}

					if (PlayerId == -1) continue;

					std::string PlayerName = xorstr("");
					if (Player[xorstr("name")].is_string()) {
						PlayerName = Player[xorstr("name")].get<std::string>();
					} else if (Player[xorstr("name")].is_number()) {
						PlayerName = std::to_string(Player[xorstr("name")].get<int>());
					}

					std::string Discord, SteamId;

					if (Player.contains(xorstr("identifiers"))) {
						nlohmann::json Identifiers = Player[xorstr("identifiers")];
						if (!Identifiers.is_null() && Identifiers.is_array())
						{
							for (const auto& Identifier : Identifiers)
							{
								if (!Identifier.is_string())
									continue;

								std::string IdentifierVal = Identifier.get<std::string>();

								if (IdentifierVal.find(xorstr("discord:")) != std::string::npos)
									Discord = IdentifierVal.substr(8);
								else if (IdentifierVal.find(xorstr("steam:")) != std::string::npos)
									SteamId = IdentifierVal.substr(6);
							}
						}
					}

					if (!PlayerName.empty()) {
						NetworkMap[PlayerId] =
						{
							PlayerName, Discord, SteamId
						};
					}
				}
			}

			void Update()
			{
				while (true)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(3500));
					try {
						GetPlayerNames();
					}
					catch (const std::exception& e) {
						std::string errorMessage = xorstr("Crash Detected. Code: 2\nException: ");
						errorMessage += e.what();
						MessageBox(NULL, errorMessage.c_str(), xorstr("Error"), MB_ICONERROR);
						break;
					}
					catch (...) {
						MessageBox(NULL, xorstr("Crash Detected. Code: 2\nUnknown exception caught."), xorstr("Error"), MB_ICONERROR);
						break;
					}

				}
			}
		};

		inline cUpdateNames g_UpdateNames;
	}

}
