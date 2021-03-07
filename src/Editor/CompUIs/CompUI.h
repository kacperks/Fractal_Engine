#pragma once

#include "Resource/Resource.h"
#include "ECS/Base/EntityManager.h"
#include "Editor/Controls/Widgets.h"

static const float DRAG_WIDTH = 60;
static const ImVec2 BUT_SIZE = ImVec2(20, 18);
static const ImVec4 RED = ImVec4(0.79f, 0.17f, 0.0, 1.0f);
static const ImVec4 BLUE = ImVec4(0.27f, 0.55f, 0.94, 1.0f);
static const ImVec4 GREEN = ImVec4(0.4f, 0.6f, 0.0, 1.0f);
static const ImVec4 DARK = ImVec4(0.19f, 0.19f, 0.19, 1.0f);

static const ImVec2 FRAME_PADDING = ImVec2(8,8);
static const ImGuiColorEditFlags COLOR_PICKER_FALGS =  ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_Float;

class CompUI {
public:
	CompUI() = default;
	virtual ~CompUI() = default;
	inline bool IsVisible() const { return isVisible; }

	virtual void Show() {}
	virtual void Init(ECS::EntityID entity) {}

protected:
	bool isVisible = false;
};



