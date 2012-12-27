#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <map>
#include <string>
#include <vector>
#include "Event.h"
#include "Views.h"

using namespace std;

class IGameState
{
public:
	virtual void init() = 0;
	virtual void update(double totalTime, double elapsedTime) = 0;
	HumanView * getHumanView() { return humanView; }

protected:
	HumanView *humanView;
};

class MainMenuState : public IGameState
{
public:
	virtual void init();
	virtual void update(double totalTime, double elapsedTime);
private:
	double timer;
};

class InnerGameState : public IGameState 
{
public:
	virtual void init();
	virtual void update(double totalTime, double elapsedTime);
private:
	virtual void bindKeys();
	virtual void createPlayer(int player, Actor	* &horiz, Actor * &vert);
	virtual void makeBumpers();

	double timer;
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
};

class GameOverState : public IGameState
{
public:
	virtual void init();
	virtual void update(double totalTime, double elapsedTime);
private:
	double timer;
};

class StateManager : public IEventListener	
{
public:
	// Get global state manager
	static StateManager * get();

	// Initialize StateManager with currentState = null
	StateManager(bool global);

	// Delete game state as well as currentState
	~StateManager();

	// Add a new state to the state manager
	void addState(string id, IGameState *state);

	// Return the current game state
	IGameState * getCurrentState();

	// Change the current game state to newState and initialize newState
	void changeState(string newState, bool init = true);

	// Overrides IEventListener::processEvent
	virtual void processEvent(IEventData *e);

	// Process game state change events
	void onChangeGameState(ChangeGameStateEvtData *event);

private:
	static StateManager *globalStateManager;

	map<string, IGameState*> stateDict;
	IGameState *currentState;
};


#endif