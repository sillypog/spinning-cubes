#include <GL/glew.h>

#include <iostream>

#include "./window.h"

using namespace std;

Window::Window(int _width, int _height) : width(_width), height(_height){
	glfwSetErrorCallback([](int error, const char* description){
		cout << "There was an error" << endl;
	});

	if (!glfwInit()){
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(width, height, "My Title", NULL, NULL);
	if (!window){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(0);

	// Setup GLEW to handle modern OpenGL functions
	glewExperimental = GL_TRUE;
	glewInit();

	cout << "Window created" << endl;
	cout << "OpenGL version supported by this platform" << glGetString(GL_VERSION) << endl;
}

Window::~Window(){
	cout << "Destroy Window" << endl;

	// Cleanup GLFW
	glfwDestroyWindow(window);

	glfwTerminate();
}

bool Window::isClosing(){
	return glfwWindowShouldClose(window);
}

void Window::update(){
	glfwPollEvents();
}

