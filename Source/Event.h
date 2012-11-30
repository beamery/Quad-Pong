#ifndef EVENT_H
#define EVENT_H

#include <string>

using namespace std;

enum EventType
{
	Change_Game_State_Event,

};


class IEventData
{
public:
	explicit IEventData(const float timeStamp = 0.0f): timeStamp(timeStamp) {}
	virtual ~IEventData() {}
	float getTimeStamp() const { return timeStamp; }
	string getEventName() const { return eventName; }

protected:
	const float timeStamp;
	string eventName;
};

class ChangeGameStateEvtData : public IEventData
{
public:
	static const EventType eventType = Change_Game_State_Event;
	explicit ChangeGameStateEvtData(const string stateName);
	string getStateName();

protected:
	string stateName;
	string eventName;
};


#endif
