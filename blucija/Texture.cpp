#include "stdafx.h"
#include "Texture.h"

#include <string>
#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using std::string;

string Texture::path_prefix = "../data/textures/";
uint32 Texture::texture_count = 0;

Texture::Texture() : id(texture_count++)
{
}

Texture::~Texture()
{
	destroy_opengl_texture(); //THIS CAN FUCK YOU UP
}

void Texture::load_texture(string path)
{
	if (path.size() > path_prefix.size() && path.compare(0, path_prefix.size(), path_prefix) == 0) //if path begins with prefix
		this->short_path = path.substr(path_prefix.size() - 1);
	else //if already given the shortened path name
		this->short_path = path;

	this->data = stbi_load(this->path().c_str(), &this->width, &this->height, &this->channels, STBI_rgb_alpha);

	this->create_opengl_texture();
	this->free_image_data(); //meh not here
}

void Texture::free_image_data()
{
	stbi_image_free(this->data);
	printf("Freed image data: %s\n", this->path().c_str());
}

void Texture::create_opengl_texture()
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->data);
	if (uint32 error = glGetError())
	{
		printf("Can't load texture: %s; openGL error: %i\n", this->path().c_str(), error);
		this->gl_id = 0;
		return;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glGenerateMipmap(GL_TEXTURE_2D); //no need for mipmaps for 2D, if you include mipmaps change MIN/MAG_FILTER

	glBindTexture(GL_TEXTURE_2D, 0);
	
	this->gl_id = textureID;
	//free image data
}

void Texture::destroy_opengl_texture()
{
	glDeleteTextures(1, &this->gl_id);
	printf("destroyed opengl texture: %s\n", this->path().c_str());
}

void Texture::bind_texture(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->gl_id);
}



