#define GLEW_STATIC
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "renderer/window.cpp"
#include "util/framecounter.cpp"

using namespace std;



void loop(){
	Framecounter framecounter;

	while(true){
		framecounter.tick();
	}
}

int main() {
	cout << "Spinning Boxes" << endl;

	Window window(640, 480);

	// loop();

	return 0;
}
