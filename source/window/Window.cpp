#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

GLFWwindow* Window::window;

int Window::initialize(const int width, const int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    int glewExperimental = GL_TRUE;
    if(glfwInit() != GL_TRUE)
    {
        std::cout << "Failed to initialize GLEW." << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    glViewport(0, 0, width, height);
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
