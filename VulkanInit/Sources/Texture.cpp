#include "../../Headers/Texture.hpp" 
#include <vulkan/vulkan_core.h>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <../stb_image.h>
void Texture::LoadTextureImage() 
{
    // mod 32 to 16
    //pixels = stbi_load("Resources/Textures/Statue.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

    pixels = stbi_load(TEXTURE_PATH.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

    if (!pixels) 
    {
        throw std::runtime_error("failed to load texture image!");
    }
}