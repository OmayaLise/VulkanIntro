#pragma once
#include <../stb_image.h>
#include <sstream>

const std::string TEXTURE_PATH = "Resources/Textures/viking_room.png";

class Texture
{
public:
	void LoadTextureImage();
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels;
};