#ifndef SQUARE_H
#define SQUARE_H

#include <vector>

#include "./entity.h"

using namespace std;

class Square : public Entity {
	/**
	* Once there is more than one cube,
	* it will probably be better for the cube to describe itself with
	* x, y, size
	* or
	* x, y, length, width, height
	*
	* Those values would get converted into OpenGL vertices on demand
	*/

public:
	Square();
};

#endif
