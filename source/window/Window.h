#ifndef WINDOWS_H
#define WINDOWS_H

class GLFWwindow;

class Window {
public:
    static int width;
    static int height;
    static GLFWwindow* window;
    static int initialize(int width, int height, const char* title);
    static void terminate();

    static bool isShouldClose();
    static void setShouldClose(bool value);
    static void swapBuffers();
    static void setCursorMode(int mode);
};


#endif //WINDOWS_H
