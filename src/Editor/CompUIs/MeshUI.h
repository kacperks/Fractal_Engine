#pragma once

#include "CompUI.h"
#include "Resource/Resource.h"
#include "ECS/Components/MeshRenderer.h"

class MeshUI : public CompUI {

public:
	MeshUI(): mesh(nullptr), material(nullptr), currItemIndex(0) { }

	void Init(ECS::EntityID entity) override {
		isVisible = false;
		if (ECS::Manager.HasComponent<MeshRenderer>(entity)) {
			mesh = &ECS::Manager.GetComponent<MeshRenderer>(entity);
			material = &mesh->Mesh.GetMaterial();
			isVisible = true;
		}
	}

	void Show() override {

		// MeshRenderer

		if (ImGui::CollapsingHeader("MeshRenderer")) {
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[1]);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, FRAME_PADDING);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, DARK);

			ImGui::BeginChildFrame(ImGui::GetID("meshframe"), ImVec2(0, 35));
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));

				if (ImGui::BeginCombo("Filter", mesh->Name.c_str())) {
					for (int item_index = 0; item_index < IM_ARRAYSIZE(items); item_index++) {
						const bool is_selected = (currItemIndex == item_index);
						if (ImGui::Selectable(items[item_index], is_selected)) {
								currItemIndex = item_index;
								mesh->Name = items[item_index];
								mesh->Mesh = fr::Resource.GetMesh(items[item_index]);
						}
					}
					ImGui::EndCombo();
				}
				ImGui::PopStyleVar();
			}
			ImGui::EndChildFrame();
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[0]);
		}

		// Material

		if (ImGui::CollapsingHeader("Material")) {
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[1]);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, FRAME_PADDING);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, DARK);

			ImGui::BeginChildFrame(ImGui::GetID("matframe"), ImVec2(0, 95));
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			{
				ImGui::PushStyleColor(ImGuiCol_Button, GREEN);
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));
				
				// Albedo
				if (ImGui::Button("Albedo", ImVec2(60, 18))) { material->Albedo = glm::vec3(1.0); }
				ImGui::SameLine();
				ImGui::SetNextItemWidth(-1);
				ImGui::ColorEdit3("##Color", glm::value_ptr(material->Albedo), ImGuiColorEditFlags_Float);

				// Ambient Occlusion
				if (ImGui::Button("A-Occlusion", ImVec2(60, 18))) { material->Ao = 1.0f; }
				ImGui::SameLine();
				ImGui::SetNextItemWidth(-1);
				ImGui::DragFloat("##ao", &material->Ao, 0.01f, 0.01f, 1.0f, "%.2f");

				// Roughness
				if (ImGui::Button("Roughness", ImVec2(60, 18))) { material->Roughness = 0.01f; }
				ImGui::SameLine();
				ImGui::SetNextItemWidth(-1);
				ImGui::DragFloat("##roughness", &material->Roughness, 0.01f, 0.01f, 1.0f, "%.2f");

				// Mettalic
				if (ImGui::Button("Metallic", ImVec2(60, 18))) { material->Metallic = 0.01f; }
				ImGui::SameLine();
				ImGui::SetNextItemWidth(-1);
				ImGui::DragFloat("##mettalic", &material->Metallic, 0.01f, 0.01f, 1.0f, "%.2f");

				ImGui::PopStyleVar();
				ImGui::PopStyleColor();
			}
			ImGui::EndChildFrame();
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[0]);
		}
	}

private:
	MeshRenderer* mesh;
	Material* material;
	char buffer[20];
    int currItemIndex;
    const char* items[2] = { "CUBE", "SPHERE"};
};