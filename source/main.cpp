#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "window/Window.h"              // Custom Window class
#include "window/Event.h"               // Custom Event class
#include "window/Camera.h"              // Custom Camera class

#include "graphics/Shader.h"            // Custom Shader class
#include "graphics/Texture.h"           // Custom Texture class
#include "graphics/Mesh.h"              // Custom Mesh class

#include "system/Log.h"                 // Custom Log class

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

int attrs[] = {
    3, 2, 0
};

int main()
{
    System::Log::alert("Program started");
    Window::initialize(WIDTH, HEIGHT, "Minecraft"); // Initialize the window with specified width, height, and title
    Event::initialize();                                // Initialize event handling

    // Load vertex and fragment shaders from specified paths
    Graphics::Shader* shader = Graphics::loadShader(RESOURCES_PATH "shaders/main.vert", RESOURCES_PATH "shaders/main.frag");
    if(shader == nullptr) // Check if shader loading failed
    {
        System::Log::error("Failed to load shaders");
        Window::terminate();
        return -1; // Exit with error code
    }

    // Load texture from specified path
    Graphics::Texture* texture = Graphics::loadTexture(RESOURCES_PATH "textures/test.png");
    if(texture == nullptr) // Check if texture loading failed
    {
        System::Log::error("Failed to load textures");
        delete shader; // Clean up shader resource
        Window::terminate(); // Terminate the window
        return -1; // Exit with error code
    }

    Graphics::Mesh* mesh = new Graphics::Mesh(vertices, 6, attrs);
    glClearColor(0.6f,0.62f,0.65f,1);

    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Main camera
    constexpr float defaultFOV = 70.0f;                         // Default value for FOV in camera
    constexpr auto defaultPosition = glm::vec3(0, 0, 1);  // Default value for position in camera
    auto* camera = new Windows::Camera(defaultPosition, glm::radians(defaultFOV));
    System::Log::alert("Initialized camera");


    glm::mat4 model(1.0f); // Initialize the matrix
    model = glm::translate(model, glm::vec3(0.5f, 0, 0));
    System::Log::alert("Initialized matrix");

    float lastTime = static_cast<float>(glfwGetTime());
    float delta = 0.0f; //
    float camX = 0.0f;
    float camY = 0.0f;  // C

    // Main loop
    while (!Window::isShouldClose())
    {

        constexpr float speed = 5;  // Camera movement speed
        const float currentTime = static_cast<float>(glfwGetTime());

        delta = currentTime - lastTime;
        lastTime = currentTime;

        if (Event::jpressed(GLFW_KEY_ESCAPE))
            Window::setShouldClose(true);

        if (Event::jpressed(GLFW_KEY_TAB))
            Event::toggleCursorLocked();

        if (Event::pressed(GLFW_KEY_W))
            camera->position += camera->front * delta * speed;

        if (Event::pressed(GLFW_KEY_S))
            camera->position -= camera->front * delta * speed;

        if (Event::pressed(GLFW_KEY_D))
            camera->position += camera->right * delta * speed;

        if (Event::pressed(GLFW_KEY_A))
            camera->position -= camera->right * delta * speed;


        if (Event::_cursorLocked){
            camY += -Event::deltaY / static_cast<float>(Window::height) * 2;
            camX += -Event::deltaX / static_cast<float>(Window::height) * 2;

            if (camY < -glm::radians(89.0f)){
                camY = -glm::radians(89.0f);
            }
            if (camY > glm::radians(89.0f)){
                camY = glm::radians(89.0f);
            }

            camera->rotation = glm::mat4(1.0f);
            camera->rotate(camY, camX, 0);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer

        shader->use();                                  // Use the loaded shader program
        shader->uniformMatrix("model", model);     // Load matrix to shader
        shader->uniformMatrix("projectionView", camera->getProjectionMatrix() * camera->getViewMatrix());
        texture->bind();                                // Bind the loaded texture
        mesh->draw(GL_TRIANGLES);

        Window::swapBuffers();                          // Swap the front and back buffers
        Event::pullEvents();
    }

    // Clean up resources
    delete shader; // Delete the shader
    delete texture; // Delete the texture
    delete mesh; // Delete the mesh

    Window::terminate();
    System::Log::alert("Program ended");
    return 0;
}