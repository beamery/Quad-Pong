#ifndef SHAPE_H
#define SHAPE_H

#include "Utils.h"

enum ShapeID
{
	CIRCLE, RECTANGLE
};


struct Shape
{
	ShapeID type;
	Shape(ShapeID type) : type(type) {}
};

struct Circle : Shape
{
	double radius;
	Circle(double r) : Shape(CIRCLE), radius(r) {}
};

struct Rect : Shape
{
	double width, height;
	Rect(double w, double h) : Shape(RECTANGLE), width(w), height(h) {}
};




#endif