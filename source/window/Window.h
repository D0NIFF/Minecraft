#ifndef WINDOWS_H
#define WINDOWS_H

class GLFWwindow;

class Window {
public:
    static GLFWwindow* window;
    static int initialize(int width, int height, const char* title);
    static void terminate();

    static bool isShouldClose();
    static void setShouldClose(bool value);
    static void swapBuffers();
};


#endif //WINDOWS_H
