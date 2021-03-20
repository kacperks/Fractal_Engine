#pragma once

#include "UserControl.h"
#include "../../fractal.hpp"

class TransformUserControl : public UserControl {
public:
	void Display(ECS::EntityHandle entity) override {		
		if (!FuseOrbit3D::Manager.HasComponent<Transform3D>(entity)) { return; }
		auto& transform = fr::Manager.GetComponent<Transform3D>(entity);

		Widget::ComponentUI::Begin("Transform3D", 128.0f, compIcon);				
		Widget::DragVec3::Display("Position", transform.Position, posIcon, 0.1f);
		Widget::DragVec3::Display("Rotation", transform.Rotation, posIcon, 1.0f, -360.0f, 360.0f);
		Widget::DragVec3::Display("Scale     ", transform.Scale, posIcon, 0.1f);		
		Widget::ComponentUI::End();
	}

private:
	ImTextureID delIcon = UI_ASSETS.Icon("trash");
	ImTextureID posIcon = UI_ASSETS.Icon("position");
	ImTextureID compIcon = UI_ASSETS.Icon("transform");
};