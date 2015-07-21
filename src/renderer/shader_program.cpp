#include <iostream>
#include <numeric>

#include "./shader_program.h"
#include "../util/deleter.cpp"

using namespace std;

ShaderProgram::ShaderProgram(){}

void ShaderProgram::addFragmentShader(string filename){
	unique_ptr<Shader> s(new Shader(filename, GL_FRAGMENT_SHADER));
	shaders.push_back(move(s));
}

void ShaderProgram::addVertexShader(string filename){
	unique_ptr<Shader> s(new Shader(filename, GL_VERTEX_SHADER));
	shaders.push_back(move(s));
}

void ShaderProgram::link(){
	shaderProgram = glCreateProgram();
	for (auto const &s:shaders){	// Have to use references here or unique_ptr copy constructor will be illegally invoked
		glAttachShader(shaderProgram, s->getShader());
	}
    glLinkProgram(shaderProgram);   // Saves changes
    glUseProgram(shaderProgram);    // Only one can be used at a time
}

// If this took all of the attributes at once, I wouldn't need to pass in total size and could have my running total as a local variable
// Can I pass in an array of tuples for this?
void ShaderProgram::defineAttributes(vector<pair<string, int>> attributes){
	// Can I use a std::algorithm to sum the total length of the attribute sizes? Need it for the 5th param
	// Would I need a std::vector (or std::array) for this?

	int totalAttributeLength = accumulate(attributes.begin(), attributes.end(), 0, [](int lhs, const pair<string, int> & rhs){
    	return lhs += rhs.second;
    });

    cout << "totalAttributeLength: " << totalAttributeLength << endl;

    int currentLength = 0;

	for(auto attributePair : attributes){
		cout << "currentLength: " << currentLength << endl;
		GLint attributeAddress = glGetAttribLocation(shaderProgram, attributePair.first.c_str());
		glVertexAttribPointer(attributeAddress, attributePair.second, GL_FLOAT, GL_FALSE, totalAttributeLength * sizeof(float), (void*)(currentLength * sizeof(float)));  // Better way to cast to void pointer?
		glEnableVertexAttribArray(attributeAddress);
		currentLength += attributePair.second;
	}
}

ShaderProgram::~ShaderProgram(){
	glDeleteProgram(shaderProgram);
}
