#include "./renderer.h"

Renderer::Renderer(Window& _window): window(_window) {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	shaderProgram.addVertexShader("assets/shaders/flat/vertex.glsl");
	shaderProgram.addFragmentShader("assets/shaders/flat/fragment.glsl");
	shaderProgram.link();
}

Renderer::~Renderer(){
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

/**
* This method is just temporary
* It would be better to build a model of the scene,
* itself containing instances of model classes.
*/
void Renderer::createScene(){
	// These values should come from model classes
	float vertices[] {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f,	// tl
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	// tr
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	// br
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f	// bl
	};

	int elements[] {
		0, 1, 2, // tl, tr, br
		2, 3, 0  // br, bl, tl
	};

	numElements = sizeof(elements);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements, elements, GL_STATIC_DRAW);

	shaderProgram.defineAttributes({{"position", 2}, {"color", 3}});
}

void Renderer::draw(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

	window.swapBuffers();
}
