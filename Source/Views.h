#ifndef VIEWS_H
#define VIEWS_H

#include "Actor.h"
#include "Input.h"

enum GameViewType
{
	VIEW_HUMAN,
};


class View
{
public:
	virtual void update(double totalTime, double elapsedTime) = 0;
};

class HumanView : View
{
public:
	HumanView();
	virtual void update(double totalTime, double elapsedTime);

	// input handling
	KeyboardHandler *keyboardHandler;
	PointerHandler *pointerHandler;
	

	// rendering
	virtual void drawObject(/* params */); // <-- Replace with drawing screen elements?
	virtual void drawText(/* params */);
	virtual void drawUI(/* params */);
	virtual void setCameraOffset(/* params */);

	virtual GameViewType getViewType() { return VIEW_HUMAN; }
	virtual void attachActor(Actor *a) { actor = a; }

protected:
	Actor *actor;
};




#endif