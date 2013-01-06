#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "Error.h"

using namespace std;

class FontManager
{
public:
	FontManager(bool global);
	void loadFont(string path, string id);
	sf::Font * getFont(string id);
	static FontManager * get() { return globalFontManager; }

private:
	static FontManager *globalFontManager;
	map<string, sf::Font*> fontMap;
};


#endif