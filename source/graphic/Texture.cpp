#include "Texture.h"

#include <format>
#include <GL/glew.h>

#include "../system/Loader.h"
#include "../system/Log.h"

namespace Graphic {
    Texture::Texture(const unsigned int id, const int width, const int height): id(id), width(width), height(height)
    {
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &id);
    }

    void Texture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    Texture* loadTexture(const char* path)
    {
        int width, height;
        const GLuint texture = System::Loader::loadPng(path, &width, &height);
        if (texture == 0){
            System::Log::error(std::format("Could not load texture {}", path));
            return nullptr;
        }
        return new Texture(texture, width, height);
    }
} // Graphic