#pragma once

#include <vec2.hpp>

#include "Quad.h"
#include "Texture.h"

enum EntityType
{
	PLAYER,
	ENEMY
};

class EntityBase
{
public:
	
	EntityType type;
	Texture *text;

	EntityBase();
	~EntityBase();
};

class Entity
{
public:

	glm::vec2 pos;

	Entity();
	~Entity();
};

