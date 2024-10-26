#pragma once
#include "Loader.h"

#include <GLFW/glfw3.h>
#include <format>

#define STB_IMAGE_IMPLEMENTATION
#include "Log.h"
#include "../graphic/stb_image.h"

namespace System {
    int Loader::loadPng(const char* fileName, int* width, int* height) {
        //std::cout << "Opening file: " << fileName << std::endl;
        System::Log::alert(std::format("Opening file:  {}", fileName));

        // Image load with stb_image
        unsigned char* image_data = stbi_load(fileName, width, height, nullptr, 4); // 4 - RGBA
        if (!image_data) {
            System::Log::error(std::format("Failed to load image: {}", fileName));
            return 0;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);

        // To free the memory, selected for image
        stbi_image_free(image_data);

        System::Log::alert(std::format("Texture loaded successfully: {}", fileName));

        return texture;
    }

} // System
