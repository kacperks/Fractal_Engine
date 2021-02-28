#version 330 core

out vec4 FragColor;

in vec3 TextureCoords;

uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform samplerCube CubeMap;

void main() {
    vec4 light = vec4(Ambient + Diffuse + Specular, 1.0f);
    FragColor = texture(CubeMap, TextureCoords) * light;;
}

