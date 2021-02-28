#version 330 core
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

out vec3 Normal;
out vec3 Position;
out vec3 FragPosition;
out vec2 TextureCoords;

uniform mat4 View;
uniform mat4 Model;
uniform mat4 Projection;

void main() {	
	TextureCoords = texCoords;
	Normal = mat3(transpose(inverse(Model))) * normal;	
	FragPosition = vec3(Model * vec4(position.xyz, 1.0f));

	vec4 Pos = Model * vec4(position.xyz, 1.0f);
	gl_Position = Projection * View * Pos;
	Position = Pos.xyz;
}
