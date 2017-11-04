#pragma once

#include <vec2.hpp>
#include <vector>

#include "EntityType.h"

class Entity
{
public:
	
	//type
	EntityType *type;

	//graphics
	float scale;
	bool orientation_r;

	//logic
	glm::vec2 pos;
	int health;
	int attack;
	float velocity;

	Entity(EntityType *type);
	Entity();
	~Entity();

	void move_to(float x, float y);
	void move_by(float x, float y);
};

