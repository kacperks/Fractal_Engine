#pragma once

#include "Editor/UiLayer.h"

namespace Panels {
	/*
	inline std::pair<bool, uint32_t> DirectoryTreeViewRecursive(const std::filesystem::path& path, uint32_t* count, int* selection_mask) {
		std::map<std::string, ImTextureID> icons = UI.GetIcons();

		ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_SpanFullWidth;

		bool any_node_clicked = false;
		uint32_t node_clicked = 0;

		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			ImGuiTreeNodeFlags node_flags = base_flags;
			const bool is_selected = (*selection_mask & *count) != 0;
			if (is_selected)
				node_flags |= ImGuiTreeNodeFlags_Selected;

			std::string name = entry.path().string();

			auto lastSlash = name.find_last_of("/\\");
			lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
			name = name.substr(lastSlash, name.size() - lastSlash);

			bool node_open = false;
			bool entryIsFile = !std::filesystem::is_directory(entry.path());
			if (entryIsFile == false) {

				ImGui::Image(icons.at("folder"), ImVec2(15.0f, 15.0f), ImVec2(0, 1), ImVec2(1, 0));
				ImGui::SameLine();
				node_open = ImGui::TreeNodeEx((void*)(intptr_t)(*count), node_flags, name.c_str());
			}
			else {
				if (name.find(".fr") < name.length()) {
					ImGui::Image(icons.at("Logo"), ImVec2(15.0f, 15.0f), ImVec2(0, 1), ImVec2(1, 0));
				}
				else if (name.find(".lua") < name.length()) {
					ImGui::Image(icons.at("lua"), ImVec2(15.0f, 15.0f), ImVec2(0, 1), ImVec2(1, 0));
				}
				else if (name.find(".cs") < name.length()) {
					ImGui::Image(icons.at("cs"), ImVec2(15.0f, 15.0f), ImVec2(0, 1), ImVec2(1, 0));
				}
				else if (name.find(".shader") < name.length()) {
					ImGui::Image(icons.at("light"), ImVec2(15.0f, 15.0f), ImVec2(0, 1), ImVec2(1, 0));
				}
				else if (name.find(".obj") < name.length()) {
					ImGui::Image(icons.at("mag"), ImVec2(15.0f, 15.0f), ImVec2(0, 1), ImVec2(1, 0));
				}
				else if (name.find(".png") < name.length()) {
					ImGui::Image(icons.at("png"), ImVec2(15.0f, 15.0f), ImVec2(0, 1), ImVec2(1, 0));
				}
				else {
					ImGui::Image(icons.at("obj"), ImVec2(15.0f, 15.0f), ImVec2(0, 1), ImVec2(1, 0));
				}

				ImGui::SameLine();
				ImGui::Text(name.c_str());
			}

			if (ImGui::IsItemClicked()) {
				node_clicked = *count;
				any_node_clicked = true;
			}

			(*count)--;

			if (!entryIsFile) {
				if (node_open) {
					auto clickState = DirectoryTreeViewRecursive(entry.path(), count, selection_mask);
					if (!any_node_clicked) {
						any_node_clicked = clickState.first;
						node_clicked = clickState.second;
					}

					ImGui::TreePop();
				}
				else {
					for (const auto& e : std::filesystem::recursive_directory_iterator(entry.path()))
						(*count)--;
				}
			}
		}

		return { any_node_clicked, node_clicked };
	}
*/
	inline void OnImGui(std::string directoryPath) {
		uint32_t count = 0;
		static int selection_mask = 0;
		//for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) { count++; }
		//auto clickState = DirectoryTreeViewRecursive(directoryPath, &count, &selection_mask);
	}

	inline void Resources() {
		ImGui::Begin("File System", nullptr);
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, dark);
			ImGui::BeginChildFrame(ImGui::GetID("rframe"), ImVec2(0, 0));
			{
				OnImGui("Resource");
			}
			ImGui::PopStyleColor();
			ImGui::EndChildFrame();
		}
		ImGui::End();
	}
}