#ifndef H_PNG_LOADER
#define H_PNG_LOADER

#include <fstream>
#include <string>
#include <png.h>

struct ImageData {
	int width, height;
	bool alpha, success = false;
	unsigned char* pixels;
};

class PngLoader {
	const unsigned int SIG_BYTES = 8;

	std::string filename;
	std::ifstream source;
	png_structp pngPtr = nullptr;
	png_infop infoPtr = nullptr;

	bool isPng();
public:
	PngLoader(std::string _filename);
	~PngLoader();
	/*
	Pixels will be put on the heap in the loader, we just need to grab the location.
	Caller will have to cast to appropriate type.

	Hmm, we have to get width, height and alpha too.
	Maybe this should return an image data struct.
	*/
	ImageData extractImageData();
};

#endif
