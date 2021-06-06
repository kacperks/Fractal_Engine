#version 330 core

out vec4 FragColor;
in vec3 TexCoords;

#define MAX_DIR_LIGHTS 10

struct DirectLight {
    vec3 Color;
    vec3 Position;
    vec3 Direction;
    float Intensity;
};

uniform samplerCube CubeMap;
uniform int directLightCount;
uniform DirectLight directLights[MAX_DIR_LIGHTS];

vec3 ProcessLight(vec3 L, vec3 color, float I) {
    float distance = length(L);
    float attenuation = I / (distance * distance);
    vec3 radiance = color * attenuation;
    return radiance;
}

void main() {

    vec3 result = vec3(0.0001f);
    int count = (directLightCount > MAX_DIR_LIGHTS) ? MAX_DIR_LIGHTS : directLightCount;

    for (int i = 0; i < count; i++) {
        vec3 LightDirection = normalize(directLights[i].Direction);
        result += ProcessLight(LightDirection, directLights[i].Color, directLights[i].Intensity);
    }

    FragColor = texture(CubeMap, TexCoords) * vec4(result, 1.0);
}

