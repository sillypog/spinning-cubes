#ifndef SQUARE_H
#define SQUARE_H

#include <vector>

using namespace std;

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
	vector<float> vertices;
	vector<int> elements;

public:
	Square();
	vector<float> getVertices();
	vector<int> getElements();
};

#endif
