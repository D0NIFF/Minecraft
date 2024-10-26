#ifndef SHADER_H
#define SHADER_H
#include <glm/fwd.hpp>

namespace Graphic {

class Shader {
public:
    unsigned int id;

    explicit Shader(unsigned int id);
    ~Shader();

    void use() const;
    void uniformMatrix(const char* name, glm::mat4 matrix);
};

extern Shader* loadShader(const char* vertexPath, const char* fragmentPath);

} // Graphic

#endif //SHADER_H
