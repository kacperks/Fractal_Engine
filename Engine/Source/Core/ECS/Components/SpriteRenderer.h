#pragma once

#include "Core/Resource/Resource.h"
#include "Core/ECS/Base/BaseComponent.h"

struct SpriteRenderer : public ECS::BaseComponent{
	~SpriteRenderer() = default;
	SpriteRenderer() = default;
	SpriteRenderer(std::string name): TexName(name) {
		TexID = fr::Resource.Tex2D(TexName);
	}

	void SetUniform(Shader& shader) {
		shader.Bind();
		shader.SetSample2D("Sprite", TexID);
	}

	GLuint TexID=0;
	std::string TexName;
};