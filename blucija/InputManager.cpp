#include "stdafx.h"
#include "InputManager.h"

namespace io
{

const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
bool pressed_keys[K_TOTAL];
bool released_keys[K_TOTAL];
SDL_Event evnt;

bool update()
{
	for (int i = 0; i < K_TOTAL; i++)
	{
		pressed_keys[i]		= false;
		released_keys[i]	= false;
	}

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			return false;
			break;
		case SDL_KEYDOWN:
			pressed_keys[evnt.key.keysym.scancode] = true;
			keyboard = SDL_GetKeyboardState(NULL);

			break;
		case SDL_KEYUP:
			released_keys[evnt.key.keysym.scancode] = true;
			keyboard = SDL_GetKeyboardState(NULL);

			break;
		case SDL_MOUSEMOTION:

			break;
		case SDL_MOUSEBUTTONDOWN:

			break;
		case SDL_MOUSEBUTTONUP:

			break;
		}
	}
	return true;
}

}