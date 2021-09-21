#pragma once

#include "Editor/UiLayer.h"

namespace Panels {
	void MenuBar() {
		std::map<std::string, ImTextureID> icons = UI.GetIcons();
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Save", "Ctrl+S")) { fr::Serializer.SaveScene(Core.GetCurrentScene()); }

				if (ImGui::MenuItem("Save As..")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings")) {
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Window")) {
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Tools")) {
				if (ImGui::MenuItem("Rotate")) { UI.SetGizmoOperation(ImGuizmo::OPERATION::ROTATE); }
				if (ImGui::MenuItem("Move")) { UI.SetGizmoOperation(ImGuizmo::OPERATION::TRANSLATE); }
				if (ImGui::MenuItem("Scale")) { UI.SetGizmoOperation(ImGuizmo::OPERATION::SCALE); }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help")) {
				if (ImGui::MenuItem("View Help", "Ctrl+H")) {}
				if (ImGui::MenuItem("About Fractal Engine")) {}
				ImGui::EndMenu();
			}
			ImGui::Dummy(ImVec2(700, 0));
			ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			if (Widget::ToolButton::Show(icons.at("save"))) { fr::Serializer.SaveScene(Core.GetCurrentScene()); UI.AddToConsole(" [Scene] Saved Scene!"); }
			if (Widget::ToolButton::Show(icons.at("move"))) { UI.SetGizmoOperation(ImGuizmo::OPERATION::TRANSLATE); UI.AddToConsole(" [DEBUG] Tool Move "); }
			if (Widget::ToolButton::Show(icons.at("rotate"))) { UI.SetGizmoOperation(ImGuizmo::OPERATION::ROTATE);  UI.AddToConsole(" [DEBUG] Tool Rotate "); }
			if (Widget::ToolButton::Show(icons.at("scale"))) { UI.SetGizmoOperation(ImGuizmo::OPERATION::SCALE);	UI.AddToConsole(" [DEBUG] Tool Scale "); }

			ImGui::Text("Fractal Editor " EDITOR_VERSION);

			ImGui::EndMenuBar();
		}
	}
}