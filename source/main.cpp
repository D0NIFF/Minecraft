#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window/Window.h"
#include "window/Event.h"
#include "graphic/Shader.h"
#include "graphic/Texture.h"


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
    Window::initialize(WIDTH, HEIGHT, "Minecraft");
    Event::initialize();

    Graphic::Shader* shader = Graphic::loadShader(RESOURCES_PATH "shaders/main.vert", RESOURCES_PATH "shaders/main.frag");
    if(shader == nullptr)
    {
        std::cerr << "Failed to load shaders" << std::endl;
        Window::terminate();
        return -1;
    }

    Graphic::Texture* texture = Graphic::Texture::loadTexture(RESOURCES_PATH "textures/test.png");
    if(texture == nullptr)
    {
        std::cerr << "Failed to load textures" << std::endl;
        delete shader;
        Window::terminate();
        return -1;
    }


    // Create VAO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glClearColor(0.6f,0.62f,0.65f,1);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!Window::isShouldClose()) {
        Event::pullEvents();

        if(Event::jpressed(GLFW_KEY_ESCAPE))
            Window::setShouldClose(true);

        if(Event::jclicked(GLFW_MOUSE_BUTTON_1))
        {
            glClearColor(1.0f, 0.2467f, 0.3164f, 1.0f);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();
        texture->bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        Window::swapBuffers();
    }

    delete shader;
    delete texture;

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    Window::terminate();
    return 0;
}
