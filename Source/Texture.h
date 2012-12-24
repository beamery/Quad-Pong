#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML/OpenGL.hpp>
#include <map>
#include <string>
#include "Error.h"
#include <SFML/OpenGL.hpp>
#include <SFML\Graphics.hpp>

using namespace std;

namespace bm
{
	struct Texture
	{
		GLuint id;
		double width, height;
		Texture(GLuint id, double width, double height) :
			id(id), width(width), height(height) {}
	};
};

class TextureManager
{
public:
	TextureManager(bool global);
	void loadTexture(string path, string id);
	bm::Texture * getTexture(string id);
	static TextureManager * get() { return globalTextureManager; }

private:
	map<string, bm::Texture *> textureMap;
	static TextureManager *globalTextureManager;
};


#endif