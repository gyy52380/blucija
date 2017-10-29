#version 330 core

uniform mat4 cameraMatrix;

layout(location = 0) in vec2 quadPos;
layout(location = 1) in vec2 quadUV;

layout(location = 2) in vec2 transPos;
layout(location = 3) in vec2 transUV;

out vec2 fragmentUV;

void main()
{
	gl_Position = cameraMatrix * vec4(quadPos + transPos, 0, 1);

	fragmentUV = vec2(quadUV.s + transUV.s, 1.0 - (quadUV.t+transUV.t));	
}