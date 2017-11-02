#pragma once

#include <vec2.hpp>
#include <vector>

#include "E_type.h"

class Entity
{
public:
	
	//type
	E_type *type;

	//for the manager
	bool is_alive; //manager takes care of this

	//graphics
	float scale;
	bool orientation_r;

	//logic
	glm::vec2 pos;
	int health;
	int attack;
	float velocity;

	Entity(E_type *type);
	Entity();
	~Entity();

	void move_to(float x, float y);
	void move_by(float x, float y);
};

