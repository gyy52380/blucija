//////////////////
//functions that should be in main.cpp
/////////////////
#include "stdafx.h"
#include <Windows.h>

#include "typedef.h"
#include "Error.h"
#include "Graphics.h"


#ifdef GL_DEBUG
static void APIENTRY opengl_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	if (type == GL_DEBUG_TYPE_OTHER_ARB) return;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW_ARB:     fprintf(stderr, "[LOW] ");    break;
	case GL_DEBUG_SEVERITY_MEDIUM_ARB:  fprintf(stderr, "[MEDIUM] "); break;
	case GL_DEBUG_SEVERITY_HIGH_ARB:    fprintf(stderr, "[HIGH] ");   break;
	}

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR_ARB:               fprintf(stderr, "ERROR: ");               break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: fprintf(stderr, "DEPRECATED_BEHAVIOR: "); break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:  fprintf(stderr, "UNDEFINED_BEHAVIOR: ");  break;
	case GL_DEBUG_TYPE_PORTABILITY_ARB:         fprintf(stderr, "PORTABILITY: ");         break;
	case GL_DEBUG_TYPE_PERFORMANCE_ARB:         fprintf(stderr, "PERFORMANCE: ");         break;
	case GL_DEBUG_TYPE_OTHER_ARB:               fprintf(stderr, "OTHER: ");               break;
	}

	fprintf(stderr, "id=0x%u %s\n", (unsigned int)id, message);
}
#endif

static void init(SDL_Window* &the_window_handle, SDL_GLContext &the_gl_context, const uint32 SCREEN_WIDTH, const uint32 SCREEN_HEIGHT)
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

#ifdef GL_DEBUG
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

	the_window_handle = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!the_window_handle)
		fatalError("SDL2 failed to create a window!, SDL error: " + (std::string)SDL_GetError());

	the_gl_context = SDL_GL_CreateContext(the_window_handle);
	if (!the_gl_context)
		fatalError("SDL2 failed to create a GL context!, SDL error: " + (std::string)SDL_GetError());

#ifdef GL_DEBUG
	glewExperimental = GL_TRUE;
#endif
	if (glewInit())
		fatalError("Glew failed to initialize!");

#ifdef GL_DEBUG
	if (glDebugMessageCallbackARB)
	{
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageCallbackARB(opengl_callback, NULL);
		GLuint ids;
		glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &ids, true);
	}
#endif

	gl::init(8, 8); //amount of quads in direction
}

static void cleanup(SDL_Window* &the_window_handle, SDL_GLContext &the_gl_context)
{
	gl::cleanup();
	SDL_GL_DeleteContext(the_gl_context);
	SDL_DestroyWindow(the_window_handle);
	SDL_Quit();
	exit(0);
}