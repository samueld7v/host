#pragma once

#include <KeyAuth/auth.hpp>
#include <Security/xorstr.hpp>

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>

namespace Auth {
	inline std::string ToLower(std::string value) {
		std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
			return static_cast<char>(std::tolower(c));
		});
		return value;
	}

	inline bool IsHwidError(const std::string& message) {
		return ToLower(message).find("hwid") != std::string::npos;
	}

	inline std::string FormatLoginMessage(const std::string& message) {
		if (message.empty()) {
			return "Nao foi possivel validar sua key.";
		}

		if (IsHwidError(message)) {
			return "HWID nao autorizado para esta key.";
		}

		return message;
	}

	inline std::string GetSavedKeyPath() {
		const char* localAppData = std::getenv("LOCALAPPDATA");
		std::filesystem::path basePath = localAppData && *localAppData
			? std::filesystem::path(localAppData)
			: std::filesystem::current_path();
		std::filesystem::path saveDirectory = basePath / "HyperX";
		std::filesystem::create_directories(saveDirectory);
		return (saveDirectory / "saved_key.txt").string();
	}

	inline std::string LoadSavedKey() {
		std::ifstream savedKeyFile(GetSavedKeyPath());
		if (!savedKeyFile.is_open()) {
			return "";
		}

		std::string key;
		std::getline(savedKeyFile, key);
		return key;
	}

	inline void SaveKey(const std::string& key) {
		std::ofstream savedKeyFile(GetSavedKeyPath(), std::ios::trunc);
		if (!savedKeyFile.is_open()) {
			return;
		}

		savedKeyFile << key;
	}

	inline KeyAuth::api KeyAuthApp(
		std::string(skCrypt("Samuel Menu").decrypt()),
		std::string(skCrypt("NXbH4Pldyf").decrypt()),
		std::string(skCrypt("9066e84a389f02e3b11f6679ab1cf320fd6e2c66a19f80965b91bae5b82ec4a7").decrypt()),
		std::string(skCrypt("1.0").decrypt()),
		std::string(skCrypt("https://keyauth.win/api/1.3/").decrypt()),
		std::string(skCrypt("").decrypt())
	);

	inline std::string g_SavedLicenseKey;
	inline std::mutex g_AuthMutex;
	inline bool g_SessionValid = false;
	inline bool g_SessionChecked = false;

	inline void InitializeKeyAuth() {
		static bool initialized = false;
		if (!initialized) {
			KeyAuthApp.init();
			initialized = true;
		}
	}

	inline bool LoginWithLicense(const std::string& key, std::string& message) {
		if (key.empty()) {
			message = "Digite sua key da Alt.";
			return false;
		}

		{
			std::lock_guard<std::mutex> lock(g_AuthMutex);
			KeyAuthApp.license(key);
			message = FormatLoginMessage(KeyAuthApp.response.message);
			if (KeyAuthApp.response.success) {
				SaveKey(key);
				g_SavedLicenseKey = key;
				g_SessionValid = true;
			}
		}
		return KeyAuthApp.response.success;
	}

	inline void SessionKeepAlive() {
		while (true) {
			std::this_thread::sleep_for(std::chrono::minutes(5));
			if (!g_SessionValid) {
				g_SessionChecked = true;
				continue;
			}

			std::string savedKey = LoadSavedKey();
			if (savedKey.empty() && g_SavedLicenseKey.empty()) {
				g_SessionValid = false;
				g_SessionChecked = true;
				continue;
			}

			std::string keyToUse = g_SavedLicenseKey.empty() ? savedKey : g_SavedLicenseKey;
			
			{
				std::lock_guard<std::mutex> lock(g_AuthMutex);
				KeyAuthApp.license(keyToUse);
				if (!KeyAuthApp.response.success) {
					g_SessionValid = false;
				}
			}
			g_SessionChecked = true;
		}
	}
}
