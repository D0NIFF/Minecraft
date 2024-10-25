#include "Loader.h"
#include <GLFW/glfw3.h>
#include <png.h>
#include <iostream>

namespace System {
    int Loader::loadPng(const char* fileName, int* width, int* height) {
        FILE *f;
        int is_png, bit_depth, color_type, row_bytes;
        png_infop info_ptr, end_info;
        png_uint_32 t_width, t_height;
        png_byte header[8], *image_data;
        png_bytepp row_pointers;
        png_structp png_ptr;
        GLuint texture;
        int alpha;

        std::cout << "Opening file: " << fileName << std::endl;
        f = fopen(fileName, "rb");
        if (!f) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return 0;
        }

        fread(header, 1, 8, f);
        is_png = !png_sig_cmp(header, 0, 8);
        if (!is_png) {
            fclose(f);
            std::cerr << "File is not recognized as a PNG file" << std::endl;
            return 0;
        }

        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_ptr) {
            fclose(f);
            std::cerr << "png_create_read_struct failed" << std::endl;
            return 0;
        }

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr) {
            png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
            fclose(f);
            std::cerr << "png_create_info_struct failed" << std::endl;
            return 0;
        }
        end_info = png_create_info_struct(png_ptr);
        if (!end_info) {
            png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
            fclose(f);
            std::cerr << "png_create_info_struct failed (end_info)" << std::endl;
            return 0;
        }

        if (setjmp(png_jmpbuf(png_ptr))) {
            std::cerr << "Error during png creation" << std::endl;
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(f);
            return 0;
        }

        png_init_io(png_ptr, f);
        png_set_sig_bytes(png_ptr, 8);
        std::cerr << "Error reading PNG info" << std::endl;
        png_read_info(png_ptr, info_ptr);
        std::cerr << "Error2 reading PNG info" << std::endl;

        // Логирование состояния
        std::cout << "Reading PNG info" << std::endl;

        png_get_IHDR(png_ptr, info_ptr, &t_width, &t_height, &bit_depth, &color_type, NULL, NULL, NULL);
        *width = t_width;
        *height = t_height;
        png_read_update_info(png_ptr, info_ptr);

        row_bytes = png_get_rowbytes(png_ptr, info_ptr);
        image_data = (png_bytep) malloc(row_bytes * t_height * sizeof(png_byte));
        if (!image_data) {
            std::cerr << "Failed to allocate memory for image_data" << std::endl;
            throw std::runtime_error("Failed to allocate memory for image_data");
        }
        row_pointers = (png_bytepp) malloc(t_height * sizeof(png_bytep));
        if (!row_pointers) {
            std::cerr << "Failed to allocate memory for row_pointers" << std::endl;
            throw std::runtime_error("Failed to allocate memory for row_pointers");
        }
        for (unsigned int i = 0; i < t_height; ++i) {
            row_pointers[t_height - 1 - i] = image_data + i * row_bytes;
        }

        png_read_image(png_ptr, row_pointers);

        switch (png_get_color_type(png_ptr, info_ptr)) {
            case PNG_COLOR_TYPE_RGBA:
                alpha = GL_RGBA;
                break;
            case PNG_COLOR_TYPE_RGB:
                alpha = GL_RGB;
                break;
            default:
                std::cerr << "Color type " << png_get_color_type(png_ptr, info_ptr) << " not supported!" << std::endl;
                throw std::runtime_error("Color type not supported");
        }

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t_width, t_height, 0, alpha, GL_UNSIGNED_BYTE, (GLvoid *) image_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);

        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        free(row_pointers);
        fclose(f);

        std::cout << "Texture loaded successfully: " << fileName << std::endl;

        return texture;
    }
} // System
