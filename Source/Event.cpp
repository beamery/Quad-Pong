#include "Event.h"
#include <SFML/System.hpp>

IEventData::IEventData(EventType type, string eventName, const float timeStamp) : 
	timeStamp(timeStamp), eventType(type), eventName(eventName) {}

IEventData & IEventData::operator=(IEventData &event)
{
	IEventData *e = 
		new IEventData(event.getEventType(), event.getEventName(), event.getTimeStamp());
	return *e;
}



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



void ChangeGameStateListener::processEvent(IEventData *e)
{
	switch(e->getEventType())
	{
	case CHANGE_GAME_STATE:
		onChangeGameState((ChangeGameStateEvtData*)e);
	}

}
