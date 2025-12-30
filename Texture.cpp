#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "LoadPngTexture.h"

GLuint Texture::load(const std::string& path)
{
    return LoadTexturePng::loadTexture(path.c_str());
}
