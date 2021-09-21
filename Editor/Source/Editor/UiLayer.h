#pragma once

#ifndef FR_UILAYER_H
#define FR_UILAYER_H

#include "CompUIs/CompUI.h"
#include "Vendor/IMGUI/imgui.h"
#include "Vendor/GUIZMO/ImGuizmo.h"

struct Transform;

const ImVec4 dark = ImVec4(0.17f, 0.17f, 0.17f, 1.0f);

namespace fr {

	struct ViewPortRect {
		float X, Y, W, H = 0;
	};

	struct Gizmo {
		bool UseSnap = false;
		glm::mat4 View, Proj, Model;
		glm::vec3 Snap = glm::vec3(0);
		Transform* cTransform = nullptr;
		ImGuizmo::MODE Mode = ImGuizmo::LOCAL;
		ImGuizmo::OPERATION Operation = ImGuizmo::TRANSLATE;
	};

	using EntityField = std::tuple<size_t, std::string, ImTextureID>;

	class UiLayer {

	public:
		~UiLayer() = default;
		UiLayer(const UiLayer&) = delete;
		UiLayer& operator=(const UiLayer&) = delete;
		static UiLayer& Ref() {
			static UiLayer ref;
			return ref;
		}

		FRuint Display();
		FRuint Initialiaze();
		FRuint AddExistingEntity(const size_t entity);

		void AddComponent(const char* typeName);
		void RemoveComponent(const char* typeName);

		void MoveEntityUp();
		void MoveEntityDown();

		void AddNewEntity();
		void RemoveEntity();
		void SetLastSelectedEntity(int n) { lastSelectedEntity = n; }
		void Tg() { TransformGizmo(); }

		void SetGizmoViewProjection(glm::mat4 view, glm::mat4 proj) {
			gizmo.View = view;
			gizmo.Proj = proj;
		}

		static void AddToConsole(std::string Log);

		inline const ViewPortRect ViewportRect() const { return viewRect; }
		inline const bool IsUsingGizmo() const { return ImGuizmo::IsUsing(); }
		inline const Gizmo GetGizmo() { return gizmo; }
		inline const glm::vec2 ViewSize() const { return glm::vec2(viewRect.W, viewRect.H); }
		inline const ImTextureID GetSceneFrameTexture() { return sceneFrameTexture; }
		inline const int GetSelectedEntity() { return selectedEntity; }
		inline const int GetLastSelectedEntity() { return lastSelectedEntity; }
		std::map<std::string, ImTextureID> GetIcons() { return icons; }
		std::vector<std::shared_ptr<CompUI>> GetActiveCompUIs() { return activeCompUIs; }
		std::vector<EntityField> GetEntities() { return entities; }

		void SetGizmoOperation(ImGuizmo::OPERATION o) { gizmo.Operation = o; }

	private:
		UiLayer();
		void LoadIcons();
		void SetGuiStyle();

		// PANELS

		void Entities();
		void Dockspace();
		void ToolBar();
		void Viewport();
		void RendererInfo();

		// ACTIONS

		void InitCompUI();
		void TransformGizmo();

	private:
		int selectedEntity;
		int lastSelectedEntity;
		ImGuiWindowFlags window_flags;

		Gizmo gizmo;
		ViewPortRect viewRect;
		ImTextureID sceneFrameTexture;
		std::vector<EntityField> entities;

		std::map<std::string, ImTextureID> icons;
		std::vector<std::shared_ptr<CompUI>> compUIs;
		std::vector<std::shared_ptr<CompUI>> activeCompUIs;
	};

	static UiLayer& UI = UiLayer::Ref();
}

#endif