#version 330 core

uniform mat4 camera_matrix;

layout(location = 0) in vec2 quad_pos;
layout(location = 1) in vec2 quad_uv;

layout(location = 2) in vec2 trans_pos;

out vec2 frag_uv;

void main()
{
	gl_Position = camera_matrix * vec4(quad_pos + trans_pos, 0, 1);

	frag_uv = vec2(quad_uv.s, 1.0f-quad_uv.t);
}