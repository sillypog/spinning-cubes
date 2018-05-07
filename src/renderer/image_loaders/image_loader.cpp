#include "image_loader.h"
#include "png_loader.h"

ImageLoader* ImageLoader::buildLoader(std::string filename) {
	// Use filename to guess type, but only supports png for now
	return new PngLoader(filename);
}

ImageLoader::ImageLoader(std::string _filename) : filename(_filename) {
	source.open(filename, std::ios::binary);
}

ImageLoader::~ImageLoader() {}
