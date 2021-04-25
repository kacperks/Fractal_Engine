#pragma once

#include "ECS/Base/BaseComponent.h"

#include <iostream>

struct CppScript : public ECS::BaseComponent {
	void OpenAssembly() {
		// not finished yet!
	}

	void AddToRuntimeSystem() {
		// not finished yet
	}

public:
	std::string AssemblyPath;
	std::string ClassName;
};