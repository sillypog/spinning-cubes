#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

using namespace std;

class Entity {
// Need to make these protected?
	vector<float> vertices;
	vector<int> elements;
	string texture;

protected:
	Entity(vector<float> _v, vector<int> _e, string _t = "");

public:
	vector<float> getVertices();
	vector<int> getElements();
	string getTexture();
};

#endif
