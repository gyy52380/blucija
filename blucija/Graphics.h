#pragma once

#include <glm.hpp>

#include "typedef.h"
#include "GLProgram.h"
#include "Vertex.h"

namespace gl
{

textureID create_texture(const char* texture_path);
void add_batch(std::vector<glm::vec2> trans_vec, GLuint textureID);
void init(uint32 screen_width, uint32 screen_height);
void cleanup();
void clear_screen();
void draw(SDL_Window* window_handle);

}