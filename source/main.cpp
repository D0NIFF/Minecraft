#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window/Window.h"
#include "window/Event.h"
#include "graphic/Shader.h"
#include "graphic/Texture.h"
#include "system/Log.h"

// Define the width and height of the window
int WIDTH = 1280;
int HEIGHT = 720;

// Define the vertex data for a rectangle (two triangles)
float vertices[] = {
    // x    y     z     u     v
    -1.0f,-1.0f, 0.0f, 0.0f, 1.0f, // Bottom left vertex
     1.0f,-1.0f, 0.0f, 1.0f, 1.0f, // Bottom right vertex
    -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Top left vertex

     1.0f,-1.0f, 0.0f, 1.0f, 1.0f, // Bottom right vertex (again)
     1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top right vertex
    -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Top left vertex (again)
};

int main()
{
    System::Log::alert("Program started");
    Window::initialize(WIDTH, HEIGHT, "Minecraft"); // Initialize the window with specified width, height, and title
    Event::initialize();                                // Initialize event handling

    // Load vertex and fragment shaders from specified paths
    Graphic::Shader* shader = Graphic::loadShader(RESOURCES_PATH "shaders/main.vert", RESOURCES_PATH "shaders/main.frag");
    if(shader == nullptr) // Check if shader loading failed
    {
        System::Log::error("Failed to load shaders");
        Window::terminate();
        return -1; // Exit with error code
    }

    // Load texture from specified path
    Graphic::Texture* texture = Graphic::loadTexture(RESOURCES_PATH "textures/test.png");
    if(texture == nullptr) // Check if texture loading failed
    {
        System::Log::error("Failed to load textures");
        delete shader; // Clean up shader resource
        Window::terminate(); // Terminate the window
        return -1; // Exit with error code
    }

    // Create Vertex Array Object (VAO) and Vertex Buffer Object (VBO)
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO); // Generate a VAO
    glGenBuffers(1, &VBO); // Generate a VBO

    glBindVertexArray(VAO); // Bind the VAO to the current context
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the VBO to the current context
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Upload vertex data to the GPU

    // Set up vertex attribute pointers
    // Position attribute (x, y, z)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0); // Enable the position attribute

    // Texture coordinate attribute (u, v)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); // Enable the texture coordinate attribute

    glBindVertexArray(0); // Unbind the VAO

    // Set the clear color for the window
    glClearColor(0.6f, 0.62f, 0.65f, 1); // Light gray color

    // Enable face culling and blending
    glEnable(GL_CULL_FACE); // Enable face culling to remove back faces
    glEnable(GL_BLEND); // Enable blending for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending function

    // Main loop
    while (!Window::isShouldClose()) { // Continue until the window should close
        Event::pullEvents(); // Poll for and process events

        // Check if the escape key is pressed
        if(Event::jpressed(GLFW_KEY_ESCAPE))
            Window::setShouldClose(true); // Set the window to close

        // Check if the left mouse button is clicked
        if(Event::jclicked(GLFW_MOUSE_BUTTON_1))
        {
            glClearColor(1.0f, 0.2467f, 0.3164f, 1.0f); // Change clear color to a different color
        }

        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

        shader->use(); // Use the loaded shader program
        texture->bind(); // Bind the loaded texture
        glBindVertexArray(VAO); // Bind the VAO
        glDrawArrays(GL_TRIANGLES, 0, 6); // Draw the rectangle as two triangles
        glBindVertexArray(0); // Unbind the VAO

        Window::swapBuffers(); // Swap the front and back buffers
    }

    // Clean up resources
    delete shader; // Delete the shader
    delete texture; // Delete the texture

    glDeleteBuffers(1, &VBO); // Delete the VBO
    glDeleteVertexArrays(1, &VAO); // Delete the VAO
    Window::terminate();
    System::Log::alert("Program ended");
    return 0;
}