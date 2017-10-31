#include "stdafx.h"
#include "Creature.h"


Creature::Creature() 
	: health(1), attack(0), velocity_x(0), velocity_y(0)
{
}

Creature::Creature(int health, int attack, float velocity) 
	: health(health), attack(attack), velocity_x(velocity_x), velocity_y(0)
{
}

Creature::~Creature()
{
}

void Creature::deal_damage(Creature *attack_target)
{
	attack_target->health -= attack;
}
