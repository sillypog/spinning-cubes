#include "./entity.h"

#include <utility>

Entity::Entity(vector<float> _v, vector<int> _e, string _t) : vertices(std::move(_v)), elements(std::move(_e)), texture(_t) {}

const vector<float>& Entity::getVertices() const {
	return vertices;
}

const vector<int>& Entity::getElements() const {
	return elements;
}

string Entity::getTexture(){
	return "assets/textures/" + texture;
}

int Entity::numElements() const {
	return elements.size();
}

glm::mat4 Entity::getTransform() const {
	return transform;
}
