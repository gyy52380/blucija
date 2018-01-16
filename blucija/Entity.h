#pragma once

#include <vec2.hpp>
#include <vector>

#include "EntityType.h"

#include "Shapes.h"

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
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	uint16 health;
	uint16 attack;

	////
	Circle hitbox;

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

