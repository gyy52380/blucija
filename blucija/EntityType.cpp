#include "stdafx.h"

#include "EntityType.h"
#include "Graphics.h"


EntityType::EntityType(ent_type type) :
	type(type)
{
}

EntityType::EntityType()
{
}

EntityType::~EntityType()
{
}

EntityType* EntityType::init_entity_types() //ONLY CALL AFTER OPENGL INIT
{
	assert(glewInit() == GLEW_OK && "OpenGL not initialized!");

	static EntityType types[TYPE_TOTAL];
	/////////////////////////////////////////////////////////
	//UNKNOWN_TYPE
	types[TYPE_UNKNOWN] = EntityType(TYPE_UNKNOWN);

	types[TYPE_UNKNOWN].asset.bind_textureID(0); //no texture
	types[TYPE_UNKNOWN].default_scale = 0.0f;
	types[TYPE_UNKNOWN].default_orientation_r = true;

	types[TYPE_UNKNOWN].default_velocity = glm::vec2(0, 0);
	types[TYPE_UNKNOWN].default_health = 0;
	types[TYPE_UNKNOWN].default_attack = 0;

	//PLAYER_TYPE
	types[TYPE_PLAYER] = EntityType(TYPE_PLAYER);

	types[TYPE_PLAYER].asset.bind_texture("../data/textures/player.jpg");
	types[TYPE_PLAYER].default_scale = 1.0f;
	types[TYPE_PLAYER].default_orientation_r = true;

	types[TYPE_PLAYER].default_velocity = glm::vec2(0, 0);
	types[TYPE_PLAYER].default_health = 20;
	types[TYPE_PLAYER].default_attack = 5;

	//MONSTER_TYPE
	types[TYPE_MONSTER] = EntityType(TYPE_MONSTER);

	types[TYPE_MONSTER].asset.bind_texture("../data/textures/enemy.jpg");
	types[TYPE_MONSTER].default_scale = 1.0f;
	types[TYPE_MONSTER].default_orientation_r = false;

	types[TYPE_MONSTER].default_velocity = glm::vec2(1, 0);
	types[TYPE_MONSTER].default_health = 10;
	types[TYPE_MONSTER].default_attack = 1;

	//FRIENDLY_TYPE
	types[TYPE_FRIENDLY] = EntityType(TYPE_FRIENDLY);

	types[TYPE_FRIENDLY].asset.bind_texture("../data/textures/friendly.jpg");
	types[TYPE_FRIENDLY].default_scale = 1.0f;
	types[TYPE_FRIENDLY].default_orientation_r = true;

	types[TYPE_FRIENDLY].default_velocity = glm::vec2(0, 0);
	types[TYPE_FRIENDLY].default_health = 50;
	types[TYPE_FRIENDLY].default_attack = 0;
	/////////////////////////////////////////////////////////

	return types;
}