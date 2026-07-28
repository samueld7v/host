#pragma once

#include <KeyAuth/auth.hpp>
#include <KeyAuth/includes.hpp>
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
	inline std::string g_SessionToken;
	inline std::string g_SavedLicenseKey;
	inline std::mutex g_AuthMutex;
	inline bool g_SessionValid = false;
	inline bool g_SessionChecked = false;

	const std::string API_URL = skCrypt("https://host-production-f6a9.up.railway.app/api").decrypt();

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
		if (!savedKeyFile.is_open()) return "";
		std::string key;
		std::getline(savedKeyFile, key);
		return key;
	}

	inline void SaveKey(const std::string& key) {
		std::ofstream savedKeyFile(GetSavedKeyPath(), std::ios::trunc);
		if (!savedKeyFile.is_open()) return;
		savedKeyFile << key;
	}

	inline std::string HttpPost(const std::string& url, const std::string& jsonBody) {
		CURL* curl = curl_easy_init();
		if (!curl) return "";
		std::string response;
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](void* contents, size_t size, size_t nmemb, void* userp) -> size_t {
			((std::string*)userp)->append((char*)contents, size * nmemb);
			return size * nmemb;
		});
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
		curl_easy_perform(curl);
		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
		return response;
	}

	inline void InitializeKeyAuth() {
	}

	inline bool LoginWithLicense(const std::string& key, std::string& message) {
		if (key.empty()) {
			message = "Digite sua key.";
			return false;
		}

		std::string hwid = utils::get_hwid();
		nlohmann::json body;
		body["key"] = key;
		body["hwid"] = hwid;

		std::string resp = HttpPost(API_URL + "/auth/handshake", body.dump());
		if (resp.empty()) {
			message = "API offline.";
			return false;
		}

		try {
			auto json = nlohmann::json::parse(resp);
			if (json.value("ok", false)) {
				g_SessionToken = json.value("sessionToken", "");
				SaveKey(key);
				g_SavedLicenseKey = key;
				g_SessionValid = true;
				message = "Autenticado com sucesso!";
				return true;
			}
			message = FormatLoginMessage(json.value("error", "Key invalida."));
		} catch (...) {
			message = "Erro ao processar resposta.";
		}
		return false;
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
			std::string hwid = utils::get_hwid();
			nlohmann::json body;
			body["key"] = keyToUse;
			body["hwid"] = hwid;

			std::string resp = HttpPost(API_URL + "/auth/handshake", body.dump());
			if (!resp.empty()) {
				try {
					auto json = nlohmann::json::parse(resp);
					if (json.value("ok", false)) {
						g_SessionToken = json.value("sessionToken", "");
						g_SessionChecked = true;
						continue;
					}
				} catch (...) {}
			}
			g_SessionValid = false;
			g_SessionChecked = true;
		}
	}
}
