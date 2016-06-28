#ifndef CUBE_H
#define CUBE_H

#include "./entity.h"

class Cube : public Entity {
	const static vector<float> templateVertices;
	const static vector<int> templateElements;

public:
	Cube();
};

#endif
