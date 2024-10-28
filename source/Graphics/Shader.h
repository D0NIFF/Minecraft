#ifndef SHADER_H
#define SHADER_H
#pragma once
#include <glm/fwd.hpp>

namespace Graphics {

class Shader {
public:
    unsigned int id;

    explicit Shader(unsigned int id);
    ~Shader();

    void use() const;
    void uniformMatrix(const char* name, glm::mat4 matrix) const;
};

extern Shader* loadShader(const char* vertexPath, const char* fragmentPath);

} // Graphic

#endif //SHADER_H
