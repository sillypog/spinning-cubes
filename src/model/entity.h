#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

using namespace std;

class Entity {
// Need to make these protected?
	vector<float> vertices;
	vector<int> elements;

protected:
	Entity(vector<float> _v, vector<int> _e);

public:
	vector<float> getVertices() const;
	vector<int> getElements() const;
};

#endif
