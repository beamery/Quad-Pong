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
	BASE_EVENT, CHANGE_GAME_STATE, MOUSE_POSITION, PADDLE_MOVE,
	BUMPER_PADDLE_COLL, BALL_PADDLE_COLL,
};

enum Direction
{
	UP, DOWN, LEFT, RIGHT
};

enum RelativeDir
{
	R_UP, R_DOWN, R_LEFT, R_RIGHT, R_UP_LEFT, R_UP_RIGHT, R_DOWN_LEFT, R_DOWN_RIGHT
};

typedef unsigned long ActorID;

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
						   bool init = true) :
		IEventData(CHANGE_GAME_STATE, "Change Game State Event"),
		nextState(nextState), previousState(previousState),
		init(init) {}

	// Return the state which is being changed TO
	string getNextState() { return nextState; }

	// Return the state which is being changed FROM
	string getPreviousState() { return previousState; }

	// Return whether or not to initialize the next state
	bool needsInit() { return init; }

protected:
	string previousState;
	string nextState;
	bool init;
};

////////////////////////////////////////////////////////////////////////////////
// Event class which contains data for paddle movements.
////////////////////////////////////////////////////////////////////////////////
class PaddleMoveEvtData : IEventData
{
public:
	PaddleMoveEvtData(int player, Direction dir, bool start = true) :
		IEventData(PADDLE_MOVE, "Paddle movement"),
		player(player), dir(dir), start(start) {}

	Direction getDirection() { return dir; } 
	int getPlayer() { return player; } 
	bool isStarting() { return start; }
	void setStart(bool s) { start = s; }

protected:
	Direction dir;
	int player;
	bool start;
};

////////////////////////////////////////////////////////////////////////////////
// Event class which contains data for bumper-paddle collisions.
////////////////////////////////////////////////////////////////////////////////
class BumperPaddleCollEvtData : IEventData
{
public:
	BumperPaddleCollEvtData(ActorID bumper, ActorID paddle) :
		IEventData(BUMPER_PADDLE_COLL, "Bumper paddle collision"),
		bumper(bumper), paddle(paddle) {}

	ActorID getBumper() { return bumper; }
	ActorID getPaddle() { return paddle; }

private:
	ActorID bumper;
	ActorID paddle;
};

////////////////////////////////////////////////////////////////////////////////
// Event class which contains data for ball-paddle collisions.
////////////////////////////////////////////////////////////////////////////////
class BallPaddleCollEvtData : IEventData
{
public:
	BallPaddleCollEvtData(ActorID paddle, RelativeDir r) :
		IEventData(BALL_PADDLE_COLL, "Ball paddle collision"),
		paddle(paddle), relDir(r) {}

	ActorID getPaddle() { return paddle; }
	RelativeDir getRelDir() { return relDir; }

private:
	ActorID paddle;
	RelativeDir relDir;
};

//////////////////////////////// EVENT LISTENER ////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Base event listener interface
////////////////////////////////////////////////////////////////////////////////
class IEventListener
{
public:
	IEventListener & operator=(IEventListener &iel) { return iel; }
	virtual void processEvent(IEventData *e) = 0;
};


////////////////////////////////////////////////////////////////////////////////
// Classes which inherit from this class are notified whenever a 
// CHANGE_GAME_STATE event is triggered.
////////////////////////////////////////////////////////////////////////////////
class ChangeGameStateListener : IEventListener
{
public:
	ChangeGameStateListener() {}
	virtual void processEvent(IEventData *e);
};


////////////////////////////////////////////////////////////////////////////////
// Classes which inherit from this class are notified whenever a 
// PADDLE_MOVE event is triggered.
////////////////////////////////////////////////////////////////////////////////
class PaddleMoveListener : public IEventListener
{
public:
	PaddleMoveListener() {}
	virtual void processEvent(IEventData *e);
};

////////////////////////////////////////////////////////////////////////////////
// Classes which inherit from this class are notified whenever a 
// BUMPER_PADDLE_COLL event is triggered.
////////////////////////////////////////////////////////////////////////////////
class BumperPaddleListener : public IEventListener
{
public:
	BumperPaddleListener() {}
	virtual void processEvent(IEventData *e);
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
	bool addListener(IEventListener *listener, EventType type);

	// Remove an event listener for the corresponding event type
	bool removeListener(IEventListener *listener, EventType type);

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
