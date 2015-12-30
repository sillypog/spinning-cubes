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
	const vector<float>& getVertices() const;
	const vector<int>& getElements() const;
};

#endif
