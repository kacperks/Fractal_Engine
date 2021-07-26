#pragma once

#include "Editor/UiLayer.h"
#include "MenuBar.h"

namespace Panels {
	void Components(){
		static const char* names[] = { "Camera", "RigidBody", "MeshRenderer",
			"ModelRenderer", "SpriteRenderer", "Directional Light", "Point Light", "Spot Light" };

		std::map<std::string, ImTextureID> icons = UI.GetIcons();

		ImGui::Begin("Inspector", nullptr);
		{
			// toolbar		
			ImGui::PushStyleColor(ImGuiCol_FrameBg, dark);
			ImGui::BeginChildFrame(ImGui::GetID("toolbar"), ImVec2(0, 32));
			{
				if (ImGui::Button("Add Component")) {
					ImGui::OpenPopup("compPopup");
				}
				ImGui::SameLine();
				if (Widget::ToolButton::Show(icons.at("trash"), 20.0f)) { ImGui::OpenPopup("compPopup9"); }
				ImGui::SameLine();
				if (ImGui::BeginPopup("compPopup")) {
					ImGui::Text("Components");
					ImGui::Separator();

					for (size_t i = 0; i < IM_ARRAYSIZE(names); i++) {
						if (ImGui::Selectable(names[i])) {
							UI.AddComponent(names[i]);
							UI.AddToConsole(" [ECS] Added Component");
						}
					}
					ImGui::EndPopup();
				}
				ImGui::SameLine();
				if (ImGui::BeginPopup("compPopup9")) {
					ImGui::Text("Components");
					ImGui::Separator();

					for (size_t i = 0; i < IM_ARRAYSIZE(names); i++) {
						if (ImGui::Selectable(names[i])) {
							UI.RemoveComponent(names[i]);
							UI.AddToConsole(" [ECS] Removed Component");
						}
					}
					ImGui::EndPopup();
				}
			}
			ImGui::PopStyleColor();
			ImGui::EndChildFrame();
			// components			
			if (UI.GetSelectedEntity() > ECS::INVALID_ENTITY) {
				for (auto compUi : UI.GetActiveCompUIs()) {
					compUi->Show();
				}

			}

		}
		ImGui::End();
	}
}