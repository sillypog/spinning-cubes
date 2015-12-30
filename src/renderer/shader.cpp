#include <iostream>
#include <fstream>
#include <sstream>

#include "./shader.h"

using namespace std;

Shader::Shader(string _filename, GLenum _type):filename(_filename), type(_type){
	cout << "Creating shader for: " << filename << endl;
	content = load(_filename);
	compile();
	checkStatus();
}

Shader::~Shader(){
	cout << "Destroying shader " << filename << endl;
	glDeleteShader(shader);
}

GLuint Shader::getShader(){
	return shader;	// Would it be better to return a reference?
}

string Shader::load(string filename){
	cout << "Loading file: " << filename << endl;

	ifstream data(filename);
	if (data.bad() || !data.is_open()){
		cerr << "Unable to open " << filename << endl;
		exit(EXIT_FAILURE);	// Better to use an exception and shutdown gracefully
	}

	stringstream buffer;
	buffer << data.rdbuf();

	data.close();

	return buffer.str();
}

void Shader::compile(){
	shader = glCreateShader(type);
	const char* shader_cStr = content.c_str(); // Have to convert to c pointer array to pass to function
	glShaderSource(shader, 1, &shader_cStr, NULL);
	glCompileShader(shader);
}

void Shader::checkStatus() const {
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE){
		cout << filename << " compiled successfully" << endl;
	} else {
		cout << filename << " compilation failed" << endl;
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		cout << buffer;
	}
}


