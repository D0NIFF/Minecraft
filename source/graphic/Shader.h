//
// Created by doniff on 10/22/2024.
//

#ifndef SHADER_H
#define SHADER_H

namespace Graphic {

class Shader {
public:
    unsigned int ID;

    explicit Shader(unsigned int id);
    ~Shader();

    void use();
};

    Shader* loadShader(const char* vertexPath, const char* fragmentPath);

} // Graphic

#endif //SHADER_H
