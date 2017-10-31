#pragma once
#include <SDL_scancode.h>

enum Keycode
{
	K_1,
	K_2,
	K_3,
	K_4,
	K_5,
	K_6,
	K_7,
	K_8,
	K_9,
	K_0,
	K_Q,
	K_W,
	K_E,
	K_R,
	K_T,
	K_Z,
	K_U,
	K_I,
	K_O,
	K_P,
	K_A,
	K_S,
	K_D,
	K_F,
	K_G,
	K_H,
	K_J,
	K_K,
	K_L,
	K_Y,
	K_X,
	K_C,
	K_V,
	K_B,
	K_N,
	K_M,
	K_UP,
	K_DOWN,
	K_RIGHT,
	K_LEFT,
	K_SPACE,

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

bool update();

inline bool is_key_pressed(Keycode key)
{
	extern bool pressed_keys[K_TOTAL];
	return pressed_keys[key];
}

inline bool is_key_released(Keycode key)
{
	extern bool released_keys[K_TOTAL];
	return released_keys[key];
}

inline bool is_key_held(Keycode key)
{
	extern bool held_keys[K_TOTAL];
	return held_keys[key];
}

}
