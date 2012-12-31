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
#include "Texture.h"
#include "Event.h"

using namespace std;

typedef tinyxml2::XMLElement XMLElement;
typedef tinyxml2::XMLDocument XMLDoc;
typedef tinyxml2::XMLAttribute XMLAttrib;
typedef unsigned long ActorID;


class Actor;
//////////////////// ACTOR COMPONENT ////////////////////

enum ComponentType
{
	BASE_COMPONENT, VISUAL, PHYSICAL, PADDLE, TEST1, TEST2, BALL,
};

enum Orientation
{
	VERTICAL, HORIZONTAL
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
	friend class HumanView;

public:
	VisualComponent() {}
	virtual ~VisualComponent();
	virtual void init(XMLElement *xmlData);
	virtual void postInit();
	virtual void update(double totalTime, double elapsedTime);
	virtual ComponentType getComponentType() { return VISUAL; }
	bool isVisible() { return visible; }
	void setColor(int r, int g, int b, int a);
	void print();

private:
	bool visible;
	bm::Texture *texture;
	double width, height;
	bm::Color colorData;

	// TL, BL, TR, BR
	vector< Vec2D<double> > vertexData;
	vector< Vec2D<double> > textureData;
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
	bool canCollide() { return collidable; }
	bm::Shape * getShape() { return shape; }
	Vec2D<double> getPos() { return pos; }
	Vec2D<double> getVelocity() { return vel; }
	Vec2D<double> getForces() { return forces; }
	Vec2D<double> getImpulses() { return impulses; }
	void addImpulse(Vec2D<double> i) { impulses = impulses + i; }
	void addForce(Vec2D<double> f) { forces = forces + f; }
	void clearForces() { forces.x = 0; forces.y = 0; }
	void clearVelocity() { vel.x = 0; vel.y = 0; }
	void setPos(double x, double y);
	void removeForce(Vec2D<double> f);

	void print();
	

private:
	bool movable;
	bool collidable;
	bm::Shape *shape;
	Vec2D<double> pos;
	Vec2D<double> vel;
	Vec2D<double> forces;
	Vec2D<double> impulses;
};

class PaddleComponent : ActorComponent, IEventListener
{
public:
	virtual void init(XMLElement *xmlData);
	virtual void postInit();
	virtual void update(double totalTime, double elapsedTime);
	virtual void processEvent(IEventData *e);
	void onPaddleMove(PaddleMoveEvtData *event);
	void onBumperPaddleColl(BumperPaddleCollEvtData *event);
	virtual ComponentType getComponentType() { return PADDLE; }

	Orientation getOrientation() { return orientation; }
	void setPlayer(int p) { player = p; }

private:
	int player;
	double paddleForce;
	double forceOfFriction;
	Orientation orientation;

};

class BallComponent : ActorComponent, IEventListener
{
public:
	virtual void postInit();
	virtual void processEvent(IEventData *e);
	void onBallPaddleColl(BallPaddleCollEvtData *event);
	void onBallBumperColl(BallBumperCollEvtData *event);
	virtual ComponentType getComponentType() { return BALL; }
};



//////////////////// ACTOR ////////////////////
class Actor
{
	friend class ActorFactory;

public:
	Actor() {};
	virtual ~Actor() {}
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
	ActorID actorId;

};


//////////////////// ACTOR FACTORY ////////////////////

typedef ActorComponent *(*ComponentCreator)();
class ActorFactory
{
public:
	ActorFactory(bool global = false);
	~ActorFactory() {}
	Actor * createActor(const char *actorFilename);
	static ActorFactory * get() { return globalActorFactory; }

private:
	unsigned long lastActorId;
	map<string, ComponentCreator> componentCreatorMap;
	static ActorFactory *globalActorFactory;

	unsigned long getNextActorId() { lastActorId++; return lastActorId; }
	ActorComponent * createActorComponent(XMLElement *xmlData);
};


#endif