#include "./scene.h"

#include <iostream>

Scene::Scene() : entities{new Cube} {
	//std::cout << "Creating scene containing " << cube.getElements().size() << std::endl;
}

const vector<float>& Scene::getVertices() const {
	return entities[0]->getVertices();
}

const vector<int>& Scene::getElements() const {
	return entities[0]->getElements();
}
