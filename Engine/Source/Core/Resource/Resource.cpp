#include "pch.h"
#include "Resource.h"
//#include "Vendor/STB/stb_image.h"

namespace fr {
	RsrcManager::RsrcManager(){}

	RsrcManager::~RsrcManager(){

		for (auto texture : texture2ds) {
			GLCALL(glDeleteTextures(1, &texture.second));
		}

		// destroy all shaders
		for (auto program : shaders) {
			GLCALL(glDeleteProgram(program.second));
		}

		shaders.clear();
		texture2ds.clear();
	}

	void RsrcManager::Initialize() {
		INFO("Loading Resources...");
		// meshes
		LoadMeshes();

		// shaders
		CreateProgram("SPRITE", "SpriteV.shader", "SpriteF.shader");
		CreateProgram("SHADOW", "ShadowV.shader", "ShadowF.shader");
		CreateProgram("SKYBOX", "SkyboxV.shader", "SkyboxF.shader");
		CreateProgram("MESH", "MeshV.shader", "MeshF.shader");
		CreateProgram("GRID", "GridV.shader", "GridF.shader");

		// textures
		AddTex2D("light", LoadTex2D("Resource/Textures/light.png"));
		AddTex2D("camera", LoadTex2D("Resource/Textures/camera.png"));

		LoadModel("Sphere", "Resource/Models/Sphere.obj");

		// skybox cubemap
		std::vector<std::string> facepaths;
		facepaths.push_back("Resource/Textures/skybox/right.png");
		facepaths.push_back("Resource/Textures/skybox/left.png");
		facepaths.push_back("Resource/Textures/skybox/top.png");
		facepaths.push_back("Resource/Textures/skybox/bottom.png");
		facepaths.push_back("Resource/Textures/skybox/back.png");
		facepaths.push_back("Resource/Textures/skybox/front.png");
		LoadCubeMap("SKYBOX", facepaths);

		INFO("Resources Loaded!");
	}

	// texture 2d
	const GLuint RsrcManager::LoadTex2D(std::string filename) {
		int w, h = 0;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* buffer = stbi_load(filename.c_str(), &w, &h, nullptr, 4);

		GLuint textureID;
		GLCALL(glGenTextures(1, &textureID));
		GLCALL(glBindTexture(GL_TEXTURE_2D, textureID));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
		GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(buffer);
		return textureID;
	}

	void RsrcManager::AddTex2D(std::string name, const GLuint texID) {
		assert(texture2ds.find(name) == texture2ds.end() && "Trying to add same texture twice!");
		texture2ds.insert({ name, texID });

		RsrcManager::ActiveTxTs++;
	}

	// cubemap
	void RsrcManager::LoadCubeMap(std::string name, std::vector<std::string> faces) {
		GLuint textureID = 0;
		stbi_set_flip_vertically_on_load(0);
		GLCALL(glGenTextures(1, &textureID));
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		for (GLuint i = 0; i < faces.size(); i++) {
			int w, h = 0;
			unsigned char* buffer = stbi_load(faces[i].c_str(), &w, &h, nullptr, 4);
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

	void RsrcManager::LoadMeshes() {
		static Vertex cubeVertices[] = {
		// positions					       // normals					 // texture coords
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)),

		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f),   glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),   glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f)),

		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),   glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),   glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)),

		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f),   glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 0.0f)),

		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f),   glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f),   glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)),

		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),   glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 1.0f)),
	};
		CreateSphere();
		meshes.insert({ "CUBE", GLMesh(cubeVertices, sizeof(cubeVertices)) });
	}

	void RsrcManager::CreateSphere(GLuint X_SEGMENTS, GLuint Y_SEGMENTS) {

		std::vector<GLuint> indices;
		std::vector<Vertex> vertices;
		const float PI = 3.14159265359;

		for (unsigned int y = 0; y <= Y_SEGMENTS; ++y) {
			for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
				float xSegment = (float)x / (float)X_SEGMENTS;
				float ySegment = (float)y / (float)Y_SEGMENTS;
				float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
				float yPos = std::cos(ySegment * PI);
				float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

				Vertex vertex(glm::vec3(xPos, yPos, zPos), glm::vec3(xPos, yPos, zPos), glm::vec2(xSegment, ySegment));
				vertices.push_back(vertex);
			}
		}

		bool oddRow = false;		
		for (unsigned int y = 0; y < Y_SEGMENTS; ++y) {
			if (!oddRow) { // even rows: y == 0, y == 2; and so on
				for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
					indices.push_back(y * (X_SEGMENTS + 1) + x);
					indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				}
			}
			else {
				for (int x = X_SEGMENTS; x >= 0; --x) {
					indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
					indices.push_back(y * (X_SEGMENTS + 1) + x);
				}
			}
			oddRow = !oddRow;
		}

		meshes.insert({ "SPHERE", GLMesh(vertices.data(), vertices.size(), indices.data(), indices.size()) });
	}
	void RsrcManager::LoadModel(std::string name, std::string filename) {
		models.insert({ name, std::make_shared<Model3D>(filename) });
	}

	// shaders
	const GLuint RsrcManager::Program(std::string name) {
		assert(shaders.find(name) != shaders.end() && "Program out of range");
		return shaders[name];
	}

	std::string  RsrcManager::LoadShaderSource(std::string filename) {
		std::ifstream shaderFileStream;
		shaderFileStream.exceptions(std::ifstream::failbit | std::fstream::badbit);

		try {
			shaderFileStream.open(filename);
			std::stringstream stringStream;
			stringStream << shaderFileStream.rdbuf();
			shaderFileStream.close();
			return stringStream.str();
		}
		catch (const std::exception&) {
			std::cerr << termcolor::red << "Shader Source not Loaded! " << termcolor::white << filename << std::endl;
		}
		return std::string();
	}

	const GLuint  RsrcManager::ComplieShaderSource(GLenum type, const GLchar* src) {
		GLint status;
		GLchar info_log[512];
		GLCALL(const GLuint shaderID = glCreateShader(type));
		GLCALL(glShaderSource(shaderID, 1, &src, nullptr));
		GLCALL(glCompileShader(shaderID));

		GLCALL(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status));
		if (!status) {
			GLCALL(glGetShaderInfoLog(shaderID, 512, nullptr, info_log));
			std::cerr << termcolor::red << " Shader Compilation Failed! " << termcolor::white << info_log << "\n" << src << std::endl;
		}
		return shaderID;
	}

	void RsrcManager::CreateProgram(std::string name, std::string vtxFile, std::string fragFile) {
		assert(shaders.find(name) == shaders.end() && "ShaderID allready used!");
		const GLuint vertexShader = ComplieShaderSource(GL_VERTEX_SHADER, LoadShaderSource(SHADERS_PATH + vtxFile).c_str());
		const GLuint fragmentShader = ComplieShaderSource(GL_FRAGMENT_SHADER, LoadShaderSource(SHADERS_PATH + fragFile).c_str());

		GLuint program = 0;
		GLCALL(program = glCreateProgram());
		GLCALL(glAttachShader(program, vertexShader));
		GLCALL(glAttachShader(program, fragmentShader));
		GLCALL(glLinkProgram(program));

		GLint status;
		GLchar info_log[512];
		GLCALL(glGetProgramiv(program, GL_LINK_STATUS, &status));

		if (!status) {
			GLCALL(glGetProgramInfoLog(program, 512, nullptr, info_log));
			std::cerr << termcolor::red << " Shader Linking Failed! " << termcolor::white << info_log << std::endl;
		}

		GLCALL(glDeleteShader(vertexShader));
		GLCALL(glDeleteShader(fragmentShader));
		shaders.insert({ name, program });
	}
}
