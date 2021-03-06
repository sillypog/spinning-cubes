#ifndef RENDERER_H
#define RENDERER_H

#include "./opengl.h"
#include "./window.h"
#include "./shader_program.h"
#include "./texture_manager.h"
#include "../model/scene.h"

class Renderer {
	Window& window;	// Should store a reference to the window
	Scene& scene;	// Should store a reference to the scene to get shapes to draw
	ShaderProgram shaderProgram;
	TextureManager* textureManager;

	GLuint vao;
	GLuint vbo; // Vertex buffer object
	GLuint ebo;

	int numElements;

public:
	Renderer(Window& _window, Scene& _scene);	// Need the Window reference to get GLFWwindow for swap buffers
	~Renderer();

	void createScene();
	void draw();
};

#endif
