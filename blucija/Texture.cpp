#include "stdafx.h"
#include "Texture.h"

#include <string>
#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using std::string;

#define FULL_PATH this->path().c_str()

string Texture::path_prefix = "../data/textures/";
textureID Texture::texture_count = 0;
Texture Texture::textures[TXT_COUNT] = {};

Texture::Texture()
{
}

Texture::~Texture()
{
	destroy_opengl_texture(); //THIS CAN FUCK YOU UP
}

void Texture::load_texture(string path)
{
	id = texture_count++;

	if (path == "") //empty texture
		return;

	if (path.size() > path_prefix.size() && path.compare(0, path_prefix.size(), path_prefix) == 0) //if path begins with prefix
		short_path = path.substr(path_prefix.size() - 1);
	else //if already given the shortened path name
		short_path = path;

	this->data = stbi_load(FULL_PATH, &width, &height, &channels, STBI_rgb_alpha);

	if (this->data == NULL)
	{
		printf("Couldn't open image file: %s", FULL_PATH);
		return;
	}

	create_opengl_texture();
	free_image_data(); //meh not here
}

void Texture::free_image_data()
{
	stbi_image_free(data);
	printf("Freed image data: %s\n", FULL_PATH);
}

void Texture::create_opengl_texture()
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glGenerateMipmap(GL_TEXTURE_2D); //no need for mipmaps for 2D, if you include mipmaps change MIN/MAG_FILTER

	glBindTexture(GL_TEXTURE_2D, 0);
	
	gl_id = textureID;
}

void Texture::destroy_opengl_texture()
{
	glDeleteTextures(1, &gl_id);
	printf("destroyed opengl texture: %s\n", FULL_PATH);
}

void Texture::bind_texture(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, gl_id);
}

//this should be dynamic one day
void Texture::init_textures()
{
	textures[TXT_UNKNWON]	.load_texture("");
	textures[TXT_PLAYER]	.load_texture("player.jpg");
	textures[TXT_ENEMY]		.load_texture("enemy.jpg");
	textures[TXT_FRIENDLY]	.load_texture("friendly.jpg");

	textures[TXT_GREEN]		.load_texture("green.png");
	textures[TXT_RED]		.load_texture("red.png");

	textures[TXT_CIRCLE]	.load_texture("circle.png");
}



