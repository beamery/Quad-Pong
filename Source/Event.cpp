#include "Event.h"

ChangeGameStateEvtData::ChangeGameStateEvtData(const string stateName) :
	stateName(stateName)
{
	eventName = "Change Game State Event";
}

string ChangeGameStateEvtData::getStateName() { return stateName; }


