#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class Entity {
// Need to make these protected?
	vector<float> vertices;
	vector<int> elements;

protected:
	glm::mat4 transform;

	// Modify this to take a (x,y,z) center struct (and a scale value)
	// A cube could be created as Cube({-0.2, 0, 0}, 1)
	// It would then construct a matrix from the position and scale info
	// and use this to pass a modified version of its vertices to the parent entity
	Entity(vector<float> _v, vector<int> _e);

public:
	const vector<float>& getVertices() const;
	const vector<int>& getElements() const;
};

#endif
