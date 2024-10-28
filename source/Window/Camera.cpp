#include "Camera.h"

#include <glm/ext.hpp>

#include "Window.h"

namespace Windows {
    void Camera::updateVectors()
    {
        front = glm::vec3(rotation * glm::vec4(0, 0, -1, 1));
        right = glm::vec3(rotation * glm::vec4(1, 0, 0, 1));
        up =    glm::vec3(rotation * glm::vec4(0, 1, 0, 1));
    }

    Camera::Camera(const glm::vec3 position, const float fov) : rotation(1.0f), fov(fov), position(position)
    {
        updateVectors();
    }

    void Camera::rotate(float x, float y, float z)
    {
        rotation = glm::rotate(rotation, z, glm::vec3(0, 0, 1));
        rotation = glm::rotate(rotation, y, glm::vec3(0, 1, 0));
        rotation = glm::rotate(rotation, x, glm::vec3(1, 0, 0));

        updateVectors();
    }

    glm::mat4 Camera::getProjectionMatrix()
    {
        float aspect = (float)Window::width / (float)Window::height;
        return glm::perspective(fov, aspect, 0.1f, 100.0f);
    }

    glm::mat4 Camera::getViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }
} // Window