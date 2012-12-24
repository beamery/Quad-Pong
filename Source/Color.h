#ifndef COLOR_H
#define COLOR_H

namespace bm
{
	struct Color
	{
		int r, g, b, a;
		Color(int red, int green, int blue, int alpha) :
			r(red), g(green), b(blue),  a(alpha) {}
		Color() : r(0), g(0), b(0), a(0) {}
	};
};

#endif