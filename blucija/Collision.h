#pragma once
#include <glm.hpp>
#include "Shapes.h"

#include <iostream>

namespace gjk
{

	
template<typename Shape1, typename Shape2>
bool collision(Shape1 & const s1, Shape2 & const s2);


}

namespace gjk
{


using namespace glm;

//helper functions
inline bool same_direction(vec2 a, vec2 b) { return dot(a, b) > 0 ? true : false; }
inline vec2 triple_cross(vec2 a, vec2 b, vec2 c) { return b * dot(a, c) - c * dot(a, b); }

//manually countable array
struct Simplex2D
{
	uint8 size = 0;
	union
	{
		vec2 vertices[3];
		struct { vec2 A, B, C; };
	};
};

template<typename Shape>
vec2 support(Shape s, vec2 direction)
{
	return vec2(0, 0);
	//return point with biggest dot product on shape with direction
}

template<> vec2 support<Circle>(Circle c, vec2 direction)
{
	return c.position + normalize(direction) * c.radius;
}

template<typename Shape1, typename Shape2>
inline vec2 support(Shape1 & const s1, Shape2 & const s2, vec2 direction)
{
	return support(s1, direction) - support(s2, -direction);
}


bool in_simplex(Simplex2D *simplex, vec2 *direction)
{
	switch (simplex->size)
	{
	case 2: //line
	{
		vec2 AO = -simplex->A; 		//vector from newest point to origin
		vec2 AB = AO + simplex->B; 	//line AB

		if (same_direction(AO, AB)) //line AB closest to the origin
		{
			//simplex is unchanged, just offest to right for next looping
			//order is important!!!
			simplex->vertices[2] = simplex->B;
			simplex->vertices[1] = simplex->A;
			simplex->size = 2;

			*direction = triple_cross(AB, AO, AB);
		}
		else //most recent point added is closest to the origin
		{
			//simplex is now just the most recent point added
			simplex->vertices[1] = simplex->A;
			simplex->size = 1;

			*direction = AO; //direction from most recent point added to the origin
		}
	}
	break;
	case 3: //triangle
	{
		vec2 AO = -simplex->A; 		//vector from newest point to origin
		vec2 AB = AO + simplex->B; 	//line AB
		vec2 AC = AO + simplex->C; 	//line AC

		vec2 AB_normal = triple_cross(AB, AO, AB); //not really normal, but perpendicular (always oriented to the origin)

		if (same_direction(AB_normal, simplex->C)) //if height from AB is same direction as OC the origin is in simplex
		{
			return true; //collision! origin in the triangle
		}
		else if (same_direction(AB_normal, AO)) //if origin is closest to line AB 
		{
			//simplex is now line AB
			//order is important!!!
			simplex->vertices[2] = simplex->B;
			simplex->vertices[1] = simplex->A;
			simplex->size = 2;

			*direction = AB_normal;
		}
		else //origin is closest to line AC
		{
			//simplex is now line AC
			//order is important!!!
			simplex->vertices[2] = simplex->C;
			simplex->vertices[1] = simplex->A;
			simplex->size = 2;

			*direction = triple_cross(AC, AO, AC);
			//origin cant be closest to A because A is already the closest point in direction AO
		}
	}
	break;
	}

	return false;
}


template<typename Shape1, typename Shape2>
bool collision(Shape1 & const s1, Shape2 & const s2)
{
	Simplex2D simplex; //2D simplex, [0] is always the latest added point
	simplex.vertices[1] = support(s1, s2, vec2(1.0f, 1.0f)); //arbitrary direction
	simplex.size = 1;

	vec2 d = -simplex.vertices[1]; //if [0] == A, then d == direction AO

	while (true)
	{
		simplex.vertices[0] = support(s1, s2, d);
		++simplex.size;

		if (!same_direction(simplex.vertices[0], d))
			return false; //no collision

		if (in_simplex(&simplex, &d))
			return true;
	}
}


}