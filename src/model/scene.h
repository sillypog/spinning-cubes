/**
* Stores a list of all the models that need to be rendered.
*/
#ifndef SCENE_H
#define SCENE_H

#include "./entity.h"
#include "./cube.h"
#include "./brcube.h"

#include <unordered_set>
#include <memory>
#include <string>

class Scene {
public:
	std::vector<std::unique_ptr<Entity>> entities; // Made public to test rendering each entity
	Scene();
	const vector<float> getVertices() const;
	const vector<int> getElements() const;
	const std::unordered_set<std::string> getTextures() const;
};

#endif
