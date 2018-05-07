#ifndef H_PNG_LOADER
#define H_PNG_LOADER

#include <string>
#include <png.h>

#include "image_loader.h"

class PngLoader : public ImageLoader {
	const unsigned int SIG_BYTES = 8;

	png_structp pngPtr = nullptr;
	png_infop infoPtr = nullptr;

	bool isPng();
public:
	PngLoader(std::string _filename);
	~PngLoader();
	ImageData extractImageData();
};

#endif
