#ifndef ACTOR_H
#define ACTOR_H

#include <map>
#include <string>
#include "tinyxml2.h"
#include "Error.h"

using namespace std;

typedef tinyxml2::XMLElement XMLElement;
typedef tinyxml2::XMLDocument XMLDoc;
typedef tinyxml2::XMLAttribute XMLAttrib;




//////////////////// ACTOR COMPONENT ////////////////////


enum ComponentType
{
	BASE_COMPONENT, VISUAL, TEST1, TEST2
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


class TestComponent1 : ActorComponent
{
	virtual void init(XMLElement *xmlData);
	virtual void postInit();
	virtual void update(double elapsedTime);
	virtual ComponentType getComponentType() { return TEST1; }

};
class TestComponent2 : ActorComponent
{
	virtual ~TestComponent2();
	virtual void init(XMLElement *xmlData);
	virtual void postInit();
	virtual void update(double elapsedTime);
	virtual ComponentType getComponentType() { return TEST2; }
};



class VisualComponent : ActorComponent
{
public:
	// METHOD STUBS
	// TODO: override
	virtual ~VisualComponent();
	virtual void init(XMLElement *xmlData);
	virtual void postInit();
	virtual void update(double elapsedTime);
	virtual ComponentType getComponentType() { return VISUAL; }
};



//////////////////// ACTOR ////////////////////

class Actor
{
	friend class ActorFactory;

public:
	Actor() {};
	virtual ~Actor() {};
	virtual void init(XMLElement *xmlData);
	virtual void postInit();
	virtual void update(double elapsedTime);
	virtual void destroy();
	unsigned long getId() { return actorId; }
	virtual ActorComponent * getComponent(ComponentType type);

protected:
	void addComponent(ActorComponent *component);

	map<ComponentType, ActorComponent*> components;
	unsigned long actorId;

};


//////////////////// ACTOR FACTORY ////////////////////

typedef ActorComponent *(*ComponentCreator)();
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