#include "./square.h"

Square::Square() : vertices{
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f,	// tl
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	// tr
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	// br
	-0.5f, -0.5f, 1.0f, 1.0f, 1.0f	// bl
}, elements{
	0, 1, 2, // tl, tr, br
    2, 3, 0  // br, bl, tl
} {}

vector<float> Square::getVertices(){
	return vertices;	// Return a const reference?
}

vector<int> Square::getElements(){
	return elements;
}
