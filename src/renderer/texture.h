#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "./opengl.h"

class Texture {
	const int RGB_BYTES = 3;
	int width, height;
	bool alpha;
	GLubyte* data;
	GLuint bufferId;

public:
	Texture(const std::string &filename);
	~Texture();
	GLuint getBufferId() const;
	void setBufferId(GLuint id);
	bool hasAlpha() const;
	int getWidth() const;
	int getHeight() const;
	const GLubyte* getDataPointer() const;
};

#endif
