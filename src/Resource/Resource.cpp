#include "Resource.h"

#include <map>
#include <vector>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../Errors/ErrorLog.h"
#include "../vendor/STB/stb_image.h"

Resource::Resource() {

}

Resource::~Resource() {
	// destroy all texture
	for (auto texture : texture2ds) {
		glDeleteTextures(1, &texture.second);
	}

	// destroy all shaders
	for (auto program : shaders) {
		glDeleteProgram(program.second);
	}

	// destroy all shaders
	for (auto vao : meshes) {
		glDeleteVertexArrays(1, &vao.second);
	}

	meshes.clear();
	shaders.clear();
	texture2ds.clear();
}
	
// initialize all resources
void Resource::Initialize() {
	// Meshes
	LoadMeshes("");

	// shaders
	BuildShader("SHADER", "res/Shaders/RenderVertex.shader", "res/Shaders/RenderFrag.shader");
	BuildShader("SKYBOX", "res/Shaders/SkyboxVertex.shader", "res/Shaders/SkyboxFrag.shader");

	// textures	
	AddTex2D("container0", LoadTex2D("res/Textures/container0.jpg"));
	AddTex2D("container1", LoadTex2D("res/Textures/container1.png"));
	AddTex2D("container2", LoadTex2D("res/Textures/container2.png"));

	// cubemaps
	std::vector<const GLchar*> facepaths;
	facepaths.push_back("res/Textures/skybox/right.jpg");
	facepaths.push_back("res/Textures/skybox/left.jpg");
	facepaths.push_back("res/Textures/skybox/top.jpg");
	facepaths.push_back("res/Textures/skybox/bottom.jpg");
	facepaths.push_back("res/Textures/skybox/back.jpg");
	facepaths.push_back("res/Textures/skybox/front.jpg");

	LoadCubemap("skybox", facepaths);
}

// return handle to texture 2D 
const GLuint Resource::GetTex2D(const char* name) {	
	assert(texture2ds.find(name) != texture2ds.end() && "Undefined TextureID");
	return texture2ds[name];
}

// load texture2D
GLuint Resource::LoadTex2D(const char* filename) {
	int w, h = 0;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* buffer = stbi_load(filename, &w, &h, nullptr, 4);

	GLuint textureID;
	GLCALL(glGenTextures(1, &textureID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, textureID));
	// set parameter
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// set data to gpu
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
	GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
	glBindTexture(GL_TEXTURE_2D, 0);

	// free buffer
	stbi_image_free(buffer);
	return textureID;
}

// load texture2D
void Resource::AddTex2D(const char* name, const GLuint texID) {
	assert(texture2ds.find(name) == texture2ds.end() && "Trying to add same texture twice!");
	texture2ds.insert({ name, texID });
}

// returns cubemap id
const GLuint Resource::GetCubemap(const char* name) {
	assert(cubemaps.find(name) != cubemaps.end() && "Undefined Cubemap ID");
	return cubemaps[name];
}

// load cube map from file
void Resource::LoadCubemap(const char* name, std:: vector<const char*> faces) {
	GLuint textureID = 0;
	stbi_set_flip_vertically_on_load(0);
	GLCALL(glGenTextures(1, &textureID));
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);	

	for (GLuint i = 0; i < faces.size(); i++) {
		int w, h = 0;
		unsigned char* buffer = stbi_load(faces[i], &w, &h, nullptr, 4);
		GLCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
		stbi_image_free(buffer);
	}

	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	cubemaps.insert({ name, textureID });
}

// return vao handle
const GLuint Resource::GetMesh(const char* name) {
	assert(meshes.find(name) != meshes.end() && "Undefined VAO ID");
	return meshes[name];
}

// initialize meshes
void Resource::LoadMeshes(const GLchar* filename) {

	GLfloat cube[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	GLfloat skybox[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	
	// textured cube vao
	GLuint cubeVAO, cubeVBO;
	GLCALL(glGenVertexArrays(1, &cubeVAO));
	GLCALL(glGenBuffers(1, &cubeVBO));
	GLCALL(glBindVertexArray(cubeVAO));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, cubeVBO));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW));
	GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0));
	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))));
	GLCALL(glEnableVertexAttribArray(1));
	GLCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat))));
	GLCALL(glEnableVertexAttribArray(2));
	GLCALL(glBindVertexArray(0));

	// skybox vao
	GLuint skyboxVAO, skyboxVBO;
	GLCALL(glGenVertexArrays(1, &skyboxVAO));
	GLCALL(glGenBuffers(1, &skyboxVBO));
	GLCALL(glBindVertexArray(skyboxVAO));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(skybox), skybox, GL_STATIC_DRAW));
	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0));
	GLCALL(glBindVertexArray(0));

	meshes["CUBE"] = cubeVAO;
	meshes["SKYBOX"] = skyboxVAO;
}

// get handle shader program
const GLuint Resource::GetShader(const char* name) {
	assert(shaders.find(name) != shaders.end() && "Undefined Program ID");
	return shaders[name];
}

// load shader source code
const std::string Resource::LoadShader(const char* filename) {

	std::ifstream shaderFileStream;
	shaderFileStream.exceptions(std::ifstream::failbit | std::fstream::badbit);

	try {
		shaderFileStream.open(filename);
		std::stringstream stringStream;
		stringStream << shaderFileStream.rdbuf();
		shaderFileStream.close();
		return stringStream.str();;
	}
	catch (const std::exception&) {
		std::cerr << "\nERROR::SHADER::SOURCE FILE NOT SUCCESSFULLY LOADED!\n" << filename << std::endl;
	}

	return nullptr;
}

// compile shader source code
const GLuint Resource::ComplieShader(GLenum type, const GLchar* src) {
	GLint status;
	GLchar info_log[512];
	GLCALL(const GLuint shaderID = glCreateShader(type));
	GLCALL(glShaderSource(shaderID, 1, &src, NULL));
	GLCALL(glCompileShader(shaderID));

	GLCALL(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status));

	if (!status) {
		GLCALL(glGetShaderInfoLog(shaderID, 512, NULL, info_log));
		std::cerr << "SHADER::COMPILATION FAILED: " << info_log << std::endl;
	}
	return shaderID;
}

// load, compile and link shaders
void Resource::BuildShader(const char* name, const char* vertex, const char* fragment) {

	assert(shaders.find(name) == shaders.end() && "Shader allready build!");
	const GLuint vertexShader = ComplieShader(GL_VERTEX_SHADER, LoadShader(vertex).c_str());
	const GLuint fragmentShader = ComplieShader(GL_FRAGMENT_SHADER, LoadShader(fragment).c_str());

	GLuint program = 0;
	GLCALL(program = glCreateProgram());
	GLCALL(glAttachShader(program, vertexShader));
	GLCALL(glAttachShader(program, fragmentShader));
	GLCALL(glLinkProgram(program));

	GLint status;
	GLchar info_log[512];
	GLCALL(glGetProgramiv(program, GL_LINK_STATUS, &status));

	if (!status) {
		GLCALL(glGetProgramInfoLog(program, 512, NULL, info_log));
		std::cerr << "SHADER::LINKING FAILED: " << info_log << std::endl;
	}

	GLCALL(glDeleteShader(vertexShader));
	GLCALL(glDeleteShader(fragmentShader));
	shaders.insert({ name, program });
}

