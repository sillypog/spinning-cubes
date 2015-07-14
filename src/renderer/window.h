#ifndef WINDOW_H
#define WINDOW_H

#include "./defines.h"
#include <GLFW/glfw3.h>

class Window {
	int width;
	int height;

	GLFWwindow* window;

public:

	Window(int _width, int _height);
	~Window();

	bool isClosing();
	void update();
};

#endif
