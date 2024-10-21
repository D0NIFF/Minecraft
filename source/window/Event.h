#ifndef EVENT_H
#define EVENT_H

#include "Window.h"

typedef unsigned int uint;

class Event {
public:
    static bool* _keys;
    static uint* _frames;
    static uint _current;

    static float deltaX;
    static float deltaY;
    static float x;
    static float y;
    static bool _cursorLocked;
    static bool _cursorStarted;

    static int initialize();
    static void pullEvents();

    static bool pressed(int keycode);
    static bool jpressed(int keycode);

    static bool clicked(int button);
    static bool jclicked(int button);
};


#endif //EVENT_H
