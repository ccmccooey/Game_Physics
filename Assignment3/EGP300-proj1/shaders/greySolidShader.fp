// Flat Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible

#version 400

in vec4 vVertex;

out vec4 vFragColor;       // Fragment color to rasterize


void main(void)
{
	vFragColor = vec4(0.5, 0.5, 0.5, 1.0);
}