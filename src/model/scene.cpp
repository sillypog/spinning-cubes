#include "./scene.h"

#include <algorithm>
#include <iterator>
#include <iostream>

Scene::Scene() {
	entities.emplace_back(new Cube);
	entities.emplace_back(new BRCube);

	std::cout << "Creating scene containing " << entities.size() << " shapes" << std::endl;
}

const vector<float> Scene::getVertices() const {
	// Modify this to put the vertices of all shapes into one list
	std::vector<float> allVertices;

	// Obviously want to improve this with a loop
	allVertices.reserve(entities[0]->getVertices().size() + entities[1]->getVertices().size());
	allVertices.insert(allVertices.end(), entities[0]->getVertices().begin(), entities[0]->getVertices().end());
	allVertices.insert(allVertices.end(), entities[1]->getVertices().begin(), entities[1]->getVertices().end());

	return allVertices;
}

const vector<int> Scene::getElements() const {
	// Modify this to put the elements of all shapes into one list
	std::vector<int> allElements;

	// Loop over all of the entities and add their elements to allElements
	// BUT offset each element by the number of vertices referenced at the start of this loop.
	for (int i=0, offset=0, addition=0; i < entities.size(); i++){
		const vector<int>& elements = entities[i]->getElements();	// Because we use this 3 times in loop
		allElements.resize(allElements.size() + elements.size());

		std::transform(elements.begin(), elements.end(), std::next(allElements.begin(), offset), [&](int val){
			return val + addition;
		});

		offset = allElements.size(); // Write next set of values to the end of the vector
		addition += (entities[i]->getVertices().size() / 8); // Each vertex has 8 array members
	}

	return allElements;
}
