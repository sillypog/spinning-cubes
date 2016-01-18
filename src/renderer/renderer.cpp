#include "./renderer.h"

Renderer::Renderer(Window& _window): window(_window) {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	shaderProgram.addVertexShader("assets/shaders/solid/vertex.glsl");
	shaderProgram.addFragmentShader("assets/shaders/solid/fragment.glsl");
	shaderProgram.link();
}

Renderer::~Renderer(){
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

/**
* Scene is passed by reference. This is important because the Scene contains
* a vector of unique pointers - attempting to pass by value causes an error because
* it attempts to copy the vector of unique_ptrs. Given that Scene could contain
* a lot of data, passing by reference makes more sense anyway.
*/
void Renderer::createScene(Scene& scene){
	const vector<float>& vertices = scene.getVertices();
	const vector<int>& elements = scene.getElements();

	numElements = sizeof(int) * elements.size();

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements, elements.data(), GL_STATIC_DRAW);

	shaderProgram.defineAttributes({{"position", 3}, {"color", 3}, {"texcoord", 2}});
}

void Renderer::draw(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

	window.swapBuffers();
}
