// Flat Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible

#version 400

in vec4 vVertex;
in vec2 vUV;

out vec4 vFragColor;       // Fragment color to rasterize


uniform sampler2D tex;

void main(void)
{
	vFragColor = texture(tex, vUV);
}