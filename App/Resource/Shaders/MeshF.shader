#version 330 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

out vec4 FragColor;

#define PI 3.14159265359
#define MAX_LIGHTS 128

struct Material {
    float Ao;
    vec3 Albedo;
    float Metallic;
    float Roughness;
};

struct PointLight {
    vec3 Color;
    vec3 Position;
    float Intensity;
};

struct DirectLight {
    vec3 Color;
    vec3 Position;
    vec3 Direction;
    float Intensity;
};

struct SpotLight {
    vec3 Color;
    vec3 Position;
    vec3 Direction;
    float ICutOff;
    float OCutOff;
    float Intensity;
};

// uniforms
uniform sampler2D AoMap;
uniform sampler2D AlbedoMap;
uniform sampler2D NormalMap;
uniform sampler2D MetallicMap;
uniform sampler2D RoughnessMap;

uniform vec3 CameraPos;
uniform Material material;

uniform int spotLightCount;
uniform SpotLight spotLights[MAX_LIGHTS];

uniform int pointLightCount;
uniform PointLight pointLights[MAX_LIGHTS];

uniform int directLightCount;
uniform DirectLight directLights[MAX_LIGHTS];

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    return nom / max(denom, 0.001); // prevent divide by zero for roughness=0.0 and NdotH=1.0
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 ProcessLight(vec3 N, vec3 V, vec3 Ld, vec3 color, vec3 F0, float I, float roughness, float metallic, vec3 albedo) {

    vec3 L = normalize(Ld);
    vec3 H = normalize(V + L);
    float distance = length(Ld);
    float attenuation = I / (distance * distance);
    vec3 radiance = color * attenuation;

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 F = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

    vec3 nominator = NDF * G * F;
    float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
    vec3 specular = nominator / max(denominator, 0.001);

    vec3 KS = F;
    vec3 KD = vec3(1.0) - KS;
    KD *= 1.0 - metallic;
    float NdotL = max(dot(N, L), 0.0);
    vec3 Lo = (KD * albedo / PI + specular) * radiance * NdotL;
    return Lo;
}

void main() {
    vec3 N = normalize(Normal);
    vec3 V = normalize(CameraPos - FragPosition);

    float ao = material.Ao + texture(AoMap, TexCoords).r;
    vec3 albedo = pow(material.Albedo, vec3(2.2)) + pow(vec3(texture(AlbedoMap, TexCoords)), vec3(5.2));
    float metallic = material.Metallic + texture(MetallicMap, TexCoords).r;
    float roughness = material.Roughness + texture(RoughnessMap, TexCoords).r;

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    vec3 Luminance = vec3(0.0);

    // Point lights
    int count = (pointLightCount > MAX_LIGHTS) ? MAX_LIGHTS : pointLightCount;
    for (int i = 0; i < count; i++) {
        PointLight light = pointLights[i];
        vec3 L = (light.Position - FragPosition);
        Luminance += ProcessLight(N, V, L, light.Color, F0, light.Intensity, roughness, metallic, albedo);
    }

    // Directional lights
    count = (directLightCount > MAX_LIGHTS) ? MAX_LIGHTS : directLightCount;
    for (int i = 0; i < count; i++) {
        DirectLight light = directLights[i];
        Luminance += ProcessLight(N, V, light.Direction, light.Color, F0, light.Intensity, roughness, metallic, albedo);
    }

    // ambient
    vec3 ambient = vec3(0.1f) * albedo * ao;

    vec3 color = ambient + Luminance;
    // HDR correction
    color = color / (color + vec3(1.0));
    // Gamma correction
    color = pow(color, vec3(1.0 / 3.0));

    FragColor = vec4(color, 1.0);
}