#pragma once

#include "../../Engine/Engine.h"
#include "../../Inputs/Inputs.h"
#include "../../Errors/ErrorLog.h"

#include "../Base/BaseSystem.h"
#include "../../GLObjects/Shader.h"
#include "../Components/Camera.h"
#include "../Components/Transform3D.h"

class CameraSystem : public ECS::BaseSystem {

public:
	void OnStart() override {
		AddComponentSignature<Transform3D>();		
		AddComponentSignature<Camera>();	

		float width = FuseOrbit3D::DispWidth();
		float height = FuseOrbit3D::DispHeight();

		GLCALL(glViewport(0, 0, width, height));
		glm::ortho(0.0f, width, 0.0f, height, 0.1f, 100.0f);

		shader = Shader(RESOURCE.GetShader("SHADER"));
		skyboxShader = Shader(RESOURCE.GetShader("SKYBOX"));
	}

	void OnUpdate() override {
		for (auto entity : entities) {
			auto& transform = FuseOrbit3D::Manager.GetComponent<Transform3D>(entity);
			auto& camera = FuseOrbit3D::Manager.GetComponent<Camera>(entity);

			OnZoom(camera);
			//OnDrag(camera);

			const GLfloat Ratio = FuseOrbit3D::DispWidth() / FuseOrbit3D::DispHeight();

			// view, projection position
			FuseOrbit3D::Zoom = camera.Zoom;
			FuseOrbit3D::MainCameraPostion = transform.Position;
			FuseOrbit3D::Projection = glm::perspective(camera.Zoom, Ratio, 0.1f, 100.0f);

			FuseOrbit3D::View = glm::lookAt(transform.Position, (transform.Position + camera.Front), camera.Up);
			FuseOrbit3D::View = glm::rotate(FuseOrbit3D::View, glm::radians(transform.Rotation.x), AXIS_X);
			FuseOrbit3D::View = glm::rotate(FuseOrbit3D::View, glm::radians(transform.Rotation.y), AXIS_Y);
			FuseOrbit3D::View = glm::rotate(FuseOrbit3D::View, glm::radians(transform.Rotation.z), AXIS_Z);			

			// skybox view
			glm::mat4 skyboxProj = glm::perspective(ZOOM, Ratio, 0.1f, 100.0f);
			glm::mat4 skyboxView = glm::lookAt(glm::vec3(0.0f), camera.Front, camera.Up);
			skyboxView = glm::rotate(skyboxView, glm::radians(transform.Rotation.x), AXIS_X);
			skyboxView = glm::rotate(skyboxView, glm::radians(transform.Rotation.y), AXIS_Y);
			skyboxView = glm::rotate(skyboxView, glm::radians(transform.Rotation.z), AXIS_Z);

			shader.Bind();
			shader.SetV3f("CameraPosition", transform.Position);
			shader.SetMatrix4f("View", glm::value_ptr(FuseOrbit3D::View));
			shader.SetMatrix4f("Projection", glm::value_ptr(FuseOrbit3D::Projection));
			shader.UnBind();

			skyboxShader.Bind();
			skyboxShader.SetMatrix4f("View", glm::value_ptr(skyboxView));
			skyboxShader.SetMatrix4f("Projection", glm::value_ptr(skyboxProj));
			skyboxShader.SetSampleCube("CubeMap", RESOURCE.GetCubemap("skybox"));
			skyboxShader.UnBind();
		}
	}

private:
	void OnDrag(Camera& camera) {
		auto& event = Inputs::Event();
		if (event.IsMouseMoving() && event.IsMouseDown(MouseButton::LEFT)) {
			glm::vec2 offset = event.MouseMotionOffset() * camera.Sensitivity;

			camera.Yaw += offset.x;
			camera.Pitch += offset.y;

			if (camera.ContrainPitch) {
				if (camera.Pitch > MAX_PITCH) {
					camera.Pitch = MAX_PITCH;
				}

				if (camera.Pitch < -MAX_PITCH) {
					camera.Pitch = -MAX_PITCH;
				}
			}

			// Calculate the new Front vector
			glm::vec3 front(0.0f);
			front.x = cos(glm::radians(camera.Yaw)) * cos(glm::radians(camera.Pitch));
			front.y = sin(glm::radians(camera.Pitch));
			front.z = sin(glm::radians(camera.Yaw)) * cos(glm::radians(camera.Pitch));
			camera.Front = glm::normalize(front);

			// Also re-calculate the Right and Up vector
			// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			camera.Right = glm::normalize(glm::cross(camera.Front, camera.WorldUp));
			camera.Up = glm::normalize(glm::cross(camera.Right, camera.Front));
		}
	}

	void OnZoom(Camera& camera) {
		auto& event = Inputs::Event();
		if (event.IsMouseScrolling()) {
			camera.Zoom -= event.MouseScrollOffset().y * camera.ScrollStep;
			camera.Zoom = (camera.Zoom <= 1.0f) ? 1.0f : camera.Zoom;
			camera.Zoom = (camera.Zoom >= ZOOM) ? ZOOM : camera.Zoom;
		}		
		event.ResetScrollState();
	}

private:
	Shader shader, skyboxShader;
};
