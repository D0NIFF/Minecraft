#include "Mesh.h"

#include <GL/glew.h>

#include "../Debug/Log.h"

namespace Graphics {
    Mesh::Mesh(const float* buffer, const size_t size, const int* attributes) : vertices(size)
    {
        Debug::Log::alert("Mesh initializing started.");
        int vertexSize = 0;
        for (int i = 0; attributes[i]; i++)
            vertexSize += attributes[i];

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * vertices, buffer, GL_STATIC_DRAW);

        int offset = 0;
        for (int i = 0; attributes[i]; i++)
        {
            int tempSize = attributes[i];
            glVertexAttribPointer(i, tempSize, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (GLvoid*)(offset * sizeof(float)));
            glEnableVertexAttribArray(i);
            offset += tempSize;
        }

        glBindVertexArray(0);
        Debug::Log::alert("Mesh successfully initialized.");
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        Debug::Log::alert("Mesh successfully deleting.");
    }

    void Mesh::draw(const unsigned int shader) const
    {
        glBindVertexArray(vao);
        glDrawArrays(shader, 0, vertices);
        glBindVertexArray(0);
    }


} // Graphics