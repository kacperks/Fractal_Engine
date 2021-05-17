#pragma once

#ifndef FR_VERTEX
#define FR_VERTEX

struct Vertex {
	Vertex() = default;
	Vertex(float x, float y, float z): Position(glm::vec3(x, y, z)){}
	Vertex(glm::vec3 position): Position(position), Normal(0), TexCoords(0) { }
	Vertex(glm::vec3 position, glm::vec3 normal): Position(position), Normal(normal), TexCoords(0) { }
	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texcoord): Position(position), Normal(normal), TexCoords(texcoord) { }
	
	// position
	glm::vec3 Position = glm::vec3(0.0f);
	// normal
	glm::vec3 Normal = glm::vec3(0.0f);
	// coords
	glm::vec2 TexCoords = glm::vec2(0.0f);
};

#endif