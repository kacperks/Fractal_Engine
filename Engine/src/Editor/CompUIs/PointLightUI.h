#pragma once

#ifndef FR_POINT_LIGHT_COMPONENT_UI
#define FR_POINT_LIGHT_COMPONENT_UI

#include "CompUI.h"
#include "ECS/Components/PointLight.h"

class PointLightUI : public CompUI {
public:
	void Init(ECS::EntityID entity) override {
		isVisible = false;
		if (ECS::Manager.HasComponent<PointLight>(entity)) {
			light = &ECS::Manager.GetComponent<PointLight>(entity);
			isVisible = true;
		}
	}

	void Show() override {
		if (ImGui::CollapsingHeader("Point Light")) {
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[1]);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, FRAME_PADDING);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, DARK);

			ImGui::BeginChildFrame(ImGui::GetID("pointframe"), ImVec2(0, 55));
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			{
				ImGui::PushStyleColor(ImGuiCol_Button, GREEN);
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));

				if (ImGui::Button("Color", ImVec2(50, 18))) { light->Color = glm::vec3(1.0); }
				ImGui::SameLine();
				ImGui::SetNextItemWidth(-1);
				ImGui::ColorEdit3("##Color", glm::value_ptr(light->Color), ImGuiColorEditFlags_Float);

				if (ImGui::Button("Intensity", ImVec2(50, 18))) { light->Intensity = 1.0; }
				ImGui::SameLine();
				ImGui::SetNextItemWidth(-1);
				ImGui::DragFloat("##intensity", &light->Intensity, 1.0f, 0, 0, "%.1f");

				ImGui::PopStyleVar();
				ImGui::PopStyleColor();
			}
			ImGui::EndChildFrame();
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[0]);
		}
	}

private:
	PointLight* light;
};

#endif