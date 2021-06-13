#pragma once

#include "CompUI.h"
#include "Core/ECS/Components/DirectionalLight.h"
#include "Core/ECS/Components/CsScript.h"

class DirectLightUI : public CompUI {
public:
	void Init(ECS::EntityID entity) override {
		isVisible = false;
		if (ECS::Manager.HasComponent<DirectionalLight>(entity)) {
			light = &ECS::Manager.GetComponent<DirectionalLight>(entity);
			isVisible = true;
		}
	}

	void Show() override {
		if (ImGui::CollapsingHeader("Directional Light")) {
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[1]);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, FRAME_PADDING);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, DARK);

			ImGui::BeginChildFrame(ImGui::GetID("directframe"), ImVec2(0, 79));
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));

				ImGui::PushStyleColor(ImGuiCol_Button, GREEN);
				if (ImGui::Button("Color", ImVec2(50, 18))) { light->Color = glm::vec3(1.0); }
				ImGui::SameLine();
				ImGui::SetNextItemWidth(-1);
				ImGui::ColorEdit3("##Color", glm::value_ptr(light->Color), ImGuiColorEditFlags_Float);

				// Direction

				if (ImGui::Button("Direction", ImVec2(50, 18))) { light->Direction = glm::vec3(0, 0, 1); }
				ImGui::SameLine();
				ImGui::SetNextItemWidth(-1);
				ImGui::DragFloat3("##dirx", glm::value_ptr(light->Direction), 0.1f, 0, 0, "%.1f");

				// Intensity

				if (ImGui::Button("Intensity", ImVec2(50, 18))) { light->Intensity = 1.0; }
				ImGui::SameLine();
				ImGui::SetNextItemWidth(-1);
				ImGui::DragFloat("##intensity", &light->Intensity, 1.0f, 0, 0, "%.1f");

				
				//ImGui::SameLine();

				ImGui::PopStyleColor();
				ImGui::PopStyleVar();
			}
			ImGui::EndChildFrame();
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[0]);
		}
	}

private:
	char buffer[20];
	DirectionalLight* light;
};
