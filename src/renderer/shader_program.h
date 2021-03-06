#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "./opengl.h"
#include "./shader.h"

using namespace std;

class ShaderProgram {
	vector<unique_ptr<Shader>> shaders;	// Use vector<unique_ptr<Shader>> instead

	GLuint shaderProgram;

public:
	ShaderProgram();
	~ShaderProgram();
	void addFragmentShader(string filename);
	void addVertexShader(string filename);
	void link();
	// Convert this to a method that takes an array of all attributes
	void defineAttributes(vector<pair<string, int>> attributes);	// Supply these in order
	GLint uniform(const char* uniform);
};

#endif
