#type vertex
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 vp;
uniform mat4 model;

void main() {
  gl_Position = vp * model * vec4(aPos, 1.0);
}

#type fragment
#version 330 core
out vec4 FragCol;

void main() {
  FragCol = vec4(1.0);
}