#pragma once

#include "pch.h"

struct Scene {
	Scene() = default;
	~Scene() = default;

	void Initialize();
	void Update();

	ECS::Entity To_Entity(ECS::EntityID _handle);

	UiLayer Editor;
	T_Timer Timer;
	XMLSerializer Serializer;
	RsrcManager Resource;
	EventSystem Events;
	Engine Core;
};