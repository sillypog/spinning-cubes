#include "./entity.h"

#include <utility>

Entity::Entity(vector<float> _v, vector<int> _e, string _t) : vertices(std::move(_v)), elements(std::move(_e)), texture(_t) {}

vector<float> Entity::getVertices(){
	return vertices;	// Return a const reference?
}

vector<int> Entity::getElements(){
	return elements;
}

string Entity::getTexture(){
	return "assets/textures/" + texture;
}
