#version 330 core
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 View;
uniform mat4 Model;
uniform mat4 Projection;

void main() {
	TexCoords = aTexCoords;
	gl_Position = Projection * View * Model * vec4(aPos, 1.0f);
}
