#include "Views.h"
#include <SFML/OpenGL.hpp>

HumanView::HumanView(Actor *a) : 
	actor(a),
	keyboardHandler(new KeyboardHandler()), 
	pointerHandler(new PointerHandler())
{}

void HumanView::update(double totalTime, double elapsedTime)
{

}

void HumanView::drawActor(Actor *a)
{
	try
	{
		PhysicalComponent *phys = (PhysicalComponent*)a->getComponent(PHYSICAL);
		VisualComponent *vis = (VisualComponent*)a->getComponent(VISUAL);
		vector< Vec2D<double> > vertices;
		bm::Color col = vis->colorData;

		// if the actor is invisible, don't render it
		if (!vis->isVisible())
			return;

		// Apply position offset to each vertex
		for (auto i = vis->vertexData.begin(); i != vis->vertexData.end(); i++)
		{
			vertices.push_back((*i) + phys->getPos());
		}
		
		// if there is a texture to render, set it up
		if (vis->texture != nullptr)
		{
			glBindTexture(GL_TEXTURE_2D, vis->texture->id);
			glEnable(GL_TEXTURE_2D);
		}

		// Draw the actor
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i < vertices.size(); i++)
		{
			glTexCoord2d(vis->textureData[i].x, vis->textureData[i].y);
			glColor4ub(col.r, col.g, col.b, col.a); // unsigned-byte (0-255)
			glVertex2d(vertices[i].x, vertices[i].y);
		}
		// Cleanup
		glEnd();
		glDisable(GL_TEXTURE_2D);

	} 
	catch (Status s)
	{
		if (s != NO_SUCH_COMPONENT_ERR)
			throw s;
	}
}

void HumanView::drawText(/* params */)
{

}

void HumanView::drawUI(/* params */)
{

}

void HumanView::setCameraOffset(/* params */)
{

}
