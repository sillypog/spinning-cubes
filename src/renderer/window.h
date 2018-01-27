#ifndef WINDOW_H
#define WINDOW_H

#include "./opengl.h"

class Window {
	int width;
	int height;

	GLFWwindow* window;

public:

	Window(int _width, int _height);
	~Window();

	bool isClosing() const;
	void poll();
	void swapBuffers();
};

#endif
