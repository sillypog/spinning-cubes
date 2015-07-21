#ifndef SQUARE_H
#define SQUARE_H

class Square {
	/**
	* Once there is more than one cube,
	* it will probably be better for the cube to describe itself with
	* x, y, size
	* or
	* x, y, length, width, height
	*
	* Those values would get converted into OpenGL vertices on demand
	*/


	// Store vertices as a C++ std::array?
	float vertices[] {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f,	// tl
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	// tr
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	// br
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f	// bl
	};

	int elements {
		0, 1, 2, // tl, tr, br
        2, 3, 0  // br, bl, tl
	}

public:
	float[] getVertices();	// Is that the right syntax to return an array?
	int[] getElements();
};

#endif
