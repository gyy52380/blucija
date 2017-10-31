#include "stdafx.h"
#include "Entity.h"


Entity::Entity() 
	: pos(glm::vec2(0, 0)), scale(1), textureID(0), orientation_r(true)
{
}

Entity::Entity(glm::vec2 pos, float scale, GLuint textureID, bool orientation_r)
	: pos(pos), scale(scale), textureID(textureID), orientation_r(orientation_r)
{
}


Entity::~Entity()
{
}

void Entity::move_to(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Entity::move_by(float x, float y)
{
	pos.x = pos.x + x;
	pos.y = pos.y + y;
}
