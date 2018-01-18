#include "stdafx.h"
#include "RenderState.h"

#include <vector>
#include <algorithm>
#include <glm.hpp>

#include "Graphics.h"
#include "typedef.h"
#include "Texture.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx\string_cast.hpp>
#include <iostream>

namespace renderer
{


RenderState::RenderState(const uint32 texture_count) : texture_count(texture_count)
{
	position_array		= new vector<glm::vec2>	[texture_count];
	scale_array			= new vector<float>		[texture_count];
	//rotation_array	= new vector<float>		[texture_count];
	orientation_r_array = new vector<bool>		[texture_count];
}

RenderState::~RenderState()
{
	delete[] position_array;
	delete[] scale_array;
	//delete[] rotation_array;
	delete[] orientation_r_array;
}

void RenderState::draw(SDL_Window * const window_handle) const //TODO  add for other things like scale, orientation...
{
	gl::clear_screen();

	for (uint32 texID = 1; texID < texture_count; ++texID) //no need to start from 0 == no texture
		gl::draw_quads(window_handle, texID, position_array[texID].data(), position_array[texID].size());

	gl::swap_screen_buffer(window_handle);
}

void RenderState::lerp(RenderState * const future_state, const float param) //carefull if any more elements appear in the next frame!!!
{
	//handle different amount of elements in each RenderState object

	for (uint32 texID = 1; texID < texture_count; ++texID) //no need to start from 0 == no texture
	{
		position_array[texID].resize(future_state->position_array[texID].size());
		for (uint32 i = 0; i < position_array[texID].size(); ++i)
			position_array[texID][i] = glm::mix(position_array[texID][i], future_state->position_array[texID][i], param);

		this->scale_array[texID].resize(future_state->scale_array[texID].size());
		for (uint32 i = 0; i < this->scale_array[texID].size(); ++i)
			this->scale_array[texID][i] = glm::mix(this->scale_array[texID][i], future_state->scale_array[texID][i], param);

		/*for (uint32 i = 0; i < this->rotation_array[texID].size(); ++i)
		this->rotation_array[texID][i] = glm::mix(this->rotation_array[texID][i], future_state->rotation_array[texID][i], param);*/

		this->orientation_r_array[texID] = future_state->orientation_r_array[texID]; //this might be a memory leak
	}
}

void RenderState::add_element(GLuint textureID, glm::vec2 position, float scale, bool orientation_r)
{
	this->position_array[textureID].push_back(position);
	this->scale_array[textureID].push_back(scale);
	this->orientation_r_array[textureID].push_back(orientation_r);
}

void RenderState::clear()
{
	for (uint32 i = 0; i < this->texture_count; ++i)
	{
		position_array[i].clear();
		scale_array[i].clear();
		//rotation_array[i].clear();
		orientation_r_array[i].clear();
	}
}


}