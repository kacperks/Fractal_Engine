#pragma once

#include "../GLObjects/Model.h"
#include "../GLObjects/GLMesh.h"

const std::string ICON_PATH = "../../res/Icons/";
const std::string MODEL_PATH = "../../res/Models/";
const std::string SHADERS_PATH = "../../res/Shaders/";
const std::string TEXTURE_PATH = "../../res/extures/";

namespace fr {

	class RsrcManager{
	public:
		~RsrcManager();
		RsrcManager(const RsrcManager&) = delete;
		RsrcManager& operator=(const RsrcManager&) = delete;
		static RsrcManager& Ref() {
			static RsrcManager reference;
			return reference;
		}

		void Initialize();

		// texture
		const GLuint LoadTex2D(std::string filename);
		void AddTex2D(std::string name, const GLuint texID);
		const GLuint Tex2D(std::string name) {
			assert(texture2ds.find(name) != texture2ds.end() && "TexID out of range!");
			return texture2ds.at(name);
		}

		// Cubemap texture
		void LoadCubeMap(std::string name, std::vector<std::string> faces);
		const GLuint CubeMap(std::string name) {
			assert(cubemaps.find(name) != cubemaps.end() && "Cubemap out of range!");
			return cubemaps.at(name);
		}

		// meshes
		void LoadMeshes();
		const GLMesh& GetMesh(std::string name) {
			assert(meshes.find(name) != meshes.end() && "Mesh out of range!");
			return meshes[name];
		}

		// models
		void LoadModel(std::string name, std::string filename);
		std::shared_ptr<Model3D> GetModel(std::string name) {
			assert(models.find(name) != models.end() && "Model out of range!");
			return models[name];
		}

		// shaders
		const GLuint Program(std::string name);
		void CreateProgram(std::string name, std::string vtxFile, std::string fragFile);

	private:
		RsrcManager();
		void CreateSphere(GLuint X_SEGMENTS = 64, GLuint Y_SEGMENTS = 64);
		std::string LoadShaderSource(std::string filename);
		const GLuint ComplieShaderSource(GLenum type, const GLchar* src);

	private:
		std::map<std::string, GLMesh> meshes;
		std::map<std::string, GLuint> shaders;
		std::map<std::string, GLuint> cubemaps;
		std::map<std::string, GLuint> texture2ds;
		std::map<std::string, std::shared_ptr<Model3D>> models;
	};

	static RsrcManager& Resource = RsrcManager::Ref();
}

