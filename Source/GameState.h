#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <map>
#include <string>

using namespace std;

class IGameState
{
public:
	virtual void init() = 0;
	virtual void update(double elapsedTime) = 0;
};

class MainMenuState : public IGameState
{
public:
	virtual void init();
	virtual void update(double elapsedTime);
private:
	double timer;
};

class InnerGameState : public IGameState 
{
public:
	virtual void init();
	virtual void update(double elapsedTime);
private:
	double timer;
};

class GameOverState : public IGameState
{
public:
	virtual void init();
	virtual void update(double elapsedTime);
private:
	double timer;
};

class StateManager
{
public:
	// Initialize StateManager with currentState = null
	StateManager();

	// Delete game state as well as currentState
	~StateManager();

	// Add a new state to the state manager
	void addState(string id, IGameState *state);

	// Return the current game state
	IGameState * getCurrentState();

	// Change the current game state to newState and initialize newState
	void changeState(string newState);

private:
	map<string, IGameState*> stateDict;
	IGameState *currentState;
};


#endif