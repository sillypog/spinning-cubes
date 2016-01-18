#include "./scene.h"

#include <iostream>

Scene::Scene() {
	entities.emplace_back(new Cube);
	std::cout << "Creating scene containing " << entities.size() << " shapes" << std::endl;
}

const vector<float>& Scene::getVertices() const {
	return entities[0]->getVertices();
}

const vector<int>& Scene::getElements() const {
	return entities[0]->getElements();
}
