#pragma once

#include "../../fractal.hpp"

// not finished yet

struct LuaScript : public ECS::BaseComponent {
	void InvokeStart(){}
	void InvokeUpdate(){}

	public:
		std::string FileName;
};