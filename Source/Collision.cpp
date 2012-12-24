#include "Collision.h"

bool Collision::collide(PhysicalComponent *c1, PhysicalComponent *c2)
{
	// if either object is not collidable, no collision occurs
	if (!c1->canCollide() || !c2->canCollide())
		return false;

	// RECT-RECT collision
	if (c1->getShape()->type == RECTANGLE && c2->getShape()->type == RECTANGLE)
		return collide((Rect*)c1, c1->getPos(), (Rect*)c2, c2->getPos());

	// CIRC-CIRC collision
	else if (c1->getShape()->type == CIRCLE && c2->getShape()->type == CIRCLE)
		return collide((Circle*)c1, c1->getPos(), (Circle*)c2, c2->getPos());

	// CIRC-RECT collision
	else if (c1->getShape()->type == CIRCLE && c2->getShape()->type == RECTANGLE)
		return collide((Rect*)c2, c2->getPos(), (Circle*)c1, c1->getPos());

	// RECT-CIRC collision
	else if (c1->getShape()->type == RECTANGLE && c2->getShape()->type == CIRCLE)
		return collide((Rect*)c1, c1->getPos(), (Circle*)c2, c2->getPos());
	else
		throw BAD_SHAPE_ERR;
}

bool Collision::collide(Rect *r, Vec2D<double> rPos, Circle *c, Vec2D<double> cPos)
{
	// check collisions with corners of rect
	double rLeft = rPos.x - (r->width / 2);
	double rRight = rPos.x + (r->width / 2);
	double rTop = rPos.y - (r->height / 2);
	double rBottom = rPos.y + (r->height / 2);
	Vec2D<double> rTopRight(rRight, rTop);
	Vec2D<double> rTopLeft(rLeft, rTop);
	Vec2D<double> rBottomRight(rRight, rBottom);
	Vec2D<double> rBottomLeft(rLeft, rBottom);

	// If the distance to any of the corners is smaller than the radius of the 
	// circle, then the two shapes overlap
	if ((cPos - rTopRight).length() <= c->radius) return true;
	if ((cPos - rTopLeft).length() <= c->radius) return true;
	if ((cPos - rBottomRight).length() <= c->radius) return true;
	if ((cPos - rBottomLeft).length() <= c->radius) return true;
	
	// If we get here, then the circle does not intersect any of the corners

	double cLeft = cPos.x - c->radius;
	double cRight = cPos.x + c->radius;
	double cTop = cPos.y - c->radius;
	double cBottom = cPos.y + c->radius;

	// Now check straight-line collisions
	if (cBottom < rTop) return false;
	if (cTop > rBottom) return false;
	if (cLeft > rRight) return false;
	if (cRight < rLeft) return false;

	return true;
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