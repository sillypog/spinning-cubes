#include "./renderer.h"
#include "./texture.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer(Window& _window, Scene& _scene):
	window(_window),
	scene(_scene),
	textureManager(new TextureManager)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	shaderProgram.addVertexShader("assets/shaders/solid/vertex.glsl");
	shaderProgram.addFragmentShader("assets/shaders/solid/fragment.glsl");
	shaderProgram.link();
}

Renderer::~Renderer(){
	delete textureManager;

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
void Renderer::createScene(){
	const vector<float> vertices = scene.getVertices();
	const vector<int> elements = scene.getElements();

	numElements = sizeof(int) * elements.size();

	std::cout << vertices.size() << " vertices to render" << std::endl;
	std::cout << elements.size() << " elements to render" << std::endl;


	// I think I might have to have a vertex buffer for each cube
	// (probably owned by the Cube object)
	// and bind it at draw time
	// each one gets its own glDrawElements call
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements, elements.data(), GL_STATIC_DRAW);

	shaderProgram.defineAttributes({{"position", 3}, {"color", 3}, {"texcoord", 2}});

	// One time set up of texture uniforms to texture units
	glUniform1i(shaderProgram.uniform("tex0"), 0);
	glUniform1i(shaderProgram.uniform("tex1"), 1);

	// Load any texture files needed for the scene
	cout << "Getting set of textures." << endl;
	textureManager->loadTextureSet(scene.getTextures());
}

void Renderer::draw(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw each shape in the scene separately, applying the transform for each
	// For each shape, we need the scene to give us:
	// - The transform for the shape
	// - The number of elements to draw
	// We may need to keep track of the number of elements drawn so we can skip correctly

	int drawnElements = 0;

	for (auto &entity : scene.entities) {
		glUniformMatrix4fv(shaderProgram.uniform("trans"), 1, GL_FALSE, glm::value_ptr(entity->getTransform()));

		// Bind the appropriate textures into the appropriate texture units
		int i_activeTextureUnit = 0;
		for (auto &texture : entity->getTextures()) {
			switch (i_activeTextureUnit) {
				case 0: glActiveTexture(GL_TEXTURE0);
					break;
				case 1: glActiveTexture(GL_TEXTURE1);
					break;
				default:
					std::cout << "Only two texture units are supported" << std::endl;
			}
			textureManager->setTextureForDraw(texture);
			i_activeTextureUnit++;
		}

		int count = entity->numElements();
		// It took so long to work out how the 4th parameter to set the starting index
		// works. The offset needs to be cast to a pointer, and that apparently
		// only works certain ways.
		// https://www.opengl.org/discussion_boards/showthread.php/176296-glDrawElements-multiple-calls-one-index-array
		// https://stackoverflow.com/questions/23177229/how-to-cast-int-to-const-glvoid
		// https://stackoverflow.com/questions/8283714/what-is-the-result-of-null-int/8284829#8284829
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(drawnElements * sizeof(int)));
		drawnElements += count;
	}

	window.swapBuffers();
}
