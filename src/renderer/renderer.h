#ifndef RENDERER_H
#define RENDERER_H

#include "./opengl.h"
#include "./camera.h"
#include "./shader_program.h"
#include "./texture_manager.h"
#include "../io/window.h"
#include "../model/scene.h"

class Renderer {
	Window& window;	// Should store a reference to the window
	Scene& scene;	// Should store a reference to the scene to get shapes to draw
	Camera* camera;
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
