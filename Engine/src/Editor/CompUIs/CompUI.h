#pragma once

#include "Resource/Resource.h"
#include "ECS/Base/EntityManager.h"
#include "Editor/Controls/Widgets.h"

static const float DRAG_WIDTH = 60;
static const ImVec2 BUT_SIZE = ImVec2(20, 18);
static const ImVec4 RED = ImVec4(0.70f, 0.10f, 0.0, 1.0f);
static const ImVec4 BLUE = ImVec4(0.21f, 0.45f, 0.90, 1.0f);
static const ImVec4 GREEN = ImVec4(0.3f, 0.5f, 0.0, 1.0f);
static const ImVec4 DARK = ImVec4(0.19f, 0.19f, 0.19, 1.0f);
static const ImVec4 DARK_GREEN = ImVec4(0.176f, 0.483f, 0.112f, 0);

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



