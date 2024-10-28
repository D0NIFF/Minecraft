#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

#include "../Debug/Log.h"

GLFWwindow* Window::window;
int Window::width = 0;
int Window::height = 0;

int Window::initialize(const int width, const int height, const char* title)
{
    Debug::Log::alert("Starting window initialization");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // Max version: 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  // Min version: 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);                        // Window scaling: true

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (window == nullptr)
    {
        Debug::Log::error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    int glewExperimental = GL_TRUE;
    if(glfwInit() != GL_TRUE)
    {
        Debug::Log::error("Failed to initialize GLEW");
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        Debug::Log::error("Failed to initialize GLEW");
        return -1;
    }
    glViewport(0, 0, width, height);

    Window::width = width;
    Window::height = height;

    Debug::Log::alert("Window initialized");

    return 0;
}

void Window::terminate(){
    glfwTerminate();
}

bool Window::isShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::setShouldClose(bool value)
{
    return glfwSetWindowShouldClose(window, value);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::setCursorMode(int mode)
{
    glfwSetInputMode(window, GLFW_CURSOR, mode);
}
