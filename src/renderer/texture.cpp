#include "./texture.h"

#include <fstream>
#include <iostream>

#include "image_loaders/png_loader.h"

Texture::Texture(const std::string &filename){
	PngLoader imageLoader("assets/textures/" + filename);
	ImageData imageData = imageLoader.extractImageData();

	width = imageData.width;
	height = imageData.height;
	alpha = imageData.alpha;
	data = reinterpret_cast<GLubyte*>(imageData.pixels);

	std::cout << "Outcome of loading " << filename << ": " << (imageData.success ? "success" : "fail") << std::endl;
	if (imageData.success){
		std::cout << filename << ": " << width << "x" << height << ", alpha: " << alpha << std::endl;
	} else {
		// Assign a placeholder texture
		width = 2;
		height = 2;
		data = new GLubyte[RGB_BYTES * width * height] {
			255, 255, 255, 0, 0, 0,
			0, 0, 0, 255, 255, 255
		};
	}
}

Texture::~Texture() {
	delete [] data;
}

GLuint Texture::getBufferId() const {
	return bufferId;
}

void Texture::setBufferId(GLuint id) {
	bufferId = id;
}

bool Texture::hasAlpha() const {
	return alpha;
}

int Texture::getWidth() const {
	std::cout << "Width " << width << std::endl;
	return width;
}

int Texture::getHeight() const {
	std::cout << "Height " << height << std::endl;
	return height;
}

const GLubyte* Texture::getDataPointer() const {
	std::cout << "Data ";
	for (int i = 0; i < 20; i++) {
		std::cout << data[i];
	}
	std::cout << "..." << std::endl;
	return data;
}



