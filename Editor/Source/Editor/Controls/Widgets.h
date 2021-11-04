#pragma once

#include "VendorE/IMGUI/imgui.h"

namespace Widget {

	struct DragFloat {
		static void Show(const char* label, float* data, float width, float step = 1.0f, float min = 0.0f, float max = 0.0f) {
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f)); 
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.0f, 4.0f));
			ImGui::SetNextItemWidth(width);
			ImGui::DragFloat(label, data, step, min, max, "%.2f");
			ImGui::PopStyleColor();
			ImGui::PopStyleVar();
		}
	};

	struct DragVec3 {
		static void Show(std::string label, glm::vec3& v, ImTextureID icon = 0, float step = 1.0f, float min = 0.0f, float max = 0.0f) {
			ImGui::Image(icon, ImVec2(15.0f, 15.0f), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::SameLine();
			ImGui::Text(label.c_str());
			ImGui::SameLine();
			std::string vx = "##X" + label;
			DragFloat::Show(vx.c_str(), &v.x, 50.0f, step, min, max); ImGui::SameLine(); ImGui::Text("X");
			ImGui::SameLine();
			std::string vy = "##Y" + label;
			DragFloat::Show(vy.c_str(), &v.y, 50.0f, step, min, max); ImGui::SameLine(); ImGui::Text("Y");
			ImGui::SameLine();
			std::string vz = "##Z" + label;
			DragFloat::Show(vz.c_str(), &v.z, 50.0f, step, min, max); ImGui::SameLine(); ImGui::Text("Z");
		}
	};

	struct Window {
		static void Begin(const char* title, float wp = 5.0f, float fp = 8.0f, ImGuiWindowFlags flags = ImGuiWindowFlags_None) {
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(fp, fp));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(wp, wp));
			ImGui::Begin(title, nullptr, flags);			
			ImGui::PopStyleVar(2);
		}

		static void End() {
			ImGui::End();
		}
	};

	struct Child {
		static void Begin(const char* title, float width = 0.0f, float wp = 5.0f, float fp = 10.0f, ImGuiWindowFlags flags = ImGuiWindowFlags_None) {
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(fp, fp));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(wp, wp));
			ImGui::BeginChild(title, ImVec2(0.0f, 0.0f), flags);
			ImGui::PopStyleVar(2);
		}

		static void End() {
			ImGui::EndChild();
		}
	};

	struct Frame {
		static void Begin(const char* name, float height = 0.0f, float pd = 10.0f) {
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(pd, pd));
			ImGui::BeginChildFrame(ImGui::GetID(name), ImVec2(0.0f, height));
			ImGui::PopStyleColor();
			ImGui::PopStyleVar();
		}

		static void End() {
			ImGui::EndChildFrame();
		}
	};

	struct ComponentUI {
		static void Begin(const char* title, float height, ImTextureID icon = 0) {		
			Frame::Begin(title, height);
			ImGui::Image(icon, ImVec2(15.0f, 15.0f), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::SameLine();
			ImGui::Text(title);
			ImGui::Spacing();
			ImGui::Spacing();
		}

		static void End() {
			Frame::End();
		}
	};

	struct Selectable {
		static int Show(const char* label, int target, int current, ImTextureID icon) {
			ImGui::Image(icon, ImVec2(15.0f, 15.0f), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::SameLine();
			if (ImGui::Selectable(label, current == target)) { current = target; }
			return current;
		}
	};

	struct ToolButton {
		static bool Show(ImTextureID icon, float size = 24.0f) {
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
			bool isClicked = ImGui::ImageButton(icon, ImVec2(size, size), ImVec2(0, 1), ImVec2(1, 0), 0.0f);
			ImGui::PopStyleVar();
			return isClicked;
		}
	};
}