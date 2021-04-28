#version 330 core
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 Normal;
out vec2 TexCoords;
out vec3 FragPosition;

uniform mat4 View;
uniform mat4 Model;
uniform mat4 Projection;

void main() {	
	TexCoords = aTexCoords;
	FragPosition = vec3(Model * vec4(aPos, 1.0));
	Normal = transpose(inverse(mat3(Model))) * aNormal;
	gl_Position = Projection * View * vec4(FragPosition, 1.0);
}
