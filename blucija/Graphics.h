#pragma once

#include <glm.hpp>

#include "GLProgram.h"
#include "Vertex.h"

namespace gl
{

void init_camera(float left, float right, float bottom, float top);
GLuint create_texture(const char* texture_path);
void create_base_quad(float quad_width, float quad_height);
void update_translation_buffer_data(std::vector<Vertex> const &vertices);
void init(uint32 screen_width, uint32 screen_height);
void cleanup();
void clear_screen();
void draw(SDL_Window* window_handle);

}