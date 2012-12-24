#include "Texture.h"

TextureManager *TextureManager::globalTextureManager = nullptr;

TextureManager::TextureManager(bool global) 
{
	if (global)
		TextureManager::globalTextureManager = this;
}

void TextureManager::loadTexture(string path, string id)
{
	// load the image
	sf::Image imgData;
	if (!imgData.loadFromFile(path))
		throw INVALID_TEXTURE_PATH;

	// bind it and load it into the OpenGL context
	GLuint textureHandle;
	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glTexImage2D(
				 GL_TEXTURE_2D, 0, GL_RGBA,
				 imgData.getSize().x, imgData.getSize().y, 
				 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData.getPixelsPtr()
				);

	// set up extra parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// add texture to the database
	bm::Texture *tex = new bm::Texture(textureHandle, 
							   imgData.getSize().x, 
							   imgData.getSize().y);
	textureMap[id] = tex;
}

bm::Texture * TextureManager::getTexture(string id)
{
	if (textureMap.count(id) == 0)
		throw INVALID_TEXTURE_ERR;

	return textureMap[id];
}




