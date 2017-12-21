#pragma once
#include <vector>

#include "typedef.h"

enum asst_type
{
	ASST_UNKNOWN,
	ASST_TEXTURE,
	ASST_SOUND,

	ASST_TOTAL
};

class Asset
{
public:

	asst_type type = ASST_UNKNOWN;
	asset_ID id;

	Asset(asst_type type_to_set);
	Asset();
	~Asset();

	void bind_texture(const char *texture_path);
	void bind_textureID(texture_ID texID);
	inline texture_ID get_textureID() { return textureIDs[this->id]; }

	static asset_ID id_count;
	static std::vector<texture_ID> textureIDs; //index == assetID, value == textureID

};



