#pragma once

#include <map>
#include <string>
#include <vector>
#include <GL/glew.h>

class Resource {
public:
	~Resource();	

	static Resource& Get() {
		static Resource instance;
		return instance;
	}

	void Initialize();

	// Meshes
	void LoadMeshes(const GLchar* filename);
	const GLuint GetMesh(const char* name);

	// Textures
	GLuint LoadTex2D(const char* filename);
	const GLuint GetTex2D(const char* name);
	void AddTex2D(const char* name, const GLuint texID);

	// Cubemap texture
	const GLuint GetCubemap(const char* name);
	void LoadCubemap(const char* name, std::vector<const char*> faces);

	// shaders
	const GLuint GetShader(const char* name);
	void BuildShader(const char* name, const char* vertex, const char* fragment);

private:
	Resource();
	const std::string LoadShader(const char* filename);
	const GLuint ComplieShader(GLenum type, const GLchar* src);

private:
	std::map<std::string, GLuint> meshes;
	std::map<std::string, GLuint> shaders;
	std::map<std::string, GLuint> cubemaps;
	std::map<std::string, GLuint> texture2ds;
};

static Resource& RESOURCE = Resource::Get();