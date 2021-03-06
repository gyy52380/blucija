#include "stdafx.h"
#include "Entity.h"


Entity::Entity(EntityType *entity_type) :
	type(entity_type->type),
	entity_type(entity_type),
	position(glm::vec2(0, 0)),
	scale(entity_type->default_scale),
	orientation_r(entity_type->default_orientation_r),
	health(entity_type->default_health),
	attack(entity_type->default_attack),
	velocity(entity_type->default_velocity)
{
}

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::move_to(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Entity::move_by(float x, float y)
{
	position.x = position.x + x;
	position.y = position.y + y;
}
