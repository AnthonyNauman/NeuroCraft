#version 460
in vec3	vColor;
out vec4 frag_color;

void main() {
	frag_color = vec4(vColor, 1.0);
}