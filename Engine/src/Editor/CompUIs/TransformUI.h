#pragma once

#include "CompUI.h"
#include "ECS/Components/Transform.h"
#include "Editor/Controls/Widgets.h"

class TransformUI : public CompUI {

public:
	void Init(ECS::EntityID entity) override {
		isVisible = false;
		if (ECS::Manager.HasComponent<Transform>(entity)) {
			transform = &ECS::Manager.GetComponent<Transform>(entity);
			isVisible = true;
		}
	}

	void Show() override {	

		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {	
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[1]);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, FRAME_PADDING);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, DARK);

			ImGui::BeginChildFrame(ImGui::GetID("tframe"), ImVec2(0, 75));
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));
				ImGui::Text("Position"); ImGui::SameLine();
				ImGui::PushStyleColor(ImGuiCol_Button, GREEN);
				if (ImGui::Button("X", BUT_SIZE)) { transform->Position.x = 0; } 
				ImGui::SameLine();
				ImGui::SetNextItemWidth(DRAG_WIDTH);
				ImGui::DragFloat("##posx", &transform->Position.x, 0.1f, 0, 0, "%.1f");
				ImGui::SameLine();

				ImGui::PushStyleColor(ImGuiCol_Button, RED);
				if (ImGui::Button("Y", BUT_SIZE)) { transform->Position.y = 0; } 
				ImGui::SameLine();
				ImGui::SetNextItemWidth(DRAG_WIDTH);
				ImGui::DragFloat("##posy", &transform->Position.y, 0.1f, 0, 0, "%.1f");
				ImGui::SameLine();

				ImGui::PushStyleColor(ImGuiCol_Button, BLUE);
				if (ImGui::Button("Z", BUT_SIZE)) { transform->Position.z = 0; } 
				ImGui::SameLine();
				ImGui::SetNextItemWidth(DRAG_WIDTH);
				ImGui::DragFloat("##posz", &transform->Position.z, 0.1f, 0, 0, "%.1f");
				ImGui::PopStyleColor(3);

				// Rotation
				ImGui::Text("Rotation"); ImGui::SameLine();
				ImGui::PushStyleColor(ImGuiCol_Button, GREEN);
				if (ImGui::Button("X", BUT_SIZE)) { transform->Rotation.x = 0; } 
				ImGui::SameLine();
				ImGui::SetNextItemWidth(DRAG_WIDTH);
				ImGui::DragFloat("##rotx", &transform->Rotation.x, 1.0f, -360, 360, "%.1f");
				ImGui::SameLine();

				ImGui::PushStyleColor(ImGuiCol_Button, RED);
				if (ImGui::Button("Y", BUT_SIZE)) { transform->Rotation.y = 0; } 
				ImGui::SameLine();
				ImGui::SetNextItemWidth(DRAG_WIDTH);
				ImGui::DragFloat("##roty", &transform->Rotation.y, 1.0f, -360, 360, "%.1f");
				ImGui::SameLine();

				ImGui::PushStyleColor(ImGuiCol_Button, BLUE);
				if (ImGui::Button("Z", BUT_SIZE)) { transform->Rotation.z = 0; } 
				ImGui::SameLine();
				ImGui::SetNextItemWidth(DRAG_WIDTH);
				ImGui::DragFloat("##rotz", &transform->Rotation.z, 1.0f, -360, 360, "%.1f");
				ImGui::PopStyleColor(3);

				// Scale

				ImGui::Text("Scale     "); ImGui::SameLine();
				ImGui::PushStyleColor(ImGuiCol_Button, GREEN);
				if (ImGui::Button("X", BUT_SIZE)) { transform->Scale.x = 1; } 
				ImGui::SameLine();
				ImGui::SetNextItemWidth(DRAG_WIDTH);
				ImGui::DragFloat("##scax", &transform->Scale.x, 0.01f, 0.00001f, 0, "%.1f");
				ImGui::SameLine();

				ImGui::PushStyleColor(ImGuiCol_Button, RED);
				if (ImGui::Button("Y", BUT_SIZE)) { transform->Scale.y = 1; } 
				ImGui::SameLine();
				ImGui::SetNextItemWidth(DRAG_WIDTH);
				ImGui::DragFloat("##scay", &transform->Scale.y, 0.01f, 0.00001f, 0, "%.1f");
				ImGui::SameLine();

				ImGui::PushStyleColor(ImGuiCol_Button, BLUE);
				if (ImGui::Button("Z", BUT_SIZE)) { transform->Scale.z = 1; } 
				ImGui::SameLine();
				ImGui::SetNextItemWidth(DRAG_WIDTH);
				ImGui::DragFloat("##scaz", &transform->Scale.z, 0.01f, 0.00001f, 0, "%.1f");

				ImGui::PopStyleColor(3);

				ImGui::PopStyleVar();
			}
			ImGui::EndChildFrame();
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[0]);
		}
	}

private:
	Transform* transform;
};