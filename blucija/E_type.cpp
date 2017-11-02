#include "stdafx.h"
#include "E_type.h"


E_type::E_type(EntityType type, GLuint textureID) :
	type(type),
	textureID(textureID),
	default_scale(1.0f),
	default_orientation_r(true),
	default_health(1),
	default_attack(1),
	default_velocity(1.0f)
{
}


E_type::~E_type()
{
}
