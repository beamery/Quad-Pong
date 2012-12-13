#include "Actor.h"

void Actor::init(XMLElement *xmlData)
{

}

void Actor::postInit()
{

}

void Actor::update(double totalTime, double elapsedTime)
{
	// update all components
	for (auto it = components.begin(); it != components.end(); it++)
	{
		((*it).second)->update(totalTime, elapsedTime);
	}
}

void Actor::destroy() 
{

}

ActorComponent * Actor::getComponent(ComponentType type)
{
	if (components.count(type) > 0)
		return components[type];
	else
		throw NO_SUCH_COMPONENT_ERR;
}

void Actor::print()
{
	cout << "Info for actor " << actorId << endl;
	cout << "--------------------" << endl;
	for (auto it = components.begin(); it != components.end(); it++)
	{
		((*it).second)->print();
		cout << endl;
	}
}


void Actor::addComponent(ActorComponent *component)
{
	if (components.count(component->getComponentType()) > 0)
		throw DUPLICATE_COMPONENT_ERR;
	else
		components[component->getComponentType()] = component;
}




