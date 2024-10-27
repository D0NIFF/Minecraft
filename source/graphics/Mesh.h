#ifndef MESH_H
#define MESH_H

#include <cstddef>

namespace Graphics {

class Mesh {
private:
    unsigned int vao;
    unsigned int vbo;
    size_t vertices;

public:
    Mesh(const float* buffer, size_t size, const int* attributes);
    ~Mesh();

    void draw(unsigned int shader) const;
};

} // Graphics

#endif //MESH_H
