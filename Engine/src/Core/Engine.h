#pragma once

#ifndef FR_ENGINE
#define FR_ENGINE

#include "Renderer/DepthBuffer.h"
#include "Renderer/SamplerBuffer.h"

#include "ECS/ECS.h"
#include "pch.h"

namespace fr {
	const int SHADOW_WIDTH = 1024;
	const int SHADOW_HEIGHT = 1024;

	class Engine {

	public:
		~Engine();
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		static Engine& Ref() {
			static Engine reference;
			return reference;
		}

		void OnQuit(const Event& e) {
			isRunning = false;
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		void OnViewportResized(const Event& e) {
			auto event = Dispatcher.Cast<ViewportResizedEvent>(e);
			viewSize.x = event.Width();
			viewSize.y = event.Height();
			outputBuffer->SetSize(viewSize.x, viewSize.y);
			glViewport(0, 0, viewSize.x, viewSize.y);

			std::cout << "viewport resised! " << viewSize.x << "\n";
		}

		void SetViewport(glm::vec2 size) {
			viewSize = size;
			outputBuffer->SetSize(size.x, size.y);
			glViewport(0, 0, size.x, size.y);
		}

		void LockCursor() {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		void Update();
		void Render();
		void StopGame();
		void StartGame();
		FRuint Initialize();
		void SetCommandLineArgs(CommandLineArgs args) { commandLineArguments = args; }

		inline glm::vec2 ViewSize() const { return viewSize; }
		inline DepthBuffer* ShadowBuffer() const { return shadowBuffer; }
		inline SamplerBuffer* GetSceneBufferID() const { return outputBuffer; }

		inline GLFWwindow& Window() { return *window; }
		inline const bool Run() const { return isRunning; }
		inline const bool GameRun() const { return isGameRunnig; }

	private:
		Engine();

	private:
		bool isRunning;
		bool isGameRunnig;
		CommandLineArgs commandLineArguments;

		// I will use FRWindow instead of theese variables:
		GLFWwindow* window;
		Vector2i viewSize;
		DepthBuffer* shadowBuffer;
		SamplerBuffer* outputBuffer;
	};

	static Engine& Core = Engine::Ref();
	
	void PrintEngineInfo() {
		time_t curr;
		time(&curr);
		std::string year = std::to_string(std::localtime(&curr)->tm_year + 1900);
		
		std::cout << 		"------ Fractal Engine ------" 			 			<< std::endl;
		std::cout <<		"------ Year: " << year << "------"					<< std::endl;
		std::cout << 		"---------------------------------------------" 			<< std::endl;
		std::cout << 		"------ Contributors, Developers(GitHub Account Names) ------" 		<< std::endl;
		std::cout << 		"------ Developer: KacperKostka08(Fractal Engine Owner) ------" 	<< std::endl;
		std::cout << 		"------ Developer: lubek-dc ------" 					<< std::endl;
		std::cout << 		"------ Developer: BoomerDev ------" 					<< std::endl;
		std::cout << 		"------ Contributor: Yavuz1234567890 ------" 				<< std::endl;
		std::cout << 		"------ Contributor: honeystudios ------" 				<< std::endl;
		std::cout << 		"---------------------------------------------" 			<< std::endl;
		std::cout << 		"------ Features ------" 						<< std::endl;
		std::cout << 		"------ ImGui Editor ------" 						<< std::endl;
		std::cout << 		"------ OpenGL Support ------" 						<< std::endl;
		std::cout << 		"------ Loading 3D models with ASSIMP ------" 				<< std::endl;
		std::cout << 		"------ Loading 2D textures with stbimage ------" 			<< std::endl;
		std::cout << 		"------ Fully Featured ECS(Entity-Component-System) ------" 		<< std::endl;
		std::cout << 		"------ Scene System (XML) ------" 					<< std::endl;
		std::cout << 		"------ Light System ------" 						<< std::endl;
		std::cout << 		"------ Gizmos ------" 							<< std::endl;
		std::cout << 		"---------------------------------------------" 			<< std::endl;
	}
}

#endif
