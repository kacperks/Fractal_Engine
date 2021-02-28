#pragma once

#include "UserControl.h"
#include "../../fractal.hpp"

class MaterialUserControl : public UserControl {
public:
	void Display(ECS::EntityHandle entity) override {
		if (!FuseOrbit3D::Manager.HasComponent<Material>(entity)) { return; }

		auto& material = FuseOrbit3D::Manager.GetComponent<Material>(entity);
		SetBackupData(material);

		//if (!ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen)) { return; }
		Widget::ComponentUI::Begin("Material", 300.0f, compIcon);

		if (has_texture) {
			ImGui::Combo("Diff.Texture", &material.DiffuseTextureID, items, 4);
			ImGui::Combo("Spec.Texture", &material.SpecularTextureID, items, 4);
		}
		else {
			ImGui::SetNextItemWidth(180.0f);
			ImGui::ColorPicker3("M.Ambient", ambientColor, COLOR_PICKER_FALGS | ImGuiColorEditFlags_NoInputs);
			material.Ambient.r = ambientColor[0];
			material.Ambient.g = ambientColor[1];
			material.Ambient.b = ambientColor[2];
			ImGui::Spacing();

			ImGui::ColorEdit3("M.Diffuse", diffuseColor, COLOR_PICKER_FALGS);
			material.Diffuse.r = diffuseColor[0];
			material.Diffuse.g = diffuseColor[1];
			material.Diffuse.b = diffuseColor[2];

			ImGui::ColorEdit3("M.Specular", specularColor, COLOR_PICKER_FALGS);
			material.Specular.r = specularColor[0];
			material.Specular.g = specularColor[1];
			material.Specular.b = specularColor[2];

			Widget::DragFloat::Display("Shininess", &material.Shininess, -1, 0.1f);
			ImGui::DragFloat("Shininess", &material.Shininess, 0.1f, 0.0f);
			ImGui::Combo("Diff.Texture", &material.DiffuseTextureID, items, 4);
			ImGui::Combo("Spec.Texture", &material.SpecularTextureID, items, 4);
		}	

		Widget::ComponentUI::End();
	}

	void SetBackupData(const Material& material) {
		// ambient backup
		ambientColor[0] = material.Ambient.r;
		ambientColor[1] = material.Ambient.g;
		ambientColor[2] = material.Ambient.b;
		// diffuse backup
		diffuseColor[0] = material.Diffuse.r;
		diffuseColor[1] = material.Diffuse.g;
		diffuseColor[2] = material.Diffuse.b;
		// specular backup
		specularColor[0] = material.Specular.r;
		specularColor[1] = material.Specular.g;
		specularColor[2] = material.Specular.b;	

		has_texture = (material.DiffuseTextureID || material.SpecularTextureID) ? true : false;
	}

private:
	ImTextureID compIcon = UI_ASSETS.Icon("material");
	bool has_texture;
	const char* items[4] = { "Select", "BBBB", "CCCC", "DDDD" };
	float ambientColor[3] = { 0.0f, 0.0f, 0.0f };
	float diffuseColor[3] = { 0.0f, 0.0f, 0.0f };
	float specularColor[3] = { 0.0f, 0.0f, 0.0f };
};