#ifndef SHADER_H
#define SHADER_H

namespace Graphic {

class Shader {
public:
    unsigned int ID;

    explicit Shader(unsigned int id);
    ~Shader();

    void use() const;
};

extern Shader* loadShader(const char* vertexPath, const char* fragmentPath);

} // Graphic

#endif //SHADER_H
