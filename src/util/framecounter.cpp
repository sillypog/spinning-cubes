#include <iostream>

#include <GLFW/glfw3.h>

#include "./framecounter.h"

using namespace std;

/**
* Need to have called glfwInit before this,
* otherwise glfwGetTime will not work.
*/
Framecounter::Framecounter() : t0(glfwGetTime()), frames(0) {}

Framecounter::~Framecounter(){
	float t1 = glfwGetTime();
	float dt = t1 - t0;
	float fps = frames/dt;
	float mspf = (dt * 1000) / frames;
	cout << "FPS: " << fps << " over " << dt << " seconds." << endl;
	cout << "MSPF: " << mspf << " over " << frames << " frames." << endl;
}

void Framecounter::tick(){
	frames++;
}
