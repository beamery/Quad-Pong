#ifndef VIEWS_H
#define VIEWS_H

#include "Actor.h"
#include "Input.h"
#include "Event.h"

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
	HumanView(Actor * a = 0);
	virtual void update(double totalTime, double elapsedTime);

	// input handling
	KeyboardHandler *keyboardHandler;
	PointerHandler *pointerHandler;
	

	// rendering
	virtual void drawActor(Actor *a); // <-- Replace with drawing screen elements?
	virtual void drawText(/* params */);
	virtual void drawUI(/* params */);
	virtual void setCameraOffset(/* params */);

	virtual GameViewType getViewType() { return VIEW_HUMAN; }
	virtual Actor * getActor() { return actor; }
	virtual void attachActor(Actor *a) { actor = a; }

protected:
	Actor *actor;
};

#endif