#include "./cube.h"
#include <iostream>

const vector<float> Cube::templateVertices {
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 0
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 1
	 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 2
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 3
	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 4
	 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 5
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 6
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 7
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 8
	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 9
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 10
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 11
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 12
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 13
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 14
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 15
};

const vector<int> Cube::templateElements {
	0,  1,  2,  2,  3,  0,
	4,  5,  6,  6,  7,  4,
	8,  9, 10, 10,  4,  8,
	11, 2, 12, 12, 13, 11,
	10, 14, 5,  5,  4, 10,
	3,  2, 11, 11, 15,  3
};

Cube::Cube() : Entity(templateVertices, templateElements) {
	std::cout << "Cube is using default translation" << endl;
	glm::vec3 translation {0.0f, 0.0f, 0.0f};
	transform = glm::translate(transform, translation);
}

Cube::Cube(glm::vec3 translation) : Entity(templateVertices, templateElements) {
	std::cout << "Cube's x translation is " << translation.x << std::endl;
	transform = glm::translate(transform, translation);
}
