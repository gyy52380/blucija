#pragma once

#include <vector>
#include <vec2.hpp>

#include "typedef.h"

namespace gl
{


void add_batch(std::vector<glm::vec2> trans_vec, GLuint textureID);
void init(uint32 screen_width, uint32 screen_height);
void cleanup();
void clear_screen();
void draw(SDL_Window* window_handle);
void draw_quads(SDL_Window *window_to_draw, GLuint texID, glm::vec2 *array_ptr, uint32 n_elements);
void swap_screen_buffer(SDL_Window *window_to_swap);


}