#include "Event.h"

EventManager *EventManager::globalEventManager = nullptr;

EventManager::EventManager(bool global, string name) : 
	name(name), activeQueue(0)
{
	if (global)
		EventManager::globalEventManager = this;
}

bool EventManager::addListener(IEventListener *listener)
{
	vector<IEventListener*> l = listeners[listener->getEventType()];

	// Check if the listener is already in the list of listeners
	for (auto iter = l.begin(); iter != l.end(); iter++)
	{
		if (listener == *iter)
		{
			cout << "Warning: duplicate listener" << endl;
			return false;
		}
	}
	// If it isn't, add it to the list
	listeners[listener->getEventType()].push_back(listener);
	return true;
}

bool EventManager::removeListener(IEventListener *listener)
{
	EventType t = listener->getEventType();

	bool removed = false;
	for (auto iter = listeners[t].begin(); iter != listeners[t].end(); iter++)
	{
		// If we find the listener, remove it.
		if (listener == *iter)
		{
			listeners[t].erase(iter);
			removed = true;
			break;
		}
	}
	return removed;

}

void EventManager::triggerEvent(IEventData *e)
{
	// Get the list of listeners for this event type
	vector<IEventListener*> list = listeners[e->getEventType()];
	
	// iterate through the list, processing the event for each listener
	for (auto i = list.begin(); i != list.end(); i++)
	{
		(*i)->processEvent(e);
	}
}


void EventManager::queueEvent(IEventData *e)
{
	eventQueue[activeQueue].push_back(e);
}

void EventManager::abortEvent(IEventData *e)
{
	for (auto i = eventQueue[activeQueue].begin(); i != eventQueue[activeQueue].end(); i++)
	{
		if (*i == e)
		{
			eventQueue[activeQueue].erase(i);
			break;
		}
	}
}

void EventManager::update()
{
	int	qToProcess = activeQueue;
	// Change the active queue in case more events are triggered.
	// Also clear new active queue.
	activeQueue = (activeQueue + 1) % 2;
	eventQueue[activeQueue].clear();

	// Go through each event in the queue
	while (!eventQueue[qToProcess].empty())
	{
		// Get the event and pop it off the front of the queue
		IEventData *e = eventQueue[qToProcess].front();
		eventQueue[qToProcess].pop_front();

		// Get the listeners for this event
		vector<IEventListener*> l = listeners[e->getEventType()];

		// Go through the listeners
		for (auto j = l.begin(); j != l.end(); j++)
		{
			// process the event
			(*j)->processEvent(e);
		}
	}
}


EventManager * EventManager::get()
{
	return EventManager::globalEventManager;
}
