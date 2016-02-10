/**
* Stores a list of all the models that need to be rendered.
*/
#ifndef SCENE_H
#define SCENE_H

#include "./entity.h"
#include "./cube.h"
#include "./tlcube.h"
#include "./brcube.h"


#include <memory>

class Scene {
	std::vector<std::unique_ptr<Entity>> entities;
public:
	Scene();
	const vector<float> getVertices() const;
	const vector<int> getElements() const;
};

#endif
