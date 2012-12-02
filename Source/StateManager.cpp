#include "Error.h"
#include "GameState.h"

using namespace std;

StateManager *StateManager::globalStateManager = nullptr;

StateManager::StateManager(bool global) : 
	ChangeGameStateListener(), currentState(nullptr)
{
	if (global)
		StateManager::globalStateManager = this;
}


StateManager::~StateManager() { delete currentState; }

void StateManager::addState(string id, IGameState *state)
{
	stateDict[id] = state;
}


IGameState * StateManager::getCurrentState()
{
	return currentState;
}

void StateManager::changeState(string newState, bool init)
{
	// If we give an invalid state, throw an error
	if (stateDict.count(newState) == 0)
		throw INVALID_STATE_ERR;

	currentState = stateDict[newState];

	if (init)
		currentState->init();
}

void StateManager::onChangeGameState(ChangeGameStateEvtData *event)
{
	changeState(event->getNextState(), event->needsInit());
}

StateManager * StateManager::get()
{
	return StateManager::globalStateManager;
}

