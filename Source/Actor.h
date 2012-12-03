#ifndef ACTOR_H
#define ACTOR_H

#include <map>
#include <string>
#include "tinyxml2.h"

using namespace std;

typedef tinyxml2::XMLElement XMLElement;
typedef tinyxml2::XMLDocument XMLDoc;
typedef tinyxml2::XMLAttribute XMLAttrib;


//////////////////// ACTOR COMPONENT ////////////////////


enum ComponentType
{
	BASE_COMPONENT, VISUAL,
};

class ActorComponent
{
	friend class ActorFactory;


public:
	virtual ~ActorComponent() {}
	virtual void init(XMLElement *xmlData) {}
	virtual void postInit() {}
	virtual void update(double elapsedTime) {}
	virtual ComponentType getComponentType() { return BASE_COMPONENT; }
};


class VisualComponent : ActorComponent
{
	// METHOD STUBS
	// TODO: override
	virtual ~VisualComponent() {}
	virtual void init(XMLElement *xmlData) {}
	virtual void postInit() {}
	virtual void update(double elapsedTime) {}
	virtual ComponentType getComponentType() { return VISUAL; }
};


//////////////////// ACTOR ////////////////////

typedef ActorComponent *(*ComponentCreator)();

class Actor
{
	friend class ActorFactory;

public:
	virtual ~Actor() {}
	virtual void init(XMLElement *xmlData) {}
	virtual void postInit() {}
	virtual void update(double elapsedTime) {}
	virtual void destroy() {}

protected:
	void addComponent(ActorComponent *component) {};

	map<ComponentType, ActorComponent> components;
	unsigned long actorId;

};


//////////////////// ACTOR FACTORY ////////////////////

class ActorFactory
{
public:
	ActorFactory();
	~ActorFactory();
	Actor * createActor(const char *actorFilename);
	ActorComponent * createActorComponent(XMLElement *xmlData);

private:
	unsigned long lastActorId;
	map<string, ComponentCreator> componentCreatorMap;

	unsigned long getNextActorId() { lastActorId++; return lastActorId; }
};



#endif