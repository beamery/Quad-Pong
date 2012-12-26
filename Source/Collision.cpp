#include "Collision.h"

using namespace bm;

bool Collision::collide(PhysicalComponent *c1, PhysicalComponent *c2)
{
	// if either object is not collidable, no collision occurs
	if (!c1->canCollide() || !c2->canCollide())
		return false;

	// RECT-RECT collision
	if (c1->getShape()->type == RECTANGLE && c2->getShape()->type == RECTANGLE)
		return collide((Rect*)c1->getShape(), c1->getPos(), (Rect*)c2->getShape(), c2->getPos());

	// CIRC-CIRC collision
	else if (c1->getShape()->type == CIRCLE && c2->getShape()->type == CIRCLE)
		return collide((Circle*)c1->getShape(), c1->getPos(), (Circle*)c2->getShape(), c2->getPos());

	// CIRC-RECT collision
	else if (c1->getShape()->type == CIRCLE && c2->getShape()->type == RECTANGLE)
		return collide((Rect*)c2->getShape(), c2->getPos(), (Circle*)c1->getShape(), c1->getPos());

	// RECT-CIRC collision
	else if (c1->getShape()->type == RECTANGLE && c2->getShape()->type == CIRCLE)
		return collide((Rect*)c1->getShape(), c1->getPos(), (Circle*)c2->getShape(), c2->getPos());
	else
		throw BAD_SHAPE_ERR;
}

bool Collision::collide(Rect *r, Vec2D<double> rPos, Circle *c, Vec2D<double> cPos)
{
	double centerDistX = abs(cPos.x - rPos.x);
	double centerDistY = abs(cPos.y - rPos.y);

	// rule out impossible collisions
	if (centerDistX > (r->width / 2 + c->radius)) return false;
	if (centerDistY > (r->height / 2 + c->radius)) return false;

	// check collisions in 1D
	if (centerDistX <= (r->width / 2)) { return true; } 
    if (centerDistY <= (r->height / 2)) { return true; }

	// check collisions with corner of rectangle
	double cornerDistance_sq = 
		(centerDistX - r->width / 2) * (centerDistX - r->width / 2) +
		(centerDistY - r->height / 2) * (centerDistY - r->height / 2);

	return (cornerDistance_sq <= (c->radius * c->radius));
}

bool Collision::collide(Rect *r1, Vec2D<double> r1Pos, Rect *r2, Vec2D<double> r2Pos)
{
	double left1 = r1Pos.x - (r1->width / 2);
	double left2 = r2Pos.x - (r2->width / 2);
	double right1 = r1Pos.x + (r1->width / 2);
	double right2 = r2Pos.x + (r2->width / 2);
	double top1 = r1Pos.y - (r1->height / 2);
	double top2 = r2Pos.y - (r2->height / 2);
	double bottom1 = r1Pos.y + (r1->height / 2);
	double bottom2 = r2Pos.y + (r2->height / 2);

	if (bottom1 < top2) return false;
	if (top1 > bottom2) return false;
	if (left1 > right2) return false;
	if (right1 < left2) return false;

	return true;
}

bool Collision::collide(Circle *c1, Vec2D<double> c1Pos, Circle *c2, Vec2D<double> c2Pos)
{
	Vec2D<double> distVec = c1Pos - c2Pos;
	return (distVec.length() <= c1->radius + c2->radius);
}