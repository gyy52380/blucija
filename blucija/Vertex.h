#pragma once

#include <vec2.hpp>
#include <vec4.hpp>

#include "typedef.h"

struct Vertex
{
	glm::vec2 pos;
	glm::vec2 uv;
	glm::vec4 color;
	uint16 depth;
};