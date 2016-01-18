/**
* Stores a list of all the models that need to be rendered.
*/
#ifndef SCENE_H
#define SCENE_H

#include "./entity.h"
#include "./cube.h"

class Scene {
	std::vector<Entity*> entities;
	//Cube cube;
public:
	Scene();
	const vector<float>& getVertices() const;
	const vector<int>& getElements() const;
};

#endif
