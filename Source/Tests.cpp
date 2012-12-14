#include "Tests.h"

void testXml()
{
	static const char* xml = 
        "<?xml version=\"1.0\"?>"
        "<!DOCTYPE PLAY SYSTEM \"play.dtd\">"
        "<PLAY>"
        "<TITLE>A Midsummer Night's Dream</TITLE>"
        "</PLAY>";

	tinyxml2::XMLDocument doc;
	if (doc.LoadFile("test.xml") != tinyxml2::XML_NO_ERROR)
	{
		cout << "Error" << endl;
	}
	else
	{
		tinyxml2::XMLElement *visual = doc.FirstChildElement("Actor")->FirstChildElement("VisualComponent");
		tinyxml2::XMLElement *texture = visual->FirstChildElement("Texture");
		const char *tText = texture->GetText();

		tinyxml2::XMLElement *pos = visual->FirstChildElement("Position");
		int x = pos->IntAttribute("x");
		int y = pos->IntAttribute("y");
		int z = pos->IntAttribute("z");

		cout << "Texture: " << tText << endl;
		cout << "Position: (" << x << ", " << y << ", " << z << ")" << endl << endl;
	}
}

void testActors()
{
	ActorFactory *af = new ActorFactory();
	Actor *a1 = af->createActor("test1.xml");
	Actor *a2 = af->createActor("test2.xml");
	Actor *a3 = af->createActor("test3.xml");
	Actor *a4 = af->createActor("test4.xml");

	a1->print();
	a2->print();
	a3->print();
	a4->print();
}

void testVectors()
{
	Vec2D<int> v1(13, 17);
	Vec2D<int> v2(14, 19);
	cout << v1.toStr() << endl;
	cout << v2.toStr() << endl;
	Vec2D<int> v3 = v1 - v2;
	cout << v3.toStr() << endl;
	v2 = v1 * v3;
	cout << v2.toStr() << endl;
	v1 = Vec2D<int>(-13, -34);

	cout << boolalpha << (v1 == v2) << endl;
	cout << boolalpha << (v1 == v3) << endl;
}

