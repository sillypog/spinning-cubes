#ifndef FRAMECOUNTER_H
#define FRAMECOUNTER_H

#include <GLFW/glfw3.h>

class Framecounter {
	float t0;
	int frames;

public:

	Framecounter();
	~Framecounter();

	void tick();
};

#endif
