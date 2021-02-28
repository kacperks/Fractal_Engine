#pragma once

#include "UserControl.h"
#include "../../fractal.hpp"

class LightUserControl : public UserControl {
public:
	void Display(ECS::EntityHandle entity) override {
		if (!FuseOrbit3D::Manager.HasComponent<Light>(entity)) { return; }

		auto& light = FuseOrbit3D::Manager.GetComponent<Light>(entity);
		SetBackupData(light);

		if (!ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
			return;
		{
			ImGui::SliderInt("Type", &light.Type, 0, 2);
			ImGui::SetNextItemWidth(180.0f);
			ImGui::ColorPicker3("L.Ambient", ambientColor, COLOR_PICKER_FALGS | ImGuiColorEditFlags_NoInputs);
			light.Ambient.r = ambientColor[0];
			light.Ambient.g = ambientColor[1];
			light.Ambient.b = ambientColor[2];
			ImGui::Spacing();

			ImGui::ColorEdit3("L.Diffuse", diffuseColor, COLOR_PICKER_FALGS);
			light.Diffuse.r = diffuseColor[0];
			light.Diffuse.g = diffuseColor[1];
			light.Diffuse.b = diffuseColor[2];

			ImGui::ColorEdit3("L.Specular", specularColor, COLOR_PICKER_FALGS);
			light.Specular.r = specularColor[0];
			light.Specular.g = specularColor[1];
			light.Specular.b = specularColor[2];

			if (light.Type == 1 || light.Type == 2) {
				ImGui::DragFloat3("Direction", lightDirection, 1.0f);
				light.Direction.x = lightDirection[0];
				light.Direction.y = lightDirection[1];
				light.Direction.z = lightDirection[2];
			}
			if (light.Type == 2) {
				//DragFloat().Display("I.CuttOff", &light.InnerCutOff, 1.0f, 0.0f, 360.0f);
				ImGui::DragFloat("I.CuttOff", &light.InnerCutOff, 1.0f, 0.0f, 360.0f);
				ImGui::DragFloat("O.CuttOff", &light.OuterCutOff, 1.0f, 0.0f, 360.0f);
			}

			ImGui::DragFloat("Linear", &light.Linear, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Constant", &light.Constant, 0.01f, 0.1f, 1.0f);
			ImGui::DragFloat("Quadratic", &light.Quadratic, 0.01f, 0.0f, 1.0f);
		}
	}

	void SetBackupData(const Light& light) {
		// ambient backup
		ambientColor[0] = light.Ambient.r;
		ambientColor[1] = light.Ambient.g;
		ambientColor[2] = light.Ambient.b;
		// diffuse backup
		diffuseColor[0] = light.Diffuse.r;
		diffuseColor[1] = light.Diffuse.g;
		diffuseColor[2] = light.Diffuse.b;
		// specular backup
		specularColor[0] = light.Specular.r;
		specularColor[1] = light.Specular.g;
		specularColor[2] = light.Specular.b;
		// light direction backup
		lightDirection[0] = light.Direction.x;
		lightDirection[1] = light.Direction.y;
		lightDirection[2] = light.Direction.z;
	}

private:
	float ambientColor[3] = { 0.0f, 0.0f, 0.0f };
	float diffuseColor[3] = { 0.0f, 0.0f, 0.0f };
	float specularColor[3] = { 0.0f, 0.0f, 0.0f };
	float lightDirection[3] = { 0.0f, 0.0f, 0.0f };	
};

