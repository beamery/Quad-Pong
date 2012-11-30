#include "Error.h"
#include "GameState.h"

using namespace std;

StateManager::StateManager() : currentState(nullptr) {}

StateManager::~StateManager() { delete currentState; }

void StateManager::addState(string id, IGameState *state)
{
	stateDict[id] = state;
}


IGameState * StateManager::getCurrentState()
{
	return currentState;
}

void StateManager::changeState(string newState)
{
	// If we give an invalid state, throw an error
	if (stateDict.count(newState) == 0)
		throw INVALID_STATE_ERROR;

	currentState = stateDict[newState];
	currentState->init();
}