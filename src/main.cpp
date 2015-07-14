#include <iostream>
#include <chrono>
#include <thread>

#include "renderer/window.h"
#include "util/framecounter.h"

using namespace std;

void loop(Window &window){
	Framecounter framecounter;

	int loops = 0;

	while(!window.isClosing() && loops < 1000){
		this_thread::sleep_for(chrono::milliseconds(10));
		window.update();
		framecounter.tick();
		loops++;
	}
}

int main() {
	cout << "Spinning Boxes" << endl;

	Window window(640, 480);

	loop(window);

	return 0;
}
