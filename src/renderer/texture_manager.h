#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "opengl.h"
#include "texture.h"

class TextureManager {
	GLuint* textureBuffers = nullptr;	// When will this get released?
	std::unordered_map<std::string, Texture> textureData;

public:
	void loadTextureSet(std::unordered_set<std::string> textureNames);
	GLuint getBufferIdForTexture(const std::string textureName) const;
	void setTextureForDraw(const std::string textureName) const;
};

#endif
