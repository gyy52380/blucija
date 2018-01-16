// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>

#include "typedef.h"
#include "Graphics.h"
#include "InputManager.h"
#include "Quad.h"
#include "EntityManager.h"
#include "Renderer.h"
#include "Collision.h"

#include <glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx\string_cast.hpp>

#include <cmath>

const uint32 SCREEN_WIDTH = 640;
const uint32 SCREEN_HEIGHT = 640;

SDL_Window* the_window_handle;
SDL_GLContext the_gl_context;

void fatalError(std::string errMessage)
{
	printf("%s\n", errMessage.c_str());

	SDL_GL_DeleteContext(the_gl_context);
	SDL_DestroyWindow(the_window_handle);
	SDL_Quit();
	exit(0xF);
}

void init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		fatalError("SDL2 failed to initialize!, SDL error: " + (std::string)SDL_GetError());

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); //MSAA
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); //MSAA
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1); //vsync

	the_window_handle = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
										SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!the_window_handle)
		fatalError("SDL2 failed to create a window!, SDL error: " + (std::string)SDL_GetError());

	the_gl_context = SDL_GL_CreateContext(the_window_handle);
	if (!the_gl_context)
		fatalError("SDL2 failed to create a GL context!, SDL error: " + (std::string)SDL_GetError());

	glewExperimental = GL_TRUE;
	if (glewInit())
		fatalError("Glew failed to initialize!");

	gl::init(8, 8); //amount of quads in direction
}

void cleanup()
{
	gl::cleanup();
	SDL_GL_DeleteContext(the_gl_context);
	SDL_DestroyWindow(the_window_handle);
	SDL_Quit();
	exit(0);
}


int main(int argc, char **argv)
{
	init();

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

	cleanup();
	return 0;
}

