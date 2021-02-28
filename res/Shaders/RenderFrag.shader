#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec3 FragPosition;
in vec2 TextureCoords;

#define MAX_LIGHT_COUNT 10

struct Light {
    int type;
	vec3 position;
    vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

    float linear;
	float constant;
	float quadratic;

    float innerCutOff;
    float outerCutOff;
};

struct Material {
    bool hasTexture;
    float shininess;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 CameraPosition;

uniform Material material;
uniform int lightSourceCount;
uniform Light[MAX_LIGHT_COUNT] lights;

// diffuse & specular textures
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

// for reflec and refrac
uniform sampler2D SceneTexture;
uniform samplerCube skyboxTexture;

vec3 ProcessLight(Light light, vec3 lightDir, float intensity);

void main() {
    vec3 color = vec3(0.0f);
    for (int i = 0; i < lightSourceCount; i++) {
        Light light = lights[i];
        vec3 lightDirection = normalize(light.position - FragPosition);

        if (light.type == 0) {
            color += ProcessLight(light, lightDirection, 1.0f);
            continue;
        }
        else if (light.type == 1) {
            color += ProcessLight(light, normalize(-light.direction), 1.0f);
            continue;
        }
        else if (light.type == 2) {
            float theta = dot(lightDirection, normalize(-light.direction));
            float epsilon = (light.innerCutOff - light.outerCutOff);
            float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
            color += ProcessLight(light, lightDirection, intensity);
            continue;
        }
    }

    float Ratio = 1.00 / 0.52;
    vec3 Incidence = normalize(Position - CameraPosition);

    // reflection, refraction
    vec3 Reflection = reflect(Incidence, normalize(Normal));
    vec3 Refraction = refract(Incidence, normalize(Normal), Ratio);

    vec4 reflectionColor = texture(skyboxTexture, Reflection);
    vec4 refractionColor = texture(skyboxTexture, Refraction);

    FragColor = vec4(color.xyz, 1.0f);
}

vec3 ProcessLight(Light light, vec3 lightDir, float intensity) {
    // diffuse factor
    vec3 norm = normalize(Normal);
    float diffuseFactor = max(dot(norm, lightDir), 0.0f);

    // specular factor
    vec3 reflectDirection = reflect(-lightDir, norm);
    vec3 viewDirection = normalize(CameraPosition - FragPosition);
    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);

    // light components vectors
    vec3 ambientLight, diffuseLight, specularLight;

    // with texture
    if (material.hasTexture == true) {
        ambientLight = light.ambient * vec3(texture(diffuseTexture, TextureCoords));
        diffuseLight = light.diffuse * vec3(texture(diffuseTexture, TextureCoords)) * diffuseFactor;
        specularLight = light.specular * vec3(texture(specularTexture, TextureCoords)) * specularFactor;
    }
    else {
        ambientLight = light.ambient * material.ambient;
        diffuseLight = light.diffuse * material.diffuse * diffuseFactor;
        specularLight = light.specular * material.specular * specularFactor;
    }

    // attenuation
    float distance = length(light.position - FragPosition);
    float attenuation = intensity / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // result
    vec3 result = (ambientLight + diffuseLight + specularLight) * attenuation;
    return result;
}
