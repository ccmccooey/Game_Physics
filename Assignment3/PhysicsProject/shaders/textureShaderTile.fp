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
	vec2 v = vUV * 16.0;
	v[0] = fract(v[0]);
	v[1] = fract(v[1]);

	vFragColor = texture(tex, v);
}