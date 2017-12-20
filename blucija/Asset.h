#pragma once
#include <vector>

#include "typedef.h"


typedef uint32 assetID;

class Asset
{
public:

	assetID id;

	Asset();
	~Asset();

	void bind_texture(const char *texture_path);
	void bind_texture(textureID texID);
	inline textureID get_textureID() { return textureIDs[this->id]; }

	static assetID id_count;
	static std::vector<textureID> textureIDs; //index == assetID, value == textureID

};



