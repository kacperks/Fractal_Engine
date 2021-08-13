#pragma once

#include "pch.h"

struct Scene {
	Scene();
	Scene(UiLayer UI, T_Timer timer, XMLSerializer serializer, RsrcManager Resource, EventSystem events, Engine core);
	~Scene();

	UiLayer Editor;
	T_Timer Timer;
	XMLSerializer Serializer;
	RsrcManager Resource;
	EventSystem Events;
	Engine Core;
};