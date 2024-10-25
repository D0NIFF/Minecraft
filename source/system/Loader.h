#ifndef PNGLOADER_H
#define PNGLOADER_H

namespace System {

class Loader {
public:
    static int loadPng(const char* fileName, int* width, int* height);
};

} // System

#endif //PNGLOADER_H
