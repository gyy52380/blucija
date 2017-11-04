#include "stdafx.h"
#include "EntityManager.h"

#include "EntityType_defs.h"

#include <iostream> //for errors, change with errror function later

EntityManager::EntityManager(const int MAX_ENTITIES) : MAX_ENTITIES(MAX_ENTITIES)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		instances.push_back(new Entity());
		instances.back()->type = type(UNKNOWN_TYPE);
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
		if (entity_ptr->type->type != UNKNOWN_TYPE)
		{
			*entity_ptr = Entity(entity_type_to_init);
			return entity_ptr;
		}
	}

	//no more space to init entity
	std::cout << "Entity Manager can't init another Entity, object pool out of space. MAX_ENTITIES = " << MAX_ENTITIES << std::endl;
	return nullptr;
}

void EntityManager::remove_entity(Entity *entity_to_kill)
{
	entity_to_kill->type = type(UNKNOWN_TYPE);
}

void EntityManager::update()
{
}

void EntityManager::draw()
{
}

