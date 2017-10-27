#pragma once

#include "typedef.h"

class Texture
{
public:

	unsigned char *data;
	int w, h;
	int comp;

	Texture(const char *path, int request_comp = 4);
	~Texture();
};

