#version 330 core
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) in vec3 position;

out vec3 TextureCoords;

uniform mat4 View;
uniform mat4 Projection;

void main() {
	vec4 pos = Projection * View * vec4(position.xyz, 1.0f);
	TextureCoords = position;
	gl_Position = pos.xyww;
}
