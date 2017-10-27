#pragma once

#include "stdafx.h"

#include <vector>
#include <string>

struct Shader
{
	const char* path;
	GLenum type;
	GLuint ID;
};

class GLProgram
{
    public:
        GLuint ID = 0;

        GLProgram();

        void addShader(const char* path, GLenum shaderType);
        void compileShaders();
        void linkShaders();
        void compile();
		void destroy();
        void use();
        void disable();
        GLint setUniformLocation(const char* name);

    private:
        std::vector<Shader> shaders;
};