#include <SFML/OpenGL.hpp>
// FOR TESTING, REMOVE LATER

#include "GameState.h"
#include "Event.h"
#include "Actor.h"
#include "Collision.h"

void InnerGameState::init()
{
	timer = 0;
	ActorFactory af;
	me = af.createActor("Circle.xml");
	rect = af.createActor("Circle.xml");
	((PhysicalComponent*)me->getComponent(PHYSICAL))->addImpulse(Vec2D<double>(20, 20));
	humanView = new HumanView(me);
}

void InnerGameState::update(double totalTime, double elapsedTime)
{
	glClearColor(0.2f, 0.2f, 0.4f, 1.0f);

	timer += elapsedTime;
	
	me->update(totalTime, elapsedTime);

	PhysicalComponent *p1 = (PhysicalComponent*)me->getComponent(PHYSICAL);
	PhysicalComponent *p2 = (PhysicalComponent*)rect->getComponent(PHYSICAL);
	VisualComponent *vRect = (VisualComponent*)rect->getComponent(VISUAL);

	if (Collision::collide(p1, p2))
		vRect->setColor(200, 0, 0, 200);
	else
		vRect->setColor(0, 200, 0, 200);

	humanView->drawActor(me);
	humanView->drawActor(rect);

	if (timer > 10)
	{
		ChangeGameStateEvtData *data = 
			new ChangeGameStateEvtData("game_over", "inner_game", true);

		EventManager::get()->queueEvent((IEventData*)data);
	}

}
