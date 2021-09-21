#pragma once

#include "Editor/UiLayer.h"

namespace Panels {
	std::string console = "Fractal Engine Debug Console";
	void Console() {
		ImGui::Begin("Output", nullptr);
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, dark);
			ImGui::BeginChildFrame(ImGui::GetID("cframe"), ImVec2(0, 0));
			{
				ImGui::Text(console.c_str());
			}
			ImGui::PopStyleColor();
			ImGui::EndChildFrame();
		}
		ImGui::End();
	}
}