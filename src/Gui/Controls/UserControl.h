#pragma once

#include "Widgets.h"
#include "../../Resource/Resource.h"
#include "../../fractal.hpp"

static const ImGuiColorEditFlags COLOR_PICKER_FALGS =  ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_Float;

class UserControl {
public:
	virtual ~UserControl() { }
	virtual void Display(ECS::EntityHandle entity) { }
};

class UiAssets {

public:
	static UiAssets& Get() {
		static UiAssets ref;
		return ref;
	}

	UiAssets() {
		icons.insert({"trash", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/trash.png") });
		icons.insert({"light", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/light.png") });
		icons.insert({"camera", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/camera.png") });
		icons.insert({"entity", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/entity.png") });
		icons.insert({"material", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/material.png") });
		icons.insert({"position", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/position.png") });
		icons.insert({"transform", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/transform.png") });

		icons.insert({"up", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/up.png") });
		icons.insert({"down", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/down.png") });

		icons.insert({"add", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/add.png") });
		icons.insert({"minus", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/minus.png") });
		icons.insert({"play", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/play.png") });
		icons.insert({"move", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/move.png") });
		icons.insert({"view", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/view.png") });
		icons.insert({"rotate", (ImTextureID)RESOURCE.LoadTex2D("Resource/Gui/rotate.png") });
	}

	ImTextureID Icon(std::string name) {
		assert(icons.find(name) != icons.end() && "Icon name out of range");
		return icons.at(name);
	}

private:
	std::map<std::string, ImTextureID> icons;
};

static UiAssets UI_ASSETS = UiAssets::Get();


