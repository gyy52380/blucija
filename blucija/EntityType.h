#pragma once
#include <vec2.hpp>
#include <glew.h>

enum ent_type
{
	UNKNOWN_TYPE,
	PLAYER_TYPE,
	MONSTER_TYPE,
	FRIENDLY_TYPE,

	TOTAL_TYPES
};

class EntityType
{
public:
	//IDs
	ent_type type;
	GLuint textureID;

	//graphics stuff
	float default_scale;
	float default_orientation_r;

	//logic
	float default_velocity;
	int default_health;
	int default_attack;
	

	EntityType(ent_type type);
	EntityType();
	~EntityType();
};

bool operator== (EntityType *entity_type_ptr, ent_type entity_type_enum);
bool operator!= (EntityType *entity_type_ptr, ent_type entity_type_enum);

