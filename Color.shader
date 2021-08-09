#type vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 vp;
uniform mat4 model;

out vec3 normal;
out vec3 fragPos;

void main() {
  gl_Position = vp * model * vec4(aPos, 1.0);
  fragPos = vec3(model * vec4(aPos, 1.0));
  normal = aNormal;
}

#type fragment
#version 330 core
out vec4 FragCol;
in vec3 normal;
in vec3 fragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

struct material_t {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

uniform material_t material;

void main() {
  float ambientStrength = 0.3;
  float specularStrength = 0.5;
  vec3 ambient = material.ambient * lightColor;

  vec3 norm = normalize(normal);
  vec3 lightDirection = normalize(lightPosition - fragPos);

  float diff   = max(dot(normal, lightDirection), 0.0);
  vec3 diffuse = (diff * material.diffuse) * lightColor;

  vec3 viewDirection = normalize(viewPosition - fragPos);
  vec3 reflectDirection = reflect(-lightDirection, normal);

  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
  vec3 specular = (material.specular * spec )* lightColor;

  vec3 result = (ambient + diffuse + specular) * objectColor;
  FragCol = vec4(result, 1.0);
}