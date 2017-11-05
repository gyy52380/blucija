#pragma once
#include "EntityType.h"

EntityType* init_entity_types(); //please only call once

inline EntityType* type(ent_type enum_entity_type)
{
	static EntityType *types = init_entity_types();
	return &types[enum_entity_type];
}