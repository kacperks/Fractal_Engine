#pragma once

#include "pch.h"
#include "Core/Window.h"

struct Scene {
	Scene() = default;
	~Scene() = default;

	void Update();
	FRuint Initialize();

	UiLayer Editor;
	T_Timer Timer;
	XMLSerializer Serializer;
	RsrcManager Resource;
	EventSystem Events;
	Engine Core;
};