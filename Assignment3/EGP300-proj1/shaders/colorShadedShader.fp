// Flat Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible

#version 400

in vec4 vVertex;
in vec2 vUV;

out vec4 vFragColor;       // Fragment color to rasterize


uniform vec4 color;

void main(void)
{
	vFragColor = color * ((vUV[0] + vUV[1]) * 0.5);
}