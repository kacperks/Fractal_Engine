#pragma once

#include "pch.h"

class Physics {
	public:
		Physics();
		virtual ~Physics();

		void UpdatePhysics();
	private:
		float GravitationalConstant = 9.807;
};