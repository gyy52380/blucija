#include "stdafx.h"
#include "EntityManager.h"

#include <vec2.hpp>
#include <iostream> //for errors, change with errror function later

#include "EntityType.h"
#include "Graphics.h"
#include "InputManager.h"
#include "typedef.h"
#include "Texture.h"
#include "Renderer.h"

#define player_ instances[0]


EntityManager::EntityManager(const int MAX_ENTITIES) :
	MAX_ENTITIES(MAX_ENTITIES),
	instances(MAX_ENTITIES)
{
	for (auto &entity_to_allocate : instances)
		entity_to_allocate = new Entity(type(TYPE_UNKNOWN));

	*player_ = Entity(type(TYPE_PLAYER));
}

EntityManager::~EntityManager()
{
	for (auto &entity_to_free : instances)
		delete entity_to_free;
}


Entity* EntityManager::add_entity(ent_type entity_type_to_init) //this can be optimised some day
{
	if (entity_type_to_init == TYPE_PLAYER)
		return player_;

	for (auto &entity : instances)
	{
		if (entity->entity_type == TYPE_UNKNOWN)
		{
			*entity = Entity(type(entity_type_to_init)); //this maybe doesnt set entity.type
			return entity;
		}
	}

	//no more space to init entity
	std::cout << "Entity Manager can't init another Entity, object pool out of space. MAX_ENTITIES = " << MAX_ENTITIES << std::endl;
	return nullptr;
}

void EntityManager::remove_entity(Entity *entity_to_kill)
{
	entity_to_kill->entity_type = type(TYPE_UNKNOWN); //just change the type ptr. all other params stay as before the entity "died"
}

void EntityManager::update()
{
	get_input();
	player_->move_by(player_->velocity.x, player_->velocity.y);
}

void EntityManager::queue_for_rendering()
{
	renderer::start_new_frame(this->MAX_ENTITIES);

	for (auto &entity : instances)
		if (entity->type != TYPE_UNKNOWN)
			renderer::add_element(entity->entity_type->texture->gl_id, entity->pos, entity->scale, entity->orientation_r);
}

void EntityManager::get_input()
{
	if		(io::is_key_held(K_A)) player_->velocity.x	= -0.1f;
	else if (io::is_key_held(K_D)) player_->velocity.x	= 0.1f;
	else	player_->velocity.x = 0;
}

