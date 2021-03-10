#pragma once

#include "../Base/BaseComponent.h"
#include "../../Resource/Resource.h"

#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <ASSIMP/postprocess.h>
#include <ASSIMP/Importer.hpp>
#include <ASSIMP/scene.h>

struct Name : public ECS::BaseComponent {
	std::string Value;
	Name(): Value("Entity") {}
	Name(std::string value):Value(value) {}
};

struct Tag : public ECS::BaseComponent {
	std::string Value;
	Tag() : Value("") {}
	Tag(std::string value) : Value(value) { }
};

struct Renderer : public ECS::BaseComponent {

};

struct Texture {
	GLuint ID;
	aiString Path;
	std::string Type; // diffuse or specular
};

struct Vertex {
	glm::vec3 Position = glm::vec3(0.0f);
	glm::vec3 Normal = glm::vec3(0.0f);
	glm::vec2 TexCoords = glm::vec2(0.0f);
};

class Mesh {
public:	
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures):
	Vertices(vertices), Indices(indices), Textures(textures), VAO(0), VBO(0), EBO(0){
		SetUp();
	}

	void Draw(GLuint shader) {
		GLuint diffuseNr = 1;
		GLuint specularNr = 1;
		for (GLuint i = 0; i < Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding 
			// Retrieve texture number (the N in diffuse_textureN)
			std::stringstream ss;			
			std::string number;
			std::string name = Textures[i].Type;
			if (name == "texture_diffuse")
				ss << diffuseNr++; // Transfer GLuint to stream
			else if (name == "texture_specular")
				ss << specularNr++; // Transfer GLuint to stream

			number = ss.str();
			glUniform1f(glGetUniformLocation(shader, (name + number).c_str()), i);
			glBindTexture(GL_TEXTURE_2D, Textures[i].ID);
		}
		glActiveTexture(GL_TEXTURE0);
		// Draw mesh
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

private:
	void SetUp() {
		//generate buffers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		//set buffers
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(GLuint), &Indices[0], GL_STATIC_DRAW);

		// Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		// Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		// Texture Coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}

public:
	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;
	std::vector<Texture> Textures;

private:
	GLuint VAO, VBO, EBO;
};

class Model {
public:
	std::vector<Texture> textures_loaded;

public:
	Model(const GLchar* filename) {
		Load(filename);
	}

	void Draw(GLuint shader) {
		for (auto mesh : meshes) mesh.Draw(shader);
	}

private:
	void Load(std::string filename) {
		Assimp::Importer loader;
		const aiScene* scene = loader.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs); 
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "ERROR::ASSIMP::" << loader.GetErrorString() << std::endl;
			return;
		}
		directory = filename.substr(0, filename.find_last_of('/'));
		ProcessNode(scene->mRootNode, scene);
	}

	void ProcessNode(aiNode* node, const aiScene* scene) {
		// Process all the node�s meshes (if any)
		for (GLuint i = 0; i < node->mNumMeshes; i++){
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(ProcessMesh(mesh, scene));
		}
		// Then do the same for each of its children
		for (GLuint i = 0; i < node->mNumChildren; i++){
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene) {
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		// vertices
		for (GLuint i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			vertex.Position.x = mesh->mVertices[i].x;
			vertex.Position.y = mesh->mVertices[i].y;
			vertex.Position.z = mesh->mVertices[i].z;

			vertex.Normal.x = mesh->mNormals[i].x;
			vertex.Normal.y = mesh->mNormals[i].y;
			vertex.Normal.z = mesh->mNormals[i].z;

			if (mesh->mTextureCoords[0]) {
				vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
				vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
			}

			vertices.push_back(vertex);
		}

		// indices
		for (GLuint i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (GLuint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// material
		if (mesh->mMaterialIndex >= 0){
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName) {
		std::vector<Texture> textures;
		for (GLuint i = 0; i < material->GetTextureCount(type); i++)
		{
			aiString str;
			material->GetTexture(type, i, &str);
			GLboolean canLoad = true;
			for (GLuint j = 0; j < textures_loaded.size(); j++) {
				if (textures_loaded[j].Path == str) {
					textures.push_back(textures_loaded[j]);
					canLoad = false;
					break;
				}
			}

			if (canLoad) {
				Texture texture;				
				texture.ID = RESOURCE.LoadTex2D(str.C_Str());
				texture.Type = typeName;
				texture.Path = str;
				textures.push_back(texture);
				textures_loaded.push_back(texture);
			}
		}

		return textures;
	}

private:
	std::string directory;
	std::vector<Mesh> meshes;
};
