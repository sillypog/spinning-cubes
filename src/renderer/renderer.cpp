#include "./renderer.h"

Renderer::Renderer(Window& _window): window(_window) {
	/*glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Make an element buffer to reuse vertices
    glGenBuffers(1, &ebo);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    */
}

Renderer::~Renderer(){
	/*glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);*/
}

void Renderer::draw(){
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // This is where we should bind buffers

    //glDrawElements(GL_TRIANGLES, sizeof(elements), GL_UNSIGNED_INT, 0);

    //glfwSwapBuffers(window);	// Need to change this so it gets the GLFWwindow from Window
    window.swapBuffers();
}
