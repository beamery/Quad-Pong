#ifndef PONG_H
#define PONG_H

#include "Actor.h"
#include "Views.h"
#include "Collision.h"
#include "Event.h"
#include <string>

class Volley : IEventListener
{
public:
	Volley(HumanView *h) : humanView(h) { init(); }
	void init();
	void reset();
	void update(double totalTime, double elapsedTime);
	virtual void processEvent(IEventData *e);

private:
	void onScore(ScoreEvtData *event);
	void onLaunchBall(LaunchBallEvtData *event);

	void resetPlayerPos(int player, Actor * &horiz, Actor * &vert);
	void createPlayer(int player, Actor	* &horiz, Actor * &vert);
	void makeBumpers();
	void resetBall();
	void makeBall();
	RelativeDir getRelDir(Actor *ball, Actor *paddle);

	HumanView *humanView;
	bool isReset;

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

	Actor *field;
};

class Match : IEventListener
{
public:
	Match(HumanView *h) : humanView(h) { init(); } 
	void init();
	void update(double totalTime, double elapsedTime);
	virtual void processEvent(IEventData *e);

private:
	void onMatchOver(MatchOverEvtData *event);
	
	HumanView *humanView;
	Volley *volley;
	Actor *scoreboard;
};

#endif