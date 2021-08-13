#pragma once

#include "Core/Resource/Resource.h"
#include "Scene/BaseComponent.h"

using namespace fr;

struct MeshRenderer : public ECS::BaseComponent {
	~MeshRenderer() = default;

	MeshRenderer(std::string name="CUBE"): Name(name) {
		Mesh = Resource.GetMesh(Name);
	}
	
	GLMesh Mesh;
	std::string Name;
};

