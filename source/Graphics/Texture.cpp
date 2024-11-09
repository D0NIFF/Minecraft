#include "Texture.h"

#include <format>
#include <GL/glew.h>

#include "../System/ImageLoader.h"
#include "../Debug/Log.h"

namespace Graphics {
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
        const GLuint texture = System::ImageLoader::loadPng(path, &width, &height);
        if (texture == 0){
            Debug::Log::error(std::format("Could not load texture {}", path));
            return nullptr;
        }
        return new Texture(texture, width, height);
    }
} // Graphic