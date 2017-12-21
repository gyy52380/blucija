#pragma once

#include <glm.hpp>

#include "typedef.h"
#include "GLProgram.h"
#include "Vertex.h"

namespace gl
{

texture_ID create_texture(const char* texture_path);
void add_batch(std::vector<glm::vec2> trans_vec, GLuint textureID);
void init(uint32 screen_width, uint32 screen_height);
void cleanup();
void clear_screen();
void draw(SDL_Window* window_handle);
void draw_quads(SDL_Window *window_to_draw, texture_ID texID, glm::vec2 *array_ptr, uint32 n_elements);

}