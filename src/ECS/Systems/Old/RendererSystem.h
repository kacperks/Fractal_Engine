#pragma once

#include "../Base/BaseSystem.h"
#include "../Components/Material.h"
#include "../Components/Transform3D.h"

#include "../../Engine/Engine.h"
#include "../../Errors/ErrorLog.h"
#include "../../Resource/Resource.h"

#include "../../GLObjects/Shader.h"
#include "../../GLObjects/VertexArray.h"
#include "../../GLObjects/FrameBuffer.h"

class RendererSystem : public ECS::BaseSystem {

public:
	RendererSystem() : frameFBO(nullptr){
		AddComponentSignature<Transform3D>();
		AddComponentSignature<Material>();
	}

	void OnStart() {			
		frameFBO = new FrameBuffer(FuseOrbit3D::DispWidth(), FuseOrbit3D::DispHeight());
		RESOURCE.AddTex2D("SceneFBO", frameFBO->GetTexID());

		skyboxShader = Shader(RESOURCE.GetShader("SKYBOX"));
		rendererShader = Shader(RESOURCE.GetShader("SHADER"));

		GLCALL(glEnable(GL_DEPTH_TEST));
		GLCALL(glEnable(GL_STENCIL_TEST));	
	}

	void OnUpdate() {	
		frameFBO->SetSize(FuseOrbit3D::DispWidth(), FuseOrbit3D::DispHeight());		
		if (FuseOrbit3D::Core.mode == OperationMode::EDIT_MODE) { frameFBO->Clear(); }
		
		rendererShader.Bind();
		for (auto entity : entities) {
			auto& transform = FuseOrbit3D::Manager.GetComponent<Transform3D>(entity);
			auto& material = FuseOrbit3D::Manager.GetComponent<Material>(entity);

			glm::mat4 model(1.0f);
			model = glm::translate(model, transform.Position);
			model = glm::rotate(model, glm::radians(transform.Rotation.x), AXIS_X);
			model = glm::rotate(model, glm::radians(transform.Rotation.y), AXIS_Y);
			model = glm::rotate(model, glm::radians(transform.Rotation.z), AXIS_Z);
			model = glm::scale(model, transform.Scale);

			rendererShader.SetMatrix4f("Model", glm::value_ptr(model));
			rendererShader.Set1f("material.shininess", material.Shininess);

			if (material.DiffuseTextureID != 0) {
				rendererShader.SetSample2D("diffuseTexture", material.DiffuseTextureID, 1);
				rendererShader.SetSample2D("specularTexture", material.SpecularTextureID, 2);
			}
			else {
				rendererShader.Set1i("material.hasTexture", false);
				rendererShader.SetV3f("material.ambient", material.Ambient);
				rendererShader.SetV3f("material.diffuse", material.Diffuse);
				rendererShader.SetV3f("material.specular", material.Specular);
			}

			VertexArray(RESOURCE.GetMesh("CUBE"), 0, 36, GL_TRIANGLES).Draw();
		}

		RenderSkybox();
		frameFBO->UnBind();
	}	

	void RenderSkybox() {
		GLCALL(glDepthMask(GL_FALSE));
		GLCALL(glDepthFunc(GL_LEQUAL));		
	
		skyboxShader.Bind();
		VertexArray(RESOURCE.GetMesh("SKYBOX"), 0, 36, GL_TRIANGLES).Draw();
		skyboxShader.UnBind();

		GLCALL(glDepthMask(GL_TRUE));
		GLCALL(glDepthFunc(GL_LESS));
	}
	
private:
	FrameBuffer* frameFBO;
	Shader rendererShader, skyboxShader;
};

