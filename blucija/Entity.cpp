#include "stdafx.h"
#include "Entity.h"


Entity::Entity(EntityType *type) :
	type(type),
	pos(glm::vec2(0, 0)),
	scale(type->default_scale),
	orientation_r(type->default_orientation_r),
	health(type->default_health),
	attack(type->default_attack),
	velocity(type->default_velocity)
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
	pos.x = x;
	pos.y = y;
}

void Entity::move_by(float x, float y)
{
	pos.x = pos.x + x;
	pos.y = pos.y + y;
}
