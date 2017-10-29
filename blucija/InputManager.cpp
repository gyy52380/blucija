#include "stdafx.h"
#include "InputManager.h"

namespace io
{

const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
bool pressed_keys[K_TOTAL] = {};
bool released_keys[K_TOTAL] = {};


bool update()
{
	

	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{

		for (int i = 0; i < K_TOTAL; i++)
		{
			pressed_keys[i] = false;
			released_keys[i] = false;
		}

		switch (evnt.type)
		{
		case SDL_QUIT:
		{
			return false; //quit main loop
		}	break;
		case SDL_KEYDOWN:
		{
			const KeyScancode key = static_cast<KeyScancode>(evnt.key.keysym.scancode);
			keyboard = SDL_GetKeyboardState(NULL);

			pressed_keys[key] = true;
			
		}	break;
		case SDL_KEYUP:
		{
			const KeyScancode key = static_cast<KeyScancode>(evnt.key.keysym.scancode);
			keyboard = SDL_GetKeyboardState(NULL);

			released_keys[key] = true;

		}	break;
		case SDL_MOUSEMOTION:
		{

		}	break;
		case SDL_MOUSEBUTTONDOWN:
		{

		}	break;
		case SDL_MOUSEBUTTONUP:
		{

		}	break;
		}
	}
	return true;
}

}