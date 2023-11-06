#version 460
layout(location = 0) in vec3 vPos;
//layout(location = 1) in vec3 color;
uniform mat4 translate;
out vec3 vColor;

void main() {
	vColor = vec3(1.0, 0.0, 0.0); //color;
	gl_Position = translate * vec4(vPos, 1.0);
}