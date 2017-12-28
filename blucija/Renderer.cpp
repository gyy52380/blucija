#include "stdafx.h"
#include "Renderer.h"


#include <vector>
#include <glm.hpp>

#include "RenderState.h"
#include "Texture.h"
#include "EntityType.h"

namespace renderer
{


RenderState draw_state(Texture::texture_count);
RenderState future_state(Texture::texture_count);


void render(SDL_Window *the_window, float interpolation_param)
{
	draw_state.lerp(&future_state, interpolation_param);
	draw_state.draw(the_window);
	future_state.clear();
}

void add_element(GLuint textureID, glm::vec2 position, float scale, bool orientation_r)
{
	future_state.add_element(textureID, position, scale, orientation_r);
}

void start_new_frame()
{
	future_state.clear();
}


}