#ifndef VIEWS_H
#define VIEWS_H

#include "Actor.h"
#include "Input.h"
#include "Event.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

enum GameViewType
{
	VIEW_HUMAN,
};


class GameView
{
public:
	virtual void update(double totalTime, double elapsedTime) = 0;
};

class HumanView : GameView
{
public:
	// input handling
	KeyboardHandler *keyboardHandler;
	PointerHandler *pointerHandler;
	sf::RenderWindow *window;
	
	HumanView(sf::RenderWindow *w, Actor * a = 0);
	virtual void update(double totalTime, double elapsedTime);

	// rendering
	virtual void drawActor(Actor *a); // <-- Replace with drawing screen elements?
	virtual void drawText(string text, Vec2D<double> position, int size = 36);
	virtual void drawUI(/* params */);
	virtual void setCameraOffset(/* params */);

	virtual GameViewType getViewType() { return VIEW_HUMAN; }
	virtual Actor * getActor() { return actor; }
	virtual void attachActor(Actor *a) { actor = a; }

protected:
	Actor *actor;
};

#endif