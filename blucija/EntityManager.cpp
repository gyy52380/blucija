#include "stdafx.h"
#include "EntityManager.h"

#include <vec2.hpp>
#include <iostream> //for errors, change with errror function later

#include "EntityType.h"
#include "Graphics.h"
#include "InputManager.h"

#define _player instances[0]


EntityManager::EntityManager(const int MAX_ENTITIES) :
	MAX_ENTITIES(MAX_ENTITIES),
	instances(MAX_ENTITIES)
{
	for (auto &entity_to_allocate : instances)
		entity_to_allocate = new Entity(type(TYPE_UNKNOWN));

	_player->type = type(TYPE_PLAYER);
}

EntityManager::~EntityManager()
{
	for (auto &entity_to_free : instances)
		delete entity_to_free;
}


Entity* EntityManager::add_entity(ent_type entity_type_to_init) //this can be optimised some day
{
	if (entity_type_to_init == TYPE_PLAYER)
		return _player;

	for (auto &entity : instances)
	{
		if (entity->type == TYPE_UNKNOWN)
		{
			*entity = Entity(type(entity_type_to_init));
			return entity;
		}
	}

	//no more space to init entity
	std::cout << "Entity Manager can't init another Entity, object pool out of space. MAX_ENTITIES = " << MAX_ENTITIES << std::endl;
	return nullptr;
}

void EntityManager::remove_entity(Entity *entity_to_kill)
{
	entity_to_kill->type = type(TYPE_UNKNOWN); //just change the type ptr. all other params stay as before the entity "died"
}

void EntityManager::update()
{
	get_input();
	_player->move_by(_player->velocity.x, _player->velocity.y);
}

void EntityManager::get_input()
{
	if		(io::is_key_held(K_A)) _player->velocity.x	= -0.0001f;
	else if (io::is_key_held(K_D)) _player->velocity.x	= 0.0001f;
	else	_player->velocity.x = 0;
}

void EntityManager::draw()
{
	std::sort(instances.begin(), instances.end(),
		[](const Entity* entity1, const Entity* entity2) -> bool 
		{ return entity1->type->asset.get_textureID() < entity2->type->asset.get_textureID(); });

	std::vector<glm::vec2> translation_vec;
	GLuint bound_texture = instances[0]->type->asset.get_textureID();

	for (Entity *entity : instances)
	{
		if (entity->type == TYPE_UNKNOWN)
			continue;
		if (bound_texture == type(TYPE_UNKNOWN)->asset.get_textureID())
			bound_texture = entity->type->asset.get_textureID(); //first texture other than 0

		if (entity->type->asset.get_textureID() == bound_texture)
		{
			translation_vec.push_back(entity->pos);
		}
		else
		{
			gl::add_batch(translation_vec, bound_texture);
			translation_vec.clear();
			translation_vec.push_back(entity->pos);
			bound_texture = entity->type->asset.get_textureID();
		}
	}
	gl::add_batch(translation_vec, bound_texture);
}

