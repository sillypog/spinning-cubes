#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "./opengl.h"

using namespace std;

class Shader {

	string filename;
	string content;
	GLenum type;
	GLuint shader;

	string load(string filename);
	void compile();
	void checkStatus() const;

public:
	Shader(string _filename, GLenum _type);
	~Shader();
	GLuint getShader();
};

#endif
