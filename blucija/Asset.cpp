#include "stdafx.h"
#include "Asset.h"

#include "Graphics.h"

asset_ID Asset::id_count = 0;
std::vector<texture_ID>	Asset::textureIDs(0);

Asset::Asset(asst_type type_to_set) :
	type(type_to_set)
{
	id = id_count;
	++id_count;

	if (type == ASST_TEXTURE)
		textureIDs.push_back(0);
}

Asset::Asset() :
	type(ASST_UNKNOWN)
{
}

Asset::~Asset()
{
}

void Asset::bind_texture(const char *texture_path)
{
	if (type == ASST_TEXTURE)
		textureIDs[this->id] = gl::create_texture(texture_path);
	else
		assert("Not a texture");
}

void Asset::bind_textureID(texture_ID texID)
{
	if (type == ASST_TEXTURE)
		textureIDs[this->id] = texID;
	else
		assert("Not a texture");
}
