#pragma once

#include <string.h>
#include "UserControl.h"
#include "../../fractal.hpp"

class NameUserControl : public UserControl {
public:
	void Display(ECS::EntityHandle entity) override {
		if (!FuseOrbit3D::Manager.HasComponent<Name>(entity)) { return; }
		auto& name = FuseOrbit3D::Manager.GetComponent<Name>(entity);
		strcpy_s(buffer, name.Value.c_str());

		Widget::ComponentUI::Begin("Name", 100.0f, icon);
		{
			ImGui::InputText("##EntityName", buffer, IM_ARRAYSIZE(buffer));
		}

		name.Value = std::string(buffer);
		Widget::ComponentUI::End();
	}


private:
	char buffer[20];
	ImTextureID icon = UI_ASSETS.Icon("add");
};

class TagUserControl : public UserControl {
public:
	void Display(ECS::EntityHandle entity) override {
		if (!FuseOrbit3D::Manager.HasComponent<Tag>(entity)) { return; }
		auto& tag = FuseOrbit3D::Manager.GetComponent<Tag>(entity);
		strcpy_s(buffer, tag.Value.c_str());

		Widget::ComponentUI::Begin("Tag", 100.0f, icon);
		{
			ImGui::InputText("##EntityTag", buffer, IM_ARRAYSIZE(buffer));
		}

		tag.Value = std::string(buffer);
		Widget::ComponentUI::End();
	}

private:
	char buffer[20];
	ImTextureID icon = UI_ASSETS.Icon("minus");
};