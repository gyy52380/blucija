#include "stdafx.h"
#include "EntityType_defs.h"

#include "EntityType.h"
#include "Graphics.h"

EntityType* init_entity_types() //ONLY CALL AFTER OPENGL INIT
{
	assert(glewInit() == GLEW_OK && "OpenGL not initialized!");

	static EntityType types[TOTAL_TYPES];

	/////////////////////////////////////////////////////////
	//UNKNOWN_TYPE
	types[UNKNOWN_TYPE] = EntityType(UNKNOWN_TYPE);
	
	types[UNKNOWN_TYPE].textureID = 0; //no texture
	types[UNKNOWN_TYPE].default_scale = 0.0f;
	types[UNKNOWN_TYPE].default_orientation_r = true;

	types[UNKNOWN_TYPE].default_velocity = 0.0f;
	types[UNKNOWN_TYPE].default_health = 0;
	types[UNKNOWN_TYPE].default_attack = 0;

	//PLAYER_TYPE
	types[PLAYER_TYPE] = EntityType(PLAYER_TYPE);

	types[PLAYER_TYPE].textureID = gl::create_texture("../data/textures/player.jpg");
	types[PLAYER_TYPE].default_scale = 1.0f;
	types[PLAYER_TYPE].default_orientation_r = true;

	types[PLAYER_TYPE].default_velocity = 1.0f;
	types[PLAYER_TYPE].default_health = 20;
	types[PLAYER_TYPE].default_attack = 5;

	//MONSTER_TYPE
	types[MONSTER_TYPE] = EntityType(MONSTER_TYPE);

	types[MONSTER_TYPE].textureID = gl::create_texture("../data/textures/enemy.jpg");
	types[MONSTER_TYPE].default_scale = 1.0f;
	types[MONSTER_TYPE].default_orientation_r = false;

	types[MONSTER_TYPE].default_velocity = 1.0f;
	types[MONSTER_TYPE].default_health = 10;
	types[MONSTER_TYPE].default_attack = 1;

	//FRIENDLY_TYPE
	types[FRIENDLY_TYPE] = EntityType(FRIENDLY_TYPE);

	types[FRIENDLY_TYPE].textureID = gl::create_texture("../data/textures/friendly.jpg");
	types[FRIENDLY_TYPE].default_scale = 1.0f;
	types[FRIENDLY_TYPE].default_orientation_r = true;

	types[FRIENDLY_TYPE].default_velocity = 1.0f;
	types[FRIENDLY_TYPE].default_health = 50;
	types[FRIENDLY_TYPE].default_attack = 0;
	/////////////////////////////////////////////////////////

	return types;
}

