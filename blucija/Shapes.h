#pragma once
#include <vec2.hpp>

struct Shape {};

struct Circle : Shape
{
	glm::vec2 position;
	float radius = 1.0f;
};