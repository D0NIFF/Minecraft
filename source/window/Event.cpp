//
// Created by doniff on 10/20/2024.
//

#include "Event.h"

#include <GLFW/glfw3.h>
#include <cstring>

#include "Window.h"

bool* Event::_keys;
uint* Event::_frames;
uint Event::_current = 0;
float Event::deltaX = 0.0f;
float Event::deltaY = 0.0f;
float Event::x = 0.0f;
float Event::y = 0.0f;
bool Event::_cursorLocked = false;
bool Event::_cursorStarted = false;

#define _MOUSE_BUTTONS 1024

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos){
	if (Event::_cursorStarted){
		Event::deltaX += xpos-Event::x;
		Event::deltaY += ypos-Event::y;
	}
	else {
		Event::_cursorStarted = true;
	}
	Event::x = xpos;
	Event::y = ypos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode){
	if (action == GLFW_PRESS){
		Event::_keys[_MOUSE_BUTTONS+button] = true;
		Event::_frames[_MOUSE_BUTTONS+button] = Event::_current;
	}
	else if (action == GLFW_RELEASE){
		Event::_keys[_MOUSE_BUTTONS+button] = false;
		Event::_frames[_MOUSE_BUTTONS+button] = Event::_current;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS){
		Event::_keys[key] = true;
		Event::_frames[key] = Event::_current;
	}
	else if (action == GLFW_RELEASE){
		Event::_keys[key] = false;
		Event::_frames[key] = Event::_current;
	}
}

int Event::initialize(){
	GLFWwindow* window = Window::window;
	_keys = new bool[1032];
	_frames = new uint[1032];

	memset(_keys, false, 1032 * sizeof(bool));
	memset(_frames, 0, 1032 * sizeof(uint));

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	return 0;
}

bool Event::pressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode];
}

bool Event::jpressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return _keys[keycode] && _frames[keycode] == _current;
}

bool Event::clicked(int button){
	int index = _MOUSE_BUTTONS+button;
	return _keys[index];
}

bool Event::jclicked(int button){
	int index = _MOUSE_BUTTONS+button;
	return _keys[index] && _frames[index] == _current;
}

void Event::pullEvents(){
	_current++;
	deltaX = 0.0f;
	deltaY = 0.0f;
	glfwPollEvents();
}