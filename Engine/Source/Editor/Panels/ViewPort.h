#pragma once

#include "Editor/UiLayer.h"

namespace Panels {
	void ViewPort() {
		ImGui::Begin("Scene", nullptr);
		{
			ImTextureID sceneFrameTexture = UI.GetSceneFrameTexture();
			fr::ViewPortRect viewRect = UI.ViewportRect();
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(dark));
			ImGui::PopStyleColor();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			ImGui::BeginChildFrame(ImGui::GetID("sceneFrame"), ImVec2(0, 0), ImGuiWindowFlags_NoScrollbar);
			{
				const ImVec2& size = ImGui::GetWindowSize();
				ImGui::Image(sceneFrameTexture, size, ImVec2(0, 1), ImVec2(1, 0));
				const ImVec2& pos = ImGui::GetWindowPos();
				viewRect = { pos.x, pos.y, size.x, size.y };
				UI.Tg();
			}
			ImGui::PopStyleVar();
			ImGui::EndChildFrame();
		}
		ImGui::End();
	}
}