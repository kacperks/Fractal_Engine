#pragma once

#include "CompUIs/CompUI.h"
#include "../vendor/imgui/imgui.h"
#include "../vendor/GUIZMO/ImGuizmo.h"

struct Transform;

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

		void Display();
		void Initialiaze();
		void LightTheme();
		void DarkTheme();
		void AddExistingEntity(const size_t entity);
		void SetGizmoViewProjection(glm::mat4 view, glm::mat4 proj) {
			gizmo.View = view;
			gizmo.Proj = proj;
		}

		inline const ViewPortRect ViewportRect() const { return viewRect; }
		inline const bool IsUsingGizmo() const { return ImGuizmo::IsUsing(); }
		inline const glm::vec2 ViewSize() const { return glm::vec2(viewRect.W, viewRect.H); }

	private:
		UiLayer();
		void LoadIcons();
		void SetGuiStyle();

		// PANELS

		void MenuBar();
		void Viewport();
		void Components();
		void Console();
		void Entities();
		void Resources();
		void CodeEditor();
		void Dockspace();

		// ACTIONS

		void MoveEntityUp();
		void MoveEntityDown();

		void AddNewEntity();
		void RemoveEntity();

		void AddComponent(const char* typeName);
		void RemoveComponent(const char* typeName);

		void AddAsset(const char* Name);

		void InitCompUI();
		void TransformGizmo();
		void OnImGui(std::string directoryPath);
		std::pair<bool, uint32_t> DirectoryTreeViewRecursive(const std::filesystem::path& path, uint32_t* count, int* selection_mask);

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