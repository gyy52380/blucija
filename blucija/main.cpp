// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>

#include "typedef.h"
#include "Graphics.h"
#include "InputManager.h"

#include "Quad.h"

const uint32 WIDTH = 640;
const uint32 HEIGHT = 480;

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

	the_window_handle = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
										SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!the_window_handle)
		fatalError("SDL2 failed to create a window!, SDL error: " + (std::string)SDL_GetError());

	the_gl_context = SDL_GL_CreateContext(the_window_handle);
	if (!the_gl_context)
		fatalError("SDL2 failed to create a GL context!, SDL error: " + (std::string)SDL_GetError());

	glewExperimental = GL_TRUE;
	if (glewInit())
		fatalError("Glew failed to initialize!");
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
	gl::init(WIDTH, HEIGHT);

	Vertex v;
	v.pos = glm::vec2(2, 2);
	v.uv = glm::vec2(0, 0);

	std::vector<Vertex> vert;
	vert.push_back(v);

	gl::update_translation_buffer_data(vert);

	while (io::update())
	{
		gl::draw(the_window_handle);
	}

	cleanup();
	return 0;
}

