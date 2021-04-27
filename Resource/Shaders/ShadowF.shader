#version 330 core

out vec4 FragColor;

in VS_DATA{
	vec3 Normal;
	vec3 FragPos;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
} vs_data;

uniform sampler2D ShadowMap;
uniform sampler2D DiffuseMap;

void main() {  

    gl_FragDepth = gl_FragCoord.z;
}