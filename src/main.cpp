#include <iostream>
#include <chrono>
#include <thread>

#include "renderer/window.h"
#include "renderer/renderer.h"
#include "util/framecounter.h"
#include "model/scene.h"

using namespace std;

void loop(Window &window, Renderer &renderer){
	Framecounter framecounter;

	while(!window.isClosing()){
		this_thread::sleep_for(chrono::milliseconds(10));
		window.poll();
		renderer.draw();
		framecounter.tick();
	}
}

int main() {
	cout << "Spinning Boxes" << endl;

	Window window(640, 480);
	Renderer renderer(window);

	Scene scene;
	renderer.createScene(scene);

	loop(window, renderer);

	return 0;
}
