#include "Actor.h"

void TestComponent1::init(XMLElement *xmlData)
{
	name = xmlData->FirstChildElement("Name")->GetText();
	x = xmlData->FirstChildElement("Position")->DoubleAttribute("x");
	y = xmlData->FirstChildElement("Position")->DoubleAttribute("y");
	speed = atof(xmlData->FirstChildElement("Speed")->GetText());
}

void TestComponent1::postInit()
{
	name = name + "Test";
}

void TestComponent1::update(double elapsedTime) 
{
	x += speed * elapsedTime;
	y += speed * elapsedTime;
}

void TestComponent1::print()
{
	cout << "Test1:" << endl;
	cout << "\t" << "name:\t\t " << name << endl;
	cout << "\t" << "position:\t (" << x << ", " << y << ")" << endl;
	cout << "\t" << "speed:\t\t " << speed << endl;
}



void TestComponent2::init(XMLElement *xmlData)
{
	texture = xmlData->FirstChildElement("Texture")->GetText();
	r = xmlData->FirstChildElement("Color")->IntAttribute("r") / 255.0f;
	g = xmlData->FirstChildElement("Color")->IntAttribute("g") / 255.0f;
	b = xmlData->FirstChildElement("Color")->IntAttribute("b") / 255.0f;
	a = xmlData->FirstChildElement("Color")->IntAttribute("a") / 255.0f;
}

void TestComponent2::postInit()
{
	texture = texture + ".tex";
}

void TestComponent2::update(double elapsedTime) 
{
	int rInc = rand() % 3;
	int gInc = rand() % 3;
	int bInc = rand() % 3;

	if (rP)
		r = (r + elapsedTime);
	else
		r = (r - elapsedTime);
	if (r > 1)
		rP = false;
	else if (r < 0)
		rP = true;

	if (rP)
		g = (g + elapsedTime);
	else
		g = (g - elapsedTime);
	if (g > 1)
		gP = false;
	else if (r < 0)
		gP = true;

	if (rP)
		g = (g + elapsedTime);
	else
		g = (g - elapsedTime);
	if (b > 1)
		bP = false;
	else if (r < 0)
		bP = true;
}

void TestComponent2::print()
{
	cout << "Test2:" << endl;
	cout << "\t" << "texture:\t " << texture << endl;
	cout << "\t" << "color:\t\t (" << r << ", " << g << ", " << b << ", " << a << ")" << endl;
}

void TestComponent2::getColor(float &rc, float &gc, float &bc)
{
	rc = r;
	gc = g;
	bc = b;
}
