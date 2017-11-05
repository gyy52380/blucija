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

	Quad(float width, float height);
	Quad();
	~Quad();

	void setUV(glm::vec2 bottomLeftUV);
	void moveTo(glm::vec2 bottomLeftPos);
	void moveBy(glm::vec2 translationVec);
};

