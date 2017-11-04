#pragma once
#include "EntityType.h"

inline EntityType* type(ent_type enum_entity_type)
{
	extern EntityType* init_entity_types();
	static EntityType *types = init_entity_types();

	return &types[enum_entity_type];
}