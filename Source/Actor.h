#ifndef ACTOR_H
#define ACTOR_H

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "tinyxml2.h"
#include "Error.h"
#include "Utils.h"
#include "Shape.h"
#include "Error.h"

using namespace std;

typedef tinyxml2::XMLElement XMLElement;
typedef tinyxml2::XMLDocument XMLDoc;
typedef tinyxml2::XMLAttribute XMLAttrib;



class Actor;
//////////////////// ACTOR COMPONENT ////////////////////

enum ComponentType
{
	BASE_COMPONENT, VISUAL, PHYSICAL, TEST1, TEST2,
};

class ActorComponent
{
	friend class ActorFactory;

public:
	Actor *parent;

	virtual ~ActorComponent() {}
	virtual void init(XMLElement *xmlData) {}
	virtual void postInit() {}
	virtual void update(double totalTime, double elapsedTime) {}
	virtual ComponentType getComponentType() { return BASE_COMPONENT; }
	virtual void print() {}
};


class TestComponent1 : ActorComponent
{
public:
	virtual void init(XMLElement *xmlData);
	virtual void postInit();
	virtual void update(double totalTime, double elapsedTime);
	virtual void print();
	virtual ComponentType getComponentType() { return TEST1; }

private:
	string name;
	double x, y;
	double speed;
	
private:

};
class TestComponent2 : ActorComponent
{
public:

	virtual void init(XMLElement *xmlData);
	virtual void postInit();
	virtual void update(double totalTime, double elapsedTime);
	virtual void print();
	virtual ComponentType getComponentType() { return TEST2; }

	void getColor(float &rc, float &gc, float &bc);

private:
	string texture;
	float r, g, b, a;
	bool rP, gP, bP;
	
};

class VisualComponent : ActorComponent
{
public:
	// METHOD STUBS
	// TODO: override
	virtual ~VisualComponent();
	virtual void init(XMLElement *xmlData);
	virtual void postInit();
	virtual void update(double totalTime, double elapsedTime);
	virtual ComponentType getComponentType() { return VISUAL; }
};

class PhysicalComponent : ActorComponent
{
public:

	virtual ~PhysicalComponent();
	virtual void init(XMLElement *xmlData);
	virtual void postInit();
	virtual void update(double totalTime, double elapsedTime);
	virtual ComponentType getComponentType() { return PHYSICAL; }

	bool isMovable() { return movable; }
	Shape * getShape() { return shape; }
	Vec2D<double> getPos() { return pos; }
	Vec2D<double> getVelocity() { return vel; }
	vector< Vec2D<double> > getForces() { return forces; }
	vector< Vec2D<double> > getImpulses() { return impulses; }
	void addImpulse(Vec2D<double> i) { impulses.push_back(i); }
	void addForce(Vec2D<double> f) { forces.push_back(f); }
	void setPos(double x, double y);
	void removeForce(Vec2D<double> f);

	void print();
	

private:
	bool movable;
	Shape *shape;
	Vec2D<double> pos;
	Vec2D<double> vel;
	vector< Vec2D<double> > forces;
	vector< Vec2D<double> > impulses;
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
	virtual void update(double totalTime, double elapsedTime);
	virtual void destroy();
	unsigned long getId() { return actorId; }
	virtual ActorComponent * getComponent(ComponentType type);
	virtual void print();

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

private:
	unsigned long lastActorId;
	map<string, ComponentCreator> componentCreatorMap;

	unsigned long getNextActorId() { lastActorId++; return lastActorId; }
	ActorComponent * createActorComponent(XMLElement *xmlData);
};


#endif