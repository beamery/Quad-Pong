#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include "Error.h"

using namespace std;

enum EventType
{
	BASE_EVENT, CHANGE_GAME_STATE, MOUSE_POSITION,
};


////////////////////////////////// EVENT DATA //////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Base event interface
////////////////////////////////////////////////////////////////////////////////
class IEventData
{
public:
	IEventData(EventType type = BASE_EVENT, 
			   string eventName = "Base Event",
			   const float timeStamp = 0.0f);

	virtual ~IEventData() {}
	IEventData & operator=(IEventData &event);
	float getTimeStamp() const { return timeStamp; }
	string getEventName() const { return eventName; }
	EventType getEventType() const { return eventType; }

protected:
	const EventType eventType;
	const float timeStamp;
	const string eventName;
};

////////////////////////////////////////////////////////////////////////////////
// Event class which contains data for game state changes
////////////////////////////////////////////////////////////////////////////////
class ChangeGameStateEvtData : IEventData
{
public:
	ChangeGameStateEvtData(const string nextState, 
						   const string previousState, 
						   bool init = true);

	// Return the state which is being changed TO
	string getNextState();

	// Return the state which is being changed FROM
	string getPreviousState();

	// Return whether or not to initialize the next state
	bool needsInit();

protected:
	string previousState;
	string nextState;
	bool init;
};

////////////////////////////////////////////////////////////////////////////////
// Event class which contains data for mouse movements
////////////////////////////////////////////////////////////////////////////////
class MousePositionEvtData : IEventData
{
public:
	MousePositionEvtData(int x, int y);
	int getX() { return x; }
	int getY() { return y; }
protected:
	int x, y;
};


//////////////////////////////// EVENT LISTENER ////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Base event listener interface
////////////////////////////////////////////////////////////////////////////////
class IEventListener
{
public:
	IEventListener(EventType eventType = BASE_EVENT) : eventType(eventType) {}
	IEventListener & operator=(IEventListener &iel) { return iel; }
	const EventType getEventType() { return eventType; }
	virtual void processEvent(IEventData *e) = 0;

protected:
	const EventType eventType;
};


////////////////////////////////////////////////////////////////////////////////
// Classes which inherit from this class are notified whenever a 
// CHANGE_GAME_STATE event is triggered.
////////////////////////////////////////////////////////////////////////////////
class ChangeGameStateListener : protected IEventListener
{
public:
	ChangeGameStateListener() : IEventListener(CHANGE_GAME_STATE) {}
	virtual void processEvent(IEventData *e);
	virtual void onChangeGameState(ChangeGameStateEvtData *event) = 0;
};

////////////////////////////////////////////////////////////////////////////////
// Classes which inherit from this class are notified whenever a 
// MOUSE_POSITION event is triggered.
////////////////////////////////////////////////////////////////////////////////
class MousePositionListener : protected IEventListener
{
public:
	MousePositionListener() : IEventListener(MOUSE_POSITION) {}
	virtual void processEvent(IEventData *e);
	virtual void onMouseMove(MousePositionEvtData *event) = 0;
};



//////////////////////////////// EVENT MANAGER /////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Class used to facilitate the sending of events between different components
// of the game.
////////////////////////////////////////////////////////////////////////////////
class EventManager
{
public:

	explicit EventManager(bool global, string name = "");
	~EventManager();

	string getName() { return name; }

	// Add an event listener for the correspoding event type
	bool addListener(IEventListener *listener);

	// Remove an event listener for the corresponding event type
	bool removeListener(IEventListener *listener);

	// Immediately fire off an event. This bypasses the event queue.
	void triggerEvent(IEventData *e);

	// Add an event to the event queue. This will be processed on the next
	// call to update(). This should be preferred over triggerEvent(), except
	// for in extreme cases.
	void queueEvent(IEventData *e);

	// Finds the next instance of this event, and removes it from the event queue
	void abortEvent(IEventData *e);

	// Processes events in the event queue on a FIFO basis.
	void update();

	static EventManager* get();

private:
	string name;
	map< EventType, vector<IEventListener*> > listeners;
	
	// maintain two event queues to avoid the case in which events trigger
	// other events which are processed in the same update().
	list<IEventData*> eventQueue[2];
	int activeQueue;

	static EventManager *globalEventManager;
};
#endif
