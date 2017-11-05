#include "Quad.h"

using namespace glm;

Quad::~Quad()
{
}

Quad::Quad(float width, float height) :
	width(width),
	height(height)
{
	moveTo(glm::vec2(0, 0));
}

Quad::Quad() :
	width(1.0f),
	height(1.0f)
{
	moveTo(glm::vec2(0, 0));
}

void Quad::setUV(vec2 bottomLeftUV) //meh kinda bad
{
	bottomLeft.uv = bottomLeftUV;
	bottomRight.uv = bottomLeftUV + glm::vec2(0, 1);
	topLeft.uv = bottomLeftUV + glm::vec2(1, 0);
	topRight.uv = bottomLeftUV + glm::vec2(1, 1);
}

void Quad::moveTo(vec2 bottomLeftPos)
{
	bottomLeft.pos = bottomLeftPos;
	bottomRight.pos = vec2(bottomLeft.pos.x + width, bottomLeft.pos.y);
	topLeft.pos = vec2(bottomLeft.pos.x, bottomLeft.pos.y + height);
	topRight.pos = vec2(bottomLeft.pos.x + width, bottomLeft.pos.y + height);
}

void Quad::moveBy(vec2 translationVec)
{
	moveTo(bottomLeft.pos + translationVec);
}



