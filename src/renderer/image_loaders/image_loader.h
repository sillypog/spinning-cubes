#ifndef H_IMAGE_LOADER
#define H_IMAGE_LOADER

#include <fstream>
#include <string>

struct ImageData {
	int width, height;
	bool alpha;
	unsigned char* pixels;
};

class ImageLoadException {
	std::string message;
public:
	ImageLoadException(std::string m) : message(m) {}
	std::string getMessage() const{
		return message;
	}
};

class ImageLoader {
protected:
	std::string filename;
	std::ifstream source;

public:
	static ImageLoader* buildLoader(std::string filename);

	ImageLoader(std::string _filename);
	virtual ~ImageLoader();
	virtual ImageData extractImageData() = 0;
};

#endif
