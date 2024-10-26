#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace Windows {

class Camera {
private:
    void updateVectors();
public:
    glm::vec3 front {};
    glm::vec3 up {};
    glm::vec3 right {};
    glm::mat4 rotation {};

    float fov;
    glm::vec3 position;

    Camera(glm::vec3 position, float fov);

    void rotate(float x, float y, float z);

    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
};

} // Window

#endif //CAMERA_H
