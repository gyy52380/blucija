#include "stdafx.h"

#include "EntityType.h"
#include "Graphics.h"


EntityType::EntityType(ent_type type) :
	type(type),
	textureID(0),
	default_scale(1.0f),
	default_orientation_r(true),
	default_health(0),
	default_attack(0),
	default_velocity_x(0),
	default_velocity_y(0)
{
}

EntityType::EntityType()
{
}

EntityType::~EntityType()
{
}

bool operator== (EntityType *entity_type_ptr, ent_type entity_type_enum)
{
	return entity_type_ptr->type == entity_type_enum;
}

bool operator!= (EntityType *entity_type_ptr, ent_type entity_type_enum)
{
	return entity_type_ptr->type != entity_type_enum;
}

EntityType* EntityType::init_entity_types() //ONLY CALL AFTER OPENGL INIT
{
	assert(glewInit() == GLEW_OK && "OpenGL not initialized!");

	static EntityType types[TOTAL_TYPES];

	/////////////////////////////////////////////////////////
	//UNKNOWN_TYPE
	types[UNKNOWN_TYPE] = EntityType(UNKNOWN_TYPE);

	types[UNKNOWN_TYPE].textureID = 0; //no texture
	types[UNKNOWN_TYPE].default_scale = 0.0f;
	types[UNKNOWN_TYPE].default_orientation_r = true;

	types[UNKNOWN_TYPE].default_velocity_x = 0.0f;
	types[UNKNOWN_TYPE].default_velocity_y = 0.0f;
	types[UNKNOWN_TYPE].default_health = 0;
	types[UNKNOWN_TYPE].default_attack = 0;

	//PLAYER_TYPE
	types[PLAYER_TYPE] = EntityType(PLAYER_TYPE);

	types[PLAYER_TYPE].textureID = gl::create_texture("../data/textures/player.jpg");
	types[PLAYER_TYPE].default_scale = 1.0f;
	types[PLAYER_TYPE].default_orientation_r = true;

	types[PLAYER_TYPE].default_velocity_x = 0.0f;
	types[PLAYER_TYPE].default_velocity_y = 0.0f;
	types[PLAYER_TYPE].default_health = 20;
	types[PLAYER_TYPE].default_attack = 5;

	//MONSTER_TYPE
	types[MONSTER_TYPE] = EntityType(MONSTER_TYPE);

	types[MONSTER_TYPE].textureID = gl::create_texture("../data/textures/enemy.jpg");
	types[MONSTER_TYPE].default_scale = 1.0f;
	types[MONSTER_TYPE].default_orientation_r = false;

	types[MONSTER_TYPE].default_velocity_x = 1.0f;
	types[MONSTER_TYPE].default_velocity_y = 0.0f;
	types[MONSTER_TYPE].default_health = 10;
	types[MONSTER_TYPE].default_attack = 1;

	//FRIENDLY_TYPE
	types[FRIENDLY_TYPE] = EntityType(FRIENDLY_TYPE);

	types[FRIENDLY_TYPE].textureID = gl::create_texture("../data/textures/friendly.jpg");
	types[FRIENDLY_TYPE].default_scale = 1.0f;
	types[FRIENDLY_TYPE].default_orientation_r = true;

	types[FRIENDLY_TYPE].default_velocity_x = 1.0f;
	types[FRIENDLY_TYPE].default_velocity_y = 1.0f;
	types[FRIENDLY_TYPE].default_health = 50;
	types[FRIENDLY_TYPE].default_attack = 0;
	/////////////////////////////////////////////////////////

	return types;
}