#include "Tests.h"
#include "Error.h"

void testXml()
{
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

		tinyxml2::XMLElement *nothing = visual->FirstChildElement("Nothing");
		cout << "pointer to nothing is null: " << boolalpha << (nothing == nullptr) << endl;

		cout << "Texture: " << tText << endl;
		cout << "Position: (" << x << ", " << y << ", " << z << ")" << endl << endl;
	}
}

void testActors()
{
	ActorFactory *af = new ActorFactory();
	try 
	{
		Actor *phys = af->createActor("Circle.xml");
		phys->print();
	} 
	catch(Status e)
	{
		Error::print(e);
	}



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

void drawCircle(float cx, float cy, float r, int num_segments) 
{ 
	glBegin(GL_TRIANGLE_STRIP); 
	for(int ii = 0; ii <= num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 
		glVertex2f(cx, cy);

	} 
	glEnd(); 
}

void drawTriangle(Actor *background, double totalTime, double elapsedTime)
{
	float r, g, b;
	background->update(totalTime, elapsedTime);
	((TestComponent2*)background->getComponent(TEST2))->getColor(r, g, b);

	glBegin(GL_TRIANGLES);
	{
		glColor3f(r, g, b);
		glVertex2f(350, 350);
		glColor3f(b, g, r);
		glVertex2f(450, 350);
		glColor3f(g, r, b);
		glVertex2f(400, 250);
	}
	glEnd();
}


// TODO: implement
void drawSprite()
{
	sf::Image img_data;
	if (!img_data.loadFromFile("../Assets/SpriteLogo.jpg"))
	{
		cerr << "Could not load ../Assets/SpriteLogo.jpg" << endl;
	}
	GLuint textureHandle;
	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glTexImage2D(
				 GL_TEXTURE_2D, 0, GL_RGBA, 
				 img_data.getSize().x, img_data.getSize().y,
				 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data.getPixelsPtr()
				);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glEnable(GL_TEXTURE_2D);
	
	glBegin(GL_TRIANGLE_STRIP);
	{
		glTexCoord2d(0.0, 0.0);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glVertex2d(300, 200);

		glTexCoord2d(0.0, 1.0);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glVertex2d(300, 400);

		glTexCoord2d(1.0, 0.0);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glVertex2d(500, 200);

		glTexCoord2d(1.0, 1.0);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glVertex2d(500, 400);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
