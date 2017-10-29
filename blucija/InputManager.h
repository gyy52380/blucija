#pragma once
#include <SDL_scancode.h>

enum KeyScancode
{
	K_1 = SDL_SCANCODE_1,
	K_2 = SDL_SCANCODE_2,
	K_3 = SDL_SCANCODE_3,
	K_4 = SDL_SCANCODE_4,
	K_5 = SDL_SCANCODE_5,
	K_6 = SDL_SCANCODE_6,
	K_7 = SDL_SCANCODE_7,
	K_8 = SDL_SCANCODE_8,
	K_9 = SDL_SCANCODE_9,
	K_0 = SDL_SCANCODE_0,
	K_Q = SDL_SCANCODE_Q,
	K_W = SDL_SCANCODE_W,
	K_E = SDL_SCANCODE_E,
	K_R = SDL_SCANCODE_R,
	K_T = SDL_SCANCODE_T,
	K_Z = SDL_SCANCODE_Z,
	K_U = SDL_SCANCODE_U,
	K_I = SDL_SCANCODE_I,
	K_O = SDL_SCANCODE_O,
	K_P = SDL_SCANCODE_P,
	K_A = SDL_SCANCODE_A,
	K_S = SDL_SCANCODE_S,
	K_D = SDL_SCANCODE_D,
	K_F = SDL_SCANCODE_F,
	K_G = SDL_SCANCODE_G,
	K_H = SDL_SCANCODE_H,
	K_J = SDL_SCANCODE_J,
	K_K = SDL_SCANCODE_K,
	K_L = SDL_SCANCODE_L,
	K_Y = SDL_SCANCODE_Y,
	K_X = SDL_SCANCODE_X,
	K_C = SDL_SCANCODE_C,
	K_V = SDL_SCANCODE_V,
	K_B = SDL_SCANCODE_B,
	K_N = SDL_SCANCODE_N,
	K_M = SDL_SCANCODE_M,
	K_UP = SDL_SCANCODE_UP,
	K_DOWN = SDL_SCANCODE_DOWN,
	K_RIGHT = SDL_SCANCODE_RIGHT,
	K_LEFT = SDL_SCANCODE_LEFT,
	K_SPACE = SDL_SCANCODE_SPACE,

	K_TOTAL
};

enum Mousecode
{
	M_LEFT,
	M_RIGHT,

	M_TOTAL
};

namespace io
{

inline bool is_key_pressed(KeyScancode key)
{
	extern bool pressed_keys[K_TOTAL];
	return pressed_keys[key];
}

inline bool is_key_released(KeyScancode key)
{
	extern bool released_keys[K_TOTAL];
	return released_keys[key];
}

inline bool is_key_held(KeyScancode key)
{
	extern const Uint8 *keyboard;
	return static_cast<bool>(keyboard[key]);
}

bool update();

}
