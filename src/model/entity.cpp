#include "./entity.h"

#include <utility>

Entity::Entity(vector<float> _v, vector<int> _e) : vertices(std::move(_v)), elements(std::move(_e)) {}

const vector<float>& Entity::getVertices() const {
	return vertices;
}

const vector<int>& Entity::getElements() const {
	return elements;
}
