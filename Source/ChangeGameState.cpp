#include "Event.h"

////////////////////////////////////////////////////////////////////////////////
// Event Data
////////////////////////////////////////////////////////////////////////////////
ChangeGameStateEvtData::ChangeGameStateEvtData(const string nextState,
											   const string previousState,
											   bool init):
	IEventData(CHANGE_GAME_STATE, "Change Game State Event"),
	nextState(nextState), 
	previousState(previousState),
	init(init) {}


string ChangeGameStateEvtData::getNextState() { return nextState; }

string ChangeGameStateEvtData::getPreviousState() { return previousState; }

bool ChangeGameStateEvtData::needsInit() { return init; }


////////////////////////////////////////////////////////////////////////////////
// Event Listener
////////////////////////////////////////////////////////////////////////////////
void ChangeGameStateListener::processEvent(IEventData *e)
{
	switch(e->getEventType())
	{
	case CHANGE_GAME_STATE:
		onChangeGameState((ChangeGameStateEvtData*)e);
	}
}