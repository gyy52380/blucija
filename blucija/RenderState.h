#pragma once

#include <vector>
//#include <SDL.h> 
//#include <glew.h>
#include <vec2.hpp>

#include "typedef.h"

namespace renderer
{


using std::vector;

class RenderState
{
public:

	const uint32 texture_count;

	//every index represents one texture id, where vectors of <type> are stored
	vector<glm::vec2>	*position_array;
	vector<float>		*scale_array;
	//vector<float>		*rotation_array;
	vector<bool>		*orientation_r_array;


	RenderState(const uint32 texture_count);
	~RenderState();

	void draw(SDL_Window* const window_handle) const;
	void lerp(RenderState* const future_state, const float param);
	void add_element(GLuint textureID, glm::vec2 position, float scale = 1.0f, bool orientation_r = true);
	void clear();
};


}