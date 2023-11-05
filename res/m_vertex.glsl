#version 460
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 color;
uniform mat4 viewProjMat;
out vec3 vColor;

void main() {
	vColor = color;
	gl_Position = viewProjMat * vec4(vPos, 1.0);
}