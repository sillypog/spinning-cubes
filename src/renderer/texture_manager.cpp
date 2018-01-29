#include "texture_manager.h"

#include <iostream>

#include "texture.h"

void TextureManager::loadTextureSet(std::unordered_set<std::string> textureNames){
	// Create appropriate number of texture buffers
	int numBuffers = textureNames.size();
	std::cout << "Creating " << numBuffers << " texture buffers" << std::endl;
	delete [] textureBuffers;
	textureBuffers = new GLuint[numBuffers];
	glGenTextures(numBuffers, textureBuffers);	// Shouldn't these be deleted eventually?

	// Load data for each texture
	textureData.clear();
	for (auto textureName : textureNames) {
		std::cout << "Loading " << textureName << " data" << std::endl;
		textureData.emplace(textureName, textureName);
	}

	// Load texture data into buffer
	GLuint nextBufferId = 0;
	for (auto &texturePair : textureData) {
		// Get the texture from the pair
		Texture &texture = texturePair.second;
		// Assume GL_TEXTURE0 is active, we'll just render one texture per draw
		glBindTexture(GL_TEXTURE_2D, textureBuffers[nextBufferId]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, texture.hasAlpha() ? GL_RGBA : GL_RGB, texture.getWidth(), texture.getHeight(), 0, texture.hasAlpha() ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, texture.getDataPointer());

		// Store a lookup for each texture name to that buffer
		texture.setBufferId(nextBufferId++);
	}
}

GLuint TextureManager::getBufferIdForTexture(std::string textureName) {
	auto result = textureData.find(textureName);	// Hopefully this doesn't copy the result into the iterator
	if (result == textureData.end()) {
		std::cout << "No texture named " << textureName << " found." << std::endl;
		return -1;	// Should probably throw exception
	} else {
		Texture &texture = result->second;
		return texture.getBufferId();
	}
}

void TextureManager::setTextureForDraw(std::string textureName) {
	GLuint bufferId = getBufferIdForTexture(textureName);
	glBindTexture(GL_TEXTURE_2D, textureBuffers[bufferId]);
}
