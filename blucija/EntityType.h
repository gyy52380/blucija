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
	int default_health;
	int default_attack;
	float default_velocity_x;
	float default_velocity_y;
	

	EntityType(ent_type type);
	EntityType();
	~EntityType();
	
	static inline EntityType* get_type(ent_type enum_entity_type)
	{
		static EntityType *inited_types = init_entity_types();
		return &inited_types[enum_entity_type];
	}

private:
	static EntityType* init_entity_types(); //this is only called once
};

const auto &type = EntityType::get_type; //alias bcs too long

bool operator== (EntityType *entity_type_ptr, ent_type entity_type_enum);
bool operator!= (EntityType *entity_type_ptr, ent_type entity_type_enum);

