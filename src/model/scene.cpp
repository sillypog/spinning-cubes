#include "./scene.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric> // accumulate

Scene::Scene() {
	entities.emplace_back(new Cube({-0.3f, 0.0f, 0.0f}));
	entities.emplace_back(new BRCube);

	std::cout << "Creating scene containing " << entities.size() << " shapes" << std::endl;
}

const vector<float> Scene::getVertices() const {
	// Modify this to put the vertices of all shapes into one list
	std::vector<float> allVertices;

	// Loop over the entities and put their vertices in the list
	int reserveSpace = std::accumulate(entities.begin(), entities.end(), 0, [](int accumulator, const std::unique_ptr<Entity> &entity){
		return accumulator + entity->getVertices().size();
	});
	allVertices.reserve(reserveSpace);

	for(auto &entity : entities) {
		allVertices.insert(allVertices.end(), entity->getVertices().begin(), entity->getVertices().end());
	}

	return allVertices;
}

const vector<int> Scene::getElements() const {
	// Modify this to put the elements of all shapes into one list
	std::vector<int> allElements;

	// Loop over all of the entities and add their elements to allElements
	// BUT offset each element by the number of vertices referenced at the start of this loop.
	int offset = 0, addition = 0;
	for (auto &entity : entities){
		const vector<int>& elements = entity->getElements();	// Because we use this 3 times in loop
		allElements.resize(allElements.size() + elements.size());

		std::transform(elements.begin(), elements.end(), std::next(allElements.begin(), offset), [&](int val){
			return val + addition;
		});

		offset = allElements.size(); // Write next set of values to the end of the vector
		addition += (entity->getVertices().size() / 8); // Each vertex has 8 array members
	}

	return allElements;
}
