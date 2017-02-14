#version 330 core

out vec4 color;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main() {
	// vec3 lightColor = vec3(1.0, 1.0, 1.0);

	float ambientStrength = 0.15f;
	vec3 ambientColor = ambientStrength * lightColor;
	
	vec3 lightDir = normalize(lightPos - FragPos);
	// float attenuationFactor = max(0.1,  + (distance(lightPos, FragPos) - 750)/2000);
	float diffuseStrength = max(dot(Normal, lightDir), 0);
	vec3 diffuseColor = diffuseStrength * lightColor;

	vec3 result = (ambientColor + diffuseColor)*objectColor;

	color = vec4(result, 1.0);
}
