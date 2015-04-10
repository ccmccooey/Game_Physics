// Flat Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible

#version 400

in vec4 vVertex;
in vec2 vUV;

out vec4 vFragColor;       // Fragment color to rasterize


void main(void)
{

	vFragColor = vec4(1, 1, 1, 1) * ((vUV[0] + vUV[1]) * 0.5);
}