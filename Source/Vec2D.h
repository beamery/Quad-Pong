#ifndef VEC2D_H
#define VEC2D_H

#include <sstream>
#include <string>
#include <cmath>

using namespace std;

template <typename E>
class Vec2D
{
public:
	E x, y;

	Vec2D() {}
	Vec2D(E x, E y);
	Vec2D(const Vec2D<E> &v2);
	void operator=(const Vec2D &v2);
	Vec2D & operator+(const Vec2D &v2);
	Vec2D & operator-(const Vec2D &v2);
	Vec2D & operator*(const Vec2D &v2);
	Vec2D & operator*(const double d);
	bool operator==(const Vec2D &v2);
	bool operator!=(const Vec2D &v2);
	string toStr();
	double length();
	Vec2D & normalize();
};

template <typename E>
Vec2D<E>::Vec2D(E x, E y) : x(x), y(y) {}

template <typename E>
Vec2D<E>::Vec2D(const Vec2D<E> &v2) : x(v2.x), y(v2.y) {}

template <typename E>
void Vec2D<E>::operator=(const Vec2D &v2)
{
	x = v2.x;
	y = v2.y;
}

template <typename E>
Vec2D<E> & Vec2D<E>::operator+(const Vec2D &v2)
{
	Vec2D *v3 = new Vec2D();
	v3->x = x + v2.x;
	v3->y = y + v2.y;

	return *v3;
}

template <typename E>
Vec2D<E> & Vec2D<E>::operator-(const Vec2D &v2)
{
	Vec2D *v3 = new Vec2D();
	v3->x = x - v2.x;
	v3->y = y - v2.y;

	return *v3;
}

template <typename E>
Vec2D<E> & Vec2D<E>::operator*(const Vec2D &v2)
{
	Vec2D *v3 = new Vec2D();
	v3->x = x * v2.x;
	v3->y = y * v2.y;

	return *v3;
}

template <typename E>
Vec2D<E> & Vec2D<E>::operator*(const double d)
{
	Vec2D *v3 = new Vec2D();
	v3->x = x * d;
	v3->y = y * d;

	return *v3;
}

template <typename E>
bool Vec2D<E>::operator==(const Vec2D &v2)
{
	return (x == v2.x && y == v2.y);
}

template <typename E>
bool Vec2D<E>::operator!=(const Vec2D &v2)
{
	return !(x == v2.x && y == v2.y);
}

template <typename E>
string Vec2D<E>::toStr()
{
	ostringstream oss;
	oss << "[" << x << " " << y << "]";
	return oss.str();
}

template <typename E>
double Vec2D<E>::length()
{
	double xSquared = x * x;
	double ySquared = y * y;
	return sqrt(xSquared + ySquared);
}

template <typename E>
Vec2D<E> & Vec2D<E>::normalize()
{
	Vec2D<E> *tmp = new Vec2D<E>(x / length(), y / length());
	return *tmp;
}


#endif