#pragma once

#include "pch.h"

class Scene {
public:
	Scene();
	~Scene();

	void InitScene();
	void UpdateScene();

private:
	UiLayer Editor;
	T_Timer timer;
	XMLSerializer serializer;
	RsrcManager resource;
	EventSystem events;
	Engine core;
};