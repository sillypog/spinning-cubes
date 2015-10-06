#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "./opengl.h"

using namespace std;

class Texture {
	int width, height;
	bool alpha;
	GLubyte* data;

	bool loadPNGImage(string filename, int& outWidth, int& outHeight, bool& outHasAlpha, GLubyte** outData);

public:
	Texture(string filename);

	// Need a destructor to clear the data member?
};

#endif
