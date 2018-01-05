#include "stdafx.h"
#include "Renderer.h"

#include <vector>
#include <glm.hpp>

#include "RenderState.h"
#include "Texture.h"
#include "EntityType.h"

namespace renderer
{

//very inefficient

RenderState draw_state(TYPE_COUNT); //this is very limited currently, should be dynamic number of textures? (Texture::texture_count)
RenderState future_state(TYPE_COUNT);


void render(SDL_Window *the_window, float interpolation_param)
{
	draw_state.lerp(&future_state, interpolation_param); //problem
	draw_state.draw(the_window);
}

void add_element(GLuint textureID, glm::vec2 position, float scale, bool orientation_r) //ERROR: draw and future do not have same amount of elements in vectors
{
	future_state.add_element(textureID, position, scale, orientation_r);
}

void start_new_frame()
{
	future_state.clear();
}


}