#include "stdafx.h"
#include "GLProgram.h"

#include <vector>
#include <string>
#include <fstream>

GLProgram::GLProgram()
{
    shaders.clear();
}


void GLProgram::addShader(const char* path, GLenum shaderType)
{
    shaders.push_back({path, shaderType});
}
void GLProgram::compileShaders()
{
    for (Shader &shader : shaders)
    {
        //read source from file
        std::string shaderCode;
        std::ifstream shaderStream(shader.path, std::ios::in);
        if(shaderStream.is_open()){
            std::string Line = "";
            while(getline(shaderStream, Line))
                shaderCode += "\n" + Line;
            shaderStream.close();
        }else{
            printf("Can't open shader source file: %s\n", shader.path);
            getchar();
            return; // change to fatal error
        }

        //create the shader
        shader.ID = glCreateShader(shader.type);

        // Compile Shader
        char const * SourcePointer = shaderCode.c_str();
        glShaderSource(shader.ID, 1, &SourcePointer, NULL);
        glCompileShader(shader.ID);

        // Check Shader
        //for openGL error handling
        GLint Result = GL_FALSE;
        int InfoLogLength;

        glGetShaderiv(shader.ID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(shader.ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0)
        {
            std::vector<char> ShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(shader.ID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
            printf("%s\n", &ShaderErrorMessage[0]);
        }
    }
}
void GLProgram::linkShaders()
{
	//create program
	ID = glCreateProgram();

    //link program
    for (Shader &shader : shaders)
        glAttachShader(ID, shader.ID);

	glLinkProgram(ID);

	// Check the program
	GLint Result = GL_FALSE;
    int InfoLogLength;
	glGetProgramiv(ID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	//detach and delete shaders
	for (Shader &shader : shaders)
    {
        glDetachShader(ID, shader.ID);
        glDeleteShader(shader.ID);
    }

}
void GLProgram::compile()
{
    compileShaders();
    linkShaders();
}
void GLProgram::use()
{
    glUseProgram(ID);
}
void GLProgram::disable()
{
    glUseProgram(0);
}
void GLProgram::destroy() //make a function destroy(), do not use destructor!!
{
	glDeleteProgram(ID);
}
GLint GLProgram::setUniformLocation(const char* name)
{
    return glGetUniformLocation(ID, name);
}
