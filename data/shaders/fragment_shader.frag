#version 330 core

uniform sampler2D atlasSampler;

in vec2 fragmentUV;

out vec4 outColor;

void main()
{
	outColor = texture(atlasSampler, fragmentUV);
}