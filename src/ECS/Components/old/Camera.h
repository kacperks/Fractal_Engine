#pragma once

#include "../Base/BaseComponent.h"
#include <glm/ext/vector_float3.hpp>

const float YAW = -90.0f;
const float ZOOM = 45.0f;
const float PITCH = 0.0f;
const float MAX_PITCH = 89.0f;
const float SENSITIVTY = 0.04f;

struct Camera : public ECS::BaseComponent {

	Camera(): Front(0.0f, 0.0f, -1.0f), Up(0.0f, 1.0f, 0.0f), 
		Right(1.0f, 0.0f, 0.0f), WorldUp(0.0f, 1.0f, 0.0f),Pitch(PITCH), Yaw(YAW),
		Sensitivity(SENSITIVTY), Zoom(ZOOM), ScrollStep(0.1f), ContrainPitch(true) { }

	~Camera() = default;
	
	// camera vectors
	glm::vec3 WorldUp;
	glm::vec3 Front;
	glm::vec3 Right;
	glm::vec3 Up;

	// Eular angles
	float Yaw;
	float Pitch;

	// motion
	float Zoom;
	float ScrollStep;
	float Sensitivity;
	bool ContrainPitch;
};

