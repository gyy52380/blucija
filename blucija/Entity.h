#pragma once

#include <vec2.hpp>
#include <vector>

class Entity
{
public:

	glm::vec2 pos;
	float scale;
	GLuint textureID;
	bool orientation_r;

	Entity();
	Entity(glm::vec2 pos, float scale, GLuint textureID, bool orientation_r);
	~Entity();

	void move_to(float x, float y);
	void move_by(float x, float y);

	static std::vector<Entity*> entity_list;
	
	static void add_entity(Entity* to_add);
	static void remove_entity(Entity* to_remove);
	static void draw();
};

