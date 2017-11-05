#include "stdafx.h"
#include "EntityManager.h"

#include <vec2.hpp>
#include <iostream> //for errors, change with errror function later

#include "EntityType_defs.h"
#include "Graphics.h"


EntityManager::EntityManager(const int MAX_ENTITIES) : MAX_ENTITIES(MAX_ENTITIES)
{
	instances = std::vector<Entity>(MAX_ENTITIES, Entity(type(UNKNOWN_TYPE)));
}

EntityManager::~EntityManager()
{
}


Entity* EntityManager::add_entity(ent_type entity_type_to_init) //this can be optimised some day
{
	for (auto &entity : instances)
	{
		if (entity.type == UNKNOWN_TYPE)
		{
			entity = Entity(type(entity_type_to_init));
			return &entity;
		}
	}

	//no more space to init entity
	std::cout << "Entity Manager can't init another Entity, object pool out of space. MAX_ENTITIES = " << MAX_ENTITIES << std::endl;
	return nullptr;
}

void EntityManager::remove_entity(Entity *entity_to_kill)
{
	*entity_to_kill = Entity(type(UNKNOWN_TYPE)); //this makes a new default UNKNOWN_TYPE entity. maybe just change the type?
}

void EntityManager::update()
{
}

void EntityManager::draw()
{
	std::sort(instances.begin(), instances.end(),
		[](const Entity &entity1, const Entity &entity2) -> bool 
		{ return entity1.type->textureID < entity2.type->textureID; });

	std::vector<glm::vec2> translation_vec;
	GLuint bound_texture = instances[0].type->textureID;

	for (Entity &entity : instances)
	{
		if (entity.type == UNKNOWN_TYPE)
			continue;
		if (bound_texture == type(UNKNOWN_TYPE)->textureID)
			bound_texture = entity.type->textureID; //first texture other than 0

		if (entity.type->textureID == bound_texture)
		{
			translation_vec.push_back(entity.pos);
		}
		else
		{
			gl::add_batch(translation_vec, bound_texture);
			translation_vec.clear();
			translation_vec.push_back(entity.pos);
			bound_texture = entity.type->textureID;
		}
	}
	gl::add_batch(translation_vec, bound_texture);
}

