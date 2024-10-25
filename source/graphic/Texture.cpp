#include "Texture.h"

#include <iostream>
#include <ostream>
#include <GL/glew.h>

#include "../system/Loader.h"

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

    Texture* Texture::loadTexture(const char* path)
    {
        int width, height;
        const GLuint texture = System::Loader::loadPng(path, &width, &height);
        if (texture == 0){
            std::cerr << "Could not load texture " << path << std::endl;
            return nullptr;
        }
        return new Texture(texture, width, height);
    }
} // Graphic