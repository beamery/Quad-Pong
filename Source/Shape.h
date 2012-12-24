#ifndef SHAPE_H
#define SHAPE_H

#include "Utils.h"

enum ShapeID
{
	CIRCLE, RECTANGLE
};


namespace bm
{
	struct Shape
	{
		ShapeID type;
		Shape(ShapeID type) : type(type) {}
	};
};

struct Circle : bm::Shape
{
	double radius;
	Circle(double r) : Shape(CIRCLE), radius(r) {}
};

struct Rect : bm::Shape
{
	double width, height;
	Rect(double w, double h) : Shape(RECTANGLE), width(w), height(h) {}
};




#endif