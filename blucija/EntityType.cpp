#include "stdafx.h"
#include "EntityType.h"


EntityType::EntityType(ent_type type) :
	type(type),
	textureID(0),
	default_scale(1.0f),
	default_orientation_r(true),
	default_velocity(0),
	default_health(0),
	default_attack(0)
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