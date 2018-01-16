#pragma once

//#include <SDL.h> 
//#include <glew.h>
#include <vec2.hpp>

#include "typedef.h"

#include "RenderState.h"

namespace renderer
{


void render(SDL_Window *the_window, float interpolation_param);
void add_element(GLuint textureID, glm::vec2 position, float scale = 1.0f, bool orientation_r = true);
void start_new_frame(uint32 entity_count);


}