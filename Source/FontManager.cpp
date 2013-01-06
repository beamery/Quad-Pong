#include "FontManager.h"

FontManager *FontManager::globalFontManager = nullptr;

FontManager::FontManager(bool global)
{
	if (global)
		globalFontManager = this;
}

void FontManager::loadFont(string path, string id)
{
	sf::Font *font = new sf::Font();
	if (!font->loadFromFile(path))
		throw FONT_LOAD_ERR;

	fontMap[id] = font;
}

sf::Font * FontManager::getFont(string id)
{
	if (fontMap.count(id) == 0)
		throw INVALID_FONT_ERR;

	return fontMap[id];
}