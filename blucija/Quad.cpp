#include "Quad.h"

using namespace glm;

Quad::~Quad() {}

void Quad::init(vec2 bottomLeftPos, float width, float height)
{
	this->width = width;
	this->height = height;
	
	moveTo(bottomLeftPos);
}

void Quad::setUV(vec2 bottomLeftUV, float texture_pixel_w, float texture_pixel_h)
{
	if (!texture_pixel_w) texture_pixel_w = width;
	if (!texture_pixel_h) texture_pixel_h = height;

	static const float atlas_pixel_w = 7.0f * 16.0f;
	static const float atlas_pixel_h = 16.0f;

	bottomLeft.uv = vec2((bottomLeftUV.x) / atlas_pixel_w,
		(bottomLeftUV.y) / atlas_pixel_h);
	bottomRight.uv = vec2((bottomLeftUV.x + texture_pixel_w) / atlas_pixel_w,
		(bottomLeftUV.y) / atlas_pixel_h);
	topLeft.uv = vec2((bottomLeftUV.x) / atlas_pixel_w,
		(bottomLeftUV.y + texture_pixel_h) / atlas_pixel_h);
	topRight.uv = vec2((bottomLeftUV.x + texture_pixel_w) / atlas_pixel_w,
		(bottomLeftUV.y + texture_pixel_h) / atlas_pixel_h);
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



