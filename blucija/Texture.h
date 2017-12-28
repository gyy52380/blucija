#pragma once
#include <string>

#include "typedef.h"
using std::string;

class Texture
{
public:

	string	short_path;
	int		width;
	int		height;
	int 	channels;
	uint8*	data;

	uint32	id;
	uint32	gl_id = 0; //uninitialized


	Texture();
	~Texture();

	void load_texture(string path);
	void free_image_data();
	void create_opengl_texture();
	void destroy_opengl_texture();
	void bind_texture(int slot = 0);

	static string path_prefix;
	static uint32 texture_count;

	inline string path() { return path_prefix + short_path; }
};
