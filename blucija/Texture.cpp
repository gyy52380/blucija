#include "stdafx.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture(const char *path, int request_comp)
{
	data = stbi_load(path, &w, &h, &comp, request_comp);
}


Texture::~Texture()
{
	stbi_image_free(data);
}
