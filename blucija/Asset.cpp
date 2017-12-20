#include "stdafx.h"
#include "Asset.h"

#include "Graphics.h"

assetID					Asset::id_count = 0;
std::vector<textureID>	Asset::textureIDs(0);

Asset::Asset()
{
	id = id_count;
	++id_count;
	textureIDs.push_back(0);
}

Asset::~Asset()
{
}

void Asset::bind_texture(const char *texture_path)
{
	textureIDs[this->id] = gl::create_texture(texture_path);
}

void Asset::bind_texture(textureID texID)
{
	textureIDs[this->id] = texID;
}
