#ifndef RENDERER_H
#define RENDERER_H

#include "./opengl.h"
#include "./window.h"
//#include "./shader_program.h"

class Renderer {
	Window& window;	// Should store a reference to the window
	/*ShaderProgram shaderProgram;

	GLuint vao;
	GLuint vbo; // Vertex buffer object
	GLuint ebo;*/

public:
	Renderer(Window& _window);	// Need the Window reference to get GLFWwindow for swap buffers
	~Renderer();

	void draw();
};

#endif
