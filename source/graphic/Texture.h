#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>

namespace Graphic {

class Texture {
public:
    unsigned int id;
    int width;
    int height;
    Texture(unsigned int id, int width, int height);
    ~Texture();

    void bind() const;

    static Texture* loadTexture(const char* path);
};


} // Graphic

#endif //TEXTURE_H
