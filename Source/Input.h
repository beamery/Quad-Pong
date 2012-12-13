#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <SFML/Window.hpp>

using namespace sf;

class KeyboardHandler
{
public:
	void onKeyDown(Event e);
	void onKeyUp(Event e);
	static const char * getKeyName(const sf::Keyboard::Key key);
};

class PointerHandler
{
public:
	void onPointerMove(Event e, Window &w);
	void onPointerButtonDown(Event e);
	void onPointerButtonUp(Event e);
	void onWheelMove(Event e);
	static const char * getButtonName(const sf::Mouse::Button button);
};



#endif 