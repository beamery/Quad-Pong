#include "Actor.h"

using namespace bm;

PhysicalComponent::~PhysicalComponent()
{
	delete shape;
}


void PhysicalComponent::init(XMLElement *xmlData)
{
	// Initialize movable
	XMLElement *movableElt = xmlData->FirstChildElement("Movable");
	if (movableElt == nullptr)
		movable = true;
	else
		movable = movableElt->BoolAttribute("value");

	// Initialize collidable
	XMLElement *collidableElt = xmlData->FirstChildElement("Collidable");
	if (collidableElt == nullptr)
		collidable = true;
	else
		collidable = collidableElt->BoolAttribute("value");

	// Initialize shape
	XMLElement *circleElt = xmlData->FirstChildElement("Circle");
	XMLElement *rectElt = xmlData->FirstChildElement("Rect");

	// Component should only be assigned one shape
	if (circleElt != nullptr && rectElt != nullptr)
		throw MULTIPLE_SHAPE_ERR;
	// Throw error if no shape is assigned
	else if (circleElt == nullptr && rectElt == nullptr)
		throw NULL_SHAPE_ERR;

	// Initialize circle
	else if (circleElt != nullptr) 
	{
		double r = circleElt->DoubleAttribute("r");
		Circle *circ = new Circle(r);
		shape = (bm::Shape *)circ;
	}
	// Initialize rectangle
	else
	{
		double w = rectElt->DoubleAttribute("w");
		double h = rectElt->DoubleAttribute("h");
		Rect *rect = new Rect(w, h);
		shape = (bm::Shape *)rect;
	}

	// Initialize position
	XMLElement *posElt = xmlData->FirstChildElement("Position");
	pos.x = posElt->DoubleAttribute("x");
	pos.y = posElt->DoubleAttribute("y");
}

void PhysicalComponent::postInit() 
{
	forces.x = 0; 
	forces.y = 0;
	impulses.x = 0;
	impulses.y = 0;
	vel.x = 0;
	vel.y = 0;
}

void PhysicalComponent::update(double totalTime, double elapsedTime) 
{
	if (movable)
	{
		// apply forces to the object
		vel = vel + (forces * elapsedTime);
		// apply impulses to the object and then get rid of them
		vel = vel + impulses;
		impulses.x = 0;
		impulses.y = 0;
		
		// update the position
		pos = pos + (vel * elapsedTime);
	}
}

void PhysicalComponent::setPos(double x, double y)
{
	if (movable)
	{
		pos.x = x;
		pos.y = y;
	}
	else
		throw OBJ_NOT_MOVABLE;
}


void PhysicalComponent::removeForce(Vec2D<double> f)
{
	forces = forces - f;
}

void PhysicalComponent::print()
{
	cout << "PhysicalComponent:" << endl;
	cout << "\t" << "movable:\t" << boolalpha << movable << endl;
	cout << "\t" << "shape:\t\t";
	if (shape->type == CIRCLE)
	{
		cout << "circle" << endl; 
		cout << "\t  " << "radius: " << ((Circle*)shape)->radius << endl;
	}
	else
	{
		cout << "rectangle" << endl;
		cout << "\t  " << "height: " << ((Rect*)shape)->height << endl;
		cout << "\t  " << "width:  " << ((Rect*)shape)->width << endl;
	}
	cout << "\t" << "pos:\t\t(" << pos.x << ", " << pos.y << ")" << endl;
	cout << "\t" << "forces:" << endl;
	cout << "\t\t" << "(" << forces.x << ", " << forces.y << ")" << endl;
	cout << "\t" << "impulses:" << endl;
	cout << "\t\t" << "(" << impulses.x << ", " << impulses.y << ")" << endl;
}

