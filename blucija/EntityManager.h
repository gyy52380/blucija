#pragma once

#include <vector>
#include <array>

#include "Entity.h"

class EntityManager
{
public:
	const int MAX_ENTITIES;

	EntityManager(const int MAX_ENTITIES);
	~EntityManager();

	Entity* add_entity(ent_type entity_type_to_init);
	void remove_entity(Entity* entity_to_kill);

	void update();
	void draw();

	std::vector<Entity> instances;
};

