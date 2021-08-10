#pragma once

#include "pch.h"

class Scene {
public:
	Scene();
	Scene(UiLayer UI, T_Timer timer, XMLSerializer serializer, RsrcManager Resource, EventSystem events, Engine core);
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