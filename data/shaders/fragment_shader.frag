#version 330 core

uniform sampler2D texture_sampler;

in vec2 frag_uv;

out vec4 out_color;

void main()
{
	out_color = texture(texture_sampler, frag_uv);
}