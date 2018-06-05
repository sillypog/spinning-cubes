#include "./keyboard.h"

#include <iostream>

void Keyboard::handleInput(int key, int action){
	std::cout << "Keyboard event: " << key << " " << action << std::endl;
}

