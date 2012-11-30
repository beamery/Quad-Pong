#ifndef ACTOR_H
#define ACTOR_H

#include <map>
#include "ActorComponent.h"

using namespace std;

class Actor
{
public:
	virtual void init();
	virtual void update(double elapsedTime);
	virtual void destroy();

protected:
	map<ComponentType, ActorComponent> components;

};


#endif