#pragma once

#include <iostream>
#include <GL/glew.h>

#include "GLFW/glfw3.h"
#include "window/Window.h"
#include "window/Event.h"
#include "graphic/Shader.h"


int WIDTH = 1280;
int HEIGHT = 720;

float vertices[] = {
    // x    y     z     u     v
    -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
     1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

     1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
     1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

int main()
{
    Window::initialize(1280, 720, "Minecraft");
    Event::initialize();

    Graphic::Shader* shader = Graphic::loadShader(RESOURCES_PATH "shaders/main.glslv", RESOURCES_PATH "shaders/main.glslf");
    if(shader == nullptr)
    {
        std::cerr << "Failed to load shaders" << std::endl;
        Window::terminate();
        return -1;
    }

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    while (!Window::isShouldClose()) {
        Event::pullEvents();

        if(Event::jpressed(GLFW_KEY_ESCAPE))
            Window::setShouldClose(true);

        if(Event::jclicked(GLFW_MOUSE_BUTTON_1))
            glClearColor(0.6f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        Window::swapBuffers();
    }

    //glfwDestroyWindow(window);
    Window::terminate();
    return 0;
}
