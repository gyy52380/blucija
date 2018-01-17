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
	void change_entity_type(Entity *to_change, ent_type new_type);

	void update();
	void queue_for_rendering();

	void get_input();

	std::vector<Entity*> instances;
	
};


