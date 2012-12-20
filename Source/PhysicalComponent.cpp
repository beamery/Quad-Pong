#include "Actor.h"

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
	{
		movable = movableElt->BoolAttribute("value");
	}

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
		double r = circleElt->DoubleAttribute("radius");
		Circle *circ = new Circle(r);
		shape = (Shape *)circ;
	}
	// Initialize rectangle
	else
	{
		double w = rectElt->DoubleAttribute("w");
		double h = rectElt->DoubleAttribute("h");
		Rect *rect = new Rect(w, h);
		shape = (Shape *)rect;
	}

	// Initialize position
	XMLElement *posElt = xmlData->FirstChildElement("Position");
	pos.x = posElt->DoubleAttribute("x");
	pos.y = posElt->DoubleAttribute("y");
}

void PhysicalComponent::postInit() {}

void PhysicalComponent::update(double totalTime, double elapsedTime) 
{
	// apply forces to the object
	for (auto i = forces.begin(); i != forces.end(); i++)
	{
		vel = vel + ((*i) * elapsedTime);
	}
	// apply impulses to the object and then get rid of them
	for (auto i = impulses.begin(); i != impulses.end(); i++)
	{
		vel = vel + ((*i) * elapsedTime);
	}
	impulses.clear();
	
	// update the position
	pos = pos + vel;
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
	for (auto i = forces.begin(); i != forces.end(); i++)
	{
		if (*i == f)
		{
			forces.erase(i);
			return;
		}

	}

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
	for (auto i = forces.begin(); i != forces.end(); i++)
	{
		cout << "\t\t" << "(" << (*i).x << ", " << (*i).y << ")" << endl;
	}
	cout << "\t" << "impulses:" << endl;
	for (auto i = impulses.begin(); i != impulses.end(); i++)
	{
		cout << "\t\t" << "(" << (*i).x << ", " << (*i).y << ")" << endl;
	}
}

