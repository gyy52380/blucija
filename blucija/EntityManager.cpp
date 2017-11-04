#include "stdafx.h"
#include "EntityManager.h"

#include <iostream> //for errors, change with errror function later

EntityManager::EntityManager(const int MAX_ENTITIES) : MAX_ENTITIES(MAX_ENTITIES)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		instances.push_back(new Entity());
		instances.back()->is_alive = false;
	}
}

EntityManager::~EntityManager()
{
	for (auto &entity_ptr : instances)
		delete entity_ptr;

	instances.clear();
}


Entity* EntityManager::add_entity(EntityType *entity_type_to_init) //this can be optimised some day
{
	for (auto &entity_ptr : instances)
	{
		if (entity_ptr->is_alive == false)
		{
			*entity_ptr = Entity(entity_type_to_init);
			entity_ptr->is_alive = true;

			return entity_ptr;
		}
	}

	//no more space to init entity
	std::cout << "Entity Manager can't init another Entity, object pool out of space. MAX_ENTITIES = " << MAX_ENTITIES << std::endl;
	return nullptr;
}

void EntityManager::remove_entity(Entity *entity_to_kill)
{
	entity_to_kill->is_alive = false;
	//define types entity_to_kill->type = unknown_type;
}

