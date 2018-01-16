#include "stdafx.h"

#include "EntityType.h"
#include "Graphics.h"
#include "Texture.h"

#include <iostream>
using namespace std;


EntityType::EntityType(ent_type type) : type(type)
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

	static Texture entity_textures[TYPE_COUNT]; //important to not initialize textures below with copy constructor, that calls dtor and destroy_gl_texture
	entity_textures[TYPE_UNKNOWN]	.gl_id = 0;//.load_texture(""); //no texture
	entity_textures[TYPE_PLAYER]	.load_texture("circle.png");//("player.jpg");
	entity_textures[TYPE_ENEMY]		.load_texture("circle.png");//("enemy.jpg");
	entity_textures[TYPE_FRIENDLY]	.load_texture("friendly.jpg");

	std::cout << entity_textures[TYPE_UNKNOWN].gl_id << std::endl;
	std::cout << entity_textures[TYPE_PLAYER].gl_id << std::endl;
	std::cout << entity_textures[TYPE_ENEMY].gl_id << std::endl;
	std::cout << entity_textures[TYPE_FRIENDLY].gl_id << std::endl;


	static EntityType types[TYPE_COUNT];
	/////////////////////////////////////////////////////////
	//UNKNOWN_TYPE
	types[TYPE_UNKNOWN] = EntityType(TYPE_UNKNOWN);
	
	types[TYPE_UNKNOWN].texture = &entity_textures[TYPE_UNKNOWN];
	types[TYPE_UNKNOWN].default_scale = 0.0f;
	types[TYPE_UNKNOWN].default_orientation_r = true;

	types[TYPE_UNKNOWN].default_velocity = glm::vec2(0, 0);
	types[TYPE_UNKNOWN].default_health = 0;
	types[TYPE_UNKNOWN].default_attack = 0;

	//PLAYER_TYPE
	types[TYPE_PLAYER] = EntityType(TYPE_PLAYER);

	types[TYPE_PLAYER].texture = &entity_textures[TYPE_PLAYER];
	types[TYPE_PLAYER].default_scale = 1.0f;
	types[TYPE_PLAYER].default_orientation_r = true;

	types[TYPE_PLAYER].default_velocity = glm::vec2(0, 0);
	types[TYPE_PLAYER].default_health = 20;
	types[TYPE_PLAYER].default_attack = 5;

	//MONSTER_TYPE
	types[TYPE_ENEMY] = EntityType(TYPE_ENEMY);

	types[TYPE_ENEMY].texture = &entity_textures[TYPE_ENEMY];
	types[TYPE_ENEMY].default_scale = 1.0f;
	types[TYPE_ENEMY].default_orientation_r = false;

	types[TYPE_ENEMY].default_velocity = glm::vec2(0, 0);
	types[TYPE_ENEMY].default_health = 10;
	types[TYPE_ENEMY].default_attack = 1;

	//FRIENDLY_TYPE
	types[TYPE_FRIENDLY] = EntityType(TYPE_FRIENDLY);

	types[TYPE_FRIENDLY].texture = &entity_textures[TYPE_FRIENDLY];
	types[TYPE_FRIENDLY].default_scale = 1.0f;
	types[TYPE_FRIENDLY].default_orientation_r = true;

	types[TYPE_FRIENDLY].default_velocity = glm::vec2(0, 0);
	types[TYPE_FRIENDLY].default_health = 50;
	types[TYPE_FRIENDLY].default_attack = 0;
	/////////////////////////////////////////////////////////

	return types;
}