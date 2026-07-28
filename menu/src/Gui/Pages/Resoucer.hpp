#pragma once
#include <Includes/Includes.hpp>
#include <Core/Features/Exploits/ResourceList.hpp>

namespace Resoucer {

	void Render() {
		static int selected_resource = -1;

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 25.f);

		ImVec2 avail = ImGui::GetContentRegionAvail();
		
		float full_width = avail.x;
		float bottom_bar_height = 40.f;
		float list_height = avail.y - bottom_bar_height - 10.f; 

		ImGui::BeginGroup();
		{
			std::lock_guard<std::mutex> lock(Core::Features::Exploits::vResourcesMtx);

			ImVec2 list_start_pos = ImGui::GetCursorPos();

			// --- RESOURCE LIST ---
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 4.0f);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // Fundo transparente
			static char searchBuffer[128] = "";
			ImGui::BeginChild(xorstr("List"), ImVec2(full_width, list_height), false, ImGuiWindowFlags_NoScrollbar);
			{
				for (size_t i = 0; i < Core::Features::Exploits::vResources.size(); i++) {
					auto& res = Core::Features::Exploits::vResources[i];
					
					std::string cleanName = res.Path;
					size_t pos = cleanName.find(xorstr("resources:/"));
					if (pos != std::string::npos) {
						cleanName.erase(pos, 11);
					}
					if (cleanName.length() > 0 && cleanName[0] == '/') cleanName.erase(0, 1);

					if (searchBuffer[0] != '\0') {
						std::string resNameLower = cleanName;
						std::string searchLower = searchBuffer;
						std::transform(resNameLower.begin(), resNameLower.end(), resNameLower.begin(), ::tolower);
						std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
						
						if (resNameLower.find(searchLower) == std::string::npos) {
							continue;
						}
					}

					bool is_selected = (selected_resource == (int)i);

					ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
					ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
					ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.25f, 0.25f, 0.25f, 1.0f));

					std::string label = cleanName + " [" + res.GetState() + "]##" + std::to_string(i);
					
					if (ImGui::Selectable(label.c_str(), is_selected, ImGuiSelectableFlags_None, ImVec2(0, 25))) {
						selected_resource = (int)i;
					}

					ImGui::PopStyleColor(3);

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndChild();
			ImGui::PopStyleColor();
			ImGui::PopStyleVar();

			ImVec2 list_end_pos = ImGui::GetCursorPos();

			// --- SEARCH BAR DENTRO DO CABEÇALHO ---
			// Renderiza o input por cima do child.
			ImGui::SetCursorPos(ImVec2(list_start_pos.x + full_width - 255.f, list_start_pos.y + 4.f)); 
			
			ImGui::PushItemWidth(250.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));
			ImGui::InputTextWithHint(xorstr("##SearchResource"), xorstr("Procurar Resource..."), searchBuffer, IM_ARRAYSIZE(searchBuffer));
			ImGui::PopStyleColor(3);
			ImGui::PopStyleVar();
			ImGui::PopItemWidth();

			ImGui::SetCursorPos(list_end_pos);

			// --- BOTOES NO FUNDO ---
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);

			ImGui::BeginGroup();
			{
				if (Custom::Button(xorstr("Dump Resources"), ImVec2(150.f, 35.f), 0)) {
					Core::Features::Exploits::g_ResourceList.DumpResourcesToFile();
				}

				ImGui::SameLine();
				ImGui::SetCursorPosX(full_width - 148.f); 

				bool has_selected = (selected_resource != -1 && selected_resource < (int)Core::Features::Exploits::vResources.size());
				
				if (Custom::Button(xorstr("Stop"), ImVec2(70.f, 35.f), 0)) {
					if (has_selected) {
						auto& res = Core::Features::Exploits::vResources[selected_resource];
						std::thread([res]() {
							Core::Features::Exploits::g_ResourceList.Stop(res.Pointer);
						}).detach();
					}
				}

				ImGui::SameLine();
				
				if (Custom::Button(xorstr("Destroy"), ImVec2(70.f, 35.f), 0)) {
					if (has_selected) {
						auto& res = Core::Features::Exploits::vResources[selected_resource];
						std::thread([res]() {
							Core::Features::Exploits::g_ResourceList.Destroy(res.Pointer);
						}).detach();
					}
				}
			}
			ImGui::EndGroup();

		}
		ImGui::EndGroup();
	}
}