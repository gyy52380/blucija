#pragma once

#include <vec2.hpp>
#include <vector>

#include "EntityType.h"

class Entity
{
public:
	
	//type
	ent_type type;
	EntityType *entity_type;

	//graphics
	float scale;
	bool orientation_r;

	//logic
	glm::vec2 pos;
	int health;
	int attack;
	glm::vec2 velocity;

	Entity(EntityType *entity_type);
	Entity();
	~Entity();

	void move_to(float x, float y);
	void move_by(float x, float y);
};

class EntityInteractive : Entity
{
public:
	//logic
	int health;
	int attack;
	float velocity_x;
	float velocity_y;
};

