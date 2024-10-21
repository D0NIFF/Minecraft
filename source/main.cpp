#pragma once

#include <iostream>

#include "GLFW/glfw3.h"
#include "window/Window.h"
#include "window/Event.h"


int WIDTH = 1280;
int HEIGHT = 720;
int main()
{
    Window::initialize(1280, 720, "Minecraft");
    Event::initialize();

    while (!Window::isShouldClose()) {
        Event::pullEvents();

        if(Event::jpressed(GLFW_KEY_ESCAPE))
            Window::setShouldClose(true);

        if(Event::jclicked(GLFW_MOUSE_BUTTON_1))
            glClearColor(0.6f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);
        Window::swapBuffers();
    }

    //glfwDestroyWindow(window);
    Window::terminate();
    return 0;
}
