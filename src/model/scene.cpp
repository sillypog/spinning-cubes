#include "./scene.h"

#include <iostream>

Scene::Scene() {
	entities.emplace_back(new TLCube);
	entities.emplace_back(new BRCube);

	std::cout << "Creating scene containing " << entities.size() << " shapes" << std::endl;
}

const vector<float> Scene::getVertices() const {
	// Modify this to put the vertices of all shapes into one list
	// return entities[0]->getVertices();

	std::vector<float> allVertices;

	// Obviously want to improve this with a loop
	allVertices.reserve(entities[0]->getVertices().size() + entities[1]->getVertices().size());
	allVertices.insert(allVertices.end(), entities[0]->getVertices().begin(), entities[0]->getVertices().end());
	allVertices.insert(allVertices.end(), entities[1]->getVertices().begin(), entities[1]->getVertices().end());

	return allVertices;
}

const vector<int> Scene::getElements() const {
	// Modify this to put the elements of all shapes into one list
	//return entities[0]->getElements();

	std::vector<int> allElements;

	allElements.reserve(entities[0]->getElements().size() + entities[1]->getElements().size());
	allElements.insert(allElements.end(), entities[0]->getElements().begin(), entities[0]->getElements().end());
	allElements.insert(allElements.end(), entities[1]->getElements().begin(), entities[1]->getElements().end());

	return allElements;
}
