#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../ECS/ECS.h"
#include "../GLObjects/FrameBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr int SCREEN_WIDTH(1280);
constexpr int SCREEN_HEIGHT(720);

enum class OperationMode { GAME_MODE = 0, EDIT_MODE = 1 };

class Engine {
public:	
	OperationMode mode;
	float Zoom;
	glm::mat4 View;
	glm::mat4 Projection;
	glm::vec3 MainCameraPostion;
	ECS::EntityManager Manager;

	~Engine();
	static Engine& Get() {
		static Engine instance;
		return instance;
	}

	void Update();
	void Initialize();

	void Quit() {
		OnRun = false;
	}

	void UpdateScreenSize(float w, float h) {
		screenWidth = w;
		screenHeight = h;
	}
	float DisplayWidth() { return screenWidth; }
	float DisplayHeight() { return screenHeight; }

	inline const bool OnRunApp() const { return OnRun; }
	inline GLFWwindow& Window() { return *window; }
	inline const float DeltaTime() { return deltaTime; }
	const bool Run() { return !glfwWindowShouldClose(window); }
	inline ECS::EntityManager& GetManager() { return Manager; }

private:
	Engine();
	void UpdateDeltaTime();
	void InitializeEntities();

private:	
	bool OnRun;
	GLFWwindow* window;	
	FrameBuffer screenBuffer;
	float lastFrame, deltaTime;
	float screenWidth, screenHeight;	
};

namespace fr {
	const static int EXIT_PROG_SUCCESS = 0;
	const static int EXIT_PROG_FAILURE = -1;

	static Engine& Core = Engine::Get();
	static ECS::EntityManager& Manager = Core.Manager;

	static float& Zoom = Core.Zoom;
	static glm::mat4& View = Core.View;
	static glm::mat4& Projection = Core.Projection;
	static glm::vec3& MainCameraPostion = Core.MainCameraPostion;

	static float DispWidth() {
		return Core.DisplayWidth();
	}

	static float DispHeight() {
		return Core.DisplayHeight();
	}
}

