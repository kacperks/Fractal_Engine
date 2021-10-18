#pragma once
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/pbrmaterial.h>
#include <assimp/postprocess.h>

#include "GLMesh.h"
#include "Vendor/STB/stb_image.h"
#include <termcolor/termcolor.hpp>

using namespace fr;

class Model3D {

public:
	Model3D(std::string filename) {		
		Load(filename);
	}

	~Model3D() {
		for (auto texture : loadedTexMaps) {
			GLCALL(glDeleteTextures(1, &texture.second));
		}
	}

	void Render(Shader& shader) {
		for (auto mesh : meshes) {
			mesh.Render(shader, GL_TRIANGLES);
		}
	}

private:
	void Load(std::string filename) {
		Assimp::Importer loader;
		directory = filename.substr(0, filename.find_last_of('/')).append("/");
		const aiScene* scene = loader.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << termcolor::red << "Assimp Error! : " << loader.GetErrorString() << std::endl;
			return;
		}
		ParseNode(scene->mRootNode, scene);
	}

	void ParseNode(aiNode* node, const aiScene* scene) {
		for (GLuint i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			ParseMesh(mesh, scene);
		}

		for (GLuint i = 0; i < node->mNumChildren; i++) {
			ParseNode(node->mChildren[i], scene);
		}
	}

	void ParseMesh(aiMesh* mesh, const aiScene* scene) {

		std::vector<GLuint> indices;
		std::vector<Vertex> vertices;

		// vertices
		for (GLuint i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			vertex.Position.x = mesh->mVertices[i].x;
			vertex.Position.y = mesh->mVertices[i].y;
			vertex.Position.z = mesh->mVertices[i].z;

			// normals
			if (mesh->HasNormals()) {
				vertex.Normal.x = mesh->mNormals[i].x;
				vertex.Normal.y = mesh->mNormals[i].y;
				vertex.Normal.z = mesh->mNormals[i].z;
			}

			// texture coordinates
			if (mesh->mTextureCoords[0]) {
				vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
				vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
			}

			vertices.push_back(vertex);
		}

		// indices		
		for (GLuint i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (GLuint j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		GLMesh glMesh(vertices.data(), vertices.size(), indices.data(), indices.size());

		// material
		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* aMaterial = scene->mMaterials[mesh->mMaterialIndex];
			glMesh.SetMaterial(ParseMaterial(aMaterial));
		}

		meshes.push_back(glMesh);
	}

	Material ParseMaterial(aiMaterial* aMaterial) {
		Material glMaterial(glm::vec3(0), 0.01, 0.01, 1.0);

		aiColor3D kd(0.f, 0.f, 0.f);
		if (aMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, kd) == 0) {
			glMaterial.Albedo = glm::vec3(kd.r, kd.g, kd.b);
		}

		ai_real metallic ;
		if (aMaterial->Get(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLIC_FACTOR, metallic) == 0) {
			glMaterial.Metallic = metallic;
		}

		ai_real roughness;
		if (aMaterial->Get(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_ROUGHNESS_FACTOR, roughness) == 0) {
			glMaterial.Roughness = roughness;
		}
		
		glMaterial.AlbedoMap = GetTexMap(aMaterial, aiTextureType_DIFFUSE);
		glMaterial.NormalMap = GetTexMap(aMaterial, aiTextureType_NORMALS);
		glMaterial.MetallicMap = GetTexMap(aMaterial, aiTextureType_METALNESS);
		glMaterial.AoMap = GetTexMap(aMaterial, aiTextureType_AMBIENT_OCCLUSION);
		glMaterial.RoughnessMap = GetTexMap(aMaterial, aiTextureType_DIFFUSE_ROUGHNESS);
		return glMaterial;
	}

	GLuint GetTexMap(aiMaterial* aMaterial, aiTextureType type) {
		int count = aMaterial->GetTextureCount(type);

		if (count > 0) {
			for (int i = 0; i < count; i++) {
				aiString name;
				aMaterial->GetTexture(type, i, &name);

				if (loadedTexMaps.find(name.C_Str()) != loadedTexMaps.end()) {
					return loadedTexMaps.at(name.C_Str());
				}

				std::cout << name.C_Str() << std::endl;

				std::string path = directory;
				path.append(name.C_Str());
				GLuint texID = LoadTex2D(path);
				loadedTexMaps.insert({ name.C_Str(), texID });
				return texID;
			}
		}

		return 0;
	}
public:
	const GLuint LoadTex2D(std::string filename) {
		int w, h = 0;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* buffer = stbi_load(filename.c_str(), &w, &h, nullptr, 4);

		GLuint textureID;
		GLCALL(glGenTextures(1, &textureID));
		GLCALL(glBindTexture(GL_TEXTURE_2D, textureID));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
		GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(buffer);
		return textureID;
	}

private:	
	std::string directory;
	std::vector<GLMesh> meshes;
	std::map<const char*, GLuint> loadedTexMaps;
};
