#ifndef PONG_H
#define PONG_H

#include "Actor.h"
#include "Views.h"
#include "Collision.h"
#include "Event.h"

class Volley
{
public:
	Volley(HumanView *h) : humanView(h) { init(); }
	void init();
	void reset();
	void update(double totalTime, double elapsedTime);

private:
	void resetPlayerPos(int player, Actor * &horiz, Actor * &vert);
	void createPlayer(int player, Actor	* &horiz, Actor * &vert);
	void makeBumpers();
	void resetBallPos();
	void makeBall();
	RelativeDir getRelDir(Actor *ball, Actor *paddle);

	HumanView *humanView;

	vector<Actor *> paddles;
	vector<Actor *> bumpers;
	Actor *p1Vert;
	Actor *p1Horiz;
	Actor *p2Vert;
	Actor *p2Horiz;

	Actor *bumperBL;
	Actor *bumperTL;
	Actor *bumperBR;
	Actor *bumperTR;

	Actor *ball;
};

class Match
{
public:
	Match(HumanView *h) : humanView(h) { init(); } 
	void init();
	void update(double totalTime, double elapsedTime);

private:
	HumanView *humanView;
	Volley *volley;
};

#endif