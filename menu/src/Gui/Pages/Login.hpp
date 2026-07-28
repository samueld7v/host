#pragma once
#include <Includes/Includes.hpp>
#include <Auth/KeyAuthApp.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <math.h>

using namespace std;

namespace Login {

	void Render() {
		static bool loaded_saved_key = false;
		if (!loaded_saved_key) {
			std::string saved_key = Auth::LoadSavedKey();
			if (!saved_key.empty()) {
				strncpy_s(g_MenuInfo.key, saved_key.c_str(), sizeof(g_MenuInfo.key) - 1);
			}
			loaded_saved_key = true;
		}

		ImDrawList* drawList = ImGui::GetWindowDrawList();
		ImVec2 p = ImGui::GetWindowPos();

		ImVec4 hyperx_red = ImVec4(1.0f, 0.1f, 0.15f, 1.0f);
		ImVec4 hyperx_red_hover = ImVec4(1.0f, 0.2f, 0.25f, 1.0f);
		ImVec4 hyperx_red_active = ImVec4(0.8f, 0.05f, 0.1f, 1.0f);

		ImGui::SetCursorPos(ImVec2(g_MenuInfo.LoginSize.x - 25, 10));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0,0,0,0));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 0.2f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.f, 0.f, 0.f, 0.4f));
		if (ImGui::Button("X", ImVec2(20, 20))) {
			exit(0);
		}
		ImGui::PopStyleColor(4);

		if (!g_MenuInfo.show_product_selection) {
			if (g_Variables.Logo) {
				float logoWidth = 200.f; float logoHeight = 85.f;
				ImGui::SetCursorPos(ImVec2(g_MenuInfo.LoginSize.x / 2 - logoWidth / 2, 5));
				ImGui::Image((void*)g_Variables.Logo, ImVec2(logoWidth, logoHeight));
			}

			drawList->AddLine(ImVec2(p.x, p.y + 95), ImVec2(p.x + g_MenuInfo.LoginSize.x, p.y + 95), ImGui::GetColorU32(ImVec4(0.15f, 0.15f, 0.15f, 1.f)));

			ImGui::SetCursorPos(ImVec2(g_MenuInfo.LoginSize.x / 2 - 200, 150));
			ImGui::PushItemWidth(400);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(15 / 255.f, 15 / 255.f, 15 / 255.f, 1.f));
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12, 8));
			ImGui::PushFont(g_Variables.m_FontBigSmall);
			ImGui::InputTextWithHint("##KeyInput", "key...", g_MenuInfo.key, sizeof(g_MenuInfo.key));
			ImGui::PopFont();
			ImGui::PopStyleVar(3);
			ImGui::PopStyleColor(2);
			ImGui::PopItemWidth();

			ImGui::SetCursorPos(ImVec2(g_MenuInfo.LoginSize.x / 2 - 200, 220));
			ImGui::PushStyleColor(ImGuiCol_Button, hyperx_red);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hyperx_red_hover);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, hyperx_red_active);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.f));
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 20.0f);
			ImGui::PushFont(g_Variables.m_FontNormal);
			if (ImGui::Button("Login", ImVec2(400, 45))) {
				std::string response_message;
				g_MenuInfo.login_success = Auth::LoginWithLicense(g_MenuInfo.key, response_message);
				g_MenuInfo.server_response = response_message;
				g_MenuInfo.show_product_selection = g_MenuInfo.login_success;
			}
			ImGui::PopFont();
			ImGui::PopStyleVar();
			ImGui::PopStyleColor(4);

			if (!g_MenuInfo.server_response.empty()) {
				ImGui::SetCursorPos(ImVec2(g_MenuInfo.LoginSize.x / 2 - 200, 275));
				ImVec4 message_color = g_MenuInfo.login_success
					? ImVec4(0.15f, 0.85f, 0.25f, 1.f)
					: (Auth::IsHwidError(g_MenuInfo.server_response)
						? ImVec4(1.0f, 0.45f, 0.2f, 1.f)
						: ImVec4(1.0f, 0.2f, 0.2f, 1.f));
				ImGui::PushStyleColor(ImGuiCol_Text, message_color);
				ImGui::PushTextWrapPos(g_MenuInfo.LoginSize.x / 2 + 200);
				ImGui::TextWrapped("%s", g_MenuInfo.server_response.c_str());
				ImGui::PopTextWrapPos();
				ImGui::PopStyleColor();
			}

			if (g_MenuInfo.IsLogged && Auth::g_SessionChecked && !Auth::g_SessionValid) {
				ImGui::SetCursorPos(ImVec2(g_MenuInfo.LoginSize.x / 2 - 200, 320));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));
				ImGui::TextWrapped("Sessao expirada. Pressione F5 para re-autenticar ou reinicie o menu.");
				ImGui::PopStyleColor();
			}

		} else {
			if (g_Variables.Logo) {
				float logoWidth = 140.f; float logoHeight = 55.f;
				ImGui::SetCursorPos(ImVec2(g_MenuInfo.LoginSize.x / 2 - logoWidth / 2, 5));
				ImGui::Image((void*)g_Variables.Logo, ImVec2(logoWidth, logoHeight));
			}

			drawList->AddLine(ImVec2(p.x, p.y + 65), ImVec2(p.x + g_MenuInfo.LoginSize.x, p.y + 65), ImGui::GetColorU32(ImVec4(0.15f, 0.15f, 0.15f, 1.f)));

			float padding = 20.f;
			float colWidth1 = (g_MenuInfo.LoginSize.x - padding * 3) * 0.4f;
			float colWidth2 = (g_MenuInfo.LoginSize.x - padding * 3) * 0.6f;
			float childHeight = g_MenuInfo.LoginSize.y - 80 - padding;

			ImGui::SetCursorPos(ImVec2(padding, 80));
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.2f, 0.2f, 0.2f, 1.f));
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 6.0f);
			ImGui::BeginChild("ProductsList", ImVec2(colWidth1, childHeight), true);
			ImGui::SetCursorPos(ImVec2(10, 10));
			ImGui::PushFont(g_Variables.m_FontSecundary);
			ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.f), "Products");
			ImGui::PopFont();
			ImGui::SetCursorPos(ImVec2(10, 40));
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(15 / 255.f, 15 / 255.f, 15 / 255.f, 1.f));
			ImGui::PushStyleColor(ImGuiCol_Border, hyperx_red);
			ImGui::BeginChild("ProductItem", ImVec2(colWidth1 - 20, 45), true);
			ImGui::SetCursorPos(ImVec2(10, 13));
			ImGui::PushFont(g_Variables.m_FontSecundary);
			ImGui::TextColored(ImVec4(0.9f, 0.9f, 0.9f, 1.f), "HyperX-External-FiveM");
			ImGui::PopFont();
			ImGui::EndChild();
			ImGui::PopStyleColor(2);
			ImGui::EndChild();
			ImGui::PopStyleVar();
			ImGui::PopStyleColor(2);

			ImGui::SetCursorPos(ImVec2(padding * 2 + colWidth1, 80));
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.2f, 0.2f, 0.2f, 1.f));
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 6.0f);
			ImGui::BeginChild("ProductDetails", ImVec2(colWidth2, childHeight), true);
			ImGui::SetCursorPos(ImVec2(10, 10));
			ImGui::PushFont(g_Variables.m_FontBigSmall);
			ImGui::TextColored(hyperx_red, "HyperX-External-FiveM");
			ImGui::PopFont();
			ImGui::PushFont(g_Variables.m_FontSecundary);
			ImGui::SetCursorPos(ImVec2(10, 45));
			ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.f), "Status: ");
			ImGui::SameLine(0, 5);
			ImGui::TextColored(ImVec4(0.1f, 0.8f, 0.1f, 1.f), "Undetected");
			ImGui::SetCursorPos(ImVec2(10, 70));
			ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.f), "Owned: ");
			ImGui::SameLine(0, 5);
			ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.f), "Yes (Lifetime)");
			ImGui::SetCursorPos(ImVec2(10, 95));
			ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.f), "Version: ");
			ImGui::SameLine(0, 5);
			ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.f), "1.0.0-Alpha");
			ImGui::PopFont();
			ImGui::SetCursorPos(ImVec2(20, childHeight / 2 - 10));
			ImGui::PushStyleColor(ImGuiCol_Button, hyperx_red);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hyperx_red_hover);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, hyperx_red_active);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.f));
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
			if (ImGui::Button("Inject", ImVec2(colWidth2 - 40, 45))) { g_MenuInfo.is_injecting = true; }
			ImGui::SetCursorPos(ImVec2(20, childHeight / 2 + 45));
			ImGui::PushStyleColor(ImGuiCol_Button, hyperx_red);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hyperx_red_hover);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, hyperx_red_active);
			if (ImGui::Button("Bypass", ImVec2(colWidth2 - 40, 45))) { g_MenuInfo.is_injecting = true; }
			ImGui::PopStyleColor(3);
			ImGui::PopStyleVar();
			ImGui::PopStyleColor(4);
			ImGui::EndChild();
			ImGui::PopStyleVar();
			ImGui::PopStyleColor(2);
		}
	}
}
