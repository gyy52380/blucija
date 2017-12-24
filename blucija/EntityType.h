 #pragma once
#include <vec2.hpp>
#include <glew.h>

#include "Texture.h"

enum ent_type
{
	TYPE_UNKNOWN,
	TYPE_PLAYER,
	TYPE_ENEMY,
	TYPE_FRIENDLY,

	TYPE_COUNT
};

class EntityType
{
public:

	ent_type type = TYPE_UNKNOWN;

	//graphics stuff
	Texture *texture;
	float default_scale = 1.0f;
	float default_orientation_r = true;

	//logic
	int default_health = 0;
	int default_attack = 0;
	glm::vec2 default_velocity = glm::vec2(0, 0);


	EntityType(ent_type type);
	EntityType();
	~EntityType();

	static EntityType* init_entity_types(); //this is only called once
};

static inline EntityType* type(ent_type enum_entity_type)
{
	static EntityType *inited_types = EntityType::init_entity_types();
	return &inited_types[enum_entity_type];
}

inline bool operator== (EntityType *entity_type_ptr, ent_type entity_type_enum)
{
	return entity_type_ptr->type == entity_type_enum;
}

inline bool operator!= (EntityType *entity_type_ptr, ent_type entity_type_enum)
{
	return entity_type_ptr->type != entity_type_enum;
}