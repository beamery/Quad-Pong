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
	static bool collide(bm::Rect *r, Vec2D<double> rPos, bm::Circle *c, Vec2D<double> cPos);
	static bool collide(bm::Rect *r1, Vec2D<double> r1Pos, bm::Rect *r2, Vec2D<double> r2Pos);
	static bool collide(bm::Circle *c1, Vec2D<double> c1Pos, bm::Circle *c2, Vec2D<double> c2Pos);
};


#endif