#pragma once
#include "Entity.h"

class Creature : public Entity
{
public:

	int health;
	int attack;
	float velocity_x;
	float velocity_y;

	Creature();
	Creature(int health, int attack, float velocity_x);
	~Creature();

	void deal_damage(Creature *attack_target);
	void jump();
};

