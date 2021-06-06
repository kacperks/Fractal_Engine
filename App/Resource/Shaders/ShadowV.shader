#version 330 core
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out VS_DATA {
	vec3 Normal;
	vec3 FragPos;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
} vs_data;

uniform mat4 View;
uniform mat4 Model;
uniform mat4 Projection;
uniform mat4 LightViewProj;

void main() {
	vs_data.TexCoords = aTexCoords;
	vs_data.FragPos = vec3(Model * vec4(aPos, 1.0));
	vs_data.Normal = transpose(inverse(mat3(Model))) * aNormal;
	gl_Position = Projection * View * Model * vec4(aPos, 1.0f);
	vs_data.FragPosLightSpace = LightViewProj * vec4(vs_data.FragPos, 1.0);
}
