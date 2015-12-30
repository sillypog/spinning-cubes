#include "./entity.h"

#include <utility>

Entity::Entity(vector<float> _v, vector<int> _e) : vertices(std::move(_v)), elements(std::move(_e)) {}

vector<float> Entity::getVertices() const {
	return vertices;	// Return a const reference?
}

vector<int> Entity::getElements() const {
	return elements;
}