#pragma once

#include "Resource/Resource.h"
#include "ECS/Base/BaseComponent.h"

using namespace Orbit3D;

struct MeshRenderer : public ECS::BaseComponent {
	~MeshRenderer() = default;

	MeshRenderer(std::string name="CUBE"): Name(name) {
		Mesh = Resource.GetMesh(Name);
	}
	
	GLMesh Mesh;
	std::string Name;
};

