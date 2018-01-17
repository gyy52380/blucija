#pragma once
#include <string>

#include "typedef.h"
using std::string;

enum
{
	TXT_UNKNWON,
	TXT_PLAYER,
	TXT_ENEMY,
	TXT_FRIENDLY,

	TXT_GREEN,
	TXT_RED,

	TXT_CIRCLE,

	TXT_COUNT
};

typedef int textureID;
typedef unsigned int GLuint;

class Texture
{
public:

	string	short_path;
	int		width;
	int		height;
	int 	channels;
	uint8*	data;

	textureID	id		= TXT_UNKNWON;
	GLuint		gl_id	= 0; //uninitialized


	Texture();
	~Texture();

	void load_texture(string path);
	void free_image_data();
	void create_opengl_texture();
	void destroy_opengl_texture();
	void bind_texture(int slot = 0);

	static string path_prefix;
	static textureID texture_count;
	static Texture textures[TXT_COUNT];

	static void init_textures();

	inline string path() { return path_prefix + short_path; }


	
};
