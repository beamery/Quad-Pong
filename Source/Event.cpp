#include "Event.h"

IEventData::IEventData(EventType type, string eventName, const float timeStamp) : 
	timeStamp(timeStamp), eventType(type), eventName(eventName) {}

IEventData & IEventData::operator=(IEventData &event)
{
	IEventData *e = 
		new IEventData(event.getEventType(), event.getEventName(), event.getTimeStamp());
	return *e;
}