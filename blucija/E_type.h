#pragma once
#include <vec2.hpp>

enum EntityType
{
	UNKNOWN_TYPE,
	PLAYER_TYPE,
	MONSTER_TYPE,
	FRIENDLY_TYPE,

	TOTAL_TYPES
};

struct E_type
{
	//IDs
	EntityType type;
	GLuint textureID;

	//graphics stuff
	float default_scale;
	float default_orientation_r;

	//logic
	glm::vec2 default_pos;
	int default_health;
	int default_attack;
	float default_velocity;

	E_type(EntityType type, GLuint textureID);
	~E_type();
};

bool operator== (EntityType type, E_type *type_object)
{
	return type_object->type == type;
}

