#pragma once

#include <vector>

#include "Entity.h"

class EntityManager
{
public:

	const int MAX_ENTITIES;

	EntityManager(const int MAX_ENTITIES);
	~EntityManager();

	Entity* add_entity(EntityType  *entity_type_to_init);
	void remove_entity(Entity* entity_to_kill);

	void update();
	void draw();


	

private:
	std::vector<Entity*> instances;
};

