#pragma once

#include "Vertex.h"
#include <vec2.hpp>

class Quad
{
public:
	Vertex bottomLeft;
	Vertex bottomRight;
	Vertex topLeft;
	Vertex topRight;

	float width = 1.0f;
	float height = 1.0f;

	void init(glm::vec2 bottomLeftPos, float width = 1.0f, float height = 1.0f);
	void setUV(glm::vec2 bottomLeftUV, float texture_pixel_w = 0, float texture_pixel_h = 0);
	void moveTo(glm::vec2 bottomLeftPos);
	void moveBy(glm::vec2 translationVec);

	~Quad();
};

