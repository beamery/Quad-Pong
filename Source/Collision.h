#ifndef COLLISION_H
#define COLLISION_H

#include "Shape.h"
#include "Utils.h"
#include "Actor.h"

class Collision
{
public:
	static bool collide(PhysicalComponent *s1, PhysicalComponent *s2);

private:
	static bool collide(Rect *r, Vec2D<double> rPos, Circle *c, Vec2D<double> cPos);
	static bool collide(Rect *r1, Vec2D<double> r1Pos, Rect *r2, Vec2D<double> r2Pos);
	static bool collide(Circle *c1, Vec2D<double> c1Pos, Circle *c2, Vec2D<double> c2Pos);
};


#endif