#include "stdafx.h"
#include "Error.h"

#include <string>
#include <cstdio>

void fatalError(const char *errMessage)
{
	printf("%s\n", errMessage);

	extern SDL_Window* the_window_handle;
	extern SDL_GLContext the_gl_context;

	SDL_GL_DeleteContext(the_gl_context);
	SDL_DestroyWindow(the_window_handle);
	SDL_Quit();
	exit(0xF);
}

void fatalError(std::string errMessage)
{
	fatalError(errMessage.c_str());
}



