#include "stdafx.h"
#include "InputManager.h"

#include <iostream>

namespace io
{

bool pressed_keys[K_TOTAL];
bool released_keys[K_TOTAL];
bool held_keys[K_TOTAL];

Keycode convert_sdlk_to_keycode(SDL_Keycode keycode)
{
	switch (keycode)
	{
	case SDLK_UP:
		return K_UP;
		break;
	case SDLK_DOWN:
		return K_DOWN;
		break;
	case SDLK_LEFT:
		return K_LEFT;
		break;
	case SDLK_RIGHT:
		return K_RIGHT;
		break;
	case SDLK_SPACE:
		return K_SPACE;
		break;
	case SDLK_w:
		return K_W;
		break;
	case SDLK_a:
		return K_A;
		break;
	case SDLK_s:
		return K_S;
		break;
	case SDLK_d:
		return K_D;
		break;
	}
}

bool update()
{
	SDL_Event evnt;
	for (int i = 0; i < K_TOTAL; i++)
	{
		released_keys[i] = pressed_keys[i] || held_keys[i]; //this works bcs of for loop after while; or is used for VERY short press of key
		pressed_keys[i] = false;
	}

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
		{
			return false;
		}	break;
		case SDL_KEYDOWN:
		{
			const Keycode key = convert_sdlk_to_keycode(evnt.key.keysym.sym);

			if (!is_key_held(key))
				pressed_keys[key] = true;
			held_keys[key] = true;
		}	break;
		case SDL_KEYUP:
		{
			const Keycode key = convert_sdlk_to_keycode(evnt.key.keysym.sym);
			held_keys[key] = false;
		}	break;
		//more event cases
		}
	}

	for (int i = 0; i < K_TOTAL; i++)
	{
		if (held_keys[i])
			released_keys[i] = false;
	}

	return true;
}

}