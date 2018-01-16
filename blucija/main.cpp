// main.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <string>
#include <iostream>


#include "InputManager.h"
#include "Renderer.h"

#include "EntityManager.h"
#include "Collision.h"

#include <glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx\string_cast.hpp>

#include <cmath>

constexpr uint32 SCREEN_WIDTH = 640;
constexpr uint32 SCREEN_HEIGHT = 640;

SDL_Window* the_window_handle;
SDL_GLContext the_gl_context;

#define GL_DEBUG
#include "main_extension.cpp"


int main(int argc, char **argv)
{
	init(the_window_handle, the_gl_context, SCREEN_WIDTH, SCREEN_HEIGHT);//(the_window_handle, the_gl_context, SCREEN_WIDTH, SCREEN_HEIGHT);

	using namespace glm;

	EntityManager manager(4);
	auto player = manager.add_entity(TYPE_PLAYER);
	auto enemy = manager.add_entity(TYPE_ENEMY);
	auto is_colliding_indicator = manager.add_entity(TYPE_FRIENDLY);

	player->move_to(0, 0);
	enemy->move_to(4, 0);

	float r = 0.5f;
	player->hitbox.radius = r;
	enemy->hitbox.radius = r;
	is_colliding_indicator->move_to(3, 3);

	////
	constexpr float timestep = 1.0f / 120.0f * 1000.0f;
	uint32 time[2];
	uint32 dt = 0.0f;
	float accumulator = 0.0f;
	////
	while (io::update())
	{
		////
		time[0] = SDL_GetTicks();
		////
		while (accumulator >= timestep) //physics loop
		{
			////
			accumulator -= timestep;
			////

			if (enemy->position.x >= 6)
				enemy->velocity.x = -0.1f;

			manager.update();
			
			
			player->hitbox.position = player->position + vec2(r/sqrt(2), r / sqrt(2));
			enemy->hitbox.position = enemy->position + vec2(r / sqrt(2), r / sqrt(2));

			if (gjk::collision<Circle, Circle>(player->hitbox, enemy->hitbox))
			{
				//std::cout << "Colliding" << std::endl;
				enemy->velocity.x = 0.1f;
			}
			else
				//std::cout << "Not" << std::endl;
				
			

			manager.queue_for_rendering();
		}

		renderer::render(the_window_handle, accumulator/1000.0f);
		////
		time[1] = SDL_GetTicks();
		dt = time[1] - time[0];
		accumulator += dt;
		////
	}

	cleanup(the_window_handle, the_gl_context);
	return 0;
}

