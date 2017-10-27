#pragma once

#include <glm.hpp>

#include "GLProgram.h"
#include "Vertex.h"

namespace gl
{

extern GLProgram program;

//extern GLuint vao;
//extern GLuint vbo;
//extern GLuint instanceVBO;
//extern GLuint instanceIBO;
//
//extern uint32 n_of_elements_to_draw;

void initCamera(float left, float right, float bottom, float top);
void createTexture(const char* texture_path, uint8 texture_slot);
void createBaseQuad(float quad_width, float quad_height);
void updateTranslationBufferData(std::vector<Vertex> const &vertices);
void init(uint32 screen_width, uint32 screen_height);
void cleanup();
void clearScreen();
void draw(SDL_Window* window_handle);

}
