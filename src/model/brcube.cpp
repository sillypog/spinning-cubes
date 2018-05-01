#include "./brcube.h"

BRCube::BRCube() : Entity({
	0.9f, -0.9f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 0
	0.7f, -0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // 1
	0.7f, -0.7f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 2
	0.9f, -0.7f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 3
	0.9f, -0.9f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, // 4
	0.7f, -0.9f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 5
	0.7f, -0.7f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 6
	0.9f, -0.7f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 7
	0.9f, -0.7f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // 8
	0.9f, -0.7f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 9
	0.9f, -0.9f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 10
	0.7f, -0.7f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 11
	0.7f, -0.9f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 12
	0.7f, -0.9f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 13
	0.7f, -0.9f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 14
	0.9f, -0.7f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 15
}, {
	0,  1,  2,  2,  3,  0,
	4,  5,  6,  6,  7,  4,
	8,  9, 10, 10,  4,  8,
	11, 2, 12, 12, 13, 11,
	10, 14, 5,  5,  4, 10,
	3,  2, 11, 11, 15,  3
}, {"puppy.png", "kitten.png"}) {
	std::cout << "BRCube is using default translation" << endl;
	glm::vec3 translation {0.0f, 0.0f, 0.0f};
	transform = glm::translate(transform, translation);
}

// The elements array assumes this is the second shape
// This works because it adds 16 to all of the element numbers,
// to account for the 16 elements from the 1st shape.
